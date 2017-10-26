#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <unordered_map>

#include "node.h"
#include "exception.h"

namespace tfc {

// class to represent tensorflow graph
// this class store all nodes, and it is the owner of these nodes
class Graph {
 public:
  using NodeMap = std::unordered_map<std::string, std::unique_ptr<Node>>;
  using iterator = NodeMap::iterator;
  using const_iterator = NodeMap::const_iterator;

  Graph() noexcept = default;

  inline void AddNode(const std::string name, std::unique_ptr<Node>&& node) {
    nodes_.insert(std::pair<std::string, std::unique_ptr<Node>>(name,
        std::move(node)));
  }

  inline Node& operator[](const std::string& name) {
    try {
      return *nodes_.at(name);
    } catch (std::out_of_range& e) {
      throw Exception(Exception::ErrorCode::KEY_NOT_FOUND, e.what());
    }
  }

  inline const Node& operator[](const std::string& name) const {
    return this->operator[](name);
  }

  inline iterator begin() noexcept {
    return nodes_.begin();
  }

  inline const_iterator begin() const noexcept {
    return nodes_.begin();
  }

  inline iterator end() noexcept {
    return nodes_.end();
  }

  inline const_iterator end() const noexcept {
    return nodes_.end();
  }

 private:
  NodeMap nodes_;
  std::vector<std::string> input_nodes_;
  std::vector<std::string> output_nodes_;
};

}  // namespace tfc

#endif  // SRC_GRAPH_H_
