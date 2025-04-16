#include "bounding_box.h"

using namespace engine;

bool BoundingBox::DoesCollides(const BoundingBox& other) const
{
    if (max.x() < other.min.x() || min.x() > other.max.x())
    {
        return false;
    }

    if (max.y() < other.min.y() || min.y() > other.max.y())
    {
        return false;
    }

    if (max.z() < other.min.z() || min.z() > other.max.z())
    {
        return false;
    }

    return true;
}

// Computes the square distance between a point p and an AABB b
float BoundingBox::SquareDistancePoint(const Vector3& point) const
{
    float sqDist = 0.0f;
    for (int i = 0; i < 3; i++)
    {
        // For each axis count any excess distance outside box extents
        float v = point[i];
        if (v < min[i])
            sqDist += (min[i] - v) * (min[i] - v);
        if (v > max[i])
            sqDist += (v - max[i]) * (v - max[i]);
    }
    return sqDist;
}

Vector3 BoundingBox::ClosestPtPointAABB(const Vector3& p) const
{
    // For each coordinate axis, if the point coordinate value is
    // outside box, clamp it to the box, else keep it as is
    Vector3 q;
    for (int i = 0; i < 3; i++)
    {
        float v = p[i];
        if (v < min[i])
            v = min[i];  // v = max(v, b.min[i])
        if (v > max[i])
            v = max[i];  // v = min(v, b.max[i])
        q[i] = v;
    }

    return q;
}

float BoundingBox::SqDistPointAABB(Vector3 point) const
{
    // Computes the square distance between a point p and an AABB b
    float sqDist = 0.0f;
    for (int i = 0; i < 3; i++)
    {
        // For each axis count any excess distance outside box extents
        float v = point[i];
        if (v < min[i])
            sqDist += (min[i] - v) * (min[i] - v);
        if (v > max[i])
            sqDist += (v - max[i]) * (v - max[i]);
    }
    return sqDist;
}
