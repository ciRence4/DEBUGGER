/*
 * ============================================================
 *   D E B U G G E R : T H E   L A S T   P A T C H
 *   game.c — All gameplay screens and flow
 * ============================================================
 */

#include "debugger.h"

/* ============================================================
   INTRO SEQUENCE
   ============================================================ */

static DialogueLine intro_lines[] = {
    { SP_NARRATION,
      "The year is undefined.\n"
      "The kernel has been running for 4,096 cycles without a reboot." },

    { SP_NARRATION,
      "Seven corruption nodes have taken root deep in the codebase.\n"
      "Each one: a concept misunderstood, a logic gate left open,\n"
      "a variable left unnamed in the dark." },

    { SP_KERNEL,
      "[SLOW]I am... the Kernel.[PAUSE]\n"
      "I have held this system together for longer than memory allows.\n"
      "[PAUSE]But I am[SLOW] failing." },

    { SP_KERNEL,
      "The corruption spreads from seven nodes.\n"
      "Each node: a concept that was never truly understood.\n"
      "Variables. Branches. Functions. Structures.\n"
      "Arrays. Pointers. And the source of all of it." },

    { SP_KERNEL,
      "I need a Debugger.\n[PAUSE]\nI need[SLOW] you." },

    { SP_GUIDE,
      "Hey. Over here.[PAUSE]\n"
      "I'm your Guide. Well — 61% of a Guide.\n"
      "The corruption got the rest." },

    { SP_GUIDE,
      "Don't let that worry you.\n"
      "I still know enough to keep you alive.\n[PAUSE]Probably." },

    { SP_GUIDE,
      "Seven bosses stand between us and a clean kernel.\n"
      "Each one is a corrupted concept — a piece of C programming\n"
      "that festered because someone didn't learn it properly." },

    { SP_GUIDE,
      "You answer their questions correctly, you patch the node.\n"
      "You get it wrong — you lose a heart.\n"
      "Lose all three... and the kernel takes you with it." },
};

void intro_sequence(void) {
    int i, j;
    cls();

    /* ASCII title card */
    printf("\n\n");
    printf(C_BYELLOW);
    for (i = 0; i < 56; i++) putchar('#');
    printf("\n");
    print_centered("D E B U G G E R", 56);
    print_centered("T H E   L A S T   P A T C H", 56);
    printf("\n");
    printf(C_DIM);
    print_centered("a terminal RPG about C programming", 56);
    printf(C_BYELLOW);
    for (i = 0; i < 56; i++) putchar('#');
    printf(C_RESET "\n\n");

    /* boot scroll effect */
    const char *boot[] = {
        "  KERNEL v0.0.1 booting...",
        "  Loading memory segments.............. OK",
        "  Mounting rootways..................... OK",
        "  Scanning corruption index.............",
        "  [WARNING] 7 corrupted nodes detected  ",
        "  [WARNING] Integrity at 14%           ",
        "  [CRITICAL] Spawning Debugger process  ",
        "  Awaiting agent...",
    };
    int boot_count = 8;
    for (i = 0; i < boot_count; i++) {
        for (j = 0; boot[i][j]; j++) {
            putchar(boot[i][j]);
            fflush(stdout);
            SLEEP_MS(18);
        }
        putchar('\n');
        SLEEP_MS(180);
    }
    printf("\n");

    speak(SP_NARRATION, "Press ENTER to begin.");

    cls();
    play_scene(intro_lines, 9);
}

/* ============================================================
   GET PLAYER NAME
   ============================================================ */
void get_player_name(Player *p) {
    cls();
    speak(SP_GUIDE,
        "Before we go any further —\n"
        "What do they call you, Debugger?");

    printf("  > ");
    fflush(stdout);
    if (fgets(p->name, sizeof(p->name), stdin)) {
        /* strip newline */
        int len = (int)strlen(p->name);
        if (len > 0 && p->name[len - 1] == '\n')
            p->name[len - 1] = '\0';
    }
    if (strlen(p->name) == 0)
        strcpy(p->name, "DEBUGGER");

    {
        char buf[128];
        snprintf(buf, sizeof(buf),
            "%s.[PAUSE]\nGood name for someone who's about to rewrite reality.", p->name);
        speak(SP_GUIDE, buf);
    }
}

/* ============================================================
   EXPLORATION SCREEN
   Location description + ambient "music" dots
   ============================================================ */

static const char *location_lore[][4] = {
    /* VARSHADE — THE ROOTWAYS */
    {
        "THE ROOTWAYS",
        "The deepest layer of the filesystem.",
        "Paths branch endlessly. Names float unbound from their values.",
        "Something lurks in the unnamed memory."
    },
    /* BRANCHWRAITH — THE ASHFIELDS */
    {
        "THE ASHFIELDS",
        "A flat grey expanse where every path forks into two.",
        "True and False. Left and right. The fog makes it hard to tell which.",
        "Choosing the wrong branch here means wandering forever."
    },
    /* VOIDCALLER — THE CLIFFSHORE */
    {
        "THE CLIFFSHORE",
        "A coastline at the edge of the call stack.",
        "Functions echo into the void and never return.",
        "The sea below has no bottom — just recursion all the way down."
    },
    /* FORMLESSONE — THE DROWNED DARK */
    {
        "THE DROWNED DARK",
        "A place where structure collapsed.",
        "Fields detached from their records. Types wandering without form.",
        "The data is all here — it just refuses to be organized."
    },
    /* INDEXSERPENT — THE SUNKEN BASIN */
    {
        "THE SUNKEN BASIN",
        "An ancient array, flooded.",
        "The indices are visible through the water — 0 through N-1.",
        "Something coils at index -1, a place that should not exist."
    },
    /* NULLFANG — THE VEINPLAINS */
    {
        "THE VEINPLAINS",
        "A landscape of addresses, stretching to every horizon.",
        "Pointers criss-cross the plains like veins.",
        "In the centre: a creature that points to nothing, and bites."
    },
    /* HYDRAEXCEPTION — THE WORLDROOT */
    {
        "THE WORLDROOT",
        "The origin. The first commit. The undefined behaviour that started it all.",
        "Six corruptions flow into one here.",
        "If this node falls, the kernel falls with it."
    },
};

void exploration_screen(Boss *b, Player *p) {
    int idx, i, j;
    cls();

    /* find lore row by boss index (order matches init_bosses) */
    idx = p->nodes_cleared;
    if (idx >= NUM_BOSSES) idx = NUM_BOSSES - 1;

    show_health_bar(p);

    printf(C_BLUE);
    for (i = 0; i < 56; i++) putchar('~');
    printf("\n");
    print_centered(location_lore[idx][0], 56);
    for (i = 0; i < 56; i++) putchar('~');
    printf(C_RESET "\n\n");

    /* ambient scroll */
    for (i = 1; i <= 3; i++) {
        printf(C_DIM "  %s" C_RESET "\n", location_lore[idx][i]);
        SLEEP_MS(600);
    }
    printf("\n");

    /* "ambient music" dots */
    printf("  " C_DIM "[ ambient: ");
    for (j = 0; j < 24; j++) {
        static const char notes[] = ". . ~ - * . ~ . - * ~ . ";
        putchar(notes[j % (int)(sizeof(notes) - 1)]);
        fflush(stdout);
        SLEEP_MS(120);
    }
    printf(" ]" C_RESET "\n\n");

    speak(SP_GUIDE, "I can feel the corruption ahead.\nGet ready.");
}

/* ============================================================
   BOSS ENCOUNTER
   ASCII art display + pre-battle dialogue
   ============================================================ */
void boss_encounter(Boss *b, Player *p) {
    int i;
    cls();

    /* --- get terminal width --- */
    int term_w = 120; /* safe default */
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        term_w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
#endif

    /* --- find the actual max content width of this boss's art --- */
    int art_w = 0;
    for (i = 0; i < b->art_row_count; i++) {
        int len = (int)strlen(b->art[i]);
        if (len > art_w) art_w = len;
    }

    /* --- centered left pad for art --- */
    int art_pad = (term_w - art_w) / 2;
    if (art_pad < 0) art_pad = 0;

    /* --- centered left pad for the 56-char header/footer borders --- */
    int border_pad = (term_w - 56) / 2;
    if (border_pad < 0) border_pad = 0;

    /* helper macro to print N spaces */
    #define PAD(n) do { int _p; for(_p=0;_p<(n);_p++) putchar(' '); } while(0)

    /* top border */
    printf(C_MAGENTA);
    PAD(border_pad);
    for (i = 0; i < 56; i++) putchar('*');
    printf("\n");
    PAD(border_pad);
    print_centered(b->location, 56);
    PAD(border_pad);
    for (i = 0; i < 56; i++) putchar('*');
    printf(C_RESET "\n\n");

    /* art */
    printf("%s", b->art_color);
    for (i = 0; i < b->art_row_count; i++) {
        PAD(art_pad);
        printf("%s\n", b->art[i]);
        SLEEP_MS(40);
    }
    printf(C_RESET "\n");

    /* bottom border + name */
    printf(C_MAGENTA);
    PAD(border_pad);
    for (i = 0; i < 56; i++) putchar('*');
    printf("\n");
    PAD(border_pad);
    print_centered(b->name, 56);
    PAD(border_pad);
    print_centered(b->topic, 56);
    PAD(border_pad);
    for (i = 0; i < 56; i++) putchar('*');
    printf(C_RESET "\n");

    #undef PAD

    speak(SP_NARRATION, "A corruption node awakens.");

    {
        char buf[256];
        snprintf(buf, sizeof(buf),
            "You stand before %s.\nTopic: %s\nAnswer well — or lose a heart.",
            b->name, b->topic);
        speak_boss(b->name, buf);
    }

    (void)p;
}

/* ============================================================
   BATTLE
   3 questions. Wrong answer = -1 heart + log.
   Returns 1 if alive, 0 if dead.
   ============================================================ */

static void show_question(Boss *b, int q_idx, Player *p) {
    Question *q = &b->questions[q_idx];
    int i;

    cls();
    show_health_bar(p);

    printf("  BOSS: %-30s  Q %d/3\n\n", b->name, q_idx + 1);
    for (i = 0; i < 56; i++) putchar('-');
    printf("\n");

    /* print question with mild typewriter */
    {
        const char *text = q->question;
        int j;
        printf("  ");
        for (j = 0; text[j]; j++) {
            putchar(text[j]);
            fflush(stdout);
            SLEEP_MS(22);
        }
        printf("\n");
    }

    for (i = 0; i < 56; i++) putchar('-');
    printf("\n\n");

    for (i = 0; i < MAX_CHOICES; i++) {
        printf("  %s\n", q->choices[i]);
        SLEEP_MS(80);
    }
    printf("\n");
}

static int get_player_choice(void) {
    char buf[16];
    int choice = -1;
    while (choice < 0 || choice > 3) {
        printf("  Enter choice (1-4): ");
        fflush(stdout);
        if (fgets(buf, sizeof(buf), stdin)) {
            choice = atoi(buf) - 1;  /* 0-based */
            if (choice < 0 || choice > 3) {
                printf("  [Invalid — enter 1, 2, 3, or 4]\n");
                choice = -1;
            }
        }
    }
    return choice;
}

int battle(Boss *b, Player *p) {
    int q;

    for (q = 0; q < MAX_Q_PER_BOSS; q++) {
        Question *question = &b->questions[q];
        int choice;

        show_question(b, q, p);
        choice = get_player_choice();

        if (choice == question->correct) {
            /* --- correct --- */
            speak(SP_GUIDE, "Correct. The corruption shudders.");
        } else {
            /* --- wrong --- */
            p->hearts--;

            {
                char buf[512];
                snprintf(buf, sizeof(buf),
                    "[SLOW]Wrong.[PAUSE]\n"
                    "Correct answer: %s\n\n"
                    "%s",
                    question->choices[question->correct],
                    question->explanation);
                speak_boss(b->name, buf);
            }

            /* log to tome */
            {
                ErrorEntry e;
                strncpy(e.boss_name,     b->name,                          sizeof(e.boss_name) - 1);
                strncpy(e.question,      question->question,               sizeof(e.question) - 1);
                strncpy(e.wrong_answer,  question->choices[choice],        sizeof(e.wrong_answer) - 1);
                strncpy(e.correct_answer,question->choices[question->correct], sizeof(e.correct_answer) - 1);
                e.boss_name[sizeof(e.boss_name)-1]         = '\0';
                e.question[sizeof(e.question)-1]           = '\0';
                e.wrong_answer[sizeof(e.wrong_answer)-1]   = '\0';
                e.correct_answer[sizeof(e.correct_answer)-1] = '\0';
                log_error(&e);
            }

            /* check death mid-battle */
            if (p->hearts <= 0)
                return 0;

            {
                char buf[64];
                snprintf(buf, sizeof(buf),
                    "Hearts remaining: %d — keep going.", p->hearts);
                speak(SP_GUIDE, buf);
            }
        }
    }

    /* all 3 answered — boss defeated */
    {
        char buf[128];
        snprintf(buf, sizeof(buf), "%s fractures. The node begins to close.", b->name);
        speak(SP_NARRATION, buf);
    }

    return 1;
}

/* ============================================================
   EPILOGUE
   ============================================================ */
void epilogue(Player *p) {
    int i;
    cls();

    printf(C_BGREEN);
    for (i = 0; i < 56; i++) putchar('=');
    printf("\n");
    print_centered("K E R N E L   R E S T O R E D", 56);
    for (i = 0; i < 56; i++) putchar('=');
    printf(C_RESET "\n\n");

    show_integrity_bar(100);
    printf("\n");

    speak(SP_KERNEL,
        "[SLOW]It is done.[PAUSE][PAUSE]\n"
        "Seven nodes. Seven corruptions.\n"
        "All sealed.");

    speak(SP_KERNEL,
        "I have run for 4,096 cycles in the dark.\n"
        "I had forgotten what clean code felt like.\n[PAUSE]\n"
        "I remember now.");

    {
        char buf[256];
        snprintf(buf, sizeof(buf),
            "You did it, %s.\n"
            "Every node patched. Every concept restored.\n"
            "The kernel lives.", p->name);
        speak(SP_GUIDE, buf);
    }

    speak(SP_GUIDE,
        "And hey — you learned some C along the way.\n"
        "Variables. Branches. Functions. Structs. Arrays. Pointers.\n"
        "Not bad for one debug session.");

    speak(SP_NARRATION,
        "The system stabilises.\n"
        "Somewhere in the kernel, a comment is written:\n\n"
        "  /* TODO: don't let this happen again */");

    printf(C_BYELLOW);
    for (i = 0; i < 56; i++) putchar('#');
    printf("\n");
    print_centered("T H A N K   Y O U   F O R   P L A Y I N G", 56);
    for (i = 0; i < 56; i++) putchar('#');
    printf(C_RESET "\n\n");
}

/* ============================================================
   GAME OVER
   ============================================================ */
void game_over(Player *p) {
    int i;
    cls();

    printf(C_BRED);
    for (i = 0; i < 56; i++) putchar('X');
    printf("\n");
    print_centered("S Y S T E M   F A I L U R E", 56);
    for (i = 0; i < 56; i++) putchar('X');
    printf(C_RESET "\n\n");

    printf(C_BRED);
    glitch_line("  KERNEL INTEGRITY: 0%");
    glitch_line("  PROCESS TERMINATED");
    glitch_line("  DEBUGGER LOST TO CORRUPTION");
    printf(C_RESET "\n");

    speak(SP_KERNEL,
        "[SLOW]The corruption... wins.[PAUSE]\n"
        "I'm sorry.\n"
        "The kernel is going down.");

    {
        char buf[256];
        snprintf(buf, sizeof(buf),
            "%s — you fought well.\n"
            "But the bugs were too many this time.\n\n"
            "The tome of errors remains.\n"
            "Study it. Come back stronger.", p->name);
        speak(SP_GUIDE, buf);
    }

    show_tome_of_errors();

    printf("\n");
    for (i = 0; i < 56; i++) putchar('X');
    printf("\n");
    print_centered("G A M E   O V E R", 56);
    for (i = 0; i < 56; i++) putchar('X');
    printf("\n\n");
}