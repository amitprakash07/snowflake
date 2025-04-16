#ifndef ENGINE_COMMON_OCTREE_H
#define ENGINE_COMMON_OCTREE_H

#include <vector>

#include "maths/vector3.h"

namespace engine
{
    namespace Physics
    {
        struct TriangleIndex
        {
            TriangleIndex() = default;
            union
            {
                uint32_t _indices[3];
                struct
                {
                    uint32_t index0;
                    uint32_t index1;
                    uint32_t index2;
                };
            };
        };

        struct OctreeNode
        {
            Vector3              pos;
            Vector3              extent;
            std::vector<TriangleIndex> triangles;
            Vector3              GetMin() const
            {
                return pos - extent;
            }
            Vector3 GetMax() const
            {
                return pos + extent;
            }
        };

        class Octree
        {
        public:
            Octree();
            ~Octree();
            void          InitFromRange(uint32_t level, Vector3 min, Vector3 max);
            void          InitFromFile(const char* pFile);
            OctreeNode*   GetNodesInLevel(uint32_t levelIndex) const;
            uint32_t      GetCountOfNodesInLevel(uint32_t levelIndex) const;
            uint32_t      GetNodeCount() const;
            OctreeNode*   GetNodes() const;
            Vector3 GetMin() const;
            Vector3 GetMax() const;
            uint32_t      Level() const;

        private:
            uint32_t      mLevel;
            OctreeNode*   mNodes;
            uint32_t      mCountOfNode;
            Vector3 min;
            Vector3 max;
        };

    }  // namespace Physics
}  // namespace engine

#endif