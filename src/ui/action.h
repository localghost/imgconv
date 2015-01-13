#ifndef ACTION_H
#define ACTION_H

#include <memory>
#include <vector>
#include <QString>
#include <im/image.h>
#include <im/imageaction.h>

//namespace im {
//class Image;
//}
//

class Action
{
public:
  virtual ~Action() = 0;
  virtual void configure() = 0;
  virtual std::unique_ptr<im::ImageAction> compile() = 0;
  virtual QString description() const = 0;
};

class Pipeline
{
public:
  void add_action(std::unique_ptr<Action> action)
  {
    pipeline.push_back(std::move(action));
  }

  void configure() // temporary
  {
    for (const auto& action : pipeline)
    {
      action->configure();
    }
  }

  // TODO compile im::Pipeline and run it (to not create new action for each image).
  void run(im::Image& image)
  {
    for (const auto& action : pipeline)
    {
      auto act = action->compile();
      image.call(act.get());
    }
  }

  const std::vector<std::unique_ptr<Action>>& get_actions() const
  {
    return pipeline;
  }

private:
  std::vector<std::unique_ptr<Action>> pipeline;
};

//class NewAction
//{
//private:
//  struct Concept
//  {
//    virtual ~Concept() {}
//    virtual void configure() = 0;
//    virtual void run(im::Image& image) = 0;
//  };

//  template<class MagickAction, class Configurator>
//  class Model : public Concept
//  {
//  public:
//    Model() : action_{new MagickAction{}} {}

//    void configure()
//    {
//      std::unique_ptr<Configurator> configurator{new Configurator{*action_}};
//      configurator->run();
//    }

//    void run(im::Image& image)
//    {
//      image.call(*action_);
//    }

//  private:
//    std::unique_ptr<MagickAction> action_;
//  };
//public:
//  template<class MagickAction, class Configurator>
//  NewAction() : impl{new Model<MagickAction, Configurator>{}} {}

//  void configure()
//  {
//    impl->configure();
//  }

//  void run(im::Image& image)
//  {
//    impl->run(image);
//  }

//private:
//  std::unique_ptr<Concept> impl;
//};

#endif // ACTION_H
