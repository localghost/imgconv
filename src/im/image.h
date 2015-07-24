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

using ImageHandleDeleter = MagickFunctionDeleterHelper< ::Image, &::DestroyImage>;
using ImageHandle = Handle< ::Image, ImageHandleDeleter>;

using ImageInfoHandleDeleter = MagickFunctionDeleterHelper< ::ImageInfo, &::DestroyImageInfo>;
using ImageInfoHandle = Handle< ::ImageInfo, ImageInfoHandleDeleter>;

class Image
{
public:
   explicit Image(const std::string& path);

   std::size_t width() const;

   std::size_t height() const;

   ImageFormat format() const;

   void write(const std::string& path);

   void call(ImageAction* action);

private:
   void read(const std::string& path);

   ImageHandle imageHandle_;
   ImageInfoHandle imageInfoHandle_;
   ImageFormat format_;
};
}

#endif
