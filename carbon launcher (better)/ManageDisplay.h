#pragma once
#include "handlefile.h"
#include "ManageInputs.h"
#include "Windows.h"
#include "util.h"
#include "TextBox.h"
#include <functional>


enum windowtype
{
	Normal,
	Name,
	Adding,
	Deleting,
};

class ManageDisplay
{
public:
	ManageDisplay();

	void displaywindow(std::vector<pair> pairs,std::string name,ManageInputs* Inputs);
	void ChangeWindow(windowtype newWindow);

	//helper funcs
	windowtype getWindow(); 
	void UpdateNameCallback(std::function<void(std::string)> func);
private:
	windowtype window = Normal;

	bool WindowChanged = true;

	int CursorY;
	int CursorX;

	TextBox* NameTextBox;


	void NormalWindow(std::vector<pair> pairs, std::string name, ManageInputs* Inputs);
	void NameWindow(std::vector<pair> pairs, std::string name,ManageInputs* Inputs);

	std::function<void(std::string)> CallbackFunc;
};

