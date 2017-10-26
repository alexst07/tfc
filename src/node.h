#ifndef SRC_NODES_H_
#define SRC_NODES_H_

#include <boost/variant.hpp>
#include <string>
#include <memory>
#include <vector>
#include <utility>


namespace tfc {

class AttrValue {
 public:
  // TODO: add the others types for variant
  using Value = boost::variant<std::string, uint64_t, float, bool>;

  explicit AttrValue(Value&& value): value_(std::move(value)) {}

 private:
  Value value_;
};

class Node {
 public:
  Node(const std::string& op, std::vector<std::string>&& inputs) noexcept
      : op_(op)
      , inputs_(std::move(inputs)) {}

  const std::string& op() const {
    return op_;
  }

  const std::vector<std::string>& inputs() const {
    return inputs_;
  }

 private:
  std::string op_;
  std::vector<std::string> inputs_;
};

}  // namespace tfc

#endif  // SRC_NODES_H_
