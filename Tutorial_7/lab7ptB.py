import cv2
import math
from pupil_apriltags import Detector



img = cv2.imread("test_img.png",cv2.IMREAD_GRAYSCALE)
cv2.imshow("img",img)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
at_detector = Detector(
   families="tag36h11",
   nthreads=1,
   quad_decimate=1.0,
   quad_sigma=0.0,
   refine_edges=1,
   decode_sharpening=0.25,
   debug=0
)
fx = ( img.shape[0] / 2.0 ) / math.tan( (math.pi * 120/180.0 )/2.0 )
fy = ( img.shape[1] / 2.0 ) / math.tan( (math.pi * 120/180.0 )/2.0 )
cx = img.shape[0]/2
cy = img.shape[1]/2
tags = at_detector.detect(img, estimate_tag_pose=True, camera_params=[fx,fy,cx,cy], tag_size=1)
# rotation matrix 
print(tags[0].pose_R)
