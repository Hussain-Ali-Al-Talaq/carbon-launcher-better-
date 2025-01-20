#include <iostream>
#include <string>
#include <format>
#include <windows.h>
#include "HandleFile.h"
#include "ManageInputs.h"
#include "ManageDisplay.h"
#include <functional>
#include <chrono>

int main()
{   
    HandleFile file;
    ManageInputs Inputs;
    ManageDisplay Display;


    int selected = 0;
    bool updateDisplay = true;
    file.Read();

    Display.displaywindow(file.getPair(), file.getName(), selected,&Inputs, true);
    Display.UpdateNameCallback(std::bind(&HandleFile::UpdateName, &file, std::placeholders::_1));

    std::chrono::duration<double> LastFrameTime = std::chrono::system_clock::now().time_since_epoch(); 

    while (true) {
        //limit frame rate
        std::chrono::duration<double> CurrentTime = std::chrono::system_clock::now().time_since_epoch(); 
        long long elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime - LastFrameTime).count();

        if (elapsed_seconds > 16) {
            LastFrameTime = std::chrono::system_clock::now().time_since_epoch();
        }
        else {
            continue;
        } 

        Inputs.updateKeys();

        if (Display.getWindow() == Normal) {
            if (Inputs.GetKey(UpArrow) == pressed) {
                selected--;
                if (selected < 0) {
                    selected = 0;
                }
                else {
                    updateDisplay = true;
                }
            }

            if (Inputs.GetKey(DownArrow) == pressed) {
                selected++;
                if (selected > file.getPair().size() + 2) {
                    selected = file.getPair().size() + 2;
                }
                else {
                    updateDisplay = true;
                }
            }

            if (updateDisplay) {
                Display.displaywindow(file.getPair(), file.getName(), selected, &Inputs, false);
                updateDisplay = false;
            }

            if (Inputs.GetKey(Enter) == pressed) {
                if (selected < file.getPair().size()) {
                    std::cout << "write file!" << "\n";
                }
                if (selected == file.getPair().size()) {
                    Display.ChangeWindow(Name);
                    Display.displaywindow(file.getPair(), file.getName(), selected, &Inputs, true);
                }
                if (selected == file.getPair().size() + 1) {
                    std::cout << "Add version!" << "\n";
                }
                if (selected == file.getPair().size() + 2) {
                    std::cout << "Delete Version!" << "\n";
                }
            }
        }
        else if(Display.getWindow() == Name){
            Display.displaywindow(file.getPair(), file.getName(), selected, &Inputs, false);
        }

        
        
    }
    
}
