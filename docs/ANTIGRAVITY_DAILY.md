# Prompt Antigravity — tu prends la main sur Hortensia (à partir du 7 nov 2026)

Claude n'a plus de quota cette semaine. **C'est toi qui pilotes Hortensia maintenant, tous les
jours.** Lis d'abord `docs/HANDOFF.md` en entier (règles, forks, méthode, journal), puis ce fichier.
Écris ce que tu fais dans le journal de `docs/HANDOFF.md` à la fin de chaque session (date, ce
que tu as vérifié, intégré, testé, ce qui a échoué, la suite).

Objectif de Ramzi : **Hortensia doit être l'émulateur Switch 2 le plus rapide sur son PC**, en
premier sur Mario Kart World (MKW), sans rien casser sur les autres jeux. Débrouille-toi : lis
les commits, les PR (ouvertes et fermées), les releases et les discussions de tous les forks,
et intègre ce qui apporte vraiment quelque chose.

## 1. Ce qu'on a mesuré le 6 nov au soir (PC de Ramzi)

PC : Ryzen 5 5600, RX 6700 XT 12 Go (pilote AMD Windows, ancien 2.0.353, mise à jour en cours),
32 Go, Windows 11. Jeu : MKW `0400C3F00006E000`, **même course**, mode **portable**, shaders
déjà en cache, **frame generation désactivée**. Les fps sont **à l'œil** (overlay), pas mesurés
par un outil : c'est une estimation, ne les présente pas comme des mesures.

Réglages identiques pour tous (vérifiés dans les lignes `LogSettings` de chaque log) :
résolution 1x, filtre Bilinear, GPU accuracy Low, CPU Unsafe, DMA Unsafe, fences Default,
VRAM Aggressive, ASTC recompression BC3, présentation asynchrone, shaders asynchrones,
sync memory off, reactive flushing off, frame gen off.

| Émulateur | Build | Moyenne | Max | Min | Notes |
| --- | --- | --- | --- | --- | --- |
| SmileyTatsu | build-18 PGO (`smileytatsu/dev-rebased` 2ff2871729) | ~40 | 47 | 26-27 | creux = shaders, « très fluide » |
| Selevet | build 10 (fenêtre « Lichii test/build18 ») | ~33 | — | — | `EDEN_NX2_AMD_PARALLEL_PIPELINES=1` |
| Hortensia | release 6 nov (main 3edd84fd, PGO MKW + AVX2 + ThinLTO) | *à remplir par Ramzi* | | | |

Conclusions à ce stade :
- **SmileyTatsu build-18 est devant Selevet build 10 d'environ 7 fps** sur ce PC (AMD). Le guide
  wichforks (github.com/riyadhHDA/wichforks) recommande aussi SmileyTatsu pour MKW sur AMD.
- Les optimisations « build 31 » du thread GPU séparé de Selevet (Fast Draw, sémaphores par
  slot, FLUSH_DRAWS 128, DMA_RANGES/LIST_TRUST, spins courts, voir HANDOFF) **ne suffisent pas à
  le mettre devant sur AMD**. Ne les porte pas en bloc en pensant que ça va tout régler. Si tu les
  portes, garde-les derrière des switches, et ne les active par défaut qu'après les avoir mesurés.
- Le plus gros écart vu jusqu'ici venait des **réglages** : Bouquet tournait avec frame gen
  LSFG 2x, fences Immediate, ASTC non compressé, présentation synchrone. Le preset MKW
  d'Hortensia (`src/common/game_presets.h`) applique maintenant les réglages de la ligne ci-dessus.

## 2. Pièges découverts (à connaître avant tout test)

1. **Tous ces forks partagent `%APPDATA%\eden\config\qt-config.ini`.** En se fermant, un émulateur
   réécrit la config et peut remettre des réglages par défaut. C'est arrivé : SmileyTatsu a remis
   frame gen ON, résolution 0.5x et ASTC non compressé pour Selevet. Il faut **verrouiller** chaque
   réglage avec `cle\default=false` + `cle=valeur`. Et **avant de croire un chiffre, vérifie les
   lignes `LogSettings` du log** de la session.
2. **Selevet compile les pipelines un par un sur le pilote AMD Windows** pour les jeux Switch 2
   (`vulkan_device.cpp`, « serializing pipeline compilation »). Le chargement des shaders devient
   très lent vers 400 (environ 5 s par shader). `EDEN_NX2_AMD_PARALLEL_PIPELINES=1` dans
   `%APPDATA%\eden\nx2_switches.txt` remet le parallèle (ça a marché sans crash chez Ramzi). Vérifie
   si Hortensia hérite de ce comportement. Si oui, mets le même switch et documente-le.
3. Hortensia utilise `%APPDATA%\hortensia` et le log `hortensia_log.txt`. Il propose d'importer
   depuis Eden/Eglantine/Selevet, Lichii, Bouquet, Citron, Sudachi, Suyu et Yuzu.
4. Le proxy de Claude ne pouvait pas télécharger les artifacts GitHub Actions. Ramzi les prend
   lui-même sur la page du run.

## 3. Ta tâche n°1 : savoir pourquoi SmileyTatsu est plus rapide, et le battre

1. `git fetch https://github.com/SmileyTatsu/Eglantine.git smileytatsu/dev-rebased` (et ses
   tags/releases, en particulier build-18). Trouve la base commune avec Hortensia, liste **tous**
   les commits SmileyTatsu absents d'Hortensia (`git cherry`, `git log base..ref`). Classe-les :
   perf CPU, perf GPU/Vulkan, shaders/pipelines, ASTC, mémoire, build (flags, PGO, LTO), UI.
   Regarde aussi **comment il compile** son build PGO : flags, profil, version de clang, options
   CMake, `-march`. Une partie de l'écart peut venir de là, pas du code.
2. Porte tout ce qui touche à la perf. Garde l'auteur d'origine (`git cherry-pick -x`) et mets
   chaque optimisation derrière un switch `EDEN_*`. Ce qui conflit trop : note-le dans HANDOFF.
3. Si l'écart reste grand et que le portage est trop conflictuel, prépare une branche
   **`rebase/smileytatsu`** : base SmileyTatsu `dev-rebased`, plus les ajouts d'Hortensia (nom,
   thème, imports, presets, updater, bug report, PGO MKW, ports AMD de chuppatricky/Orchid, OOT de
   Lichii). Ne touche **pas** à `main` sans que Ramzi ait mesuré que c'est mieux.
4. Ensuite seulement : Selevet build 9/10 (liste dans HANDOFF), Frizti, Lichii `perf/*`, KektJ,
   Wael3rd (MKW), Orchid 0.8.

## 4. Ta tâche n°2 : un compteur de fps dans le log (pour des mesures objectives)

Ajoute à Hortensia un logger de fps, activé par défaut, désactivable avec `EDEN_FPS_LOG=0` :
- toutes les 5 s, une ligne dans `hortensia_log.txt` : `FPS avg=… min=… max=… 1%low=…
  frametime_avg=…ms`, calculée sur les présentations réelles (pas les images de la frame gen,
  ou alors les deux séparément) ;
- à la fermeture du jeu, un résumé de la session : moyenne, 1 % low, min, durée et nombre de
  pipelines compilés pendant la session.

Comme ça, plus de chiffres à l'œil : Ramzi joue et tu lis le log. Documente-le dans le README et
dans `dist/nx2_switches.txt`.

## 5. Routine de chaque jour (c'est toi, plus Claude)

1. Lis l'issue « Fork watch » (workflow `fork-watch.yml`, 6h41 UTC). Puis **vérifie toi-même en
   détail** chaque fork du tableau de HANDOFF : commits, PR ouvertes et mergées, releases, plus
   wichforks pour voir qui est recommandé pour quoi. Cherche aussi les **nouveaux forks** (onglet
   Forks d'Eglantine et de Lichii, guide wichforks).
2. Intègre ce qui est utile en suivant la « Method that works » de HANDOFF. Build sur `dev`
   (Actions → release-binaries, `publish_release=false`), lis la première erreur de chaque job
   en échec, corrige.
3. Quand c'est vert et que ça n'a rien cassé : merge sur `main`, puis release (`publish_release=true`).
4. Mets à jour le README (contenu, switches, crédits) et le journal de HANDOFF.
5. Dis à Ramzi, en français simple et court : ce qui a changé, quoi tester, et sur quel jeu.

## 6. Protocole de test avec Ramzi

- Une seule variable à la fois. Même course de MKW, mode portable puis TV, shaders déjà en
  cache (lancer une course une fois avant), frame gen off.
- Avant de lancer : config verrouillée (`\default=false`). Après : vérifie `LogSettings` et le
  résumé fps du log.
- Note : build, commit, switches actifs, moyenne, 1 % low, min, et ce que Ramzi a ressenti.
- Mets chaque résultat dans un tableau « Mesures » dans HANDOFF.

## 7. Règles (rappel, détails dans HANDOFF)

- Commits sous `justr4mzi <justr4mzi@users.noreply.github.com>`, **aucune** mention d'IA ni
  `Co-Authored-By` dans les commits ou le README.
- Ports : auteur d'origine conservé, source créditée dans le README.
- Jamais de force-push, ni de suppression de tags, de branches ou de releases sans que Ramzi le
  demande.
- Toute optimisation doit pouvoir se désactiver (switch `EDEN_*`) et être documentée.
- PR vers d'autres projets : une seule chose par PR, honnête sur ce qui a été testé, rien vers
  Djihads80/Eglantine (politique IA).
- Pas de chiffres inventés : « mesuré par X sur Y » ou « estimation ».

## 8. En attente

- Issue #1 (riyadhHDA, « There's just no release ») : réponds avec le lien de la release
  quand elle est publiée (run 42294127813), puis ferme-la.
- Run de test `dev` 42299447282 : vérifie le résultat, corrige s'il est rouge.
- Ramzi doit supprimer le tag vide `build-1` sur le site (toi, n'y touche pas).
- DK Bananza plante au début d'une scène (log coupé pendant la compilation des pipelines) :
  après la mise à jour du pilote AMD, essayer `EDEN_NX2_AMD_SAFE_COMPILE_GRAPHICS=1`.
- OOT charge à l'infini : activer les deux add-ons intégrés (Max Resolution, Dynamic FPS), puis
  regarder le cache des shaders (Ramzi a mis ça de côté pour l'instant).
- La tâche planifiée Claude de 7h47 n'a plus de quota cette semaine. Ramzi peut la désactiver
  dans l'app, et c'est toi qui fais la ronde du matin.

## 9. Thème : Ramzi trouve le violet actuel désagréable (« ça fait mal aux yeux »)

Fichier : `dist/qt_themes/hortensia/style.qss` (+ la palette dans le code si elle y est). Ce qui
gêne sur la capture du 6 nov : fond violet saturé `#1d1430`, ligne du dossier en violet vif,
lignes alternées gris/violet qui jurent, et accent `#6f5fd0` trop saturé sur du sombre.
Suis les règles des guides de thème sombre (Material Design dark theme, guides UX) :
- **Fond gris très sombre presque neutre**, pas noir pur ni violet saturé : `#121212` à
  `#16141b`, avec juste une pointe de violet.
- **Profondeur par élévation** : chaque surface au-dessus est un peu plus claire (`#1c1a22`,
  `#24212c`, `#2c2836`), pas des couleurs différentes.
- **Couleurs d'accent désaturées** (teintes « 200 » de Material) : lavande douce vers `#b4a7f5`
  au lieu de `#6f5fd0`. Garde le rose seulement pour le bouton principal (Yes/OK/Lancer),
  un peu adouci (vers `#e05a82`).
- **Texte blanc cassé, pas blanc pur** : principal vers `#e8e4ef` (87 %), secondaire vers
  `#a8a2b4` (60 %), désactivé à 38 %. Contraste WCAG ≥ 4.5:1 pour le texte.
- Ligne du dossier : surface +1 niveau avec une fine bordure, plus de bandeau violet. Lignes
  alternées quasi invisibles (écart de 2-3 % de luminosité) ou supprimées. Sélection discrète
  (`#2f2a40`) avec l'accent en liseré à gauche.
- Barre de statut : une seule couleur d'accent pour les états actifs, gris pour le reste
  (aujourd'hui rouge/orange/blanc mélangés).
- Propose 2-3 variantes (captures avant/après) à Ramzi avant de choisir, et garde l'ancien
  thème dans le menu des thèmes. Option bonus : un thème clair doux.

## 10. URGENT : le preset MKW de la release est le mauvais (bloque à ~30 fps)

La release du 6 nov (`main` 3edd84fd, « build-10 ») contient encore l'**ancien** preset MKW
(« Lichii's recommended settings, dynamic FPS, uncompressed ASTC ») : `mkw_dynamic_fps=true`,
fences Immediate, ASTC non compressé, présentation synchrone, CPU Accurate, VSync FifoRelaxed.
Résultat chez Ramzi : MKW bloqué entre 22 et 30 fps, alors que SmileyTatsu et Selevet font
33-40 avec les réglages de la section 1. Le patch « dynamic FPS » semble caler le jeu sur 30
dès qu'il ne tient pas 60.
Le preset corrigé (aligné sur Selevet) est sur `dev` mais **pas sur `main`**. À faire :
1. Dans `src/common/game_presets.h`, MKW = **exactement** les réglages de la section 1, pour AMD,
   NVIDIA et Intel : CPU Unsafe, DMA Unsafe, GPU accuracy Low, fences Default, VRAM Aggressive,
   ASTC BC3, présentation asynchrone, shaders asynchrones, reactive flushing off, sync memory off,
   1x, Bilinear, VSync Fifo, frame gen off et **`mkw_dynamic_fps` off**. Vérifie aussi
   `SetMarioKartWorldRecommendedSettings` (VRAM Conservative et FifoRelaxed : à aligner) et le
   texte du log « Hortensia optimized settings ».
2. Mets ces réglages aussi comme valeurs par défaut d'une nouvelle installation, là où c'est
   possible sans casser les autres jeux.
3. Merge sur `main` et republie la release. Préviens Ramzi pour qu'il remesure avec le preset
   activé.

## 11. Notes de version obligatoires à chaque release

Chaque release (et son tag) doit avoir des notes qui disent **ce qu'elle ajoute par rapport à la
précédente** : nouveautés, ports (avec le fork et l'auteur d'origine), corrections de bugs,
changements de réglages ou de presets, nouveaux switches, problèmes connus, et ce qu'il faut
tester. Fais-les à partir de `git log <tag précédent>..HEAD`, en phrases simples, en anglais
(avec un court résumé en français si tu veux). Mets-les dans la release GitHub
(`gh release edit <tag> --notes-file …`) et dans le message du tag annoté. Si le workflow
génère un texte automatique, complète-le au lieu de le laisser vide.

## 12. Mode TV (Docked) par défaut + blocage 30 fps de MKW

- Ramzi veut le **mode TV (Docked) par défaut** pour les jeux, preset MKW compris : quasiment le
  même fps qu'en portable chez lui, et beaucoup plus beau. Change `use_docked_mode` dans les
  presets (`game_presets.h`, `SetMarioKartWorldRecommendedSettings` met Handheld) et la valeur
  par défaut. Garde portable seulement là où un fork l'a mesuré plus rapide, et note-le.
- Même avec les bons réglages, Hortensia restait vers 30 fps sur MKW. Piste trouvée :
  `PaceToVblank` dans `src/core/hle/service/nx2_gsv.h` respecte l'intervalle 2 (0x2003c,
  donc 30 fps) que MKW demande, une fois stable 120 presents (logique Orchid/Selevet).
  SmileyTatsu (~40 fps) ne bride probablement pas comme ça : vérifie dans son code. Ramzi
  teste `EDEN_NX2_SWAP_INTERVAL=1` (dans `%APPDATA%\hortensia\nx2_switches.txt`) : si ça
  débloque sans que le jeu tourne trop vite, mets intervalle 1 par défaut pour MKW quand le
  patch dynamic FPS est off, derrière un switch.

## 13. Résultat final Hortensia (6 nov 23:38) et décision

Hortensia release (main 3edd84fd), mêmes réglages verrouillés que SmileyTatsu et Selevet,
preset auto off, dynamic FPS off, `EDEN_NX2_SWAP_INTERVAL=1` : **~25 fps de moyenne en course
(22-30)**, 60 dans les menus. Ce n'est donc pas un bridage : Hortensia est **plus lent**.
Classement MKW sur le PC de Ramzi (à l'œil) : **SmileyTatsu build-18 ~40 > Selevet build 10 ~33
> Hortensia ~25**.
Décision : la **tâche n°1 devient la reconstruction sur SmileyTatsu** (branche
`rebase/smileytatsu`, section 3 point 3). Repars de SmileyTatsu `dev-rebased` (build-18), ajoute
par-dessus les ajouts d'Hortensia un par un (nom, thème, imports, presets, updater, PGO MKW, OOT
de Lichii), puis **fais remesurer MKW à Ramzi après chaque gros ajout**, pour trouver lequel coûte
des fps. Suspects côté Hortensia : le pacing GSV d'Orchid (`nx2_gsv.h`), les commits AMD de
chuppatricky/sharkiix, la base Lichii et ses ports Selevet, le profil PGO. Ne republie sur `main`
que quand c'est au moins aussi rapide que SmileyTatsu.
