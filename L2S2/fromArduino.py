import serial
import json
arduino = serial.Serial()
arduino.baudrate = 19200
arduino.port = 'COM4'
while True:
    jsonString = json.dumps(arduino.readline().decode("utf-8"))
    inputData.append(jsonString)
