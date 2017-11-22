import socket
import os
import requests
import time
import datetime

s = socket.socket();

port = 27015
clearScreen = 0;
URL = "http://pigeonholelogic.com/request.php"

s.bind(('', port))
s.listen(5)
c, addr = s.accept()
print("Got Connection From", addr)
while True:
    msg = c.recv(1024)
    decoded = "";
    if(len(msg) > 0):
        decoded = msg.decode('ascii')
    if decoded == "close":
        c.close()
        break;
    elif decoded == "TRUE":
        #if last != decoded:
        os.system('cls')
        print("Detection!...")
        now = datetime.datetime.now()
        PARAMS = {'token':"CMUNetworksClass",'year': now.year, 'month':now.month, 'day':now.day, 'hour':now.hour, 'minute':now.minute, 'second':now.second}
        r = requests.get(url = URL, params = PARAMS)
        print(r.text)
        clearScreen = 1;
        time.sleep(5)
    else:
        if(clearScreen == 1):
            os.system('cls')
            print("Noting Detected")
            last = decoded
            clearScreen = 0;
