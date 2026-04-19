#include <algorithm>

#include "geometry.h"
#include "Triangle.h"

using namespace amit;

float geometry::Triangle::Signed2DTriArea() const
{
    return ((vert_a_position_.x - vert_c_position_.x) * (vert_b_position_.y - vert_c_position_.y)) -
           ((vert_a_position_.y - vert_c_position_.y) * (vert_b_position_.x - vert_c_position_.x));
}

geometry::AxisAlignedBoundingBox geometry::Triangle::GetBoundingBox() const
{
    if (!is_bounding_box_computed_)
    {
        Point3D min_point;
        min_point.x = std::min({vert_a_position_.x, vert_b_position_.x, vert_c_position_.x});
        min_point.y = std::min({vert_a_position_.y, vert_b_position_.y, vert_c_position_.y});

        // This is not required as box is a 2D shape, but we may need it for depth testing in the future.
        min_point.z = std::min({vert_a_position_.z, vert_b_position_.z, vert_c_position_.z});

        Point3D max_point;
        max_point.x = std::max({vert_a_position_.x, vert_b_position_.x, vert_c_position_.x});
        max_point.y = std::max({vert_a_position_.y, vert_b_position_.y, vert_c_position_.y});

        // This is not required as box is a 2D shape, but we may need it for depth testing in the future.
        max_point.z = std::max({vert_a_position_.z, vert_b_position_.z, vert_c_position_.z});

        bounding_box_ = geometry::AxisAlignedBoundingBox(min_point, max_point);
    }

    return bounding_box_;
}
