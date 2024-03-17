#define PIN_LED_RED (8)
#define PIN_LED_GREEN (9)

#define PIN_LED_READY (10)
#define PIN_START_BUTTON (7)

void setup() {
	pinMode(PIN_LED_RED, OUTPUT);
	pinMode(PIN_LED_GREEN, OUTPUT);
	pinMode(PIN_LED_READY, OUTPUT);
	pinMode(PIN_START_BUTTON, INPUT_PULLUP);
}

void loop() {

	//  додав його просто щоб показати 
	//  що "цикл" завершено і програма готова розпочати новий
	if (digitalRead(PIN_START_BUTTON)) {
		digitalWrite(PIN_LED_READY, HIGH);
		return;
	}

	digitalWrite(PIN_LED_READY, LOW);

	digitalWrite(PIN_LED_RED, HIGH);
	digitalWrite(PIN_LED_GREEN, HIGH);

	delay(3000);
	digitalWrite(PIN_LED_RED, LOW);

	delay(4000);
	digitalWrite(PIN_LED_GREEN, LOW);
}
