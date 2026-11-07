# Contributing

Hortensia is an experimental Switch 2 emulator that gathers the best work of the Eglantine forks
(SmileyTatsu, Lichii, Selevet, Orchid, PokeDinner and others) into one build. You can help even
without writing code:

- Report a bug or a game that does not work: [open an issue](https://github.com/justr4mzi/hortensia/issues)
  (in the emulator: Help > Create Bug Report attaches the log for you).
- Share reproducible test results: game, build, GPU, driver, settings and the FPS lines of
  `hortensia_log.txt`.
- Improve the documentation or the [translations](./dist/languages/README.md).

## Code contributions

Hortensia is free, open-source, copyleft software under the
[GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html). By contributing you agree to license your
work under the same terms.

### Rules

- **Keep the original author.** When you bring a change from another fork, cherry-pick it
  (`git cherry-pick -x`) or set `--author` so the original author stays on the commit, and credit
  the source in the README.
- **Every optimization must be switchable.** Speed-ups and game-specific workarounds go behind an
  `EDEN_*` switch read from `nx2_switches.txt`, documented in `dist/nx2_switches.txt` and in the
  README, with its default value.
- **Measure, don't guess.** Performance changes need before/after numbers from the FPS log
  (`EDEN_FPS_LOG`), with the game, scene, GPU and settings used.
- **One focused change per pull request**, following the style of the surrounding code.
- Be respectful to other contributors and to the authors of the forks we build on.

### Where do I start?

Look at the [open issues](https://github.com/justr4mzi/hortensia/issues) and the "Known issues"
section of the README. For a new feature, open an issue first to discuss it.

### Opening a pull request

1. Fork [justr4mzi/hortensia](https://github.com/justr4mzi/hortensia) and create a branch from `main`.
2. Make your change and build it (see [the build documentation](docs/Build.md)).
3. Test the game or the behavior you changed, and note what you tested.
4. Open a pull request to `main`. Explain the problem, the change, where it comes from (fork and
   commit, if ported) and how you verified it. Link the related issue.

## Upstream

If your change also helps other forks, consider sending it to the project it comes from as well
(for example [Lichii](https://github.com/zortos293/Lichii),
[SmileyTatsu](https://github.com/SmileyTatsu/Eglantine) or
[Eglantine](https://github.com/Djihads80/Eglantine)), following their own contribution rules.
