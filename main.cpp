#include "engine.h"

int main()
{
    Engine engine;
    if (engine.initialize())
        engine.run();

    return 0;
}