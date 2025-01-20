#include "ManageDisplay.h"

ManageDisplay::ManageDisplay() {
}

void ManageDisplay::displaywindow(std::vector<pair> pairs, std::string name,ManageInputs* Inputs) {
	

	switch (window)
	{
	case Normal:
		NormalWindow(pairs, name, Inputs);
		break;
	case Name:
		NameWindow(pairs, name, Inputs);
		break;
	case Adding:
		break;
	case Deleting:
		break;
	default:
		break;
	}
}

void ManageDisplay::NormalWindow(std::vector<pair> pairs, std::string name, ManageInputs* Inputs) {
	int nameYOffset = 2;

	//full window refresh
	if (WindowChanged) {
		WindowChanged = false;

		std::cout << "Name: " << name << "\n" << "\n";

		for (int i = 0; i < pairs.size(); i++) {
			std::cout << "   " << pairs[i].name << "\n";
		}
		std::cout << "\n";


		std::cout << "   Change Name" << "\n";
		std::cout << "   Add version" << "\n";
		std::cout << "   delete version" << "\n";

		CursorY = nameYOffset;

		util::ChangeLetter(">"[0], 1, CursorY); //add the cursor at the begining 
	}
	else {
		bool doUpdate = false;

		int oldCursorY = CursorY;

		if (oldCursorY > (pairs.size() - 1) + nameYOffset) { //offset for the setting being a space apart
			oldCursorY++; 
		}

		if (Inputs->GetKey(UpArrow) == pressed) {
			CursorY--;
			if (CursorY < nameYOffset) { 
				CursorY = nameYOffset;
			}
			else {
				doUpdate = !doUpdate;
			}
		}

		if (Inputs->GetKey(DownArrow) == pressed) {
			CursorY++;
			if (CursorY > (pairs.size() - 1) + 3 + nameYOffset) { // +3 is for the extra settings
				CursorY = (pairs.size() - 1) + 3 + nameYOffset;
			}
			else {
				doUpdate = !doUpdate;
			}
		}

		if (doUpdate) {
			int settingsOffset = 0;

			if (CursorY > (pairs.size() - 1) + nameYOffset) { //offset for the setting being a space apart
				settingsOffset = 1; //don't add it to CursorY becuase this offset it temparary
			}

			util::ChangeLetter(" "[0], 1, oldCursorY); //remove the old one 

			util::ChangeLetter(">"[0], 1, CursorY + settingsOffset);
		}

		if (Inputs->GetKey(Enter) == pressed) {
			if (CursorY < pairs.size() + nameYOffset) {
				std::cout << "write file!" << "\n"; //launch carbon
			}
			if (CursorY == pairs.size() + nameYOffset) {
				ChangeWindow(Name);
				WindowChanged = true;
			}
			if (CursorY == (pairs.size() + 1) + nameYOffset) {
				std::cout << "Add version!" << "\n";
			}
			if (CursorY == (pairs.size() + 2) + nameYOffset) {
				std::cout << "Delete Version!" << "\n";
			}
		}	
	}
}


void ManageDisplay::NameWindow(std::vector<pair> pairs, std::string name,ManageInputs* Inputs) {
	int nameXoffset = 6; // 6 is an offset for "Name: "


	if (WindowChanged) {
		WindowChanged = false;

		system("cls");
		std::cout << "Name: " << name;

		NameTextBox = new TextBox(nameXoffset, 0, name);
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