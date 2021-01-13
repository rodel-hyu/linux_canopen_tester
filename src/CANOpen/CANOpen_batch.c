
#include "CANOpen_batch.h"

CO_PDOStruct RPDO1_M1;
CO_PDOStruct TPDO1_M1;
int32_t OD_M1_target_position;
int32_t OD_M1_actual_position;

CO_PDOStruct RPDO1_M2;
CO_PDOStruct TPDO1_M2;
int32_t OD_M2_target_position;
int32_t OD_M2_actual_position;

CO_PDOStruct RPDO1_0x42;
CO_PDOStruct TPDO1_0x42;
int32_t OD_0x42_target_speed;
int32_t OD_0x42_actual_speed;

void CANOpen_batch_M1_start(){

	CANOpen_writeOD_uint8(M1_ID, 0x2000, 0x04, 0x00, 100);

	CANOpen_writeOD_uint32(M1_ID, 0x1400, 0x01, 0x80000200 | M1_ID, 100);
	CANOpen_writeOD_uint8(M1_ID, 0x1600, 0x00, 0x00, 100);
	CANOpen_writeOD_uint32(M1_ID, 0x1600, 0x01, 0x20000220, 100);
	CANOpen_writeOD_uint8(M1_ID, 0x1600, 0x00, 0x01, 100);
	CANOpen_writeOD_uint32(M1_ID, 0x1400, 0x01, 0x200 | M1_ID, 100);

	CANOpen_writeOD_uint32(M1_ID, 0x1800, 0x01, 0x80000180 | M1_ID, 100);
	CANOpen_writeOD_uint8(M1_ID, 0x1A00, 0x00, 0x00, 100);
	CANOpen_writeOD_uint32(M1_ID, 0x1A00, 0x01, 0x20010220, 100);
	CANOpen_writeOD_uint8(M1_ID, 0x1A00, 0x00, 0x01, 100);
	CANOpen_writeOD_uint32(M1_ID, 0x1800, 0x01, 0x180 | M1_ID, 100);

	CANOpen_mappingPDO_init(&RPDO1_M1);
	CANOpen_mappingPDO_int32(&RPDO1_M1, &OD_M1_target_position);

	CANOpen_mappingPDO_init(&TPDO1_M1);
	CANOpen_mappingPDO_int32(&TPDO1_M1, &OD_M1_actual_position);

	CANOpen_writeOD_uint8(M1_ID, 0x2002, 0x07, 0x01, 100);
	CANOpen_writeOD_uint8(M1_ID, 0x2000, 0x04, 0x04, 100);

}

void CANOpen_batch_M1_end(){
	CANOpen_writeOD_uint8(M1_ID, 0x2000, 0x04, 0x00, 100);
}

void CANOpen_batch_M2_start(){

	CANOpen_writeOD_uint8(M2_ID, 0x2000, 0x04, 0x00, 100);

	CANOpen_writeOD_uint32(M2_ID, 0x1400, 0x01, 0x80000200 | M2_ID, 100);
	CANOpen_writeOD_uint8(M2_ID, 0x1600, 0x00, 0x00, 100);
	CANOpen_writeOD_uint32(M2_ID, 0x1600, 0x01, 0x20000220, 100);
	CANOpen_writeOD_uint8(M2_ID, 0x1600, 0x00, 0x01, 100);
	CANOpen_writeOD_uint32(M2_ID, 0x1400, 0x01, 0x200 | M2_ID, 100);

	CANOpen_writeOD_uint32(M2_ID, 0x1800, 0x01, 0x80000180 | M2_ID, 100);
	CANOpen_writeOD_uint8(M2_ID, 0x1A00, 0x00, 0x00, 100);
	CANOpen_writeOD_uint32(M2_ID, 0x1A00, 0x01, 0x20010220, 100);
	CANOpen_writeOD_uint8(M2_ID, 0x1A00, 0x00, 0x01, 100);
	CANOpen_writeOD_uint32(M2_ID, 0x1800, 0x01, 0x180 | M2_ID, 100);

	CANOpen_mappingPDO_init(&RPDO1_M2);
	CANOpen_mappingPDO_int32(&RPDO1_M2, &OD_M2_target_position);

	CANOpen_mappingPDO_init(&TPDO1_M2);
	CANOpen_mappingPDO_int32(&TPDO1_M2, &OD_M2_actual_position);

	CANOpen_writeOD_uint8(M2_ID, 0x2002, 0x07, 0x01, 100);
	CANOpen_writeOD_uint8(M2_ID, 0x2000, 0x04, 0x04, 100);

}

void CANOpen_batch_M2_end(){
	CANOpen_writeOD_uint8(M2_ID, 0x2000, 0x04, 0x00, 100);
}

void CANOpen_batch_0x42_start(){

	CANOpen_writeOD_uint8(0x42, 0x2040, 0x00, 0x00, 100);

	CANOpen_writeOD_uint32(0x42, 0x1400, 0x01, 0x80000200 | 0x42, 100);
	CANOpen_writeOD_uint8(0x42, 0x1600, 0x00, 0x00, 100);
	CANOpen_writeOD_uint32(0x42, 0x1600, 0x01, 0x20430520, 100);
	CANOpen_writeOD_uint8(0x42, 0x1600, 0x00, 0x01, 100);
	CANOpen_writeOD_uint32(0x42, 0x1400, 0x01, 0x200 | 0x42, 100);

	CANOpen_writeOD_uint32(0x42, 0x1800, 0x01, 0x80000180 | 0x42, 100);
	CANOpen_writeOD_uint8(0x42, 0x1A00, 0x00, 0x00, 100);
	CANOpen_writeOD_uint32(0x42, 0x1A00, 0x01, 0x20430420, 100);
	CANOpen_writeOD_uint8(0x42, 0x1A00, 0x00, 0x01, 100);
	CANOpen_writeOD_uint32(0x42, 0x1800, 0x01, 0x180 | 0x42, 100);

	CANOpen_mappingPDO_init(&RPDO1_0x42);
	CANOpen_mappingPDO_int32(&RPDO1_0x42, &OD_0x42_target_speed);

	CANOpen_mappingPDO_init(&TPDO1_0x42);
	CANOpen_mappingPDO_int32(&TPDO1_0x42, &OD_0x42_actual_speed);

	CANOpen_writeOD_uint8(0x42, 0x2040, 0x00, 0x02, 100);

}

void CANOpen_batch_0x42_end(){

	CANOpen_writeOD_uint8(0x42, 0x2040, 0x00, 0x00, 100);
	CANOpen_writeOD_int32(0x42, 0x2043, 0x05, 0, 100);

}
