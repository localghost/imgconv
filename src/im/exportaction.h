#ifndef IM_EXPORTACTION_H
#define IM_EXPORTACTION_H

#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include <im/imageaction.h>

namespace im {
struct ExportFormat
{
  ImageFormat format;
  unsigned quality;
};

class ExportAction : public ImageAction
{
public:
  ExportAction() = default;
  explicit ExportAction(const boost::filesystem::path& destination);

  void format(ExportFormat format);
  void destination(const boost::filesystem::path& destination);

  ImageHandle run(ImageHandle image) override;

private:
  boost::optional<ExportFormat> format_;
  boost::filesystem::path destination_;
};
}

#endif
