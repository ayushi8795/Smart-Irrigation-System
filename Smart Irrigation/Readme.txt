//////////////////////////////////Smart Irrigation System 

// connections 
soil sensor pins 
GND- Arduino GND
SIG-Arduino A0
VCC-Arduino pin7 

Water Pump 
GND-Arduino GND
VCC- Relay second pin 

Relay connection ( first side )

GND-Arduino GND
VCC-Arduino vcc5 
SIG-Arduino pin 13
Relay connection ( first side )
First pin - Arduino Vcc3.3 

// How to run 

1-conncet arduino using usb cable 
2-check your port number ( tools-port->)
3- open cmd and write following command 
    1- change the working directory to “C:\Program Files (x86)\Arduino\libraries\Blynk\scripts” using the cd command.
    
    2- In the command prompt (with the working directory set as mentioned above), enter the following and hit enter
         blynk-ser.bat –c COM3
	Make sure to check your COM Port and make necessary changes in the above line
4-Now, open the Blynk App on your Phone and check values 
