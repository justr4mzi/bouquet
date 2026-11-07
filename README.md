<!--
# SPDX-FileCopyrightText: Copyright 2026 Hortensia Contributors
# SPDX-License-Identifier: GPL-3.0-or-later
-->
<!-- lang: en-GB -->

<h1 align="center">
  <br>
  <b>Hortensia</b>
  <br>
</h1>

<h4 align="center"><b>Hortensia</b> is an experimental, performance-focused open-source Switch 2 emulator derived from SmileyTatsu, Lichii, and Eden/Eglantine.
It is written in C++ with portability in mind, providing optimized builds for Windows, Linux, and macOS.
</h4>

<p align="center">
  <a href="#about-hortensia">About Hortensia</a> |
  <a href="#compatibility--performance">Compatibility & Performance</a> |
  <a href="#known-issues">Known Issues</a> |
  <a href="#downloads">Downloads</a> |
  <a href="#building">Building</a> |
  <a href="#license">License</a>
</p>

## About Hortensia

Hortensia focuses on maximizing performance and compatibility for next-generation Switch 2 titles, combining:
- **SmileyTatsu build-20 PGO base**: Highly optimized instruction dispatch and memory management yielding peak frame rates on modern hardware.
- **AMD RDNA & Vulkan pipeline optimizations**: Elimination of multi-second compiler stalls via selective unoptimized pipeline compilation (`VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT`), memory barrier correctness (`COMPUTE_TO_GRAPHICS`), dynamic tap gather offsets, and misaligned SSBO splitting.
- **Native compute & tensor enhancements**: Native HMMA emulation, robust native branch lowering, and memory descriptor validation.
- **Smart per-game presets & frame pacing**: Automatic tailored settings for supported titles, customizable swap interval pacing (including 30 FPS locks), and optimized VRR reporting defaults.

## Compatibility & Performance

*Measured in TV / Docked Mode on an AMD Radeon RX 6700 XT with latest drivers:*

| Title | Status | Performance / Notes |
|---|---|---|
| **Mario Kart World** | **Playable** | **~43.4 FPS** average in-race (1% low ~28.5 FPS). Smooth frame pacing with VRR reporting disabled by default (`EDEN_NX2_REPORT_VRR=0`). |
| **Mario Tennis Fever** | **Playable** | **~58 FPS** stable. |
| **Pokémon Pokopia** | **Playable** | **~58 FPS** stable (note: sky rendering issue). |
| **The Legend of Zelda: Ocarina of Time** | **Testing** | Fixes included (HLE service commands 1050 / 201 / 101, stall shader bypass, SSBO alignment sync); currently being tested. |
| **Donkey Kong Bananza** | **Testing** | Fixes included (HMMA 0x23c compute emulation, unmapped buffer descriptor fix, RDNA geometry shader masking, optional `dk_30fps` lock); currently being tested. |
| **Splatoon Raiders** | **In Progress** | Not working yet in this release (fixes in progress for future releases). |
| **Nintendo Switch Sports Resort** | **In Progress** | Not working yet in this release (fixes in progress for future releases). |

## Known Issues

- **The Legend of Zelda: Ocarina of Time & Donkey Kong Bananza**: Fixes are included in this release and are currently undergoing hardware validation.
- **Splatoon Raiders & Nintendo Switch Sports Resort**: Do not boot or render yet on this version; fixes are under active development.
- **Controller UI**: Some button prompt icons appear as `?`.
- **Pokémon Pokopia**: The sky currently renders black in exterior environments.

## Downloads

Download the latest stable release and pre-compiled binaries from the [GitHub Releases page](https://github.com/justr4mzi/hortensia/releases).

- **Windows x64 / AVX2 (PGO)**: Recommended for modern x86-64 processors.
- **Linux x86_64 / AArch64**: Standard and PGO builds.
- **macOS Apple Silicon**: Universal ARM64 build.

## Building

See the [General Build Guide](docs/Build.md).

For development tooling and switches, check [dist/nx2_switches.txt](dist/nx2_switches.txt) and [docs/HANDOFF.md](docs/HANDOFF.md).

## License

Hortensia is licensed under the GPLv3 (or any later version). Refer to the [LICENSE.txt](LICENSE.txt) file.
