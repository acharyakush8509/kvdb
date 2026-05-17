#pragma once
#include <cstdint>
#include <string>
#include <string_view>

namespace kvdb {

enum class StatusCode : uint8_t {
    OK             = 0,
    NOT_FOUND      = 1,
    IO_ERROR       = 2,
    PARSE_ERROR    = 3,
    BUFFER_FULL    = 4,  // BPM: all frames pinned, cannot evict
    KEY_TOO_LARGE  = 5,
    VAL_TOO_LARGE  = 6,
    INVALID_ARG    = 7,
    INTERNAL_ERROR = 8,
};

class Status {
public:
    // Factory constructors — using these, not the constructor directly
    static Status OK()          { return Status(StatusCode::OK, ""); }
    static Status NotFound(std::string_view msg = "")     { return Status(StatusCode::NOT_FOUND, msg); }
    static Status IOError(std::string_view msg)           { return Status(StatusCode::IO_ERROR, msg); }
    static Status ParseError(std::string_view msg)        { return Status(StatusCode::PARSE_ERROR, msg); }
    static Status BufferFull(std::string_view msg = "")   { return Status(StatusCode::BUFFER_FULL, msg); }
    static Status InternalError(std::string_view msg)     { return Status(StatusCode::INTERNAL_ERROR, msg); }

    bool ok()           const { return code_ == StatusCode::OK; }
    bool is_not_found() const { return code_ == StatusCode::NOT_FOUND; }
    StatusCode code()   const { return code_; }
    const std::string& message() const { return msg_; }

private:
    explicit Status(StatusCode c, std::string_view msg) : code_(c), msg_(msg) {}
    StatusCode  code_;
    std::string msg_;
};

} // namespace kvdb