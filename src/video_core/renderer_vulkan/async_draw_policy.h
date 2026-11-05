// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <cstddef>
#include <cstdlib>

#include "common/common_types.h"

namespace Vulkan {

inline bool CanDiscardPendingDraw(bool native, bool depth_enabled, u32 index_count,
                                    u32 vertex_count) {
    // Native draws can produce persistent resources, even with depth enabled.
    // EDEN_NX2_ASYNC_SKIP=1 (from selevet-eglantine) skips the small ones anyway while their
    // pipeline builds: fewer stalls on new scenery, at the risk of missing effects.
    if (native) {
        static const bool skip_native = [] {
            const char* value = std::getenv("EDEN_NX2_ASYNC_SKIP");
            return value != nullptr && value[0] == '1';
        }();
        return skip_native && (index_count > 6 && vertex_count > 6);
    }
    // Preserve the legacy async-shader heuristic.
    return depth_enabled || (index_count > 6 && vertex_count > 6);
}

constexpr bool DefersShaderEmission(bool native, size_t pending, size_t capacity) {
    return native && pending < capacity;
}

} // namespace Vulkan
