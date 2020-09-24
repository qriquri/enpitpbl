

// %Tag(FULLTEXT)%
// %Tag(ROS_HEADER)%
#include "ros/ros.h"
// %EndTag(ROS_HEADER)%
// %Tag(MSG_HEADER)%
#include "std_msgs/String.h"
// %EndTag(MSG_HEADER)%

#include <sstream>
#include <string.h>
#include <stdlib.h>
#include<cmath>
//custommessage
#include <gnc/command.h>
#include <gnc/GoalPos.h>

#include <SDL2/SDL.h>
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
    char str[10];	
    char cmd[2];		
    char chDist[10];
    double dDist = 0;		

    printf("Chose command.\nq w e * * * u i * *\n a s d * * h * *l\n z x c * * * *\n");
    printf("And Setting distance!!\n");
    scanf("%s", str);

    strncpy(cmd, str, 1);
    cmd[1] = '\0';

    strncpy(chDist, str + 1, strlen(str) - 1);
    chDist[strlen(str) - 1] = '\0';
    dDist = atof(chDist);

	
    if(!dDist){
      dDist = 0.5;
    }
    
    switch(cmd[0]){
        case 'u':
          command.com = "up"; 
          command.z = dDist;
          
          break;
        case 'i':
          command.com = "down"; 
          command.z = -dDist;
          
          break;
        case 'w':
          command.com = "front"; 
          command.y = dDist;
          
          break;
        case 'e':
          command.com = "rfront"; 
          command.x = dDist/sqrt(2);
          command.y = dDist/sqrt(2);
          //stop_flag =1; 
          break;
        case 'd': 
          command.com = "right";
          command.x = dDist;
          //stop_flag =0; 
          break;
        case 'c':
          command.com = "rback"; 
          command.x = dDist/sqrt(2);
          command.y = -dDist/sqrt(2);
          //stop_flag =1; 
          break;
        case 'x':
          command.com = "back";
          command.y = -dDist;
          // stop_flag =0; 
          break;
        case 'z':
          command.com = "lback";
          command.x = -dDist/sqrt(2);
          command.y = -dDist/sqrt(2);
          // stop_flag =0; 
          break;
        case 'a':
          command.com = "left"; 
          command.x = -dDist;
          break;
        case 'q':
          command.com = "lfront";
          
          command.x = -dDist/sqrt(2);
          command.y = dDist/sqrt(2);
          // stop_flag =1; 
          break;
        case 's':
          command.com = "stop"; 
          stop_flag =1; 
          break;
        case 'm':
          command.com = "mark"; 
          
          break;
        case 'l':
          command.com = "land"; 
          break;
        case 'h':
          command.com = "home";
          command.x = 0;
          command.y = 0; 
          break;
        default:
          break;
      }
      
    
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

