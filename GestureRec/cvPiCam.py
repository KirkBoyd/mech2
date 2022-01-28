from picamera.array import PiRGBArray
from picamera import PiCamera
import cv2
import numpy as np
import math

# picamera setup
camera = PiCamera()
camera.resolution = (320,240)
camera.framerate = 30
#camera.brightness = 65

raw_capture = PiRGBArray(camera, size=(320,240))

for frame in camera.capture_continuous(raw_capture,format='bgr',use_video_port=True):
	img = frame.array
	raw_capture.truncate(0)
	cv2.imshow("Raw PiCam", img)

	# close the windows with 'q'
	if cv2.waitKey(1) & 0xFF==ord('q'):
		break
