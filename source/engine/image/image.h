#ifndef ENGINE_IMAGE_IMAGE_H_
#define ENGINE_IMAGE_IMAGE_H_

#include "platform/platform_objects.h"

namespace engine
{
    enum class ImageType
    {
        Unknown,
        JPEG,
        PNG,
        TIFF,
        PPM
    };

    class Image
    {
    public:
        static Image*            LoadImage(const FilePath& image_file_path);
        inline virtual ImageType Type() const = 0;
        virtual bool             Load()       = 0;
        virtual ~Image()                      = default;
    };

    class PngImage : public Image
    {
    public:
        PngImage()
        {
        }

        ImageType Type() const override
        {
            return ImageType::PNG;
        }

        bool Load() override;
    };

    class JpegImage : public Image
    {
    public:
        JpegImage()
        {
        }

        ImageType Type() const override
        {
            return ImageType::JPEG;
        }

        bool Load() override;
    };
}  // namespace engine

#endif
