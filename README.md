# nodelet_cv_demo
Shows how to use nodelets in the context of computer vision

You need the ROS usb-cam package:

```sudo apt-get install ros-indigo-usb-cam```

## How to use
First download and compile the package inside a catkin-workspace.

There are two demo pipelines:

1. usb_cam -> gray -> canny -> scale (```roslaunch nodelet_cv_demo demo_pipeline_1.launch```)
2. usb_cam -> scale -> canny (```roslaunch nodelet_cv_demo demo_pipeline_2.launch```)

With rqt you can check the result of every single filter.
