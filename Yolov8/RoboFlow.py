from roboflow import Roboflow
import cv2
import numpy as np
import math
import time
from ultralytics import YOLO


# ROBOFLOW_API_KEY = "oIcDJovVAvTV8Yg3AT20"
# ROBOFLOW_MODEL = "cmsc477_project3/1" # eg xx-xxxx--#
# ROBOFLOW_SIZE = 360

# rf = Roboflow(api_key="oIcDJovVAvTV8Yg3AT20")
# project = rf.workspace().project("cmsc477_project3")
# model = project.version(3).model
model = YOLO('./Yolov8/best.pt')  # load an official detection model

def call_roboflow_api(img):
    resp = model.predict(img)
    return resp

# Use vid instead of ep_camera to use your laptop's webcam
vid = cv2.VideoCapture(0)
while True:
    # Get the current image from the webcam
    ret, img = vid.read()
    #image = ep_camera.read_cv2_image(strategy="newest", timeout=5.0)
    results = call_roboflow_api(img)
    new_frame = results[0].plot()
    cv2.imshow('Webcam', new_frame)
    if cv2.waitKey(1) == ord('q'):
        break
cv2.destroyAllWindows()