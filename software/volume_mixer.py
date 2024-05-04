import serial

ser = serial.Serial(port='/dev/ttyUSB0', baudrate=9600)

while True:
    ser_value = ser.read()
    if ser_value:
        print(ser_value)
