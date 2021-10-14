/**
 * @file
 */

#ifndef MODULES_COMMON_STATUS_STATUS_H_
#define MODULES_COMMON_STATUS_STATUS_H_

#include <string>

/**
 * @namespace apollo::common
 * @brief apollo::common
 */
namespace apollo {
namespace common {

// Error codes enum for API's categorized by modules.
enum ErrorCode {
    // No error, reutrns on success.
    OK = 0,

    // Control module error codes start from here.
    CONTROL_ERROR = 1000,
    CONTROL_INIT_ERROR = 1001,
    CONTROL_COMPUTE_ERROR = 1002,

    // Canbus module error codes start from here.
    CANBUS_ERROR = 2000,
    CAN_CLIENT_ERROR_BASE = 2100,
    CAN_CLIENT_ERROR_OPEN_DEVICE_FAILED = 2101,
    CAN_CLIENT_ERROR_FRAME_NUM = 2102,
    CAN_CLIENT_ERROR_SEND_FAILED = 2103,
    CAN_CLIENT_ERROR_RECV_FAILED = 2104,

    // Localization module error codes start from here.
    LOCALIZATION_ERROR = 3000,
};

std::string ErrorCode_Name(ErrorCode error) {
    return std::to_string(error);
}

/**
 * @class Status
 *
 * @brief A general class to denote the return status of an API call. It
 * can either be an OK status for success, or a failure status with error
 * message and error code enum.
 */
class Status {
  public:
    /**
     * @brief Create a success status.
     */
    Status() : code_(ErrorCode::OK), msg_() {}
    ~Status() = default;

    /**
     * @brief Create a status with the specified error code and msg as a
     * human-readable string containing more detailed information.
     * @param code the error code.
     * @param msg the message associated with the error.
     */
    Status(ErrorCode code, const std::string& msg) : code_(code), msg_(msg) {}

    /**
     * @brief generate a success status.
     * @returns a success status
     */
    static Status OK() { return Status(); }

    /**
     * @brief check whether the return status is OK.
     * @returns true if the code is ErrorCode::OK
     *          false otherwise
     */
    bool ok() const { return code_ == ErrorCode::OK; }

    /**
     * @brief get the error code
     * @returns the error code
     */
    ErrorCode code() const { return code_; }

    /**
     * @brief defines the logic of testing if two Status are equal
     */
    bool operator==(const Status& rh) const {
        return (this->code_ == rh.code_) && (this->msg_ == rh.msg_);
    }

    /**
     * @brief defines the logic of testing if two Status are unequal
     */
    bool operator!=(const Status& rh) const { return !(*this == rh); }

    /**
     * @brief returns the error message of the status, empty if the status is
     * OK.
     * @returns the error message
     */
    const std::string& error_message() const { return msg_; }

    /**
     * @brief returns a string representation in a readable format.
     * @returns the string "OK" if success.
     *          the internal error message otherwise.
     */
    std::string ToString() const {
        if (ok()) {
            return "OK";
        }
        return ErrorCode_Name(code_) + ": " + msg_;
    }

  private:
    ErrorCode code_;
    std::string msg_;
};

inline std::ostream& operator<<(std::ostream& os, const Status& s) {
    os << s.ToString();
    return os;
}

}  // namespace common
}  // namespace apollo

#endif  // MODULES_COMMON_STATUS_STATUS_H_
