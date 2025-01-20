#pragma once
#include "Windows.h"
#include <iostream>
#include <conio.h>
#include "util.h"
#include "thread"

enum Keys
{
	UpArrow = VK_UP,
	DownArrow = VK_DOWN,
	Enter = VK_RETURN,
	DeleteKey = VK_DELETE,
	BackSpace = VK_BACK,
	RightArrow = VK_RIGHT,
	LeftArrow = VK_LEFT,
};
enum Status
{
	released,
	pressed,
	hold
};

struct KeyState
{
	int key;
	Status status = released;
	bool toggled = false;
};

class InputThread {
public:
	void initialize();
	wchar_t GetKeyIfAvalible();
private:
	wchar_t* line[2];
	bool GotLine = false;

	void Get();

	bool initialized = false;
};


class ManageInputs
{
public:

	ManageInputs();
	//~ManageInputs();

	void updateKeys();

	Status GetKey(Keys);
	wchar_t GetAnyKeyPressed();
	
private:
	const static int KeysNumber = 256;
	KeyState* keyStates;
	void updatekey(int);

	char NumbersToSymbols[10]{'!','@','#','$','%','^','&','*','(',')'};
	InputThread* thread;
};
