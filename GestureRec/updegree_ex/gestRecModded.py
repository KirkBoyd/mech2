from picamera.array import PiRGBArray
from picamera import PiCamera
import cv2
import numpy as np
import math
from gpiozero import LED

ledR = LED(16)
ledY = LED(21)
ledG = LED(26)

ledR.off()
ledY.off()
ledG.off()

start_rectx = 400
start_recty = 300
start_rect = (start_rectx,start_recty)
end_rectx = 200
end_recty = 100
end_rect = (end_rectx,end_recty)

# picamera setup
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 30
#camera.brightness = 65

raw_capture = PiRGBArray(camera, size=(640,480))
#cap = cv2.VideoCapture(0)

for frame in camera.capture_continuous(raw_capture, format='bgr', use_video_port=True):
# while(cap.isOpened()):
    # read image
    # ret, img = cap.read()
    img = frame.array
    # cv2.imshow("Original Image",img)
    raw_capture.truncate(0)

    # if not ret:
      # print("cap.read no worky")
      # continue
    # get hand data from the rectangle sub window on the screen
    cv2.rectangle(img, start_rect, end_rect, (0,255,0),0)
    crop_img = img[end_recty:start_recty, end_rectx:start_rectx]

    # convert to grayscale
    grey = cv2.cvtColor(crop_img, cv2.COLOR_BGR2GRAY)
    # cv2.imshow("gray",grey)

    # applying gaussian blur
    value = (25, 25)
    blurred = cv2.GaussianBlur(grey, value, 0)
    # cv2.imshow("blur",blurred)

    # thresholdin: Otsu's Binarization method
    _, thresh1 = cv2.threshold(blurred, 100, 255,
                               cv2.THRESH_BINARY+cv2.THRESH_OTSU)

    # show thresholded image
    cv2.imshow('Thresholded', thresh1)

    # check OpenCV version to avoid unpacking error
    (version, _, _) = cv2.__version__.split('.')

    if version == '3':
        image, contours, hierarchy = cv2.findContours(thresh1.copy(), \
               cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)
    elif version == '4':
        contours, hierarchy = cv2.findContours(thresh1.copy(),cv2.RETR_TREE, \
               cv2.CHAIN_APPROX_NONE)

    # find contour with max area
    cnt = max(contours, key = lambda x: cv2.contourArea(x))

    # create bounding rectangle around the contour (can skip below two lines)
    x, y, w, h = cv2.boundingRect(cnt)
    cv2.rectangle(crop_img, (x, y), (x+w, y+h), (0, 0, 255), 0)

    # finding convex hull
    hull = cv2.convexHull(cnt)

    # drawing contours
    drawing = np.zeros(crop_img.shape,np.uint8)
    cv2.drawContours(drawing, [cnt], 0, (0, 255, 0), 0)
    cv2.drawContours(drawing, [hull], 0,(0, 0, 255), 0)

    # finding convex hull
    hull = cv2.convexHull(cnt, returnPoints=False)

    # finding convexity defects
    defects = cv2.convexityDefects(cnt, hull)
    count_defects = 0
    cv2.drawContours(thresh1, contours, -1, (0, 255, 0), 3)

    # applying Cosine Rule to find angle for all defects (between fingers)
    # with angle > 90 degrees and ignore defects
    for i in range(defects.shape[0]):
        s,e,f,d = defects[i,0]

        start = tuple(cnt[s][0])
        end = tuple(cnt[e][0])
        far = tuple(cnt[f][0])

        # find length of all sides of triangle
        a = math.sqrt((end[0] - start[0])**2 + (end[1] - start[1])**2)
        b = math.sqrt((far[0] - start[0])**2 + (far[1] - start[1])**2)
        c = math.sqrt((end[0] - far[0])**2 + (end[1] - far[1])**2)

        # apply cosine rule here
        angle = math.acos((b**2 + c**2 - a**2)/(2*b*c)) * 57

        # ignore angles > 90 and highlight rest with red dots
        if angle <= 90:
            count_defects += 1
            cv2.circle(crop_img, far, 1, [0,0,255], -1)
        #dist = cv2.pointPolygonTest(cnt,far,True)

        # draw a line from start to end i.e. the convex points (finger tips)
        # (can skip this part)
        cv2.line(crop_img,start, end, [0,255,0], 2)
        #cv2.circle(crop_img,far,5,[0,0,255],-1)

    # define actions required
    if count_defects == 1:
        ledR.on()
        ledY.off()
        ledG.off()
        cv2.putText(img,"2 fingers", (5, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (255,255,255))
    elif count_defects == 2:
        ledY.on()
        ledR.off()
        ledG.off()
        cv2.putText(img, "3 fingers",(5,50),cv2.FONT_HERSHEY_SIMPLEX,1,(255,255,255))
    elif count_defects == 3:
        ledG.on()
        ledR.off()
        ledY.off()
        cv2.putText(img,"4 fingers",(5,50),cv2.FONT_HERSHEY_SIMPLEX,1,(255,255,255))
    elif count_defects == 4:
        ledG.off()
        ledR.off()
        ledY.off()
        cv2.putText(img,"5 fingers",(5,50),cv2.FONT_HERSHEY_SIMPLEX,1,(255,255,255))
    elif count_defects == 5:
        continue
        ledG.off()
        ledR.off()
        ledY.off()
        #cv2.putText(img,"Entire hand",(5,50),cv2.FONT_HERSHEY_SIMPLEX,1,(255,255,255))
    else:
        cv2.putText(img,"No hand",(5,50),cv2.FONT_HERSHEY_SIMPLEX,1,(255,255,255))
        ledG.off()
        ledR.off()
        ledY.off()

    # show appropriate images in windows
    cv2.imshow('Gesture', img)
    all_img = np.hstack((drawing, crop_img))
    cv2.imshow('Contours', all_img)

    #k = cv2.waitKey(10)
    #if k == 27:
    if cv2.waitKey(1) & 0xFF==ord('q'):
        break
