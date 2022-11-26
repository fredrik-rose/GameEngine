#include "Base/common.h"
#include "Game/Game.h"

#define FPS (5.0)
#define STEPS (100)

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    GAME_run(FPS, STEPS);
}
