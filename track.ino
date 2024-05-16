#include<Servo.h>
Servo x, y;
int width = 640, height = 480; // total resolution of the video
int xpos = 90, ypos = 90; // initial positions of both Servos
int shoot = 15; //initial position of shooting servo
void setup() {
Serial.begin(9600);
x.attach(9);
y.attach(10);
s.attach(11);
x.write(xpos);
y.write(ypos);
s.write(shoot);
}
const int angle = 1; // degree of increment or decrement
void loop() {
if (Serial.available() > 0)
{
int x_mid, y_mid;
if (Serial.read() == 'X')
{
x_mid = Serial.parseInt(); // read center x-coordinate
if (Serial.read() == 'Y')
y_mid = Serial.parseInt(); // read center y-coordinate
}
int errorx = x_mid - width/2;
int errory = y_mid - height/2;
int error = sqrt(errorx*errorx + errory*errory);
/* adjust the servo within the squared region if the coordinates
is outside it
*/
if (x_mid > width/2 + 20)
xpos += angle;
if (x_mid < width/2 - 20)
xpos -= angle;
if (y_mid < height/2 + 20)
ypos += angle;
if (y_mid > height/2 - 20)
ypos -= angle;
if (error <=20)
s.write(70);
delay(100);
shoot=15
// if the servo degree is outside its range
if (xpos >= 180)
xpos = 180;
else if (xpos <= 0)
xpos = 0;
if (ypos >= 180)
ypos = 180;
else if (ypos <= 0)
ypos = 0;
x.write(xpos);
y.write(ypos);
s.write(shoot);
}
}