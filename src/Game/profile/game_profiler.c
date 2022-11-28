#include "Base/common.h"
#include "Game/Game.h"

#include <stdio.h>

#define FPS (100.0)
#define STEPS (50)

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    /*
     * Temporarily disable printf to avoid game outputs. This is a hack that might only work on
     * Linux running in a terminal.
     */
    fclose(stdout);
    GAME_run(FPS, STEPS);
    stdout = fopen("/dev/tty","we");
}
