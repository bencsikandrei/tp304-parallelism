#ifndef PA_TREE_H
#define PA_TREE_H

#include <memory>
#include <vector>

template<typename Value>
class Tree {
  Value value_;
  std::vector<std::unique_ptr<Tree>> children_;

  public:
  Tree(Value const& value) : value_(value) {}

  void add_child(std::unique_ptr<Tree> child) {
    children_.emplace_back(std::move(child));
  }

  Value const& value() const 
  { 
    return value_;
  }

  void value(Value const& value) 
  { 
    value_ = value;
  }

  auto begin() const -> decltype(children_.begin()) 
  { 
    return children_.begin(); 
  }

  auto begin() -> decltype(children_.begin()) 
  { 
    return children_.begin(); 
  }

  auto end() const -> decltype(children_.end()) 
  { 
    return children_.end(); 
  }
  auto end() -> decltype(children_.end()) 
  { 
    return children_.end(); 
  }
  bool isleaf() const 
  { 
    return children_.empty();
  }
  std::size_t size() const 
  { 
    return children_.size(); 
  }

  std::vector<std::unique_ptr<Tree>> getChildren() 
  {
    return children_;
  }
  
};

template<typename Value>
std::unique_ptr<Tree<Value>> makeTree(Value const& value) {
  return std::unique_ptr<Tree<Value>>(new Tree<Value>{value});
}

#endif
