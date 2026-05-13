/*
 * ============================================================
 *   D E B U G G E R : T H E   L A S T   P A T C H
 *   main.c — Entry point, game loop
 * ============================================================
 */

#include "debugger.h"

/* ============================================================
   game_loop()
   Iterates over all bosses. Returns 1 if player survives all,
   0 if they died mid-run (game_over already called inside).
   ============================================================ */
static int game_loop(Boss bosses[NUM_BOSSES], Player *p) {
    int i;
    for (i = 0; i < NUM_BOSSES; i++) {
        /* --- exploration --- */
        exploration_screen(&bosses[i], p);

        /* --- encounter cutscene --- */
        boss_encounter(&bosses[i], p);

        /* --- battle --- */
        int survived = battle(&bosses[i], p);
        if (!survived) {
            game_over(p);
            return 0;
        }

        /* --- patch victory --- */
        /* integrity starts at 0, each boss repaired adds ~14% */
        int integrity = ((i + 1) * 100) / NUM_BOSSES;
        show_patch_result(&bosses[i], integrity);

        bosses[i].defeated = 1;
        p->nodes_cleared++;
    }
    return 1;
}

/* ============================================================
   main()
   ============================================================ */
int main(void) {
    Boss   bosses[NUM_BOSSES];
    Player player;

    enable_ansi();   /* enable ANSI colors on Windows */
    srand((unsigned int)time(NULL));

    memset(bosses, 0, sizeof(bosses));

    init_bosses(bosses);

    /* zero player */
    memset(&player, 0, sizeof(Player));
    player.hearts       = 3;
    player.nodes_cleared = 0;

    /* --- title / intro --- */
    intro_sequence();

    /* --- get name --- */
    get_player_name(&player);

    /* --- main game --- */
    if (game_loop(bosses, &player)) {
        
        epilogue(&player);
        show_tome_of_errors();
    }

    return 0;
}