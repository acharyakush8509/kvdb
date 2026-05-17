# Development Log — KVDB Project

### Phase 1: Foundation & Global Configuration
**Date: May 17, 2026**

- **Implemented Modules:** `types.h`, `status.h`
- **Accomplishments:** 
    - Established global database type primitives (`page_id_t`, `frame_id_t`, `lsn_t`) ensuring explicit bit-width control across the codebase.
    - Defined the core physical geometry of the engine, anchoring the system to 4KB (4096 bytes) page layouts to match native Linux OS page sizes and optimize hardware alignment.
    - Built a custom, explicit `Status` class interface to enforce high-performance error handling, bypassing the heavy CPU overhead of standard C++ stack-unwinding exceptions.
    - Testing Status: Baseline headers compile cleanly with C++20 standard constraints. (using -fsyntax-only flag in c++ to fully parse and compile without looking for executable entry points).
- Implemented the `Config` manager (`config.h` / `config.cpp`) to handle dynamic database parameters (ports, buffer pool size, file paths) via environment variable overrides. Engineered the root `CMakeLists.txt` build pipeline to enforce strict C++20 standard compliance and `-Werror` compiler hardening.

### Phase 2: Storage Engine Foundation
**Date: May 18, 2026**

- **Implemented Modules:** `page.h`, `lru_replacer.h`, `lru_replacer.cpp`
- **Accomplishments:**
  - Initiated the Storage Engine layer.
  - Engineered the core `Page` class, representing the raw 4KB physical memory block used for all database I/O, strictly encapsulated for BPM access.
  - Engineered the `LRUReplacer` algorithm to manage Buffer Pool memory eviction.
  - Achieved O(1) constant-time eviction and pinning latency by coupling a `std::list` with a `std::unordered_map` for memory-address teleportation.
  - Ensured high-concurrency thread safety across the eviction queues using `std::mutex` and `std::lock_guard`.
- **Testing Status:** Storage foundation and LRU eviction algorithms compile cleanly into the `kvdb_core` static library.