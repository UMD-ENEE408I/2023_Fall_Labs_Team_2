from ultralytics import YOLO
from roboflow import Roboflow
import cv2

# rf = Roboflow(api_key="oIcDJovVAvTV8Yg3AT20")
# project = rf.workspace("david-lee-d0rhs").project("american-sign-language-letters")
# dataset = project.version(1).download("yolov5")

# # Load the model.
# model = YOLO('yolov8l.pt')
# # Training.
# results = model.train(
#    data='Yolov8/American-Sign-Language-Letters-1/data.yaml',
#    imgsz=800,
#    epochs=2,
#    batch=2,
#    name='yolov8l_custom')


cam = cv2.VideoCapture(0)
rf = Roboflow(api_key="oIcDJovVAvTV8Yg3AT20")
project = rf.workspace().project("sign-language-letters-detection")
model = project.version(2).model

while True:
    check, frame = cam.read()


    img = model.predict(frame, confidence=40, overlap=30)

    cv2.imshow('video', img)

    key = cv2.waitKey(1)
    if key == 27:
        break

cam.release()
cv2.destroyAllWindows()

# infer on a local image
# print(model.predict("your_image.jpg", confidence=40, overlap=30).json())

# visualize your prediction
# model.predict("your_image.jpg", confidence=40, overlap=30).save("prediction.jpg")

# infer on an image hosted elsewhere
# print(model.predict("URL_OF_YOUR_IMAGE", hosted=True, confidence=40, overlap=30).json())