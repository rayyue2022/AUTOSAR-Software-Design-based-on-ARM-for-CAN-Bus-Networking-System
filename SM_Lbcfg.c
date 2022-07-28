/**********************************************/
/*Module Name: State Machine Software Component  */
/*Author: Ahmed Essam / Ahmed Hatem    */
/*Purpose: Initializes and configures the required sets of the state machine module.  */
/**********************************************/

#include "SM_Lbcfg.h"

uint8 state;
uint8 colorstate;
/***************************************************************/
/*Function Name  : App_SM_Init                                              */
/*Inputs                : None                                                          */
/*Outputs             : None                                                          */
/*Reentrancy        : Non-Reentrant                                          */
/*Synchronous     : Synch                                                         */
/*Description       : Initializes the ECU and color states.        */
/***************************************************************/
void App_SM_Init (void)
{
    /*  Set the leds initially to red   */
    Dio_WriteChannel(Red, STD_HIGH);    /*  Turn on LED 1 (RED) */
    colorstate = RED_LED;   /*  Declare color state variable   */
    state=waiting;      /*  Declare state variable   */
}


