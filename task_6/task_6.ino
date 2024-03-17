#define PIN_DRIVER_ENABLE (9)
#define PIN_DRIVER_REVERSE (8)

#define PIN_FORWARD_BUTTON (6)
#define PIN_BACKWARD_BUTTON (7)
#define PIN_STOP_BUTTON (5)

class Button {
	public:
		using FunctionType = void(*)();

	private:
		uint8_t m_dpin;
		FunctionType m_cb;
		unsigned long m_bounced = 0;
		bool m_prev_state = false;

	public:
		static const int debounce_time = 50;

		Button() = delete;
		Button(int buttonPin, FunctionType callback) {
			this->m_dpin = buttonPin;
			this->m_cb = callback;
		}

		void update() {

			const auto nextState = !digitalRead(this->m_dpin);
			if (this->m_prev_state == nextState) {
				return;
			}

			const auto mill_now = millis();
			if (this->m_bounced + debounce_time < mill_now) {
				this->m_cb();
			}

			this->m_bounced = millis();
		}
};

void setup() {

	pinMode(PIN_DRIVER_ENABLE, OUTPUT);
	pinMode(PIN_DRIVER_REVERSE, OUTPUT);

	pinMode(PIN_FORWARD_BUTTON, INPUT_PULLUP);
	pinMode(PIN_BACKWARD_BUTTON, INPUT_PULLUP);
	pinMode(PIN_STOP_BUTTON, INPUT_PULLUP);
}

void callback_forward() {
	digitalWrite(PIN_DRIVER_ENABLE, HIGH);
	digitalWrite(PIN_DRIVER_REVERSE, LOW);
}

void callback_backward() {
	digitalWrite(PIN_DRIVER_ENABLE, HIGH);
	digitalWrite(PIN_DRIVER_REVERSE, HIGH);
}
void callback_stop() {
	digitalWrite(PIN_DRIVER_ENABLE, LOW);
	digitalWrite(PIN_DRIVER_REVERSE, LOW);
}

Button btn_push_sensor(PIN_FORWARD_BUTTON, &callback_forward);
Button btn_start(PIN_BACKWARD_BUTTON, &callback_backward);
Button btn_stop(PIN_STOP_BUTTON, &callback_stop);

void loop() {
	btn_push_sensor.update();
	btn_start.update();
	btn_stop.update();
}
