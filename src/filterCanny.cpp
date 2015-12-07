#include "filterCanny.h"

// this should really be in the implementation (.cpp file)
#include <pluginlib/class_list_macros.h>

// watch the capitalization carefully
PLUGINLIB_EXPORT_CLASS(vision::FilterCanny, nodelet::Nodelet)

namespace vision
{
   FilterCanny::FilterCanny(){

   }

   FilterCanny::~FilterCanny(){

   }

   void FilterCanny::onInit()
   {
      ROS_INFO("Initializing nodelet \"%s\"", getName().c_str());
      bool ready = true;

      getPrivateNodeHandle().param<double>("threshold1", thresh1, 0.5);
      getPrivateNodeHandle().param<double>("threshold2", thresh2, 0.9);
      getPrivateNodeHandle().param<int>("apertureSize", aperture, 3);
      getPrivateNodeHandle().param<bool>("L2gradient", l2grad, false);

      image_transport::ImageTransport it_handle(getNodeHandle());

      if ( getPrivateNodeHandle().hasParam("input_topic") ) {
         std::string input_topic;
         getPrivateNodeHandle().getParam("input_topic", input_topic);
         img_sub = it_handle.subscribe(input_topic, 1, &FilterCanny::inputCallback, this);
      } else {
         ready = false;
         ROS_FATAL("Parameter \"%s/input_topic\" wasn't set. Nothing will be done.", getName().c_str());
      }

      if ( getPrivateNodeHandle().hasParam("output_topic") ) {
         std::string output_topic;
         getPrivateNodeHandle().getParam("output_topic", output_topic);
         img_pub = it_handle.advertise(output_topic, 1);
      } else {
         ready = false;
         ROS_FATAL("Parameter \"%s/output_topic\" wasn't set. Nothing will be done.", getName().c_str());
      }

      if (ready) {
         ROS_INFO("Nodelet \"%s\" ready. Params: thresh1=%.3lf; thresh2=%.3lf; aperture=%i; l2grad=%s", getName().c_str(),
            thresh1, thresh2, aperture, (l2grad) ? "true" : "false");
      }
   }

   void FilterCanny::inputCallback(const sensor_msgs::ImageConstPtr& input_msg)
   {
      cv::Mat input_image, output_image;

      try
      {
         input_image = cv_bridge::toCvShare(input_msg, "bgr8")->image;
      }
      catch (cv_bridge::Exception& e)
      {
         ROS_ERROR("Could not convert from '%s' to 'bgr8'.", input_msg->encoding.c_str());
      }

      //Doing awesome stuff on working_image with openCV
      cv::cvtColor(input_image, input_image, CV_BGR2GRAY);
      cv::Canny(input_image, output_image, thresh1, thresh2, aperture, l2grad);
      cv::cvtColor(output_image, output_image, CV_GRAY2BGR);

      sensor_msgs::ImagePtr output_msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", output_image).toImageMsg();
      img_pub.publish(output_msg);
   }

}
