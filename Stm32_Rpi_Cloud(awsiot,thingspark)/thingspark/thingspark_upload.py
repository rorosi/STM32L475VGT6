import requests
import serial

ser = serial.Serial('/dev/ttyUSB0', baudrate=9600)
ser.reset_input_buffer()

url = "https://api.thingspark.co.kr/channels/entrys"

r = ser.readline()
params = {
      "apiKey" : "jzf4yzysHC95K2Y0",
      "field1" : r,
      "field2" : 10
     }       
result = requests.get(url, params=params)
print(result.text)
