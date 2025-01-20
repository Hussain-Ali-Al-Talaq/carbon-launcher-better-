#pragma once
#include <windows.h>
#include <iostream>

class util
{
public:
	util();

	static void ChangeLetter(char letter, int x, int y);
	static void ChangeWord(char* word,int len, int x, int y);
	static void setCursorPosition(int x, int y);
	static void GoToActiveCursorPosition();
	static int* SetActiveCursorPosition(int x, int y);
};

