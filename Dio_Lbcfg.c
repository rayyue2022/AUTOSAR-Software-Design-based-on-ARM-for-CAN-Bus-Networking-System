/**********************************************/
/*Module Name: DIO Driver                         */
/*Author: Mahmoud Ayman / Nader Ahmed  */
/*Purpose: Initializes the ports and pins required to configure the DIO input switches.    */
/**********************************************/

#include "Dio_Lbcfg.h"

/***************************************************************/
/*Function Name : DioChannel_Init                                     */
/*Inputs               : None                                                     */
/*Outputs            : None                                                     */
/*Reentrancy        : Non-Reentrant                                      */
/*Synchronous     : Synch                                                    */
/*Description       : Initializes the DIO Driver module.           */
 /***************************************************************/
void DioChannel_Init (void)
{
    Port_ConfigType PORT_Switch2 = { DIO, GPIO_Port, Channel_0, PORT_PIN_IN};
    Port_ConfigType PORT_Switch1 = { DIO,GPIO_Port , Channel_1, PORT_PIN_IN};
   Port_Init(&PORT_Switch2);
   Port_Init(&PORT_Switch1);

    GPIOIntDisable(GPIO_Port, Channel_0 | Channel_1);        /* Disable interrupt for PF0, PF4 (in case it was enabled)  */
    GPIOIntClear(GPIO_Port, Channel_0 | Channel_1);      /* Clear pending interrupts for PF0, PF4   */
    GPIOIntTypeSet(GPIO_Port, Channel_0 | Channel_1, GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_Port, Channel_0 | Channel_1);
    IntEnable(GPIOPort_Interrupt);

}
