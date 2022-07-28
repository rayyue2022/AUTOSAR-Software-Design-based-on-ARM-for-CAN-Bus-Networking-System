/**********************************************/
/*Module Name: CAN Driver                        */
/*Author: Mahmoud Ayman / Nader Ahmed   */
/*Purpose: Initializes and configures the required sets of the CAN module.  */
/**********************************************/

#include <CAN_Lbcfg.h>

tCANMsgObject sCANMessage1;
uint8 Sw1Data[8];

tCANMsgObject sCANMessage2;
uint8 Sw2Data[8];

tCANMsgObject sCANMessage3;
uint8 BothSwData[8];


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
     Initialize the message object that will be used for sending CAN
     messages.  The message will be 4 bytes that will contain an incrementing
     value.  Initially it will be set to 0.
    */

    /*
     Initialize message object 1 to be able to send CAN message 1.  This
     message object is not shared so it only needs to be initialized one
     time, and can be used for repeatedly sending the same message ID.
    */
    /*  MSG OBJECT 1    */
    sCANMessage1.ui32MsgID = Msg1_ID;
    sCANMessage1.ui32MsgIDMask = MsgIDMask;
    sCANMessage1.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage1.ui32MsgLen = sizeof(Sw1Data);
    sCANMessage1.pui8MsgData = Sw1Data;
    /*
     Initialize message object 2 to be able to send CAN message 2.  This
     message object is not shared so it only needs to be initialized one
     time, and can be used for repeatedly sending the same message ID.
    */
    /*  MSG OBJECT 2    */
    sCANMessage2.ui32MsgID = Msg2_ID;
    sCANMessage2.ui32MsgIDMask = MsgIDMask;
    sCANMessage2.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage2.ui32MsgLen = sizeof(Sw2Data);
    sCANMessage2.pui8MsgData = Sw2Data;
    /*
     Initialize message object 2 to be able to send CAN message 3.  This
     message object is not shared so it only needs to be initialized one
     time, and can be used for repeatedly sending the same message ID.
    */
    /*  MSG OBJECT 3    */
    sCANMessage3.ui32MsgID = Msg3_ID;
    sCANMessage3.ui32MsgIDMask = MsgIDMask;
    sCANMessage3.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage3.ui32MsgLen = sizeof(BothSwData);
    sCANMessage3.pui8MsgData = BothSwData;

}

