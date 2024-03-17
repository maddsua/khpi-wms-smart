#define PIN_LED_RED (8)
#define PIN_LED_GREEN (9)
#define PIN_START_BUTTON (7)

class StateMachine {
	private:

		struct State {
			bool red;
			bool green;
		};

		inline static const State m_sequence[] = {
			{ false, false },
			{ true, false },
			{ true, true },
			{ false, true }
		};

		inline static const uint8_t m_len = sizeof(m_sequence) / sizeof(State);
		uint8_t m_idx = 0;

	public:

		void next() {

			const auto hasNext = this->m_idx < this->m_len - 1;
			this->m_idx = hasNext ? this->m_idx + 1 : 0;

			const auto nextState = this->m_sequence[this->m_idx];

			digitalWrite(PIN_LED_RED, nextState.red);
			digitalWrite(PIN_LED_GREEN, nextState.green);
		}
};

class Button {
	public:
		using FunctionType = void(*)();

	private:
		uint8_t m_dpin;
		FunctionType m_cb;
		bool m_locked = false;

	public:
		Button() = delete;
		Button(int buttonPin, FunctionType callback) {
			this->m_dpin = buttonPin;
			this->m_cb = callback;
		}

		void update() {

			const auto nextState = digitalRead(this->m_dpin);
			const auto nextActive = !nextState;

			if (nextActive && !this->m_locked) {
				this->m_locked = true;
				this->m_cb();
			} else if (!nextActive && this->m_locked) {
				this->m_locked = false;
			}
		}
};

StateMachine sm;

void stepSm() {
	sm.next();
}

Button push_button(PIN_START_BUTTON, &stepSm);

void setup() {
	pinMode(PIN_LED_RED, OUTPUT);
	pinMode(PIN_LED_GREEN, OUTPUT);
	pinMode(PIN_START_BUTTON, INPUT_PULLUP);
}

void loop() {

	push_button.update();

}
