#ifndef IM_IMAGE_H
#define IM_IMAGE_H

#include <cstddef>
#include <string>
#include <memory>
#include <magick/MagickCore.h>
#include <im/imageformat.h>
#include <im/handle.h>

namespace im {
class ImageAction;

struct ImageHandleDeleter
{
  void operator()(::Image* image)
  {
    ::DestroyImage(image);
  }
};

using ImageHandle = Handle<::Image, ImageHandleDeleter>;

struct ImageInfoHandleDeleter
{
  void operator()(::ImageInfo* info)
  {
    ::DestroyImageInfo(info);
  }
};

using ImageInfoHandle = Handle<::ImageInfo, ImageInfoHandleDeleter>;

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

   void call(ImageAction* action);

private:
   ImageHandle image_;
   ImageInfoHandle info_;
   ImageFormat format_;
};
}

#endif
