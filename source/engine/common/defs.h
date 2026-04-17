#ifndef ENGINE_COMMON_DEFS_H
#define ENGINE_COMMON_DEFS_H

#define ENGINE_STRINGIZE_MACRO_(X) #X
#define ENGINE_STRINGIZE_MACRO(X) ENGINE_STRINGIZE_MACRO_(X)

#ifndef ENGINE_SHADER_DIR
#define ENGINE_SHADER_DIR ""
#endif

namespace engine
{
    template <class T>
    concept IntType = std::is_integral_v<T>;

    template <class T>
    concept UnsignedType = std::is_signed_v<T>;

    template <class T>
    concept UnsignedIntType = IntType<T> && !UnsignedType<T>;

    template <class T>
    concept FloatType = std::is_floating_point_v<T>;

}  // namespace engine

#endif