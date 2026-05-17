#pragma once
#include "include/common/types.h"
#include <cstring>

namespace kvdb {

/**
 * @class Page
 * @brief The fundamental physical memory block of the database.
 * A Page is exactly 4096 bytes (PAGE_SIZE). This class wraps that raw byte array
 * with metadata required by the Buffer Pool Manager to track its state in RAM.
 */
class Page {
public:
    Page() { ResetMemory(); }
    ~Page() = default;

    // ─── Data Access ─────────────────────────────────────────────────────────
    // Returns a pointer to the raw 4KB memory block
    inline char* GetData() { return data_; }
    
    // ─── Metadata Access ─────────────────────────────────────────────────────
    inline page_id_t GetPageId() const { return page_id_; }
    inline int GetPinCount() const     { return pin_count_; }
    inline bool IsDirty() const        { return is_dirty_; }

    // ─── Buffer Pool Management ──────────────────────────────────────────────
    // Zeroes out the memory and resets all metadata trackers
    inline void Wipe() {
        ResetMemory();
        page_id_ = INVALID_PAGE_ID;
        pin_count_ = 0;
        is_dirty_ = false;
    }

private:
    // The Buffer Pool Manager is the only system allowed to alter page metadata
    friend class BufferPoolManager; 
    
    inline void ResetMemory() { std::memset(data_, 0, PAGE_SIZE); }

    // ─── Physical Memory ─────────────────────────────────────────────────────
    char data_[PAGE_SIZE]{};             // The actual 4096-byte payload

    // ─── In-Memory Metadata (Not written to disk) ────────────────────────────
    page_id_t page_id_{INVALID_PAGE_ID}; // The physical disk page ID this memory represents
    int pin_count_{0};                   // Number of concurrent threads accessing this page
    bool is_dirty_{false};               // True if memory was modified and needs writing to disk
};

} // namespace kvdb