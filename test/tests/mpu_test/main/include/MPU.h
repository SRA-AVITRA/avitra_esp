#ifndef MPU_H
#define MPU_H

#include <stdio.h>
#include <math.h>
#include <time.h>
#include "esp_system.h"
#include "driver/i2c.h"
#include "esp_timer.h"

#define I2C_MASTER_SCL_IO    		21  		// gpio number for I2C master clock
#define I2C_MASTER_SDA_IO    		22    		// gpio number for I2C master data 
#define I2C_MASTER_NUM 				I2C_NUM_0   // I2C port number for master dev
#define I2C_MASTER_TX_BUF_DISABLE   0   		// I2C master do not need buffer
#define I2C_MASTER_RX_BUF_DISABLE   0   		// I2C master do not need buffer
#define I2C_MASTER_FREQ_HZ		    400000		// I2C master clock frequency

#define MPU9250_ADDR		0x68    			// slave address for BH1750 sensor
#define MAG_ADDR 			0x0C
#define MAG_START_ADDR 		0x03				//magnetometer start address
#define ACCE_START_ADDR 	0x3B				//acce start address
#define GYRO_START_ADDR 	0x43				//gyro start address

#define WRITE_BIT  			I2C_MASTER_WRITE	// I2C master write
#define READ_BIT   			I2C_MASTER_READ 	// I2C master read
#define ACK_CHECK_EN   		0x1    				// I2C master will check ack from slave*/
#define ACK_CHECK_DIS  		0x0     			// I2C master will not check ack from slave
#define ACK_VAL    			0x0         		// I2C ack value
#define NACK_VAL   			0x1         		// I2C nack value
#define I2C_MST_CTRL   		0x24   				// I2C master control
#define I2C_SLV0_ADDR  		0x25   				// I2C slave 0 address
#define I2C_SLV0_REG   		0x26   				// I2C slave 0 register
#define I2C_SLV0_CTRL  		0x27   				// I2C slave 0 control
#define I2C_SLV0_EN   		0x80   				// I2C slave 0 enable
#define I2C_SLV0_DO   		0x63   				// I2C slave 0 data out
#define EXT_SENSE_DATA_00   0x49   				// External sensor data
#define PWR_MGMT_1   		0x6B   				// Power management 1
#define USER_CTRL   		0x6A		   		// User control
#define INT_PIN_CFG   		0x37   				// Bypass enable config
#define CNTL_1   			0x0A 				// Magnetometer control 1

#define BUFF_SIZE 6

#define PI 3.141592653589793238462643383279502884

//Calibration values
#define magCalibration_x 1.171875
#define magCalibration_y 1.171875
#define magCalibration_z 1.132812

#define mag_offset_x 485.837341
#define mag_offset_y 266.200195
#define mag_offset_z -67.091797

#define gyro_offset_x 5.946565
#define gyro_offset_y 2.870229
#define gyro_offset_z -0.015267

#define acce_offset_x 0.014587
#define acce_offset_y 0.021423
#define acce_offset_z 0.496155

#define scale_x 0.852330
#define scale_y 0.978601
#define scale_z 1.242424

#define mRes 10.*4912./32760.0
#define gRes 250.0/32768.0
#define aRes 16.0/32768.0

esp_err_t write_byte(i2c_port_t i2c_num, int8_t main_add, int8_t add, int8_t data);

esp_err_t write_to_mag(int8_t sub_address, int8_t* data);

esp_err_t read_byte(i2c_port_t i2c_num,int8_t main_add, int8_t add, uint8_t* data_rd, size_t size);

esp_err_t read_from_mag(int8_t sub_address, int8_t count, uint8_t* data);

//Initialise and power ON, MPU9250
esp_err_t mpu9250_init(i2c_port_t i2c_num);

esp_err_t mpu9250_read_mag(i2c_port_t i2c_num, uint8_t* data_rd, size_t size);

//Initialise the I2C bus and install driver to specified pins
void i2c_master_init();

//Proceed only when MPU is initialise
void start_mpu();

//Read raw magnetometer values
void get_mag_raw(int16_t* mag_raw);

//Read raw magnetometer values
void get_acce_raw(int16_t* acce_raw);

//Read raw magnetometer values
void get_gyro_raw(int16_t* gyro_raw);

//Calibrate magnetometer
void mpu_calibration();

//Shift 8-bit values to 16-bit variable
void shift_buf_mag(uint8_t* buf_1, int16_t* buf_2, int len);

void shift_buf(uint8_t* buf_1, int16_t* buf_2, int len);

void get_mag_sensitivity(float* magCal_x, float* magCal_y, float* magCal_z);

void normalized_raw(int16_t* mag_raw, int16_t* acce_raw, int16_t* gyro_raw);

void MahonyQuaternionUpdate(int16_t* mag_raw, int16_t* acce_raw, int16_t* gyro_raw);
           
void get_rpy(float* roll, float* pitch, float* yaw);

#endif