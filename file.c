/*
 * ============================================================
 *   D E B U G G E R : T H E   L A S T   P A T C H
 *   file.c — Tome of Errors: write & read
 * ============================================================
 */

#include "debugger.h"

/* ============================================================
   log_error()
   Appends one wrong-answer entry to the tome file.
   ============================================================ */
void log_error(ErrorEntry *e) {
    FILE *f = fopen(TOME_FILE, "a");
    if (!f) return;

    fprintf(f, "---\n");
    fprintf(f, "BOSS       : %s\n",  e->boss_name);
    fprintf(f, "QUESTION   : %s\n",  e->question);
    fprintf(f, "YOUR ANSWER: %s\n",  e->wrong_answer);
    fprintf(f, "CORRECT    : %s\n",  e->correct_answer);
    fprintf(f, "\n");

    fclose(f);
}

/* ============================================================
   show_tome_of_errors()
   Reads the tome file and prints every entry with typewriter
   effect. If file doesn't exist, prints a clean record msg.
   ============================================================ */
void show_tome_of_errors(void) {
    FILE *f;
    char  line[512];
    int   count = 0;
    int   i;

    cls();
    printf("\n");
    for (i = 0; i < 56; i++) putchar('=');
    printf("\n");
    print_centered("T O M E   O F   E R R O R S", 56);
    for (i = 0; i < 56; i++) putchar('=');
    printf("\n\n");

    speak(SP_KERNEL,
        "Every error you made has been recorded here.\n"
        "Study them. The same bugs must never corrupt the kernel again.");

    f = fopen(TOME_FILE, "r");
    if (!f) {
        speak(SP_GUIDE,
            "The tome is empty. A flawless run.\n"
            "The kernel has never seen such clean code.");
        return;
    }

    printf("\n");
    while (fgets(line, sizeof(line), f)) {
        /* strip trailing newline for display */
        int len = (int)strlen(line);
        if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0';

        if (strcmp(line, "---") == 0) {
            count++;
            printf("\n");
            for (i = 0; i < 50; i++) putchar('-');
            printf("\n  ERROR #%d\n", count);
        } else {
            /* small delay for dramatic reading */
            int j;
            for (j = 0; line[j]; j++) {
                putchar(line[j]);
                fflush(stdout);
                SLEEP_MS(8);
            }
            putchar('\n');
        }
    }
    fclose(f);

    printf("\n");
    for (i = 0; i < 56; i++) putchar('=');
    printf("\n");
    printf("  Total errors logged: %d\n", count);
    for (i = 0; i < 56; i++) putchar('=');
    printf("\n\n");

    if (count == 0) {
        speak(SP_GUIDE, "Not a single error. Legendary.");
    } else {
        speak(SP_KERNEL,
            "These were your failures. They are sealed now.\n"
            "But the memory remains — so you may never repeat them.");
    }
}