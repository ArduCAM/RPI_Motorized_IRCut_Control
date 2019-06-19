#!/usr/bin/env python

import os, fcntl, struct

# RaspberryPi zero w  camera LED controller by  Arducam

class CameraLED():
    def on(self):
        cmd="echo 1 > /sys/class/gpio/gpio40/value"
        os.system(cmd)
        return "on" #self.__firmware_request__(self.SET_TAG, 1)

    def off(self):
        cmd="echo 0 > /sys/class/gpio/gpio40/value"
        os.system(cmd)
        return "off" #self.__firmware_request__(self.SET_TAG, 0)

   # def state(self):
        #return self.__firmware_request__(self.GET_TAG)

if __name__ == "__main__":
    import sys

    def usage():
        print("Usage: " + sys.argv[0] + " (on|off)")
    cmd="echo 40 > /sys/class/gpio/export"
    os.system(cmd)
    cmd="echo out > /sys/class/gpio/gpio40/direction"
    os.system(cmd)
    if len(sys.argv) == 2:
        led = CameraLED()
        if sys.argv[1] == "on":
            print("State: " + str(led.on()))
        elif sys.argv[1] == "off":
            print("State: " + str(led.off()))
        else:
            usage()
    else:
        usage() 

