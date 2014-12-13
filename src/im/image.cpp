#include "image.h"

#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

#include "imagefilter.h"

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
}

Image::Image(const std::string& path)
{
   read(path);
}

void Image::read(const std::string& path)
{
  std::cerr << "read" << std::endl;
    ExceptionInfo* ex = AcquireExceptionInfo();
    ExceptionInfoPtr guard{ex, &DestroyExceptionInfo};
    info_.reset(AcquireImageInfo());
    std::strncpy(info_->filename, path.c_str(), MaxTextExtent);
    image_.reset(ReadImage(info_.get(), ex));
    if (!image_)
        throw std::runtime_error(ex->reason);
}

size_t Image::width() const
{
   return image_->columns;
}

size_t Image::height() const
{
   return image_->rows;
}

void Image::write(const std::string& path)
{
  std::cerr << "write" << std::endl;
    std::strncpy(image_->filename, path.c_str(), MaxTextExtent);
    WriteImage(info_.get(), image_.get());
}

void Image::apply_filter(ImageFilter* filter)
{
   image_ = filter->run(image_);
}
}
