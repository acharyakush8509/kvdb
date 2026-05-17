#pragma once
#include <cstdint>
#include <cstddef>
#include <array>
#include <limits>

namespace kvdb {

// ─── Physical storage identifiers ────────────────────────────────────────────
using page_id_t  = uint32_t;   // Physical page number in store.db (0-indexed)
using frame_id_t = uint32_t;   // Index into BufferPoolManager's frames[] array
using slot_id_t  = uint16_t;   // Slot index within a single page

// ─── WAL / Transaction identifiers (reserved for Phase 2) ────────────────────
using lsn_t      = uint64_t;   // Log Sequence Number — monotonically increasing
using txn_id_t   = uint64_t;   // Transaction identifier

// ─── Sentinel values ─────────────────────────────────────────────────────────
constexpr page_id_t  INVALID_PAGE_ID  = std::numeric_limits<page_id_t>::max();
constexpr frame_id_t INVALID_FRAME_ID = std::numeric_limits<frame_id_t>::max();
constexpr lsn_t      INVALID_LSN      = 0;

// ─── Page geometry ────────────────────────────────────────────────────────────
constexpr size_t PAGE_SIZE        = 4096;   // 4 KB physical page (matches OS page)
constexpr size_t PAGE_HEADER_SIZE = 32;     // Bytes reserved at start of every page

// ─── B+ Tree structural limits (computed, not magic numbers) ─────────────────
constexpr uint16_t BTREE_LEAF_MAX_SLOTS     = 64;
constexpr uint16_t BTREE_INTERNAL_MAX_KEYS  = 128;

// ─── Page type tag (stored in PageHeader::page_type) ─────────────────────────
enum class PageType : uint8_t {
    INVALID   = 0,
    LEAF      = 1,   // B+ Tree leaf node — holds actual KV data
    INTERNAL  = 2,   // B+ Tree internal routing node — holds separator keys + child page_ids
    META      = 3,   // Reserved page 0: stores root_page_id, next_page_id, etc.
};

} // namespace kvdb