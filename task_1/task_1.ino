#define PIN_LED_RED (8)
#define PIN_LED_GREEN (9)

void setup() {
	pinMode(PIN_LED_RED, OUTPUT);
	pinMode(PIN_LED_GREEN, OUTPUT);
}

void loop() {
	delay(5000);
	digitalWrite(PIN_LED_RED, HIGH);
	digitalWrite(PIN_LED_GREEN, HIGH);

	delay(3000);
	digitalWrite(PIN_LED_RED, LOW);

	delay(4000);
	digitalWrite(PIN_LED_GREEN, LOW);
}
