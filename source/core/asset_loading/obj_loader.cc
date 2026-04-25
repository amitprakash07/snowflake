#include "obj_loader.h"

#define TINYOBJLOADER_DISABLE_FAST_FLOAT
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <cstddef>

namespace
{
    amit::asset_loading::ObjColor GetVertexColor(const tinyobj::attrib_t& attrib, std::size_t vertex_index)
    {
        const std::size_t color_index = 3 * vertex_index;
        if (color_index + 2 >= attrib.colors.size())
        {
            return {};
        }

        return {attrib.colors[color_index], attrib.colors[color_index + 1], attrib.colors[color_index + 2]};
    }

    amit::asset_loading::ObjTextureCoordinate GetTextureCoordinate(const tinyobj::attrib_t& attrib,
                                                                   int                     texture_coordinate_index)
    {
        if (texture_coordinate_index < 0)
        {
            return {};
        }

        const std::size_t texcoord_index = 2 * static_cast<std::size_t>(texture_coordinate_index);
        if (texcoord_index + 1 >= attrib.texcoords.size())
        {
            return {};
        }

        return {attrib.texcoords[texcoord_index], attrib.texcoords[texcoord_index + 1]};
    }

}  // namespace

std::optional<amit::asset_loading::ObjMeshData> amit::asset_loading::LoadObjMesh(const std::filesystem::path& file_path)
{
    tinyobj::ObjReaderConfig reader_config;
    reader_config.triangulate  = true;
    reader_config.vertex_color = true;

    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(file_path.string(), reader_config))
    {
        return std::nullopt;
    }

    const tinyobj::attrib_t&              attrib = reader.GetAttrib();
    const std::vector<tinyobj::shape_t>& shapes = reader.GetShapes();

    ObjMeshData mesh_data;

    for (const tinyobj::shape_t& shape : shapes)
    {
        for (const tinyobj::index_t& index : shape.mesh.indices)
        {
            if (index.vertex_index < 0)
            {
                return std::nullopt;
            }

            const std::size_t vertex_index   = static_cast<std::size_t>(index.vertex_index);
            const std::size_t position_index = 3 * vertex_index;

            if (position_index + 2 >= attrib.vertices.size())
            {
                return std::nullopt;
            }

            ObjVertex vertex{
                .position           = {attrib.vertices[position_index],
                                       attrib.vertices[position_index + 1],
                                       attrib.vertices[position_index + 2]},
                .texture_coordinate = GetTextureCoordinate(attrib, index.texcoord_index),
                .color              = GetVertexColor(attrib, vertex_index)};

            mesh_data.indices.push_back(static_cast<std::uint32_t>(mesh_data.vertices.size()));
            mesh_data.vertices.push_back(vertex);
        }
    }

    return mesh_data;
}
