/*
 * ============================================================
 *   D E B U G G E R : T H E   L A S T   P A T C H
 *   bosses.c — Boss definitions, ASCII art, questions
 * ============================================================
 */

#include "debugger.h"

void init_bosses(Boss bosses[NUM_BOSSES]) {
    int i;
    for (i = 0; i < NUM_BOSSES; i++) {
        bosses[i].defeated      = 0;
        bosses[i].art_row_count = 0;
        bosses[i].art_color     = C_WHITE;
    }

    /* =============================================================================================================================
       BOSS 0 — VARSHADE  (Variables)
       ============================================================================================================================= */
    strcpy(bosses[0].name,     "VARSHADE");
    strcpy(bosses[0].topic,    "Variables");
    strcpy(bosses[0].location, "THE ROOTWAYS");

    {
        const char *art[] = {
        "                              +                                        ",
        "                         +@@@     @                                    ",
        "                        @@@@@ :@@@:  -                                 ",
        "                       @@@@@@@@@@  @                                   ",
        "                     #@@@@@@@@@@ @                                     ",
        "                     -# @@@+ /@@@                                      ",
        "                      - @@@/ #@@@                                      ",
        "                      @@@@@@@@@@                                       ",
        "                       -@@@@@@@@@#= :  +                               ",
        "                        :@@@@@@@@@@@@  .                               ",
        "                      @@@@@@@@@@@@@@@@@@@@@:#                          ",
        "                     :@@@@ :@@@  @@@@@@@@@@@.                          ",
        "                      @@@@ +@@@@ @@@@@@- @@@@@              @@@        ",
        "                     @@@@@ :@@@@ @@@@      -+@@@@- *      @@@+@@       ",
        "                     /@@ :@ *@@@@ @@@+       =@@@@     @@+@@  *@@      ",
        "          .@@=       @@#    @@@@@@@@@          @@+@@@@+        @@/     ",
        "       @@@*  @@@      @.       @@@@@@ /:         @@@:@@         =@@@   ",
        "      @@@@  :@@@@  @@@@-       :@@@@@@          @@@#:           /@@/   ",
        "     @#@/     @   :@@@@           @@@*  @.                     -@@@@@# ",
        "   @#@/      @       =        #@@ :@@                       +# @@@@+   ",
        "    = @                      *@@@@@@*                       :  :@*@@   ",
        "    : /#=                #@=@@@. @:                             @ *++  ",
        "       :                @@                                      @ #    ",
        "                         *@                                   @  :     ",                                                                                                                         
        };
        int r;
        bosses[0].art_row_count = 24; bosses[0].art_color = C_MAGENTA;
        for (r = 0; r < 24; r++)
            strncpy(bosses[0].art[r], art[r], ART_COLS - 1);
    }

    /* Questions */
    strcpy(bosses[0].questions[0].question,
        "What is a variable in C?");
    strcpy(bosses[0].questions[0].choices[0], "A. A function that stores logic");
    strcpy(bosses[0].questions[0].choices[1], "B. A named memory location that stores a value");
    strcpy(bosses[0].questions[0].choices[2], "C. A type of loop");
    strcpy(bosses[0].questions[0].choices[3], "D. A fixed constant that never changes");
    bosses[0].questions[0].correct = 1;
    strcpy(bosses[0].questions[0].explanation,
        "A variable is a named storage location in memory that holds a value which can change during program execution.");

    strcpy(bosses[0].questions[1].question,
        "Which declaration correctly initializes an integer variable to 5?");
    strcpy(bosses[0].questions[1].choices[0], "A. int x;");
    strcpy(bosses[0].questions[1].choices[1], "B. int x = 5;");
    strcpy(bosses[0].questions[1].choices[2], "C. x = 5;");
    strcpy(bosses[0].questions[1].choices[3], "D. variable x = 5;");
    bosses[0].questions[1].correct = 1;
    strcpy(bosses[0].questions[1].explanation,
        "'int x = 5;' both declares the type AND initializes it. Just 'int x;' declares but leaves value undefined.");

    strcpy(bosses[0].questions[2].question,
        "What happens if you use an uninitialized variable in C?");
    strcpy(bosses[0].questions[2].choices[0], "A. It defaults to 0 automatically");
    strcpy(bosses[0].questions[2].choices[1], "B. The compiler always gives an error");
    strcpy(bosses[0].questions[2].choices[2], "C. It contains garbage — undefined behavior");
    strcpy(bosses[0].questions[2].choices[3], "D. It becomes NULL");
    bosses[0].questions[2].correct = 2;
    strcpy(bosses[0].questions[2].explanation,
        "Uninitialized local variables hold whatever random garbage was in that memory address. This is undefined behavior — just like the VarShade.");

    /* =============================================================================================================================
       BOSS 1 — BRANCHWRAITH  (If/Else)
       =============================================================================================================================*/
    strcpy(bosses[1].name,     "BRANCHWRAITH");
    strcpy(bosses[1].topic,    "If/Else — Selection");
    strcpy(bosses[1].location, "THE ASHFIELDS");

    {
        const char *art[] = {
"                                                       .    .:      -    :.                   ",
"                                                       :+:   =- :-  =-: -=                    ",
"                                                        -#@+  +@..* %+                        ",
"                                                            #=@@.% @@%@+                      ",
"                                                          -#-*@@@@@@                          ",
"                                                              %@@@@ :     =*+.                ",
"                                                              .@@@=+   :+*                    ",
"                                                                %@@%--=      :.               ",
"                                                        ::..-+#@@@@@%*=#=  -@#.               ",
"                                                       := :%#=-*@@+=+:-.-*#@@@@-:             ",
"                                                      :%@#**.  -=   ::.=::. =@+ -             ",
"                                                     :@@@@#.  *-   #@@@+  .: :%:.:            ",
"                                                   ..- .%#  .@@@@  *@@@+  ::  #*:             ",
"                                                  -    =#:   %@@@ ..=:  -:     *%@@*=*.       ",
"                                              =:%:  ##+#=     =-::=    .+:::.  -. %+.     -   ",
"                                             :    :==  :-     @@@@#.    =@@@*  ::   @*:.   -  ",
"                                                .@@@@  -*-   -=+@%  *     -:        @- .      ",
"                                                 :@.   :    +-   %*    =   --       %:@.      ",
"                                             .=..:%-       #@@@: :@.   =@=%@@@@@:     @%:=    ",
"                                             =:  .@@@*      #+:=:@@   -  :@@@@@@-   -%:@  .   ",
"                                            +#:  :@@@@     .*: #- -#  +.  .::::.    +  @: .:  ",
"                                           -##=   -+-.    :=. -%   +@-  :=         =@   ::    ",
"                                          *@@@@-        .:=*:=@@: +-%:    .       #=@-: .*    ",
"                                        .:%@@***          =@@@@@@+   @    .       @@@@@  :*.  ",
                                                        
        };
        int r;
        bosses[1].art_row_count = 24; bosses[1].art_color = C_CYAN;
        for (r = 0; r < 24; r++)
            strncpy(bosses[1].art[r], art[r], ART_COLS - 1);
    }

    strcpy(bosses[1].questions[0].question,
        "What does an if/else statement do in C?");
    strcpy(bosses[1].questions[0].choices[0], "A. Repeats a block of code multiple times");
    strcpy(bosses[1].questions[0].choices[1], "B. Executes different code based on a condition");
    strcpy(bosses[1].questions[0].choices[2], "C. Declares a new variable");
    strcpy(bosses[1].questions[0].choices[3], "D. Calls a function");
    bosses[1].questions[0].correct = 1;
    strcpy(bosses[1].questions[0].explanation,
        "if/else is selection — it evaluates a condition and branches to the correct block. True path or false path.");

    strcpy(bosses[1].questions[1].question,
        "What is the output of: if (0) printf(\"A\"); else printf(\"B\");");
    strcpy(bosses[1].questions[1].choices[0], "A. A");
    strcpy(bosses[1].questions[1].choices[1], "B. B");
    strcpy(bosses[1].questions[1].choices[2], "C. AB");
    strcpy(bosses[1].questions[1].choices[3], "D. Nothing");
    bosses[1].questions[1].correct = 1;
    strcpy(bosses[1].questions[1].explanation,
        "In C, 0 is FALSE. So the if-block is skipped and the else-block runs, printing B.");

    strcpy(bosses[1].questions[2].question,
        "Which operator checks if two values are EQUAL in C?");
    strcpy(bosses[1].questions[2].choices[0], "A.  =");
    strcpy(bosses[1].questions[2].choices[1], "B. ==");
    strcpy(bosses[1].questions[2].choices[2], "C. !=");
    strcpy(bosses[1].questions[2].choices[3], "D. >=");
    bosses[1].questions[2].correct = 1;
    strcpy(bosses[1].questions[2].explanation,
        "'==' compares. '=' assigns. Using '=' in a condition is the classic bug — the BranchWraith's favorite meal.");

    /* =============================================================================================================================
       BOSS 2 — VOIDCALLER  (Functions)
       =============================================================================================================================*/
    strcpy(bosses[2].name,     "VOIDCALLER");
    strcpy(bosses[2].topic,    "Functions");
    strcpy(bosses[2].location, "THE CLIFFSHORE");

    {
        const char *art[] = {
"                               :                               =@@@@@@@@@@#.                  .                      ",
"                                 :                   .        @@@@@@@@@@@@@@@@@%               '                     ",
"                                   :           .    '       %@#. =  * =@@@@@@@@@@@@                 .                ",
"                     '           :            '            #@ - =  - .= :*@@@@@@@@@@@:             '                 ",
"                        :           :                     .+:.-#@@@@+@ .* -#@@@@@@@@@#*@-                            ",
"                                      :                   -:@@@@@@@@@@@@:*- @@@@@@@@@@@+   .++.                      ",
"                                        .       .         .@@@@@@@@@@@@@@@.@ .@@@@@@@@@@@@                           ",
"                   : '                 '       '           @@@@@@@@@@@@@@@@@@% @@@@@@@@@@@@@@@%%+:.:-+               ",
"                                         :                :**@@@@@@@@@@@@@@@@.@@@@@@@@@@ .@@@@@@%=:                  ",
"                                           :                 .=@@@@@@@@@@@@@@@@@@@@@@@@@@@.          :-+-           ",
"                         '                .+ ..     .           :@@@@@@@@@@@@@@@@@@@@@@@@@@@@=:           -.        ",
"                        :'                 .#: #      .          :@@@@@@@@@@@@@@#@@@@@@@@@=       -@@%@@:       ..  ",
"                                                               ++%@@@@@@@@@@@@%@@@@@@@@@@@*           #.:@@.        ",
"                  :                 :                         #@@@@@@@@@@@@@# @@@@@@@@@@@@@@.               .#.     ",
"                                             '               =@@@@@@@@@@@@ @.@@@@@@@@@@@@@@@@@@.              +.    ",
"                                                             +=-#@@@@=@-.= @@@@@@@@@@.    :@@@=@@@@=-+@        ::   ",
"                               :                      .      -@.- = * + #@@@@@@@@@@@@#      .@% :       +         . ",
"                                                    '         @@@%*=%@@@@@@@@@@@@@@@-@@       @+         =          ",
"                                 '  :                          +@@@@@@@@@@@@@@@@@@@@*  *#       :*                  ",
"                                '                                  :*@@@@@@@@@@@%@@@@*  .*       :-                 ",
"                                        '                                  =+  +@: @@@#  .-        ::               ",
"                          .            '                                      *  .- -@@-   -                        ",
"                         '                                                        . @@#                             ",
"                                                                                   . *@=                            ",
"                                                                                     @:                             ",
"                                                                                    -z                              ",                                             
"                                                                                                                    ",
"                                                                                                                    "
        };
        int r;
        bosses[2].art_row_count = 28; bosses[2].art_color = C_BLUE;
        for (r = 0; r < 28; r++)
            strncpy(bosses[2].art[r], art[r], ART_COLS - 1);
    }

    strcpy(bosses[2].questions[0].question,
        "What is the correct syntax to declare a function in C?");
    strcpy(bosses[2].questions[0].choices[0], "A. function myFunc() {}");
    strcpy(bosses[2].questions[0].choices[1], "B. def myFunc(): pass");
    strcpy(bosses[2].questions[0].choices[2], "C. void myFunc() {}");
    strcpy(bosses[2].questions[0].choices[3], "D. myFunc => void {}");
    bosses[2].questions[0].correct = 2;
    strcpy(bosses[2].questions[0].explanation,
        "In C: return_type function_name(parameters) { body }. 'void' means it returns nothing.");

    strcpy(bosses[2].questions[1].question,
        "What does 'void' mean as a return type?");
    strcpy(bosses[2].questions[1].choices[0], "A. The function returns 0");
    strcpy(bosses[2].questions[1].choices[1], "B. The function returns nothing");
    strcpy(bosses[2].questions[1].choices[2], "C. The function can return anything");
    strcpy(bosses[2].questions[1].choices[3], "D. The function is empty");
    bosses[2].questions[1].correct = 1;
    strcpy(bosses[2].questions[1].explanation,
        "void means the function completes its task and returns nothing to the caller. Like the VoidCaller — except it refuses to return at all.");

    strcpy(bosses[2].questions[2].question,
        "What is a function parameter?");
    strcpy(bosses[2].questions[2].choices[0], "A. A value a function returns");
    strcpy(bosses[2].questions[2].choices[1], "B. A variable that stores the function name");
    strcpy(bosses[2].questions[2].choices[2], "C. A value passed INTO the function when called");
    strcpy(bosses[2].questions[2].choices[3], "D. A special kind of loop");
    bosses[2].questions[2].correct = 2;
    strcpy(bosses[2].questions[2].explanation,
        "Parameters are the inputs declared in the function signature. Arguments are what you pass when calling it.");

    /* =============================================================================================================================
       BOSS 3 — FORMLESSONE  (Structs)
       =============================================================================================================================*/
    strcpy(bosses[3].name,     "FORMLESSONE");
    strcpy(bosses[3].topic,    "Structs");
    strcpy(bosses[3].location, "THE DROWNED DARK");

    {
        const char *art[] = {
                             
          "                                                .     ___..                -=:___           .     ",                     
          "                                                         .+     ::..:=.    +.                '    ",                     
          "                                  '            ______..   :. ::.... ...:-  :    .:______          ",                     
          "                                                ____..+.   .::. .... ....:.     :.   .____        ",                     
          "                                   .                  -.  .-:.: : .....=::.:        - =           ",                     
          "                                  '         ..           .-:-.:.       .....:       ::            ",                     
          "                                          :=...        .-**+-::.--: .. ..--:*-.     -.            ",                     
          "                                         .@-:+.    .+*#@%@=*:::  . ...:-...---.*.         -.      ",                     
          "                                        .*%::=    .#:   =---=... . ... .:..*-=#*%#-.    ..-#*-    ",                     
          "                                        :@.       *:   .=:...... . .  . ...:+-=#::=*#.  .-==+@-   ",                     
          "                                         -%.     =-   .+:.:.-.-: . ....:.....::=.   -+   ..+..**  ",                     
          "                                         .@.    :+   :=::-:....  ..     . ..:...=.   ==       :-  ",                     
          "                                          +:   :+:.:**==*--.::.. ...   :: . ...:.=:   +:      +.  ",                     
          "                                          .=  .+@#*.    =+:::.....    .:..-....:..:-  .+.    .*.  ",                     
          "                                           *. =#.      ----...        .. . .=..=%::**:.-=.   ::   ",                     
          "                                           ==         :.-.....: .:   --:......:-+:   .=%@=   =.   ",                     
          "                                           .+.       ..-....::.  . .  . . .-.:-.:::     .=. :+    ",                     
          "                                            +*.       -:..:.: ..     ..: .:.....=:-.       .*:    ",                     
          "                                            .=-:   .=.. ....:. . .:..  .. ....:-.:-        =*.    ",                     
          "                                             .::-++-:.::-.:::.::.::.   ..-....:.:.:.:..  .+-:     ",                     
          "                                              .=.-- :.:-=:+-:..-       .. ...::.:...::--=..:      ",                     
          "                                                 :-.-:.    :=::.. :..:. . ...-=------.:..:.       ",                     
          "                                                           .:.-.:... .. :..--:-  ..:=:::.         ",                     
          "                                                          ..:...-:.. .:.-....:-.                  ",                     
          "                                                            .:=:...........::-.                   ",
          "                                                                :+.=-=-:=.                        ",                     
          "                                                                :+:-.:-.+.                        ",                     
          "                                                           ...:.-:.--::.-.--.                     ",                     
          "                                                .-:..---:. .::-: ....... ....::. .:---:..-.       ",                     
          "                                            ..::..::.-.::...::..:.:. -.. :.:....::...:::..::::.   ",                     
          "                                              .--.  .::::   :::..:.  .:::..:..:::.-: .   .::.     ",                     
        };
        int r;
        bosses[3].art_row_count = 31; bosses[3].art_color = C_BMAGENTA;
        for (r = 0; r < 31; r++)
            strncpy(bosses[3].art[r], art[r], ART_COLS - 1);
    }

    strcpy(bosses[3].questions[0].question,
        "What is a struct in C?");
    strcpy(bosses[3].questions[0].choices[0], "A. A type of loop");
    strcpy(bosses[3].questions[0].choices[1], "B. A single variable that holds one value");
    strcpy(bosses[3].questions[0].choices[2], "C. A user-defined type grouping related variables");
    strcpy(bosses[3].questions[0].choices[3], "D. A built-in C function");
    bosses[3].questions[0].correct = 2;
    strcpy(bosses[3].questions[0].explanation,
        "A struct bundles multiple variables (fields/members) of different types into one named record. Like a blueprint.");

    strcpy(bosses[3].questions[1].question,
        "How do you access a struct member in C?");
    strcpy(bosses[3].questions[1].choices[0], "A. struct->member");
    strcpy(bosses[3].questions[1].choices[1], "B. struct.member");
    strcpy(bosses[3].questions[1].choices[2], "C. struct[member]");
    strcpy(bosses[3].questions[1].choices[3], "D. struct::member");
    bosses[3].questions[1].correct = 1;
    strcpy(bosses[3].questions[1].explanation,
        "Use the dot operator '.' to access a member of a struct variable. Use '->' only when you have a pointer to a struct.");

    strcpy(bosses[3].questions[2].question,
        "Given: struct Point { int x; int y; }; Point p;\nHow do you set p's x to 10?");
    strcpy(bosses[3].questions[2].choices[0], "A. p->x = 10;");
    strcpy(bosses[3].questions[2].choices[1], "B. Point.x = 10;");
    strcpy(bosses[3].questions[2].choices[2], "C. p.x = 10;");
    strcpy(bosses[3].questions[2].choices[3], "D. x(p) = 10;");
    bosses[3].questions[2].correct = 2;
    strcpy(bosses[3].questions[2].explanation,
        "p.x = 10; — variable name, dot, member name. The struct is the container; the dot opens it.");

    /* =============================================================================================================================
       BOSS 4 — INDEXSERPENT  (Arrays)
       =============================================================================================================================*/
    strcpy(bosses[4].name,     "INDEXSERPENT");
    strcpy(bosses[4].topic,    "Arrays");
    strcpy(bosses[4].location, "THE SUNKEN BASIN");

    {
        const char *art[] = {
          
    "                               _________                          ____            _________  ",            
    "                                   ______                  _..+~/@-~--.@       _______       ",                
    "                                         ____         _-=~@@@~@ (@@@  @@   _______           ",
    "                                                 - _-~*:@@@_.--=.n@@ @@n                     ",
    "                                                _-+*:.=~@@/-       @  @_                     ",
    "             ____________                      =*:.=~@@/_=         '--'                      ",                 
    "                  _____________             '*:.=~@@@/              ''                       ",               
    "                        ____________       '*:.@@@ =/                                        ",              
    "                                         :*:.@@@=~/:                                         ",            
	"                               	    |*:.@@@.~/;                                           ",     
	"                               	  |*:.@@@=~';                                             ",     
	"                               	 |*:@@@@ =~';                                             ",                 
	"                                   |* @@@@@@@.=~'                                            ",
	"                                  |*:.@@@@@@...=~'*                              ,           ",
    "                                 '*:.=@@@@@@@@@.=~***'                         .             ",
    "                                 :*:.=~@@@@@@@@@@@.=~***:'                    '=_. ___       ",
    "                                |*:.=~@@@@@@@@@.=@@@@;'=~.=~: '             ____ '~--.~.     ",
    "                                ;*:.=~:.@@@@@@.=~;@@@@~:=~.=~: '            ____  _  } |     ",
    "                               _=*:.:.=~@@@@@@@@@.=~' @@@@__ __..-...__          ___/__/__   ",
    "                                : *:.=~ @@@=_ @@.= @@@@@@ _.-~~   *:.=~   ~~--.__            ",
    "                               _      *:.=~=~.=@@@@@@@@@~-+-~*:.=~*:.=~*:.=~  *:.=~   __ ____",
    "                                ~@#~~ == ...______ __ ___ _--~~--_                      ",  
            
        };
        int r;
        bosses[4].art_row_count = 22; bosses[4].art_color = C_BGREEN;
        for (r = 0; r < 22; r++)
            strncpy(bosses[4].art[r], art[r], ART_COLS - 1);
    }

    strcpy(bosses[4].questions[0].question,
        "What is the index of the FIRST element of an array in C?");
    strcpy(bosses[4].questions[0].choices[0], "A. 1");
    strcpy(bosses[4].questions[0].choices[1], "B. -1");
    strcpy(bosses[4].questions[0].choices[2], "C. 0");
    strcpy(bosses[4].questions[0].choices[3], "D. It depends on the array size");
    bosses[4].questions[0].correct = 2;
    strcpy(bosses[4].questions[0].explanation,
        "Arrays in C are zero-indexed. The first element is always at index 0. This is why the IndexSerpent lives at index -1 — a place that shouldn't exist.");

    strcpy(bosses[4].questions[1].question,
        "int arr[5]; — What is the valid index range?");
    strcpy(bosses[4].questions[1].choices[0], "A. 1 to 5");
    strcpy(bosses[4].questions[1].choices[1], "B. 0 to 5");
    strcpy(bosses[4].questions[1].choices[2], "C. 0 to 4");
    strcpy(bosses[4].questions[1].choices[3], "D. -1 to 4");
    bosses[4].questions[1].correct = 2;
    strcpy(bosses[4].questions[1].explanation,
        "int arr[5] creates 5 elements: arr[0] through arr[4]. Accessing arr[5] or beyond is out-of-bounds — undefined behavior.");

    strcpy(bosses[4].questions[2].question,
        "How do you declare an integer array of size 10 in C?");
    strcpy(bosses[4].questions[2].choices[0], "A. array int[10];");
    strcpy(bosses[4].questions[2].choices[1], "B. int arr[10];");
    strcpy(bosses[4].questions[2].choices[2], "C. int arr = new int[10];");
    strcpy(bosses[4].questions[2].choices[3], "D. int[10] arr;");
    bosses[4].questions[2].correct = 1;
    strcpy(bosses[4].questions[2].explanation,
        "int arr[10]; — type first, then name, then size in brackets. Clean. Simple. Indexed from 0 to 9.");

    /* =============================================================================================================================
       BOSS 5 — NULLFANG  (Pointers)
       =============================================================================================================================*/
    strcpy(bosses[5].name,     "NULLFANG");
    strcpy(bosses[5].topic,    "Pointers");
    strcpy(bosses[5].location, "THE VEINPLAINS");

    {
        const char *art[] = {
                                                                                                            
    "                                                                                --+-.                               ",          
    "                                                                             =%:.:.                                 ",          
    "                                                                           :@+                                      ",          
    "                                                                    :  .*#          --:                             ",          
    "                                                        ..     -*@@@@@@@@@@@%#-                                     ",          
    "                     :=*%@@%#=-                       -     *@@@@@@#:                                               ",          
    "                 -*%@@@@@@@@@@@@@@*=                 +.   *@@@@#%#:.                                          :.    ",          
    "               %@@@- :*@@@@@@@@@@@@%%*--=-:-#*     -+:**:%%%@@@+     .                                       +.     ",          
    "             *@@@*+@@@@ #@@@@@@@@@@@@@@=.      *@@#%%@%*%@@@@@@@@@@@@@@+*@@-                               *+       ",          
    "            @@@@% %@@@@:@@@@@@@@@@@@@@@@@@@@@@@@@@@**@@@@@@@@@@@@@@@@@@@@@@@@@@=                        .@%         ",          
    "           #%@@@@% -*. %@@@@@@-@@@+@@@@@:=@@@@%:*%+@@@@@@##+*:.=*%%#+:.-=**@@@@@@++                    =+-          ",          
    "          -@@@@@@@@@@@@@%#@%#@@@@@@@@@@@@@@@@*%@@@@@@@@@++=#@@@@@@@@@@@@@*:. ..+@@%.               :%@.  .       +  ",          
    "           .@:%+*++@%@@@@@@@@@@@@@@@@@@@@@@@+@@@@@@@@@=@@@@@@@@@@@@@@@-*#@@@@@@@@.@@@:          :@@@#     .    -    ",          
    "            @ * =  # -  *:#@%@@@@@@@+ %@:@@@@@@@@@-%-@@@@@@@@@=@@@@= =%@@@@@*@@@@@#+@@*@@@-=*@@%     +    . +       ",          
    "             .             :. @@@+*@@@@@@#.=#@@@%%@*@%#@@@@@@@@@:          %@=%@@@@@-@@**:.%@@:          :*         ",          
    "                             .@@@%@@@@@@@@*-@@@**@@%%@@@@@@-     %+@         -  #@@@@*.#@@@@+-        -*      .-    ",          
    "                           +.%@@@@@%@@@@@@@@@@@@@@@@%#*@-          *@@@%:      =:=@@@@@#@@@@@@@@%%%%%@@%%%@@-       ",          
    "                       : -+-@@+@@@@@@+@@@@@@@@@@@@@@@%:              :#@@@.        @@@@@@@@@@@@@@@@%=-:...          ",          
    "                  :  + .%#@@@@@#=: :+@- .@@#@@@@@*                      . =          #%=@@=     .                   ",          
    "                 -.%.=@@@@#+*%@=       *+ -=  -@@@@@@@@@%*: ..             #.          :+.:#*                       ",          
    "                  %*@@@@@* =    +=         .=+:       :-.      -:           %.             .     .+.                ",          
    "                   +- :=*@:      -=           ##.                            =%=                                    ",          
    "                          %+      --          .==                                  =@@=              ..             ",          
    "                           : :.       ..         -:                                   -*                            ",          
    "                            :.:       .             :*-.                                -:                          ",          
    "                                -                       *+...                             .+                        ",          
    "                                  .#:=                    :    .-+                          +                       ",          
    "                                        -                  -.   .                            =.                     ",          
    "                                          +.                   :--.                                                 ",          
    "                                           .                        +.                                              ",          
    "                                                                                                                    ",   
        };
        int r;
        bosses[5].art_row_count = 31; bosses[5].art_color = C_WHITE;
        for (r = 0; r < 31; r++)
            strncpy(bosses[5].art[r], art[r], ART_COLS - 1);
    }

    strcpy(bosses[5].questions[0].question,
        "What is a pointer in C?");
    strcpy(bosses[5].questions[0].choices[0], "A. A variable that stores another variable's value");
    strcpy(bosses[5].questions[0].choices[1], "B. A variable that stores a memory address");
    strcpy(bosses[5].questions[0].choices[2], "C. A type of array");
    strcpy(bosses[5].questions[0].choices[3], "D. A function that points to memory");
    bosses[5].questions[0].correct = 1;
    strcpy(bosses[5].questions[0].explanation,
        "A pointer stores the memory address of another variable. It doesn't hold the value directly — it holds the location of the value.");

    strcpy(bosses[5].questions[1].question,
        "What does the & operator do in C?");
    strcpy(bosses[5].questions[1].choices[0], "A. Dereferences a pointer");
    strcpy(bosses[5].questions[1].choices[1], "B. Multiplies two values");
    strcpy(bosses[5].questions[1].choices[2], "C. Gets the memory address of a variable");
    strcpy(bosses[5].questions[1].choices[3], "D. Declares a pointer");
    bosses[5].questions[1].correct = 2;
    strcpy(bosses[5].questions[1].explanation,
        "& is the 'address-of' operator. int x = 5; int *p = &x; — p now holds the address where x lives in memory.");

    strcpy(bosses[5].questions[2].question,
        "What is a NULL pointer?");
    strcpy(bosses[5].questions[2].choices[0], "A. A pointer that points to the value 0");
    strcpy(bosses[5].questions[2].choices[1], "B. A pointer that points to nothing — no valid address");
    strcpy(bosses[5].questions[2].choices[2], "C. A pointer with no declared type");
    strcpy(bosses[5].questions[2].choices[3], "D. A pointer that has been freed");
    bosses[5].questions[2].correct = 1;
    strcpy(bosses[5].questions[2].explanation,
        "NULL means the pointer is intentionally pointing at nothing. Dereferencing NULL crashes your program — the NullFang's signature move.");

    /* =============================================================================================================================
       BOSS 6 — HYDRAEXCEPTION  (All classes)
       ============================================================================================================================= */
    strcpy(bosses[6].name,     "HYDRAEXCEPTION");
    strcpy(bosses[6].topic,    "Fatal Exception — All Errors");
    strcpy(bosses[6].location, "THE WORLDROOT");

    {
        const char *art[] = {                                                                                                                                                 
     "                                                :  .+   .              -%  :-   -:  %                                            ",              
     "                                               :::-*.=+-               :%:.%     #.#-                                            ",              
     "                                             ..@+%%%@@%@#..           ..*@:+=*%+==:%:                 -    -                     ",              
     "                                              *#@%%%%%%%%@=            =-@%#%@@@@#@@=-             :=*:++..::                    ",              
     "                                             .##%+#%%%@@@#@+           :%@%@%@@@#@#@*.           :%@@%@%%%%*=:                   ",              
     "                                             .%*@@*#=..%@@@%:          --@%@@%@@@%%@==          =%#%%@%@%%%@#:                   ",              
     "                                              =#=:%-   =%@%@=           :@#:*@@%#-%@-          *@%@@@%%%%#%%*:                   ",              
     "                                                =#=    -%@%@+            *%%%#@#%%%+          *@%@@+   **=@%@:                   ",              
     "                                                 =.    #%@@#-             -%*%@%*#*          .%@@@+     =*:::                    ",              
     "                                                      :%%@@#              -@*++=+%=          *@%@%.     .#%.                     ",              
     "                                                     .%@@%%.              .@%=.-#@:          -@%@@-      :                       ",              
     "                                                     =@@@@@               :@%%%###           :#@@@@.                             ",              
     "                                                     +#@@@*    :           @@@%%%%+           +@@@@*                 -   .       ",                 
     "                                  +                  =@%@@#:  *.  .        +@@@@%%-            +@%@%#                 *-  -      ",               
     "                             -   +:..-               .@@@+%#-#.*#.         +@@%@@%+            .@@@@@:            +%@@%%#== -    ",               
     "                            -::-%%%@@@*               :%@#*@#@%@#%#        :#@@@@%%.            *@%@@*          *@#@%%%@%#@*=    ",              
     "                            :#@%%@%%#@%@@:             :%*%%%@%%@%@%-       =%@@#@%%            #%%@%#        .%%#@@@%#%##%@=:   ",              
     "                            #%%%%@%#@@@@%@*             :%%#:*%@%@@%%-      -@#@@@%@#=         .#%%@@#        +%%@@#.:%%@@%%*.   ",                    
     "                           .*#%#%%@= .%@@%%*            .%%%@*@=@@@@@#       *@@@%@%%%        *@%%@@%-        @%@%%:   +#-%#%    ",               
     "                            #*@*+#.   .%@@@#             +@#.#. -@@@@%=      *@%@@@%@%.   .+#%@@@@@@#         ##@@%.    +=::     ",              
     "                            .+=:#      #@@%@*              .+*=  .%@@%@=     :@@@@%@%%@@: *@@%%@@@@%=        =%@%@@%+    :#-     ",                 
     "                              -@+      #@@%@@@%:              :%   :%%@%%*:    +%%@@@@@@#%#@%@%@@@@@@:      .:*#%@@@#            ",              
     "                                .      %%@@%%@@@*.              *%@%@%%%   :#@@@@@@@@#%@%@%@@%@%:        .:*#%@%@%%:             ",              
     "                                       +@@%@*. %@@@@@%@@@%@@@%@@@%@@@%@@@%@@@%@@@%@@@@%%@%:%@@%@@@#@@   .:*#%@#@@%.              ",              
     "                                       .#@@@%@@@@%@@@#@@@@%@@@%@@@%@@@%@@@%@@@%@@@=@@@@%%%%%@@@%%@%.  .:*#%@=%@@%+               ",              
     "                                        +@%@%@@*%@@@@%@@@#@@@@%@@@#@@%@@@@%@@@#@%@@@@*@@%#@%@@%        .:*#%@#%%@@*              ",              
     "                                         =#@@@%%@@@%##.       -%%@@@@@%#@@@+@@@#@@@@#@%@@%@%%      .:*#%@ #%@@@*                 ",              
     "                                          :*%@@@@@@@@@@@=  .+#@%@@@@#@%@%@%@%@@%@@@@##@@@%%%@%=.  .:*#%@*#%@@@#                  ",              
     "                                            :+%%@@@@@@@@@@%@@@%@@@%*%+#%@@@*%@@@#@@@%+@%@@%%%@@%:+%@@@-%%@@@@@%@@%%=             ",              
     "                                               .*@@@@@@@#%##*@@@%@@@#@%@@@@@*%@@@%#@%*@@@@@@@*@@@%#+%@@@@%%@@@@@@%-              ",              
     "                                                 .%@@%%*#@@#@@%%@@@%%@@%@%@%%@@@@@@%@#*%@@@@@%*%%%@%%@@@@@@@%@%@*                ",              
     "                                             *:=#@@@#%@@*@@@@%@@@@#@@@@. %@@%@@-#@@%@@@##@@%#@@#@@+@@%#*%%%@@%-                  ",              
     "                                           +*@@@%#+@@%#-@%%#@+ .#@@%+-  :#@@@%@# - *@@@%.#@@@@@-@@%=#@@@%%@%%@@@:..=-            ",              
     "                                   -##*%@@@. .+%#     .#%@-   .#*     -@@%+ #%@%:   :#%@+    #@%%:.:= -%%@:..: .#@%%@*:-.        ",              
     "                                                   :.             :+-. :      :. ==       .       :.-=.                          "  
        };
        int r;
        bosses[6].art_row_count = 35; bosses[6].art_color = C_BRED;
        for (r = 0; r < 35; r++)
            strncpy(bosses[6].art[r], art[r], ART_COLS - 1);
    }

    /* One question from each corruption class */
    strcpy(bosses[6].questions[0].question,
        "HEAD 1 (Variables): What keyword declares a constant in C?");
    strcpy(bosses[6].questions[0].choices[0], "A. static");
    strcpy(bosses[6].questions[0].choices[1], "B. const");
    strcpy(bosses[6].questions[0].choices[2], "C. fixed");
    strcpy(bosses[6].questions[0].choices[3], "D. final");
    bosses[6].questions[0].correct = 1;
    strcpy(bosses[6].questions[0].explanation,
        "'const' tells the compiler this variable's value cannot be changed after initialization.");

    strcpy(bosses[6].questions[1].question,
        "HEAD 2 (If/Else): What does else-if allow you to do?");
    strcpy(bosses[6].questions[1].choices[0], "A. Loop through a range of values");
    strcpy(bosses[6].questions[1].choices[1], "B. Check multiple conditions in sequence");
    strcpy(bosses[6].questions[1].choices[2], "C. Compare two strings");
    strcpy(bosses[6].questions[1].choices[3], "D. Call a function conditionally");
    bosses[6].questions[1].correct = 1;
    strcpy(bosses[6].questions[1].explanation,
        "else if chains let you check multiple conditions one by one — only the first true branch executes.");

    strcpy(bosses[6].questions[2].question,
        "HEAD 3-6 (All): Which concept lets a function call itself?");
    strcpy(bosses[6].questions[2].choices[0], "A. Iteration");
    strcpy(bosses[6].questions[2].choices[1], "B. Polymorphism");
    strcpy(bosses[6].questions[2].choices[2], "C. Recursion");
    strcpy(bosses[6].questions[2].choices[3], "D. Dereferencing");
    bosses[6].questions[2].correct = 2;
    strcpy(bosses[6].questions[2].explanation,
        "Recursion — a function that calls itself. Like the Hydra regrowing heads, it must have a base case or it runs forever.");
}