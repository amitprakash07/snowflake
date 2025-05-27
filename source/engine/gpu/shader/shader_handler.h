#ifndef ENGINE_GPU_SHADER_SHADER_HANDLER_H_
#define ENGINE_GPU_SHADER_SHADER_HANDLER_H_

#include <string>
#include <nlohmann/json.hpp>

#include "common/defs.h"

namespace engine
{
    class ShaderHandler
    {
    public:
        static bool           Init();
        static ShaderHandler* Instance();
        static bool           DenInit();

        bool CompileDefaultShaders();

    private:
        struct ShaderDesc
        {
            ShaderDesc(const nlohmann::json& json_shader_dec_obj);
            std::string name_;
            std::string relative_path_;
            std::string entry_point_;
            std::string profile_;
            std::string macros_;
            bool        enable_debug_info_;
        };

        static ShaderHandler* shader_handler_;
        const std::string     kEngineShaderDir = ENGINE_STRINGIZE_MACRO(ENGINE_SHADER_DIR);
        const std::string     kEngineShaderAssetDescFileName = "asset_shaders.json";
    };
}  // namespace engine

#endif
