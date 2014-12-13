#ifndef LOG_H
#define LOG_H

#include <iostream>

#define LOG(x) \
  do { \
    std::cerr << x << std::endl; \
  } while (false)

#endif
