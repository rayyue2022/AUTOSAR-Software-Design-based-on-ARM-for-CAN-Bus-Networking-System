/**********************************************/
/*Module Name: CAN Driver                        */
/*Author: Ahmed Essam / Ahmed Hatem    */
/*Purpose: Reads messages over CAN bus and the CAN interrupt status. */
/**********************************************/

#include "can.h"

uint8 SW1State = SW_LOW;
uint8 BothSWState = SW_LOW;

/***************************************************************/
/*Function Name : CAN_Read                                             */
/*Inputs               : None                                                    */
/*Outputs            : None                                                    */
/*Reentrancy        : Reentrant                                             */
/*Synchronous     : Synch                                                   */
/*Description       : Reads if a CAN message is sent on CanDrv for receive. */
 /***************************************************************/
void CAN_Read (void)
{
        if(g_M1RXFlag)
            {

                /*
                 Reuse the same message object that was used earlier to configure
                 the CAN for receiving messages.  A buffer for storing the
                 received data must also be provided, so set the buffer pointer
                 within the message object.
                */
                sCANMessageRX.pui8MsgData = pui8MsgDataRX;

                /*
                 Read the message from the CAN.  Message object number 1 is used
                 (which is not the same thing as CAN ID).  The interrupt clearing
                 flag is not set because this interrupt was already cleared in
                 the interrupt handler.
                */
                CANMessageGet(CANChannel, Msg1RX_Object, &sCANMessageRX, 0);      //Tiva2 receive from Tiva1

                SW1State = pui8MsgDataRX[0];

                /*  Clear the pending message flag so that the interrupt handler can set it again when the next message arrives. */
                g_M1RXFlag = 0;
            }
            else if(g_M2RXFlag)
            {

                sCANMessageRX.pui8MsgData = pui8MsgDataRX;
                CANMessageGet(CANChannel, Msg2RX_Object, &sCANMessageRX, 0);      //Tiva2 receive from Tiva1

                BothSWState = pui8MsgDataRX[0];

                /*  Clear the pending message flag so that the interrupt handler can set it again when the next message arrives. */
                g_M2RXFlag = 0;
            }
}




/******************************************************************************
 A flag to indicate that some transmission error occurred.
******************************************************************************/
volatile bool g_bErrFlag=0;

/******************************************************************************
 A flag for the interrupt handler to indicate that a message was received.
******************************************************************************/
volatile bool g_M1RXFlag=0;
volatile bool g_M2RXFlag=0;

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

    //
    // Check if the cause is message object 1, which what we are using for
    // sending messages.
    //
    else if(ui32Status == Msg1RX_Object)
    {
        /*
         Getting to this point means that the TX interrupt occurred on
         message object TXOBJECT, and the message reception is complete.
         Clear the message object interrupt.
        */
        CANIntClear(CANChannel, Msg1RX_Object);


        /*  Set flag to indicate received message is pending.  */
        g_M1RXFlag = 1;
        /*  Since the message was sent, clear any error flags. */
        g_bErrFlag = 0;
    }
    else if(ui32Status == Msg2RX_Object)
    {
        /*
         Getting to this point means that the TX interrupt occurred on
         message object TXOBJECT, and the message reception is complete.
         Clear the message object interrupt.
        */
        CANIntClear(CANChannel, Msg2RX_Object);


        /*  Set flag to indicate received message is pending.  */
        g_M2RXFlag = 1;
        /*  Since the message was sent, clear any error flags. */
        g_bErrFlag = 0;
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
