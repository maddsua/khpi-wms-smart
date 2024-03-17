#include <Servo.h>

#define PIN_SERVO (9)

Servo servo;

void setup() {
	servo.attach(PIN_SERVO);
	servo.write(0);
}

const int servo_rot_angle = 180;
const int rot_resolution = 100;

const int rot_fwd_time = 10;
const int rot_back_time = 5;

const float step_fwd = ((float)servo_rot_angle / (rot_fwd_time * rot_resolution));
const float step_back = ((float)servo_rot_angle / (rot_back_time * rot_resolution));
const float step_delay = 1000 / rot_resolution;

void loop() {

	for (float i = 0; i < servo_rot_angle; i += step_fwd) {
		servo.write(i);
		delay(step_delay);
	}

	delay(3000);

	for (float i = 0; i < servo_rot_angle; i += step_back) {
		servo.write(servo_rot_angle - i);
		delay(step_delay);
	}
	
	delay(3000);
}
