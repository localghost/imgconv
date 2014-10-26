#ifndef IMIMAGE_H
#define IMIMAGE_H

#include <string>
#include <memory>
#include <magick/MagickCore.h>

class IMImage
{
public:
   IMImage() = default;
   explicit IMImage(const std::string& path);

   void read(const std::string& path);

   void write(const std::string& path);

   void resize(size_t width, size_t height, bool keep_aspect_ratio = true);

private:
   template<typename T, typename D, D del>
   struct scope_ptr
   {
      scope_ptr() {}

      explicit scope_ptr(T* value) : value{value} {}

      ~scope_ptr() { if (value) deleter(value); }

      void reset(T* value) { this->value = value; }

      T* get() const { return value; }

      T* operator->() const
      {
         return value;
      }

      explicit operator bool()
      {
         return value != nullptr;
      }

      T* value{nullptr};
      D* deleter{&del};
   };

   typedef std::unique_ptr<Image, decltype(&DestroyImage)> ImagePtr;
   typedef std::unique_ptr<ImageInfo, decltype(&DestroyImageInfo)> ImageInfoPtr;
   typedef std::unique_ptr<ExceptionInfo, decltype(&DestroyExceptionInfo)> ExceptionInfoPtr;

   ImagePtr image_{nullptr, &DestroyImage};
   ImageInfoPtr info_{nullptr, &DestroyImageInfo};
};

#endif // IMIMAGE_H
