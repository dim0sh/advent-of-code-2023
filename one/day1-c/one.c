#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int str_len(char * str)
{
    int i = 0;
    while (str[i++]);
    return i;
}
char norm_numbs[9][10] = {"one","two","three","four","five","six","seven","eight","nine"};
char back_numbs[9][10] = {"eno","owt","eerht","ruof","evif","xis","neves","thgie","enin"};
int contains_string_num(char * str, int backwards)
{   
    char (* numbs)[10];
    if (backwards) {
        numbs = back_numbs;
    } else {
        numbs = norm_numbs;
    }

    for (int i = 0; i<9; i++)
    {
        if (strncmp(str,&numbs[i][0],str_len(&numbs[i][0])-1) == 0)
        {
            return i+1;
        }

    }
    return 0;
}

int search_str_int(char * str, int backwards)
{
    int current_int = 0;
    for (int i = 0; i<str_len(str)-1;i++)
    {
        current_int = (int)str[i]-48;
        if (current_int <= 9 &&  current_int >0) {
            return current_int;
        }
        current_int = contains_string_num(&str[i],backwards);
        if (current_int)
        {
            return current_int;
        } 

    }    
}
int search_str(char * str)
{
    char * strcp = (char *) malloc(str_len(str)*sizeof(char));
    strcpy_s(strcp,str_len(str)*sizeof(char),str);
    int x, y = 0;
    x = search_str_int(str,0);
    _strrev(strcp);
    y = search_str_int(strcp,1);
    free(strcp);
    return x*10+y;
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
    // char * str1 = "1abc2";
    // char * str2 = "pqr3stu8vwx";
    // char * str3 = "a1b2c3d4e5f";
    char * str4 = "treb7uchet";
    // char * str5 = "kqrcrq723";
    char * str_test = "asdadsoneeight3434";
    clock_t t ;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    int sum = 0;
    t = clock();
    fp = fopen("../input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((getline(&line, &len, fp)) != -1) {
        sum += search_str(line);
    }

    fclose(fp);
    if (line)
        free(line);
    printf("sum:%d\n",sum);
    int sum_test = 0;
    
    
    for (int i = 0; i<str_len(str_test);i++)
    {
        sum_test += contains_string_num(&str_test[i],0);
    }
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("took %f seconds to execute \n", time_taken);
    printf("%d\n",CLOCKS_PER_SEC);
    printf("sum_test:%d\n",sum_test);
    printf("search_test:%d\n",search_str(str4));
}