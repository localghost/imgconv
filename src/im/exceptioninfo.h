#ifndef IM_EXCEPTIONINFO_H
#define IM_EXCEPTIONINFO_H

#include <im/handle.h>
namespace im {
struct ExceptionInfoHandleDeleter
{
  void operator()(::ExceptionInfo* info)
  {
    ::DestroyExceptionInfo(info);
  }
};
using ExceptionInfoHandle = Handle<ExceptionInfo, ExceptionInfoHandleDeleter>;
}

#endif
