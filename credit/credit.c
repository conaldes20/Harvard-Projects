#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#define AMEX "AMEX\n"
#define MASTERCARD "MASTERCARD\n"
#define VISA "VISA\n"
#define INVALID "INVALID\n"

void cardValiditiy(char *line);
void trim(char *str);
char *buildString(char *line);
char *concat(int count, ...);
int luhnAlgorithm(char *line);
int sumDigitsX2(char *line);
int sumDigitsOthers(char *line);
int checkFirstdAndSeconDigits(char *line);
int checkNumberOfDigits(char *line);

int main(int argc, char *argv[])
{

    char *line = NULL;  /* forces getline to allocate with malloc */
    size_t len = 0;     /* ignored when line = NULL */
    size_t read = 0;

    printf("\nEnter card number [ctrl + d] to quit\n");

    do
    {
        //printf ("\nEnter card number [ctrl + d] to quit\n");
        read = getline(&line, &len, stdin);
        cardValiditiy(line);
        printf("\nEnter card number [ctrl + d] to quit\n");
        //if (read == -1){
        //    read = 0;
        //    printf ("\nRe-Enter card number [ctrl + d] to quit\n");
        //}
    }
    while (read >= 0);
    free(line); /* free memory allocated by getline */
    return 0;
}

void cardValiditiy(char *line)
{
    //char* newstr = buildString(line);
    int numdigits = checkNumberOfDigits(line);
    //printf("Number of digits: %d\n", numdigits);
    if (numdigits == 13 || numdigits == 15 || numdigits == 16)
    {
        int statusCode = checkFirstdAndSeconDigits(line);
        //printf("statusCode: %d\n", statusCode);
        if (statusCode == 111 || statusCode == 112 || statusCode == 113)
        {
            int remainder = luhnAlgorithm(line);
            //printf("remainder: %d\n", remainder);
            if (remainder == 0 && statusCode == 111)
            {
                printf(AMEX);
            }
            else if (remainder == 0 && statusCode == 112)
            {
                printf(MASTERCARD);
            }
            else if (remainder == 0 && statusCode == 113)
            {
                printf(VISA);
            }
            else
            {
                printf(INVALID);
            }
        }
        else
        {
            printf("Number: %s\n", line);
            printf(INVALID);
        }
    }
    else
    {
        printf("Number: %s\n", line);
        printf(INVALID);
    }
}

int lookForSpaceOrLetter(char *line)
{
    int length = (int)strlen(line);
    int flag = 1;
    if (line[length - 1] == '\n')
    {
        for (int i = 0; i < length - 1; i++)
        {
            char ch = line[i];
            if (ch < '0' || ch > '9') // if(ch >= 48 && ch <= 57) { Using ASCII value
            {
                flag = -1;
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            char ch = line[i];
            if (ch < '0' || ch > '9')
            {
                flag = -1;
                break;
            }
        }
    }
    return flag;
}

void trim(char *str)
{
    int index, i;

    /*
     * Trim leading white spaces
     */
    index = 0;
    while (str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
    {
        index++;
    }

    /* Shift all trailing characters to its left */
    i = 0;
    while (str[i + index] != '\0')
    {
        str[i] = str[i + index];
        i++;
    }
    str[i] = '\0'; // Terminate string with NULL


    /*
     * Trim trailing white spaces
     */
    i = 0;
    index = -1;
    while (str[i] != '\0')
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index = i;
        }
        i++;
    }

    /* Mark the next character to last non white space character as NULL */
    str[index + 1] = '\0';
}

char *buildString(char *line)
{
    /*char *line = "hello, world";
    char *buffer = ( char * ) malloc( strlen( line ) + 1 );

    buffer[0] = '\0';
    char *p = Buffer;

    for ( size_t i = 0; i < strlen( line ); i++ ) {
      *p++ = line[i];
      *p = '\0';
    }
    */

    // declare and initialize string
    char *str = " ";

    for (size_t i = 0; i < strlen(line); i++)
    {
        char ch = line[i];
        //if(ch != ' ' && ch != '-' && ch != '\n') {
        if (ch >= '0' && ch <= '9')
        {
            // append ch to str
            strncat(str, &ch, 1);
        }
    }
    return str;
}

char *concat(int count, ...)
{
    va_list ap;
    int i;

    // Find required length to store merged string
    int len = 1; // room for NULL
    va_start(ap, count);
    for (i = 0; i < count; i++)
    {
        len += strlen(va_arg(ap, char *));
    }
    va_end(ap);

    // Allocate memory to concat strings
    char *merged = calloc(sizeof(char), len);
    int null_pos = 0;

    // Actually concatenate strings
    va_start(ap, count);
    for (i = 0; i < count; i++)
    {
        char *s = va_arg(ap, char *);
        strcpy(merged + null_pos, s);
        null_pos += strlen(s);
    }
    va_end(ap);
    return merged;
}

int luhnAlgorithm(char *line)
{
    char *str = "";
    int length = (int)strlen(line);
    //printf("(luhnAlgorithm) length: %d\n", length);
    //printf("(luhnAlgorithm) length - 1: %d\n", (length - 1));

    int modulus2 = (length - 1) % 2;
    if (modulus2 != 0)
    {
        if (line[length - 1] == '\n')
        {
            for (int i = length - 3; i > 0; i = i - 2)
            {
                char digitstr[2] = {line[i], '\0'};
                int num = atoi(digitstr);       //line[i] - '0';
                //printf("(luhnAlgorithm) atoi(digitstr): %d\n", num);
                int res = num * 2;
                int str_len = snprintf(NULL, 0, "%d", res);
                char *nstr = malloc(str_len + 1);
                snprintf(nstr, str_len + 1, "%d", res);
                //printf("(luhnAlgorithm) nstr: %s\n", nstr);
                str = concat(2, str, nstr);
                free(nstr);
                // printf("(luhnAlgorithm) str: %s\n", str);
            }
        }
        else
        {
            for (int i = length - 2; i > 0; i = i - 2)
            {
                char digitstr[2] = {line[i], '\0'};
                int num = atoi(digitstr);       //line[i] - '0';
                //printf("(luhnAlgorithm) atoi(digitstr): %d\n", num);
                int res = num * 2;
                int str_len = snprintf(NULL, 0, "%d", res);
                char *nstr = malloc(str_len + 1);
                snprintf(nstr, str_len + 1, "%d", res);
                //printf("(luhnAlgorithm) nstr: %s\n", nstr);
                str = concat(2, str, nstr);
                free(nstr);
                //printf("(luhnAlgorithm) str: %s\n", str);
            }
        }
    }
    else if (modulus2 == 0)
    {
        if (line[length - 1] == '\n')
        {
            for (int i = length - 3; i >= 0; i = i - 2)
            {
                char digitstr[2] = {line[i], '\0'};
                int num = atoi(digitstr);       //line[i] - '0';
                //printf("(luhnAlgorithm) atoi(digitstr): %d\n", num);
                int res = num * 2;
                int str_len = snprintf(NULL, 0, "%d", res);
                char  *nstr = malloc(str_len + 1);
                snprintf(nstr, str_len + 1, "%d", res);
                //printf("(luhnAlgorithm) nstr: %s\n", nstr);
                str = concat(2, str, nstr);
                free(nstr);
                //printf("(luhnAlgorithm) str: %s\n", str);
            }
        }
        else
        {
            for (int i = length - 2; i >= 0; i = i - 2)
            {
                char digitstr[2] = {line[i], '\0'};
                int num = atoi(digitstr);       //line[i] - '0';
                //printf("(luhnAlgorithm) atoi(digitstr): %d\n", num);
                int res = num * 2;
                int str_len = snprintf(NULL, 0, "%d", res);
                char *nstr = malloc(str_len + 1);
                snprintf(nstr, str_len + 1, "%d", res);
                //printf("(luhnAlgorithm) nstr: %s\n", nstr);
                str = concat(2, str, nstr);
                free(nstr);
                //printf("(luhnAlgorithm) str: %s\n", str);
            }
        }
    }
    //trim(str)
    int sum1 = sumDigitsX2(str);
    //printf("sum1: %d\n", sum1);
    free(str);
    int sum2 = sumDigitsOthers(line);
    //printf("sum2: %d\n", sum2);
    int remainder = (sum1 + sum2) % 10;
    return remainder;
}

int sumDigitsX2(char *line)
{
    int sum = 0;
    int length = (int)strlen(line);
    if (line[length - 1] == '\n')
    {
        for (int i = 0; i < length - 1; i++)
        {
            //char ch = line[i];
            //if(ch >= '0' && ch <= '9') {
            int num = line[i] - '0';        //atoi(line[i]);
            sum = sum + num;
            //}
        }
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            //char ch = line[i];
            //if(ch >= '0' && ch <= '9') {
            int num = line[i] - '0';    //atoi(line[i]);
            sum = sum + num;
            //}
        }
    }
    return sum;
}

int sumDigitsOthers(char *line)
{
    int sum = 0;
    int length = (int)strlen(line);
    int modulus2 = (length - 1) % 2;
    if (modulus2 != 0)
    {
        if (line[length - 1] == '\n')
        {
            for (int i = length - 2; i >= 0; i = i - 2)
            {
                //char ch = line[i];
                //if(ch >= '0' && ch <= '9') {
                // if(ch >= 48 && ch <= 57) { Using ASCII value
                int num = line[i] - '0';    //atoi(line[i]);
                //printf("i: %d num: %d\n", i, num);
                sum = sum + num;
                //}
            }
        }
        else
        {
            for (int i = length - 1; i >= 0; i = i - 2)
            {
                //char ch = line[i];
                //if(ch >= '0' && ch <= '9') {
                // if(ch >= 48 && ch <= 57) { Using ASCII value
                int num = line[i] - '0';    //atoi(line[i]);
                sum = sum + num;
                //}
            }
        }
    }
    else if (modulus2 == 0)
    {
        if (line[length - 1] == '\n')
        {
            for (int i = length - 2; i > 0; i = i - 2)
            {
                //char ch = line[i];
                //if(ch >= '0' && ch <= '9') {
                // if(ch >= 48 && ch <= 57) { Using ASCII value
                int num = line[i] - '0';    //atoi(line[i]);
                //printf("i: %d num: %d\n", i, num);
                sum = sum + num;
                //}
            }
        }
        else
        {
            for (int i = length - 1; i > 0; i = i - 2)
            {
                //char ch = line[i];
                //if(ch >= '0' && ch <= '9') {
                // if(ch >= 48 && ch <= 57) { Using ASCII value
                int num = line[i] - '0';    //atoi(line[i]);
                sum = sum + num;
                //}
            }
        }
    }
    return sum;
}

int checkFirstdAndSeconDigits(char *line)
{
    int length = (int)strlen(line);
    int first = 0;
    int second = 0;
    for (int i = 0; i < length; i++)
    {
        if (i == 0)
        {
            first = line[i] - '0';  //atoi(line[i]);
        }
        if (i == 1)
        {
            second = line[i] - '0'; //atoi(line[i]);
        }
    }
    if ((first == 3) && (second == 4 || second == 7))
    {
        return 111;
    }
    else if ((first == 5) && (second == 1 || second == 2 || second == 3 || second == 4 || second == 5))
    {
        return 112;
    }
    else if (first == 4)
    {
        return 113;
    }
    else
    {
        return -1;
    }
}

int checkNumberOfDigits(char *line)
{
    int count = 0;
    int length = (int)strlen(line);
    if (line[length - 1] == '\n')
    {
        for (int i = 0; i < length - 1; i++)
        {
            char ch = line[i];
            if(ch >= '0' && ch <= '9') {
                count++;
            }
        }
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            char ch = line[i];
            if(ch >= '0' && ch <= '9') {
                count++;
            }
        }
    }
    return count;
}
