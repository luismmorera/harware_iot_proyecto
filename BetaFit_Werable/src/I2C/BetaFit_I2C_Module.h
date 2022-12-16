/**
  ******************************************************************************
  * @file   I2C_Module.h
  * @author Juan Morales Sáez (j.msaez@alumnos.upm.es)
  * @brief  I2C Module header.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the I2C bus.
  ******************************************************************************
*/

#ifndef __BetaFit_I2C_Module_h
#define __BetaFit_I2C_Module_h

  /* Includes ------------------------------------------------------------------*/
  #include <Arduino.h>
  
  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
    
    void I2C_Device_Begin (void);

    bool I2C_Device_Detected (uint8_t slave_address);

    void I2C_Device_Send_Data (uint8_t slave_address, uint8_t slave_register, uint8_t *buffer, uint8_t buffer_size);
    
    void I2C_Device_Read_Data (uint8_t slave_address, uint8_t slave_register, uint8_t *buffer, uint8_t buffer_size);

#endif // __BetaFit_I2C_Module_h
