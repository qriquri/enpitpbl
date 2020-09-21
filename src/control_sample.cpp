

// %Tag(FULLTEXT)%
// %Tag(ROS_HEADER)%
#include "ros/ros.h"
// %EndTag(ROS_HEADER)%
// %Tag(MSG_HEADER)%
#include "std_msgs/String.h"
// %EndTag(MSG_HEADER)%

#include <sstream>
//custommessage
#include <gnc/command.h>
#include <gnc/GoalPos.h>
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
  ros::NodeHandle c;
  ros::NodeHandle g;
// %EndTag(NODEHANDLE)%

  
// %Tag(PUBLISHER)%
  ros::Publisher ctrl_pub = n.advertise<std_msgs::String>("gnc_node/cmd", 1000);
  ros::Publisher command_pub = c.advertise<gnc::command>("gnc_node/command", 1000);

  ros::Publisher goal_pub = g.advertise<gnc::GoalPos>("gnc_node/goalpos", 1000);
// %EndTag(PUBLISHER)%

// %Tag(LOOP_RATE)%
  ros::Rate loop_rate(10);
// %EndTag(LOOP_RATE)%

 
// %Tag(ROS_OK)%
  int count = 0;
  int stop_flag = 1;
  while (ros::ok())
  {
// %EndTag(ROS_OK)%
   
// %Tag(FILL_MESSAGE)%
    //std_msgs::String command;
    gnc::command command;
    gnc::GoalPos position;
    //std::stringstream ss;
    //SELECT COMMAND
    int msg;
    float x = 0; float y = 0; float z = 0;
    //printf("%d %d %d", 'w', "w", 'a');
    if(stop_flag == 1){
      printf("1:UP\n2:DOWN\n3:FRONT\n4:BACK\n5:LEFT\n6:RITHI\n7:STOP\n0:HALT\n");
      printf("And set XYZ when you use 1~6 command.\n");
    }else{
      printf("Please stop before next action!!!!\n7:STOP\n");
    }
    scanf("%d %f %f %f", &msg, &x, &y, &z);
    command.x = x;
    command.y = y;
    command.z = z;
    switch(msg){
       case 4:
        command.com = "back"; stop_flag =0; break;
       case 2:
        command.com = "down"; stop_flag =1; break;
       case 3: 
        command.com = "front";stop_flag =0; break;
       case 0:
        command.com = "halt"; stop_flag =1; break;
       case 5:
        command.com = "left"; stop_flag =0; break;
       case 6:
        command.com = "right"; stop_flag =0; break;
       case 7:
        command.com = "stop"; stop_flag =1; break;
       
       case 1:
        command.com = "up"; stop_flag =1; break;
       default:
        break;
    }
    //ss << tmp << count;
    
// %EndTag(FILL_MESSAGE)%

// %Tag(ROSCONSOLE)%
    ROS_INFO("%s", command.com.c_str());
    ROS_INFO("%f %f %f", command.x, command.y, command.z);
   char com[10];

sprintf(com, "%s", command.com.c_str());
   if(strcmp("halt", com) == 0){
     printf("sucsess\n");
}
// %EndTag(ROSCONSOLE)%

   
// %Tag(PUBLISH)%
    //ctrl_pub.publish(command);
    command_pub.publish(command);
    //goal_pub.publish(position);
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

