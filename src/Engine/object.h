/**
 * \file
 * \brief Object interface
 */
#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H

#include "Base/coordinates.h"

/**
 * \brief A 3D object
 */
struct OBJ_Object
{
    /**
     * The 3D coordinates of the object. The coordinates are in the object internal coordinate
     * system. It does thus not contain any information about where in the world the object is
     * located nor how it is rotated.
     */
    struct COORD_Coordinate3D *coordinates;
    int length; /**< Number of coordinates */
};

#endif /* ENGINE_OBJECT_H */
