#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#include "image.h"

namespace im {
class ImageFilter
{
public:
   virtual ~ImageFilter() { }
   virtual ImagePtr run(const ImagePtr& image) = 0;
};
}

#endif // IMAGEFILTER_H
