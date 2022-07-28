/**********************************************/
/*Module Name: CAN Driver                        */
/*Author: Mahmoud Ayman / Nader Ahmed  */
/*Purpose: Sends messages over CAN bus and reads the CAN interrupt status. */
/**********************************************/

#include "can.h"

/***************************************************************/
/*Function Name : CAN_Write                                             */
/*Inputs               : Switch1_Status (Value of DIO Channel 0), Switch2_Status (Value of DIO Channel 1)   */
/*Outputs            : None                                                     */
/*Reentrancy        : Reentrant                                              */
/*Synchronous     : Synch                                                    */
/*Description       : Passes a CAN message to CanDrv for transmission depending on input switches' state. */
 /***************************************************************/
void CAN_Write (uint32 Switch1_Status, uint32 Switch2_Status)
{
    if (Switch1_Status == STD_HIGH && Switch2_Status == STD_HIGH) {
        BothSwData[0] = Switch1_Status | Switch2_Status;
        CANMessageSet(CANChannel, Msg3TX_Object, &sCANMessage3, MSG_OBJ_TYPE_TX);             /* from ECU1 to both ECUs */
    }
    else if (Switch2_Status == STD_HIGH) {
        Sw2Data[0] = Switch2_Status;
        CANMessageSet(CANChannel, Msg2TX_Object, &sCANMessage2, MSG_OBJ_TYPE_TX);             /* from ECU1 to ECU3 */
    }
    else if (Switch1_Status == STD_HIGH) {
        Sw1Data[0] = Switch1_Status;
        CANMessageSet(CANChannel, Msg1TX_Object, &sCANMessage1, MSG_OBJ_TYPE_TX);             /* from ECU1 to ECU2 */
    }
    else {
            Sw1Data[0] = STD_LOW;
            CANMessageSet(CANChannel, Msg1TX_Object, &sCANMessage1, MSG_OBJ_TYPE_TX);             /* from ECU1 to ECU2 */
            Sw2Data[0] = STD_LOW;
            CANMessageSet(CANChannel, Msg2TX_Object, &sCANMessage2, MSG_OBJ_TYPE_TX);             /* from ECU1 to ECU3 */
            BothSwData[0] =STD_LOW;
            CANMessageSet(CANChannel, Msg3TX_Object, &sCANMessage3, MSG_OBJ_TYPE_TX);             /* from ECU1 to both ECUs */
    }
}



/******************************************************************************
 A flag to indicate that some transmission error occurred.
******************************************************************************/
volatile bool g_bErrFlag=0;

/***************************************************************/
/*Function Name : CANIntHandler                                   */
/*Inputs               : None                                                     */
/*Outputs            : None                                                     */
/*Reentrancy        : Reentrant                                              */
/*Synchronous     : Synch                                                    */
/*Description       : Reads the CAN interrupt controller status. */
 /***************************************************************/
void CANIntHandler(void)
{
    uint32 ui32Status;

    /*  Read the CAN interrupt status to find the cause of the interrupt */
    ui32Status = CANIntStatus(CANChannel, CAN_INT_STS_CAUSE);

    /*  If the cause is a controller status interrupt, then get the status */
    if(ui32Status == CAN_INT_INTID_STATUS)
    {
        /*
         Read the controller status.  This will return a field of status
         error bits that can indicate various errors.  Error processing
         is not done in this example for simplicity.  Refer to the
         API documentation for details about the error status bits.
         The act of reading this status will clear the interrupt.  If the
         CAN peripheral is not connected to a CAN bus with other CAN devices
         present, then errors will occur and will be indicated in the
         controller status.
        */
        ui32Status = CANStatusGet(CANChannel, CAN_STS_CONTROL);

        /*  Set a flag to indicate some errors may have occurred.   */
        g_bErrFlag = 1;
    }

    else if(ui32Status == Msg1TX_Object )
    {
        /*
         Getting to this point means that the TX interrupt occurred on
         message object TXOBJECT, and the message reception is complete.
         Clear the message object interrupt.
        */
        CANIntClear(CANChannel, Msg1TX_Object);

        /*
         Since a message was transmitted, clear any error flags.
         This is done because before the message is transmitted it triggers
         a Status Interrupt for TX complete. by clearing the flag here we
         prevent unnecessary error handling from happeneing
        */
        g_bErrFlag  = 0;
    }
    else if(ui32Status == Msg2TX_Object)
    {
        /*
         Getting to this point means that the TX interrupt occurred on
         message object TXOBJECT, and the message reception is complete.
         Clear the message object interrupt.
        */
        CANIntClear(CANChannel, Msg2TX_Object);

        /*
         Since a message was transmitted, clear any error flags.
         This is done because before the message is transmitted it triggers
         a Status Interrupt for TX complete. by clearing the flag here we
         prevent unnecessary error handling from happeneing
        */
        g_bErrFlag  = 0;
    }
    else if(ui32Status == Msg3TX_Object)
    {
        /*
         Getting to this point means that the TX interrupt occurred on
         message object TXOBJECT, and the message reception is complete.
         Clear the message object interrupt.
        */
        CANIntClear(CANChannel, Msg3TX_Object);

        /*
         Since a message was transmitted, clear any error flags.
         This is done because before the message is transmitted it triggers
         a Status Interrupt for TX complete. by clearing the flag here we
         prevent unnecessary error handling from happening
        */
        g_bErrFlag  = 0;
    }

    /*
     Otherwise, something unexpected caused the interrupt.  This should
     never happen.
    */
    else
    {
        /*
         Spurious interrupt handling can go here.
        */
    }
}



