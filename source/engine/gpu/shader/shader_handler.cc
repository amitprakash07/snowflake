
#include "shader_handler.h"

#include <iostream>

#include "platform/platform.h"
#include "nlohmann/json.hpp"
#include "platform/platform_objects.h"
#include "platform/platform_systems.h"

engine::ShaderHandler* engine::ShaderHandler::shader_handler_ = nullptr;

bool engine::ShaderHandler::Init()
{
    if (shader_handler_ == nullptr)
    {
        shader_handler_ = new (std::nothrow) ShaderHandler();
    }

    bool success = shader_handler_ != nullptr;
    return success;
}

engine::ShaderHandler* engine::ShaderHandler::Instance()
{
    if (Init())
    {
        return shader_handler_;
    }

    return nullptr;
}

bool engine::ShaderHandler::DenInit()
{
    delete shader_handler_;
    shader_handler_ = nullptr;
    return true;
}

bool engine::ShaderHandler::CompileDefaultShaders()
{
    bool success = false;

    File shader_asset(FilePath(kEngineShaderDir, kEngineShaderAssetDescFileName));
    if (shader_asset.Open())
    {
        std::istream   input(shader_asset.GetRawBuffer());
        nlohmann::json shader_asset_desc = nlohmann::json::parse(input);

        for (size_t it = 0; it < shader_asset_desc.size(); it++)
        {
            ShaderDesc shader_desc(shader_asset_desc["compile"][it]);
            File       shader(FilePath(kEngineShaderDir, shader_desc.relative_path_));
            if (shader.Open())
            {
                // TODO
                std::cout << "file is opened";
                success = true;
            }
        }
    }

    return success;
}

engine::ShaderHandler::ShaderDesc::ShaderDesc(const nlohmann::json& json_shader_dec_obj)
{
    name_              = json_shader_dec_obj["name"];
    relative_path_     = json_shader_dec_obj["file"];
    entry_point_       = json_shader_dec_obj["entry_point"];
    profile_           = json_shader_dec_obj["profile"];
    macros_            = json_shader_dec_obj["macros"];
    enable_debug_info_ = json_shader_dec_obj["enable_debug_info"];
}
