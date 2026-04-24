#include "geometry.h"
#include "triangle.h"

using namespace amit;

float geometry::Triangle::Signed2DTriArea() const
{
    return ((vert_a_position_.x - vert_c_position_.x) * (vert_b_position_.y - vert_c_position_.y)) -
           ((vert_a_position_.y - vert_c_position_.y) * (vert_b_position_.x - vert_c_position_.x));
}
