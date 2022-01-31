import cv2
from picamera.array import PiRGBArray
from picamera import PiCamera
import mediapipe
import time

camera = PiCamera()
camera.resolution = (320,240)
camera.framerate = 30
camera.brightness = 65

raw_capture = PiRGBArray(camera, size=(320,240))
#cap = cv2.VideoCapture(0)

mpHands = mp.solutions.hands
hands = mpHands.Hands()


for frame in camera.capture_continuous(raw_capture, format="bgr", use_video_port=True):
	img = frame.array
	cv2.imshow("Original Image", img)
	raw_capture.truncate(0)
	if cv2.waitKey(1) & 0xFF==ord('q'):
		break
#while True:
  #  success, img = cap.read()
  #  imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
	results = hands.process(imgRGB)
    
#    cv2.imshow('grayscale image', img_grayscale)
#    cv2.waitKey(0)
    
#cv2.destroyAllWindows()
