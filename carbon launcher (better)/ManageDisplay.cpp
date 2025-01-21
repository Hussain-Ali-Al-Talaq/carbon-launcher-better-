#include "ManageDisplay.h"

ManageDisplay::ManageDisplay() {
}

void ManageDisplay::displaywindow(std::vector<pair> pairs, std::string name,ManageInputs* Inputs) {
	

	switch (window)
	{
	case Main:
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

		system("cls");

		std::cout << "Username: " << name << "\n" << "\n";

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
		int oldCursorY = CursorY;

		bool doUpdate = UpdateYCursor(Inputs, nameYOffset, (pairs.size() - 1) + 3 + nameYOffset); // +3 is for the extra settings

		if (oldCursorY > (pairs.size() - 1) + nameYOffset) { //offset for the setting being a space apart
			oldCursorY++; 
		}

		if (doUpdate) {
			int settingsOffset = 0;

			if (CursorY > (pairs.size() - 1) + nameYOffset) { //offset for the setting being a space apart
				settingsOffset = 1; //don't add it to CursorY becuase this offset it temparary
			}

			util::ChangeLetter(" "[0], 1, oldCursorY); //remove the old one 

			util::ChangeLetter(">"[0], 1, CursorY + settingsOffset);
		}

		if (Inputs->GetKeyPressed(Enter)) {
			if (CursorY < pairs.size() + nameYOffset) {
				std::cout << "write file!" << "\n"; //launch carbon
			}
			if (CursorY == pairs.size() + nameYOffset) {
				ChangeWindow(Name);
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
	int nameXoffset = 10; // 6 is an offset for "Username: "


	if (WindowChanged) {
		WindowChanged = false;

		system("cls");
		std::cout << "Username: " << name;

		char text[15] = " - SaveAndExit";
		util::ChangeWord(text, 15, 0, 2); // so we don't move the cursor

		NameTextBox = new TextBox(nameXoffset, 0, name);

		CursorY = 0;
	}
	else {
		if (UpdateYCursor(Inputs, 0, 1)) {
			if (CursorY == 0) {
				util::ChangeLetter('-', 1, 2); // so we don't move the cursor
			}
			else if (CursorY == 1) {
				util::ChangeLetter('>', 1, 2); // so we don't move the cursor
				util::setCursorPosition(1,2);
			}
		}
		if (CursorY == 0) {
			NameTextBox->Update(Inputs);
		}
		
		if (Inputs->GetKeyPressed(Enter)) {
			ChangeWindow(Main);
			if (CallbackFunc != NULL) {
				CallbackFunc(NameTextBox->GetName());
			}
		}
	}
}

windowtype ManageDisplay::getWindow() {
	return window;
}

void ManageDisplay::ChangeWindow(windowtype newWindow) {
	window = newWindow;
	WindowChanged = true;
}

void ManageDisplay::UpdateNameCallback(std::function<void(std::string)> Func) {
	CallbackFunc = Func;
}

bool ManageDisplay::UpdateYCursor(ManageInputs* Inputs, int minValue, int maxValue) {
	bool updated = false;

	if (Inputs->GetKeyPressed(UpArrow)) {
		CursorY--;
		if (CursorY < minValue) {
			CursorY = minValue;
		}
		else {
			updated = !updated;
		}
	}

	if (Inputs->GetKeyPressed(DownArrow)) {
		CursorY++;
		if (CursorY > maxValue) { 
			CursorY = maxValue;
		}
		else {
			updated = !updated;
		}
	}
	return updated;
}