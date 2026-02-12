#ifndef ENGINE_GRAPHICS_COLOR_H_
#define ENGINE_GRAPHICS_COLOR_H_

namespace engine
{
    namespace graphics
    {
        class Color
        {
        public:
            Color() = default;
                
            Color(float red, float green, float blue)
                : r(red)
                , g(green)
                , b(blue)
            {
            }

            float r;
            float g;
            float b;
        };
    }  // namespace graphics
}  // namespace engine

#endif