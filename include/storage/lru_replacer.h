#pragma once
#include "common/types.h"
#include <list>
#include <unordered_map>
#include <mutex>

namespace kvdb {

class LRUReplacer {
public:
    // Initialize the replacer with the maximum number of frames it can track
    explicit LRUReplacer(size_t num_pages);
    ~LRUReplacer() = default;

    // ─── Core Operations ─────────────────────────────────────────────────────
    
    // Finds the least recently used frame, removes it from tracking, and outputs its ID.
    // Returns true if a victim was found, false if everything is pinned/empty.
    bool Victim(frame_id_t* frame_id);

    // A thread is actively using this frame. Remove it from the eviction queue.
    void Pin(frame_id_t frame_id);

    // A thread is done using this frame. Add it back to the eviction queue.
    void Unpin(frame_id_t frame_id);

    // Returns how many frames are currently eligible to be evicted
    size_t Size();

private:
    size_t capacity_;
    std::mutex latch_; // Ensures thread safety if multiple queries hit the DB at once

    // ─── LRU Data Structures ─────────────────────────────────────────────────
    // The list tracks the actual order. Front = most recently used. Back = least recently used.
    std::list<frame_id_t> lru_list_;
    
    // The hash map gives us O(1) lightning-fast lookups to find where a frame is in the list.
    std::unordered_map<frame_id_t, std::list<frame_id_t>::iterator> lru_hash_;
};

} // namespace kvdb