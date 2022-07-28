/**********************************************/
/*Module Name: CAN Driver                        */
/*Author: Ahmed Essam / Ahmed Hatem    */
/*Purpose: Initializes and configures the required sets of the CAN module.  */
/**********************************************/


#include "CAN_Lbcfg.h"

tCANMsgObject sCANMessageRX;
uint8 pui8MsgDataRX[8];


/***************************************************************/
/*Function Name : CAN_Init                                                */
/*Inputs               : None                                                     */
/*Outputs            : None                                                     */
/*Reentrancy        : Non-Reentrant                                      */
/*Synchronous     : Synch                                                    */
/*Description       : Initializes the CAN Driver module.          */
 /***************************************************************/
void CAN_Init(void)
{

    Port_ConfigType PORT_CANRX = { CAN, CAN_GPIOPort, GPIO_RXPin };
    Port_ConfigType PORT_CANTX = { CAN, CAN_GPIOPort, GPIO_TXPin };
    Port_Init(&PORT_CANRX);
    Port_Init(&PORT_CANTX);

    /*
     Enable interrupts on the CAN peripheral.  This example uses static
     allocation of interrupt handlers which means the name of the handler
     is in the vector table of startup code.  If you want to use dynamic
     allocation of the vector table, then you must also call CANIntRegister()
     here.
    */
    CANIntRegister(CANChannel, CANIntHandler);     /*  Register an interrupt handler for the CAN controller.   */

    CANIntEnable(CANChannel, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

    /*  Enable the CAN interrupt on the processor (NVIC).  */
    IntEnable(CANChannel_Interrupt);


    /*
     Initialize a message object to be used for receiving CAN messages with
     any CAN ID.  In order to receive any CAN ID, the ID and mask must both
     be set to 0, and the ID filter enabled.
    */
    /*
     Initialize a message object to receive CAN messages with ID 0x1001.
     The expected ID must be set along with the mask to indicate that all
     bits in the ID must match.
    */
    sCANMessageRX.ui32MsgID = Msg1_ID;
    sCANMessageRX.ui32MsgIDMask = MsgIDMask;
    sCANMessageRX.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sCANMessageRX.ui32MsgLen = 8;

    /*
     Now load the message object into the CAN peripheral message object 1.
     Once loaded the CAN will receive any messages with this CAN ID into
     this message object, and an interrupt will occur.
    */
    CANMessageSet(CANChannel, Msg1RX_Object, &sCANMessageRX, MSG_OBJ_TYPE_RX);

    /*
     Change the ID to 0x2001, and load into message object 2 which will be
     used for receiving any CAN messages with this ID.  Since only the CAN
     ID field changes, we don't need to reload all the other fields.
    */
    sCANMessageRX.ui32MsgID = Msg2_ID;
    CANMessageSet(CANChannel, Msg2RX_Object, &sCANMessageRX, MSG_OBJ_TYPE_RX);

}


