#include "mpu6050.h"

#include "driver/i2c.h"
#include "esp_log.h"
#include "esp_system.h"
#include "unity.h"

static mpu6050_handle_t mpu6050 = NULL;

void
test_i2c_bus_init ()
{
  i2c_config_t conf = {
    .mode = I2C_MODE_MASTER,
    .sda_io_num = (gpio_num_t)21,
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .scl_io_num = (gpio_num_t)22,
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .master.clk_speed = 100000,
    .clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL,
  };

  esp_err_t ret;

  ret = i2c_param_config (I2C_NUM_0, &conf);
  TEST_ASSERT_EQUAL_MESSAGE (ESP_OK, ret, "I2C config returned error");

  ret = i2c_driver_install (I2C_NUM_0, conf.mode, 0, 0, 0);
  TEST_ASSERT_EQUAL_MESSAGE (ESP_OK, ret, "I2C install returned error");
}

void
test_i2c_bus_delete ()
{
  esp_err_t ret;

  ret = i2c_driver_delete (I2C_NUM_0);
  TEST_ASSERT_EQUAL_MESSAGE (ESP_OK, ret, "I2C driver delete returned error");
}

void
test_mpu6050_init ()
{
  esp_err_t ret;

  mpu6050 = mpu6050_create (I2C_NUM_0, MPU6050_I2C_ADDRESS);
  TEST_ASSERT_NOT_NULL_MESSAGE (mpu6050, "MPU6050 create returned NULL");

  ret = mpu6050_config (mpu6050, ACCE_FS_4G, GYRO_FS_500DPS);
  TEST_ASSERT_EQUAL_MESSAGE (ESP_OK, ret, "MPU6050 config returned error");

  ret = mpu6050_wake_up (mpu6050);
  TEST_ASSERT_EQUAL_MESSAGE (ESP_OK, ret, "MPU6050 wake up returned error");
}

void
test_mpu6050_accelerometer ()
{
  esp_err_t ret;
  uint8_t mpu6050_deviceid;
  mpu6050_acce_value_t acce;

  test_mpu6050_init ();

  ret = mpu6050_get_deviceid (mpu6050, &mpu6050_deviceid);
  TEST_ASSERT_EQUAL (ESP_OK, ret);
  TEST_ASSERT_EQUAL_UINT8_MESSAGE (MPU6050_WHO_AM_I_VAL, mpu6050_deviceid,
                                   "MPU6050 device ID is not correct");

  ret = mpu6050_get_acce (mpu6050, &acce);
  TEST_ASSERT_EQUAL (ESP_OK, ret);

  mpu6050_delete (mpu6050);
}

void
test_mpu6050_gyroscope ()
{
  esp_err_t ret;
  uint8_t mpu6050_deviceid;
  mpu6050_gyro_value_t gyro;

  test_mpu6050_init ();

  ret = mpu6050_get_deviceid (mpu6050, &mpu6050_deviceid);
  TEST_ASSERT_EQUAL (ESP_OK, ret);
  TEST_ASSERT_EQUAL_UINT8_MESSAGE (MPU6050_WHO_AM_I_VAL, mpu6050_deviceid,
                                   "MPU6050 device ID is not correct");

  ret = mpu6050_get_gyro (mpu6050, &gyro);
  TEST_ASSERT_EQUAL (ESP_OK, ret);

  mpu6050_delete (mpu6050);
}

void
test_mpu6050_temperature ()
{
  esp_err_t ret;
  uint8_t mpu6050_deviceid;
  mpu6050_temp_value_t temp;

  test_mpu6050_init ();

  ret = mpu6050_get_deviceid (mpu6050, &mpu6050_deviceid);
  TEST_ASSERT_EQUAL (ESP_OK, ret);
  TEST_ASSERT_EQUAL_UINT8_MESSAGE (MPU6050_WHO_AM_I_VAL, mpu6050_deviceid,
                                   "MPU6050 device ID is not correct");

  ret = mpu6050_get_temp (mpu6050, &temp);
  TEST_ASSERT_EQUAL (ESP_OK, ret);

  mpu6050_delete (mpu6050);
}

void
app_main ()
{
  UNITY_BEGIN ();
  RUN_TEST (test_i2c_bus_init);
  RUN_TEST (test_mpu6050_init);
  RUN_TEST (test_mpu6050_accelerometer);
  RUN_TEST (test_mpu6050_gyroscope);
  RUN_TEST (test_mpu6050_temperature);
  RUN_TEST (test_i2c_bus_delete);
  UNITY_END ();
}