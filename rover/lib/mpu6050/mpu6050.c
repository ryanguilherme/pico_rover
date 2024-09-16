#include "mpu6050.h"

void mpu6050_reset()
{
    uint8_t reset[] = {REG_PWR_MGMT_1, 0x80};
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, reset, 2, false);

    sleep_ms(200);

    uint8_t wake[] = {REG_PWR_MGMT_1, 0x00};
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, wake, 2, false);

    sleep_ms(200);
}

void mpu6050_port_configure()
{
    // Initialize chosen serial port
    stdio_init_all();

    // Initialize I2C
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SCL_PIN);
}

void mpu6050_sensors_configure()
{
    // Set accelerometer range
    uint8_t accel_config[] = {REG_ACCEL_CONFIG, ACCEL_CONFIG_VALUE};
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, accel_config, 2, false);

    // Set gyroscope range
    uint8_t gyro_config[] = {REG_GYRO_CONFIG, GYRO_CONFIG_VALUE};
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, gyro_config, 2, false);

    // Set sample rate
    uint8_t sample_rate[] = {REG_SMPLRT_DIV, SAMPLE_RATE_DIV};
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, sample_rate, 2, false);
}

void mpu6050_read_raw(mpu6050_data_t *data)
{
    uint8_t buf[14];
    uint8_t reg = REG_ACCEL_XOUT_H;

    // Escreve o registro inicial de leitura
    int ret = i2c_write_blocking(I2C_PORT, MPU6050_ADDR, &reg, 1, true);
    if (ret < 0)
    {
        printf("Falha na escrita I2C: %d\n", ret);
    }

    // Lê os 14 bytes (acelerômetro, temperatura e giroscópio)
    ret = i2c_read_blocking(I2C_PORT, MPU6050_ADDR, buf, 14, false);
    if (ret < 0)
    {
        printf("Falha na leitura I2C: %d\n", ret);
    }

    // Combina os valores altos e baixos para os dados do acelerômetro
    data->accel_x = (buf[0] << 8) | buf[1];
    data->accel_y = (buf[2] << 8) | buf[3];
    data->accel_z = (buf[4] << 8) | buf[5];
    data->temp = (buf[6] << 8) | buf[7];
    data->gyro_x = (buf[8] << 8) | buf[9];
    data->gyro_y = (buf[10] << 8) | buf[11];
    data->gyro_z = (buf[12] << 8) | buf[13];
}

void mpu6050_init()
{
    // Reset and configure MPU6050
    mpu6050_port_configure();
    mpu6050_reset();
    mpu6050_sensors_configure();

    uint8_t who_am_i = 0;
    uint8_t reg = WHO_AM_I_REG;

    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, MPU6050_ADDR, &who_am_i, 1, false);

    sleep_ms(200);

    printf("MPU6050 WHO_AM_I: 0x%02X\n", who_am_i);

    sleep_ms(200);

    if (who_am_i != 0x72)
    {
        printf("MPU6050 not found!\n");
        while (1)
        {
            printf("Não foi possível ler o dispositivo\n");
            sleep_ms(1000);
        }
    }
}

void mpu6050_print_raw_data(mpu6050_data_t data)
{
    mpu6050_read_raw(&data);

    // Convert raw accelerometer values to g
    float accel_g[3];
    accel_g[0] = data.accel_x / ACCEL_SCALE_FACTOR;
    accel_g[1] = data.accel_y / ACCEL_SCALE_FACTOR;
    accel_g[2] = data.accel_z / ACCEL_SCALE_FACTOR;

    // Convert raw gyroscope values to degrees per second
    float gyro_dps[3];
    gyro_dps[0] = data.gyro_x / GYRO_SCALE_FACTOR;
    gyro_dps[1] = data.gyro_y / GYRO_SCALE_FACTOR;
    gyro_dps[2] = data.gyro_z / GYRO_SCALE_FACTOR;

    // Print converted values
    printf("aX = %.2f g | aY = %.2f g | aZ = %.2f g \n", accel_g[0], accel_g[1], accel_g[2]);

    printf("gX = %.2f dps | gY = %.2f dps | gZ = %.2f dps | \n", gyro_dps[0], gyro_dps[1], gyro_dps[2]);
}