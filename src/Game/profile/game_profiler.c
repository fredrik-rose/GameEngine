#include <Base/common.h>
#include <Game/Game.h>

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
    GAME_run(FPS, STEPS / 2); /* Warm up, to make sure the CPU enters performance state. */
    unsigned int cpu = 0U;
    unsigned int node = 0U;
    long long execution_time = 0LL;
    TIME_AND_RUN(GAME_run, cpu, node, execution_time, FPS, STEPS);
    stdout = fopen("/dev/tty","we");
    printf("Execution time: %lld ns, CPU: %u, Node: %u\n", execution_time, cpu, node);
}
