#ifndef IMAGEACTION_H
#define IMAGEACTION_H

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

//class Action
//{
//private:
//  class Concept
//  {
//  public:
//    virtual ~Concept() {}
//    virtual ImageHandle run(const ImageHandle& image) = 0;
//  };

//  template<typename T>
//  class Model : Concept
//  {
//  public:
//    explicit Model(T object) : object_(object) { }

////  private:
////    virtual ImageHandle run(const ImageHandle &image) override
////    {
//////      return object
////    }
//  };
//};
}

#endif
