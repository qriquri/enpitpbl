/*----------------------------------------------------------------------------
 * File:  Control.c
 *
 * UML Component Port Messages
 * Component/Module Name:  Control
 *
 * your copyright statement can go here (from te_copyright.body)
 *--------------------------------------------------------------------------*/

#include "gnc_sys_types.h"
#include "Control.h"
#include "MAV.h"
#include "Control_classes.h"

/*
 * Interface:  mavcontrol
 * Required Port:  Port1
 * To Provider Message:  arm
 */
void
Control_Port1_arm()
{
  MAV_Port1_arm();
}

/*
 * Interface:  mavcontrol
 * Required Port:  Port1
 * To Provider Message:  get_heading
 */
r_t
Control_Port1_get_heading()
{
return   MAV_Port1_get_heading();
}

/*
 * Interface:  mavcontrol
 * Required Port:  Port1
 * To Provider Message:  init
 */
void
Control_Port1_init()
{
  MAV_Port1_init();
}

/*
 * Interface:  mavcontrol
 * Required Port:  Port1
 * To Provider Message:  land
 */
void
Control_Port1_land()
{
  MAV_Port1_land();
}

/*
 * Interface:  mavcontrol
 * Required Port:  Port1
 * From Provider Message:  ready
 */
void
Control_Port1_ready()
{
  Control_Controller * ctrl=0;
  /* SELECT any ctrl FROM INSTANCES OF Controller */
  XTUML_OAL_STMT_TRACE( 1, "SELECT any ctrl FROM INSTANCES OF Controller" );
  ctrl = (Control_Controller *) Escher_SetGetAny( &pG_Control_Controller_extent.active );
  /* GENERATE Controller2:ready() TO ctrl */
  XTUML_OAL_STMT_TRACE( 1, "GENERATE Controller2:ready() TO ctrl" );
  { Escher_xtUMLEvent_t * e = Escher_NewxtUMLEvent( ctrl, &Control_Controllerevent2c );
    Escher_SendEvent( e );
  }
}

/*
 * Interface:  mavcontrol
 * Required Port:  Port1
 * To Provider Message:  set_destination
 */
void
Control_Port1_set_destination( const r_t p_x, const r_t p_y, const r_t p_z )
{
  MAV_Port1_set_destination(  p_x, p_y, p_z );
}

/*
 * Interface:  mavcontrol
 * Required Port:  Port1
 * To Provider Message:  set_heading
 */
void
Control_Port1_set_heading( const r_t p_heading )
{
  MAV_Port1_set_heading(  p_heading );
}

/*
 * Interface:  mavcontrol
 * Required Port:  Port1
 * To Provider Message:  takeoff
 */
void
Control_Port1_takeoff( const r_t p_alt )
{
  MAV_Port1_takeoff(  p_alt );
}
/*
 * UML Domain Functions (Synchronous Services)
 */

/*
 * Domain Function:  back
 */
void
Control_back()
{
  Control_Controller * ctrl=0;
  /* SELECT any ctrl FROM INSTANCES OF Controller */
  XTUML_OAL_STMT_TRACE( 1, "SELECT any ctrl FROM INSTANCES OF Controller" );
  ctrl = (Control_Controller *) Escher_SetGetAny( &pG_Control_Controller_extent.active );
  /* GENERATE Controller8:back() TO ctrl */
  XTUML_OAL_STMT_TRACE( 1, "GENERATE Controller8:back() TO ctrl" );
  { Escher_xtUMLEvent_t * e = Escher_NewxtUMLEvent( ctrl, &Control_Controllerevent8c );
    Escher_SendEvent( e );
  }
}

/*
 * Domain Function:  down
 */
void
Control_down()
{
  Control_Controller * ctrl=0;
  /* SELECT any ctrl FROM INSTANCES OF Controller */
  XTUML_OAL_STMT_TRACE( 1, "SELECT any ctrl FROM INSTANCES OF Controller" );
  ctrl = (Control_Controller *) Escher_SetGetAny( &pG_Control_Controller_extent.active );
  /* GENERATE Controller6:down() TO ctrl */
  XTUML_OAL_STMT_TRACE( 1, "GENERATE Controller6:down() TO ctrl" );
  { Escher_xtUMLEvent_t * e = Escher_NewxtUMLEvent( ctrl, &Control_Controllerevent6c );
    Escher_SendEvent( e );
  }
}

/*
 * Domain Function:  front
 */
void
Control_front()
{
  Control_Controller * ctrl=0;
  /* SELECT any ctrl FROM INSTANCES OF Controller */
  XTUML_OAL_STMT_TRACE( 1, "SELECT any ctrl FROM INSTANCES OF Controller" );
  ctrl = (Control_Controller *) Escher_SetGetAny( &pG_Control_Controller_extent.active );
  /* GENERATE Controller7:front() TO ctrl */
  XTUML_OAL_STMT_TRACE( 1, "GENERATE Controller7:front() TO ctrl" );
  { Escher_xtUMLEvent_t * e = Escher_NewxtUMLEvent( ctrl, &Control_Controllerevent7c );
    Escher_SendEvent( e );
  }
}

/*
 * Domain Function:  hault
 */
void
Control_hault()
{
  Control_Controller * ctrl=0;
  /* SELECT any ctrl FROM INSTANCES OF Controller */
  XTUML_OAL_STMT_TRACE( 1, "SELECT any ctrl FROM INSTANCES OF Controller" );
  ctrl = (Control_Controller *) Escher_SetGetAny( &pG_Control_Controller_extent.active );
  /* GENERATE Controller4:hault() TO ctrl */
  XTUML_OAL_STMT_TRACE( 1, "GENERATE Controller4:hault() TO ctrl" );
  { Escher_xtUMLEvent_t * e = Escher_NewxtUMLEvent( ctrl, &Control_Controllerevent4c );
    Escher_SendEvent( e );
  }
}

/*
 * Domain Function:  left
 */
void
Control_left()
{
  Control_Controller * ctrl=0;
  /* SELECT any ctrl FROM INSTANCES OF Controller */
  XTUML_OAL_STMT_TRACE( 1, "SELECT any ctrl FROM INSTANCES OF Controller" );
  ctrl = (Control_Controller *) Escher_SetGetAny( &pG_Control_Controller_extent.active );
  /* GENERATE Controller9:left() TO ctrl */
  XTUML_OAL_STMT_TRACE( 1, "GENERATE Controller9:left() TO ctrl" );
  { Escher_xtUMLEvent_t * e = Escher_NewxtUMLEvent( ctrl, &Control_Controllerevent9c );
    Escher_SendEvent( e );
  }
}

/*
 * Domain Function:  right
 */
void
Control_right()
{
  Control_Controller * ctrl=0;
  /* SELECT any ctrl FROM INSTANCES OF Controller */
  XTUML_OAL_STMT_TRACE( 1, "SELECT any ctrl FROM INSTANCES OF Controller" );
  ctrl = (Control_Controller *) Escher_SetGetAny( &pG_Control_Controller_extent.active );
  /* GENERATE Controller10:right() TO ctrl */
  XTUML_OAL_STMT_TRACE( 1, "GENERATE Controller10:right() TO ctrl" );
  { Escher_xtUMLEvent_t * e = Escher_NewxtUMLEvent( ctrl, &Control_Controllerevent10c );
    Escher_SendEvent( e );
  }
}

/*
 * Domain Function:  setup
 */
void
Control_setup()
{
  Control_Controller * ctrl;
  /* CREATE OBJECT INSTANCE ctrl OF Controller */
  XTUML_OAL_STMT_TRACE( 1, "CREATE OBJECT INSTANCE ctrl OF Controller" );
  ctrl = (Control_Controller *) Escher_CreateInstance( Control_DOMAIN_ID, Control_Controller_CLASS_NUMBER );
  /* GENERATE Controller1:start() TO ctrl */
  XTUML_OAL_STMT_TRACE( 1, "GENERATE Controller1:start() TO ctrl" );
  { Escher_xtUMLEvent_t * e = Escher_NewxtUMLEvent( ctrl, &Control_Controllerevent1c );
    Escher_SendEvent( e );
  }
}

/*
 * Domain Function:  stop
 */
void
Control_stop()
{
  Control_Controller * ctrl=0;
  /* SELECT any ctrl FROM INSTANCES OF Controller */
  XTUML_OAL_STMT_TRACE( 1, "SELECT any ctrl FROM INSTANCES OF Controller" );
  ctrl = (Control_Controller *) Escher_SetGetAny( &pG_Control_Controller_extent.active );
  /* GENERATE Controller11:stop() TO ctrl */
  XTUML_OAL_STMT_TRACE( 1, "GENERATE Controller11:stop() TO ctrl" );
  { Escher_xtUMLEvent_t * e = Escher_NewxtUMLEvent( ctrl, &Control_Controllerevent11c );
    Escher_SendEvent( e );
  }
}

/*
 * Domain Function:  up
 */
void
Control_up()
{
  Control_Controller * ctrl=0;
  /* SELECT any ctrl FROM INSTANCES OF Controller */
  XTUML_OAL_STMT_TRACE( 1, "SELECT any ctrl FROM INSTANCES OF Controller" );
  ctrl = (Control_Controller *) Escher_SetGetAny( &pG_Control_Controller_extent.active );
  /* GENERATE Controller5:up() TO ctrl */
  XTUML_OAL_STMT_TRACE( 1, "GENERATE Controller5:up() TO ctrl" );
  { Escher_xtUMLEvent_t * e = Escher_NewxtUMLEvent( ctrl, &Control_Controllerevent5c );
    Escher_SendEvent( e );
  }
}
/* xtUML class info (collections, sizes, etc.) */
Escher_Extent_t * const Control_class_info[ Control_MAX_CLASS_NUMBERS ] = {
  &pG_Control_Controller_extent
};

/*
 * Array of pointers to the class event dispatcher method.
 * Index is the (model compiler enumerated) number of the state model.
 */
const EventTaker_t Control_EventDispatcher[ Control_STATE_MODELS ] = {
  Control_class_dispatchers
};

void Control_execute_initialization()
{
  /*
   * Initialization Function:  setup
   * Component:  Control
   */
  Control_setup();

}
