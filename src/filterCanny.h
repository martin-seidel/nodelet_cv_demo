#pragma once

#include <nodelet/nodelet.h>

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

//#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace vision
{
   /** The name of the class should also used as name of the Library
   (CMakeLists.txt and nodelet_plugins.xml) and for starting the nodelet inside
   the launch-script.
   **/
   class FilterCanny : public nodelet::Nodelet
   {
      image_transport::Publisher img_pub; /**< send images from this nodelet **/
      image_transport::Subscriber img_sub;   /**< receive images for this nodelet **/

      double thresh1;
      double thresh2;
      int aperture;
      bool l2grad;

   public:
      FilterCanny(); /**< Intentionally left empty. **/
      virtual ~FilterCanny(); /**< Intentionally left empty. **/

      /** Do the initialisation normally done in the constructor. Create
      #img_sub and #img_pub . **/
      virtual void onInit();

      /** Convert the received ros-image into a Cv::Mat. Then you can do real
      cool stuff with openCV on the image. Afterwards the image will be
      published as sensor_msgs::ImagePtr. **/
      void inputCallback(const sensor_msgs::ImageConstPtr& input_msg);
   };
}
