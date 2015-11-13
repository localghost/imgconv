#include "image.h"

#include <cstring>
#include <cstdlib>
#include <stdexcept>

#include <base/log.h>
#include <base/exception.h>

#include "imageaction.h"
#include "exceptioninfo.h"

namespace im {

namespace {
void finalizeMagickCore()
{
  MagickCoreTerminus();
}

bool initializeMagickCore();
bool initialized = initializeMagickCore();
bool initializeMagickCore()
{
  static_cast<void>(initialized);
  MagickCoreGenesis("imgconv", MagickTrue);
  ::atexit(&finalizeMagickCore);
  return true;
}

ImageFormat magickToFormat(const char* const magick)
{
  if (!strncmp(magick, "JPEG", 4))
  {
    return ImageFormat::JPG;
  }
  else if (!strncmp(magick, "PSD", 3))
  {
    return ImageFormat::PSD;
  }
  else if (!strncmp(magick, "PNG", 3))
  {
    return ImageFormat::PNG;
  }
  else if (!strncmp(magick, "GIF", 3))
  {
    return ImageFormat::GIF;
  }
  THROW_MSG(base::exception{}, "Unsupported image format [" << std::string(magick) << "]");
}
}

Image::Image(const std::string& path)
{
   read(path);
}

void Image::read(const std::string& path)
{
  ExceptionInfo ex;
  imageInfoHandle_ = ::AcquireImageInfo();
  std::strncpy(imageInfoHandle_->filename, path.c_str(), MaxTextExtent);
  imageHandle_ = ::ReadImage(*imageInfoHandle_, ex.native());
  if (!imageHandle_)
  {
    LOG_ERROR << "Could not read image " << path << " [" << ex.reason() << "]";
    THROW_MSG(base::exception{}, "Could not read image " << path);
  }

  LOG_DEBUG << "MAGICK = " << imageHandle_->magick;
  format_ = magickToFormat(imageHandle_->magick);
}

size_t Image::width() const
{
   return imageHandle_->columns;
}

size_t Image::height() const
{
   return imageHandle_->rows;
}

ImageFormat Image::format() const
{
  return format_;
}

void Image::write(const std::string& path)
{
  LOG_DEBUG << "Write image as " << path;
  LOG_DEBUG << "Current filename: " << imageHandle_->filename;

  ImageInfoHandle info{::CloneImageInfo(NULL)};
  std::strncpy(imageHandle_->filename, path.c_str(), MaxTextExtent);
  if (::WriteImage(*info, *imageHandle_) == MagickFalse)
  {
    LOG_ERROR << "Could not write image to: " << path;
    THROW_MSG(base::exception{}, "Could not write image to " << path);
  }
}

void Image::call(ImageAction* action)
{
   imageHandle_ = action->run(std::move(imageHandle_));
}
}
