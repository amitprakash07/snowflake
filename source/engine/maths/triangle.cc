#include <algorithm>

#include "Triangle.h"

using namespace engine;

float geometry::Triangle::Signed2DTriArea() const
{
    return ((vert_a_.x - vert_c_.x) * (vert_b_.y - vert_c_.y)) - ((vert_a_.y - vert_c_.y) * (vert_b_.x - vert_c_.x));
}

geometry::AxisAlignedBoundingBox geometry::Triangle::GetBoundingBox() const
{
    return bounding_box_;
}

bool geometry::Triangle::IsInside(const Point3D& point) const
{
    if (!bounding_box_.IsInside(point))
    {
        return false;
    }

    // TODO
    return false;
}

void geometry::Triangle::FindBoundingBox()
{
    bounding_box_.min.x = std::min({vert_a_.x, vert_b_.x, vert_c_.x});
    bounding_box_.min.y = std::min({vert_a_.y, vert_b_.y, vert_c_.y});
    bounding_box_.min.z = std::min({vert_a_.z, vert_b_.z, vert_c_.z});

    bounding_box_.max.x = std::max({vert_a_.x, vert_b_.x, vert_c_.x});
    bounding_box_.max.y = std::max({vert_a_.y, vert_b_.y, vert_c_.y});
    bounding_box_.max.z = std::max({vert_a_.z, vert_b_.z, vert_c_.z});
}
