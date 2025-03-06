#include <stdio.h>
#include "Application.h"
#include "Dry_SDL.h"
using namespace Dry;

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    
    Application app(480, 640);

    app.Run();

    return 0;
}