/*
 * ============================================================
 *   D E B U G G E R : T H E   L A S T   P A T C H
 *   ui.c — HUD, bars, screens
 * ============================================================
 */

#include "debugger.h"

/* ============================================================
   show_health_bar()
   ♥ ♥ ♥  /  ♥ ♥ ✗
   ============================================================ */
void show_health_bar(Player *p) {
    int i;
    printf("\n  " C_BCYAN "INTEGRITY AGENT: %s" C_RESET "\n", p->name);
    printf("  HEARTS: ");
    for (i = 0; i < 3; i++) {
        if (i < p->hearts)
            printf(C_RED " <3 " C_RESET);
        else
            printf(C_DIM " XX " C_RESET);
    }
    printf("\n  " C_DIM "NODES PATCHED: %d / %d" C_RESET "\n\n",
           p->nodes_cleared, NUM_BOSSES);
}

/* ============================================================
   show_integrity_bar()
   Kernel integrity 0-100 %
   ============================================================ */
void show_integrity_bar(int percent) {
    int filled, i;
    int bar_w = 40;

    if (percent < 0)   percent = 0;
    if (percent > 100) percent = 100;
    filled = (percent * bar_w) / 100;

    printf("  " C_BYELLOW "KERNEL INTEGRITY" C_RESET "  [");
    for (i = 0; i < bar_w; i++) {
        if (i < filled)
            printf(C_BGREEN "#" C_RESET);
        else
            printf(C_DIM "." C_RESET);
    }
    printf("] " C_BYELLOW "%3d%%" C_RESET "\n", percent);
}

/* ============================================================
   show_patch_result()
   Victory screen after defeating a boss.
   ============================================================ */
void show_patch_result(Boss *b, int integrity_pct) {
    int i;
    cls();
    printf("\n");
    printf(C_BGREEN);
    for (i = 0; i < 56; i++) putchar('=');
    printf("\n");
    print_centered(">> NODE PATCHED <<", 56);
    for (i = 0; i < 56; i++) putchar('=');
    printf(C_RESET "\n\n");

    printf("  Corruption source : " C_BRED "%s" C_RESET "\n", b->name);
    printf("  Topic sealed      : " C_CYAN "%s" C_RESET "\n", b->topic);
    printf("  Location cleared  : " C_DIM  "%s" C_RESET "\n\n", b->location);

    show_integrity_bar(integrity_pct);

    printf("\n");
    for (i = 0; i < 56; i++) putchar('-');
    printf("\n");

    printf("  Stabilising kernel");
    fflush(stdout);
    for (i = 0; i < 6; i++) {
        SLEEP_MS(200);
        printf(C_BGREEN "." C_RESET);
        fflush(stdout);
    }
    printf("  " C_BGREEN "DONE" C_RESET "\n\n");

    speak(SP_GUIDE, "The corruption recedes. One more node sealed.\nThe kernel breathes a little easier.");
}

/* print_centered() is defined in dialogue.c */ 