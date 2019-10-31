# CameraLED
Pure python3 library to control Camera LED for RaspberryPi 3

# Background
This library is used for ArduCAM with motorized IR Cut Filter.  
The IR Cur filter is connected to the camera LED, so by controlling the LED you can control the IR filter.  
This python library is used to control the camera LED (and IR filter) on Raspberry 3.  .  

# Prerequisites
You have to disable the automatic management of camera led in `/boot/config.txt`.  
```bash
$ echo "disable_camera_led=1" | sudo tee -a /boot/config.txt 
$ sudo reboot
```
# Installation
```bash
$ wget https://raw.githubusercontent.com/arducam/RPI_Motorized_IRCut_Control/master/CameraLED.py 
$ chmod 755 CameraLED.py
```

# Usage
You need to be root (or at least be able to use sudo).
### Standalone
You can use the library as a standalone command:
```bash
$ sudo ./CameraLED.py 
Usage: ./CameraLED.py (state|toggle|on|off)

$ sudo ./CameraLED.py state
State: 0

$ sudo ./CameraLED.py toggle
State: 1

$ sudo ./CameraLED.py toggle
State: 0

$ sudo ./CameraLED.py on    
State: 1

$ sudo ./CameraLED.py off
State: 0
```
### For Pi4 with UC350 Rev.B  
```bash
$ sudo ./IMX219_UC-350_Rev.B_pi4_gpio_ircut_ctl on    
State: 1
```
```bash
$ sudo ./IMX219_UC-350_Rev.B_pi4_gpio_ircut_ctl off
State: 0
```
![IMAGE ALT TEXT](doc/uc350_rev.B.jpg)  
### Python library
You can use my library in your Camera projects
```python
from CameraLED import CameraLED
led = CameraLED() # CameraLED(134)
led.on()
led.off()
led.toggle()
led.state()
```

# Photos
LED OFF = NO IR filter = Night vision  
![image](doc/led_off.jpg)  
LED ON = IR filter = Daily vision  
![image](doc/led_on.jpg)  



# Thanks
Thanks to Lorenzo Santina for sharing
https://github.com/BigNerd95/CameraLED


