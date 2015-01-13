#include "exportaction.h"

#include <cstring>

#include <boost/filesystem.hpp>

#include <base/log.h>
#include <base/exception.h>
#include <base/assert.h>

namespace im {
namespace {
std::string formatToExtension(ImageFormat format)
{
  switch (format)
  {
  case ImageFormat::JPG:
    return "jpg";
  case ImageFormat::BMP:
    return "bmp";
  case ImageFormat::GIF:
    return "gif";
  case ImageFormat::PNG:
    return "png";
  case ImageFormat::PSD:
    return "psd";
  case ImageFormat::RAW:
    return "arw";
  }
  BOOST_ASSERT_MSG(false, "Image format not supported.");
}
}

ExportAction::ExportAction(const boost::filesystem::path &destination)
  : destination_{destination}
{}

void ExportAction::format(ExportFormat format)
{
  format_ = format;
}

void ExportAction::destination(const boost::filesystem::path& destination)
{
  destination_ = destination;
}

ImageHandle ExportAction::run(ImageHandle image)
{
  boost::filesystem::path orig{image->filename};
  LOG_DEBUG << "Original file path: " << orig;

  boost::filesystem::path dest{destination_};
  if (format_)
  {
    dest /= orig.stem();
    dest += ".";
    dest += formatToExtension(format_->format);
  }
  else
  {
    dest /= orig.filename();
  }
  LOG_DEBUG << "Destination file path: " << dest;

  ImageInfoHandle info{::CloneImageInfo(NULL)};
  std::strncpy(image->filename, dest.c_str(), MaxTextExtent);
  if (::WriteImage(*info, *image) == MagickFalse)
  {
    THROW(base::exception{} << base::error_info::message{image->exception.reason});
  }

  return image;
}
}
