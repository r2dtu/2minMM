/*
 * File: PID_Control.c
 * Author: Clark Phan & David Tu
 * Last Updated: February 3, 2018
 * Description: 
 */
#include "PID_Control.h"

double error_prior = 0;
double totalError = 0;
unsigned long iteration_time = 0;

// Will change depending on which way we want to turn
float encoderSetPoint;
float gyroSetPoint;
float accelSetPoint;

int PID_Control() {
  float correction;

  // Drive straight example
  float encoderError = leftEncoder.getPulses() - rightEncoder.getPulses();
  float gyroError = gyro.read() - gyroSetPoint;
  float accelError = accel.read() - accelSetPoint;

  /* Deal with both errors together, or separately? */

  // Calculate total error for PID
  totalError = totalError + (error * iteration_time);
  derivative = (error – error_prior) / iteration_time;

  // Calculate correction
  correction = Kp * error + Ki * totalError + Kd * derivative + bias;

  // Record current error for next iteration
  error_prior = error;

  return correction;
}

