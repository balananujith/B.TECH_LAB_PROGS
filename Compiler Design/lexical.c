#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// Checks if the character is a delimiter
bool isDelimiter(char ch) {
    return strchr(" +-*/><=()[]{};,", ch) != NULL;
}

// Checks if the character is an operator
bool isOperator(char ch) {
    return strchr("+-*/><=", ch) != NULL;
}

// Checks if the string is a valid identifier
bool validIdentifier(char* str) {
    return !(isdigit(str[0]) || isDelimiter(str[0]));
}

// Checks if the string is a keyword
bool isKeyword(char* str) {
    const char* keywords[] = {"if", "else", "while", "do", "break", "continue", "int", "double", "float", "return", "char", "case", "sizeof", "long", "short", "typedef", "switch", "unsigned", "void", "static", "struct", "goto"};
    int keywordCount = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < keywordCount; ++i)
        if (strcmp(str, keywords[i]) == 0)
            return true;
    return false;
}

// Checks if the string is an integer
bool isInteger(char* str) {
    for (int i = 0; str[i] != '\0'; ++i)
        if (!isdigit(str[i]) && !(str[i] == '-' && i == 0))
            return false;
    return true;
}

// Checks if the string is a real number
bool isRealNumber(char* str) {
    bool hasDecimal = false;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == '.') {
            if (hasDecimal) return false;
            hasDecimal = true;
        } else if (!isdigit(str[i]) && !(str[i] == '-' && i == 0)) {
            return false;
        }
    }
    return hasDecimal;
}

// Extracts a substring
char* subString(char* str, int left, int right) {
    char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));
    strncpy(subStr, &str[left], right - left + 1);
    subStr[right - left + 1] = '\0';
    return subStr;
}

// Parses the input string
void parse(char* str) {
    int left = 0, right = 0, len = strlen(str);

    while (right <= len) {
        if (!isDelimiter(str[right])) {
            right++;
        } else {
            if (left != right) {
                char* subStr = subString(str, left, right - 1);
                if (isKeyword(subStr))
                    printf("'%s' IS A KEYWORD\n", subStr);
                else if (isInteger(subStr))
                    printf("'%s' IS AN INTEGER\n", subStr);
                else if (isRealNumber(subStr))
                    printf("'%s' IS A REAL NUMBER\n", subStr);
                else if (validIdentifier(subStr))
                    printf("'%s' IS A VALID IDENTIFIER\n", subStr);
                else
                    printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
                free(subStr);
            }
            if (isOperator(str[right]))
                printf("'%c' IS AN OPERATOR\n", str[right]);
            else if (str[right] != ' ')
                printf("'%c' IS A DELIMITER\n", str[right]);
            right++;
            left = right;
        }
    }
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    str[strcspn(str, "\n")] = '\0'; // Remove newline character
    parse(str);
    return 0;
}
