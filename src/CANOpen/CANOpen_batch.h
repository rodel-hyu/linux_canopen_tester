#ifndef CANOPEN_CANOPEN_BATCH_H_
#define CANOPEN_CANOPEN_BATCH_H_

#include "CANOpen.h"

#define M1_ID	0x70
#define M2_ID	0x71

extern CO_PDOStruct RPDO1_M1;
extern CO_PDOStruct TPDO1_M1;
extern int32_t OD_M1_target_position;
extern int32_t OD_M1_actual_position;

extern CO_PDOStruct RPDO1_M2;
extern CO_PDOStruct TPDO1_M2;
extern int32_t OD_M2_target_position;
extern int32_t OD_M2_actual_position;

extern CO_PDOStruct RPDO1_0x42;
extern CO_PDOStruct TPDO1_0x42;
extern int32_t OD_0x42_target_speed;
extern int32_t OD_0x42_actual_speed;

extern void CANOpen_batch_M1_start();
extern void CANOpen_batch_M1_end();

extern void CANOpen_batch_M2_start();
extern void CANOpen_batch_M2_end();

extern void CANOpen_batch_0x42_start();
extern void CANOpen_batch_0x42_end();

#endif /* CANOPEN_CANOPEN_BATCH_H_ */
