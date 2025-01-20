#pragma once
#include <iostream>
#include "util.h"
#include "ManageInputs.h"
#include <conio.h>
#include <stdio.h>



class TextBox
{
public:
	TextBox(int xPosition, int yPosition,std::string text);
	
	void Update(ManageInputs* Inputs);

private:
	int xPosition;
	int yPosition;

	std::string text;

	int CursorX;
	const static int ExcludeSize = 23;
	const char ExcludeList[ExcludeSize]{ VK_RIGHT,VK_LEFT,VK_UP,VK_DOWN,'.','/',"'"[0],'"','!','@','#','$','%','^','&','*','(',')','=','+','\r','\b',0};

	void UpdateCursor(ManageInputs* Inputs);
	void HandleDeleteLetter(ManageInputs* Inputs);
	void HandleAddLetter(ManageInputs* Inputs);
};

