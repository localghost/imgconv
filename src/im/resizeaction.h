#ifndef IM_RESIZEACTION_H
#define IM_RESIZEACTION_H

#include <cstddef>
#include "imageaction.h"

namespace im {
class ResizeAction : public ImageAction
{
public:
   ResizeAction() = default;
   ResizeAction(size_t width, size_t height);
   ResizeAction(size_t width, size_t height, bool keep_aspect_ratio);

   void width(std::size_t w);
   void height(std::size_t h);
   void keep_aspect_ratio(bool keep);

   ImageHandle run(ImageHandle image) override;

private:
   std::size_t width_{0};
   std::size_t height_{0};
   bool keep_aspect_ratio_{false};
};
}

#endif
