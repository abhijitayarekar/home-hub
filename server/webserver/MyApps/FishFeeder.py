from MyConns.xbdev import XbDev
from flask import request
from datetime import datetime
from flask_restful import Resource, reqparse, abort
import logging

get_req_parser = reqparse.RequestParser()
get_req_parser.add_argument('last_feed', required=False)
get_req_parser.add_argument('feeder_opening', required=False)
get_req_parser.add_argument('feeder_open_time', required=False)
get_req_parser.add_argument('schedule', required=False)

post_req_parser = reqparse.RequestParser()
post_req_parser.add_argument('feed_now', required=False)

data_state = {
  'now' : datetime.now(), 
  'last_feed' : 'unknown',
  'feeder_opening' : 60,
  'feeder_open_time_in_millis' : 100,
  'schedule' : {
    'duration' : 'forever',
    'days' : [ 'tuesday', 'thursday', 'saturday' ],
    'times' : [ '07:00pm' ]
  }
}

def xb_dev_cb(name, data):
  logging.info("(" + name + ") : " + str(data))

xb_dev = XbDev("fish-feeder", "/dev/ttyUSB0", xb_dev_cb)

class FishFeeder(Resource):

  def start(self):
    if (xb_dev.isRunning() == True):
        xb_dev.stop()

    logging.debug("Starting xbdev")
    xb_dev.start()

  def stop(self):
    logging.debug("Stopping xbdev")
    if (xb_dev.isRunning() == True):
        xb_dev.stop()

  def get(self):
    args = get_req_parser.parse_args()
    if not args['last_feed'] == None:
      return { 'last_feed' : data_state['last_feed'] }
    if not args['feeder_opening'] == None:
      return { 'feeder_opening' : data_state['feeder_opening'] }
    if not args['feeder_open_time'] == None:
      return { 'feeder_open_time' : data_state['feeder_open_time'] }
    if not args['schedule'] == None:
      return { 'schedule' : data_state['schedule'] }

    data_state['now'] = str(datetime.now())
    return data_state

  def post(self):
    args = post_req_parser.parse_args()
    if not args['feed_now'] == None:
      data_state['last_feed'] = str(datetime.now())
      return { 'last_feed' : data_state['last_feed'] }

    return abort(404, message="Available post args : feed_now")

  # def handle_http_request(self, request):
  #   cmd = request.args.get('param')

  #   if cmd == 'api':
  #     return open(os.getcwd() + "/MyApps/FishFeeder/schema.json", "r").read()


