
#include "shader_handler.h"
#include "platform/platform.h"
#include "nlohmann/json.hpp"
#include "platform/platform_objects.h"

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
    bool        success = false;
    FileSystem* fs      = FileHandler();

    if (fs)
    {
        File shader_asset(FilePath(kEngineShaderDir, kEngineShaderAssetDescFileName));
        if (shader_asset.Open())
        {
            std::istream   input(shader_asset.GetRawBuffer());
            nlohmann::json shader_asset_desc = nlohmann::json::parse(input);
        }
    }

    return success;
}