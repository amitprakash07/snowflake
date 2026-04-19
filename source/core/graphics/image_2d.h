#ifndef CORE_GRAPHICS_IMAGE_2D_H_
#define CORE_GRAPHICS_IMAGE_2D_H_

#include <cstdint>

#include "core/graphics/pixel.h"

namespace amit::graphics
{
    struct ImageCoordinate
    {
        uint32_t x;
        uint32_t y;
    };

    template <typename ImageDataType>
    class Image2D
    {
    public:
        Image2D() = delete;

        Image2D(uint32_t width, uint32_t height);

        ~Image2D()
        {
            delete[] image_data_;
        }

        uint32_t GetWidth() const
        {
            return width_;
        }

        uint32_t GetHeight() const
        {
            return height_;
        }

        const ImageDataType& Get(const ImageCoordinate& image_coordinate) const
        {
            if (image_coordinate.x >= width_ || image_coordinate.y >= height_)
            {
                printf("It's wrong");
                static ImageDataType default_value{};
                return default_value;
            }
            uint64_t index = image_coordinate.y * width_ + image_coordinate.x;
            return image_data_[index];
        }

        const ImageDataType* GetData() const
        {
            return image_data_;
        }

        void SetImageData(const ImageCoordinate& image_coordinate, const ImageDataType& data);

    private:
        ImageDataType* image_data_;  // Array to hold pixel colors by row-major order
        uint32_t       width_;
        uint32_t       height_;
    };

    template <typename ImageDataType>
    amit::graphics::Image2D<ImageDataType>::Image2D(uint32_t width, uint32_t height)
        : image_data_(nullptr)
        , width_(width)
        , height_(height)
    {
        if (width_ > 0 && height_ > 0)
        {
            image_data_ = new ImageDataType[static_cast<size_t>(width_ * height_)];
            memset(image_data_, 0, static_cast<size_t>(width_ * height_) * sizeof(ImageDataType));
        }
    }

    template <typename ImageDataType>
    void amit::graphics::Image2D<ImageDataType>::SetImageData(const ImageCoordinate& image_coordinate,
                                                                const ImageDataType&   data)
    {
        if (image_coordinate.x >= width_ || image_coordinate.y >= height_)
        {
            printf("It's wrong");
            return;
        }

        uint64_t index     = image_coordinate.y * width_ + image_coordinate.x;
        image_data_[index] = data;
    }

    using ColorBuffer = Image2D<Rgb8>;
    using DepthBuffer = Image2D<float>;

}  // namespace amit::graphics

namespace amit::image
{
    void WriteColorBufferToPPM(const amit::graphics::ColorBuffer& color_buffer, const char* filename);
    void WriteDepthBufferToPPM(const amit::graphics::DepthBuffer& depth_buffer, const char* filename);
}  // namespace amit::image

#endif