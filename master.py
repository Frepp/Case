import serial
import datetime

# Connect to the serial port and open the log
ser = serial.Serial('/dev/ttyACM1', 9600)
f = open("log.txt","w+")

while True:
    message = ser.readline().decode('UTF-8').replace(' \n', '')
    message = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S") + "\t" + message
    print(message)
    f.write(message + "\n")
