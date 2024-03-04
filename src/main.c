/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <stdio.h>
#include <string.h>
#include "definitions.h"                // SYS function prototypes

#define ADC_VREF            (3.3f)
#define DAC_COUNT_INCREMENT (124U)
#define DAC_COUNT_MAX       (4095U)

uintptr_t adc_context;
volatile uint16_t adc_result = 0;
volatile bool adc_window_det = false;

void adc_cb(ADC_STATUS status, uintptr_t context)
{
    adc_window_det = true;
    adc_result = ADC_ConversionResultGet();
}

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    TC0_Timer16bitPeriodSet(10);
    TC0_TimerStart();
    
    ADC_ComparisonWindowSet(1024, 1024);
    
    ADC_CallbackRegister(adc_cb, adc_context);
    ADC_Enable();

    while ( true )
    {
         PM_StandbyModeEnter();
        if(adc_window_det == true)  {
            adc_window_det = false;
            printf("Window!!Window!!\r\n");
            printf("ADC : %d\r\n", adc_result);
        }
    }
    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

