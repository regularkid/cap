#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include "Cap.h"
#include "Utils.h"

void RunREPL();
void RunFile(const char* const filename);

int main(int argc, char* argv[])
{
    // REPL
    if (argc == 1)
    {
        RunREPL();
    }
    // Run script
    else if (argc == 2)
    {
        RunFile(argv[1]);
    }
    // Not supported
    else
    {
        LOG("Usage:");
        LOG("   cap")
        LOG("   cap [scriptName]")
    }

    return 0;
}

void RunREPL()
{
    LOG("Starting REPL...");

    Cap cap;

    std::string line;
    while (true)
    {
        printf("> ");        
        getline(std::cin, line);

        if (line == "q" || line == "quit")
        {
            break;
        }

        cap.Run(line);
    }
}

void RunFile(const char* const filename)
{
    LOG("Running script '%s'...", filename);

    std::ifstream file(filename);
    if (!file.is_open())
    {
        LOG("Failed to open '%s'", filename);
        return;
    }

    std::stringstream contents;
    contents << file.rdbuf();

    Cap cap;
    cap.Run(contents.str());
}