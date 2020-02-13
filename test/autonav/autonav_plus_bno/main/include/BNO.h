#ifndef BNO_H
#define BNO_H

#include <stdio.h>
#include <math.h>
#include <time.h>
#include "esp_system.h"
#include "driver/i2c.h"

#define I2C_MASTER_SCL_IO    		16  		// gpio number for I2C master clock
#define I2C_MASTER_SDA_IO    		17    		// gpio number for I2C master data 
#define I2C_MASTER_NUM 				I2C_NUM_0   // I2C port number for master dev
#define I2C_MASTER_TX_BUF_DISABLE   0   		// I2C master do not need buffer
#define I2C_MASTER_RX_BUF_DISABLE   0   		// I2C master do not need buffer
#define I2C_MASTER_FREQ_HZ		    400000		// I2C master clock frequency

#define BNO_ADDR		    0x29    			// slave address for BH1750 sensor
#define MAG_ADDR 			0x0C
#define MAG_START_ADDR 		0x03				//magnetometer start address
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

esp_err_t write_byte(i2c_port_t i2c_num, int8_t main_add, int8_t add, int8_t data);

esp_err_t read_byte(i2c_port_t i2c_num,int8_t main_add, int8_t add, uint8_t* data_rd, size_t size);

void i2c_master_init();

void start_bno();

void shift_buf_mag(uint8_t* buf_1, int16_t* buf_2);

void get_yaw(float* x);

#endif