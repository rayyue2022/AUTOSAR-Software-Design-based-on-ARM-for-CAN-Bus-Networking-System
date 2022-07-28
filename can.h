/**********************************************/
/*Module Name: CAN Driver                        */
/*Author: Mahmoud Ayman / Nader Ahmed  */
/*Purpose: Sends messages over CAN bus and reads the CAN interrupt status. */
/**********************************************/

#ifndef CAN_H_
#define CAN_H_

#include "Typedefs.h"
#include "CAN_Lbcfg.h"

extern void CAN_Write (uint32 Switch1_Status, uint32 Switch2_Status);
extern void CANIntHandler(void);

#endif /* CAN_H_ */
