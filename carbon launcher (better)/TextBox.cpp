#include "TextBox.h"

TextBox::TextBox(int x, int y, std::string t) {
	xPosition = x;
	yPosition = y;

	text = t;

	CursorX = xPosition + text.length();
}

void TextBox::Update(ManageInputs* Inputs) {
	UpdateCursor(Inputs);
	HandleDeleteLetter(Inputs);
	HandleAddLetter(Inputs);

	util::setCursorPosition(CursorX, yPosition);
}

void TextBox::UpdateCursor(ManageInputs* Inputs) {
	int messagelen = xPosition + text.length();

	//move cursor
	if (Inputs->GetKeyPressed(LeftArrow)) {
		CursorX--;
		if (CursorX < xPosition) {
			CursorX = xPosition;
		}

	}
	if (Inputs->GetKeyPressed(RightArrow)) {
		CursorX++;

		if (CursorX > messagelen) {
			CursorX = messagelen;
		}
	}
}

void TextBox::HandleDeleteLetter(ManageInputs* Inputs) {
	if (text.length() > 0) {

		//i know that the delete key should behave different but i don't care
		if ((Inputs->GetKeyPressed(BackSpace) || Inputs->GetKeyPressed(DeleteKey)) && CursorX != xPosition) {

			std::string tmptext;

			for (int i = 0; i < text.length(); i++) {

				if (i != CursorX - xPosition - 1) { //if its not the deleted letter than add it
					tmptext += text[i];
				}

				if (i > CursorX - xPosition - 1) { //shift the rest of the leters	
					util::ChangeLetter(text[i], xPosition + i - 1, yPosition);
				}

				if (i == text.length() - 1) { //delete last letter

					util::ChangeLetter(' ', xPosition + i, yPosition);
				}
			}
			text = tmptext;
			CursorX--;

		}
	}
}

void TextBox::HandleAddLetter(ManageInputs* Inputs) {
	wchar_t c = Inputs->GetAnyKeyPressed();

	for (int i = 0; i < ExcludeSize; i++) {
		if (c == ExcludeList[i]) {
			return; //key doesn't need to be handled
		}	
	}

	std::string tmptext;

	for (int i = 0; i < text.length() + 1; i++) {

		if (i == CursorX - xPosition) { //see if we're where the cursor is
			tmptext += (char)c;
		}
		if (i <= text.length() - 1 && text[i] != '\0') { // add the letters as we go
			tmptext += text[i];
		}

		if (i >= CursorX - xPosition) { //shift the rest of the leters	
			util::ChangeLetter(tmptext[i], xPosition + i, yPosition);

		}
	}
	text = tmptext;
	CursorX++;
}

std::string TextBox::GetName() {
	return text;
}