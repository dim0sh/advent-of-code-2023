#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_red 12
#define max_green 13
#define max_blue 14
#define num_pulls 5

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
game_t * parse_game(char * game_input)
{
// Add a function declaration or remove the unnecessary opening brace.
    // add ! to end of string
    char * game_result = (char *) malloc(sizeof(char)*strlen(game_input)+1);
    strcpy(game_result,game_input);
    strcat(game_result,"!");
    // create new game struct to contain gameresult
    game_t * game = (game_t *) malloc(sizeof(game_t));
    game->red = (int *) calloc(num_pulls,sizeof(int));
    game->green = (int *) calloc(num_pulls,sizeof(int));
    game->blue = (int *) calloc(num_pulls,sizeof(int));
    // read game id from string
    int i = 5;
    char string_id[4] = "";
    while ((int)game_result[i] != 58/*58 => ASCII for :*/)
    {
        string_id[i-5] = game_result[i];
        i++;
    }
    game->id = atoi(string_id);
    //read pieces (red, green, blue)
    int set = 0;
    int num_color;
    while ((int)game_result[i] != 33/*33 => ASCII for !*/)
    {
        if ((int)game_result[i] == 59/*59 => ASCII for ;*/)
        {
            set++;
        }
        if ((int)game_result[i] == 44/*44 => ASCII for ,*/|| (int)game_result[i] == 58/*58 => ASCII for :*/|| (int)game_result[i] == 59/*59 => ASCII for ;*/)
        {
            i+=2;
            num_color = game_result[i]-48;
            i+=2;
            if (!strncmp(&game_result[i],"g",1))
            {
                game->green[set] = num_color;
            }
            if (!strncmp(&game_result[i],"b",1))
            {
                game->blue[set] = num_color;
            }
            if (!strncmp(&game_result[i],"r",1))
            {
                game->red[set] = num_color;
            }
        }
        i++;        
    }
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
void print_arr(int * arr,int n)
{
    for (int i = 0; i<n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}

int main()
{
    // char * game_result_1 ="Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green";
    char * game_result_2 ="Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue";
    // char * game_result_3 ="Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red";
    // char * game_result_4 ="Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red";
    // char * game_result_5 ="Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green";
    


    game_t * game1 = parse_game(game_result_2);
    int x = valid_game(game1);
    printf("game id: %d\n", game1->id);
    printf("green: ");
    print_arr(game1->green,5);
    printf("red: ");
    print_arr(game1->red,5);
    printf("blue: ");
    print_arr(game1->blue,5);
    printf("\n");
    printf("valid game id: %d\n",x);
    // printf("%c",32);
    // if (!0.2) {
    //     printf("1");

    // } else {
    //     printf("0");

    // }

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    int sum = 0;

    fp = fopen("../input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((getline(&line, &len, fp)) != -1) {
        game_t * game = parse_game(line);
        sum += valid_game(game);
    }

    fclose(fp);
    if (line)
        free(line);
    printf("sum: %d\n",sum);

    return 0;
}