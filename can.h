/**********************************************/
/*Module Name: CAN Driver                        */
/*Author: Ahmed Essam / Ahmed Hatem    */
/*Purpose: Reads messages over CAN bus and the CAN interrupt status. */
/**********************************************/

#ifndef CAN_H_
#define CAN_H_

#include "CAN_Lbcfg.h"

extern uint8 SW1State;
extern uint8 BothSWState;

extern void CAN_Read (void);
extern void CANIntHandler(void);

#endif /* CAN_H_ */
