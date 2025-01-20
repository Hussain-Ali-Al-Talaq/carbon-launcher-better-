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


    bool updateDisplay = true;
    file.Read();

    Display.displaywindow(file.getPair(), file.getName(),&Inputs);
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

        Display.displaywindow(file.getPair(), file.getName(), &Inputs);        
    }
    
}
