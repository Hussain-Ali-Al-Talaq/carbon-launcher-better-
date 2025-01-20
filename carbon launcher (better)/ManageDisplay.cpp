#include "ManageDisplay.h"

ManageDisplay::ManageDisplay() {
}

void ManageDisplay::displaywindow(std::vector<pair> pairs, std::string name, int selected,ManageInputs* Inputs,bool UpdateAll) {
	switch (window)
	{
	case Normal:
		NormalWindow(pairs, name, selected, UpdateAll);
		break;
	case Name:
		NameWindow(pairs, name, selected,
			 Inputs, UpdateAll);
		break;
	case Adding:
		break;
	case Deleting:
		break;
	default:
		break;
	}
}

void ManageDisplay::NormalWindow(std::vector<pair> pairs, std::string name, int selected,bool UpdateAll) {
	if (UpdateAll) {
		std::cout << "Name: " << name << "\n" << "\n";

		for (int i = 0; i < pairs.size(); i++) {
			std::cout << "   " << pairs[i].name << "\n";
		}
		std::cout << "\n";


		std::cout << "   Change Name" << "\n";
		std::cout << "   Add version" << "\n";
		std::cout << "   delete version" << "\n";

		oldCursorY = 1;

		util::ChangeLetter(">"[0], 1, 2); //add the cursor at the begining 
	}
	else {

		if (selected > pairs.size() - 1) { //offset for the setting being a space apart
			selected++; 
		}

		selected = selected + 2; //name offset

		util::ChangeLetter(" "[0], 1, oldCursorY); //remove the old one 

		util::ChangeLetter(">"[0], 1, selected);
		oldCursorY = selected;
	}
}


void ManageDisplay::NameWindow(std::vector<pair> pairs, std::string name, int selected,ManageInputs* Inputs, bool UpdateAll) {
	int nameoffset = 6; // 6 is an offset for "Name: "


	if (UpdateAll) {
		system("cls");
		std::cout << "Name: " << name;

		NameTextBox = new TextBox(nameoffset, 0, name);
	}
	else {
		NameTextBox->Update(Inputs);
		if (CallbackFunc != NULL) {
			CallbackFunc("dddd");
		}
	}
}

windowtype ManageDisplay::getWindow() {
	return window;
}

void ManageDisplay::ChangeWindow(windowtype newWindow) {
	window = newWindow;
}

void ManageDisplay::UpdateNameCallback(std::function<void(std::string)> Func) {
	CallbackFunc = Func;
}