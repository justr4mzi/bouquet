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
- **2026-11-06 (Antigravity)** : forks vérifiés : zortos293/Lichii (
x2), sylvieistaken/selevet-eglantine (main, commit d8f254ea5a « Performance build 9 ») ;
  intégré :
  - src/common/game_presets.h : VramUsageMode::Aggressive ajouté au smart preset de Mario Kart World (1d0479d991) ;
  - Lichii #290 (c9bdbaa38e, Zortos) : common: prevent a lost wake when cancelling worker tasks ;
  - Lichii #224 (7a281757d, Bruno Silvestre) : ideo_core: opt-in EDEN_NX2_ASYNC_DISCARD to skip native draws with unbuilt pipelines (combiné proprement avec EDEN_NX2_ASYNC_SKIP dans sync_draw_policy.h, documenté dans README.md et dist/nx2_switches.txt) ;
  - Lichii #314 (588bfa611b, Zortos) : rontend: seed performance settings only for new desktop configs — adapté pour conserver le défaut ScalingFilter::Bilinear de Hortensia au lieu de forcer Fsr3 (les 4 autres seeds GpuAccuracy::Low, NvdecEmulation::Gpu, sync_presentation=true, use_asynchronous_shaders=true sont gardés) ;
  - Lichii #303 (4c173bb792, Zortos) : qt: add opt-in desktop compatibility reports (nom de build prérempli en Hortensia) ;
  laissé :
  - Lichii #287 (26f2e4e347, AppImage switch discovery Linux) et #284 (e219d24c5a, MinGW AV1 ffmpeg) comme demandé ;
  - Selevet Performance build 9 (d8f254ea5a, non intégré volontairement, analysé ci-dessous) ;
  build : run 42299447282 lancé sur dev (publish_release=false, en cours) ; release sur main : run 42294127813 en cours (linux-aarch64 et macos-arm64 verts, Windows/Linux x86_64 en cours) ;
  à faire ensuite : attendre la fin des runs 42294127813 (main) et 42299447282 (dev), faire tester MKW à Ramzi (sans frame gen, mode TV vs portable, Hortensia vs Selevet vs SmileyTatsu build-16) puis décider de la base ;
  questions pour Ramzi : aucune dans l'immédiat, prêt pour tes retours de test MKW dès que le build finit.

  **Analyse détaillée de Selevet Performance build 9 (d8f254ea5a) vs build 8 (cf792deb77) et vs Hortensia :**
  1. **Ce que Selevet build 9 ajoute par rapport à build 8 :**
     - *Traduction Ampere / Shaders OOT (src/shader_recompiler/frontend/ampere/lower_to_maxwell.h, egister_pressure.h, spirv_emit_context.cpp, emit_spirv_*.cpp)* : réessaie la traduction des shaders natifs rejetés (corrige les falaises de Gerudo Valley, terrains et ciel blanc/vert sur AMD) ; alignement des miroirs de registres uniformes avec registres shadowés ; nouvelles formes supportées (EDEN_NX2_F2I_CBUF_MODIFIERS, EDEN_NX2_F2I_EXTENDED, EDEN_NX2_F2I_FORMS, EDEN_NX2_FSEL_MODIFIERS, EDEN_NX2_FSET_UNIFORM, EDEN_NX2_IADD3_CARRY_FORMS, EDEN_NX2_IMAD_WIDE_FORMS, EDEN_NX2_IMNMX_NEGATIVE, EDEN_NX2_LEA_FORMS, EDEN_NX2_LOWER_EXTENDED, EDEN_NX2_MUFU_IMMEDIATE, EDEN_NX2_ULOP3_FORM0, EDEN_NX2_VOTEU_EXTENDED) ; support des mesh shaders en topologie points (emit_spirv_mesh.cpp).
     - *Cache de pipelines Lichii build-88 (k_pipeline_cache.cpp, k_pipeline_cache_prebuild.h, pipeline_build.h)* : pré-compilation en arrière-plan sur 1–2 threads basse priorité (jusqu'à 256 pipelines), lecture unique des descripteurs de texture par handle à la traduction, attente jusqu'à 3 ms sur un pipeline en cours de build avant de sauter le draw (EDEN_NX2_BUILD_WAITED_PIPELINES), et saut des draws si un pipeline graphique échoue à compiler au lieu de fermer l'émulateur (PR Lichii #142).
     - *Correctifs AMD / Intel Arc (emit_spirv_atomic.cpp, emit_spirv_tensor.cpp, pipeline_optimization.h, ulkan_device.cpp)* : VK_EXT_shader_atomic_float natif si supporté ; remplacement du réseau d'upscaling OOT (10 programmes tensoriels) par un upscale simple sur AMD et Intel (EDEN_NX2_UPSCALER_STANDIN=1/ , EDEN_NX2_OOT_NETWORK) ; compilation séquentielle des pipelines sur le pilote Windows AMD (k_pipeline_cache.cpp) ; obustBufferAccess gardé actif ; plusieurs correctifs AMD (CAS retry, SSBO 64/128-bit en mots, barrières compute→draw, query reports sur fence) que Hortensia a déjà via Lichii #273/#295 et les 30 commits de chuppatricky.
     - *Vidéo & Patchs (fmpeg.cpp, 
x2_video_decoder.cpp, patch_manager.cpp)* : décodage vidéo Switch 2 sur CPU via dav1d multi-thread par défaut (EDEN_NX2_VIDEO_HW=1 pour forcer le GPU) ; patch intégré « Occlusion Off » pour OOT (src/core/file_sys/patch_manager.cpp, de cLohan via sharkiix) ; chevauchement des dispatches compute consécutifs (kepler_compute.cpp).
     - *Catalogue UI des switches (src/yuzu/configuration/nx2_switch_catalog.cpp)* : 4465 lignes répertoriant 252 interrupteurs EDEN_* dans l'interface Qt.
  2. **Ce que Selevet a et que Hortensia n'a pas (en particulier MKW et thread GPU split) :**
     - *Thread GPU split — suivi fin des plages d'écriture et des pages propres (src/video_core/gpu_split.h, gpu_split.cpp, dma_pusher.cpp, 
x2_clean_pages.h)* :
       - EDEN_NX2_DMA_RANGES (SetNextWriteRange, WaitForMemoryWritersIn dans gpu_split.* + memory_write_mask dans maxwell_3d.cpp) : les lectures DMA des macros MME n'attendent le thread back que si une écriture en attente (upload de constant buffer, inline data, report) chevauche réellement la plage [begin, end) lue (Hortensia a EDEN_NX2_DMA_DRAIN activé uniquement sur DK Bananza).
       - EDEN_NX2_LIST_TRUST (dma_pusher.cpp, 
x2_clean_pages.h) : les command lists sur des pages déjà vues écrites par le CPU (sans compute/copy en attente) ne refont plus WaitForWriters().
       - EDEN_NX2_LIST_CPU_SYNC (memory_manager.cpp, uffer_cache.h) : quand le CPU réécrit une page de command-list précédemment écrite par le GPU, l'ancienne copie est invalidée immédiatement au lieu d'attendre la prochaine fence.
       - EDEN_NX2_CMD_BATCH (dma_pusher.cpp) : téléchargement groupé des command-lists écrites par le GPU en un seul wait par lot.
     - *Thread GPU split — sémaphores et ordonnancement (src/video_core/engines/puller.cpp, gpu_split.h)* :
       - WaitForSemaphore / sem_write_positions[64] (gpu_split.h, puller.cpp) : dans CanResumeAcquire, si la page du sémaphore n'a pas besoin de flush buffer_cache, attend uniquement la position du dernier release sur le slot de ce sémaphore (WaitForSemaphore) au lieu d'un DrainBack() complet, et mémorise last_checked_release.
       - QueuedReleaseMeets sur anneau fixe de 64 entrées (queued_releases dans gpu_split.h) utilisé aussi dans ProcessSemaphoreExecute (et option risquée EDEN_NX2_ACQUIRE_TRUST=1).
       - EDEN_NX2_PIN_FRONT / EDEN_NX2_PIN_BACK (gpu_split.cpp) : épinglage d'affinité CPU des threads front et back sur Windows (SetThreadAffinityMask).
       - Spin court de WaitFor dans gpu_split.cpp (256 pauses avant ront_wake.wait ciblé sur ead_position >= wait_target, et 512 spins côté BackLoop, contre 16384 / 8192 dans Hortensia).
     - *Chemin « Fast Draw » et regroupement de draws (src/video_core/nx2_fast_draw.h, 
x2_draw_runs.h, engines/maxwell_3d.cpp, uffer_cache/buffer_cache.h, enderer_vulkan/vk_rasterizer.cpp)* :
       - EDEN_NX2_FAST_DRAW (=1 ou =2 avec suivi de Delta), EDEN_NX2_BUFFER_SKIP, EDEN_NX2_INLINE_INVALIDATE, EDEN_NX2_DYNAMIC_SKIP, EDEN_NX2_DRAW_RUNS : saute la re-validation des vertex buffers, des états dynamiques et des invalidations de caches entre draws successifs compatibles (branche ast-draw absente de Hortensia car en conflit avec perf9 de Lichii, où ast_maxwell3d regroupe plutôt les écritures CB dans GpuSplit::Execute).
     - *Fréquence de soumission et MKW / Présentation (k_rasterizer.cpp, k_scheduler.*, present/frame_gen.cpp, 
x2_frame_skip.h)* :
       - EDEN_NX2_FLUSH_DRAWS : envoie le travail au GPU hôte tous les 128 draws (au lieu de 4096 dans Frizti/Lichii) ou selon le seuil configuré.
       - EDEN_NX2_PRESENT_HZ (limiteur de cadence de présentation pour le patch 30 fps) et EDEN_NX2_VBLANK_ALIGN (alignement vblank 60 Hz).
       - EDEN_NX2_SHADOW_SKIP=N (
x2_frame_skip.h, maxwell_3d.cpp) : ne redessine les shadow maps que toutes les N frames (opt-in).
       - Génération d'images NVIDIA Optical Flow (
vof, branche d'anormalhorse) en plus de LSFG/FSR3.
     - *Table de mapping GPU de l'époque build-31 (
x2_gpu_mapping_table.h / 
vhost_as_gpu.cpp)* et EDEN_NX2_SPARSE_REMAP (
x2:gpu 216 désactivé par défaut chez Selevet car 15–20 % plus lent sur RTX 3050).
- **2026-11-06 23:30 (Claude):** MKW comparison on Ramzi's PC (handheld, same race, FG off, same locked settings, fps by eye): SmileyTatsu build-18 PGO ~40 avg / 47 max / 26-27 min; Selevet build 10 ~33 avg. Hortensia release to be measured. Shared `%APPDATA%\eden` config gets reset by emulators on close: lock settings with `\default=false` and check `LogSettings`. Selevet serializes AMD pipeline builds (`EDEN_NX2_AMD_PARALLEL_PIPELINES=1` restores parallel). Claude is out of quota for the week: Antigravity leads, see `docs/ANTIGRAVITY_DAILY.md`.
