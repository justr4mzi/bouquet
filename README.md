<!--
SPDX-FileCopyrightText: Copyright 2026 Eden Emulator Project
SPDX-License-Identifier: GPL-3.0-or-later
-->

<p align="center">
  <img src="dist/branding/bouquet_icon.png" alt="Bouquet" width="180">
</p>

<h1 align="center">Bouquet</h1>

<p align="center">
  <b>An experimental Nintendo Switch 2 emulator that gathers the best work of the Eglantine forks in one build.</b><br>
  Windows · Linux · macOS
</p>

---

## What is Bouquet?

The Switch 2 emulation scene moves fast and is spread over many forks of
[Eglantine](https://github.com/Djihads80/Eglantine): one is best for Mario Kart World, another
for Ocarina of Time, another for AMD graphics cards… Bouquet picks the best changes from each of
them and puts them in a single emulator, so you don't have to juggle five builds.

Bouquet starts from **[Lichii](https://github.com/zortos293/Lichii)** (the most active fork, with
the best Ocarina of Time support) and adds work from the forks listed below. **Every change keeps
its original author** in the git history, and every optimization Bouquet adds can be switched off
(see [Turning an optimization off](#turning-an-optimization-off)).

> [!WARNING]
> This is experimental software. Games may crash, show graphical errors or run slowly.
> You need your own legally dumped games, keys and firmware. Bouquet ships none of them.

## Download

Get the latest build from the **[Releases page](https://github.com/justr4mzi/bouquet/releases)**.

| Your computer | File to download |
| --- | --- |
| Windows, Ryzen or Intel 4th gen and newer (almost every PC from 2014 on) | `bouquet-windows-x86_64-pgo-avx2.zip` (fastest) |
| Windows, older CPU | `bouquet-windows-x86_64-pgo.zip` |
| Windows, graphical problems with the builds above | `bouquet-windows-x86_64.zip` (MSVC) |
| Linux | `bouquet-linux-x86_64-pgo.AppImage` |
| Mac with Apple Silicon (M1 and newer) | `bouquet-macos-arm64.zip` |

The **PGO** builds are compiled with clang and a performance profile, the way Eden and Selevet
build theirs. The **AVX2** build also targets modern CPUs (x86-64-v3).

## Setting it up

1. **Extract** the zip anywhere (for example `C:\Games\Bouquet`) and run `bouquet.exe`.
2. **Keys and firmware**: Bouquet keeps its own data folder so it never touches the config of
   your other emulators:
   - Windows: `%APPDATA%\bouquet`
   - Linux: `~/.local/share/bouquet` and `~/.config/bouquet`
   - macOS: `~/Library/Application Support/bouquet`

   Copy your `keys` folder and install your firmware there (or from the **File** menu), exactly as
   you did for Eglantine, Lichii or Eden.
   *Portable mode:* create an empty folder named `user` next to `bouquet.exe` and Bouquet keeps
   everything in it instead.
3. **Add your games folder** (double-click the game list) and launch a game.

## Recommended settings

| Game | Tips |
| --- | --- |
| **Mario Kart World** | Turn on **Mario Kart World: dynamic FPS (experimental)** in Configure → Graphics → Advanced, then restart the game. Expect drops while new tracks load their textures. |
| **The Legend of Zelda: Ocarina of Time** | The built-in **Max Resolution** and **Dynamic FPS** patches are on by default (Add-Ons tab): the game keeps its normal speed even below 60 fps. On AMD, if parts of the picture are black or the game hangs, see [Known issues](#known-issues). |
| **Donkey Kong Bananza** | **Donkey Kong Bananza: dynamic FPS** is on by default (same tab): the game follows real time instead of slowing down. Frame generation can be toggled in game with **Ctrl+G**. |
| **Pokémon Pokopia** | Works out of the box. |
| **Splatoon Raiders** | Works out of the box. |

## What's inside

Bouquet = **Lichii** (`nx2`) + the changes below. The commit history shows each one with its
author.

| From | What it brings |
| --- | --- |
| [Lichii](https://github.com/zortos293/Lichii) (zortos293 and contributors) | The base: Ocarina of Time boot and rendering, built-in Max Resolution and Dynamic FPS patches, the AMD black-scene fix, Frizti's performance work, the 17 "perf9" GPU-thread optimizations, MWAITX waits on Ryzen, FSR3 fixes |
| [Eglantine](https://github.com/Djihads80/Eglantine) (Djihads80 and contributors) | Upstream fixes: H0_NH1 half-precision source, NVDEC end of stream, pipeline cache recovery, Turing MME register reads, small-BAR staging buffer, x64 call reach, Switch 2 channel state, atomic exit flags, GPU device fallback, memory manager reference counts |
| [Selevet](https://github.com/sylvieistaken/selevet-eglantine) (Sylvie) | Semaphore acquires that skip the GPU-thread drain (already met, or met by a queued release), SEM_EXECUTE without a drain, GPU wait polling, high process priority, VRR reported to the game |
| [SmileyTatsu](https://github.com/SmileyTatsu/Eglantine) | Cheaper ASTC texture scan and decode (less stutter when textures stream in), guest RAM released when a game stops |
| [Eglantine-DKB](https://github.com/monteger8/Eglantine-DKB) (monteger8, adamd) and [Orchid](https://github.com/MythosOfs/Orchid) | Buffer-cache shortcuts (unchanged vertex buffers, repeated written ranges), empty draws skipped, Donkey Kong Bananza macro DMA reads without a full drain |
| ZendNevs (via Eglantine-DKB) | Donkey Kong Bananza dynamic FPS, frame generation toggle in game (Ctrl+G) |

## Turning an optimization off

If something looks wrong after an update, the cause is often one optimization. Each one has a
switch. Copy `nx2_switches.txt` (next to `bouquet.exe`) to your data folder
(`%APPDATA%\bouquet\nx2_switches.txt` on Windows), remove the `#` in front of the line you want,
and restart Bouquet. The "Bouquet" section at the end of that file lists every optimization
Bouquet adds, with where it comes from.

## Reporting a problem

Open an [issue](https://github.com/justr4mzi/bouquet/issues) and attach:

- the log file `eden_log.txt` (the **Log Folder** entry in the menu bar opens its folder);
- the game and its version, your CPU, your graphics card and its driver version;
- what you did and what went wrong (a screenshot helps a lot).

## Known issues

- **Ocarina of Time** runs at about 30 fps on most PCs: the emulator's GPU threads are the limit,
  not your graphics card. It plays at normal speed thanks to the Dynamic FPS patch.
- **AMD graphics cards**: most testing in the scene is done on NVIDIA. Bugs specific to AMD are
  possible; logs from AMD users are very welcome.
- **Donkey Kong Bananza**: later areas are still slow.

## Building from source

Bouquet builds like Eglantine and Lichii: see the [build guide](docs/Build.md). The release
binaries come from [.github/workflows/release-binaries.yml](.github/workflows/release-binaries.yml).

## Credits

Bouquet only gathers other people's work. All credit goes to the developers of
[Lichii](https://github.com/zortos293/Lichii), [Eglantine](https://github.com/Djihads80/Eglantine),
[Selevet](https://github.com/sylvieistaken/selevet-eglantine),
[SmileyTatsu's fork](https://github.com/SmileyTatsu/Eglantine),
[Orchid](https://github.com/MythosOfs/Orchid),
[Eglantine-DKB](https://github.com/monteger8/Eglantine-DKB),
[Eden](https://git.eden-emu.dev/eden-emu/eden) and yuzu. Please don't report Bouquet bugs to them.

Bouquet is put together by [justr4mzi](https://github.com/justr4mzi) with the help of Claude (AI).

## License

GPL-3.0-or-later, like Eden and Eglantine. See [LICENSE.txt](LICENSE.txt).

*"Nintendo Switch" is a trademark of Nintendo. Bouquet is not affiliated with Nintendo in any way.
This software should not be used to play games you have not legally obtained.*
