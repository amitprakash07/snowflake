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
        static Image*            CreateImage(const FilePath& image_file_path);
        inline virtual ImageType Type() const = 0;
        virtual bool             Load()       = 0;
        virtual ~Image()                      = default;
        FilePath GetPath() const
        {
            return image_file_path_;
        }

    protected:
        Image(const FilePath& path)
            : image_file_path_(path)
        {
        }

    private:
        FilePath image_file_path_;
    };

    class PngImage : public Image
    {
    public:
        PngImage(const FilePath& path)
            : Image(path)
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
        JpegImage(const FilePath& path)
            : Image(path)
        {
        }

        ImageType Type() const override
        {
            return ImageType::JPEG;
        }

        bool Load() override;
    };

    class PpmImage : public Image
    {
    public:
        PpmImage(const FilePath& path)
            : Image(path)
        {
        }

        ImageType Type() const override
        {
            return ImageType::PPM;
        }

        bool Load() override;
    };
}  // namespace engine

#endif
