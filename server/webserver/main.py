from flask import Flask, url_for, request
from flask_restful import Api
import sys
import time
import logging
import os
import uuid
import netifaces as ni
from MyLibs.ssdp import SSDPServer
from MyLibs.upnp_http_server import UPNPHTTPServer
#from MyApps import *
from threading import Event

# Add path to import zmq_node
_zmq_node_path = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'python', 'classes'))
if _zmq_node_path not in sys.path:
    sys.path.insert(0, _zmq_node_path)

from zmq_node import ZMQNode  # type: ignore

exit = Event()

app = Flask(__name__)
api = Api(app)

my_apps = {}

@app.route('/')
def index():
	ret_str = '{ Apps : { '
	for my_app in my_apps:
		ret_str += my_app + ', '

	ret_str = ret_str[:len(ret_str) - 2] + ' } }' 
	return ret_str

# api.add_resource(FishFeeder, '/fishfeeder/')

@app.route('/<myapp_name>/')
def myapp_handler(myapp_name):
	if myapp_name.lower() in my_apps:
		return my_apps[myapp_name.lower()].handle_http_request(request)

	return '{not found}'

def start_device_discovery():

	if ('default' not in ni.gateways()):
		return

	gw = ni.gateways()['default']
	if (ni.AF_INET not in gw):
		return

	ifaddrs = ni.ifaddresses(gw[ni.AF_INET][1])
	ifaddr = ifaddrs[ni.AF_INET][0]['addr']
	device_uuid = uuid.uuid4()
	http_server = UPNPHTTPServer(8088,
															 friendly_name="Homehub 1.0",
															 manufacturer="Abhijit Ayarekar",
															 manufacturer_url='http://www.dontknowyet.com/',
															 model_description='Homehub Appliance 1.0',
															 model_name="Homehub",
															 model_number="1.0",
															 model_url="http://www.dontknowyet.com/en/prducts/homehub-10/",
															 serial_number="HHN95035",
															 uuid=device_uuid,
															 presentation_url="http://{}:5000/".format(ifaddr))
	http_server.start()

	ssdp_server = SSDPServer()
	ssdp_server.register('local',
								'uuid:{}::urn:aya-home-org:service:homehub:1'.format(device_uuid),
								'urn:aya-home-org:service:homehub:1',
								'http://{}:9090'.format(ifaddr))
	ssdp_server.start()
	return ssdp_server, http_server

def stop_device_discovery(ssdp_server, http_server):
	ssdp_server.shutdown()
	http_server.stop()

def start_my_apps():
	"""Dynamically load and start apps from MyApps directory"""
	import importlib
	myapps_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'MyApps')
	
	if not os.path.exists(myapps_dir):
		logging.warning(f"MyApps directory not found at: {myapps_dir}")
		return
	
	for f in os.listdir(myapps_dir):
		if f.endswith('.py') and not f.startswith('_'):
			module_name = f[:-3]
			try:
				# Dynamically import the module
				module = importlib.import_module(f'MyApps.{module_name}')
				# Get the class from the module (assumes class name matches module name)
				app_class = getattr(module, module_name)
				# Instantiate and start the app
				my_app = app_class()
				my_apps[module_name.lower()] = my_app
				my_app.start()
				logging.info(f"Started app: {module_name}")
			except Exception as e:
				logging.error(f"Failed to load app {module_name}: {e}")

def stop_my_apps():
	for my_app in my_apps.values():
		my_app.stop()

def zmq_request_handler(request):
	"""Handle incoming ZMQ requests"""
	print(f"Received request: {request}")
	
	# Process the request and return a response
	if request.get("type") == "ping":
		return {"status": "success", "message": "pong"}
	elif request.get("type") == "status":
		return {"status": "success", "apps": list(my_apps.keys())}
	else:
		return {"status": "error", "message": "Unknown request type"}

def start_zmq():
	# Create ZMQNode with pub/sub on port 5555 and req/rep on port 5571
	try:
		zmq_node = ZMQNode(
			name="webserver",
			pub_sub_port=5555,
			req_rep_port=5572,
			request_callback=zmq_request_handler
		)
		zmq_node.start()
		return zmq_node
	except Exception as e:
		logging.error(f"Failed to start ZMQ node: {e}")
		logging.error("Hint: Port may be in use. Run: netstat -ano | findstr :5571")
		raise

def stop_zmq(zmq_node):
	zmq_node.stop()

if __name__ == "__main__":
	logging.basicConfig(level=logging.INFO)

	zmq_node = start_zmq()
#	start_my_apps()
	ssdp_server, http_server = start_device_discovery()
	app.run(debug=True, port=9090, host='0.0.0.0', use_reloader=False)
	exit.set()
	stop_zmq(zmq_node)

	stop_device_discovery(ssdp_server, http_server)
#	stop_my_apps()

