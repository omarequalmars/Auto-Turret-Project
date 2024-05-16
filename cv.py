import cv2
import serial,time
face_cascade = cv2.CascadeClassifier('haar_face.xml')
cap=cv2.VideoCapture(1, cv2.CAP_DSHOW)
ArduinoSerial=serial.Serial('com12',9600,timeout=0.1)
time.sleep(1)
while cap.isOpened():
    ret, frame= cap.read()
    frame=cv2.flip(frame,1) #mirror the image
    gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    faces= face_cascade.detectMultiScale(gray,1.1,6) #detect the face
    for x,y,w,h in faces:
    #creating string for coordiantes
        string='X{0:d}Y{1:d}'.format((x+w//2),(y+h//2))
        print(string)
        ArduinoSerial.write(string.encode('utf-8')) #send string to arduino
        time.sleep(0.05)
        #plot the center of the face
        cv2.circle(frame,(x+w//2,y+h//2),2,(0,255,0),2)
        #plot the roi
        cv2.rectangle(frame,(x,y),(x+w,y+h),(0,0,255),3)
    cv2.imshow('img',frame)
    #for testing purpose
    read= str(ArduinoSerial.readline(ArduinoSerial.inWaiting()))
    time.sleep(0.05)
    print('data from arduino:'+read)
# press q to Quit
    if cv2.waitKey(10)&0xFF== ord('q'):
        break
cap.release()
cv2.destroyAllWindows()