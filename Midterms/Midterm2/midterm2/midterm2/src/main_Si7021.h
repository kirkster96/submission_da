/*
 * main_Si7021.h
 *
 * Created: 12/13/2019 12:37:30 PM
 *  Author: Kirks
 */ 


#ifndef MAIN_SI7021_H_
#define MAIN_SI7021_H_
#define Si7021 (0x40<<1)     // (0x40 << 1) I2C slave address

#define Si7021_Measure_RH_Hold_Mode             0xE5
#define Si7021_Measure_RH_No_Hold_Mode          0xF5
#define Si7021_Measure_T_Hold_Mode              0xE3
#define Si7021_Measure_T_No_Hold_Mode           0xF3
#define Si7021_Read_T_from_Last_RH_Value        0xE0
#define Si7021_Reset                            0xFE
#define Si7021_Write_Config_Register            0xE6
#define Si7021_Read_Config_Register             0xE7
#define Si7021_Write_Heater_Control_Register    0x51
#define Si7021_Read_Heater_Control_Register     0x11
#define Si7021_Read_ID1_H                       0xFA
#define Si7021_Read_ID1_L                       0x0F
#define Si7021_Read_ID2_H                       0xFC
#define Si7021_Read_ID2_L                       0xC9
#define Si7021_Read_Firmware_Version_H          0x84
#define Si7021_Read_Firmware_Version_L          0xB8

#define Si7021_Config_Resolution_RH_12_T14      0x00
#define Si70211_Config_Resolution_RH_8_T12      0x01
#define Si70211_Config_Resolution_RH_10_T13     0x80
#define Si70211_Config_Resolution_RH_11_T11     0x81

#define Si70211_Config_VDD_Ok                   0x00
#define Si70211_Config_VDD_Low                  0x40

#define Si70211_Config_Heater_Off               0x00
#define Si70211_Config_Heater_On                0x04


void Si7021_writereg(uint8_t reg, uint8_t val);
void Init_Si7021();
void Si7021_config(void);

#endif /* MAIN_SI7021_H_ */
