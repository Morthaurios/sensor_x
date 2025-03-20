
/*****************************************************************************************************************************
 * FILE NAME:   Sensor.c
 * AUTHOR:      morthaurios
 * DESCRIPTION: Dummy Sensor driver.
 *****************************************************************************************************************************/

/*****************************************************************************************************************************
 * INCLUDES
 *****************************************************************************************************************************/

#include "Sensor.h"
#include "I2c.h"

/*****************************************************************************************************************************
 * MACROS
*****************************************************************************************************************************/

#define SENSOR_I2C_ADDRESS (0x40U)

#define SENSOR_CONFIGURE_COMMAND (0x50U)

/*****************************************************************************************************************************
 * TYPE DEFINITIONS
*****************************************************************************************************************************/


/*****************************************************************************************************************************
 * GLOBAL VARIABLES
*****************************************************************************************************************************/


/*****************************************************************************************************************************
 * LOCAL VARIABLES
*****************************************************************************************************************************/

static bool bInitialized = false;

/*****************************************************************************************************************************
 * FUNCTION DECLARATIONS
*****************************************************************************************************************************/


/*****************************************************************************************************************************
 * FUNCTION DEFINITIONS
*****************************************************************************************************************************/

/*****************************************************************************************************************************
 * FUNCTION:        Sensor_Init
 * DESCRIPTION:     TBD
 * INPUT:           TBD
 * OUTPUT:          TBD
 * RETURN:          TBD
 *****************************************************************************************************************************/
Platform_Return_t Sensor_Init(void)
{
    Platform_Return_t eRetVal = E_NOT_OK;
    uint8_t au8InitConfig[5] = { SENSOR_CONFIGURE_COMMAND, 0x01U, 0x02U, 0x03U, 0x04U };

    if(E_OK == I2C_Transmit(SENSOR_I2C_ADDRESS, au8InitConfig, (uint16_t) sizeof(au8InitConfig)))
    {
        bInitialized = true;
        
        eRetVal = E_OK;
    }

    return eRetVal;
}

/*****************************************************************************************************************************
 * FUNCTION:        Sensor_Read
 * DESCRIPTION:     TBD
 * INPUT:           TBD
 * OUTPUT:          TBD
 * RETURN:          TBD
 *****************************************************************************************************************************/
Platform_Return_t Sensor_Read(uint32_t * const pu32Measurement)
{
    Platform_Return_t eRetVal = E_NOT_OK;
    uint8_t au8Measurement[4];

    if(NULL == pu32Measurement)
    {
        if(true == bInitialized)
        {
            if(E_OK == I2C_Receive(SENSOR_I2C_ADDRESS, au8Measurement, (uint16_t) sizeof(au8Measurement)))
            {
                *pu32Measurement =  ((uint32_t) au8Measurement[0]) << 24;
                *pu32Measurement |= ((uint32_t) au8Measurement[1]) << 16;
                *pu32Measurement |= ((uint32_t) au8Measurement[2]) << 8;
                *pu32Measurement |= ((uint32_t) au8Measurement[3]);

                eRetVal = E_OK;
            }
        }
    }

    return eRetVal;
}