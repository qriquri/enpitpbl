/*----------------------------------------------------------------------------
 * File:  Control_Controller_class.c
 *
 * Class:       Controller  (Controller)
 * Component:   Control
 *
 * your copyright statement can go here (from te_copyright.body)
 *--------------------------------------------------------------------------*/

#include "gnc_sys_types.h"
#include "Control_classes.h"


/*
 * Statically allocate space for the instance population for this class.
 * Allocate space for the class instance and its attribute values.
 * Depending upon the collection scheme, allocate containoids (collection
 * nodes) for gathering instances into free and active extents.
 */
static Escher_SetElement_s Control_Controller_container[ Control_Controller_MAX_EXTENT_SIZE ];
static Control_Controller Control_Controller_instances[ Control_Controller_MAX_EXTENT_SIZE ];
Escher_Extent_t pG_Control_Controller_extent = {
  {0}, {0}, &Control_Controller_container[ 0 ],
  (Escher_iHandle_t) &Control_Controller_instances,
  sizeof( Control_Controller ), Control_Controller_STATE_1, Control_Controller_MAX_EXTENT_SIZE
  };
/*----------------------------------------------------------------------------
 * State and transition action implementations for the following class:
 *
 * Class:      Controller  (Controller)
 * Component:  Control
 *--------------------------------------------------------------------------*/

/*
 * State 1:  [init]
 */
static void Control_Controller_act1( Control_Controller *, const Escher_xtUMLEvent_t * const );
static void
Control_Controller_act1( Control_Controller * self, const Escher_xtUMLEvent_t * const event )
{
}

/*
 * State 2:  [takeoff]
 */
static void Control_Controller_act2( Control_Controller *, const Escher_xtUMLEvent_t * const );
static void
Control_Controller_act2( Control_Controller * self, const Escher_xtUMLEvent_t * const event )
{
  /* Port1::takeoff(alt:4) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::takeoff(alt:4)" );
  Control_Port1_takeoff( 4 );
  /* Port1::set_heading(heading:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_heading(heading:0)" );
  Control_Port1_set_heading( 0 );
}

/*
 * State 3:  [land]
 */
static void Control_Controller_act3( Control_Controller *, const Escher_xtUMLEvent_t * const );
static void
Control_Controller_act3( Control_Controller * self, const Escher_xtUMLEvent_t * const event )
{
  /* Port1::land() */
  XTUML_OAL_STMT_TRACE( 1, "Port1::land()" );
  Control_Port1_land();
  /* Port1::set_heading(heading:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_heading(heading:0)" );
  Control_Port1_set_heading( 0 );
}

/*
 * State 4:  [front]
 */
static void Control_Controller_act4( Control_Controller *, const Escher_xtUMLEvent_t * const );
static void
Control_Controller_act4( Control_Controller * self, const Escher_xtUMLEvent_t * const event )
{
  /* Port1::set_destination(x:0, y:3, z:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_destination(x:0, y:3, z:0)" );
  Control_Port1_set_destination( 0, 3, 0 );
  /* Port1::set_heading(heading:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_heading(heading:0)" );
  Control_Port1_set_heading( 0 );
}

/*
 * State 9:  [front]
 */
static void Control_Controller_act9( Control_Controller *, const Escher_xtUMLEvent_t * const );
static void
Control_Controller_act9( Control_Controller * self, const Escher_xtUMLEvent_t * const event )
{
  /* Port1::set_destination(x:0, y:3, z:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_destination(x:0, y:3, z:0)" );
  Control_Port1_set_destination( 0, 3, 0 );
  /* Port1::set_heading(heading:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_heading(heading:0)" );
  Control_Port1_set_heading( 0 );
}

/*
 * State 10:  [stop]
 */
static void Control_Controller_act10( Control_Controller *, const Escher_xtUMLEvent_t * const );
static void
Control_Controller_act10( Control_Controller * self, const Escher_xtUMLEvent_t * const event )
{
  /* Port1::set_destination(x:0, y:0, z:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_destination(x:0, y:0, z:0)" );
  Control_Port1_set_destination( 0, 0, 0 );
  /* Port1::set_heading(heading:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_heading(heading:0)" );
  Control_Port1_set_heading( 0 );
}

/*
 * State 11:  [back]
 */
static void Control_Controller_act11( Control_Controller *, const Escher_xtUMLEvent_t * const );
static void
Control_Controller_act11( Control_Controller * self, const Escher_xtUMLEvent_t * const event )
{
  /* Port1::set_destination(x:0, y:- 3, z:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_destination(x:0, y:- 3, z:0)" );
  Control_Port1_set_destination( 0, -3, 0 );
  /* Port1::set_heading(heading:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_heading(heading:0)" );
  Control_Port1_set_heading( 0 );
}

/*
 * State 12:  [back]
 */
static void Control_Controller_act12( Control_Controller *, const Escher_xtUMLEvent_t * const );
static void
Control_Controller_act12( Control_Controller * self, const Escher_xtUMLEvent_t * const event )
{
  /* Port1::set_destination(x:0, y:- 3, z:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_destination(x:0, y:- 3, z:0)" );
  Control_Port1_set_destination( 0, -3, 0 );
  /* Port1::set_heading(heading:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_heading(heading:0)" );
  Control_Port1_set_heading( 0 );
}

/*
 * State 13:  [left]
 */
static void Control_Controller_act13( Control_Controller *, const Escher_xtUMLEvent_t * const );
static void
Control_Controller_act13( Control_Controller * self, const Escher_xtUMLEvent_t * const event )
{
  /* Port1::set_destination(x:- 3, y:0, z:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_destination(x:- 3, y:0, z:0)" );
  Control_Port1_set_destination( -3, 0, 0 );
  /* Port1::set_heading(heading:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_heading(heading:0)" );
  Control_Port1_set_heading( 0 );
}

/*
 * State 14:  [left]
 */
static void Control_Controller_act14( Control_Controller *, const Escher_xtUMLEvent_t * const );
static void
Control_Controller_act14( Control_Controller * self, const Escher_xtUMLEvent_t * const event )
{
  /* Port1::set_destination(x:- 3, y:0, z:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_destination(x:- 3, y:0, z:0)" );
  Control_Port1_set_destination( -3, 0, 0 );
  /* Port1::set_heading(heading:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_heading(heading:0)" );
  Control_Port1_set_heading( 0 );
}

/*
 * State 15:  [right]
 */
static void Control_Controller_act15( Control_Controller *, const Escher_xtUMLEvent_t * const );
static void
Control_Controller_act15( Control_Controller * self, const Escher_xtUMLEvent_t * const event )
{
  /* Port1::set_destination(x:3, y:0, z:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_destination(x:3, y:0, z:0)" );
  Control_Port1_set_destination( 3, 0, 0 );
  /* Port1::set_heading(heading:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_heading(heading:0)" );
  Control_Port1_set_heading( 0 );
}

/*
 * State 16:  [right]
 */
static void Control_Controller_act16( Control_Controller *, const Escher_xtUMLEvent_t * const );
static void
Control_Controller_act16( Control_Controller * self, const Escher_xtUMLEvent_t * const event )
{
  /* Port1::set_destination(x:3, y:0, z:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_destination(x:3, y:0, z:0)" );
  Control_Port1_set_destination( 3, 0, 0 );
  /* Port1::set_heading(heading:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_heading(heading:0)" );
  Control_Port1_set_heading( 0 );
}

/*
 * State 17:  [up]
 */
static void Control_Controller_act17( Control_Controller *, const Escher_xtUMLEvent_t * const );
static void
Control_Controller_act17( Control_Controller * self, const Escher_xtUMLEvent_t * const event )
{
  /* Port1::set_destination(x:0, y:0, z:0.5) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_destination(x:0, y:0, z:0.5)" );
  Control_Port1_set_destination( 0, 0, 0.5 );
  /* Port1::set_heading(heading:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_heading(heading:0)" );
  Control_Port1_set_heading( 0 );
}

/*
 * State 18:  [down]
 */
static void Control_Controller_act18( Control_Controller *, const Escher_xtUMLEvent_t * const );
static void
Control_Controller_act18( Control_Controller * self, const Escher_xtUMLEvent_t * const event )
{
  /* Port1::set_destination(x:0, y:0, z:- 0.5) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_destination(x:0, y:0, z:- 0.5)" );
  Control_Port1_set_destination( 0, 0, -0.5 );
  /* Port1::set_heading(heading:0) */
  XTUML_OAL_STMT_TRACE( 1, "Port1::set_heading(heading:0)" );
  Control_Port1_set_heading( 0 );
}

const Escher_xtUMLEventConstant_t Control_Controllerevent1c = {
  Control_DOMAIN_ID, Control_Controller_CLASS_NUMBER, CONTROL_CONTROLLEREVENT1NUM,
  ESCHER_IS_INSTANCE_EVENT };
const Escher_xtUMLEventConstant_t Control_Controllerevent2c = {
  Control_DOMAIN_ID, Control_Controller_CLASS_NUMBER, CONTROL_CONTROLLEREVENT2NUM,
  ESCHER_IS_INSTANCE_EVENT };
const Escher_xtUMLEventConstant_t Control_Controllerevent4c = {
  Control_DOMAIN_ID, Control_Controller_CLASS_NUMBER, CONTROL_CONTROLLEREVENT4NUM,
  ESCHER_IS_INSTANCE_EVENT };
const Escher_xtUMLEventConstant_t Control_Controllerevent5c = {
  Control_DOMAIN_ID, Control_Controller_CLASS_NUMBER, CONTROL_CONTROLLEREVENT5NUM,
  ESCHER_IS_INSTANCE_EVENT };
const Escher_xtUMLEventConstant_t Control_Controllerevent6c = {
  Control_DOMAIN_ID, Control_Controller_CLASS_NUMBER, CONTROL_CONTROLLEREVENT6NUM,
  ESCHER_IS_INSTANCE_EVENT };
const Escher_xtUMLEventConstant_t Control_Controllerevent7c = {
  Control_DOMAIN_ID, Control_Controller_CLASS_NUMBER, CONTROL_CONTROLLEREVENT7NUM,
  ESCHER_IS_INSTANCE_EVENT };
const Escher_xtUMLEventConstant_t Control_Controllerevent8c = {
  Control_DOMAIN_ID, Control_Controller_CLASS_NUMBER, CONTROL_CONTROLLEREVENT8NUM,
  ESCHER_IS_INSTANCE_EVENT };
const Escher_xtUMLEventConstant_t Control_Controllerevent9c = {
  Control_DOMAIN_ID, Control_Controller_CLASS_NUMBER, CONTROL_CONTROLLEREVENT9NUM,
  ESCHER_IS_INSTANCE_EVENT };
const Escher_xtUMLEventConstant_t Control_Controllerevent10c = {
  Control_DOMAIN_ID, Control_Controller_CLASS_NUMBER, CONTROL_CONTROLLEREVENT10NUM,
  ESCHER_IS_INSTANCE_EVENT };
const Escher_xtUMLEventConstant_t Control_Controllerevent11c = {
  Control_DOMAIN_ID, Control_Controller_CLASS_NUMBER, CONTROL_CONTROLLEREVENT11NUM,
  ESCHER_IS_INSTANCE_EVENT };


/*
 * State-Event Matrix (SEM)
 * Row index is object (MC enumerated) current state.
 * Row zero is the uninitialized state (e.g., for creation event transitions).
 * Column index is (MC enumerated) state machine events.
 */
static const Escher_SEMcell_t Control_Controller_StateEventMatrix[ 14 + 1 ][ 10 ] = {
  /* row 0:  uninitialized state (for creation events) */
  { EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN },
  /* row 1:  Control_Controller_STATE_1 (init) */
  { Control_Controller_STATE_2, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN },
  /* row 2:  Control_Controller_STATE_2 (takeoff) */
  { EVENT_CANT_HAPPEN, Control_Controller_STATE_10, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN },
  /* row 3:  Control_Controller_STATE_3 (land) */
  { EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN },
  /* row 4:  Control_Controller_STATE_4 (front) */
  { EVENT_CANT_HAPPEN, Control_Controller_STATE_9, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, Control_Controller_STATE_10 },
  /* row 5:  Control_Controller_STATE_9 (front) */
  { EVENT_CANT_HAPPEN, Control_Controller_STATE_4, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, Control_Controller_STATE_10 },
  /* row 6:  Control_Controller_STATE_10 (stop) */
  { EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, Control_Controller_STATE_3, Control_Controller_STATE_17, Control_Controller_STATE_18, Control_Controller_STATE_4, Control_Controller_STATE_11, Control_Controller_STATE_13, Control_Controller_STATE_15, EVENT_CANT_HAPPEN },
  /* row 7:  Control_Controller_STATE_11 (back) */
  { EVENT_CANT_HAPPEN, Control_Controller_STATE_12, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, Control_Controller_STATE_10 },
  /* row 8:  Control_Controller_STATE_12 (back) */
  { EVENT_CANT_HAPPEN, Control_Controller_STATE_11, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, Control_Controller_STATE_10 },
  /* row 9:  Control_Controller_STATE_13 (left) */
  { EVENT_CANT_HAPPEN, Control_Controller_STATE_14, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, Control_Controller_STATE_10 },
  /* row 10:  Control_Controller_STATE_14 (left) */
  { EVENT_CANT_HAPPEN, Control_Controller_STATE_13, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, Control_Controller_STATE_10 },
  /* row 11:  Control_Controller_STATE_15 (right) */
  { EVENT_CANT_HAPPEN, Control_Controller_STATE_16, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, Control_Controller_STATE_10 },
  /* row 12:  Control_Controller_STATE_16 (right) */
  { EVENT_CANT_HAPPEN, Control_Controller_STATE_15, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, Control_Controller_STATE_10 },
  /* row 13:  Control_Controller_STATE_17 (up) */
  { EVENT_CANT_HAPPEN, Control_Controller_STATE_10, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, Control_Controller_STATE_10 },
  /* row 14:  Control_Controller_STATE_18 (down) */
  { EVENT_CANT_HAPPEN, Control_Controller_STATE_10, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, EVENT_CANT_HAPPEN, Control_Controller_STATE_10 }
};

  /*
   * Array of pointers to the class state action procedures.
   * Index is the (MC enumerated) number of the state action to execute.
   */
  static const StateAction_t Control_Controller_acts[ 15 ] = {
    (StateAction_t) 0,
    (StateAction_t) Control_Controller_act1,  /* init */
    (StateAction_t) Control_Controller_act2,  /* takeoff */
    (StateAction_t) Control_Controller_act3,  /* land */
    (StateAction_t) Control_Controller_act4,  /* front */
    (StateAction_t) Control_Controller_act9,  /* front */
    (StateAction_t) Control_Controller_act10,  /* stop */
    (StateAction_t) Control_Controller_act11,  /* back */
    (StateAction_t) Control_Controller_act12,  /* back */
    (StateAction_t) Control_Controller_act13,  /* left */
    (StateAction_t) Control_Controller_act14,  /* left */
    (StateAction_t) Control_Controller_act15,  /* right */
    (StateAction_t) Control_Controller_act16,  /* right */
    (StateAction_t) Control_Controller_act17,  /* up */
    (StateAction_t) Control_Controller_act18  /* down */
  };

  /*
   * Array of string names of the state machine names.
   * Index is the (MC enumerated) number of the state.
   */
  static const c_t * const state_name_strings[ 15 ] = {
    "",
    "init",
    "takeoff",
    "land",
    "front",
    "front",
    "stop",
    "back",
    "back",
    "left",
    "left",
    "right",
    "right",
    "up",
    "down"
  };

/*
 * instance state machine event dispatching
 */
void
Control_Controller_Dispatch( Escher_xtUMLEvent_t * event )
{
  Escher_iHandle_t instance = GetEventTargetInstance( event );
  Escher_EventNumber_t event_number = GetOoaEventNumber( event );
  Escher_StateNumber_t current_state;
  Escher_StateNumber_t next_state;
  if ( 0 != instance ) {
    current_state = instance->current_state;
    if ( current_state > 14 ) {
      /* instance validation failure (object deleted while event in flight) */
      UserEventNoInstanceCallout( event_number );
    } else {
      next_state = Control_Controller_StateEventMatrix[ current_state ][ event_number ];
      if ( next_state <= 14 ) {
        STATE_TXN_START_TRACE( "Controller", current_state, state_name_strings[ current_state ] );
        /* Update the current state and execute the state action.  */
        instance->current_state = next_state;
        ( *Control_Controller_acts[ next_state ] )( instance, event );
        STATE_TXN_END_TRACE( "Controller", next_state, state_name_strings[ next_state ] );
      } else if ( next_state == EVENT_CANT_HAPPEN ) {
          /* event cant happen */
          UserEventCantHappenCallout( current_state, next_state, event_number );
          STATE_TXN_CH_TRACE( "Controller", current_state );
      } else {
        /* empty else */
      }
    }
  }
}

