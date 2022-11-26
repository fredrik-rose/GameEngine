/**
 * \file
 * \brief Frame synchronizer implementation
 */
#include "frame_synchronizer.h"

#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

/**
 * \brief Frame synchronizer
 */
struct SYNC_Frame_Synchronizer
{
    long long delta_time_nsec; /**< Specified frame time [ns] */
    struct timeval previous_time; /**< Previous time */
};

struct SYNC_Frame_Synchronizer * SYNC_create(
    double fps)
{
    assert(fps > 0.0);

    struct SYNC_Frame_Synchronizer *const frame_synchronizer = calloc(1, sizeof(*frame_synchronizer));

    frame_synchronizer->delta_time_nsec = (long long)((1.0 / fps) * 1e9);
    gettimeofday(&frame_synchronizer->previous_time, 0);

    return frame_synchronizer;
}

void SYNC_destroy(
    struct SYNC_Frame_Synchronizer *frame_synchronizer)
{
    free(frame_synchronizer);
}

void SYNC_sync(
    struct SYNC_Frame_Synchronizer *frame_synchronizer)
{
    struct timeval current_time;
    gettimeofday(&current_time, 0);
    const long long seconds_nsec = (current_time.tv_sec - frame_synchronizer->previous_time.tv_sec) * 1000000000LL;
    const long long micro_seconds_nsec = (current_time.tv_usec - frame_synchronizer->previous_time.tv_usec) * 1000LL;
    const long long elapsed = seconds_nsec + micro_seconds_nsec;

    if (elapsed < frame_synchronizer->delta_time_nsec)
    {
        const long long time_left_nsec = frame_synchronizer->delta_time_nsec - elapsed;
        const struct timespec sleep_time = {
            .tv_sec = time_left_nsec / 1000000000LL,
            .tv_nsec = (time_left_nsec % 1000000000LL)
        };

        nanosleep(&sleep_time, NULL);
    }

    gettimeofday(&frame_synchronizer->previous_time, 0);
}
