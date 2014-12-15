#include "resizefilter.h"

#include <magick/MagickCore.h>

#include <base/log.h>
#include <base/exception.h>

namespace im {
namespace {
void adjust_size_to_aspect_ratio(const ImagePtr& image, size_t& width, size_t& height)
{
    if ((width > height) || ((width == height) && (image->columns > image->rows)))
    {
        float scale = (float)width / (float)image->columns;
        height = image->rows * scale;
    }
    else
    {
        float scale = (float)height / (float)image->rows;
        width = image->columns * scale;
    }
}
}

ResizeFilter::ResizeFilter(std::size_t width, std::size_t height)
   : ResizeFilter(width, height, false)
{
}

ResizeFilter::ResizeFilter(std::size_t width, std::size_t height, bool keep_aspect_ratio)
   : width_{width},
     height_{height},
     keep_aspect_ratio_{keep_aspect_ratio}
{
}

ImagePtr ResizeFilter::run(const ImagePtr& image)
{
   if (0 == width_ || 0 == height_)
   {
      LOG_DEBUG << "Invalid size";
      return make_image_ptr(nullptr);
   }

    LOG_DEBUG << "current size: " << image->columns << "x" << image->rows;

    std::size_t width = width_;
    std::size_t height = height_;

    if (keep_aspect_ratio_)
        adjust_size_to_aspect_ratio(image, width, height);
    LOG_DEBUG << "new size: " << width << "x" << height;

   if (width == 0 || height == 0)
   {
      LOG_ERROR << "One of the dimensions, after adjusting them to keep aspect ratio, is 0.";
      THROW(base::exception{});
   }

    ::ExceptionInfo* ex = AcquireExceptionInfo();
    ExceptionInfoPtr guard{ex, &DestroyExceptionInfo};
    auto result = make_image_ptr(::ResizeImage(image.get(), width, height, LanczosFilter, 1.0, ex));
    if (!result)
        throw std::runtime_error(ex->reason);
    return result;
}
}
