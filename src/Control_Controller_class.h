/*----------------------------------------------------------------------------
 * File:  Control_Controller_class.h
 *
 * Class:       Controller  (Controller)
 * Component:   Control
 *
 * your copyright statement can go here (from te_copyright.body)
 *--------------------------------------------------------------------------*/

#ifndef CONTROL_CONTROLLER_CLASS_H
#define CONTROL_CONTROLLER_CLASS_H

#ifdef	__cplusplus
extern	"C"	{
#endif

/*
 * Structural representation of application analysis class:
 *   Controller  (Controller)
 */
struct Control_Controller {
  Escher_StateNumber_t current_state;
  /* application analysis class attributes */
};



#define Control_Controller_MAX_EXTENT_SIZE 10
extern Escher_Extent_t pG_Control_Controller_extent;

/*
 * instance event:  Controller1:'start'
 */
typedef struct {
  EVENT_BASE_ATTRIBUTE_LIST         /* base attributes of all event classes */
  /* Note:  no supplemental data for this event */
} Control_Controllerevent1;
extern const Escher_xtUMLEventConstant_t Control_Controllerevent1c;
/*
 * instance event:  Controller2:'ready'
 */
typedef struct {
  EVENT_BASE_ATTRIBUTE_LIST         /* base attributes of all event classes */
  /* Note:  no supplemental data for this event */
} Control_Controllerevent2;
extern const Escher_xtUMLEventConstant_t Control_Controllerevent2c;
/*
 * instance event:  Controller4:'hault'
 */
typedef struct {
  EVENT_BASE_ATTRIBUTE_LIST         /* base attributes of all event classes */
  /* Note:  no supplemental data for this event */
} Control_Controllerevent4;
extern const Escher_xtUMLEventConstant_t Control_Controllerevent4c;
/*
 * instance event:  Controller5:'up'
 */
typedef struct {
  EVENT_BASE_ATTRIBUTE_LIST         /* base attributes of all event classes */
  /* Note:  no supplemental data for this event */
} Control_Controllerevent5;
extern const Escher_xtUMLEventConstant_t Control_Controllerevent5c;
/*
 * instance event:  Controller6:'down'
 */
typedef struct {
  EVENT_BASE_ATTRIBUTE_LIST         /* base attributes of all event classes */
  /* Note:  no supplemental data for this event */
} Control_Controllerevent6;
extern const Escher_xtUMLEventConstant_t Control_Controllerevent6c;
/*
 * instance event:  Controller7:'front'
 */
typedef struct {
  EVENT_BASE_ATTRIBUTE_LIST         /* base attributes of all event classes */
  /* Note:  no supplemental data for this event */
} Control_Controllerevent7;
extern const Escher_xtUMLEventConstant_t Control_Controllerevent7c;
/*
 * instance event:  Controller8:'back'
 */
typedef struct {
  EVENT_BASE_ATTRIBUTE_LIST         /* base attributes of all event classes */
  /* Note:  no supplemental data for this event */
} Control_Controllerevent8;
extern const Escher_xtUMLEventConstant_t Control_Controllerevent8c;
/*
 * instance event:  Controller9:'left'
 */
typedef struct {
  EVENT_BASE_ATTRIBUTE_LIST         /* base attributes of all event classes */
  /* Note:  no supplemental data for this event */
} Control_Controllerevent9;
extern const Escher_xtUMLEventConstant_t Control_Controllerevent9c;
/*
 * instance event:  Controller10:'right'
 */
typedef struct {
  EVENT_BASE_ATTRIBUTE_LIST         /* base attributes of all event classes */
  /* Note:  no supplemental data for this event */
} Control_Controllerevent10;
extern const Escher_xtUMLEventConstant_t Control_Controllerevent10c;
/*
 * instance event:  Controller11:'stop'
 */
typedef struct {
  EVENT_BASE_ATTRIBUTE_LIST         /* base attributes of all event classes */
  /* Note:  no supplemental data for this event */
} Control_Controllerevent11;
extern const Escher_xtUMLEventConstant_t Control_Controllerevent11c;
/*
 * union of events targeted towards 'Controller' state machine
 */
typedef union {
  Control_Controllerevent1 controller1_1;  
  Control_Controllerevent2 controller2_2;  
  Control_Controllerevent4 controller4_3;  
  Control_Controllerevent5 controller5_4;  
  Control_Controllerevent6 controller6_5;  
  Control_Controllerevent7 controller7_6;  
  Control_Controllerevent8 controller8_7;  
  Control_Controllerevent9 controller9_8;  
  Control_Controllerevent10 controller10_9;  
  Control_Controllerevent11 controller11_10;  
} Control_Controller_Events_u;
/*
 * enumeration of state model states for class
 */
#define Control_Controller_STATE_1 1  /* state [1]:  (init) */
#define Control_Controller_STATE_2 2  /* state [2]:  (takeoff) */
#define Control_Controller_STATE_3 3  /* state [3]:  (land) */
#define Control_Controller_STATE_4 4  /* state [4]:  (front) */
#define Control_Controller_STATE_9 5  /* state [9]:  (front) */
#define Control_Controller_STATE_10 6  /* state [10]:  (stop) */
#define Control_Controller_STATE_11 7  /* state [11]:  (back) */
#define Control_Controller_STATE_12 8  /* state [12]:  (back) */
#define Control_Controller_STATE_13 9  /* state [13]:  (left) */
#define Control_Controller_STATE_14 10  /* state [14]:  (left) */
#define Control_Controller_STATE_15 11  /* state [15]:  (right) */
#define Control_Controller_STATE_16 12  /* state [16]:  (right) */
#define Control_Controller_STATE_17 13  /* state [17]:  (up) */
#define Control_Controller_STATE_18 14  /* state [18]:  (down) */
/*
 * enumeration of state model event numbers
 */
#define CONTROL_CONTROLLEREVENT1NUM 0  /* Controller1:'start' */
#define CONTROL_CONTROLLEREVENT2NUM 1  /* Controller2:'ready' */
#define CONTROL_CONTROLLEREVENT4NUM 2  /* Controller4:'hault' */
#define CONTROL_CONTROLLEREVENT5NUM 3  /* Controller5:'up' */
#define CONTROL_CONTROLLEREVENT6NUM 4  /* Controller6:'down' */
#define CONTROL_CONTROLLEREVENT7NUM 5  /* Controller7:'front' */
#define CONTROL_CONTROLLEREVENT8NUM 6  /* Controller8:'back' */
#define CONTROL_CONTROLLEREVENT9NUM 7  /* Controller9:'left' */
#define CONTROL_CONTROLLEREVENT10NUM 8  /* Controller10:'right' */
#define CONTROL_CONTROLLEREVENT11NUM 9  /* Controller11:'stop' */
extern void Control_Controller_Dispatch( Escher_xtUMLEvent_t * );

#ifdef	__cplusplus
}
#endif

#endif  /* CONTROL_CONTROLLER_CLASS_H */
