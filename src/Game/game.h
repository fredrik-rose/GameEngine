/**
 * \file
 * \brief Game interface
 */
#ifndef GAME_GAME_H
#define GAME_GAME_H

/**
 * \brief Run the game
 *
 * \param[in] fps The frame rate [frames / s]
 * \param[in] steps The number of steps/frames to run
 */
void GAME_run(
    double fps,
    int steps);

#endif /* GAME_GAME_H */
