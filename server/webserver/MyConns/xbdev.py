import serial
import threading
import time
import logging

def xb_th_func(xb):
    logging.debug("(" + xb.name + "):" + xb.port + " Opening.")
    xb.ser = serial.Serial(xb.port, 9600, timeout=.5)
    xb.ser.flush()
    while xb.keep_running == True:
        if xb.ser.in_waiting:
            data = xb.ser.read(size=1)
            cmd_sz = int(data[0:1])
            if cmd_sz > 0:
                data = xb.ser.read(size=cmd_sz)
                xb.cb(xb.name, data)
        time.sleep(1)
    logging.debug("(" + xb.name + "):" + xb.port + " Closing.")
    xb.ser.close()

class XbDev:
    def __init__(self, name, port, cmd_sz, cb = None):
        self.name = name
        self.port = port
        self.cmd_sz = cmd_sz
        self.cb = cb
        self.keep_running = False
        self.th = threading.Thread(target=xb_th_func, args=(self,))

    def __del__(self):
        if (self.keep_running == True):
            self.stop()
            self.th.join()

    def writeSync(self, data_bytes):
        try:
            bytes_written = self.ser.write(data_bytes)
            self.ser.flush()
            return bytes_written
        except serial.SerialTimeoutException:
            logging.error("(" + xb.name + "):" + xb.port + " Failed to write.")

        return 0

    def start(self):
        if (self.keep_running == False):
            self.keep_running = True
            self.th.start()

    def stop(self):
        self.keep_running = False
        self.th.join()

    def isRunning(self):
        return self.keep_running

