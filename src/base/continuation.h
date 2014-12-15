#ifndef BASE_CONTINUATION_H
#define BASE_CONTINUATION_H

class continuation
{
public:
  template<typename T>
  typename std::remove_reference<T>::type& set_task(T&& t)
  {
    return callable_.set_action(std::move(t));
  }

private:
  callable callable_;
};

#endif
