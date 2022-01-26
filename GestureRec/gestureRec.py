import cv2
#import mediapipe
import time

#cap = cv2.VideoCapture(0)
img_grayscale = cv2.imread('test.jpg',0)

#mpHands = mp.solutions.hands
#hands = mpHands.Hands()

while True:
  #  success, img = cap.read()
  #  imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
  #  results = hands.process(imgRGB)
    
    
    cv2.imshow('grayscale image', img_grayscale)
    cv2.waitKey(0)
    
cv2.destroyAllWindows()