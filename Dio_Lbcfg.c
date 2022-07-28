/**********************************************/
/*Module Name: DIO Driver                         */
/*Author: Mostafa Khaled / Ahmed Essam  */
/*Purpose: Initializes the ports and pins required to configure the DIO output LEDs.      */
/**********************************************/

#include "Dio_Lbcfg.h"

/***************************************************************/
/*Function Name : DioChannel_Init                                        */
/*Inputs               : None                                                          */
/*Outputs            : None                                                          */
/*Reentrancy       : Non-Reentrant                                         */
/*Synchronous    : Synch                                                         */
/*Description      : Initializes the DIO Driver module.          */
 /***************************************************************/
void DioChannel_Init (void)
{
    Port_ConfigType PORT_Red = { DIO, GPIO_Port, Channel_0, PORT_PIN_OUT, 0};
    Port_ConfigType PORT_Blue = { DIO, GPIO_Port, Channel_1, PORT_PIN_OUT, 0};
    Port_ConfigType PORT_Green = { DIO, GPIO_Port, Channel_2, PORT_PIN_OUT, 0};
    Port_Init(&PORT_Red);
    Port_Init(&PORT_Blue);
    Port_Init(&PORT_Green);
}
