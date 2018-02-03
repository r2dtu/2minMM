/*
 * File: PID_Control.c
 * Author: Clark Phan & David Tu
 * Last Updated: February 3, 2018
 * Description: 
 */

double error_prior = 0;
double totalError = 0;
unsigned long iteration_time = 0;

int PID_Control() {
  float correction;
  float encoderError = leftEncoder.getPulses() - rightEncoder.getPulses();
  float gyroError = gyro.read() - gyroSetPoint;

  /* Deal with both errors together, or separately? */

  totalError = totalError + (error*iteration_time);
  derivative = (error – error_prior)/iteration_time;
  correction = Kp * error + Ki * totalError + Kd * derivative + bias;

  error_prior = error;

  return correction;
}

