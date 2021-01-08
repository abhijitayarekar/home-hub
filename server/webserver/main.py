from flask import Flask, url_for, request
from flask_restful import Api
import time
import logging
from MyApps import *
import os
import netifaces as ni
from MyLibs.ssdp import SSDPServer
from MyLibs.upnp_http_server import UPNPHTTPServer
import uuid

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

api.add_resource(FishFeeder, '/fishfeeder/')

# @app.route('/<myapp_name>/')
# def myapp_handler(myapp_name):
#   if myapp_name.lower() in my_apps:
#     return my_apps[myapp_name.lower()].handle_http_request(request)

#   return '{not found}'

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

if __name__ == "__main__":
  logging.basicConfig(level=logging.INFO)

  start_my_apps()
  ssdp_server, http_server = start_device_discovery()

  app.run(debug=True, port=9090, host='0.0.0.0', use_reloader=False)

  stop_device_discovery(ssdp_server, http_server)
  stop_my_apps()
