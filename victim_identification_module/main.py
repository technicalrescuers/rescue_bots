import cv2
import sys
from mail import sendEmail
from flask import Flask, render_template, Response
from camera import VideoCamera
from flask_basicauth import BasicAuth
import time
import threading
import serial

email_update_interval = 10 # sends an email only once in this time interval
video_camera = VideoCamera(flip=False) # creates a camera object, flip vertically
#object_classifier = cv2.CascadeClassifier("models/facial_recognition_model.xml") # an opencv classifier
object_classifier = cv2.CascadeClassifier("models/fullbody_recognition_model.xml") # an opencv classifier
#object_classifier = cv2.CascadeClassifier("models/upperbody_recognition_model.xml") # an opencv classifier

# App Globals (do not edit)
app = Flask(__name__)
app.config['BASIC_AUTH_USERNAME'] = 'pi'
app.config['BASIC_AUTH_PASSWORD'] = 'raspberry'
app.config['BASIC_AUTH_FORCE'] = True

basic_auth = BasicAuth(app)
last_epoch = 0
camera_position_error = 10

ser = serial.Serial('/dev/ttyUSB0', 115200)

@app.route('/')
@basic_auth.required
def index():
    return render_template('index.html')

def gen(camera):
    while True:
        try:
            frame, found_obj, coordinates = camera.get_object(object_classifier)

            adjust_camera((160, 128), coordinates)

            yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n\r\n')
        except:
            print "Error rendering video: ", sys.exc_info()[0] 

def gps_data():
    while True:
        try:
            ser.write('GPS')
            time.sleep(1)
            line = ser.read()
            print(line)
            yield (b'Content-Type: application/text\r\n\r\n' + line + b'\r\n\r\n')
        except:
            print "Error reading GPS data: ", sys.exc_info()[0]

def adjust_camera(frame_size, box_coordinates):
    box_center_y = 0
    for (x, y, w, h) in box_coordinates:
        box_center_y = y + int(w / 2)
        camera_center_y = int(frame_size[1] / 2)
        if (box_center_y < (camera_center_y - camera_position_error)):
            increment_camera_angle()
        elif (box_center_y > (camera_center_y + camera_position_error)):
            decrement_camera_angle()
    

def increment_camera_angle():
    ser.flush()
    ser.write('INCR')

def decrement_camera_angle():
    ser.flush()
    ser.write('DECR')

@app.route('/video_feed')
def video_feed():
    return Response(gen(video_camera),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/gps')
def gps():
    return Response(gps_data(),
                    mimetype='application/text')

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=False)
