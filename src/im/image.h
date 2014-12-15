#ifndef IM_IMAGE_H
#define IM_IMAGE_H

#include <cstddef>
#include <string>
#include <memory>
#include <magick/MagickCore.h>
#include <im/imageformat.h>

namespace im {
using ImagePtr = std::unique_ptr<::Image, decltype(&DestroyImage)>;
using ImageInfoPtr = std::unique_ptr<::ImageInfo, decltype(&DestroyImageInfo)>;
using ExceptionInfoPtr = std::unique_ptr<::ExceptionInfo, decltype(&DestroyExceptionInfo)>;

inline ImagePtr make_image_ptr(::Image* image)
{
   return ImagePtr{image, &DestroyImage};
}

class ImageFilter;

class Image
{
public:
   Image() = default;
   explicit Image(const std::string& path);

   void read(const std::string& path);

   std::size_t width() const;

   std::size_t height() const;

   ImageFormat format() const;

   void write(const std::string& path);

   void apply_filter(ImageFilter* filter);

private:
   ImagePtr image_{nullptr, &DestroyImage};
   ImageInfoPtr info_{nullptr, &DestroyImageInfo};
   ImageFormat format_;
};
}

#endif // IM_IMAGE_H
