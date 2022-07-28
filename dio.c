/**********************************************/
/*Module Name: DIO_LEDs Driver                */
/*Author: Mostafa Khaled / Ahmed Essam  */
/*Purpose: Blink the output LEDs.                */
/**********************************************/

#include "dio.h"

/***************************************************************/
/*Function Name : Dio_WriteChannel                                     */
/*Inputs                : ChannelId (ID of DIO channel), Level (Value to be written)  */
/*Outputs            : None                                                          */
/*Reentrancy        : Reentrant                                                  */
/*Synchronous     : Synch                                                        */
/*Description       : Service to set a level of a channel.         */
/***************************************************************/
void Dio_WriteChannel ( Dio_ChannelType ChannelId, Dio_LevelType Level )
{
    if (ChannelId == 0 && Level == STD_HIGH)
    {
        GPIOPinWrite(GPIO_Port, Channel_0, Channel_0);      /* Writes a value to the specified pin or channel  */
    }
    else if (ChannelId == 1 && Level == STD_HIGH)
    {
        GPIOPinWrite(GPIO_Port, Channel_1, Channel_1);       /* Writes a value to the specified pin or channel  */
    }
    else if (ChannelId == 2 &&  Level == STD_HIGH)
    {
        GPIOPinWrite(GPIO_Port, Channel_2, Channel_2);       /* Writes a value to the specified pin or channel  */
    }
    else if ( ChannelId == 0 && Level == STD_LOW)
    {
        GPIOPinWrite(GPIO_Port, Channel_0, STD_LOW);        /* Writes zero value to the specified pin or channel  */
    }
    else if ( ChannelId == 1 && Level == STD_LOW)
    {
        GPIOPinWrite(GPIO_Port, Channel_1, STD_LOW);        /* Writes zero value to the specified pin or channel  */
    }
    else if ( ChannelId == 2 && Level == STD_LOW)
    {
        GPIOPinWrite(GPIO_Port, Channel_2, STD_LOW);        /* Writes zero value to the specified pin or channel  */
    }
}