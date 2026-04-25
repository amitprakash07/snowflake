#ifndef CORE_ASSET_LOADING_OBJ_LOADER_H_
#define CORE_ASSET_LOADING_OBJ_LOADER_H_

#include <cstdint>
#include <filesystem>
#include <optional>
#include <vector>

namespace amit::asset_loading
{
    struct ObjPosition
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };

    struct ObjTextureCoordinate
    {
        float u = 0.0f;
        float v = 0.0f;
    };

    struct ObjColor
    {
        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
    };

    struct ObjVertex
    {
        ObjPosition          position;
        ObjTextureCoordinate texture_coordinate;
        ObjColor             color;
    };

    struct ObjMeshData
    {
        std::vector<ObjVertex>     vertices;
        std::vector<std::uint32_t> indices;
    };

    std::optional<ObjMeshData> LoadObjMesh(const std::filesystem::path& file_path);

}  // namespace amit::asset_loading

#endif
