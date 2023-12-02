from roboflow import Roboflow
import cv2
import numpy as np
import time
from ultralytics import YOLO


# ROBOFLOW_API_KEY = "oIcDJovVAvTV8Yg3AT20"
# ROBOFLOW_MODEL = "cmsc477_project3/1" # eg xx-xxxx--#
# ROBOFLOW_SIZE = 360

# rf = Roboflow(api_key="oIcDJovVAvTV8Yg3AT20")
# project = rf.workspace().project("cmsc477_project3")
# model = project.version(3).model
# model = YOLO('./runs/detect/yolov8n_custom9/weights/best.pt')  # load an official detection model
rf = Roboflow(api_key="oIcDJovVAvTV8Yg3AT20")
project = rf.workspace().project("sign-language-letters-detection")
model = project.version(2).model
def call_roboflow_api(img):
    resp = model.predict(img)
    return resp

# Use vid instead of ep_camera to use your laptop's webcam
vid = cv2.VideoCapture(0)

# ep_robot = robot.Robot()
# ep_robot.initialize(conn_type="ap")
# ep_camera = ep_robot.camera
# ep_camera.start_video_stream(display=False, resolution=camera.STREAM_360P)

while True:
    # Get the current image from the webcam
    ret, image = vid.read()
    #image = ep_camera.read_cv2_image(strategy="newest", timeout=5.0)

    start = time.time()
    response = call_roboflow_api(image)

    # preds = response['predictions']
    # for pred in preds:
    #     image = cv2.rectangle(img=image, pt1=(round(pred['x']-pred['width']/2),round(pred['y']-pred['height']/2)),
    #                           pt2=(round(pred['x']+pred['width']/2),round(pred['y']+pred['height']/2)),
    #                           color=(0,255,255), thickness=2)
        
    #     # write and place text
    #     cv2.putText(
    #         image, # PIL.Image object to place text on
    #         pred['class'],#text to place on image
    #         (round(pred['x']-pred['width']/2), round(pred['y']-pred['height']/2)),#location of text in pixels
    #         fontFace = cv2.FONT_HERSHEY_SIMPLEX, #text font
    #         fontScale = 0.6,#font scale
    #         color = (0, 0, 0),#text color in RGB
    #         thickness=2#thickness/"weight" of text
    #         )
    #     res_plotted = image

    # print(response)
    # print(1.0/(time.time() - start))

    # if image is not None:
    #   cv2.imshow('image', image)
    #   cv2.waitKey(1)