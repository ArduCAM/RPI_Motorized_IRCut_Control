#!/usr/bin/env python

import os, fcntl, struct

# RaspberryPi 3 camera LED controller by BigNerd95

class CameraLED():

    IOCTL_MAILBOX = 0xC0046400
    REQUEST_SUCCESS = 0x80000000
    SET_TAG = 0x38041
    GET_TAG = 0x30041

    def __init__(self, led=134):
        self.__vcio = os.open("/dev/vcio", os.O_TRUNC)
        self.__led = led
    
    def __firmware_request__(self, tag, state = 0):
        buffer = struct.pack("=8I", # buffer format, int32 buffer[8] (native endian)
                32,                 # total message length in bytes
                0, 
                tag,                # tag
                8,                  # tag data size
                0,
                self.__led,         # tag data: led number
                state,              # tag data: state
                0
            )

        # send request
        result = fcntl.ioctl(self.__vcio, self.IOCTL_MAILBOX, buffer)

        _, success, _, _, _, _, newState, _ = struct.unpack("=8I", result)

        if success == self.REQUEST_SUCCESS:
            return newState
        else:
            raise Exception("RPi firmware error!")

    def on(self):
        return self.__firmware_request__(self.SET_TAG, 1)

    def off(self):
        return self.__firmware_request__(self.SET_TAG, 0)

    def toggle(self):
        if self.state() == 1:
            return self.off()
        else:
            return self.on()

    def state(self):
        return self.__firmware_request__(self.GET_TAG)

if __name__ == "__main__":
    import sys

    def usage():
        print("Usage: " + sys.argv[0] + " (state|toggle|on|off)")
    
    if len(sys.argv) == 2:
        led = CameraLED()

        if sys.argv[1] == "state":
            print("State: " + str(led.state()))
        elif sys.argv[1] == "toggle":
            print("State: " + str(led.toggle()))
        elif sys.argv[1] == "on":
            print("State: " + str(led.on()))
        elif sys.argv[1] == "off":
            print("State: " + str(led.off()))
        else:
            usage()
    else:
        usage() 
