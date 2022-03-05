# Getting Started with Mipi_Cam Node
---
## Intro
---
通过阅读本文档，用户可以在地平线X3开发板上轻松抓取mipi摄像头的视频流数据，并通过ROS平台发布满足ROS标准的图片数据，供其他ROS Node订阅获取。目前支持F37、IMX415 mipi标准设备。
Mipi_cam Node package是地平线机器人开发平台的一部分，基于地平线VIO和ROS2 Node进行二次开发，为应用开发提供简单易用的摄像头数据采集功能的功能，避免重复开发获取视频的工作。
# Build
---

## 开发环境
- 编程语言：C/C++
- 开发平台：X3/X86
- 系统版本：Ubuntu 20.0.4
- 编译工具链：Linux GCC 9.3.0/Linaro GCC 9.3.0
## package说明
---
源码包含mipi_cam package。mipi_cam 编译完成后，头文件、动态库以及依赖安装在install/mipi_cam 路径。
# 编译
编译环境确认：
- 当前编译终端设置ROS环境变量：source /opt/ros/foxy/setup.bash。
- 已安装ROS2编译工具colcon，安装的ROS不包含编译工具colcon，需要手动安装colcon。命令：apt update ;apt install python3-colcon-common-extensions
编译：colcon build --packages-select mipi_cam
项目依赖开源的package，需要手动安装：

```
# 方法1:使用apt 安装，以cv_bridge 为例：
sudo apt-get install ros-foxy-cv-bridge -y
# 方法2：使用 rosdep检查并自动安装pkg依赖：
#安装 rosdep
sudo apt-get install python3-pip
sudo pip install rosdep
sudo rosdep init
rosdep update
#在ros 的工程路径下执行安装依赖，需要指定pkg所在路径。默认为所有pkg安装依赖，也可以指定为某个pkg安装依赖：
rosdep install -i --from-path . --rosdistro foxy -y
```
## Usage
用户直接调用ros2 命令启动即可：
ros2 run mipi_cam mipi_cam，node会发布image以及compressed格式图片。
利用 rqt_image_view 可以查看发布的图片主题，也可以用图片消费节点。例如：这个repo下的example去直接获取图片进行推理等应用。
