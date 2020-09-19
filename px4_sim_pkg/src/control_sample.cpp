/**
 * @file offb_node.cpp
 * @brief Offboard control example node, written with MAVROS version 0.19.x, PX4 Pro Flight
 * Stack and tested in Gazebo SITL
 */
/*
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include "std_msgs/String.h"
#include <sstream>




mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}
using std::cout;
int main(int argc, char **argv)
{
    ros::init(argc, argv, "ctrls_node"); 
    ros::NodeHandle n;
    ros::Publisher ctrl_pub = n.advertise<std_msgs::String>("gnc_node/cmd", 1000);
    ros::Rate loop_rate(10);
    std_msgs::String command;
    std::stringstream ss;
    ss << "halt" << count;
    command.data = ss.str();
 
    ROS_INFO("%s", command.data.c_str());
    ctrl_pub.publish(command);
 
    ros::spinOnce();
 
 
*/
/*
    //Messages for using topics and services provided 
    //by the mavros package are defined in the mavros_msgs package.
    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;
    //Initializing a subscriber to subscribe to messages of type 
    //std_msgs::String that are published to the gnc / cmd topic
    //ros::Subscriber state_sub = nh.subscribe<std_msgs::String>
      //      ("gnc_node/cmd", 10, command_cb);
    //Initializing a publisher that publishes messages of type 
    //std_msgs::String to the gnc_node/cmd topic.
    ros::Publisher local_pos_pub = nh.advertise<std_msgs::String>
            ("gnc_node/cmd", 10);

    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>
            ("mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>
            ("mavros/set_mode");

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(20.0);

    // wait for FCU connection
    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }

    
   std_msgs::String com = "halt";

    //send a few setpoints before starting
    for(int i = 100; ros::ok() && i > 0; --i){
        local_pos_pub.publish(com);
        ros::spinOnce();
        rate.sleep();
    }


    mavros_msgs::SetMode offb_set_mode;
    offb_set_mode.request.custom_mode = "OFFBOARD";

    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;

    ros::Time last_request = ros::Time::now();
*/
/*
    while(ros::ok()){
        if( current_state.mode != "OFFBOARD" &&
            (ros::Time::now() - last_request > ros::Duration(5.0))){
            if( set_mode_client.call(offb_set_mode) &&
                offb_set_mode.response.mode_sent){
                ROS_INFO("Offboard enabled");
            }
            last_request = ros::Time::now();
        } else {
            if( !current_state.armed &&
                (ros::Time::now() - last_request > ros::Duration(5.0))){
                if( arming_client.call(arm_cmd) &&
                    arm_cmd.response.success){
                    ROS_INFO("Vehicle armed");
                }
                last_request = ros::Time::now();
            }
        }

        local_pos_pub.publish(pose);

        ros::spinOnce();
        rate.sleep();
    }


    return 0;
}
*/

// %Tag(FULLTEXT)%
// %Tag(ROS_HEADER)%
#include "ros/ros.h"
// %EndTag(ROS_HEADER)%
// %Tag(MSG_HEADER)%
#include "std_msgs/String.h"
// %EndTag(MSG_HEADER)%

#include <sstream>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  
// %Tag(INIT)%
  ros::init(argc, argv, "ctrls");
// %EndTag(INIT)%

  
// %Tag(NODEHANDLE)%
  ros::NodeHandle n;
// %EndTag(NODEHANDLE)%

  
// %Tag(PUBLISHER)%
  ros::Publisher ctrl_pub = n.advertise<std_msgs::String>("gnc_node/cmd", 1000);
// %EndTag(PUBLISHER)%

// %Tag(LOOP_RATE)%
  ros::Rate loop_rate(10);
// %EndTag(LOOP_RATE)%

 
// %Tag(ROS_OK)%
  int count = 0;
  while (ros::ok())
  {
// %EndTag(ROS_OK)%
   
// %Tag(FILL_MESSAGE)%
    std_msgs::String command;

    std::stringstream ss;
    ss << "halt" << count;
    command.data = ss.str();
// %EndTag(FILL_MESSAGE)%

// %Tag(ROSCONSOLE)%
    ROS_INFO("%s", command.data.c_str());
// %EndTag(ROSCONSOLE)%

   
// %Tag(PUBLISH)%
    ctrl_pub.publish(command);
// %EndTag(PUBLISH)%

// %Tag(SPINONCE)%
    ros::spinOnce();
// %EndTag(SPINONCE)%

// %Tag(RATE_SLEEP)%
    loop_rate.sleep();
// %EndTag(RATE_SLEEP)%
   ++count;
  }


  return 0;
}
// %EndTag(FULLTEXT)%

