#ifndef IM_HANDLE_H
#define IM_HANDLE_H

#include <type_traits>
#include <utility>

namespace im {
template<typename T, T* (*D)(T*)>
struct MagickFunctionDeleterHelper
{
  void operator()(T* obj)
  {
    D(obj);
  }
};

template<typename T, void (*D)(T*)>
struct VoidFunctionDeleterHelper
{
  void operator()(T* obj)
  {
    D(obj);
  }
};

// precondition: D() does not throw
template<typename T, typename D>
class Handle
{
  static_assert(std::is_nothrow_constructible<D>::value,
                "Constructor of the deleter must not throw.");

public:
  Handle() = default;

  explicit Handle(T* ptr) : ptr_{ptr} {}

  Handle(const Handle&) = delete;

  Handle(Handle&& other) : ptr_{other.ptr_}
  {
    other.ptr_ = nullptr;
  }

  ~Handle()
  {
    if (ptr_)
    {
      D{}(ptr_);
    }
  }

  Handle& operator=(const Handle&) = delete;
  Handle& operator=(Handle&& other)
  {
    Handle tmp = std::move(other);
    std::swap(tmp.ptr_, ptr_);
    return *this;
  }

  Handle& operator=(T* ptr)
  {
    Handle tmp(ptr);
    std::swap(tmp.ptr_, ptr_);
    return *this;
  }

  T* operator->()
  {
    return ptr_;
  }

  const T* operator->() const
  {
    return ptr_;
  }

  T* operator*()
  {
    return ptr_;
  }

  const T* operator*() const
  {
    return ptr_;
  }

  explicit operator bool()
  {
    return (ptr_ != nullptr);
  }

private:
  T* ptr_{nullptr};
};
}

#endif
