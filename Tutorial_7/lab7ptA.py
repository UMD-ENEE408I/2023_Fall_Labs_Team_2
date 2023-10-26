import cv2
import numpy as np

# define the minimum confidence (to filter weak detections), 
# Non-Maximum Suppression (NMS) threshold, and the green color
confidence_thresh = 0.5
NMS_thresh = 0.3
green = (0, 255, 0)

# Load the image and get its dimensions
image = cv2.imread("images/street2.jpg")
# resize the image to 25% of its original size
image = cv2.resize(image, 
                    (int(image.shape[0] * 0.25), 
                     int(image.shape[1] * 0.25)))

# get the image dimensions
h = image.shape[0]
w = image.shape[1]

# load the class labels the model was trained on
classes_path = "yolov3-config/coco.names"
with open(classes_path, "r") as f:
    classes = f.read().strip().split("\n")

# load the configuration and weights from disk
yolo_config = "yolov3-config/yolov3.cfg"
yolo_weights = "yolov3-config/yolov3.weights"

# load YOLOv3 network pre-trained on the COCO dataset
net = cv2.dnn.readNetFromDarknet(yolo_config, yolo_weights)
net.setPreferableBackend(cv2.dnn.DNN_BACKEND_OPENCV)
net.setPreferableTarget(cv2.dnn.DNN_TARGET_CPU)

# CUDA backend
net.setPreferableBackend(cv2.dnn.DNN_BACKEND_CUDA)
net.setPreferableTarget(cv2.dnn.DNN_TARGET_CUDA)

# Get the name of all the layers in the network
layer_names = net.getLayerNames()
# Get the names of the output layers
unconnected_indices = net.getUnconnectedOutLayers()
output_layers = [layer_names[index - 1] for index in unconnected_indices]

# create a blob from the image
blob = cv2.dnn.blobFromImage(
    image, 1 / 255, (416, 416), swapRB=True, crop=False)
# pass the blob through the network and get the output predictions
net.setInput(blob)
outputs = net.forward(output_layers)

print(output_layers)

['yolo_82', 'yolo_94', 'yolo_106']

# create empty lists for storing the bounding boxes, confidences, and class IDs
boxes = []
confidences = []
class_ids = []

# loop over the output predictions
for output in outputs:
    # loop over the detections
    for detection in output:
        # get the class ID and confidence of the dected object
        scores = detection[5:]
        class_id = np.argmax(scores)
        confidence  = scores[class_id]

        # we keep the bounding boxes if the confidence (i.e. class probability) 
        # is greater than the minimum confidence 
        if confidence > confidence_thresh:
            # perform element-wise multiplication to get
            # the coordinates of the bounding box
            box = [int(a * b) for a, b in zip(detection[0:4], [w, h, w, h])]
            center_x, center_y, width, height = box

            # get the top-left corner of the bounding box
            x = int(center_x - (width / 2))
            y = int(center_y - (height / 2))

            # append the bounding box, confidence, and class ID to their respective lists
            class_ids.append(class_id)
            confidences.append(float(confidence))
            boxes.append([x, y, width, height])

# apply non-maximum suppression to remove weak bounding boxes that overlap with others.
indices = cv2.dnn.NMSBoxes(boxes, confidences, confidence_thresh, NMS_thresh)
indices = indices.flatten()
for i in indices:
    (x, y, w, h) = boxes[i][0], boxes[i][1], boxes[i][2], boxes[i][3]
    cv2.rectangle(image, (x, y), (x + w, y + h), green, 2)
    text = f"{classes[class_ids[i]]}: {confidences[i] * 100:.2f}%"
    cv2.putText(image, text, (x, y - 15), cv2.FONT_HERSHEY_SIMPLEX, 0.5, green, 2)
    
# show the output image
cv2.imshow("After NMS", image)
cv2.waitKey(0)