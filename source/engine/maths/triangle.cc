#include "Triangle.h"

float Physics::Triangle::Signed2DTriArea() const {
  return ((vertexA.X - vertexC.X) * (vertexB.Y - vertexC.Y)) -
         ((vertexA.Y - vertexC.Y) * (vertexB.X - vertexC.X));
}
