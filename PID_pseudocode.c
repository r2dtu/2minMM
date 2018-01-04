double error_prior, integral, Kp, Ki, Kd, bias;
unsigned long iteration_time = 0;

/*Set function for values*/
void SetTunings(double kp, double Ki, double Kd, double dv, unsigned long it) {
   Kp = kp;
   Ki= ki;
   Kd = kd;
   desired_value = dv;
   bias = b; //value <1 to prevent output from being 0
   iteration_time = it; //time between iterations
}

while(1) {
   error = desired_value – actual_value; //actual_value would come from sensor
   integral = integral + (error*iteration_time);
   derivative = (error – error_prior)/iteration_time;
   /*output is used to check if everything is tuned well*/
   output = Kp*error + Ki*integral + Kd*derivative + bias;
   error_prior = error;
   sleep(iteration_time);
}

