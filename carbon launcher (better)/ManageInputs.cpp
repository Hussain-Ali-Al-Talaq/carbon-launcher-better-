#include "ManageInputs.h"

ManageInputs::ManageInputs() {
	keyStates = new KeyState[KeysNumber];

	for (int i = 0; i < KeysNumber; i++) {
		keyStates[i].key = i;
	}
	thread = new InputThread;
}

void ManageInputs::updateKeys() {
	long long elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch() - LastUpdateTime).count();
	LastUpdateTime = std::chrono::system_clock::now().time_since_epoch();

	for (int i = 0; i < KeysNumber; i++) {
		updatekey(i, elapsed_ms);
	}
}


void ManageInputs::updatekey(int key,long long elapsed_ms) {
	if (key < 0) return;

	bool KeyDown = (GetKeyState(key) >> 15) && 8000;
	bool KeyToggled = (GetKeyState(key) << 15) && 8000;

	if (key == VK_CAPITAL) { //capital toggle case
		keyStates[key].toggled = KeyToggled;
	}

	if (KeyDown) {
		if (!keyStates[key].status == Status::released)
		{
			keyStates[key].status = Status::hold;
			keyStates[key].HoldTime += elapsed_ms;
		}
		else
		{
			keyStates[key].status = Status::pressed;
		}
	}
	else {
		keyStates[key].status = Status::released;
		keyStates[key].HoldTimeStarted = false;
		keyStates[key].HoldTime = 0;
		keyStates[key].burst = false;
	}

	if (keyStates[key].HoldTimeStarted) {
		if (keyStates[key].HoldTime >= burstInbetweenTime) {
			keyStates[key].HoldTime -= burstInbetweenTime;
			keyStates[key].burst = true;
		}
		else {
			keyStates[key].burst = false;
		}
	}
	else if(keyStates[key].HoldTime >= burstStartTime){
		keyStates[key].HoldTime -= burstStartTime;
		keyStates[key].HoldTimeStarted = true;
	}
}

Status ManageInputs::GetKey(Keys key) {
	return keyStates[key].status;
}

bool ManageInputs::GetKeyPressed(Keys key) {
	return keyStates[key].status == pressed || keyStates[key].burst;
}

wchar_t ManageInputs::GetAnyKeyPressed() {
	thread->initialize();

	wchar_t line = thread->GetKeyIfAvalible();

	if (line != 0) {
		return line;
	}
	return 0;
}

void InputThread::Get() {
	while(true){
		if (!GotLine) {
			HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
			SetConsoleMode(handle, DISABLE_NEWLINE_AUTO_RETURN);

			DWORD read = 0;
			char buf;

			ReadConsoleA(handle, &buf, 1, &read, NULL);

			if (read > 0) { //new char
				*line[0] = buf;
				GotLine = true;
			}
		}
	}
}

wchar_t InputThread::GetKeyIfAvalible()
{	
	if (GotLine)
	{	
		wchar_t tmpline = *line[0]; //copy so it doesn't get rewriten by the thread
		GotLine = false;
		return tmpline;
	}
	else {
		return 0;
	}

	
}
void InputThread::initialize() {
	if (!initialized) {
		*line = new wchar_t[2];
		std::thread t(&InputThread::Get, this);
		t.detach();

		initialized = true;
	}
}

