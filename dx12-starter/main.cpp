#include <cstdint>
#include <iostream>
#include "App.h"

int main(int argc, char* argv[])
{
    // Initialize our app
    App* app = new App();
    // Run the entire app. This starts an infinite loop until we exit.
    app->Run();
    
    return 0;
}