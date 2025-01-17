#include "gnc.h"
#include "MAV.h"

/* imported from iq_gnc 
   https://github.com/Intelligent-Quads/iq_gnc */

#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/State.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <cmath>
#include <math.h>
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/PositionTarget.h>
#include <sensor_msgs/LaserScan.h>
#include <unistd.h>
#include <vector>
#include <ros/duration.h>
#include <iostream>
#include <string>
#include <signal.h>

// custommsg
#include <gnc/command.h>
#include <gnc/GoalPos.h>
/**
\defgroup control_functions
This module is designed to make high level control programming more simple. 
*/


mavros_msgs::State current_state_g;
nav_msgs::Odometry current_pose_g;
geometry_msgs::Pose correction_vector_g;
geometry_msgs::Point local_offset_pose_g;
geometry_msgs::PoseStamped waypoint_g;
bool is_waypoint_set = false;

float current_heading_g;
float local_offset_g;
float correction_heading_g = 0;
float local_desired_heading_g; 



ros::Publisher local_pos_pub;
ros::Subscriber currentPos;
ros::Subscriber state_sub;
ros::Subscriber collision_sub;
ros::ServiceClient arming_client;
ros::ServiceClient land_client;
ros::ServiceClient set_mode_client;
ros::ServiceClient takeoff_client;
//ros::Subscriber command_sub;

//MY_CODE-BEGIN
ros::Subscriber command_sub;
//ros::Subscriber goal_pos_sub;
struct MY_POSITION{
	float x;
	float y;
	float z;
};
struct GOAL_POSITION{
	float x;
	float y;
	float z;
};
struct MY_POSITION My_position;
struct GOAL_POSITION Goal_Pos;
//MYCODE-END
/**
\ingroup control_functions
This structure is a convenient way to format waypoints
*/
struct gnc_api_waypoint{
	float x; ///< distance in x with respect to your reference frame
	float y; ///< distance in y with respect to your reference frame
	float z; ///< distance in z with respect to your reference frame
	float psi; ///< rotation about the third axis of your reference frame
};

//get armed state
void state_cb(const mavros_msgs::State::ConstPtr& msg)
{
  current_state_g = *msg;
}

geometry_msgs::Point enu_2_local(nav_msgs::Odometry current_pose_enu)
{
  float x = current_pose_enu.pose.pose.position.x;
  float y = current_pose_enu.pose.pose.position.y;
  float z = current_pose_enu.pose.pose.position.z;
  float deg2rad = (M_PI/180);
  geometry_msgs::Point current_pos_local;
  current_pos_local.x = x*cos((local_offset_g - 90)*deg2rad) - y*sin((local_offset_g - 90)*deg2rad);
  current_pos_local.y = x*sin((local_offset_g - 90)*deg2rad) + y*cos((local_offset_g - 90)*deg2rad);
  current_pos_local.z = z;

  return current_pos_local;

  //ROS_INFO("Local position %f %f %f",X, Y, Z);
}
//get current position of drone
void pose_cb(const nav_msgs::Odometry::ConstPtr& msg)
{
  current_pose_g = *msg;
  enu_2_local(current_pose_g);
  float q0 = current_pose_g.pose.pose.orientation.w;
  float q1 = current_pose_g.pose.pose.orientation.x;
  float q2 = current_pose_g.pose.pose.orientation.y;
  float q3 = current_pose_g.pose.pose.orientation.z;
  float psi = atan2((2*(q0*q3 + q1*q2)), (1 - 2*(pow(q2,2) + pow(q3,2))) );
  //ROS_INFO("Current Heading %f ENU", psi*(180/M_PI));
  //Heading is in ENU
  //IS YAWING COUNTERCLOCKWISE POSITIVE?
  current_heading_g = psi*(180/M_PI) - local_offset_g;
  //ROS_INFO("Current Heading %f origin", current_heading_g);
  //ROS_INFO("x: %f y: %f z: %f", current_pose_g.pose.pose.position.x, current_pose_g.pose.pose.position.y, current_pose_g.pose.pose.position.z);
}
geometry_msgs::Point get_current_location()
{
	geometry_msgs::Point current_pos_local;
	current_pos_local = enu_2_local(current_pose_g);
	return current_pos_local;

}
float gnc_get_heading()
{
	return current_heading_g;
}


//set orientation of the drone (drone should always be level) 
// Heading input should match the ENU coordinate system
/**
\ingroup control_functions
This function is used to specify the drone’s heading in the local reference frame. Psi is a counter clockwise rotation following the drone’s reference frame defined by the x axis through the right side of the drone with the y axis through the front of the drone. 
@returns n/a
*/
void gnc_set_heading(float heading)
{
  local_desired_heading_g = heading; 
  heading = heading + correction_heading_g + local_offset_g;
  
  ROS_INFO("Desired Heading %f ", local_desired_heading_g);
  float yaw = heading*(M_PI/180);
  float pitch = 0;
  float roll = 0;

  float cy = cos(yaw * 0.5);
  float sy = sin(yaw * 0.5);
  float cr = cos(roll * 0.5);
  float sr = sin(roll * 0.5);
  float cp = cos(pitch * 0.5);
  float sp = sin(pitch * 0.5);

  float qw = cy * cr * cp + sy * sr * sp;
  float qx = cy * sr * cp - sy * cr * sp;
  float qy = cy * cr * sp + sy * sr * cp;
  float qz = sy * cr * cp - cy * sr * sp;

  waypoint_g.pose.orientation.w = qw;
  waypoint_g.pose.orientation.x = qx;
  waypoint_g.pose.orientation.y = qy;
  waypoint_g.pose.orientation.z = qz;
}
// set position to fly to in the local frame
/**
\ingroup control_functions
This function is used to command the drone to fly to a waypoint. These waypoints should be specified in the local reference frame. This is typically defined from the location the drone is launched. Psi is counter clockwise rotation following the drone’s reference frame defined by the x axis through the right side of the drone with the y axis through the front of the drone. 
@returns n/a
*/
void gnc_set_destination(float x, float y, float z)
{
	// set_heading(psi);
	//transform map to local
	// float deg2rad = (M_PI/180);
	// float Xlocal = x*cos((correction_heading_g + local_offset_g - 90)*deg2rad) - y*sin((correction_heading_g + local_offset_g - 90)*deg2rad);
	// float Ylocal = x*sin((correction_heading_g + local_offset_g - 90)*deg2rad) + y*cos((correction_heading_g + local_offset_g - 90)*deg2rad);
	// float Zlocal = z;

	// x = Xlocal + correction_vector_g.position.x + local_offset_pose_g.x;
	// y = Ylocal + correction_vector_g.position.y + local_offset_pose_g.y;
	// z = Zlocal + correction_vector_g.position.z + local_offset_pose_g.z;
	x = Goal_Pos.x;
	y = Goal_Pos.y;
	z = Goal_Pos.z;
	ROS_INFO("Destination set to x: %f y: %f z: %f origin frame", x, y, z);
    
//	waypoint_g.pose.position.x = x;
//	waypoint_g.pose.position.y = y;
//	waypoint_g.pose.position.z = z;
	//MYCODE-BEGIN
	waypoint_g.pose.position.x = x + My_position.x;
	waypoint_g.pose.position.y = y + My_position.y;
	waypoint_g.pose.position.z = z + My_position.z;
//	waypoint_g.pose.position.x = x + current_pose_g.pose.pose.position.x;
//	waypoint_g.pose.position.y = y + current_pose_g.pose.pose.position.y;
//    waypoint_g.pose.position.z = z + current_pose_g.pose.pose.position.z;
    My_position.x = waypoint_g.pose.position.x;
    My_position.y = waypoint_g.pose.position.y;
    My_position.z = waypoint_g.pose.position.z;
//    current_pose_g.pose.pose.position.x = waypoint_g.pose.position.x;
//    current_pose_g.pose.pose.position.y = waypoint_g.pose.position.y;
//    current_pose_g.pose.pose.position.z = waypoint_g.pose.position.z;
    //MYCODE-END

    is_waypoint_set = true;
	local_pos_pub.publish(waypoint_g);
}
/**
\ingroup control_functions
Wait for connect is a function that will hold the program until communication with the FCU is established.
@returns 0 - connected to fcu 
@returns -1 - failed to connect to drone
*/
int wait4connect()
{
	ROS_INFO("Waiting for FCU connection");
	// wait for FCU connection
	while (ros::ok() && !current_state_g.connected)
	{
		ros::spinOnce();
		ros::Duration(0.01).sleep();
	}
	if(current_state_g.connected)
	{
		ROS_INFO("Connected to FCU");	
		return 0;
	}else{
		ROS_INFO("Error connecting to drone");
		return -1;	
	}
	
	
}
/**
\ingroup control_functions
Wait for strat will hold the program until the user signals the FCU to enther mode guided. This is typically done from a switch on the safety pilot’s remote or from the ground control station.
@returns 0 - mission started
@returns -1 - failed to start mission
*/
int wait4start()
{
	ROS_INFO("Waiting for user to set mode to GUIDED");
	while(ros::ok() && current_state_g.mode != "GUIDED")
	{
	    ros::spinOnce();
	    ros::Duration(0.01).sleep();
  	}
  	if(current_state_g.mode == "GUIDED")
	{
		ROS_INFO("Mode set to GUIDED. Mission starting");
		return 0;
	}else{
		ROS_INFO("Error starting mission!!");
		return -1;	
	}
}
/**
\ingroup control_functions
This function will create a local reference frame based on the starting location of the drone. This is typically done right before takeoff. This reference frame is what all of the the set destination commands will be in reference to.
@returns 0 - frame initialized
*/
int initialize_local_frame()
{
	//set the orientation of the local reference frame
	ROS_INFO("Initializing local coordinate system");
	local_offset_g = 0;
	for (int i = 1; i <= 30; i++) {
		ros::spinOnce();
		ros::Duration(0.1).sleep();

		

		float q0 = current_pose_g.pose.pose.orientation.w;
		float q1 = current_pose_g.pose.pose.orientation.x;
		float q2 = current_pose_g.pose.pose.orientation.y;
		float q3 = current_pose_g.pose.pose.orientation.z;
		float psi = atan2((2*(q0*q3 + q1*q2)), (1 - 2*(pow(q2,2) + pow(q3,2))) ); // yaw

		local_offset_g += psi*(180/M_PI);

		local_offset_pose_g.x = local_offset_pose_g.x + current_pose_g.pose.pose.position.x;
		local_offset_pose_g.y = local_offset_pose_g.y + current_pose_g.pose.pose.position.y;
		local_offset_pose_g.z = local_offset_pose_g.z + current_pose_g.pose.pose.position.z;
		// ROS_INFO("current heading%d: %f", i, local_offset_g/i);
	}
	local_offset_pose_g.x = local_offset_pose_g.x/30;
	local_offset_pose_g.y = local_offset_pose_g.y/30;
	local_offset_pose_g.z = local_offset_pose_g.z/30;
	local_offset_g /= 30;
	ROS_INFO("Coordinate offset set");
	ROS_INFO("the X' axis is facing: %f", local_offset_g);
	return 0;
}

int gnc_arm()
{
	//intitialize first waypoint of mission
	gnc_set_heading(0);
	gnc_set_destination(0,0,0);
	for(int i=0; i<100; i++)
	{
		local_pos_pub.publish(waypoint_g);
		ros::spinOnce();
		ros::Duration(0.01).sleep();
	}
	// arming
	ROS_INFO("Arming drone");
	mavros_msgs::CommandBool arm_request;
	arm_request.request.value = true;
	while (!current_state_g.armed && !arm_request.response.success && ros::ok())
	{
		ros::Duration(.1).sleep();
		arming_client.call(arm_request);
		local_pos_pub.publish(waypoint_g);
	}
	if(arm_request.response.success)
	{
		ROS_INFO("Arming Successful");	
		return 0;
	}else{
		ROS_INFO("Arming failed with %d", arm_request.response.success);
		return -1;	
	}
}

/**
\ingroup control_functions
The takeoff function will arm the drone and put the drone in a hover above the initial position. 
@returns 0 - nominal takeoff 
@returns -1 - failed to arm 
@returns -2 - failed to takeoff
*/
int gnc_takeoff(float takeoff_alt)
{
    //MYCODE BEGIN
	Goal_Pos.z = takeoff_alt;
	//MYCODE END
	//intitialize first waypoint of mission
	gnc_set_destination(0,0,takeoff_alt);
	//MYCODE BEGIN
	Goal_Pos.z = 0;
	//MYCODE END
	for(int i=0; i<100; i++)
	{
		local_pos_pub.publish(waypoint_g);
		ros::spinOnce();
		ros::Duration(0.01).sleep();
	}
	// arming
	ROS_INFO("Arming drone");
	mavros_msgs::CommandBool arm_request;
	arm_request.request.value = true;
	while (!current_state_g.armed && !arm_request.response.success && ros::ok())
	{
		ros::Duration(.1).sleep();
		arming_client.call(arm_request);
		local_pos_pub.publish(waypoint_g);
	}
	if(arm_request.response.success)
	{
		ROS_INFO("Arming Successful");	
	}else{
		ROS_INFO("Arming failed with %d", arm_request.response.success);
		return -1;	
	}

	//request takeoff
	
	mavros_msgs::CommandTOL srv_takeoff;
	srv_takeoff.request.altitude = takeoff_alt;
	if(takeoff_client.call(srv_takeoff)){
		sleep(3);
		ROS_INFO("takeoff sent %d", srv_takeoff.response.success);
	}else{
		ROS_ERROR("Failed Takeoff");
		return -2;
	}
	sleep(2);
	return 0; 
}
/**
\ingroup control_functions
This function returns an int of 1 or 0. THis function can be used to check when to request the next waypoint in the mission. 
@return 1 - waypoint reached 
@return 0 - waypoint not reached
*/
int gnc_check_waypoint_reached(float pos_tolerance=0.3, float heading_tolerance=0.01)
{
	static int count = 0;
	local_pos_pub.publish(waypoint_g);
	
	//check for correct position 
	float deltaX = abs(waypoint_g.pose.position.x - current_pose_g.pose.pose.position.x);
    float deltaY = abs(waypoint_g.pose.position.y - current_pose_g.pose.pose.position.y);
    float deltaZ = 0; //abs(waypoint_g.pose.position.z - current_pose_g.pose.pose.position.z);
    float dMag = sqrt( pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2) );

    //check orientation
    float cosErr = cos(current_heading_g*(M_PI/180)) - cos(local_desired_heading_g*(M_PI/180));
    float sinErr = sin(current_heading_g*(M_PI/180)) - sin(local_desired_heading_g*(M_PI/180));
    float headingErr = sqrt( pow(cosErr, 2) + pow(sinErr, 2) );

	count++;
	if (count >= 10) {
		ROS_INFO("dMag %f", dMag);
		ROS_INFO("current pose x %F y %f z %f", (current_pose_g.pose.pose.position.x), (current_pose_g.pose.pose.position.y), (current_pose_g.pose.pose.position.z));
		ROS_INFO("waypoint pose x %F y %f z %f", waypoint_g.pose.position.x, waypoint_g.pose.position.y,waypoint_g.pose.position.z);
    	ROS_INFO("current heading %f", current_heading_g);
     	ROS_INFO("local_desired_heading_g %f", local_desired_heading_g);
     	ROS_INFO("current heading error %f", headingErr);
		count = 0;
	}

    if( dMag < pos_tolerance && headingErr < heading_tolerance)
	{
		return 1;
	}else{
		return 0;
	}
}
/**
\ingroup control_functions
this function changes the mode of the drone to a user specified mode. This takes the mode as a string. ex. set_mode("GUIDED")
@returns 1 - mode change successful
@returns 0 - mode change not successful
*/
int set_mode(std::string mode)
{
	mavros_msgs::SetMode srv_setMode;
    srv_setMode.request.base_mode = 0;
    srv_setMode.request.custom_mode = mode.c_str();
    if(set_mode_client.call(srv_setMode)){
      ROS_INFO("setmode send ok");
    }else{
      ROS_ERROR("Failed SetMode");
      return -1;
    }
}

void scan_cb(const sensor_msgs::LaserScan::ConstPtr& msg)
{
	// sensor_msgs::LaserScan current_2D_scan;
  	// current_2D_scan = *msg;
	// float avoidance_vector_x = 0; 
	// float avoidance_vector_y = 0;
	// bool avoid = false;
	
	// for(int i=1; i<current_2D_scan.ranges.size(); i++)
	// {
	// 	float d0 = 3; 
	// 	float k = 0.5;

	// 	if(current_2D_scan.ranges[i] < d0 && current_2D_scan.ranges[i] > .35)
	// 	{
	// 		avoid = true;
	// 		float x = cos(current_2D_scan.angle_increment*i);
	// 		float y = sin(current_2D_scan.angle_increment*i);
	// 		float U = -.5*k*pow(((1/current_2D_scan.ranges[i]) - (1/d0)), 2);	

	// 		avoidance_vector_x = avoidance_vector_x + x*U;
	// 		avoidance_vector_y = avoidance_vector_y + y*U;

	// 	}
	// }
	// float current_heading = get_current_heading();
	// float deg2rad = (M_PI/180);
	// avoidance_vector_x = avoidance_vector_x*cos((current_heading)*deg2rad) - avoidance_vector_y*sin((current_heading)*deg2rad);
	// avoidance_vector_y = avoidance_vector_x*sin((current_heading)*deg2rad) + avoidance_vector_y*cos((current_heading)*deg2rad);

	// if(avoid)
	// {
	// 	if( sqrt(pow(avoidance_vector_x,2) + pow(avoidance_vector_y,2)) > 3)
	// 	{
	// 		avoidance_vector_x = 3 * (avoidance_vector_x/sqrt(pow(avoidance_vector_x,2) + pow(avoidance_vector_y,2)));
	// 		avoidance_vector_y = 3 * (avoidance_vector_y/sqrt(pow(avoidance_vector_x,2) + pow(avoidance_vector_y,2)));
	// 	}
	// 	geometry_msgs::Point current_pos;
	// 	current_pos = get_current_location();
	// 	set_destination(avoidance_vector_x + current_pos.x, avoidance_vector_y + current_pos.y, 2, 0);	
	// }
}


/**
\ingroup control_functions
this function changes the mode of the drone to land
@returns 1 - mode change successful
@returns 0 - mode change not successful
*/
int gnc_land()
{
  mavros_msgs::CommandTOL srv_land;
  if(land_client.call(srv_land) && srv_land.response.success)
  {
    ROS_INFO("land sent %d", srv_land.response.success);
    return 0;
  }else{
    ROS_ERROR("Landing failed");
    return -1;
  }
}

//MYCODE BEGIN
// void goal_pos_cb(const gnc::GoalPos::ConstPtr& gpos){
//  ROS_INFO("recv goal");
//  Goal_Pos.x = gpos->x;
//  Goal_Pos.y = gpos->y;
//  Goal_Pos.z = gpos->z;
 
// }
void command_cb(const gnc::command::ConstPtr& msg)
{
	char command[10];
	ROS_INFO("recv message");
	sprintf(command, "%s", msg->com.c_str());

	//EXECUTE COMMAND
	if(strcmp("halt", command) == 0){
		ROS_INFO("halt!!!!!!!");
		Control_hault();
	}
	else if(strcmp("up", command) == 0){
		ROS_INFO("up!!!!!!!");
		ROS_INFO("recv goal");
		Goal_Pos.x = msg->x;
		Goal_Pos.y = msg->y;
		Goal_Pos.z = msg->z;
		Control_up();
	}
	else if(strcmp("down", command) == 0){
		ROS_INFO("down!!!!!!!");
		Goal_Pos.x = msg->x;
		Goal_Pos.y = msg->y;
		Goal_Pos.z = msg->z;		
		Control_down();
	}
	else if(strcmp("front", command) == 0){
		ROS_INFO("front!!!!!!!");
		Goal_Pos.x = msg->x;
		Goal_Pos.y = msg->y;
		Goal_Pos.z = msg->z;
		Control_front();
	}
	else if(strcmp("back", command) == 0){
		ROS_INFO("back!!!!!!!");
		Goal_Pos.x = msg->x;
		Goal_Pos.y = msg->y;
		Goal_Pos.z = msg->z;
		Control_back();
	}
	else if(strcmp("left", command) == 0){
		ROS_INFO("left!!!!!!!");
Goal_Pos.x = msg->x;
		Goal_Pos.y = msg->y;
		Goal_Pos.z = msg->z;
				Control_left();
	}
	else if(strcmp("right", command) == 0){
		ROS_INFO("right!!!!!!!");
Goal_Pos.x = msg->x;
		Goal_Pos.y = msg->y;
		Goal_Pos.z = msg->z;		
		Control_right();
	}
	else if(strcmp("stop", command) == 0){
		ROS_INFO("stop!!!!!!!");
		Goal_Pos.x = 0;
		Goal_Pos.y = 0;
		Goal_Pos.z = 0;
		Control_stop();
	}


}
//MYCODE END
/**
\ingroup control_functions
This function is called at the beginning of a program and will start of the communication links to the FCU. The function requires the program's ros nodehandle as an input 
@returns n/a
*/
int init_publisher_subscriber(ros::NodeHandle controlnode)
{
	std::string ros_namespace;
	if (!controlnode.hasParam("namespace"))
	{

		ROS_INFO("using default namespace");
	}else{
		controlnode.getParam("namespace", ros_namespace);
		ROS_INFO("using namespace %s", ros_namespace.c_str());
	}
	local_pos_pub = controlnode.advertise<geometry_msgs::PoseStamped>((ros_namespace + "/mavros/setpoint_position/local").c_str(), 10);
	currentPos = controlnode.subscribe<nav_msgs::Odometry>((ros_namespace + "/mavros/global_position/local").c_str(), 10, pose_cb);
	state_sub = controlnode.subscribe<mavros_msgs::State>((ros_namespace + "/mavros/state").c_str(), 10, state_cb);
	arming_client = controlnode.serviceClient<mavros_msgs::CommandBool>((ros_namespace + "/mavros/cmd/arming").c_str());
	land_client = controlnode.serviceClient<mavros_msgs::CommandTOL>((ros_namespace + "/mavros/cmd/land").c_str());
	set_mode_client = controlnode.serviceClient<mavros_msgs::SetMode>((ros_namespace + "/mavros/set_mode").c_str());
	takeoff_client = controlnode.serviceClient<mavros_msgs::CommandTOL>((ros_namespace + "/mavros/cmd/takeoff").c_str());
	collision_sub = controlnode.subscribe<sensor_msgs::LaserScan>("/spur/laser/scan", 1, scan_cb);
	command_sub = controlnode.subscribe("command", 10, command_cb);
    // goal_pos_sub = controlnode.subscribe("goalpos", 100, goal_pos_cb);
}

void gnc_sigint_handler(int sig) {
	gnc_shutdown();
}

void gnc_init() {
	//initialize ros 
    int argc = 0; // dummy for init
	ros::init(argc, NULL, "gnc_node");
	ros::NodeHandle gnc_node("~");
	
	// Ctrl-C
	signal(SIGINT, gnc_sigint_handler);

	//initialize control publisher/subscribers
	init_publisher_subscriber(gnc_node);

  	// wait for FCU connection
	wait4connect();

	//
	set_mode("GUIDED");

	//wait for used to switch to mode GUIDED
	wait4start();

	//create local reference frame 
	initialize_local_frame();
}

void gnc_background (void) {
	static ros::Duration duration = ros::Duration(0.5);
	ros::spinOnce();
	if (is_waypoint_set) {
		if (gnc_check_waypoint_reached()) {
			MAV_Port1_ready();
			is_waypoint_set = false;
		}
	}
	duration.sleep();
}

void gnc_shutdown(void) {
	ros::shutdown();
	extern bool Escher_run_flag;
	Escher_run_flag = false;
}
