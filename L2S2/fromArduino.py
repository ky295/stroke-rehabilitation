import serial
import json
arduino = serial.Serial()
arduino.baudrate = 19200
arduino.port = 'COM4'
noOfVariables = 5
while (len(inputData)<noOfVariables):
    inputData.append(arduino.readline().decode("utf-8"))

jsonString = json.dumps(inputData)
