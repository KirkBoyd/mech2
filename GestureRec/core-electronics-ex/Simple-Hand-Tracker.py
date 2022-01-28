#import
import mediapipe as mp
import cv2

#
drawingModule = mp.solutions.drawing_utils
handsModule = mp.solutions.hands

# Use Cv2 funtionality to create a Video stream and add some values
cap = cv2.VideoCapture(1)
fourcc = cv2.VideoWriter_fourcc('m', 'p', '4', 'v')

# Add confidence values
# image
# More hands
with handsModule.Hands(static_image_mode=False, min_detection_confidence=0.7, min_tracking_confidence=0.7, max_num_hands=2) as hands:

# create
	while True:
		ret, frame = cap.read()
		# Uncomment below if camera is flipped
		# flipped = cv2.flip(frame, (640, 480))

		#Det
		frame1 = cv2.resize(frame, (640, 480))

		# Prod
		results = hands.process(cv2.cvtColor(frame1, cv2.COLOR_BGR2RGB))

        	# if cam
		if results.multi_hand_landmarks != None:
			for handLandmarks in results.multi_hand_landmarks:
				drawingModule.draw_landmarks(frame1, handLandmarks, handsModule.HAND_CONNECTIONS)

				#
				#

					#
					#

					#
					#
						#
						#
						#

		#
		cv2.imshow("Frame", frame1);
		key = cv2.waitKey(1) & 0xFF

		#
		if key == ord("q"):
			break


#cap.release()
#cap.destroyAllWindows()
