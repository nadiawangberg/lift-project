#include "FSM.h"


void PrintState(State state) {

	switch(state) {
		case INIT:
			printf("Init state");
			break;
		case IDLE:
			printf("Idle state");
			break;
		case RUNNING:
			printf("Running state");
			break;
		case DOOR_OPEN:
			printf("DoorOpen state");
			break;
		case STOP:
			printf("EmergencyStop state");		
			break;
		return;
	}
}

void StateMachineInit() {
	// for testing for now
	//positionInit();
	//motor_dir_g = DIRN_DOWN;
	positionInit();
    curr_state = IDLE;
    motor_dir_g = DIRN_STOP;
    //motor_dir_g = selectDir(curr_floor, motor_dir_g);
    printf("%i",motor_dir_g);
    printf("DONE WITH STATE MACHINE INIT!!");
}

void transitionFromDoorOpen() {
	// ALL STATE TRANSITIONS FROM DOOR OPEN
	curr_state = RUNNING;
	prev_state = DOOR_OPEN;

	/* prepartion for more states
	if (prev_state == EMERGENCYSTOP)
		curr_state = EMERGENCYSTOP;
	else if (order_direction_g == DIRN_UP || order_direction_g == DIRN_DOWN) :
		curr_state = RUNNING;
		elev_set_door_open_lamp(0); // close doors 
	else if (no orders) {
		elev_set_door_open_lamp(0); // close doors 
		curr_state = IDLE;
		}

	else if (no orders)
	*/
}

void StateMachine() {
	while(1) {
		// PrintState(state);

		// gjør generelle ting unless visse krav

		checkForOrders(); // checks if any buttons pressed, adds to order list
		curr_floor = elev_get_floor_sensor_signal(); // will be undefined most of the time
		if (curr_floor != UNDEFINED) { // we're in a floor
			elev_set_floor_indicator(curr_floor);
			last_floor = curr_floor;
		}

		//elev_set_floor_indicator(last_floor);
		//printOrders();
		//PrintState(curr_state);
		switch(curr_state) {
			case INIT:
				//printf("In INIT state, nothing here atm\n");
				//noe
				break;
			case IDLE:
				motor_dir_g=selectDir(last_floor,DIRN_STOP);

			 	//printf("%i",motor_dir_g);
				if(motor_dir_g!=DIRN_STOP){
					curr_state=RUNNING;
					//printf("%i",motor_dir_g);
					elev_set_motor_direction(motor_dir_g);
				}				
				prev_state = IDLE;
				//PrintState(curr_state);
				break;
			case RUNNING:
				if (curr_floor != UNDEFINED && shouldLiftStop(curr_floor)) { // we're in a floor, stop     			
        			curr_state = DOOR_OPEN;
        			removeOrders(curr_floor);
        			//elev_set_stop_lamp(0);

        			//motor_dir_g = DIRN_UP;
        			prev_state = RUNNING;
        			break;
    			}
    			elev_set_stop_lamp(1);
				//elev_set_motor_direction(motor_dir_g); // motor_dir_g, DIRN_UP
				prev_state = RUNNING;
				break;
			case DOOR_OPEN:
				if (prev_state != curr_state) { // just transitioned to door open
					DoorStateInit(); // timer started
				}

				if (TimerDone()) {
					DoorStateExit(curr_floor);
					motor_dir_g = selectDir(last_floor, motor_dir_g);
					elev_set_motor_direction(motor_dir_g);
					if(motor_dir_g!=DIRN_STOP){
						//printf("Vi burde ikke vaere her!!!\n");
						curr_state = RUNNING;
					}
					else{
						curr_state=IDLE;
					}
					// transitionFromDoorOpen();
					//DoorStateExit(curr_floor,motor_dir_g);
					break;
				}

				prev_state = DOOR_OPEN; // is it an issue to set prev_state = curr_state before EVERY break?
				break;
			case STOP:
				// noe
				break;
		}
	}
}