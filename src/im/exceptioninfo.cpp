#include "exceptioninfo.h"

namespace im {
ExceptionInfo::ExceptionInfo() : handle_{::AcquireExceptionInfo()}
{
}

::ExceptionInfo* ExceptionInfo::handle()
{
  return *handle_;
}

std::string ExceptionInfo::message() const
{
  return handle_->reason;
}
}
