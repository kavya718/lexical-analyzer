#include <stdio.h>      // Standard input-output header
#include <ctype.h>      // Character handling functions
#include <string.h>     // String handling functions
#include "lexer.h"      // Lexical analyzer header file

// List of C keywords
const char *keywords[] = {
    "int","char","float","double","if","else","for","while",
    "do","return","break","continue","void","long","short",
    "signed","unsigned","switch","case","default","struct",
    "union","typedef","static","const","enum","extern","goto",
    "sizeof","volatile","register"
};

// Function to check whether a string is a keyword
int isKeyword(char *str)
{
    int n = sizeof(keywords) / sizeof(keywords[0]); // Number of keywords
    for (int i = 0; i < n; i++)
        if (strcmp(str, keywords[i]) == 0)
            return 1;       // Keyword found
    return 0;               // Not a keyword
}

// Function to check symbols/operators
int isSymbol(char ch)
{
    return strchr("+-*/=%<>!()", ch) != NULL;
}

// Function to check special characters
int isSpecialChar(char ch)
{
    return strchr("{}[];,", ch) != NULL;
}

// Main lexical analysis function
void analyzeFile(char *filename)
{
    FILE *fp = fopen(filename, "r"); // Open source file
    char buffer[100];                // Buffer to store tokens
    int c, i, line = 1;              // Character, index, line counter
    int paren = 0, brace = 0;        // Counters for () and {}

    // Check if file exists
    if (!fp)
    {
        printf("File not found\n");
        return;
    }

    // Print file status
    printf("%s is present\n\n", filename);

    // Read file character by character
    while ((c = fgetc(fp)) != EOF)
    {
        // Increment line number
        if (c == '\n')
            line++;

        // Skip whitespace characters
        if (isspace(c))
            continue;

        // Ignore preprocessor directives
        if (c == '#')
        {
            while ((c = fgetc(fp)) != EOF && c != '\n');
            line++;
            continue;
        }

        // Track opening and closing brackets
        if (c == '(') paren++;
        if (c == ')') paren--;
        if (c == '{') brace++;
        if (c == '}') brace--;

        // Identifier or keyword detection
        if (isalpha(c) || c == '_')
        {
            i = 0;
            buffer[i++] = c;

            while ((c = fgetc(fp)) != EOF && (isalnum(c) || c == '_'))
                buffer[i++] = c;

            buffer[i] = '\0';
            if (c != EOF)
                ungetc(c, fp);

            // Print keyword or identifier
            if (isKeyword(buffer))
                printf("KEYWORD      : %s\n", buffer);
            else
                printf("IDENTIFIER   : %s\n", buffer);
        }

        // Numeric constant handling
        else if (isdigit(c))
        {
            int dot_count = 0;    // To detect floating numbers
            i = 0;
            buffer[i++] = c;

            while ((c = fgetc(fp)) != EOF && (isdigit(c) || c == '.'))
            {
                if (c == '.')
                    dot_count++;
                buffer[i++] = c;
            }

            buffer[i] = '\0';
            if (c != EOF)
                ungetc(c, fp);

            // Print numeric constant
            printf("NUMERIC CONST: %s\n", buffer);

            // Invalid floating constant check
            if (dot_count == 1)
            {
                for (int j = 0; buffer[j]; j++)
                {
                    if (!(isdigit(buffer[j]) || buffer[j] == '.'))
                    {
                        printf("\nLINE NO : %d\n", line);
                        printf("ERROR   : invalid suffix on floating constant\n");
                        fclose(fp);
                        return;
                    }
                }
            }

            // Hexadecimal constant validation
            if (strncmp(buffer, "0x", 2) == 0 || strncmp(buffer, "0X", 2) == 0)
            {
                for (int j = 2; buffer[j]; j++)
                {
                    if (!isxdigit(buffer[j]))
                    {
                        printf("\nLINE NO : %d\n", line);
                        printf("ERROR   : invalid suffix on integer constant\n");
                        fclose(fp);
                        return;
                    }
                }
            }

            // Binary constant validation
            if (strncmp(buffer, "0b", 2) == 0 || strncmp(buffer, "0B", 2) == 0)
            {
                for (int j = 2; buffer[j]; j++)
                {
                    if (buffer[j] != '0' && buffer[j] != '1')
                    {
                        printf("\nLINE NO : %d\n", line);
                        printf("ERROR   : invalid digit in binary constant\n");
                        fclose(fp);
                        return;
                    }
                }
            }

            // Octal constant validation
            if (buffer[0] == '0' && buffer[1] != 'x' && buffer[1] != 'X'
                && buffer[1] != 'b' && buffer[1] != 'B'
                && dot_count == 0)
            {
                for (int j = 1; buffer[j]; j++)
                {
                    if (buffer[j] < '0' || buffer[j] > '7')
                    {
                        printf("\nLINE NO : %d\n", line);
                        printf("ERROR   : invalid digit in octal constant\n");
                        fclose(fp);
                        return;
                    }
                }
            }
        }

        // String literal handling
        else if (c == '"')
        {
            while ((c = fgetc(fp)) != EOF && c != '"')
            {
                if (c == '\n')
                {
                    printf("\nLINE NO : %d\n", line);
                    printf("ERROR   : missing terminating \" character\n");
                    fclose(fp);
                    return;
                }
            }
        }

        // Symbol detection
        else if (isSymbol(c))
        {
            int next = fgetc(fp);
            if ((c == '+' && next == '+') || (c == '-' && next == '-'))
                printf("SYMBOL       : %c%c\n", c, next);
            else
            {
                printf("SYMBOL       : %c\n", c);
                if (next != EOF)
                    ungetc(next, fp);
            }
        }

        // Special character detection
        else if (isSpecialChar(c))
        {
            printf("SPEC CHAR    : %c\n", c);
        }
    }

    // Check for unclosed brackets
    if (paren > 0)
        printf("\nERROR   : missing closing )\n");
    else if (brace > 0)
        printf("\nERROR   : missing closing }\n");

    fclose(fp);  // Close file
}


