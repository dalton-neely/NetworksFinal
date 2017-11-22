Computer Networks Final

Languages Used:
Python3.6.3
PHP7.1
HTML5
JavaScript
XML

Description:
A detection system that uses a Raspberry Pi 3 hooked up with a USB camera to detect people coming to your door. On the Raspberry Pi 3 OpenCV 3 is used to detect faces using Haar Cascades. From there, that platform acts as a client, and sends detection alerts to a server on the same local network. From there, that server get the request and then sends another request to update a server on the world wide web. Additionally, when the external server recieves the request it sends a text message to the user that a detection has been made.

