import cv2
import math
from pupil_apriltags import Detector
import cv2 
  
  
# define a video capture object 

class vision:
   def __init__(self, vid_device):
      self.tags_list = []
      self.objects = []
      self.tag_in_frame = False
      self.obj_in_frame = False
      self.vid = cv2.VideoCapture(vid_device)
      self.frame = None
      self.at_detector = Detector(
      families="tag36h11",
      nthreads=1,
      quad_decimate=1.0,
      quad_sigma=0.0,
      refine_edges=1,
      decode_sharpening=0.25,
      debug=0
   )

   def getFrame(self):
      ret, self.frame = self.vid.read() 

   def drawCross(self,center):
    height = self.frame.shape[0]
    width = self.frame.shape[1]

    heightB = round(center[1])
    widthB = round(center[0])
    # Drawing the lines'
    # print(heightB)
    cv2.line(self.frame, (0, heightB), (width, heightB), (0, 0, 255), 2)
    cv2.line(self.frame, (widthB, 0), (widthB, height), (0, 0, 255), 2)

   def getTag(self):
      self.getFrame()
      gray_image = cv2.cvtColor(self.frame, cv2.COLOR_BGR2GRAY) 
      fx = ( gray_image.shape[0] / 2.0 ) / math.tan( (math.pi * 120/180.0 )/2.0 )
      fy = ( gray_image.shape[1] / 2.0 ) / math.tan( (math.pi * 120/180.0 )/2.0 )
      cx = gray_image.shape[0]/2
      cy = gray_image.shape[1]/2


      tags = self.at_detector.detect(gray_image, estimate_tag_pose=True, camera_params=[fx,fy,cx,cy], tag_size=1)
      self.tags_list = []
      # rotation matrix \
      if(len(tags) > 0):
         self.tag_in_frame = True
         temp_tag = tags[0]
         for tag in tags:
            Id = tags[0].tag_id
            # tag_center = tags[0].center
            if(tag.corners.sum() > temp_tag.corners.sum()):
               temp_tag = tag
         # print(tags[0].corners.sum())
         # self.drawCross(temp_tag.center)
         # print(temp_tag.tag_id)
         return temp_tag.tag_id
      else:
         # print("no tag detected")
         self.tag_in_frame = False
         return None

   def __del__(self):
        self.vid.release()
        cv2.destroyAllWindows() 
        print('Destructor called, vision deleted')

    
def main():
   cam = vision(0)
   while(True): 
      
         # Display the resulting frame 
         cam.getTag()
         cv2.imshow('frame', cam.frame) 
         # the 'q' button is set as the 
         # quitting button you may use any 
         # desired button of your choice 
         if cv2.waitKey(1) & 0xFF == ord('q'): 
            break
      # After the loop release the cap object 
   del cam

if __name__ == "__main__":
    main()
