#include <cstdint>
#include <iostream>
#include "App.h"

#define DX12_ENABLE_DEBUG_LAYER = 1;

int main(int argc, char* argv[])
{
    // Initialize our app
    App* app = new App();
    // Run the entire app. This starts an infinite loop until we exit.
    app->Run();
    
    return 0;
}