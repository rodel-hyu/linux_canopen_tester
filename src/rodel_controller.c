#include "rodel_controller.h"
#include "CANOpen/CANOpen_batch.h"

#include <stdio.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>

void control_loop(){

	// TODO
	// Use variables
	// int32_t OD_0x40_target_position
	// int32_t OD_0x40_actual_position
	// int32_t OD_0x41_target_position
	// int32_t OD_0x41_actual_position
	// int32_t OD_0x42_target_speed
	// int32_t OD_0x42_actual_speed


	// Read from stdin
	static struct timeval timeout;
	static fd_set set;
	static int rv;
	static char comm[256];


	FD_ZERO(&set);
	FD_SET(0, &set); // 0 = stdin

	timeout.tv_sec = 0;
	timeout.tv_usec = 100000;

	rv = select(1, &set, NULL, NULL, &timeout);
	if(rv > 0){
		read(0, comm, 1);
	}


	switch(comm[0]){
	case 'q' :
		CANOpen_writeOD_uint32(M1_ID, 0x2002, 0x04, 18634, 100);
		CANOpen_writeOD_uint32(M2_ID, 0x2002, 0x04, 18634, 100);
		OD_M1_target_position += 2000;
		OD_M2_target_position += 2000;
		break;
	case 'w' :
		CANOpen_writeOD_uint32(M1_ID, 0x2002, 0x04, 18634, 100);
		CANOpen_writeOD_uint32(M2_ID, 0x2002, 0x04, 18634, 100);
		OD_M1_target_position -= 2000;
		OD_M2_target_position -= 2000;
		break;
	case 'e' :
		CANOpen_writeOD_uint32(M1_ID, 0x2002, 0x04, 18634, 100);
		CANOpen_writeOD_uint32(M2_ID, 0x2002, 0x04, 18634, 100);
		OD_M1_target_position += 2000;
		OD_M2_target_position -= 2000;
		break;
	case 'r' :
		CANOpen_writeOD_uint32(M1_ID, 0x2002, 0x04, 18634, 100);
		CANOpen_writeOD_uint32(M2_ID, 0x2002, 0x04, 18634, 100);
		OD_M1_target_position -= 2000;
		OD_M2_target_position += 2000;
		break;
	case 't' :
		OD_M1_target_position += 100;
		break;
	case 'y' :
		OD_M1_target_position -= 100;
		break;
	case 'u' :
		OD_M2_target_position += 100;
		break;
	case 'i' :
		OD_M2_target_position -= 100;
		break;
	case 'o' :
		CANOpen_writeOD_uint32(M1_ID, 0x2002, 0x03, 4000, 100);
		CANOpen_writeOD_uint32(M2_ID, 0x2002, 0x03, 4000, 100);
		OD_M1_target_position = 8000;
		OD_M2_target_position = 8000;
		break;
	case 'p' :
		CANOpen_writeOD_uint32(M1_ID, 0x2002, 0x03, 4000, 100);
		CANOpen_writeOD_uint32(M2_ID, 0x2002, 0x03, 4000, 100);
		OD_M1_target_position = 0;
		OD_M2_target_position = 0;
		break;
	case 'a' :
		break;

	case 's' :
		CANOpen_batch_M1_end();
		CANOpen_batch_M2_end();
		break;

	case 'd' :
	    CANOpen_batch_M1_start();
	    CANOpen_batch_M2_start();
		break;

	case 'z' :
		CANOpen_writeOD_uint8(M1_ID, 0x2002, 0x07, 1, 100);
		CANOpen_writeOD_uint8(M2_ID, 0x2002, 0x07, 1, 100);
		break;
	}

	// Communicate
	CANOpen_sendPDO(M1_ID, 1, &RPDO1_M1);
	CANOpen_sendPDO(M2_ID, 1, &RPDO1_M2);
	CANOpen_sendSync();
	CANOpen_readPDO(M1_ID, 1, &TPDO1_M1, 2);
	CANOpen_readPDO(M2_ID, 1, &TPDO1_M2, 2);

	printf("[0x40] %d\t%d\n", OD_M1_target_position, OD_M1_actual_position);
	printf("[0x41] %d\t%d\n", OD_M2_target_position, OD_M2_actual_position);
	//printf("[0x42] %d\t%d\n", OD_0x42_target_speed, OD_0x42_actual_speed);
	printf("=====================================\n");

}
