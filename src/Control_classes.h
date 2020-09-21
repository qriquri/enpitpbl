/*----------------------------------------------------------------------------
 * File:  Control_classes.h
 *
 * This file defines the object type identification numbers for all classes
 * in the component:  Control
 *
 * your copyright statement can go here (from te_copyright.body)
 *--------------------------------------------------------------------------*/

#ifndef CONTROL_CLASSES_H
#define CONTROL_CLASSES_H

#ifdef	__cplusplus
extern	"C"	{
#endif

/*
 * Initialization services for component:  Control
 */
extern Escher_Extent_t * const Control_class_info[];
extern const EventTaker_t Control_EventDispatcher[];
void Control_execute_initialization( void );

#define Control_STATE_MODELS 1
/* Define constants to map to class numbers.  */
#define Control_Controller_CLASS_NUMBER 0
#define Control_MAX_CLASS_NUMBERS 1

/* Provide a map of classes to task numbers.  */
#define Control_TASK_NUMBERS  0

#define Control_class_dispatchers\
  Control_Controller_Dispatch

/* Provide definitions of the shapes of the class structures.  */

typedef struct Control_Controller Control_Controller;

/* union of class declarations so we may derive largest class size */
#define Control_CLASS_U \
  char Control_dummy;\

/*
 * UML Domain Functions (Synchronous Services)
 */
void Control_back( void );
void Control_down( void );
void Control_front( void );
void Control_hault( void );
void Control_left( void );
void Control_right( void );
void Control_setup( void );
void Control_stop( void );
void Control_up( void );

#include "Control.h"
#include "Control_Controller_class.h"
/*
 * roll-up of all events (with their parameters) for component Control
 */
typedef union {
  Control_Controller_Events_u Control_Controller_Events_u_namespace;
} Control_DomainEvents_u;

#ifdef	__cplusplus
}
#endif
#endif  /* CONTROL_CLASSES_H */
