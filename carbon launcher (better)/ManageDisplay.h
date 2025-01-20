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

	void displaywindow(std::vector<pair> pairs,std::string name, int selected,ManageInputs* Inputs, bool UpdateAll);
	void ChangeWindow(windowtype newWindow);

	//heleper funcs
	windowtype getWindow(); 
	void UpdateNameCallback(std::function<void(std::string)> func);
private:
	windowtype window = Normal;


	std::string namecopy;
	int oldCursorY;
	int CursorX;

	TextBox* NameTextBox;


	void NormalWindow(std::vector<pair> pairs, std::string name, int selected, bool UpdateAll);
	void NameWindow(std::vector<pair> pairs, std::string name, int selected,ManageInputs* Inputs, bool UpdateAll);

	std::function<void(std::string)> CallbackFunc;
};

