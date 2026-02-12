#include "Triangle.h"

using namespace engine;

float geometry::Triangle::Signed2DTriArea() const
{
    return ((vert_a_.x() - vert_c_.x()) * (vert_b_.y() - vert_c_.y())) - ((vert_a_.y() - vert_c_.y()) * (vert_b_.x() - vert_c_.x()));
}
