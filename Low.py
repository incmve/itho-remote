#!/usr/bin/env python
          
      
           import time
           import serial
          
      
           ser = serial.Serial(
              
               port='/dev/ttyUSB1',
               baudrate = 9600,
               parity=serial.PARITY_NONE,
               stopbits=serial.STOPBITS_ONE,
               bytesize=serial.EIGHTBITS,
               timeout=1
           )
               ser.write("Low"),
			   ser.close()