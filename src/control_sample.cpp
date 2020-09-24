

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
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseWithCovariance.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <sensor_msgs/BatteryState.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 512
#define WINDOW_HEIGT 512
#define FONT_PATH "/home/ubuntu/mygit3/4/enpitpbl/PixelMplus-20130602/PixelMplus12-Regular.ttf"
#define DRONE_IMG_PATH "/home/ubuntu/mygit3/5/enpitpbl/dron.jpg"
#define MAP_IMG_PATH "/home/ubuntu/mygit3/5/enpitpbl/map.png"
struct position{
  float x;
  float y;
  float z;
};
SDL_Window * window; // ウィンドウデータを格納する構造体
SDL_Renderer * renderer; // 2Dレンダリングコンテキスト（描画設定）を格納する構造体

TTF_Font *font;
SDL_Color black = {0, 0, 0, 255};
SDL_Color red = {255, 0, 0, 255};
SDL_Color blue = {0, 0, 255, 255};
struct position current_local_pose;
struct position way_local_pose;
float batt_percent = 100;
char Command[10];

void current_local_pose_cb(const nav_msgs::Odometry::ConstPtr& pose)
{
  current_local_pose.x = pose->pose.pose.position.x;
  current_local_pose.y = pose->pose.pose.position.y;
  current_local_pose.z = pose->pose.pose.position.z+1;
}

void way_local_pose_cb(const geometry_msgs::PoseStamped::ConstPtr& pose)
{
  way_local_pose.x = pose->pose.position.x;
  way_local_pose.y = pose->pose.position.y;
  way_local_pose.z = pose->pose.position.z+1;
}

void battery_cb(const sensor_msgs::BatteryState::ConstPtr& batt){
	batt_percent = batt->percentage*100;
	
}

void command_cb(const gnc::command::ConstPtr& msg)
{
	
	ROS_INFO("recv message");
	sprintf(Command, "%s", msg->com.c_str());

	
}

// スレッド実行する関数
int HUD_func(void * args)
{
       
    
    //SDL_mutex *mtx = (SDL_mutex *)args; // 注意：引数はmtx
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Surface *drone_surf;
    SDL_Texture *drone_tex;
    SDL_Surface *map_surf;
    SDL_Texture *map_tex;
    ros::NodeHandle cp;
    ros::Subscriber current_pose_sub;
    ros::Subscriber way_pose_sub;
    ros::Subscriber power_sub;
    ros::Subscriber command_sub;
    char strings[250];
    int iw,ih;
    SDL_Rect txtRect;
    SDL_Rect pasteRect;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  
    //
    drone_surf = IMG_Load(DRONE_IMG_PATH);
    //
    map_surf = IMG_Load(MAP_IMG_PATH);
    drone_tex = SDL_CreateTextureFromSurface(renderer, drone_surf);
    map_tex = SDL_CreateTextureFromSurface(renderer, map_surf);


    while(1)
    {
      SDL_RenderClear(renderer);
      //callback functions
      current_pose_sub = cp.subscribe("mavros/global_position/local", 1000, current_local_pose_cb);
      way_pose_sub = cp.subscribe("mavros/setpoint_position/local", 1000, way_local_pose_cb);
      power_sub = cp.subscribe("mavros/battery", 1000, battery_cb);
      command_sub = cp.subscribe("gnc_node/command", 10, command_cb);
      sprintf(strings, "current x:%fm y:%fm z:%fm", current_local_pose.x, current_local_pose.y, current_local_pose.z);
      surface = TTF_RenderUTF8_Blended(font, strings, black);
      texture = SDL_CreateTextureFromSurface(renderer, surface);
  
      SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);
      txtRect=(SDL_Rect){0,0,iw,ih};
      pasteRect=(SDL_Rect){0,0,iw/2,ih/2};
      SDL_RenderCopy(renderer, texture, &txtRect, &pasteRect);
      SDL_FreeSurface(surface);
      SDL_DestroyTexture(texture);      
      //EXECUTE COMMAND
      if(strcmp("land", Command) == 0){
        sprintf(strings, "land!!!!!!!");
      }else {
        sprintf(strings, "way     x:%fm y:%fm z:%fm", way_local_pose.x, way_local_pose.y, way_local_pose.z);
      }
      
      surface = TTF_RenderUTF8_Blended(font, strings, black);
      texture = SDL_CreateTextureFromSurface(renderer, surface);
  
      SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);
      txtRect=(SDL_Rect){0,0,iw,ih};
      pasteRect=(SDL_Rect){0,ih/2,iw/2,ih/2};
      SDL_RenderCopy(renderer, texture, &txtRect, &pasteRect);
      SDL_FreeSurface(surface);
      SDL_DestroyTexture(texture);      
      
      
      if(batt_percent < 40){
        sprintf(strings, "battery %f %% battery warning", batt_percent);
        surface = TTF_RenderUTF8_Blended(font, strings, red);
      }else{
        sprintf(strings, "battery %f %%", batt_percent);
        surface = TTF_RenderUTF8_Blended(font, strings, black);
      }
      texture = SDL_CreateTextureFromSurface(renderer, surface);
  
      SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);
      txtRect=(SDL_Rect){0,0,iw,ih};
      pasteRect=(SDL_Rect){0,ih,iw/2,ih/2};
      SDL_RenderCopy(renderer, texture, &txtRect, &pasteRect);
      SDL_FreeSurface(surface);
      SDL_DestroyTexture(texture);   
      
      // sprintf(strings, "0,0");
      // surface = TTF_RenderUTF8_Blended(font, strings, black);
      // texture = SDL_CreateTextureFromSurface(renderer, surface);
      SDL_QueryTexture(map_tex, NULL, NULL, &iw, &ih);
      txtRect=(SDL_Rect){0,0,iw,ih};
      pasteRect=(SDL_Rect){
        WINDOW_WIDTH/2-iw/6,
        WINDOW_HEIGT*3/4 - ih*2/9,
        iw/3,
        ih/3
        };
      SDL_RenderCopy(renderer, map_tex, &txtRect, &pasteRect);
      // SDL_FreeSurface(surface);
      // SDL_DestroyTexture(texture);   

      // sprintf(strings, "C");
      // surface = TTF_RenderUTF8_Blended(font, strings, black);
      // texture = SDL_CreateTextureFromSurface(renderer, surface);
  
      SDL_QueryTexture(drone_tex, NULL, NULL, &iw, &ih);
      txtRect=(SDL_Rect){0,0,iw,ih};
      pasteRect=(SDL_Rect){
        WINDOW_WIDTH/2+(int)current_local_pose.x*22/3 - iw/20,
        WINDOW_HEIGT*35/40-(int)current_local_pose.y*8 - iw/20,
        iw/10,ih/10};
      SDL_RenderCopy(renderer, drone_tex, &txtRect, &pasteRect);
      // SDL_FreeSurface(surface);
      // SDL_DestroyTexture(texture);   
      
      sprintf(strings, "w");
      surface = TTF_RenderUTF8_Blended(font, strings, blue);
      texture = SDL_CreateTextureFromSurface(renderer, surface);
  
      SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);
      txtRect=(SDL_Rect){0,0,iw,ih};
      pasteRect=(SDL_Rect){
        WINDOW_WIDTH/2+(int)way_local_pose.x*22/3 - iw/4,
        WINDOW_HEIGT*35/40-(int)way_local_pose.y*8 - iw/4,
        iw/2,ih/2};
      SDL_RenderCopy(renderer, texture, &txtRect, &pasteRect);
      SDL_FreeSurface(surface);
      SDL_DestroyTexture(texture);   

      SDL_RenderPresent(renderer);
      ros::spinOnce();
      
      SDL_Delay(10);


      //SDL_UnlockMutex(mtx); // Mutexをアンロックし、他のスレッドが共有変数にアクセスできるようにする
            
    }
    return 0;
}

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, "ctrls");
  /**SDL INIT BEGIN**/
  SDL_Thread* HUD_thread; //HUD_threadを用いる
  SDL_mutex *mtx = SDL_CreateMutex(); // 相互排除（Mutex）を用いる
  SDL_Init(SDL_INIT_EVERYTHING);
  int flags=IMG_INIT_JPG|IMG_INIT_PNG;
  IMG_Init(flags);
  window = SDL_CreateWindow(
    "HUD", 
    0, 
    0, 
    512, 
    512, 
    0
    );
  renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // 生成したRCに描画色として青を設定
  SDL_RenderClear(renderer); // 設定色でRCをクリア
  SDL_RenderPresent(renderer); // 描画データを表示
  //Initialize TTF
  TTF_Init();
  font = TTF_OpenFont(FONT_PATH, 40);
  
  HUD_thread = SDL_CreateThread(HUD_func, "HUD_thread", mtx); // HUD_threadを作成し、スレッド関数wii_funcを実行（引数mtx）
   
  /**SDL INIT END**/

// %Tag(INIT)%
  
// %EndTag(INIT)%

  
// %Tag(NODEHANDLE)%
  
  ros::NodeHandle c;
  
// %EndTag(NODEHANDLE)%

  
// %Tag(PUBLISHER)%
  ros::Publisher command_pub = c.advertise<gnc::command>("gnc_node/command", 1000);
// %EndTag(PUBLISHER)%

// %Tag(LOOP_RATE)%
  ros::Rate loop_rate(10);
// %EndTag(LOOP_RATE)%

 
// %Tag(ROS_OK)%
  int count = 0;
  int stop_flag = 1;
  int loop = 1;
  while (ros::ok() && loop)
  {
    
   
    // %Tag(FILL_MESSAGE)%
    gnc::command command;
    //std::stringstream ss;
    char str[10];	
    char cmd[2];		
    char chDist[10];
    double dDist = 0;		

    printf("Chose command.\nq w e * * * u i * *\n a s d * * h * k l\n  z x c * * * *\n");
    printf("And Setting distance!!\nK Kill this node\n");
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
          
          break;
        case 'd': 
          command.com = "right";
          command.x = dDist;
          
          break;
        case 'c':
          command.com = "rback"; 
          command.x = dDist/sqrt(2);
          command.y = -dDist/sqrt(2);
       
          break;
        case 'x':
          command.com = "back";
          command.y = -dDist;
      
          break;
        case 'z':
          command.com = "lback";
          command.x = -dDist/sqrt(2);
          command.y = -dDist/sqrt(2);
     
          break;
        case 'a':
          command.com = "left"; 
          command.x = -dDist;
          break;
        case 'q':
          command.com = "lfront";
          
          command.x = -dDist/sqrt(2);
          command.y = dDist/sqrt(2);
           
          break;
        case 's':
          command.com = "stop"; 
          
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
        case 'k':
          loop = 0;
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
    command_pub.publish(command);
// %EndTag(PUBLISH)%

// %Tag(SPINONCE)%
    ros::spinOnce();
// %EndTag(SPINONCE)%

// %Tag(RATE_SLEEP)%
    loop_rate.sleep();
// %EndTag(RATE_SLEEP)%
   ++count;
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  TTF_CloseFont(font);
  TTF_Quit();

  return 0;
}
// %EndTag(FULLTEXT)%

