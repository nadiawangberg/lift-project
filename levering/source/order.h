#ifndef __INCLUDE_ORDER_H__
#define __INCLUDE_ORDER_H__
#include "floor.h"
#include "FSM.h"
#include "elev.h"
#include <stdio.h>

/**
* @file
*  @brief Order module, stores the orders in two lists, checks for new orders, adds, removes and manages the orders by modifying these lists.
*/



/**
   Which order button type we have. Can be @c DOWN (outside lift down button), @c COMMAND (inside lift any button) or @c UP (outside lift up button).
*/
typedef enum tag_order_type { 
    DOWN = -1,
    COMMAND,
    UP
} order_type_t;


static int order_up_m[4]={0,0,0,0};
static int order_down_m[4]={0,0,0,0};

/**
  Prints our current pending orders.
*/
void print_order();

/**
  Add an order to one/both of the @p order lists
  @param order_type Which order button type we have. Can be @c DOWN (outside lift down button), @c COMMAND (inside lift any button) or @c UP (outside lift up button).
  @param floor Which floor the lift is ordered to go to. Must be 0-3.
*/
void addOrder_order(Floor floor, order_type_t order_type);

/**
  Removes all order in inputed floor, and turns off corresponding order button lights
  @param floor Which floor to remove order in. Must be 0-3.
*/
void removeOrders_order(Floor floor);
 //removes all orders in the right direction in the current floor

/**
  Checks for incoming orders and adds them to lists (by calling addOrder function)
*/
void checkForOrders_order(); 


/**
  Selects which direction the elevator should move.
  @return a @p elev_motor_direction_t which can be @c DIRN_DOWN, @c DIRN_STOP or @c DIRN_UP.
*/
elev_motor_direction_t selectDir_order(float inbetween_floor, elev_motor_direction_t current_direction);


/**
  Removes all orders. 
*/
void removeAllOrders_order();

/**
  @param floor Which floor to check for orders
  @return 1 if there is an order i floor, 0 if there are none.
*/
int isOrderInFloor_order(Floor floor);

/**
  @param floor The floor the lift should consider stopping in.
  @param motor_dir The direction the lift is currently moving in.
  @return 1 if the lift should stop, 0 if the lift shouldnt stop. 
*/
int shouldLiftStop_order(Floor floor,elev_motor_direction_t motor_dir_g);

/**
  Checks if order lists are empty
  @return 1 if there are any orders, 0 if there are no orders.
*/
int areOrderListsEmpty_order();

#endif