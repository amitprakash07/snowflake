#include <filesystem>
#include <iostream>
#include <optional>

#include "core/asset_loading/obj_loader.h"

int main(int argc, char* argv[])
{
    const std::filesystem::path obj_path =
        argc > 1 ? std::filesystem::path{argv[1]} : std::filesystem::path{"data/assets/models/textured_quad.obj"};

    const std::optional<amit::asset_loading::ObjMeshData> mesh_data = amit::asset_loading::LoadObjMesh(obj_path);
    if (!mesh_data.has_value())
    {
        std::cerr << "Failed to load OBJ mesh: " << obj_path.string() << '\n';
        return 1;
    }

    std::cout << "Loaded OBJ mesh: " << obj_path.string() << '\n';
    std::cout << "Vertex count: " << mesh_data->vertices.size() << '\n';
    std::cout << "Index count: " << mesh_data->indices.size() << '\n';
    std::cout << "Triangle count: " << mesh_data->indices.size() / 3 << '\n';

    if (!mesh_data->vertices.empty())
    {
        const amit::asset_loading::ObjVertex& first_vertex = mesh_data->vertices.front();
        std::cout << "First vertex position: " << first_vertex.position.x << ", " << first_vertex.position.y << ", "
                  << first_vertex.position.z << '\n';
        std::cout << "First vertex uv: " << first_vertex.texture_coordinate.u << ", "
                  << first_vertex.texture_coordinate.v << '\n';
    }

    return 0;
}
