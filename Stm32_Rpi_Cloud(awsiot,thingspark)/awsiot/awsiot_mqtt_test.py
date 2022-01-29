from  AWSIoTPythonSDK.MQTTLib import AWSIoTMQTTClient
import json, time
import serial

ser = serial.Serial('/dev/ttyUSB0', baudrate=9600)
ser.reset_input_buffer()

client_id = 'stm_rpi_test'

mqtt_client = AWSIoTMQTTClient(client_id)
mqtt_client.configureEndpoint("a3ren02rfin8mw-ats.iot.us-east-1.amazonaws.com",8883)
mqtt_client.configureCredentials("/home/pi/certs/root-CA.crt", "/home/pi/certs/stm_rpi_test.private.key", "/home/pi/certs/stm_rpi_test.cert.pem")
mqtt_client.configureOfflinePublishQueueing(-1)
# mqtt_client.configureDrainingFrequency(2)
mqtt_client.configureConnectDisconnectTimeout(10)
mqtt_client.configureMQTTOperationTimeout(5)

mqtt_client.connect()
mqtt_client.publish("rpi/status", '{"status":"connect"}',0)

while True:
    if ser.in_waiting:
        r = ser.readline()
        payloads = {
                "value" : r.decode('utf-8')
        }
        mqtt_client.publish("rpi/serial", json.dumps(payloads),0)
    else :
        mqtt_client.publish("rpi/status", '{"status":"disconnect"}', 0)
        ser.close()
        break
