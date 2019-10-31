#!/usr/bin/env python

import os, fcntl, struct

# IMX219(UC-350_Rev.B) RaspberryPi 4B  GPIO controller by  Arducam

class CameraLED():
    def on(self):
        cmd="gpio -g write 4 1"
        os.system(cmd)
        return "on" #self.__firmware_request__(self.SET_TAG, 1)

    def off(self):
        cmd="gpio -g write 4 0"
        os.system(cmd)
        return "off" #self.__firmware_request__(self.SET_TAG, 0)

   # def state(self):
        #return self.__firmware_request__(self.GET_TAG)

if __name__ == "__main__":
    import sys

    def usage():
        print("Usage: " + sys.argv[0] + " (on|off)")
    cmd="gpio -g mode 4 out"
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

