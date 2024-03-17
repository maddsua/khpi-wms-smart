#define PIN_PUSH_SENSOR (6)
#define PIN_START_BUTTON (5)

#define PIN_LED_GREEN (7)
#define PIN_LED_RED (8)
#define PIN_MOTOR_ENABLE (9)

void setup() {

	pinMode(PIN_LED_GREEN, OUTPUT);
	pinMode(PIN_LED_RED, OUTPUT);
	pinMode(PIN_MOTOR_ENABLE, OUTPUT);

	pinMode(PIN_PUSH_SENSOR, INPUT_PULLUP);
	pinMode(PIN_START_BUTTON, INPUT_PULLUP);
}

#define STAGE_RESET -1
#define STAGE_NOOP 0
#define STAGE_INIT 1
#define STAGE_WORKING 2
#define STAGE_WAITING 3
#define STAGE_STOPPED 5

int activeStage = STAGE_RESET;
unsigned long stageTimer = 0;
bool buttonLocked = false;

void loop() {

	const auto sensorPressed = !digitalRead(PIN_PUSH_SENSOR);
	const auto buttonPresssed = !digitalRead(PIN_START_BUTTON);

	if (buttonPresssed && !buttonLocked && activeStage == STAGE_NOOP) {
		buttonLocked = true;
		activeStage = STAGE_INIT;
	} else if (!buttonPresssed && buttonLocked) {
		buttonLocked = false;
		return;
	}

	switch (activeStage) {

		case STAGE_RESET: {
			digitalWrite(PIN_MOTOR_ENABLE, LOW);
			digitalWrite(PIN_LED_GREEN, LOW);
			digitalWrite(PIN_LED_RED, LOW);
			activeStage = STAGE_NOOP;
		} break;

		case STAGE_INIT: {
			digitalWrite(PIN_MOTOR_ENABLE, HIGH);
			activeStage = STAGE_WORKING;
		} break;

		case STAGE_WORKING: {

			if (sensorPressed) {

				digitalWrite(PIN_MOTOR_ENABLE, LOW);
				digitalWrite(PIN_LED_GREEN, HIGH);

				activeStage = STAGE_WAITING;
				stageTimer = millis() + 5000;
			}

		} break;

		case STAGE_WAITING: {

			if (stageTimer < millis()) {

				digitalWrite(PIN_LED_GREEN, LOW);
				digitalWrite(PIN_LED_RED, HIGH);

				activeStage = STAGE_STOPPED;
				stageTimer = millis() + 3000;

			} else if (!sensorPressed) {
				activeStage = STAGE_RESET;
			}

		} break;

		case STAGE_STOPPED: {

			if (stageTimer < millis()) {
				activeStage = STAGE_RESET;
			}

		} break;
		
		default: break;
	}
}
