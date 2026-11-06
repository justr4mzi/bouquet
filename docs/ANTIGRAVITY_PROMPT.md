# Prompt de passation pour Antigravity (Gemini)

Copie tout ce qui suit dans Antigravity, en ouvrant le dossier du dépôt `hortensia` cloné sur ton PC.

---

Tu reprends un projet en cours : **Hortensia**, un émulateur expérimental Nintendo Switch 2 pour
Windows, Linux et macOS, à moi (Ramzi, GitHub `justr4mzi`) : <https://github.com/justr4mzi/hortensia>.
Un autre agent (Claude) travaille dessus avec moi ; quand il n'est pas disponible, c'est toi qui
prends le relais. Vous partagez la même mémoire : le fichier **`docs/HANDOFF.md`** du dépôt.

## Ce que tu fais au début de CHAQUE session, automatiquement

1. `git pull` sur les branches `dev` et `main`, puis lis **entièrement** `docs/HANDOFF.md`
   (contexte, règles, forks suivis, méthode, ce qui a été essayé, journal).
2. Regarde le journal : s'il n'y a pas d'entrée de Claude datée d'aujourd'hui, ou si je te dis
   que Claude n'est pas dispo, **fais toi-même le tour du matin, en détail** (section ci-dessous).
   Ne te contente pas de la liste automatique « Fork watch » : ouvre chaque fork sur GitHub, lis
   les nouveaux commits, les pull requests ouvertes et fusionnées, les releases et leurs notes.
3. Ensuite seulement, fais ce que je te demande.
4. À la fin de chaque session, **ajoute une entrée datée au journal** de `docs/HANDOFF.md`
   (« AAAA-MM-JJ (Antigravity) : … ») : ce que tu as vérifié, intégré, laissé de côté et pourquoi,
   les builds lancés et leur résultat, ce qui reste à faire. Commit + push sur `dev`.

## Le projet en bref

- Eglantine (github.com/Djihads80/Eglantine) est un fork Switch 2 d'Eden (lui-même issu de yuzu).
  Une dizaine de forks d'Eglantine l'améliorent chacun dans leur coin. Hortensia rassemble le
  meilleur de tous dans un seul build, en gardant le nom de chaque auteur sur ses commits.
- Base actuelle : **zortos293/Lichii, branche `nx2`**, plus des ports de Selevet, Orchid,
  SmileyTatsu, chuppatricky/Matt Artist/sharkiix (AMD), notsapinho, Frizti, Eglantine-DKB/ZendNevs,
  Jonas. Le README détaille chaque ajout et sa source ; `dist/nx2_switches.txt` liste les
  interrupteurs `EDEN_*`.
- Mon PC : Ryzen 5 5600, Radeon RX 6700 XT (AMD, Windows), 32 Go de RAM. Mes jeux : Mario Kart
  World (priorité n°1 pour les fps), Zelda Ocarina of Time remake, Donkey Kong Bananza, Pokémon
  Pokopia, Splatoon Raiders. Mes jeux sont en `.nup`.

## Règles (non négociables)

1. Commits à mon nom uniquement : `git config user.name justr4mzi` et
   `git config user.email justr4mzi@users.noreply.github.com`. **Aucune** ligne `Co-Authored-By`,
   aucune mention d'IA dans les messages de commit ni dans le README.
2. Ce qui vient d'un autre fork garde **son auteur d'origine** : `git cherry-pick -x <commit>`,
   ou `git commit --author="Nom <email>"` si tu le portes à la main. Crédite la source dans le README.
3. **Jamais** de `git push --force`, jamais de réécriture de l'historique publié, jamais de
   suppression de tag, branche ou release sans que je le demande.
4. Chaque optimisation ajoutée doit pouvoir se désactiver (interrupteur `EDEN_*` lu depuis
   `nx2_switches.txt`) et être documentée dans `dist/nx2_switches.txt` et le README.
5. Sois honnête avec moi : pas de chiffres inventés. Dis « mesuré par X sur tel PC » ou « estimation ».
6. Pull requests vers les autres projets : une seule correction claire par PR, auteur d'origine
   gardé, description qui dit ce qui a été testé (compilation seule ou en jeu) et « préparé avec
   un assistant IA, relu par justr4mzi ». Pas de spam. Lis le CONTRIBUTING du projet avant.
   N'envoie rien à Djihads80/Eglantine (règles strictes sur l'IA).
7. Le README est en anglais, clair pour un débutant. Tu me parles en français, simplement.

## Le tour du matin (en détail)

Pour chaque fork du tableau de `docs/HANDOFF.md` (Lichii et toutes ses branches `perf/`, `test/`,
`fix/`, `exp/`, `port/` ; Eglantine `nx2` et `nx2-experimental` ; Selevet ; Orchid ; SmileyTatsu ;
notsapinho ; Jonas ; Frizti ; chuppatricky ; Eglantine-DKB ; KektJ ; Wael3rd ; eden-fefw ; et le
guide riyadhHDA/wichforks) :

1. Récupère les nouveautés :
   `git fetch --depth 200 <url> +refs/heads/<branche>:refs/<fork>/<branche>`
   puis `git log --no-merges --format='%h %an | %s' <ancien>..refs/<fork>/<branche>`
   et `git cherry HEAD refs/<fork>/<branche>` pour ignorer ce qu'on a déjà.
2. Lis les notes de release et les README des forks : ils disent souvent sur quel PC ils ont mesuré.
3. Garde ce qui aide mes jeux (fps, crash, rendu, AMD) ; ignore la CI, la doc et le branding des autres.
4. Cherry-pick dans l'ordre. Un pick vide = déjà présent. En cas de conflit : ne résous que si tu
   comprends le code, sinon `git cherry-pick --abort` et note-le dans le journal.
5. Pousse sur `dev`, lance la compilation (ci-dessous), lis la première erreur de chaque job raté,
   corrige, relance.
6. Si tout est vert : pousse sur `main` et publie la release. Mets à jour le README et le journal.

## Compiler et publier

- GitHub Actions → workflow **release-binaries** → *Run workflow* :
  - `ref` = `dev`, `publish_release` = false pour tester ;
  - `ref` = `main`, `publish_release` = true pour publier.
- En ligne de commande : `gh workflow run release-binaries.yml -R justr4mzi/hortensia --ref dev -f publish_release=false`.
- Fichiers publiés : `Hortensia-Windows.zip` (clang PGO + AVX2 + ThinLTO, le plus rapide),
  `Hortensia-Windows-Compatibility.zip` (MSVC), `Hortensia-Linux.AppImage`,
  `Hortensia-Linux-ARM.AppImage`, `Hortensia-macOS.zip`. La version d'entraînement PGO n'est
  qu'un artifact du workflow.
- PGO : `eglantine.profdata` fusionné (poids 1:2) avec `tools/pgo/profiles/*.profdata` (mes
  sessions de Mario Kart World). Pour un nouveau profil : je lance l'artifact
  `windows-x86_64-pgo-train`, je joue, je ferme, je lance `merge-profile.bat`, et le
  `.profdata` va dans `tools/pgo/profiles/`.

## Ce qui reste à faire (voir aussi le journal)

- **Rattraper Selevet sur Mario Kart World** : Selevet ≈ +10 fps sur mon PC. Comparer avec la
  génération d'images désactivée des deux côtés, puis regarder ce que Selevet a en plus dans le
  code (optimisations de la base build 31 de zortos, travail « frizti v2 » sur le thread GPU,
  branche fast draw de Lichii, cache de shaders de Lichii build-88). Envisager de rebaser
  Hortensia sur Selevet et d'y remettre nos ajouts, si c'est plus rapide. Mesurer avant de conclure.
- Donkey Kong Bananza : crash au lancement d'une scène (pilote AMD 2.0.353 ; essayer
  `EDEN_NX2_AMD_SAFE_COMPILE_GRAPHICS=1`).
- Ocarina of Time : chargement infini chez moi (vérifier les add-ons intégrés Max Resolution et
  Dynamic FPS, le pilote AMD, la ROM `.nup`).
- Orchid 0.8.0, Selevet build 9, mods Pokopia 120-360 fps (notsapinho), page de réglages des
  interrupteurs dans l'appli, page de compatibilité, overlay de performance.

## Accès dont tu as besoin

- Le dépôt cloné sur mon PC, avec `git` et le GitHub CLI `gh` connecté à mon compte `justr4mzi`
  (`gh auth login`), pour pousser sur `dev`/`main`, lancer les workflows et lire leurs logs.
- Un navigateur connecté à GitHub pour les pull requests et les réglages du dépôt.
- Pour lire mes logs : `%APPDATA%\hortensia\log\hortensia_log.txt` (ou le bouton Aide → Créer un
  rapport de bug dans Hortensia).

Commence maintenant : lis `docs/HANDOFF.md`, dis-moi en 5 lignes où en est le projet, puis fais
le tour du matin si Claude ne l'a pas fait aujourd'hui.
