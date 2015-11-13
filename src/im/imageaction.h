#ifndef IMAGEACTION_H
#define IMAGEACTION_H

#include <vector>
#include "image.h"

namespace im {
class ImageAction
{
public:
   virtual ~ImageAction() = 0;

   virtual ImageHandle run(ImageHandle image) = 0;

protected:
  ImageAction& operator=(const ImageAction&) = default;
};

class Pipeline
{
public:
  void add_action(std::unique_ptr<ImageAction> action)
  {
    actions_.push_back(std::move(action));
  }

  void run(Image & image)
  {
    for (const auto& action : actions_)
    {
      image.call(action.get());
    }
  }

private:
  std::vector<std::unique_ptr<ImageAction>> actions_;
};
}

#endif
