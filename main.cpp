#include "engine.h"

int main()
{
    Engine engine("DiarioOpenGL", 1280, 720);
    if (engine.initialize())
        engine.run();

    return 0;
}