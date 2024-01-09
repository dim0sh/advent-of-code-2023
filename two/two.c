#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_red 12
#define max_green 13
#define max_blue 14
#define num_pulls 3

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
game_t * parse_game(char * game_result)
{
    // create new game struct to contain gameresult
    game_t * game = (game_t *) malloc(sizeof(game_t));
    game->red = (int *) malloc(num_pulls*sizeof(int));
    game->green = (int *) malloc(num_pulls*sizeof(int));
    game->blue = (int *) malloc(num_pulls*sizeof(int));
    // read game id from string
    int i = 5;
    char string_id[4];
    while ((int)game_result[i] != 58/*58 => ASCII for :*/)
    {
        string_id[i-5] = game_result[i];
        i++;
    }
    game->id = atoi(string_id);
    
    
    
    
    
    
    // game->red[0] = 2;
    // game->red[1] = 1;
    // game->red[2] = 1;
    // game->green[0] = 1;
    // game->green[1] = 1;
    // game->green[2] = 1;
    // game->blue[0] = 1;
    // game->blue[1] = 1;
    // game->blue[2] = 1;
    
    
    return game;
}
int valid_game(game_t * game)
{
    int verify = 0;
    for (int i = 0; i < num_pulls; i++)
    {
        if (game->red[i] <= max_red 
        && game->green[i] <= max_green 
        && game->blue[i] <= max_blue)
        {
            verify++;
        }
    }
    if (verify == num_pulls)
    {
        return game->id;
    }
    return 0;
}

int main()
{
    char * game_result_1 ="Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green";
    char * game_result_2 ="Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue";
    char * game_result_3 ="Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red";
    char * game_result_4 ="Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red";
    char * game_result_5 ="Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green";
    
    game_t * game1 = parse_game(game_result_1);
    int x = valid_game(game1);
    printf("game id: %d\n", game1->id);
    printf("valid game id: %d",x);

    return 0;
}