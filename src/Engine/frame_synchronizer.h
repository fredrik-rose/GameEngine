/**
 * \file
 * \brief Frame synchronizer interface
 */
#ifndef ENGINE_FRAMESYNCHRONIZER_H
#define ENGINE_FRAMESYNCHRONIZER_H

struct SYNC_Frame_Synchronizer;

/**
 * \brief Create a frame synchronizer
 *
 * \param[in] fps Frame rate [frames / s]
 *
 * \return Frame synchronizer
 */
struct SYNC_Frame_Synchronizer * SYNC_create(
    double fps);

/**
 * \brief Destroy a frame synchronizer
 *
 * \param[in] frame_synchronizer The frame synchronizer, to destroy, do not use it anymore
 */
void SYNC_destroy(
    struct SYNC_Frame_Synchronizer *frame_synchronizer);

/**
 * \brief Sync frames, sleeps until specified frame rate is achieved
 *
 * \param[in] frame_synchronizer The frame synchronizer
 */
void SYNC_sync(
    struct SYNC_Frame_Synchronizer *frame_synchronizer);

#endif /* ENGINE_FRAMESYNCHRONIZER_H */
