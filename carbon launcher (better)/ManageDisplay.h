#pragma once
#include "handlefile.h"
#include "ManageInputs.h"
#include "Windows.h"
#include "util.h"
#include "TextBox.h"
#include <functional>


enum windowtype
{
	Main,
	Name,
	Adding,
	Deleting,
};

class ManageDisplay
{
public:
	ManageDisplay();

	void displaywindow(ManageInputs* Inputs, std::vector<pair> pairs,std::string name);
	void ChangeWindow(windowtype newWindow);

	//helper funcs
	windowtype getWindow(); 

	void SetNameCallback(std::function<void(std::string)> func);
	void SetDeleteCallback(std::function<void(int)> func);
private:
	windowtype window = Main;

	bool WindowChanged = true;
	bool ReprintWindow = false;

	const int nameYOffset = 2;

	int CursorY;
	int CursorX;

	TextBox* NameTextBox;


	void OptionsWindow(ManageInputs* Inputs, std::vector<pair> pairs, std::vector<std::string> settings, std::string name, char pointer);

	void NormalWindow(ManageInputs* Inputs, std::vector<pair> pairs, std::string name);
	void NameWindow(ManageInputs* Inputs, std::vector<pair> pairs, std::string name);
	void DeleteWindow(ManageInputs* Inputs, std::vector<pair> pairs, std::string name);

	std::function<void(std::string)> NameCallback;
	std::function<void(int)> DeleteCallback;

	//helper funcs
	bool UpdateYCursor(ManageInputs* Inputs, int minValue, int maxValue);
};

