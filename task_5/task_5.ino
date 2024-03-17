#define PIN_LED (A0)
#define PIN_START_BUTTON (7)

void setup() {
	pinMode(PIN_LED, OUTPUT);
	pinMode(PIN_START_BUTTON, INPUT_PULLUP);
	Serial.begin(9600);
}

bool buttonLocked = false;
int ledState = 0;
bool incrementDirection = true;

void increment() {
	if (incrementDirection) {
		ledState += 0xff / 3;
	} else {
		ledState -= 0xff / 5;
	}
}

void actionCallback() {

	increment();

	if (ledState > 0xff || ledState < 0x00) {
		ledState = ledState > 0 ? 0xff : 0x00;
		incrementDirection = !incrementDirection;
		increment();
	}

	analogWrite(PIN_LED, ledState);

	//	просто щоб показати значення,
	//	бо симулятор не має рівнів яскарвості
	char outBuff[20];
	int percentage = ((float)ledState / 0xff) * 100;
	snprintf(outBuff, sizeof(outBuff), "Duty: %i %%\n", percentage);
	Serial.print(outBuff);
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
