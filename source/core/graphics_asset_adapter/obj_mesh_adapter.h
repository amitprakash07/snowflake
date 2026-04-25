#ifndef CORE_GRAPHICS_ASSET_ADAPTER_OBJ_MESH_ADAPTER_H_
#define CORE_GRAPHICS_ASSET_ADAPTER_OBJ_MESH_ADAPTER_H_

#include <filesystem>
#include <optional>

#include "core/asset_loading/obj_loader.h"
#include "core/graphics_common/mesh_data.h"

namespace amit::graphics_asset_adapter
{
    graphics::MeshData ConvertObjMeshToGraphicsMesh(const asset_loading::ObjMeshData& obj_mesh_data);

    std::optional<graphics::MeshData> LoadObjMeshAsGraphicsMesh(const std::filesystem::path& file_path);

}  // namespace amit::graphics_asset_adapter

#endif
