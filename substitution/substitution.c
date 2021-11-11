#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

char* encrptText(char *arg1, char *line);
void writeResult(char *result);
void outputResult(void);
void trimmedWord(char *src, char *dest);
bool keyhasDigits(char *arg1);
int keyHasDuplicateChars(char *arg1);
bool keyHasNoneAlphabets(char *arg1);
bool keyAllDigits(char *arg1);
//bool keyhasDigits(char *arg1);
bool keyIsValid(char *arg1);

int main (int argc, char *argv[])
{
    char *line = NULL;
    //ignored when line = NULL
    size_t len = 0;
    size_t read;

    //read = getline(&line, &len, stdin);
    //if ((read = getline (&line, &len, stdin)) != -1)
    //{
	if (argc == 2)
	{
	    /*
	    bool key_digits_only = keyAllDigits(argv[1]);
        bool key_none_alphabets = keyHasNoneAlphabets(argv[1]);
        int n_duplicate_chars = keyHasDuplicateChars(argv[1]);
        if (!key_digits_only || !key_none_alphabets)
        {
            printf("Usage: ./substitution key\n");
            exit(1);
        }
        */

	    int charslen = (int)strlen(argv[1]);
	    //printf("argv[charslen - 1]: %s\n", argv[charslen - 1]);
		//printf("*argv[charslen - 1]: %c\n", *argv[charslen - 1]);
		//printf("(*argv[charslen - 1] == '\n'): %d\n", (*argv[charslen - 1] == '\n'));
		if (*argv[charslen - 1] == '\n')
		{
			if ((charslen - 1) == 26)
			{
				//printf("charslen 0: %d\n", charslen);
				bool valid_key = keyIsValid(argv[1]);
				//printf("valid_key 0: %d\n", valid_key);
				if (valid_key)
				{
				    int n_duplicate_chars = keyHasDuplicateChars(argv[1]);
				    if (n_duplicate_chars > 0)
                    {
                        exit(1);
                    }
                    else
                    {
                        printf("plaintext: ");
				        if ((read = getline (&line, &len, stdin)) != -1)
                        {
                            char *ciphertext = encrptText(argv[1], line);
					        //printf("ciphertext output: %s\n", ciphertext);
					        //printf("\n");
                            int ciptextlen = (int)strlen(ciphertext);
					        char str[1024] = {'\0'};
					        char *src = "ciphertext: ";
					        int str_len = strlen(src);
					        for (int i = 0; i < str_len; i++)
					        {
						        char ch = src[i];

						        // append ch to str
						        strncat(str, &ch, 1);
					        }
					        for (int i = 0; i < ciptextlen; i++)
					        {
						        char ch1 = ciphertext[i];

						        // append ch to str
						        if (ch1 != '\n')
						        {
							        strncat(str, &ch1, 1);
						        }
					        }
					        int line_len = strlen(line);
					        //printf("line_len, ciptextlen: %d, %d\n", line_len, ciptextlen);
					        char dest[line_len + 1];
                            trimmedWord(str, dest);
                            //printf("dest: %s\n", dest);
                            if (access("ciphertext.txt", F_OK ))
                            {
                                int del = remove("ciphertext.txt");
                            }
					        writeResult(dest);
					        outputResult();
					        if (access("ciphertext.txt", F_OK ))
					        {
                                int del = remove("ciphertext.txt");
                            }
					        printf("\n");
                        }
                        else
                        {
                            exit(1);
                        }
                    }

				}
				else
				{
                    bool key_digits_only = keyAllDigits(argv[1]);
                    bool key_none_alphabets = keyHasNoneAlphabets(argv[1]);
                    //int n_duplicate_chars = keyHasDuplicateChars(argv[1]);
                    if (!key_digits_only || !key_none_alphabets)
                    {
                        printf("Usage: ./substitution key\n");
                        exit(1);
                    }
				}
			}
			else
			{
				printf("Key must contain 26 characters.\n");
				exit(1);
			}
		}
		else
		{
			if (charslen == 26)
			{
			    //printf("charslen 1: %d\n", charslen);
				bool valid_key = keyIsValid(argv[1]);
				//printf("valid_key 1: %d\n", valid_key);
				if (valid_key)
				{
				    int n_duplicate_chars = keyHasDuplicateChars(argv[1]);
				    //printf("n_duplicate_chars 1: %d\n", n_duplicate_chars);
				    if (n_duplicate_chars > 0)
                    {
                        exit(1);
                    }
                    else
                    {
                        printf("plaintext: ");
				        if ((read = getline (&line, &len, stdin)) != -1)
                        {
                            char *ciphertext = encrptText(argv[1], line);
					        //printf("ciphertext output: %s\n", ciphertext);
					        //printf("\n");
                            int ciptextlen = (int)strlen(ciphertext);
					        char str[1024] = {'\0'};
					        char *src = "ciphertext: ";
					        int str_len = strlen(src);
					        for (int i = 0; i < str_len; i++)
					        {
						        char ch = src[i];

						        // append ch to str
						        strncat(str, &ch, 1);
					        }
					        for (int i = 0; i < ciptextlen; i++)
					        {
						        char ch1 = ciphertext[i];

						        // append ch to str
						        if (ch1 != '\n')
						        {
							        strncat(str, &ch1, 1);
						        }
					        }
					        int line_len = strlen(line);
					        //printf("line_len, ciptextlen: %d, %d\n", line_len, ciptextlen);
					        char dest[line_len + 1];
                            trimmedWord(str, dest);
                            //printf("dest: %s\n", dest);
                            if (access("ciphertext.txt", F_OK ))
                            {
                                int del = remove("ciphertext.txt");
                            }
					        writeResult(dest);
					        outputResult();
					        if (access("ciphertext.txt", F_OK ))
					        {
                                int del = remove("ciphertext.txt");
                            }
					        printf("\n");
                        }
                        else
                        {
                            exit(1);
                        }
                    }

				}
				else
				{
                    bool key_digits_only = keyAllDigits(argv[1]);
                    bool key_none_alphabets = keyHasNoneAlphabets(argv[1]);
                    //int n_duplicate_chars = keyHasDuplicateChars(argv[1]);
                    if (!key_digits_only || !key_none_alphabets)
                    {
                        printf("Usage: ./substitution key\n");
                        exit(1);
                    }
				}
			}
			else
			{
				printf("Key must contain 26 characters.\n");
				exit(1);
			}
		}
	}
	else if (argc == 1)
	{
		printf("Usage: ./substitution key\n");
		exit(1);
	}

	printf("\n");
	//}
    return 0;
}

bool keyAllDigits(char *arg1)
{
    int length = (int)strlen(arg1);
    int n_digits = 0;
    bool flag = false;
    if (arg1[length - 1] == '\n')
    {
        for (int i = 0; i < length - 1; i++)
        {
            char ch = arg1[i];
            if (ch >= '0' && ch <= '9')
            {
                n_digits++;
            }
        }
        if (n_digits == (length - 1))
        {
            flag = true;
        }

    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            char ch = arg1[i];
            if (ch >= '0' && ch <= '9')
            {
                n_digits++;
            }
        }
        if (n_digits == length)
        {
            flag = true;
        }
    }
    return flag;
}

bool keyHasNoneAlphabets(char *arg1)
{
    int length = (int)strlen(arg1);
    int n_digits = 0;
    bool invald = false;
    if (arg1[length - 1] == '\n')
    {
        for (int i = 0; i < length - 1; i++)
        {
            char ch = arg1[i];
            if (!((ch >= 65) && (ch <= 90)))
            {
                invald = true;
            }
            else if (!((ch >= 97) && (ch <= 122)))
            {
                invald = true;
            }
        }
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            char ch = arg1[i];
            if (!((ch >= 65) && (ch <= 90)))
            {
                invald = true;
            }
            else if (!((ch >= 97) && (ch <= 122)))
            {
                invald = true;
            }
        }
    }
    return invald;
}

int keyHasDuplicateChars(char *arg1)
{
    int length = (int)strlen(arg1);
    char str[14] = {'\0'};
    if (arg1[length - 1] == '\n')
    {
        for (int i = 0; i < length - 1; i++)
        {
            char ch1 = arg1[i];
            int count = 0;
            for (int j = 0; j < length - 1; j++)
            {
                char ch2 = arg1[j];
                if (ch1 == ch2)
                {
                    count++;
                }
                int str_len = strlen(str);
                bool seen = false;
                for (int k = 0; k < str_len; k++)
                {
                    if (ch1 == str[k])
                    {
                        seen = true;
                        break;
                    }
                }
                if ((count > 1) && !seen)
                {
                    strncat(str, &ch1, 1);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            char ch1 = arg1[i];
            int count = 0;
            for (int j = 0; j < length; j++)
            {
                char ch2 = arg1[j];
                if (ch1 == ch2)
                {
                    count++;
                }
                int str_len = strlen(str);
                bool seen = false;
                for (int k = 0; k < str_len; k++)
                {
                    if (ch1 == str[k])
                    {
                        seen = true;
                        break;
                    }
                }
                if ((count > 1) && !seen)
                {
                    strncat(str, &ch1, 1);
                }
            }
        }
    }
    int str_length = strlen(str);
    int n_dupchars = 0;
    //printf("keyHasDuplicateChars -> str: %s\n", str);
    for (int k = 0; k < str_length; k++)
    {
        char ch1 = str[k];
        if ((str[k] != '\0') && (str[k] != '\n'))
        {
            n_dupchars++;
        }
    }
    return n_dupchars;
}

bool keyIsValid(char *arg1)
{
    int length = (int)strlen(arg1);
    bool valid = true;
    if (arg1[length - 1] == '\n')
    {
        for (int i = 0; i < length - 1; i++)
        {
            char ch = arg1[i];
            if (!((ch >= 65) && (ch <= 90)) && !((ch >= 97) && (ch <= 122)))
            {
                valid = false;
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            char ch = arg1[i];
            if (!((ch >= 65) && (ch <= 90)) && !((ch >= 97) && (ch <= 122)))
            {
                valid = false;
                break;
            }
        }
    }
    return valid;
}

char* encrptText(char *arg1, char *line)
{
    int length = (int)strlen(line);

    // declare and initialize string
    char str[1024] = {'\0'};
    char ucaseAlphabets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
    int length2 = (int)strlen(ucaseAlphabets);

    if (line[length - 1] == '\n')
    {
        for (int i = 0; i < length - 1; i++)
        {
            if ((line[i] >= 65) && (line[i] <= 90))
            {
                //char ch = toupper(line[i]);
                char ch = line[i];

                if (ucaseAlphabets[length2 - 1] == '\n')
                {
                    for (int j = 0; j < length2 - 1; j++)
                    {
                        if (ch == ucaseAlphabets[j])
                        {
                            char ch1 = toupper(arg1[j]);
                            strncat(str, &ch1, 1);
                        }
                    }
                }
            }
            else if ((line[i] >= 97) && (line[i] <= 122))
            {
                char ch = toupper(line[i]);

                if (ucaseAlphabets[length2 - 1] == '\n')
                {
                    for (int j = 0; j < length2 - 1; j++)
                    {
                        if (ch == ucaseAlphabets[j])
                        {
                            char ch1 = tolower(arg1[j]);
                            strncat(str, &ch1, 1);
                        }
                    }
                }
            }
            else if (((line[i] >= 32) && (line[i] <= 64)) || ((line[i] >= 91) && (line[i] <= 96)) || ((line[i] >= 123) && (line[i] <= 126)))
            {
                char non_alphabet = line[i];
                strncat(str, &non_alphabet, 1);
            }
        }
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            if ((line[i] >= 65) && (line[i] <= 90))
            {
                //char ch = toupper(line[i]);
                char ch = line[i];

                if (ucaseAlphabets[length2 - 1] == '\n')
                {
                    for (int j = 0; j < length2 - 1; j++)
                    {
                        if (ch == ucaseAlphabets[j])
                        {
                            char ch1 = toupper(arg1[j]);
                            strncat(str, &ch1, 1);
                        }
                    }
                }
            }
            else if ((line[i] >= 97) && (line[i] <= 122))
            {
                char ch = toupper(line[i]);

                if (ucaseAlphabets[length2 - 1] == '\n')
                {
                    for (int j = 0; j < length2 - 1; j++)
                    {
                        if (ch == ucaseAlphabets[j])
                        {
                            char ch1 = tolower(arg1[j]);
                            strncat(str, &ch1, 1);
                        }
                    }
                }
            }
            else if (((line[i] >= 32) && (line[i] <= 64)) || ((line[i] >= 91) && (line[i] <= 96)) || ((line[i] >= 123) && (line[i] <= 126)))
            {
                char non_alphabet = line[i];
                strncat(str, &non_alphabet, 1);
            }
        }
    }
    char *pstr = str;
    return pstr;
}

void writeResult(char *result)
{
    // creating file pointer to work with files
    FILE *fptr;

    // opening file in writing mode
    fptr = fopen("ciphertext.txt", "w");

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

    fp = fopen("ciphertext.txt", "r");
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

void trimmedWord(char *src, char *dest)
{
    if (!src || !dest)
       return;

    int len = strlen (src);

    if (!len)
    {
        *dest = '\0';
        return;
    }
    char *ptr = src + len - 1;

    // remove trailing whitespace
    while (ptr > src)
    {
		int c = (int)*ptr;
        if (!isspace (c))
            break;
        ptr--;
    }

    ptr++;

    char *q;
    // remove leading whitespace

    for (q = src; (q < ptr && isspace ((int)*q)); q++)
        ;

    while (q < ptr)
        *dest++ = *q++;

    *dest = '\0';
}