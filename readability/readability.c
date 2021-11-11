#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

int computeIndex(char *line);
int numberOfWords(char *line);
int numberOfSentences(char *line);
int numberOfLetters(char *line);
void writeResult(char *result);
void outputResult(void);

int main(int argc, char *argv[])
{

    //forces getline to allocate with malloc
    char *line = NULL;
    //ignored when line = NULL
    size_t len = 0;
    size_t read;

    /*
    //Generously large value for most situations
    char line[1024];
    char *eof;
    //Ensure empty line if no input delivered
    line[0] = '\0';
    //Ensure no false-null at end of buffer
    line[sizeof(line)-1] = ~'\0';

    printf ("Text: ");
    eof = fgets(line, sizeof(line), stdin);
    */

    printf("Text: ");
    read = getline(&line, &len, stdin);

    int index = computeIndex(line);
    if (index < 1)
    {
        char str[15] = {'\0'};
        char *src = "Before Grade 1";
        int str_len = strlen(src);
        for (int i = 0; i < str_len; i++)
        {
            char ch = src[i];

            // append ch to str
            strncat(str, &ch, 1);
        }

        writeResult(str);
        outputResult();
        int del = remove("grade.txt");
    }
    else if (index >= 16)
    {
        char str[10] = {'\0'};
        char *src = "Grade 16+";
        int str_len = strlen(src);
        for (int i = 0; i < str_len; i++)
        {
            char ch = src[i];

            // append ch to str
            strncat(str, &ch, 1);
        }

        writeResult(str);
        outputResult();
        int del = remove("grade.txt");
    }
    else
    {
        if ((index >= 1) && (index <= 9))
        {
            char str[10] = {'\0'};
            char *src = "Grade ";
            int str_len = strlen(src);
            for (int i = 0; i < str_len; i++)
            {
                char ch = src[i];

                // append ch to str
                strncat(str, &ch, 1);
            }
            char index_str[2];
            sprintf(index_str, "%d", index);

            str_len = strlen(index_str);
            for (int i = 0; i < str_len; i++)
            {
                char ch = index_str[i];

                // append ch to str
                if ((ch >= '1') && (ch <= '9'))
                {
                    strncat(str, &ch, 1);
                }
            }

            writeResult(str);
            outputResult();
            int del = remove("grade.txt");
        }
        else if ((index >= 10) && (index <= 15))
        {
            char str[10] = {'\0'};
            char *src = "Grade ";
            int str_len = strlen(src);
            for (int i = 0; i < str_len; i++)
            {
                char ch = src[i];

                // append ch to str
                strncat(str, &ch, 1);
            }
            char index_str[3];
            sprintf(index_str, "%d", index);
            str_len = strlen(index_str);
            for (int i = 0; i < str_len; i++)
            {
                char ch = index_str[i];

                // append ch to str
                if ((ch >= '0') && (ch <= '9'))
                {
                    strncat(str, &ch, 1);
                }
            }

            writeResult(str);
            outputResult();
            int del = remove("grade.txt");
        }
    }
    printf("\n");


    // free memory allocated by getline
    free(line);

    return 0;
}

int numberOfLetters(char *line)
{
    int length = (int)strlen(line);
    int chnum = 0;

    if (line[length - 1] == '\n')
    {
        for (int i = 0; i < length - 1; i++)
        {
            char ch = line[i];
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
            {
                chnum += 1;
            }
        }
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            char ch = line[i];
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
            {
                chnum += 1;
            }
        }
    }

    return chnum;
}

int numberOfSentences(char *line)
{
    int length = (int)strlen(line);
    int chnum = 0;
    if (line[length - 1] == '\n')
    {
        for (int i = 0; i < length - 1; i++)
        {
            char ch = line[i];
            if (ch == '.' || ch == '?' || ch == '!')
            {
                chnum += 1;
            }
        }
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            char ch = line[i];
            if (ch == '.' || ch == '?' || ch == '!')
            {
                chnum += 1;
            }
        }
    }

    return chnum;
}

int numberOfWords(char *line)
{
    int length = (int)strlen(line);
    int chnum = 0;
    if (line[length - 1] == '\n')
    {
        for (int i = 0; i < length - 1; i++)
        {
            char ch = line[i];
            if (ch == ' ')
            {
                chnum += 1;
            }
        }
        chnum += 1;
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            char ch = line[i];
            if (ch == ' ')
            {
                chnum += 1;
            }
        }
        chnum += 1;
    }

    return chnum;
}

int computeIndex(char *line)
{
    int num_of_letters = numberOfLetters(line);
    int num_of_words = numberOfWords(line);
    int num_of_sentences = numberOfSentences(line);
    float L = ((float)num_of_letters / (float)num_of_words) * 100;
    float S = ((float)num_of_sentences / (float)num_of_words) * 100;
    int index = (int)(round(0.0588 * L - 0.296 * S - 15.8));
    return index;
}

void writeResult(char *result)
{
    // creating file pointer to work with files
    FILE *fptr;

    // opening file in writing mode
    fptr = fopen("grade.txt", "w");

    // exiting program
    if (fptr == NULL)
    {
        printf("Error!");
        return;
    }

    fprintf(fptr, "%s", result);
    fclose(fptr);
}

void outputResult(void)
{
    FILE *fp;
    int ch;

    fp = fopen("grade.txt", "r");
    if (fp == NULL)
    {
        printf("Error in file opening...\n");
        return;
    }

    //here we are using infinite loop to print value of
    //EOF, loop will be terminate as we got EOF
    while (1)
    {
        //read one character
        ch = getc(fp);

        if (ch == EOF)
        {
            //terminate loop
            break;
        }
        printf("%c", ch);
    }

    //close the file
    fclose(fp);
}