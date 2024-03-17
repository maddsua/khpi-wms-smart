
#define PIN_LED_RED (8)
#define PIN_LED_GREEN (9)
#define PIN_START_BUTTON (7)

void setup() {
	pinMode(PIN_LED_RED, OUTPUT);
	pinMode(PIN_LED_GREEN, OUTPUT);
	pinMode(PIN_START_BUTTON, INPUT_PULLUP);
}

bool buttonLocked = false;
uint8_t loopState = 0;

void actionCallback() {

	loopState++;
	if (loopState > 2) {
		loopState = 0;
	}

	switch (loopState) {

		case 1: {
			digitalWrite(PIN_LED_RED, HIGH);
		} break;

		case 2: {

			const auto pulse = []() {
				digitalWrite(PIN_LED_GREEN, HIGH);
				delay(1500);
				digitalWrite(PIN_LED_GREEN, LOW);
			};

			for (size_t i = 0; i < 4; i++) {
				pulse();
				delay(500);
			}

		} break;

		default: {
			digitalWrite(PIN_LED_RED, LOW);
		}
	}
}

void loop() {

	const auto buttonPresssed = !digitalRead(PIN_START_BUTTON);

	if (buttonPresssed && !buttonLocked) {
		buttonLocked = true;
		actionCallback();
	} else if (!buttonPresssed && buttonLocked) {
		buttonLocked = false;
	}
}
