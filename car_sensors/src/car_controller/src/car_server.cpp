//this program toggles between rotation and translation
//commands,based on calls to a service.
#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <car_controller/Changerate.h>//for the srv
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/PointCloud.h>

geometry_msgs::Twist twist_msg;

bool changeTwist(
       car_controller::Changerate::Request &req,
       car_controller::Changerate::Response &resp){
       ROS_INFO_STREAM("Now change linear: "<<req.linear_x<<" angular: "<< req.angular_z);
       twist_msg.linear.x = req.linear_x;
       twist_msg.angular.z = req.angular_z;
       return true;
}


void imu_callback(const sensor_msgs::Imu::ConstPtr& msg) //callback for
{
  //ROS_INFO( "Accel: %.3f,%.3f,%.3f [m/s^2] - Ang. vel: %.3f,%.3f,%.3f [deg/sec] - Orient. Quat: %.3f,%.3f,%.3f,%.3f",
  //           msg->linear_acceleration.x, msg->linear_acceleration.y, msg->linear_acceleration.z,
  //             msg->angular_velocity.x, msg->angular_velocity.y, msg->angular_velocity.z,
  //             msg->orientation.x, msg->orientation.y, msg->orientation.z, msg->orientation.w);
}

void lidar_scan_callback(const sensor_msgs::PointCloud::ConstPtr& msg){

}

int main(int argc, char **argv){
       ros::init(argc,argv,"car_node");
       ros::NodeHandle nh;

       ros::ServiceServer server =
               nh.advertiseService("/cmd_vel_server", &changeTwist);

       ros::Publisher pub=
               nh.advertise<geometry_msgs::Twist>("/cmd_vel",1000);

       ros::Subscriber sub_imu =
               nh.subscribe("/imu",1000,imu_callback);

       ros::Subscriber sub_scan =
                nh.subscribe("/slam_cloud", 1000,lidar_scan_callback);

       ros::Rate rate(2);
       while(ros::ok()){
               pub.publish(twist_msg);
               ros::spinOnce();
               rate.sleep();
       }
}
