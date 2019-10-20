#include "MPU.h"

//Initialise and power ON, MPU9250
esp_err_t write_byte(i2c_port_t i2c_num,int8_t main_add, int8_t reg_add, int8_t data){
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, ( main_add << 1 ) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, reg_add, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, data, ACK_CHECK_EN);
    vTaskDelay(10/portTICK_RATE_MS);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t write_to_mag(int8_t sub_address, int8_t* data){
    esp_err_t ret = write_byte(I2C_MASTER_NUM, MPU9250_ADDR, I2C_SLV0_ADDR,MAG_ADDR);
    ret=write_byte(I2C_MASTER_NUM, MPU9250_ADDR, I2C_SLV0_REG, sub_address);
    ret=write_byte(I2C_MASTER_NUM, MPU9250_ADDR, I2C_SLV0_DO, data);
    ret=write_byte(I2C_MASTER_NUM, MPU9250_ADDR, I2C_SLV0_CTRL, I2C_SLV0_EN | (uint8_t)1);
    return ret;
}

esp_err_t read_byte(i2c_port_t i2c_num,int8_t main_add, int8_t reg_add, uint8_t* data_rd, size_t size){
    if (size == 0) {
        return ESP_OK;
    }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, ( main_add << 1 ) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, reg_add, ACK_CHECK_EN);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, ( main_add << 1 ) | READ_BIT, ACK_CHECK_EN);
    if (size > 1) {
        i2c_master_read(cmd, data_rd, size - 1, ACK_VAL);
    }
    i2c_master_read_byte(cmd, data_rd + size - 1, NACK_VAL);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t read_from_mag(int8_t sub_address, int8_t count, uint8_t* data){
    esp_err_t ret = write_byte(I2C_MASTER_NUM, MPU9250_ADDR, I2C_SLV0_ADDR, MAG_ADDR | I2C_SLV0_EN);
    ret = write_byte(I2C_MASTER_NUM, MPU9250_ADDR, I2C_SLV0_REG, sub_address);
    ret = write_byte(I2C_MASTER_NUM, MPU9250_ADDR, I2C_SLV0_CTRL, I2C_SLV0_EN | count);
    ret = read_byte(I2C_MASTER_NUM, MPU9250_ADDR, EXT_SENSE_DATA_00, data, count);
    return ret;
}   

esp_err_t mpu9250_init(i2c_port_t i2c_num){
    esp_err_t ret = write_byte(i2c_num,MPU9250_ADDR, PWR_MGMT_1,0x01);
    ret = write_byte(i2c_num, MPU9250_ADDR, USER_CTRL, 0x20);
    ret = write_byte(i2c_num, MPU9250_ADDR, I2C_MST_CTRL, 0x0D);
    ret = write_byte(i2c_num, MPU9250_ADDR, INT_PIN_CFG, 0x02);
    write_to_mag(CNTL_1, 0x00);
    write_to_mag(CNTL_1, 0x16);
    return ret;
}

esp_err_t mpu9250_read_mag(i2c_port_t i2c_num, uint8_t* data_rd, size_t size){
    write_to_mag(CNTL_1, 0x00);
    esp_err_t ret = write_to_mag(CNTL_1, 0x16);
    read_from_mag(MAG_START_ADDR, 6, data_rd);
    return ret;
}

//Initialise the I2C bus and install driver to specified pins
void i2c_master_init(){
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    i2c_param_config(i2c_master_port, &conf);
    i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

//Proceed only when MPU is initialised
void start_mpu(){   
    int ret = mpu9250_init(I2C_MASTER_NUM);
    
    //CHECK IF MPU IS ACTIVE
    while(ret != ESP_OK)     {
        //printf("INIT FAILED... Retry\n");
        vTaskDelay(100/ portTICK_RATE_MS);
        ret = mpu9250_init(I2C_MASTER_NUM);
    }
    //printf("INIT SUCESS...\n"); 
}

void shift_buf_mag(uint8_t* buf_1, int16_t* buf_2, int len){
    buf_2[0] = ((buf_1[1] << 8) + buf_1[0]);
    buf_2[1] = ((buf_1[3] << 8) + buf_1[2]);
    buf_2[2] = ((buf_1[5] << 8) + buf_1[4]);
}

void mag_calibration(){
    uint16_t ii = 0, sample_count = 128;
    float mag_offset[3] = {0, 0, 0}, mag_scale[3] = {0, 0, 0};
    int16_t mag_max[3] = {-32767, -32767, -32767}, mag_min[3] = {32767, 32767, 32767}, mag_temp[3] = {0, 0, 0};

    //printf("Mag Calibration: Wave device in a figure eight until done!\n");
    vTaskDelay(1000 / portTICK_RATE_MS);

    // shoot for ~fifteen seconds of mag data
    for(ii = 0; ii < sample_count; ii++){
        get_mag_raw(mag_temp);  // Read the mag data   
        if(!mag_temp[0] && !mag_temp[1])
            while(true) //printf("NEED RESET!!!\n");
        
        for (int jj = 0; jj < 3; jj++){
            if(mag_temp[jj] > mag_max[jj])  mag_max[jj] = mag_temp[jj];
            if(mag_temp[jj] < mag_min[jj])  mag_min[jj] = mag_temp[jj];
        }
        vTaskDelay(10 / portTICK_RATE_MS);  // at 100 Hz, new mag data is available every 10 ms
        //printf("Calibrating... (%d %%)\n",ii*100/sample_count);
    }
    //printf("mag_min :\t%d\t%d\n", mag_min[0], mag_min[1]);
    //printf("mag_max :\t%d\t%d\n", mag_max[0], mag_max[1]);
    
    // Get hard iron correction
    mag_offset[0]  = (mag_max[0] + mag_min[0]) / 2.0;  // get offset in x axis
    mag_offset[1]  = (mag_max[1] + mag_min[1]) / 2.0;  // get offset in y axis
    mag_offset[2]  = (mag_max[2] + mag_min[2]) / 2.0;  // get offset in z axis
    //printf("mag_offset:\t%f\t%f\n", mag_offset[0], mag_offset[1]);
    
    // Get soft iron correction estimate
    mag_scale[0]  = (mag_max[0] - mag_min[0]) / 2.0;  // get average x axis max chord length in counts
    mag_scale[1]  = (mag_max[1] - mag_min[1]) / 2.0;  // get average y axis max chord length in counts
    mag_scale[2]  = (mag_max[2] - mag_min[2]) / 2.0;  // get average z axis max chord length in counts

    float avg_rad = (mag_scale[0] + mag_scale[1] + mag_scale[2]) / 3.0;

    mag_scale[0] = avg_rad / mag_scale[0];   // mag scales in G
    mag_scale[1] = avg_rad / mag_scale[1];
    mag_scale[2] = avg_rad / mag_scale[2];
    //printf("mag_scale :\t%f\t%f\n", mag_scale[0], mag_scale[1]);

    //printf("Mag Calibration done!\n");
}

void get_mag_raw(int16_t* raw_value){
    uint8_t mag_rd[BUFF_SIZE];
    int ret = mpu9250_read_mag(I2C_MASTER_NUM, mag_rd, BUFF_SIZE);
    shift_buf_mag(mag_rd, raw_value, BUFF_SIZE/2);
}

void get_yaw(float* angle){
    double mx, my;
    int16_t mag_raw[BUFF_SIZE / 2];
    get_mag_raw(mag_raw);
    if(!mag_raw[0] && !mag_raw[1])  //Check if mpu requires re-initialization
        start_mpu();
    mx = (double)mag_raw[0] - offset_x;
    my = (double)mag_raw[1] - offset_y;
    mx *= scale_x;
    my *= scale_y;
    *angle = atan2(my,mx) * (180 / 3.141592654) + 180;
}
