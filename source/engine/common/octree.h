#ifndef ENGINE_COMMON_ALGORITHMS_OCTREE_H
#define ENGINE_COMMON_ALGORITHMS_OCTREE_H

#include <vector>

#include "maths/vector3.h"

namespace engine {
namespace Physics {
struct TriangleIndex {
  TriangleIndex() = default;
  union {
    uint32_t _indices[3];
    struct {
      uint32_t index0;
      uint32_t index1;
      uint32_t index2;
    };
  };
};

struct OctreeNode {
  Math::Vector3 pos;
  Math::Vector3 extent;
  std::vector<TriangleIndex> triangles;
  Math::Vector3 GetMin() const { return pos - extent; }
  Math::Vector3 GetMax() const { return pos + extent; }
};

class Octree {
 public:
  Octree();
  ~Octree();
  void InitFromRange(uint32_t level, Math::Vector3 min,
                     Math::Vector3 max);
  void InitFromFile(const char* pFile);
  OctreeNode* GetNodesInLevel(uint32_t levelIndex) const;
  uint32_t GetCountOfNodesInLevel(uint32_t levelIndex) const;
  uint32_t GetNodeCount() const;
  OctreeNode* GetNodes() const;
  Math::Vector3 GetMin() const;
  Math::Vector3 GetMax() const;
  uint32_t Level() const;

 private:
  uint32_t mLevel;
  OctreeNode* mNodes;
  uint32_t mCountOfNode;
  Math::Vector3 min;
  Math::Vector3 max;
};

}  // namespace Physics
}  

#endif