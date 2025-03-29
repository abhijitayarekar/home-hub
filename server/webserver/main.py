from flask import Flask, url_for, request
from flask_restful import Api
import time
import logging
import os
import uuid
import netifaces as ni
from MyLibs.ssdp import SSDPServer
from MyLibs.upnp_http_server import UPNPHTTPServer
#from MyApps import *
import zmq
import threading
import time
from threading import Event

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
  for f in os.listdir("./MyApps"):
    if f.endswith('.py') and not f.startswith('_'):
      f = f[:-3]
      my_app = globals()[f]()
      my_apps[f.lower()] = my_app
      my_app.start()

def stop_my_apps():
  for my_app in my_apps.values():
      my_app.stop()

def zmq_th_func(zmq_socket):
	zmq_poller = zmq.Poller()
	zmq_poller.register(zmq_socket, zmq.POLLIN)

	while not exit.is_set():
		print("Sending hello")
		try:
			zmq_socket.send(b"Hello")
		except:
			print("Error : sending")
			exit.wait(5)
			continue

		try:
				socks = dict(zmq_poller.poll())
		except:
			print("Error : polling")
			continue

		if zmq_socket in socks:
			try:
				message = zmq_socket.recv()
			except:
				print("Error : receiving")
				continue
			print("Received reply %s" % (message))

	print("zmq th func returning")

def start_zmq():
	zmq_ctx = zmq.Context()
	zmq_socket = zmq_ctx.socket(zmq.REQ)
	zmq_socket.connect("tcp://localhost:5571")

	zmq_th = threading.Thread(target=zmq_th_func, args=(zmq_socket,))
	zmq_th.start()

	return zmq_socket, zmq_th

def stop_zmq(zmq_socket, zmq_th):
	zmq_socket.disconnect("tcp://localhost:5571")
	zmq_socket.close()
	zmq_th.join()

if __name__ == "__main__":
	logging.basicConfig(level=logging.INFO)

	zmq_socket, zmq_th = start_zmq()
#	start_my_apps()
	ssdp_server, http_server = start_device_discovery()
	app.run(debug=True, port=9090, host='0.0.0.0', use_reloader=True)
	exit.set()
	stop_zmq(zmq_socket, zmq_th)

	stop_device_discovery(ssdp_server, http_server)
#	stop_my_apps()

