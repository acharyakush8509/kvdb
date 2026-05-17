#pragma once
#include <string>
#include <cstddef>
#include <cstdint>

namespace kvdb {

struct Config {
    // ─── Network Settings ────────────────────────────────────────────────────
    uint16_t port{6379};             // Default to Redis port for easy CLI testing
    std::string host{"127.0.0.1"};   // Bind to localhost for security

    // ─── Storage Settings ────────────────────────────────────────────────────
    std::string db_file_path{"store.db"};
    std::string wal_file_path{"store.wal"};
    
    // Buffer pool size: 1024 frames * 4KB page size = 4MB RAM footprint
    size_t buffer_pool_size{1024};   

    // ─── Factory Method ──────────────────────────────────────────────────────
    // Loads configuration from default values or Environment Variables
    static Config Load();
};

} // namespace kvdb