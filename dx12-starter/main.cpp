#include <cstdint>
#include <iostream>
#include <easy/profiler.h>
#include <chrono>
#include <thread>
#include "App.h"

#define BUILD_WITH_EASY_PROFILER = 1

int main(int argc, char* argv[])
{
    EASY_MAIN_THREAD;
    EASY_PROFILER_ENABLE;

    {

        EASY_BLOCK("Calculating sum");
        std::this_thread::sleep_for(
            std::chrono::milliseconds(2));

    }

    // Initialize our app
    App* app = new App();
    // Run the entire app. This starts an infinite loop until we exit.
    app->Run();

    // Save profiling data to log file
    profiler::dumpBlocksToFile("easy-profiler.prof");
    
    return 0;
}