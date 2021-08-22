#include <stdio.h>
#include "Utils.h"

int main(int argc, char* argv[])
{
    // REPL
    if (argc == 1)
    {
        LOG("Starting REPL...");
    }
    // Run script
    else if (argc == 2)
    {
        LOG("Running script '%s'...", argv[1]);
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