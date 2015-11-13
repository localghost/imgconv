#ifndef IM_EXCEPTIONINFO_H
#define IM_EXCEPTIONINFO_H

#include <magick/MagickCore.h>
#include <im/handle.h>
#include <string>

namespace im {
using ExceptionInfoHandleDeleter = MagickFunctionDeleterHelper< ::ExceptionInfo, &::DestroyExceptionInfo>;
using ExceptionInfoHandle = Handle< ::ExceptionInfo, ExceptionInfoHandleDeleter>;

class ExceptionInfo
{
public:
  ExceptionInfo();
  ::ExceptionInfo* native();

  std::string reason() const;

private:
  ExceptionInfoHandle handle_;
};
}

#endif
