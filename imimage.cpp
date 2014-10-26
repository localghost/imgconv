#include "imimage.h"

#include <cstring>
#include <stdexcept>
#include <QDebug>

namespace {
void adjust_size_to_aspect_ratio(Image* image, size_t& width, size_t& height)
{
    if (width > height)
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

IMImage::IMImage(const std::string& path)
{
   read(path);
}

void IMImage::read(const std::string& path)
{
    qDebug("read");
    ExceptionInfo* ex = AcquireExceptionInfo();
    ExceptionInfoPtr guard{ex, &DestroyExceptionInfo};
    info_.reset(AcquireImageInfo());
    std::strncpy(info_->filename, path.c_str(), MaxTextExtent);
    image_.reset(ReadImage(info_.get(), ex));
    if (!image_)
        throw std::runtime_error(ex->reason);
}

void IMImage::write(const std::string& path)
{
    qDebug("write");
    std::strncpy(image_->filename, path.c_str(), MaxTextExtent);
    WriteImage(info_.get(), image_.get());
}

void IMImage::resize(size_t width, size_t height, bool keep_aspect_ratio)
{
   if (width == 0 || height == 0)
   {
      qDebug() << "Invalid size";
      return;
   }
    qDebug("resize");

    qDebug() << "current size: " << image_->columns << "x" << image_->rows;

    if (keep_aspect_ratio)
        adjust_size_to_aspect_ratio(image_.get(), width, height);
    qDebug() << "new size: " << width << "x" << height;

    ExceptionInfo* ex = AcquireExceptionInfo();
    ExceptionInfoPtr guard{ex, &DestroyExceptionInfo};
    ImagePtr tmp{ResizeImage(image_.get(), width, height, LanczosFilter, 1.0, ex), &DestroyImage};
    if (!tmp)
        std::runtime_error(ex->reason);
    std::swap(tmp, image_);
}
