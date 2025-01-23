#include "ManageDisplay.h"

ManageDisplay::ManageDisplay() {
}

void ManageDisplay::displaywindow(ManageInputs* Inputs, std::vector<pair> pairs, std::string name) {
	

	switch (window)
	{
	case Main:
		NormalWindow(Inputs, pairs, name);
		break;
	case Name:
		NameWindow(Inputs, pairs, name);
		break;
	case Adding:
		break;
	case Deleting:
		DeleteWindow(Inputs, pairs, name);
		break;
	default:
		break;
	}
}
void ManageDisplay::NormalWindow(ManageInputs* Inputs, std::vector<pair> pairs, std::string name) {
	std::vector<std::string> settings;

	settings.push_back("Change Name");
	settings.push_back("Add version");
	settings.push_back("delete version");

	OptionsWindow(Inputs, pairs, settings, name, '>');

	if (Inputs->GetKey(Enter) == pressed) {
		if (CursorY < pairs.size() + nameYOffset) {
			std::cout << "write file!" << "\n"; //launch carbon
		}

		//the rest of the settings
		if (CursorY == pairs.size() + nameYOffset) {
			ChangeWindow(Name);
		}
		if (CursorY == (pairs.size() + 1) + nameYOffset) {
			std::cout << "Add Version!" << "\n";
		}
		if (CursorY == (pairs.size() + 2) + nameYOffset) {
			ChangeWindow(Deleting);
		}
		
	}
}

void ManageDisplay::DeleteWindow(ManageInputs* Inputs, std::vector<pair> pairs, std::string name) {
	std::vector<std::string> settings;

	settings.push_back("SaveAndExit");

	OptionsWindow(Inputs, pairs, settings, name, '*');

	if (Inputs->GetKey(Enter) == pressed) {
		if (CursorY < pairs.size() + nameYOffset) {
			if (DeleteCallback != NULL) {
				DeleteCallback(CursorY - nameYOffset);
				ReprintWindow = true;
			}
		}

		if (CursorY == pairs.size() + nameYOffset) {
			ChangeWindow(Main);
		}
	}
}

void ManageDisplay::OptionsWindow(ManageInputs* Inputs, std::vector<pair> pairs, std::vector<std::string> settings, std::string name, char pointer) {

	//full window refresh
	if (WindowChanged || ReprintWindow) {
		if (!ReprintWindow) {
			CursorY = nameYOffset;
		}
		else if(CursorY > (pairs.size() - 1) + nameYOffset && pairs.size() != 0){
			CursorY = (pairs.size() - 1) + nameYOffset;
		}

		WindowChanged = false;
		ReprintWindow = false;

		system("cls");

		std::cout << "Username: " << name << "\n" << "\n";

		for (int i = 0; i < pairs.size(); i++) {
			std::cout << "   " << pairs[i].name << "\n";
		}

		if (pairs.size() != 0) {
			std::cout << "\n";
		}

		if (settings.size() != 0) {
			for (int i = 0; i < settings.size(); i++) {
				std::cout << "   " << settings[i] << "\n";
			}
		}

		

		util::ChangeLetter(pointer, 1, CursorY); //add the cursor at the begining
	}
	else {

		int oldCursorY = CursorY;

		bool doUpdate = UpdateYCursor(Inputs, nameYOffset, (pairs.size() - 1) + settings.size() + nameYOffset);

		if (pairs.size() != 0) {
			if (oldCursorY > (pairs.size() - 1) + nameYOffset) { //offset for the setting being a space apart
				oldCursorY++;
			}
		}

		if (doUpdate) {
			int settingsOffset = 0;

			if (CursorY > (pairs.size() - 1) + nameYOffset && pairs.size() != 0) { //offset for the setting being a space apart
				settingsOffset = 1; //don't add it to CursorY becuase this offset it temparary
			}

			util::ChangeLetter(' ', 1, oldCursorY); //remove the old one 

			util::ChangeLetter(pointer, 1, CursorY + settingsOffset);
		}
	}
}


void ManageDisplay::NameWindow(ManageInputs* Inputs, std::vector<pair> pairs, std::string name) {
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
		
		if (Inputs->GetKey(Enter) == pressed) {
			ChangeWindow(Main);

			if (NameCallback != NULL) {
				NameCallback(NameTextBox->GetName());
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

void ManageDisplay::SetNameCallback(std::function<void(std::string)> Func) {
	NameCallback = Func;
}
void ManageDisplay::SetDeleteCallback(std::function<void(int)> Func) {
	DeleteCallback = Func;
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