#include "common/config.h"
#include <cstdlib>

namespace kvdb {

Config Config::Load() {
    Config cfg;

    // Override defaults if specific Environment Variables are set in the terminal
    if (const char* port_env = std::getenv("KVDB_PORT")) {
        cfg.port = static_cast<uint16_t>(std::atoi(port_env));
    }
    if (const char* host_env = std::getenv("KVDB_HOST")) {
        cfg.host = host_env;
    }
    if (const char* db_env = std::getenv("KVDB_DB_PATH")) {
        cfg.db_file_path = db_env;
    }
    if (const char* pool_env = std::getenv("KVDB_BUFFER_POOL_SIZE")) {
        cfg.buffer_pool_size = static_cast<size_t>(std::atol(pool_env));
    }
    
    return cfg;
}

} // namespace kvdb