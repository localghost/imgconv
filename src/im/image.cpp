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
  THROW(base::exception{} << base::error_info::message{"Unsupported image format [" + std::string(magick) + "]"});
}
}

Image::Image(const std::string& path)
{
   read(path);
}

void Image::read(const std::string& path)
{
  LOG_DEBUG << "ENTER";
  ExceptionInfoHandle ex{::AcquireExceptionInfo()};
  info_ = ::AcquireImageInfo();
  std::strncpy(info_->filename, path.c_str(), MaxTextExtent);
  image_ = ::ReadImage(*info_, *ex);
  if (!image_)
  {
    LOG_ERROR << "Could not read image " << path << " [" << ex->reason << "]";
    THROW(base::exception{} << base::error_info::message{"Could not read image " + path});
  }
  format_ = magickToFormat(image_->magick);
  LOG_DEBUG << "MAGICK = " << image_->magick;
}

size_t Image::width() const
{
   return image_->columns;
}

size_t Image::height() const
{
   return image_->rows;
}

ImageFormat Image::format() const
{
  return format_;
}

void Image::write(const std::string& path)
{
  LOG_DEBUG << "Write image as " << path;
  LOG_DEBUG << "Current filename: " << image_->filename;
  ImageInfoHandle info{::CloneImageInfo(NULL)};
  std::strncpy(image_->filename, path.c_str(), MaxTextExtent);
  ::WriteImage(*info, *image_);
}

void Image::call(ImageAction* action)
{
   image_ = action->run(std::move(image_));
}
}
