#ifndef SRC_EXCEPTION_H_
#define SRC_EXCEPTION_H_

#include <exception>
#include <string>
#include <memory>
#include <boost/format.hpp>

namespace tfc {

/**
 * @brief Class to represent an run time error
 *
 * This class encapsulates run time error
 */
class Exception : public std::exception {
 public:
  enum class ErrorCode: uint8_t{
    KEY_NOT_FOUND
  };

  Exception(ErrorCode code, const boost::format& msg)
      : code_(code)
      , msg_(boost::str(msg)) {}

  Exception(ErrorCode code, const std::string& msg)
      : code_(code)
      , msg_(msg) {}

  Exception(ErrorCode code, const char* msg)
      : code_(code)
      , msg_(msg) {}

  virtual ~Exception() noexcept  = default;

  /**
   * @return the error description and the context as a text string.
   */
  virtual const char* what() const noexcept {
    return msg_.c_str();
  }

  ErrorCode err_code() const noexcept {
    return code_;
  }

  ErrorCode code_;
  std::string msg_;
};

}  // namespace tfc

#endif  // SRC_EXCEPTION_H_
