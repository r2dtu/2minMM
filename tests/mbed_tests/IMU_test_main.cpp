#include "mbed.h"
#include "MPU6050.h"

Serial pc(SERIAL_TX, SERIAL_RX);

DigitalOut myLed(LED1);

// (SDA, SCL)
MPU6050 ark(PB_7, PB_6);

int main() {
    
    while (1) {
        // Read temperature
        float temp = ark.getTemp();
        pc.printf("temperature = %0.2f \r\n", temp);
        
        // Read gyroscope
        float gyro[3];
        ark.getGyro(gyro);
        pc.printf("GyroX: %f, GyroY: %f, GyroZ: %f\r\n", gyro[0], gyro[1], gyro[2]);
        
        // Read accelerometer
        float accel[3];
        ark.getAccelero(accel);
        pc.printf("AccelX: %f, AccelY: %f, AccelZ: %f\r\n", accel[0], accel[1], accel[2]);
        
        wait(0.1);
    }
}
