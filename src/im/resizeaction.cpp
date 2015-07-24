#include "resizeaction.h"

#include <magick/MagickCore.h>

#include <base/log.h>
#include <base/exception.h>

#include "exceptioninfo.h"

namespace im {
namespace {
void adjust_size_to_aspect_ratio(const ImageHandle& image, size_t& width, size_t& height)
{
  if ((width > height) || ((width == height) && (image->columns > image->rows)))
  {
    float const scale = (float)width / (float)image->columns;
    height = image->rows * scale;
  }
  else
  {
    float const scale = (float)height / (float)image->rows;
    width = image->columns * scale;
  }
}
}

ResizeAction::ResizeAction(std::size_t width, std::size_t height)
  : ResizeAction(width, height, false)
{
}

ResizeAction::ResizeAction(std::size_t width, std::size_t height, bool keep_aspect_ratio)
  : width_{width},
    height_{height},
    keep_aspect_ratio_{keep_aspect_ratio}
{
}

void ResizeAction::width(std::size_t w)
{
  width_ = w;
}

void ResizeAction::height(std::size_t h)
{
  height_ = h;
}

void ResizeAction::keep_aspect_ratio(bool keep)
{
  keep_aspect_ratio_ = keep;
}

ImageHandle ResizeAction::run(ImageHandle image)
{
  if (0 == width_ || 0 == height_)
  {
    LOG_DEBUG << "Invalid size";
    return ImageHandle{};
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

  ExceptionInfo ex;
  ImageHandle result{::ResizeImage(*image, width, height, LanczosFilter, 1.0, ex.handle())};
  if (!result)
    throw std::runtime_error(ex.message());
  return result;
}
}
