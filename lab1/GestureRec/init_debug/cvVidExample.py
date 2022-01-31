import cv2

vid_capture = cv2.VideoCapture('Cars.mp4')

if (vid_capture.isOpened() == False):
	print("Error opening vid file")
else:
	fps = int(vid_capture.get(5))
	print("Frame Rate: ",fps," frames per second")
	
	frame_count = vid_capture.get(7)
	print("Frame Count: ",frame_count)

while(vid_capture.isOpened()):
	
	ret, frame = vid_capture.read()
	if ret == True:
		cv2.imshow('Frame',frame)
		
		key = cv2.waitKey(20)

		if key == ord('q'):
			break
	else:
		break

vid_capture.release()
cv2.destroyAllWindows()
