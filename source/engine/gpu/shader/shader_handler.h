#ifndef ENGINE_GPU_SHADER_SHADER_HANDLER_H_
#define ENGINE_GPU_SHADER_SHADER_HANDLER_H_

#include <string>

#include "common/defs.h"

namespace engine
{
    class ShaderHandler
    {
    public:
        static inline bool           Init();
        static inline ShaderHandler* Instance();
        static inline bool           DenInit();

        bool CompileDefaultShaders();

    private:
        static ShaderHandler* shader_handler_;
        const std::string     kEngineShaderDir = ENGINE_STRINGIZE_MACRO(ENGINE_SHADER_DIR);
        const std::string     kEngineShaderAssetDescFileName = "asset_shaders.json";
    };
}  // namespace engine

#endif
