# Hortensia v0.2.0

Hortensia v0.2.0 is a high-performance Nintendo Switch emulator focused on stability, accuracy, and out-of-the-box optimization for demanding titles. This release rebases the entire codebase onto **SmileyTatsu build-20**, incorporates upstream fixes from **Lichii, Eglantine, Orchid, and notsapinho**, and introduces first-class multi-language onboarding, per-game recommended settings, and real-time performance diagnostics.

---

## What's New & Highlights

### 1. Foundation: SmileyTatsu build-20 Rebase
- Clean architecture rebase onto SmileyTatsu build-20, providing modern Maxwell/Ampere compute and graphics handling.
- Integrated upstream fixes from:
  - **Lichii (Zortos & kraibse)**:
    - `#439`: Enlarge Turing macro RAM beyond `0x1000` to execute native compute macros correctly.
    - `#438`: Proper macro handback to engines on GPU split stop.
    - `#425`: 64-byte block granularity tracking in buffer cache.
    - `#429`: Storage buffer routing for untracked 32-bit global atomics (IAdd, UMax, SMin, CAS loops).
    - `#435`: Virtual address range wrap-around validation.
    - `#485`: Zeroed page-table page retention.
    - `#443` & `#442`: Game directory scanning safety and migration strategy handling.
  - **Eglantine (Duck912 & kraibse)**:
    - Compute pipeline dynamic rebuilds upon late buffer allocation (`688c6fa7`).
    - Tightened frame synchronization for sensitive titles (`a23be213`).
    - Worker stop accounting under queue mutex (`45ebf0f7`).
  - **Orchid 0.9.0 (MythosOfs)**:
    - Simultaneous color feedback snapshot preservation (`63eaaba0`, `a2cefedfc4`).
    - Extended 64-bit addends for `IMAD.HI` (`c7d26dc2`).
  - **notsapinho**:
    - Compute shader vector alignment and CAS loop coherence for AMD RADV/RDNA architectures (`77875bb6`).

### 2. Kernel & Engine Game Fixes
- **The Legend of Zelda: Ocarina of Time**:
  - Implemented kernel SVC `WaitIfEqual64` (SVC 0x34 arbitration type 3), eliminating the userspace panic `0xf001` at 21 seconds.
  - Added display version parsing for loose dumps (`LooseDumpDisplayVersion`).
- **Donkey Kong Bananza & Nintendo Switch Sports**:
  - Complete DMA pushbuffer subindex and method count reset between submissions, preventing pushbuffer state desynchronization.
  - Matrix math HMMA emulation enabled by default.
  - Safe register indexing bounds for KeplerMemory and Fermi2D.
- **Pokémon Pokopia**:
  - Far shadow cascade preservation by default (`far_shadow_mode = 1`), restoring sky visibility.

### 3. User Experience & Productivity
- **First-Run Language Selector**: Prompt on initial startup to choose between Français, English, or System Default.
- **Persistent Recommended Settings**: Dialogue only prompts once on first run, saves preference to `qt-config.ini` (`recommended_settings_asked = true`).
- **Game List Context Menu**: Right-click any game to "Apply recommended settings" anytime.
- **Real-Time FPS Logger**: `EDEN_FPS_LOG` environment switch for frame-time and FPS logging.
- **Modern UI Theme**: Refined Hortensia dark theme styling.

---

## Real Performance Benchmarks (TV Mode, RX 6700 XT)

| Title | Target | Measured FPS | Status |
| --- | --- | --- | --- |
| **Mario Kart World** | 60 | **~42 FPS** (1% low ~25) | Stable, in-race performance |
| **Mario Tennis Fever** | 60 | **~58 FPS** | Full speed, clean input icons |
| **Pokémon Pokopia** | 60 | **~58 FPS** | Playable |
| **Nintendo Switch Sports** | 60 | **~47 FPS** | Playable |

---

## Known Issues

- **The Legend of Zelda: Ocarina of Time**: Now boots and plays (~25 FPS), but may encounter a crash after a few minutes or occasional temporary black screen (extended Ampere lowering in progress).
- **Donkey Kong Bananza**: Boots and runs up to 60 FPS, but missing ground textures in certain scenes and can freeze upon breaking specific blocks (pushbuffer command desynchronization under active investigation).
- **Splatoon Raiders**: Boots and runs at 60 FPS, but rendering appears very dark (shader lowering and post-processing pass under investigation).
- **Pokémon Pokopia**: Sky may still appear black on certain Vulkan driver configurations.

---

## Downloads

| Computer | File | Notes |
| --- | --- | --- |
| **Windows** (x86-64-v3 / AVX2) | [**Hortensia-Windows.zip**](https://github.com/justr4mzi/hortensia/releases/download/v0.2.0/Hortensia-Windows.zip) | MinGW Clang PGO-AVX2 build (Recommended for Ryzen & Intel 4th Gen+) |
| **Windows** (Compatibility) | [**Hortensia-Windows-Compatibility.zip**](https://github.com/justr4mzi/hortensia/releases/download/v0.2.0/Hortensia-Windows-Compatibility.zip) | MSVC build (All x86-64 CPUs) |
| **Linux** (x86_64) | [**Hortensia-Linux.AppImage**](https://github.com/justr4mzi/hortensia/releases/download/v0.2.0/Hortensia-Linux.AppImage) | Clang PGO AppImage (glibc 2.39+) |
| **Linux** (ARM64) | [**Hortensia-Linux-ARM.AppImage**](https://github.com/justr4mzi/hortensia/releases/download/v0.2.0/Hortensia-Linux-ARM.AppImage) | Clang PGO ARM64 AppImage |
| **macOS** (Apple Silicon) | [**Hortensia-macOS.zip**](https://github.com/justr4mzi/hortensia/releases/download/v0.2.0/Hortensia-macOS.zip) | Universal Apple Silicon bundle |
