# DEBUGGER: THE LAST PATCH
### A terminal RPG about C programming

```
  ########################################################
              D E B U G G E R
        T H E   L A S T   P A T C H
  ########################################################
```

---

## ABOUT

**Debugger: The Last Patch** is a text-based RPG that runs entirely in your terminal.
The kernel is dying. Seven corruption nodes have taken root in the codebase — each one a C programming concept that was never truly understood. You are the Debugger. Patch them all before the system collapses.

Answer questions correctly to defeat bosses. Get them wrong and lose a heart. Lose all three and the kernel takes you with it.

---

## BOSSES

| # | Name | Topic | Location |
|---|------|-------|----------|
| 1 | VARSHADE | Variables | The Rootways |
| 2 | BRANCHWRAITH | If/Else — Selection | The Ashfields |
| 3 | VOIDCALLER | Functions | The Cliffshore |
| 4 | FORMLESSONE | Structs | The Drowned Dark |
| 5 | INDEXSERPENT | Arrays | The Sunken Basin |
| 6 | NULLFANG | Pointers | The Veinplains |
| 7 | HYDRAEXCEPTION | Fatal Exception — All Errors | The Worldroot |

---

## HOW TO PLAY

- Each boss asks **3 questions** about their C programming topic
- Enter **1, 2, 3, or 4** to choose your answer
- A correct answer damages the corruption node
- A wrong answer costs you **1 heart** (you have 3)
- Lose all 3 hearts and it's **game over**
- Defeat all 7 bosses to restore the kernel

At the end of the game, the **Tome of Errors** shows every question you got wrong — study it so you never make the same mistake again.

---

## HOW TO BUILD & RUN

### Requirements
- GCC (MinGW recommended on Windows — download from https://winlibs.com)

### Compile

```
gcc main.c game.c dialogue.c bosses.c ui.c file.c -o debugger.exe
```

### Run (Windows)

```
.\debugger.exe
```

### Run (Linux / Mac)

```
./debugger
```

> **Tip:** Run in a maximized terminal window for the best experience. The boss ASCII art centers itself based on your terminal width.

---

## FILES

| File | Purpose |
|------|---------|
| `main.c` | Entry point and game loop |
| `game.c` | Screens, boss encounters, battle logic |
| `bosses.c` | All boss definitions, ASCII art, and questions |
| `dialogue.c` | Typewriter engine, speaker profiles, dialogue boxes |
| `ui.c` | HUD, health bar, integrity bar, patch result screen |
| `file.c` | Tome of Errors — write and read wrong answers |
| `debugger.h` | Master header — all structs, enums, constants, prototypes |

---

## SPEAKERS

The game has five distinct voices, each with their own dialogue box style:

- **NARRATION** — white, plain borders, sets the scene
- **GUIDE** — cyan, wavy borders, slightly glitched (61% integrity)
- **YOU** — bright green, your responses
- **THE KERNEL** — yellow, double borders, slow and deliberate
- **BOSS** — red, heavy glitch, fast and erratic

---

## DIALOGUE MARKERS

Dialogue strings support special tags for dramatic effect:

| Tag | Effect |
|-----|--------|
| `[PAUSE]` | 700ms halt |
| `[SLOW]` | Halves typing speed |
| `[FAST]` | Doubles typing speed |
| `[SHAKE]` | Next word flickers with random characters |

---

## NOTES

- The game saves your wrong answers to `tome_of_errors.txt` in the same folder as the executable
- Delete `tome_of_errors.txt` to reset your error log between runs
- The game supports **Windows** (ANSI colors enabled automatically) and **Linux/Mac**

---

*"Every error you made has been recorded here. Study them. The same bugs must never corrupt the kernel again."*
— The Kernel
