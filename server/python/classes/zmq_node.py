import zmq
import socket
import threading
import time
import json

class ZMQNode:
    """
    A ZeroMQ node that subscribes to a main pub/sub channel and sends periodic hello messages.
    """
    
    def __init__(self, name, req_rep_port=None, pub_sub_port=None, ip_address=None, request_callback=None):
        """
        Initialize the ZMQ node.
        
        Args:
            name: Unique name for this node
            req_rep_port: Port for this node's req/rep channel (optional)
            pub_sub_port: Port for the main pub/sub channel (optional)
            ip_address: IP address to connect to. If None, uses localhost and detects own IP
            request_callback: Optional callback function to process incoming requests.
                             Should accept a dict and return a dict response.
        """
        self.name = name
        self.req_rep_port = req_rep_port
        self.pub_sub_port = pub_sub_port
        
        # Determine connection address and own IP
        self.ip_address = ip_address if ip_address else self._get_ip_address()
        
        # Create pub_sub_address only if pub_sub_port is provided
        if pub_sub_port is not None:
            if ip_address:
                self.pub_sub_address = f"tcp://{ip_address}:{pub_sub_port}"
            else:
                self.pub_sub_address = f"tcp://localhost:{pub_sub_port}"
        else:
            self.pub_sub_address = None
        
        # Create req_rep_address only if req_rep_port is provided
        if req_rep_port is not None:
            # REP socket binds to all interfaces (0.0.0.0 for compatibility)
            self.req_rep_address = f"tcp://*:{req_rep_port}"
        else:
            self.req_rep_address = None
        
        self.req_rep_channel = f"{self.name}/priv"
        self.request_callback = request_callback
        
        self.context = zmq.Context()
        self.subscriber = None
        self.publisher = None
        self.rep_socket = None
        self.running = False
        self.hello_thread = None
        self.req_rep_thread = None
        
    def _get_ip_address(self):
        """Get the local IP address of this machine."""
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            s.connect(("8.8.8.8", 80))
            ip = s.getsockname()[0]
            s.close()
            return ip
        except Exception:
            return "127.0.0.1"
    
    def start(self):
        """Start the ZMQ node - subscribe to main channel and begin sending hello messages."""
        self.running = True
        
        # Subscribe to main/int channel only if pub_sub_port is provided
        if self.pub_sub_port and self.pub_sub_address:
            self.subscriber = self.context.socket(zmq.SUB)
            self.subscriber.connect(self.pub_sub_address)
            self.subscriber.setsockopt_string(zmq.SUBSCRIBE, "main/int")
            
            # Create publisher for sending hello messages
            self.publisher = self.context.socket(zmq.PUB)
            self.publisher.connect(self.pub_sub_address)
            
            # Start hello message thread
            self.hello_thread = threading.Thread(target=self._send_hello_periodically, daemon=True)
            self.hello_thread.start()
        
        # Create REP socket for handling incoming requests only if req_rep_port is provided
        if self.req_rep_port and self.request_callback:
            self.rep_socket = self.context.socket(zmq.REP)
            # Allow address reuse to avoid "Address in use" errors on restart
            self.rep_socket.setsockopt(zmq.LINGER, 0)
            self.rep_socket.bind(self.req_rep_address)
            
            # Start request-response listener thread
            self.req_rep_thread = threading.Thread(target=self._listen_for_requests, daemon=True)
            self.req_rep_thread.start()
        
    def stop(self):
        """Stop the ZMQ node and clean up resources."""
        self.running = False
        if self.hello_thread:
            self.hello_thread.join(timeout=1)
        if self.req_rep_thread:
            self.req_rep_thread.join(timeout=1)
        
        if self.subscriber:
            self.subscriber.close()
        if self.publisher:
            self.publisher.close()
        if self.rep_socket:
            self.rep_socket.close()
        self.context.term()
    
    def _send_hello_periodically(self):
        """Send hello message every 5 minutes."""
        while self.running:
            self._send_hello()
            time.sleep(300)  # 5 minutes
    
    def _send_hello(self):
        """Send a hello message with node information."""
        hello_msg = {
            "type": "hello",
            "name": self.name,
            "req_rep_channel": self.req_rep_channel,
            "ip_address": self.ip_address,
            "tcp_port": self.req_rep_port
        }
        
        topic = "main/int"
        message = json.dumps(hello_msg)
        self.publisher.send_string(f"{topic} {message}")
    
    def _listen_for_requests(self):
        """Listen for incoming requests on the REP socket and process them."""
        while self.running:
            try:
                # Poll with timeout to allow clean shutdown
                if self.rep_socket.poll(1000):  # 1 second timeout
                    # Receive request
                    request_str = self.rep_socket.recv_string()
                    
                    try:
                        # Parse JSON request
                        request_dict = json.loads(request_str)
                    except json.JSONDecodeError:
                        # Handle non-JSON requests
                        request_dict = {"raw": request_str}
                    
                    # Call the callback function to process the request
                    if self.request_callback:
                        try:
                            response_dict = self.request_callback(request_dict)
                        except Exception as e:
                            # If callback fails, send error response
                            response_dict = {
                                "status": "error",
                                "message": f"Request processing failed: {str(e)}"
                            }
                    else:
                        # No callback configured
                        response_dict = {
                            "status": "error",
                            "message": "No request handler configured"
                        }
                    
                    # Send JSON response
                    response_str = json.dumps(response_dict)
                    self.rep_socket.send_string(response_str)
                    
            except zmq.ZMQError as e:
                if self.running:
                    print(f"ZMQ error in request listener: {e}")
                break
            except Exception as e:
                if self.running:
                    print(f"Error in request listener: {e}")

    
    def receive_message(self, timeout=1000):
        """
        Receive a message from the subscribed channel.
        
        Args:
            timeout: Timeout in milliseconds
            
        Returns:
            Tuple of (topic, message_dict) or (None, None) if no message
        """
        if not self.subscriber:
            return None, None
            
        if self.subscriber.poll(timeout):
            msg = self.subscriber.recv_string()
            parts = msg.split(' ', 1)
            if len(parts) == 2:
                topic, message = parts
                try:
                    message_dict = json.loads(message)
                    return topic, message_dict
                except json.JSONDecodeError:
                    return topic, {"raw": message}
        return None, None