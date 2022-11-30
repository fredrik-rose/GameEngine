#include <Base/common.h>
#include <Game/Game.h>

#define FPS (20.0)
#define STEPS (1000)

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    GAME_run(FPS, STEPS);
}
