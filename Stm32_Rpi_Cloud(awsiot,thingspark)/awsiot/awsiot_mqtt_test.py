from  AWSIoTPythonSDK.MQTTLib import AWSIoTMQTTClient
import json, time
import serial

ser = serial.Serial('/dev/ttyUSB0', baudrate=9600)
ser.reset_input_buffer()

client_id = 'stm_rpi_test'

mqtt_client = AWSIoTMQTTClient(client_id)
mqtt_client.configureEndpoint("endpoint",8883) # 찾은 endpoint 써줌
mqtt_client.configureCredentials("/home/pi/certs/root-CA.crt", "/home/pi/certs/stm_rpi_test.private.key", "/home/pi/certs/stm_rpi_test.cert.pem") # 인증서 경로 확인
mqtt_client.configureOfflinePublishQueueing(-1) # 연결되지 않을 때 얼마나쌓을것인가 무한대일경우 -1
# mqtt_client.configureDrainingFrequency(2) # 1초에 몇개 데이터 전송할 것인지
mqtt_client.configureConnectDisconnectTimeout(10) # 연결 끊어질때 타임아웃
mqtt_client.configureMQTTOperationTimeout(5)

mqtt_client.connect()
mqtt_client.publish("rpi/status", '{"status":"connect"}',0) #토픽, 데이터(페이로드), 방식

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
