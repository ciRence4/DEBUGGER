/*
 * ============================================================
 *   D E B U G G E R : T H E   L A S T   P A T C H
 *   dialogue.c — Typewriter engine, speaker profiles, boxes
 * ============================================================
 */

#include "debugger.h"

/* ============================================================
   SPEAKER PROFILES TABLE
   ============================================================ */
static SpeakerProfile profiles[] = {
    /* SP_NARRATION */
    {
        "  NARRATION  ",
        28,
        '-', '|',
        "+-", "-+", "+-", "-+",
        0,
        C_WHITE
    },
    /* SP_GUIDE */
    {
        "  GUIDE  ",
        18,
        '~', '|',
        "/-", "-\\", "\\-", "-/",
        1,   /* slight glitch — it's 61% integrity */
        C_CYAN
    },
    /* SP_PLAYER */
    {
        "  YOU  ",
        22,
        '-', '|',
        "+-", "-+", "+-", "-+",
        0,
        C_BGREEN
    },
    /* SP_KERNEL */
    {
        "  THE KERNEL  ",
        38,   /* slow, ancient, deliberate */
        '=', '|',
        "+=", "=+", "+=", "=+",
        0,
        C_BYELLOW
    },
    /* SP_BOSS */
    {
        "  ??? ",
        12,   /* fast, erratic */
        '#', '|',
        "+#", "#+", "+#", "#+",
        1,   /* heavy glitch */
        C_BRED
    }
};

/* Glitch character substitution table */
static const char *glitch_subs[] = {
    "a","@",  "e","3",  "i","1",  "o","0",  "s","$",
    "t","7",  "g","9",  "b","6",  "l","|",  " "," "
};
static const int glitch_pairs = 9;

/* ============================================================
   cls()
   ============================================================ */
void cls(void) {
    system(CLEAR_CMD);
}

/* ============================================================
   print_hline()
   Prints  +------...------+  using given chars
   ============================================================ */
void print_hline(char h, char tl[], char tr[], int width) {
    int i;
    printf("%s", tl);
    for (i = 0; i < width; i++) putchar(h);
    printf("%s\n", tr);
}

/* ============================================================
   print_vline()
   Prints  |{spaces}|
   ============================================================ */
void print_vline(char v, int width) {
    int i;
    putchar(v);
    for (i = 0; i < width; i++) putchar(' ');
    putchar(v);
    putchar('\n');
}

/* ============================================================
   type_char()
   Prints one character with optional glitch substitution.
   ============================================================ */
void type_char(char c, int delay_ms, int glitch) {
    int i;
    if (glitch && (rand() % 12 == 0)) {
        /* try to substitute */
        for (i = 0; i < glitch_pairs; i++) {
            if (c == glitch_subs[i * 2][0]) {
                printf("%s", glitch_subs[i * 2 + 1]);
                fflush(stdout);
                SLEEP_MS(delay_ms);
                return;
            }
        }
    }
    putchar(c);
    fflush(stdout);
    SLEEP_MS(delay_ms);
}

/* ============================================================
   type_text()
   Parses marker tags and types text character by character
   inside the dialogue box content area.

   Markers:
     [PAUSE]  — 700 ms halt
     [SLOW]   — halve speed for rest of string
     [FAST]   — double speed for rest of string
     [SHAKE]  — next word printed with random junk prefix
   ============================================================ */
void type_text(SpeakerProfile *sp, const char *text) {
    int   delay   = sp->char_delay_ms;
    int   glitch  = sp->glitch;
    int   col     = 0;       /* current column inside box text area */
    int   i       = 0;
    int   len     = (int)strlen(text);
    int   shake_next = 0;
    char  v       = sp->v_border;

    /* Start first content line */
    putchar(v);
    putchar(' ');

    while (i < len) {
        /* --- check for marker tags --- */
        if (text[i] == '[') {
            if (strncmp(&text[i], "[PAUSE]", 7) == 0) {
                SLEEP_MS(700);
                i += 7;
                continue;
            }
            if (strncmp(&text[i], "[SLOW]", 6) == 0) {
                delay = sp->char_delay_ms * 2;
                i += 6;
                continue;
            }
            if (strncmp(&text[i], "[FAST]", 6) == 0) {
                delay = sp->char_delay_ms / 2;
                if (delay < 5) delay = 5;
                i += 6;
                continue;
            }
            if (strncmp(&text[i], "[SHAKE]", 7) == 0) {
                shake_next = 1;
                i += 7;
                continue;
            }
        }

        /* --- shake effect: print a random char then backspace --- */
        if (shake_next && text[i] != ' ') {
            static const char noise[] = "@#$%&?!~";
            putchar(noise[rand() % (int)(sizeof(noise) - 1)]);
            fflush(stdout);
            SLEEP_MS(60);
            putchar('\b');
            fflush(stdout);
            if (text[i] == ' ' || text[i] == '.' || text[i] == ',')
                shake_next = 0;
        }

        /* --- word-wrap at BOX_WIDTH --- */
        if (col >= BOX_WIDTH - 2) {
            /* pad to end of line */
            int pad;
            for (pad = col; pad < BOX_WIDTH; pad++) putchar(' ');
            putchar(v);
            putchar('\n');
            putchar(v);
            putchar(' ');
            col = 0;
            /* skip leading space on wrapped line */
            if (text[i] == ' ') { i++; continue; }
        }

        /* --- newline in source --- */
        if (text[i] == '\n') {
            int pad;
            for (pad = col; pad < BOX_WIDTH; pad++) putchar(' ');
            putchar(v);
            putchar('\n');
            putchar(v);
            putchar(' ');
            col = 0;
            i++;
            continue;
        }

        type_char(text[i], delay, glitch);
        col++;
        i++;
    }

    /* pad remainder of last line */
    {
        int pad;
        for (pad = col + 1; pad < BOX_WIDTH; pad++) putchar(' ');
        putchar(v);
        putchar('\n');
    }
}

/* ============================================================
   wait_for_enter()
   Prints blinking prompt and waits.
   ============================================================ */
void wait_for_enter(void) {
    int i;
    /* blink the continue prompt 2 times */
    for (i = 0; i < 2; i++) {
        printf("                                          [ > ]\r");
        fflush(stdout);
        SLEEP_MS(400);
        printf("                                               \r");
        fflush(stdout);
        SLEEP_MS(300);
    }
    printf("                                          [ > ]");
    fflush(stdout);
    /* flush input buffer then wait */
    while (getchar() != '\n');
}

/* ============================================================
   speak()
   Full dialogue box for a given SpeakerID.
   ============================================================ */
void speak(SpeakerID sid, const char *text) {
    SpeakerProfile *sp = &profiles[sid];
    int label_len = (int)strlen(sp->label);
    int total_w   = BOX_WIDTH + 2;

    printf("\n");
    printf("%s", sp->color);   /* begin speaker color */

    /* top border */
    print_hline(sp->h_border, sp->tl_corner, sp->tr_corner, BOX_WIDTH);

    /* speaker label line */
    putchar(sp->v_border);
    printf("%s", sp->label);
    {
        int pad, i;
        pad = BOX_WIDTH - label_len;
        for (i = 0; i < pad; i++) putchar(' ');
    }
    putchar(sp->v_border);
    putchar('\n');

    /* separator */
    print_hline(sp->h_border, sp->tl_corner, sp->tr_corner, BOX_WIDTH);

    /* blank line */
    print_vline(sp->v_border, BOX_WIDTH);

    /* the actual text */
    type_text(sp, text);

    /* blank line */
    print_vline(sp->v_border, BOX_WIDTH);

    /* bottom border */
    print_hline(sp->h_border, sp->bl_corner, sp->br_corner, BOX_WIDTH);

    printf(C_RESET);           /* end speaker color */

    wait_for_enter();
    printf("\n");

    (void)total_w;
}

/* ============================================================
   speak_boss()
   Same as speak() but overrides the label with boss name.
   ============================================================ */
void speak_boss(const char *boss_name, const char *text) {
    SpeakerProfile tmp = profiles[SP_BOSS];
    int label_len, i, pad;
    snprintf(tmp.label, sizeof(tmp.label), "  %s  ", boss_name);
    label_len = (int)strlen(tmp.label);

    printf("\n");
    printf("%s", tmp.color);   /* begin boss color */

    print_hline(tmp.h_border, tmp.tl_corner, tmp.tr_corner, BOX_WIDTH);

    putchar(tmp.v_border);
    printf("%s", tmp.label);
    pad = BOX_WIDTH - label_len;
    for (i = 0; i < pad; i++) putchar(' ');
    putchar(tmp.v_border);
    putchar('\n');

    print_hline(tmp.h_border, tmp.tl_corner, tmp.tr_corner, BOX_WIDTH);
    print_vline(tmp.v_border, BOX_WIDTH);
    type_text(&tmp, text);
    print_vline(tmp.v_border, BOX_WIDTH);
    print_hline(tmp.h_border, tmp.bl_corner, tmp.br_corner, BOX_WIDTH);

    printf(C_RESET);           /* end boss color */

    wait_for_enter();
    printf("\n");
}

/* ============================================================
   play_scene()
   Plays an array of DialogueLine in sequence.
   ============================================================ */
void play_scene(DialogueLine *lines, int count) {
    int i;
    for (i = 0; i < count; i++) {
        speak(lines[i].speaker, lines[i].text);
    }
}

/* ============================================================
   print_centered()
   ============================================================ */
void print_centered(const char *text, int width) {
    int len = (int)strlen(text);
    int pad = (width - len) / 2;
    int i;
    for (i = 0; i < pad; i++) putchar(' ');
    printf("%s\n", text);
}

/* ============================================================
   glitch_line()
   Prints a string with heavy corruption for dramatic effect.
   ============================================================ */
void glitch_line(const char *text) {
    int i, len = (int)strlen(text);
    static const char noise[] = "@#$%&?!~01";
    for (i = 0; i < len; i++) {
        if (rand() % 3 == 0)
            putchar(noise[rand() % (int)(sizeof(noise) - 1)]);
        else
            putchar(text[i]);
        fflush(stdout);
        SLEEP_MS(14);
    }
    putchar('\n');
}