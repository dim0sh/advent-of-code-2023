#include <stdio.h>

#define max_red 12
#define max_green 13
#define max_blue 14

/*
 * records game information
 * @param int id
 * @param int array red pieces
 * @param int array green pieces
 * @param int array blue pieces
 */
typedef struct game {
    int id;
    int * red;
    int * green;
    int * blue;
} game_t;
/*
 * parse game result string -> to new gamestruct
 * @param char* game result string
 */
void parse_game(char * game)
{
    
}

int main()
{
    char * game1 ="Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green";
    char * game2 ="Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue";
    char * game3 ="Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red";
    char * game4 ="Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red";
    char * game5 ="Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green";
    
    return 0;
}