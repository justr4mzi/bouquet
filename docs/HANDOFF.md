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
- Base: **zortos293/Lichii `nx2`** (merged up to 6 Nov 2026 17:00, including the AMD fix #273),
  plus ports from Selevet, Orchid, SmileyTatsu, chuppatricky/Matt Artist/sharkiix (AMD),
  notsapinho, Frizti, Eglantine-DKB/ZendNevs, Jonas. The README lists every change and its source.
- Ramzi's PC: Ryzen 5 5600 (6 cores), Radeon RX 6700 XT 12 GB (AMD Windows driver 2.0.353 on
  6 Nov — old), 32 GB RAM, Windows 11. His games: Mario Kart World (`0400C3F00006E000`), Ocarina
  of Time remake (`0400486024DEC000`), Donkey Kong Bananza (`040074A01BF12000`), Pokémon Pokopia,
  Splatoon Raiders, Mario Tennis Fever, Switch Sports Resort. His dumps are `.nup` files.

## Rules (do not break them)

1. Commits are authored and committed as `justr4mzi <justr4mzi@users.noreply.github.com>`.
   **No** `Co-Authored-By`, no "generated with", no AI mention in commit messages or the README.
2. Ported changes keep their **original author** (`git cherry-pick -x`, or `--author` when ported
   by hand). Credit every source in the README.
3. Never force-push, never rewrite published history, never delete tags/branches/releases
   without Ramzi asking. Ask him for anything destructive.
4. Every optimization Hortensia adds must be switchable (`EDEN_*` environment switch read from
   `nx2_switches.txt`) and documented in `dist/nx2_switches.txt` and the README.
5. Pull requests to other projects: one focused change each, original author kept, description
   says what was tested (build only vs gameplay) and "prepared with an AI assistant, reviewed by
   justr4mzi". No spam. Read the project's CONTRIBUTING first. Djihads80/Eglantine has a strict
   AI policy (docs/policies/AI.md): don't send there.
6. Be honest with Ramzi: no invented numbers. Say "measured by X on Y" or "estimate".

## Branches, builds and releases

- `dev`: work branch. `main`: what is published. Push to `dev`, check the build, then `main`.
- CI: `.github/workflows/release-binaries.yml`, started by hand
  (Actions → release-binaries → Run workflow, `publish_release` true/false). Jobs: Windows MSVC
  (`Hortensia-Windows-Compatibility.zip`), Windows MinGW clang PGO + AVX2 + ThinLTO
  (`Hortensia-Windows.zip`), Windows PGO **training** build (artifact only), Linux x86_64 PGO +
  ThinLTO, Linux aarch64 PGO, macOS arm64.
- PGO: `eglantine.profdata` (general) merged 1:2 with `tools/pgo/profiles/*.profdata` (Ramzi's Mario
  Kart World sessions, recorded with the training build) for the Windows build.
- Training a new profile: run the `windows-x86_64-pgo-train` artifact, play, close, run
  `merge-profile.bat`, add the resulting `.profdata` to `tools/pgo/profiles/`.
- `gh` works through the session proxy for `repos/justr4mzi/hortensia/...`; repository settings
  (description, topics) must be changed in the browser.

## Forks to watch (check commits, releases, open/merged pull requests)

| Fork | URL | Branches / tags | Why |
| --- | --- | --- | --- |
| Lichii (zortos293) | github.com/zortos293/Lichii | `nx2`, `perf/*`, `test/*`, `fix/frizti-*`, `exp/*`, `port/*` | Base; OOT; AMD |
| Eglantine | github.com/Djihads80/Eglantine | `nx2`, `nx2-experimental`, tags `daily-*`, `v0.*` | Upstream |
| Selevet | github.com/sylvieistaken/selevet-eglantine | `main` (`tuned/README.md` explains each build) | Fastest MKW on Ramzi's PC |
| Orchid | github.com/MythosOfs/Orchid | `main`, tags `v0.*` | AMD, DK, NUP DLC |
| SmileyTatsu | github.com/SmileyTatsu/Eglantine | `smileytatsu/dev-rebased` | MKW, ASTC |
| notsapinho | github.com/notsapinho/Eglantine | `main`, `dev` | Pokopia |
| Jonas | github.com/jojo-chaechae/Eglantine | `oot-jojo` | OOT perf |
| Frizti | github.com/Frizti/Lichii | `oot-gather-fix`, `nx2` | Split-thread perf |
| chuppatricky | github.com/chuppatricky/Lichii | tags `chuppatricky-amd-testbuild-v*` | AMD fixes |
| Eglantine-DKB | github.com/monteger8/Eglantine-DKB | `dkb-terrain` | DK Bananza |
| KektJ | github.com/KektJ/Eglantine | `perf/crowded-areas` | Fire Emblem, crowded areas |
| Wael3rd | github.com/Wael3rd/Eglantine-MKW | `mkw-eglantine` | MKW |
| eden-fefw | github.com/xDarkWindx/eden-fefw | `main` | Ideas only |
| Fork guide | github.com/riyadhHDA/wichforks | — | Comparison of forks |

`.github/workflows/fork-watch.yml` lists the new commits of these forks every morning (issue
"Fork watch") without AI; an agent still has to read them in detail.

## Method that works

1. `git fetch --depth N <url> +refs/heads/<branch>:refs/<name>/<branch>`, then
   `git log --no-merges <our-base>..refs/<name>/<branch>` and `git cherry HEAD <ref>` to skip
   what is already in.
2. Cherry-pick in order; an empty pick means it is already in; on conflicts, resolve by hand only
   when the change is understood, else skip and note it here.
3. Build on `dev`, read the first error of each failing job
   (`gh api repos/justr4mzi/hortensia/actions/jobs/<id>/logs`), fix, rebuild.
4. Update README (what's inside, switches, what was left out) and this journal.

## What was tried / decided (6 Nov 2026)

- Base = Lichii `nx2` (most active, best OOT). Selevet is built on zortos293/Eglantine build 31 +
  Lichii build-67 + Frizti v2 + more; its window says Lichii.
- **MKW gap:** Ramzi measured Selevet ≈ +10 fps over Bouquet build-9 in a race (Bouquet 22-30
  fps). Log comparison: Bouquet ran with **frame generation on (LSFG 2x)**, Immediate fences,
  uncompressed ASTC, synchronous presentation; Selevet with frame generation off, Default
  fences, BC3, asynchronous presentation. The MKW preset now matches Selevet's settings. Code
  differences (build-31 era optimizations, Frizti v2 split-thread work, Lichii fast-draw branch)
  still need a measured comparison with frame generation off on both.
- Not integrated yet: Lichii fast-draw branch (old, conflicts), Frizti's newest acquire/CB-upload
  work (conflicts with Selevet acquire ports), chuppatricky's scheduler and OOT fog modes,
  Orchid 0.8.0 (NUP DLC, per-game profiles, shader fixes), Pokopia 120-360 fps mods, Selevet
  build 9 (6 Nov 21:04).
- Open bugs on Ramzi's PC: DK Bananza crashes at a scene start (log ends during pipeline
  builds, AMD driver 2.0.353); OOT loads forever (built-in Max Resolution/Dynamic FPS were
  disabled in Add-ons in that run). First thing to try: update the AMD driver, enable both OOT
  add-ons, `EDEN_NX2_AMD_SAFE_COMPILE_GRAPHICS=1` for DK.
- Pull requests opened: zortos293/Lichii #296 (ASTC, SmileyTatsu), sylvieistaken/selevet-eglantine
  #19 (MKW/DK dynamic FPS lookup, SmileyTatsu). Ramzi's forks `justr4mzi/lichii` and
  `justr4mzi/selevet-eglantine` must stay until they are merged.

## Fallback rule for other agents

When an agent starts a session (in particular Antigravity in the morning): if this journal has
no entry dated today by Claude, or Ramzi says Claude is not available, the agent does the
morning round itself, in detail (each fork's commits, pull requests and releases, not only the
Fork watch list), integrates what is useful, builds on `dev`, publishes when green, and writes
its journal entry.

## Journal

- **2026-11-06 (Claude):** Lichii merge with AMD fix #273; 30 chuppatricky/Matt Artist/sharkiix
  AMD commits; Orchid AMD shuffle fix; Selevet timer, CPU, SKIP_COMPUTE, OOT visual workaround;
  Orchid GSV host thread and swap-stable; SmileyTatsu pipelines/RAM; notsapinho read throttle;
  smart presets, theme, Switch 1/2 label, Bilinear, import, GPU pick, bug report, updater, PGO
  training build, ThinLTO; renamed Bouquet → Hortensia (logo, data folder, log
  `hortensia_log.txt`, deep violet theme); MKW PGO profile merged for Windows; MKW preset
  aligned with Selevet. PRs #296 (Lichii) and #19 (Selevet). First public release started.
