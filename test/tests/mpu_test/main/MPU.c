#include "MPU.h"

float q[4] = {1.0f, 0.0f, 0.0f, 0.0f};    // vector to hold quaternion
float deltat = 0.0f;          // integration interval for both filter schemes

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

esp_err_t mpu9250_read_acce(i2c_port_t i2c_num, uint8_t* data_rd, size_t size){
    esp_err_t ret = read_byte(i2c_num, MPU9250_ADDR, ACCE_START_ADDR, data_rd , size);
    return ret;
}

esp_err_t mpu9250_read_gyro(i2c_port_t i2c_num, uint8_t* data_rd, size_t size){
    esp_err_t ret = read_byte(i2c_num, MPU9250_ADDR, GYRO_START_ADDR, data_rd , size);
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
        printf("INIT FAILED... Retry\n");
        vTaskDelay(100/ portTICK_RATE_MS);
        ret = mpu9250_init(I2C_MASTER_NUM);
    }
    printf("INIT SUCESS...\n"); 
}

void get_mag_raw(int16_t* raw_value){
    uint8_t mag_rd[BUFF_SIZE];
    int ret = mpu9250_read_mag(I2C_MASTER_NUM, mag_rd, BUFF_SIZE);
    shift_buf_mag(mag_rd, raw_value, BUFF_SIZE/2);
}

void get_gyro_raw(int16_t* raw_value){
    uint8_t gyro_rd[BUFF_SIZE];
    int ret=mpu9250_read_gyro(I2C_MASTER_NUM, gyro_rd, BUFF_SIZE);
    shift_buf(gyro_rd, raw_value, BUFF_SIZE/2);
}

void get_acce_raw(int16_t* raw_value){
    uint8_t acce_rd[BUFF_SIZE];
    int ret=mpu9250_read_acce(I2C_MASTER_NUM, acce_rd, BUFF_SIZE);
    shift_buf(acce_rd, raw_value, BUFF_SIZE/2);
}

void shift_buf_mag(uint8_t* buf_1, int16_t* buf_2, int len){
    buf_2[0] = ((buf_1[1] << 8) + buf_1[0]);
    buf_2[1] = ((buf_1[3] << 8) + buf_1[2]);
    buf_2[2] = ((buf_1[5] << 8) + buf_1[4]);
}

void shift_buf(uint8_t* buf_1, int16_t* buf_2, int len){
    buf_2[0] = ((buf_1[0] << 8) + buf_1[1]);
    buf_2[1] = ((buf_1[2] << 8) + buf_1[3]);
    buf_2[2] = ((buf_1[4] << 8) + buf_1[5]);
}

void get_mag_sensitivity(float* magCal_x, float* magCal_y, float* magCal_z){
    uint8_t magSens[3] = {0, 0, 0};

    read_from_mag(0x10, 3, &magSens[0]);
    *magCal_x = (float)(magSens[0] - 128)/256. + 1.;
    *magCal_y = (float)(magSens[1] - 128)/256. + 1.;
    *magCal_z = (float)(magSens[2] - 128)/256. + 1.;
    printf("magCalibration : \t%f\t%f\t%f\n",*magCal_x, *magCal_y, *magCal_z);
}

void mpu_calibration(){
    uint16_t ii = 0, sample_count = 128;
    uint16_t  gyrosensitivity  = 131;   // = 131 LSB/degrees/sec
    uint16_t  accelsensitivity = 16384;  // = 16384 LSB/g
    float mag_offset[3] = {0, 0, 0}, mag_scale[3] = {0, 0, 0};
    float gyro_offset[3] = {0, 0, 0}, acce_offset[3] = {0, 0, 0};
    int16_t mag_max[3] = {-32767, -32767, -32767}, mag_min[3] = {32767, 32767, 32767}, mag_temp[3] = {0, 0, 0};
    int16_t gyro_max[3] = {-32767, -32767, -32767}, gyro_min[3] = {32767, 32767, 32767}, gyro_temp[3] = {0, 0, 0};
    int16_t acce_max[3] = {-32767, -32767, -32767}, acce_min[3] = {32767, 32767, 32767}, acce_temp[3] = {0, 0, 0};
    int64_t acce_sum[3] = {0, 0, 0}, gyro_sum[3] = {0, 0, 0};

    printf("Mag Calibration: Wave device in a figure eight until done!\n");
    vTaskDelay(1000 / portTICK_RATE_MS);

    // get_mag_sensitivity(magCalibration);     //already defined in .H
    
    // shoot for ~fifteen seconds of mag data
    for(ii = 0; ii < sample_count; ii++){
        get_mag_raw(mag_temp);   // Read the mag  data   
        get_gyro_raw(gyro_temp); // Read the gyro data
        get_acce_raw(acce_temp); // Read the acce data
        if(!mag_temp[0] && !mag_temp[1])
            while(true) printf("NEED RESET!!!\n");
        
        for (int jj = 0; jj < 3; jj++){
            if(mag_temp[jj] > mag_max[jj])
                mag_max[jj] = mag_temp[jj];
            if(mag_temp[jj] < mag_min[jj])  
                mag_min[jj] = mag_temp[jj]; 

            acce_sum[jj] += acce_temp[jj];
            gyro_sum[jj] += gyro_temp[jj];
        }
        vTaskDelay(10 / portTICK_RATE_MS);  // at 100 Hz, new mag data is available every 10 ms
        printf("Calibrating... (%d %%)\n",ii*100/sample_count);
    }    
    for(int k = 0; k < 3; k++)
    {
        acce_offset[k] = acce_sum[k] / 128;
        gyro_offset[k] = gyro_sum[k] / 128;
    }

    // if(acce_offset[2] > 0L) acce_offset[2] -= (int32_t) accelsensitivity;  // Remove gravity from the z-axis accelerometer bias calculation
    // else acce_offset[2] += (int32_t) accelsensitivity;

    for(int k = 0; k < 3; k++)
    {
        acce_offset[k] /= (float)accelsensitivity;
        gyro_offset[k] /= (float)gyrosensitivity;
    }

    printf("mag_min :\t%d\t%d\t%d\n", mag_min[0], mag_min[1], mag_min[2]);
    printf("mag_max :\t%d\t%d\t%d\n", mag_max[0], mag_max[1], mag_max[2]);
    
    // Get hard iron correction
    mag_offset[0]  = ((mag_max[0] + mag_min[0]) / 2.0 ) * mRes * magCalibration_x;  // get offset in x axis
    mag_offset[1]  = ((mag_max[1] + mag_min[1]) / 2.0 ) * mRes * magCalibration_y;  // get offset in y axis
    mag_offset[2]  = ((mag_max[2] + mag_min[2]) / 2.0 ) * mRes * magCalibration_z;  // get offset in z axis

    // Get soft iron correction estimate
    mag_scale[0]  = (mag_max[0] - mag_min[0]) / 2.0;  // get average x axis max chord length in counts
    mag_scale[1]  = (mag_max[1] - mag_min[1]) / 2.0;  // get average y axis max chord length in counts
    mag_scale[2]  = (mag_max[2] - mag_min[2]) / 2.0;  // get average z axis max chord length in counts

    float avg_rad = (mag_scale[0] + mag_scale[1] + mag_scale[2]) / 3.0;

    mag_scale[0] = avg_rad / mag_scale[0];   // mag scales in G
    mag_scale[1] = avg_rad / mag_scale[1];
    mag_scale[2] = avg_rad / mag_scale[2];

    printf("#define mag_offset_x %f\n#define mag_offset_y %f\n#define mag_offset_z %f\n", mag_offset[0], mag_offset[1], mag_offset[2]);
    printf("\n#define gyro_offset_x %f\n#define gyro_offset_y %f\n#define gyro_offset_z %f\n", gyro_offset[0], gyro_offset[1], gyro_offset[2]);
    printf("\n#define acce_offset_x %f\n#define acce_offset_y %f\n#define acce_offset_z %f\n", acce_offset[0], acce_offset[1], acce_offset[2]);
    printf("\n#define scale_x %f\n#define scale_y %f\n#define scale_z %f\n", mag_scale[0], mag_scale[1], mag_scale[2]);

    printf("Mag Calibration done!\n");
}

void normalized_raw(int16_t* mag_raw, int16_t* acce_raw, int16_t* gyro_raw){   
    get_acce_raw(acce_raw);
    get_mag_raw(mag_raw);
    get_gyro_raw(gyro_raw);

    mag_raw[0] = (mag_raw[0] * mRes * magCalibration_x - mag_offset_x) * scale_x;
    mag_raw[1] = (mag_raw[1] * mRes * magCalibration_y - mag_offset_y) * scale_y;
    mag_raw[2] = (mag_raw[2] * mRes * magCalibration_z - mag_offset_z) * scale_z;

    acce_raw[0] = (acce_raw[0] * aRes) + acce_offset_x;
    acce_raw[1] = (acce_raw[1] * aRes) + acce_offset_y;
    acce_raw[2] = (acce_raw[2] * aRes) + acce_offset_z;

    gyro_raw[0] *= gRes;
    gyro_raw[1] *= gRes;
    gyro_raw[2] *= gRes;

    gyro_raw[0] += gyro_offset_x;
    gyro_raw[1] += gyro_offset_y;
    gyro_raw[2] += gyro_offset_z;

    printf("roll = %f\t",(atan2(acce_raw[1], sqrt(acce_raw[0]*acce_raw[0] + acce_raw[2]*acce_raw[2]))*180/PI));
    printf("pitch = %f\t",(atan2(acce_raw[0], sqrt(acce_raw[1]*acce_raw[1] + acce_raw[2]*acce_raw[2]))*180/PI));
    printf("yaw = %f\n",(atan2((double)mag_raw[1],(double)mag_raw[0])*180/PI) + 180);
}

void MadgwickQuaternionUpdate(int16_t* mag_raw, int16_t* acce_raw, int16_t* gyro_raw){
    float GyroMeasError = PI * (4.0f / 180.0f);   // gyroscope measurement error in rads/s (start at 40 deg/s)
    float GyroMeasDrift = PI * (0.0f  / 180.0f);   // gyroscope measurement drift in rad/s/s (start at 0.0 deg/s/s)
    float beta = sqrt(3.0f / 4.0f) * GyroMeasError;   // compute beta
    float zeta = sqrt(3.0f / 4.0f) * GyroMeasDrift;
    float ax, ay, az, gx, gy, gz, mx, my, mz;
    float q1 = q[0], q2 = q[1], q3 = q[2], q4 = q[3];   // short name local variable for readability
    float norm;
    float hx, hy, _2bx, _2bz;
    float s1, s2, s3, s4;
    float qDot1, qDot2, qDot3, qDot4;

    ax = -acce_raw[0];
    ay = acce_raw[1];
    az = acce_raw[2];

    gx = gyro_raw[0] * PI / 180.0;
    gy = -gyro_raw[1] * PI / 180.0;
    gz = -gyro_raw[2] * PI / 180.0;

    mx = mag_raw[1];
    my = -mag_raw[0];
    mz = mag_raw[2];

    // Auxiliary variables to avoid repeated arithmetic
    float _2q1mx;
    float _2q1my;
    float _2q1mz;
    float _2q2mx;
    float _4bx;
    float _4bz;
    float _2q1 = 2.0f * q1;
    float _2q2 = 2.0f * q2;
    float _2q3 = 2.0f * q3;
    float _2q4 = 2.0f * q4;
    float _2q1q3 = 2.0f * q1 * q3;
    float _2q3q4 = 2.0f * q3 * q4;
    float q1q1 = q1 * q1;
    float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q1q4 = q1 * q4;
    float q2q2 = q2 * q2;
    float q2q3 = q2 * q3;
    float q2q4 = q2 * q4;
    float q3q3 = q3 * q3;
    float q3q4 = q3 * q4;
    float q4q4 = q4 * q4;

    // Normalise accelerometer measurement
    norm = sqrtf(ax * ax + ay * ay + az * az);
    if (norm == 0.0f) return; // handle NaN
    norm = 1.0f/norm;
    ax *= norm;
    ay *= norm;
    az *= norm;

    // Normalise magnetometer measurement
    norm = sqrtf(mx * mx + my * my + mz * mz);
    if (norm == 0.0f) return; // handle NaN
    norm = 1.0f/norm;
    mx *= norm;
    my *= norm;
    mz *= norm;

    // Reference direction of Earth's magnetic field
    _2q1mx = 2.0f * q1 * mx;
    _2q1my = 2.0f * q1 * my;
    _2q1mz = 2.0f * q1 * mz;
    _2q2mx = 2.0f * q2 * mx;
    hx = mx * q1q1 - _2q1my * q4 + _2q1mz * q3 + mx * q2q2 + _2q2 * my * q3 + _2q2 * mz * q4 - mx * q3q3 - mx * q4q4;
    hy = _2q1mx * q4 + my * q1q1 - _2q1mz * q2 + _2q2mx * q3 - my * q2q2 + my * q3q3 + _2q3 * mz * q4 - my * q4q4;
    _2bx = sqrtf(hx * hx + hy * hy);
    _2bz = -_2q1mx * q3 + _2q1my * q2 + mz * q1q1 + _2q2mx * q4 - mz * q2q2 + _2q3 * my * q4 - mz * q3q3 + mz * q4q4;
    _4bx = 2.0f * _2bx;
    _4bz = 2.0f * _2bz;

    // Gradient decent algorithm corrective step
    s1 = -_2q3 * (2.0f * q2q4 - _2q1q3 - ax) + _2q2 * (2.0f * q1q2 + _2q3q4 - ay) - _2bz * q3 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q4 + _2bz * q2) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q3 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
    s2 = _2q4 * (2.0f * q2q4 - _2q1q3 - ax) + _2q1 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q2 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + _2bz * q4 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q3 + _2bz * q1) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q4 - _4bz * q2) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
    s3 = -_2q1 * (2.0f * q2q4 - _2q1q3 - ax) + _2q4 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q3 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + (-_4bx * q3 - _2bz * q1) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q2 + _2bz * q4) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q1 - _4bz * q3) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
    s4 = _2q2 * (2.0f * q2q4 - _2q1q3 - ax) + _2q3 * (2.0f * q1q2 + _2q3q4 - ay) + (-_4bx * q4 + _2bz * q2) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q1 + _2bz * q3) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q2 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
    norm = sqrtf(s1 * s1 + s2 * s2 + s3 * s3 + s4 * s4);    // normalise step magnitude
    norm = 1.0f/norm;
    s1 *= norm;
    s2 *= norm;
    s3 *= norm;
    s4 *= norm;

    // Compute rate of change of quaternion
    qDot1 = 0.5f * (-q2 * gx - q3 * gy - q4 * gz) - beta * s1;
    qDot2 = 0.5f * (q1 * gx + q3 * gz - q4 * gy) - beta * s2;
    qDot3 = 0.5f * (q1 * gy - q2 * gz + q4 * gx) - beta * s3;
    qDot4 = 0.5f * (q1 * gz + q2 * gy - q3 * gx) - beta * s4;

    // Integrate to yield quaternion
    q1 += qDot1 * deltat;
    q2 += qDot2 * deltat;
    q3 += qDot3 * deltat;
    q4 += qDot4 * deltat;
    norm = sqrtf(q1 * q1 + q2 * q2 + q3 * q3 + q4 * q4);    // normalise quaternion
    norm = 1.0f/norm;
    q[0] = q1 * norm;
    q[1] = q2 * norm;
    q[2] = q3 * norm;
    q[3] = q4 * norm;
}

void get_rpy(float* roll, float* pitch, float* yaw){
    int16_t acce_raw[3], mag_raw[3], gyro_raw[3];
    float pitch_sum = 0, roll_sum = 0, yaw_sum = 0;
    int16_t Now, lastUpdate = 0;
    
    normalized_raw(&mag_raw, &acce_raw, &gyro_raw);

    for(uint8_t i = 0; i < 10; i++) { // iterate a fixed number of times per data read cycle
      Now = esp_timer_get_time();
      deltat = ((Now - lastUpdate)/1000000.0f); // set integration time by time elapsed since last filter update
      lastUpdate = Now;

      MadgwickQuaternionUpdate(mag_raw, acce_raw, gyro_raw);
    }
    
    for(int count = 0 ; count < 100 ; count++)
    {
        *yaw   = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);  
        *pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));
        *roll  = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);
        *pitch *= 180.0f / PI;
        *yaw   *= 180.0f / PI; 
        if(*yaw < 0) *yaw   += 360.0f; // Ensure yaw stays between 0 and 360
        *roll  *= 180.0f / PI;
        
        pitch_sum += *pitch;
        roll_sum += *roll;
        yaw_sum += *yaw;
    }
    *roll = roll_sum/100;
    *pitch = pitch_sum/100;
    *yaw = yaw_sum/100;
}