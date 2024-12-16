#include "globals.h"
#include <raylib.h>
#include <raymath.h>

int Vector2AlmostEquals(Vector2 a, Vector2 b)
{
    Vector2 approxA = {round(a.x), round(a.y)};
    Vector2 approxB = {round(b.x), round(b.y)};

    return Vector2Equals(approxA, approxB);
}