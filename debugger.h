/*
 * ============================================================
 * D E B U G G E R : T H E   L A S T   P A T C H
 * debugger.h — Master header
 * ============================================================
 */

#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ============================================================
   PLATFORM
   ============================================================ */
#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(ms)  Sleep(ms)
    #define CLEAR_CMD     "cls"
    /* Enable ANSI escape codes on Windows 10+ */
    static inline void enable_ansi(void) {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode(h, &mode);
        SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
#else
    #include <unistd.h>
    #define SLEEP_MS(ms)  usleep((ms) * 1000)
    #define CLEAR_CMD     "clear"
    static inline void enable_ansi(void) {}
#endif

/* ============================================================
   ANSI COLORS
   ============================================================ */
#define C_RESET     "\033[0m"
#define C_BOLD      "\033[1m"
#define C_DIM       "\033[2m"
#define C_RED       "\033[31m"
#define C_GREEN     "\033[32m"
#define C_YELLOW    "\033[33m"
#define C_BLUE      "\033[34m"
#define C_MAGENTA   "\033[35m"
#define C_CYAN      "\033[36m"
#define C_WHITE     "\033[37m"
#define C_BRED      "\033[91m"
#define C_BGREEN    "\033[92m"
#define C_BYELLOW   "\033[93m"
#define C_BMAGENTA  "\033[95m"
#define C_BCYAN     "\033[96m"

/* ============================================================
   CONSTANTS
   ============================================================ */
#define BOX_WIDTH       150
#define MAX_CHOICES      4
#define MAX_Q_PER_BOSS   3
#define NUM_BOSSES       7
#define TOME_FILE       "tome_of_errors.txt"
#define ART_COLS        130
#define ART_ROWS        40   /* Increased to 40 to hold all boss art safely */

/* ============================================================
   ENUMS
   ============================================================ */
typedef enum {
    SP_NARRATION = 0,
    SP_GUIDE,
    SP_PLAYER,
    SP_KERNEL,
    SP_BOSS
} SpeakerID;

/* ============================================================
   STRUCTS
   ============================================================ */
typedef struct {
    char        label[32];
    int         char_delay_ms;
    char        h_border;
    char        v_border;
    char        tl_corner[4];
    char        tr_corner[4];
    char        bl_corner[4];
    char        br_corner[4];
    int         glitch;
    const char *color;   /* ANSI color code for this speaker's box */
} SpeakerProfile;

typedef struct {
    SpeakerID  speaker;
    const char *text;
} DialogueLine;

typedef struct {
    char  question[256];
    char  choices[MAX_CHOICES][128];
    int   correct;        /* 0-based index */
    char  explanation[256];
} Question;

typedef struct {
    char      name[64];
    char      topic[64];
    char      location[64];
    char      art[ART_ROWS][ART_COLS];
    int       art_row_count;
    const char *art_color;           /* ANSI color for ASCII art display */
    Question  questions[MAX_Q_PER_BOSS];
    int       defeated;
} Boss;

typedef struct {
    char  name[64];
    int   hearts;
    int   nodes_cleared;
} Player;

typedef struct {
    char  boss_name[64];
    char  question[256];
    char  wrong_answer[128];
    char  correct_answer[128];
} ErrorEntry;

/* ============================================================
   FUNCTION PROTOTYPES
   ============================================================ */

/* dialogue.c / bosses.c */
void cls(void);
void print_hline(char h, char tl[], char tr[], int width);
void print_vline(char v, int width);
void type_char(char c, int delay_ms, int glitch);
void type_text(SpeakerProfile *sp, const char *text);
void wait_for_enter(void);
void speak(SpeakerID sid, const char *text);
void speak_boss(const char *boss_name, const char *text);
void play_scene(DialogueLine *lines, int count);
void print_centered(const char *text, int width);
void glitch_line(const char *text);

/* bosses.c */
void init_bosses(Boss bosses[NUM_BOSSES]);

/* ui.c */
void show_health_bar(Player *p);
void show_integrity_bar(int percent);
void show_patch_result(Boss *b, int integrity_pct);

/* game.c */
void intro_sequence(void);
void get_player_name(Player *p);
void exploration_screen(Boss *b, Player *p);
void boss_encounter(Boss *b, Player *p);
int  battle(Boss *b, Player *p);
void epilogue(Player *p);
void game_over(Player *p);

/* file.c */
void log_error(ErrorEntry *e);
void show_tome_of_errors(void);

#endif /* DEBUGGER_H */