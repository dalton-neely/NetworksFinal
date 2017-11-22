import numpy as np
import cv2
import socket
import sys


port = 27015
try:
	ip = sys.argv[1]
except:
	print("Must give program IP address in arguments")
	sys.exit()

try:
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	print("socket successfully created")
except socket.error:
	print("socket creation failed")
	
s.settimeout(5)

try:
	s.connect((ip, port))
	print("connected to server successfully")
except socket.error:
	print("Error connecting to server")

face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

cap = cv2.VideoCapture(0)

while 1:
	ret, img = cap.read()
	gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
	faces = face_cascade.detectMultiScale(gray,1.3, 5)
	
	t = 0;
	
	for (x,y,w,h) in faces:
		t =t +1
		cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
		roi_gray = gray[y:y+h, x:x+w]
		roi_color = img[y:y+h, x:x+w]
	if t == 1:
		try:
			s.sendall(b'TRUE')
			print('Detected')
		except:
			print('Error sending message')
	cv2.imshow('img', img)
	k = cv2.waitKey(30)
	if k == 27:
		#Escape Key was pressed
		try:
			s.sendall(b'close')
			print('Closing program and server program')
		except:
			print('Error closing program')
		break
cap.release()
