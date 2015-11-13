#include "exceptioninfo.h"

namespace im {
ExceptionInfo::ExceptionInfo() : handle_{::AcquireExceptionInfo()}
{
}

::ExceptionInfo* ExceptionInfo::native()
{
  return *handle_;
}

std::string ExceptionInfo::reason() const
{
  return handle_->reason;
}
}
