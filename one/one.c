#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int str_len(char * str)
{
    int i = 0;
    while (str[i++]);
    return i;
}

int search_str_int(char * str)
{
    int x;
    for (int i = 0; i<str_len(str)-1;i++)
    {
        switch (atoi(&str[i]))
        {
        case 1:
            x = 1;
            return x;
        case 2:
            x = 2;
            return x;
        case 3:
            x = 3;
            return x;
        case 4:
            x = 4;
            return x;
        case 5:
            x = 5;
            return x;
        case 6:
            x = 6;
            return x;
        case 7:
            x = 7;
            return x;
        case 8:
            x = 8;
            return x;
        case 9:
            x = 9;
            return x;
        case 0:
            if (strcmp(&str[i], "0")!=0) {
                break;
            }
            x = 0;
            return x;
        default:
            break;
        }
    }    
    return -1;
}
int search_str(char * str)
{
    char * strcp = (char *) malloc(str_len(str)*sizeof(char));
    strcpy_s(strcp,str_len(str)*sizeof(char),str);
    int x, y = 0;
    x = search_str_int(str);
    _strrev(strcp);
    y = search_str_int(strcp);
    return x*10+y;
}

int main()
{
    char * str1 = "1abc2";
    char * str2 = "pqr3stu8vwx";
    char * str3 = "a1b2c3d4e5f";
    char * str4 = "treb7uchet";
    char * str5 = "2akhsd0alsj";
    
    printf("x:%d\n",search_str(str3));
}