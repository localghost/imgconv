#ifndef UI_ACTIONREGISTRY_H
#define UI_ACTIONREGISTRY_H

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <functional>

#include <ui/action.h>

class ActionRegistry
{
public:
  void registerFactory(std::string name, std::function<Action()> factory)
  {
    factories_[std::move(name)] = std::move(factory);
  }

  Action createAction(const std::string& name)
  {
    const auto it = factories_.find(name);
    if (it != factories_.end())
    {
      return (it->second)();
    }
    throw "no such factory";
  }

  std::vector<std::string> listActions() const
  {
    // TODO The names could be stored as a class member and updated
    // together with `factories_` (i.e. in `registerFactory()`). Here
    // const std::vector<std::string>& could be returned.
    std::vector<std::string> result;
    result.reserve(factories_.size());

    for (const auto& p : factories_)
    {
      result.push_back(p.first);
    }
    return result;
  }

private:
  std::map<std::string, std::function<Action()>> factories_;
};

#endif
