#ifndef IM_RESIZE_FILTER_H
#define IM_RESIZE_FILTER_H

#include <cstddef>
#include "imagefilter.h"

namespace im {
class ResizeFilter : public ImageFilter
{
public:
   ResizeFilter() = default;
   ResizeFilter(size_t width, size_t height);
   ResizeFilter(size_t width, size_t height, bool keep_aspect_ratio);

   ImagePtr run(const ImagePtr& image) override;

private:
   std::size_t width_{0};
   std::size_t height_{0};
   bool keep_aspect_ratio_{false};
};
}

#endif // RESIZEIMAGE_H
