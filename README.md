# 📚 Documentation — C Compiler

> Documentation complète du projet, organisée pour reprendre le travail
> après une pause prolongée.

---

## 🗺️ Plan de lecture conseillé

Si tu reprends le projet maintenant, lis dans cet ordre :

1. **`01_RECAP_ETAT_PROJET.md`** ← commence ici
   État réel du code, écart avec la doc passée, ce qui marche / ce qui
   ne marche pas.

2. **`02_ROADMAP.md`**
   Plan détaillé de ce qui reste à coder, étape par étape, avec
   dépendances claires.

3. **`03_PORTABILITE_MAC_LINUX.md`**
   Comment garantir que le compilateur marche sur Mac et Linux,
   spécialement le piège du codegen + Apple Silicon.

4. **`tests/00_STRATEGIE.md`**
   Pourquoi des tests unitaires, choix de framework (doctest),
   organisation des tests.

5. **`tests/04_INTEGRATION_CMAKE.md`**
   Comment brancher doctest dans le projet (setup technique).

6. **`tests/01_TESTS_LEXER.md`**
   Liste complète des tests Lexer à écrire (~50 tests).

7. **`tests/02_TESTS_PARSER.md`**
   Liste complète des tests Parser, organisée par phase
   d'implémentation (~80 tests).

---

## 📂 Arborescence

```
docs/
├── README.md                          ← ce fichier
├── 01_RECAP_ETAT_PROJET.md            ← état actuel (audit honnête)
├── 02_ROADMAP.md                      ← ce qu'il reste à faire
├── 03_PORTABILITE_MAC_LINUX.md        ← Mac, Linux, Apple Silicon
└── tests/
    ├── 00_STRATEGIE.md                ← stratégie de tests + doctest
    ├── 01_TESTS_LEXER.md              ← tests Lexer détaillés
    ├── 02_TESTS_PARSER.md             ← tests Parser détaillés
    └── 04_INTEGRATION_CMAKE.md        ← setup technique CMake + doctest
```

> `03_TESTS_AVANCES.md` à créer plus tard (semantic + codegen).

---

## ⚡ TL;DR

- **Lexer** : ✅ fonctionnel, aucun test unitaire.
- **Parser** : ⚠️ 15% squelette, classes manquantes, bugs de types
  (`enum keyword` n'existe pas), méthode `parse()` qui ne lance jamais
  `parseProgram()`.
- **Tests** : ❌ aucun test unitaire dans le projet.

**Prochaine action** :
1. Mettre en place doctest (voir `tests/04_INTEGRATION_CMAKE.md`).
2. Écrire les tests Lexer (voir `tests/01_TESTS_LEXER.md`).
3. Refactor Parser.hpp (voir `02_ROADMAP.md` étape A).
4. Implémenter Parser phase par phase avec tests TDD.

---

## 🔄 Mise à jour des docs

Quand tu avances dans le projet, **mets à jour** :

- `01_RECAP_ETAT_PROJET.md` : à chaque grosse étape franchie, modifie
  le tableau de statut en haut.
- `README.md` (à la racine du projet) : la barre de progression actuelle
  ment (annonce Parser 100% et Codegen 40%). À ajuster à la réalité.

> Une doc à jour est plus utile qu'une doc parfaite. Si tu fais une grosse
> modif, prends 5 minutes pour ajuster les docs concernées.
