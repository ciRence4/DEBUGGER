# DEBUGGER: THE LAST PATCH
> *A terminal RPG about C programming.*

The kernel is failing. Seven corruption nodes have taken root deep in the
codebase — each one a C concept that was never truly understood. You are
the Debugger. Patch the nodes. Save the system.

---

## What Is This?

**Debugger: The Last Patch** is a text-based RPG that runs entirely in the
terminal. It was built as a finals project in C to make learning core
programming concepts more engaging. Instead of reading a textbook, you
fight bosses.

Each boss represents a C topic. Defeat them by answering questions
correctly. Get them wrong and you lose a heart. Every mistake is logged
to a file called the **Tome of Errors** — displayed at the end of the
game so you can review what you got wrong.

---

## The Seven Corruption Nodes

| Boss | Topic | Location |
|---|---|---|
| VARSHADE | Variables | The Rootways |
| BRANCHWRAITH | If / Else — Selection | The Ashfields |
| VOIDCALLER | Functions | The Cliffshore |
| FORMLESSONE | Structs | The Drowned Dark |
| INDEXSERPENT | Arrays | The Sunken Basin |
| NULLFANG | Pointers | The Veinplains |
| HYDRAEXCEPTION | Fatal Exception — All Errors | The Worldroot |

---

## Features

- Typewriter-style dialogue with speaker boxes for each character
- Glitch effects on corrupted speakers (the Guide, boss dialogue)
- `[PAUSE]`, `[SLOW]`, `[FAST]`, `[SHAKE]` text animation markers
- Per-boss ASCII art with unique ANSI colors
- Health bar and kernel integrity bar that fills as you progress
- Tome of Errors — wrong answers are written to a `.txt` file and read
  back dramatically at the end
- Works on Windows, Linux, and Mac

---

## How to Build and Run

### Requirements
- GCC (on Windows: install [MinGW](https://www.mingw-w64.org/))
- A terminal with ANSI color support
  - Windows: use **Windows Terminal** or **PowerShell**
  - Linux / Mac: any standard terminal

### Build

**Windows** — just double-click or run the included batch file:
```powershell
.\build.bat
```

**Manual (all platforms):**
```bash
gcc -o debugger main.c dialogue.c bosses.c ui.c file.c game.c
```

### Run

```powershell
.\debugger.exe        # Windows
./debugger            # Linux / Mac
```

---

## File Structure

```
DEBUGGER/
 ├── debugger.h      — master header: structs, constants, all prototypes
 ├── main.c          — entry point and game loop
 ├── game.c          — intro, exploration, boss encounter, battle, epilogue
 ├── dialogue.c      — typewriter engine, speaker boxes, glitch effects
 ├── bosses.c        — all 7 boss definitions, ASCII art, and questions
 ├── ui.c            — health bar, integrity bar, patch victory screen
 ├── file.c          — Tome of Errors: write on wrong answer, read at end
 └── build.bat       — Windows one-click build script
```

`tome_of_errors.txt` is not included — it gets created automatically
the first time you answer a question wrong.

---

## How to Play

1. Run the game
2. Enter your name when prompted
3. For each boss, read the question and enter **1, 2, 3, or 4**
4. Survive all 7 bosses to restore the kernel
5. At the end, the Tome of Errors shows every mistake you made

You have **3 hearts**. Wrong answers cost 1 heart. Lose all 3 mid-battle
and the game ends immediately.

---

## Built With

- **C** (C99)
- ANSI escape codes for terminal colors
- Standard library only — no external dependencies

---

*Finals project — CS / Programming subject*
*Built to make C concepts stick.*
