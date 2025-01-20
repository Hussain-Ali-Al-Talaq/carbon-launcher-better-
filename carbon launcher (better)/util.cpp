#include "util.h"

util::util() {
}

void util::ChangeLetter(char letter, int x, int y) {
	ChangeWord(&letter, 1, x, y);
}
void util::ChangeWord(char* word, int len, int x, int y) {
	COORD wordpos = { x,y };
	DWORD writen;
	WriteConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), word, len, wordpos, &writen);
}

void util::setCursorPosition(int x, int y)
{
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int* util::SetActiveCursorPosition(int x, int y) {
	static int cursorpos[2];

	if (x != -1 && y != -1) {
		cursorpos[0] = x;
		cursorpos[1] = y;
	}
	return cursorpos;
}
void util::GoToActiveCursorPosition() {
	int* pos = SetActiveCursorPosition(-1, -1);
	setCursorPosition(pos[0], pos[1]);
}
