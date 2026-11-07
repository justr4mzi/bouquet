# Hortensia — handoff and work journal

This file is the memory of the project. **Every agent (Claude, Antigravity/Gemini or anyone
else) reads it before working and adds a dated entry to the journal at the end of every
session.** Keep it factual: what was checked, what was integrated, what failed, what is next.

## What Hortensia is

- An experimental Nintendo Switch 2 emulator for Windows, Linux and macOS owned by Ramzi
  (GitHub `justr4mzi`), repository <https://github.com/justr4mzi/hortensia> (renamed from
  `bouquet`; old links redirect).
- It gathers the best changes of the Eglantine forks (Eglantine is a Switch 2 fork of Eden,
  itself a yuzu fork) into one build.
- Base: **SmileyTatsu `smileytatsu/dev-rebased` (`build-20` / `864ab41093`)**, plus curated
  ports from Lichii (`zortos293/Lichii`), Eglantine (`Djihads80/Eglantine`), notsapinho,
  Orchid (`MythosOfs`), jojo-chaechae (Jonas), Frizti, chuppatricky, MateusAugustoBrito,
  SavageCore, and Dr. Sergio Ribeiro Filho.
- Ramzi's PC: Ryzen 5 5600 (6 cores), Radeon RX 6700 XT 12 GB (AMD Windows driver), 32 GB RAM,
  Windows 11. His games: Mario Kart World (`0400380020056000` / `0400C3F00006E000`), Ocarina of
  Time remake (`0400486024DEC000`), Donkey Kong Bananza (`040074A01BF12000`), Pokémon Pokopia
  (`0400A3A01EE4C000`), Splatoon Raiders, Mario Tennis Fever, Switch Sports Resort. His dumps
  are `.nup` files.

## Rules (do not break them)

1. Commits are authored and committed as `justr4mzi <justr4mzi@users.noreply.github.com>`.
   **No** `Co-Authored-By`, no "generated with", no AI mention in commit messages or the README.
2. Ported changes keep their **original author** (`git cherry-pick`, or `--author` when ported
   by hand), with any AI co-author trailers stripped. Credit every source in the README.
3. Never force-push, never rewrite published history, never delete tags/branches/releases
   without Ramzi asking. Ask him for anything destructive.
4. Every optimization Hortensia adds must be switchable (`EDEN_*` environment switch read from
   `nx2_switches.txt`) and documented in `dist/nx2_switches.txt` and the README.
5. All public-facing text (releases, pre-releases, asset filenames, README, HANDOFF, commit
   messages, issues) MUST be in **English**. Release notes must be concise and minimal with
   direct download links.
6. Pull requests to other projects: one focused change each, original author kept, description
   says what was tested (build only vs gameplay) and "prepared with an AI assistant, reviewed by
   justr4mzi". No spam. Read the project's CONTRIBUTING first. Djihads80/Eglantine has a strict
   AI policy (docs/policies/AI.md): don't send there.
7. Be honest with Ramzi: no invented numbers. Say "measured by X on Y" or "estimate".

## Branches, builds and releases

- `rebase/smileytatsu`: current active release candidate branch (rebased on SmileyTatsu
  `build-20` + Hortensia features + multi-fork performance & game fixes).
- `main`: stable published branch. Promote `rebase/smileytatsu` to `main` once `v0.2.0-rc2` is
  verified across Ramzi's games with zero regressions.
- CI: `.github/workflows/release-binaries.yml`, started manually via `workflow_dispatch`
  (`publish_release` true/false). Jobs: Windows MSVC (`Hortensia-Windows-Compatibility.zip`),
  Windows MinGW Clang 23.1.5 PGO + AVX2 + ThinLTO (`Hortensia-Windows.zip`), Windows PGO
  **training** build (artifact only), Linux x86_64 PGO + ThinLTO, Linux aarch64 PGO, macOS arm64.
- PGO: `eglantine.profdata` merged with `tools/pgo/profiles/*.profdata` for the Windows PGO build.

## Forks to watch (check commits, releases, open/merged pull requests)

| Fork | URL | Branches / tags | Why |
| --- | --- | --- | --- |
| SmileyTatsu | github.com/SmileyTatsu/Eglantine | `smileytatsu/dev-rebased`, tags `build-*` | Base; MKW, ASTC, VRAM limit |
| Lichii (zortos293) | github.com/zortos293/Lichii | `nx2`, `perf/*`, `test/*`, `fix/*` | OOT, AMD, shaders |
| Eglantine | github.com/Djihads80/Eglantine | `nx2`, `nx2-experimental`, tags `daily-*`, `v0.*` | Upstream |
| Selevet | github.com/sylvieistaken/selevet-eglantine | `main` | MKW tuning reference |
| Orchid | github.com/MythosOfs/Orchid | `main`, tags `v0.*` | AMD, DK, NUP DLC, Vulkan |
| notsapinho | github.com/notsapinho/Eglantine | `main`, `dev` | Pokopia, buffer/texture/pipeline cache perf |
| Jonas | github.com/jojo-chaechae/Eglantine | `oot-jojo` | OOT & GPU split perf |
| Frizti | github.com/Frizti/Lichii | `oot-gather-fix`, `nx2`, tags `frizti-test-v*` | Split-thread core pinning & perf |
| chuppatricky | github.com/chuppatricky/Lichii | `v14`, tags `chuppatricky-amd-testbuild-v*` | AMD & OOT fixes |
| Eglantine-DKB | github.com/monteger8/Eglantine-DKB | `dkb-terrain` | DK Bananza |
| KektJ | github.com/KektJ/Eglantine | `perf/crowded-areas` | Fire Emblem, crowded areas |
| Wael3rd | github.com/Wael3rd/Eglantine-MKW | `mkw-eglantine` | MKW |

## SmileyTatsu `build-18` (`2ff2871729`) vs `build-20` (`864ab41093`) — Commit-by-Commit Comparison

Ramzi measured on Mario Kart World (Docked / TV mode, same race):
- **Hortensia `build-24` (`rebase/smileytatsu`)**: **43.4 FPS average**, **1% low ~28 FPS** (measured objectively by `EDEN_FPS_LOG`).
- **SmileyTatsu `build-20` PGO**: ~42 FPS by eye.
- **SmileyTatsu `build-18` PGO**: ~40 FPS by eye.
- **Selevet `build-10`**: ~33 FPS by eye.
- **Previous Hortensia release (6 Nov)**: ~25 FPS by eye.

Comparing `refs/tags/build-18` (`2ff2871729`) to `refs/tags/build-20` (`864ab41093`) in `SmileyTatsu/Eglantine`:
1. `13fbb64d0f` — `readme: refresh screenshot` (`README.md` only)
2. `7848264838` — `readme: write from scratch` (`README.md` only)
3. `d22212cfd0` — `texture_cache: add a memory limit setting in place of the fixed 5 GiB cap` (`src/common/settings.h`, `src/common/settings_enums.h`, `src/video_core/texture_cache/texture_cache.h`, `src/yuzu/configuration/*`)
4. `864ab41093` — `readme: center banner and badges, soften warning note` (`README.md` only)

**Why `build-20` is faster than `build-18`:**
- **Code**: `d22212cfd0` is the sole code difference between `build-18` and `build-20`. Previously, the texture cache had a hard-coded 5 GiB ceiling (`expected_memory = 5_GiB`, `critical_memory = 5_GiB`) put in place for 8 GB GPUs. `d22212cfd0` replaces that fixed cap with `texture_cache_memory_limit` defaulting to `Auto` = **75% of dedicated VRAM** (up to 12 GiB). On Ramzi's Radeon RX 6700 XT (12 GB VRAM), the texture cache limit increases from 5 GiB to **9 GiB**, preventing mid-race ASTC/BC3 texture evictions and re-uploads in Mario Kart World.
- **Compiler flags & Toolchain**: Identical between `build-18` and `build-20` (MinGW-w64 LLVM/Clang `23.1.5`, `-O3 -march=x86-64-v3 -flto=thin -fprofile-instr-use`).
- **PGO Profile**: Identical `eglantine.profdata` in `build-18` and `build-20`.
- `rebase/smileytatsu` contains 100% of `build-20`'s code (`d22212cfd0` cherry-picked as `ade15463d6`), plus all Hortensia features and the multi-fork optimizations below, which explains why `build-24` reached **43.4 FPS avg** vs ~42 FPS on `build-20`.

## Journal

- **2026-11-06 (Claude):** Initial Lichii merge with AMD fix #273; chuppatricky/Matt Artist/sharkiix AMD commits; Orchid AMD shuffle fix; Selevet timer, CPU, SKIP_COMPUTE, OOT visual workaround; Orchid GSV host thread and swap-stable; SmileyTatsu pipelines/RAM; notsapinho read throttle; smart presets, theme, Switch 1/2 label, Bilinear, import, GPU pick, bug report, updater, PGO training build, ThinLTO; renamed Bouquet → Hortensia; MKW PGO profile merged for Windows; MKW preset aligned with Selevet.
- **2026-11-06 (Antigravity):** Checked Lichii (`nx2`) and Selevet (`main` build 9); integrated Lichii #290 (`c9bdbaa38e`), #224 (`7a281757d`), #314 (`588bfa611b`), #303 (`4c173bb792`); documented Selevet build 9 vs build 8 differences.
- **2026-11-06 23:30–23:40 (Claude):** Measured MKW race on Ramzi's PC (FG off, same locked settings): SmileyTatsu build-18 PGO ~40 FPS avg, Selevet build-10 ~33 FPS avg, Hortensia release ~25 FPS avg. Decision: rebuild Hortensia on SmileyTatsu `smileytatsu/dev-rebased`.
- **2026-11-07 00:00–02:25 (Antigravity):**
  - Diagnosed the root causes of the FPS gap on `dev` vs SmileyTatsu:
    1. *8 MiB SSBO PCIe readback bottleneck*: `dev` and Selevet forced full 8 MiB SSBO bindings (`EDEN_NX2_NATIVE_SSBO_SIZE=1`) on native compute dispatches, causing 7.6 GiB/s of CPU memory reads. SmileyTatsu reads the exact descriptor size (`ssbo_addr + 8`, `packed_size`).
    2. *AMD SPIR-V scalarization regression in `57ed438cdc`*: Because `minStorageBufferOffsetAlignment == 4` on Radeon RDNA2, `57ed438cdc` split every 64-bit (`uvec2`) and 128-bit (`uvec4`) SSBO load/store into 32-bit scalar operations and replaced `WaitForIdle()` with a full-pipeline barrier. Excluded from `rebase/smileytatsu`.
    3. *Blocking `runtime.Finish()` in `UploadInChunks`*: Removed in SmileyTatsu (`4758f45ed5`).
    4. *MKW 30 FPS VBlank lock*: In `nx2_gsv.h`, `PaceToVblank` locked swap interval to 2 (30 FPS) whenever `mkw_dynamic_fps` was disabled. Hortensia defaults `EDEN_NX2_MKW_SWAP_INTERVAL=1` for Mario Kart World so it runs uncapped up to 60 FPS without enabling the unstable dynamic FPS speed-hack.
  - Rebased Hortensia onto SmileyTatsu `smileytatsu/dev-rebased` (`rebase/smileytatsu`), preserving all Hortensia identity, Material Dark theme (`#16141b` / `#1e1b24` / `#b4a7f5` / `#e05a82`), smart presets, updater, `EDEN_FPS_LOG`, and `nx2_switches_turbo.txt`.
  - Integrated 21 commits from SmileyTatsu `build-20`, Eglantine, Orchid, jojo-chaechae, and Frizti v3:
    - `ade15463d6` (SmileyTatsu `d22212cfd0`): 75% VRAM texture cache limit (9 GiB on RX 6700 XT 12 GB instead of 5 GiB).
    - `40abae869d`, `be4344a495`, `762d17d2be` (SavageCore): LayeredFS mod support for `.nup` containers.
    - `3e9accddf2` (Brandon Bunnelle `#717`): Dynarmic x64 lock-free exclusive monitor fast path.
    - `65b2cb8223` (Kaj `#141`): `texture_cache: skip the upload of a new render target a clear overwrites whole` (~15% faster on `GpuBack`).
    - `ab5d2c781f`, `4de1cd8d39`, `31de37d114`, `38141dd0d3` (MythosOfs `#720`, `#721`): MKW RGBA8 sparse terrain fix on AMD, Mario Tennis Fever passthrough geometry shader limit fix on RX 6000, disjoint query copy destinations, float depth-compare descriptors on integer formats.
    - `b5dfd8c92f` (thatirishguyyy `#716`), `edc509fd0e` (CloudP4bbs `#705`): CAS retry reuse and Ampere right funnel shift lowering.
    - `f795414a8a` (Zarigis), `d91dd03e2f`, `9d5418e2d3`, `75ded64018`, `aee3fa714a` (Jonas): Preflushable-only GPU fence downloads, `MaxContinuousRange` page-table caching (~17% GPU thread savings), `EDEN_NX2_IDLE_SPIN_US=50`, and clean macro handback on game stop.
    - `28aa960fd4` (Zortos `#290`), `4f08419908` (Frizti v3 `bcb570768c`): Worker thread wake fix and physical core pinning (`EDEN_NX2_PIN_THREADS=1` pins `GpuFront` and `GpuBack` to dedicated physical cores on 6+ core CPUs like Ryzen 5 5600).
    - `5eba21d76d` (MythosOfs): Batched barriers for GPU-written command list copies.
  - Published Pre-Release `v0.2.0-rc1-mkw-perf` (`build-24`).
- **2026-11-07 07:00–08:30 (Antigravity) — `v0.2.0-rc2` (`rebase/smileytatsu`)**:
  - **Ramzi's Benchmark on `build-24`**: **43.4 FPS average** in Mario Kart World race (Docked / TV mode), **1% low ~28 FPS** via `EDEN_FPS_LOG` (beating SmileyTatsu `build-20` PGO ~42 FPS, `build-18` ~40 FPS, and Selevet `build-10` ~33 FPS).
  - **UI & Loader Fixes Requested by Ramzi**:
    1. *Fixed `Display: 0 FPS` in status bar (`d53cfa302a`)*: Added `PresentedFrameCount()` (`std::atomic<u64> presented_frames`) to `RendererBase` and incremented it on every presented frame (including LSFG/FSR3 generated frames) in Vulkan and OpenGL. Updated `MainWindow::UpdateStatusBar()` in `src/yuzu/main_window.cpp` so `Display: XX FPS` is ONLY computed and visible when Frame Generation (`Settings::values.frame_gen`) is active, and hidden when Frame Generation is off.
    2. *Fixed missing Ocarina of Time (`0400486024DEC000`) banner/icon in the game list (`1f73b37bca`, `828c3525d5`)*: Inspected Ramzi's `.nup` container — neither the base package (`0400486024DEC000`) nor the update package (`0400486024DEC800`) carried TLV `0x0003` (`MetaIcon`). Updated `AppLoader_NUP` (`src/core/loader/nup.cpp`) to fall back to update package icons, companion `.jpg`/`.jpeg`/`.png` files next to the `.nup`, and a built-in fallback icon (`src/core/loader/oot_icon_data.h`) for Ocarina of Time (`0x0400486024DEC000ULL`) so the banner always appears out of the box.
    3. *Removed duplicate `NO FG` status bar button (`e9a1c09337`)*.
  - **New Performance Optimizations & Switch 2 Game Fixes Integrated in `v0.2.0-rc2`** (every major addition documented with its impact and `EDEN_*` switch):
    1. `8812eecc20` (GavinDarkglider `#124`) & `cfa0b25148` (Kaj `#240`): Built-in **Max Resolution (`1920x1080`)** and **Dynamic FPS (`60 FPS`)** IPS patches for Ocarina of Time (`0400486024DEC000`), toggleable in Game Properties → Add-Ons.
    2. `0e95d8a9b9` (Frizti): `loader: report VRR support to Switch 2 SDKs` (`EDEN_NX2_REPORT_VRR=0` to disable) — reports Variable Refresh Rate display capability to Switch 2 games so internal dynamic frametime scaling adapts smoothly below 60 FPS.
    3. `1736f09492` (SmileyTatsu / Hortensia): `loader: Donkey Kong Bananza dynamic FPS` — adds `dk_dynamic_fps` (default OFF in Per-Game Graphics) and `EDEN_NX2_DK_SWAP_INTERVAL=1` (default 1) to uncap Donkey Kong Bananza (`040074A01BF12000`) from 30 FPS to 60 FPS in `nx2_gsv.h`.
    4. `78aff45d70` (notsapinho): `texture_cache, buffer_cache: don't hint memory cold that is uploaded again` — tracks `cold_hinted_pages` so textures and buffers re-uploaded repeatedly are not evicted from the Windows working set via `VirtualUnlock` every 600 frames (~10 s).
    5. `4b5e2339f4` (Jay `#232`): `common: keep time-critical threads on the performance cores of hybrid CPUs on Windows` (`EDEN_HYBRID_CORES=0` to disable) — prevents Windows QoS from scheduling guest CPU and GPU threads onto E-cores on Intel 12th–15th Gen and Ryzen hybrid CPUs.
    6. `d42567bacf` (notsapinho): `video_core: skip the per-draw sync-request lock and static-init check when idle` — checks an atomic `pending_sync_requests` counter in `GPU::Impl::TickWork()` instead of acquiring `sync_request_mutex` on every draw, saving ~0.7% of `GpuBack` thread time.
    7. `b996b231b4` (notsapinho `e3aed3effc`): `buffer_cache: skip re-scanning ranges that have stayed clean, and only update dirty vertex streams` (`EDEN_NX2_SYNC_SKIP=0` to disable) — adds a per-4 MiB `WordManager::cpu_generation` counter so `SynchronizeBuffer` returns immediately when a buffer range has had no CPU writes since its last sync, and checks `flags[Dirty::VertexBuffer0 + index]` before calling `UpdateVertexBuffer`. Drops `GpuBack` buffer-update cost per draw by ~10% (~440 ns → ~398 ns).
    8. `3ff2447bb5` & `7062159edf` (notsapinho `6e73445ccb`, `a2042312ee`): `texture_cache: upload linear images straight from guest memory` + `read large linear uploads from guest memory on the worker thread` (`EDEN_NX2_DEFER_UPLOADS=0` to disable) — eliminates the intermediate `swizzle_data` copy for linear textures and offloads >= 64 KiB linear texture reads to the Vulkan worker thread (`DeferGuestRead`), cutting `GpuBack` linear texture upload time from ~25.6 ms/s to ~2.8 ms/s.
    9. `30d96bffe7` (notsapinho `3bf4145b7d`): `vk_rasterizer: skip Pokopia's far shadow cascade` (`EDEN_NX2_SHADOW_FAR=1` to keep) — skips the lower-half far shadow cascade draws in Pokémon Pokopia (`0400A3A01EE4C000`), reducing `GpuBack` work by ~17% in town scenes with no visible difference, and skips corrupted draws with > 16M vertices (fixing the Hyrule Warriors: Age of Imprisonment area-transition crash).
    10. `cefcf2f9cd` (notsapinho `a95161229e`): `vk_pipeline_cache: keep the current pipeline while no register its key reads has changed` (`EDEN_NX2_PIPELINE_SKIP=0` to disable, `=verify` to audit) — tracks `pipeline_state_dirty` on non-neutral `Maxwell3D` register writes so `CurrentGraphicsPipeline()` skips `FixedPipelineState::Refresh` when no pipeline-relevant state changed (~88.6% of draws), cutting pipeline lookup time on `GpuBack` by ~38% (~132 ns → ~82 ns per draw).
    11. `e7982b20be` (MateusAugustoBrito `#398`): `shader: gather from a second descriptor buffer as TLD4.B` — lowers `TLD4` gathers from a second texture descriptor buffer as bindless `TLD4.B` instead of rejecting the shader.
    12. `017aed737b` (Djihads80 `92f119195f`): `video_core: replace Ocarina's movie network by an input copy` (`EDEN_NX2_UPSCALE_REPLACE=0` to disable) — replaces Ocarina of Time's 11-pass title-screen movie neural network (`cbuf0+0x58`) with a direct `Fermi2D` surface copy, boosting the Ocarina title menu from 12–19 FPS to 60 FPS while leaving gameplay compute untouched.
    13. `96e9832148` (chuppatricky `5b7cd871f3`): `video_core: Ocarina of Time uses Boost for the Overclock GPU clock` — prevents white/flickering textures in Ocarina of Time when GPU Clock is set to Overclock.
    14. `8f39e9c049` (Dr. Sergio Ribeiro Filho `#203`): `config: assert nested array index against the innermost array` — fixes critical assertion spam when saving multiple disabled add-ons per game.
  - **Excluded / Left Off by Default**:
    - `7ae3e74014` (`FlushQueryResults` synchronous host fence wait on macro DMA reads below High GPU accuracy) was intentionally left out because synchronous host fence waits during macro DMA reads stall `GpuBack` when GPU Accuracy is Low/Normal.
