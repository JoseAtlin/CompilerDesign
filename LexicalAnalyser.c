#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

char delimiters[24] = {' ', '+', '-', '*', '/', ',', ';', '>', '<', '=', '(', ')', '[', ']', '{', '}', '\t', '\n', '|', '&', '%', '!', '^', '~'};
char operators[13] = {'+', '-', '*', '/', '>', '<', '=', '|', '&', '%', '!', '~', '^'};
char keywords[32][20] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", 
                        "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", 
                        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};

bool isDelimiter(char ch) {
	for (int i = 0; i < 24; i++)
       	if (ch == delimiters[i])
       		return (true);
    return (false);
}

bool isOperator(char ch) {
    for (int i = 0; i < 13; i++)
    	if (ch == operators[i])
	        return (true);
    return (false);
}

bool validIdentifier(char *str) {
     if (isdigit(str[0])  || isDelimiter(str[0]))
        return (false);
    return (true);
}

bool isKeyword(char *str) {
	for (int i = 0; i < 32; i++)
	    if (!strcmp(str, keywords[i])) 
    	    return (true); 
    return (false);
}

bool isInteger(char *str) {
    if (strlen(str) == 0)
        return (false);
    for (int i = 0; i < strlen(str); i++) {
    	if (!isdigit(str[i]))
    		return false;
    }
    return true;
}
  
bool isFloat(char *str) { 
    bool hasDecimal = false;

    if (strlen(str) == 0)
        return (false);
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i]) && str[i] != '.' ||  (str[i] == '-' && i > 0)) 
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}

bool isString(char *str) {
    if (strlen(str) == 0)
        return (false);
    if (str[0] == '"' && str[strlen(str) - 1] == '"')
        return (true);
    return false;
}

char* subString(char* str, int left, int right) { 
    char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));

    for (int i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    // printf("%s", subStr);  
    return (subStr);
} 
  
void parse(char* str) { 
    int left = 0, right = 0; 
    int len = strlen(str); 
  
    while (right <= len && left <= right) { 
        if (!isDelimiter(str[right])) 
            right++; 
  
        if (isDelimiter(str[right]) && left == right) {
            if (isOperator(str[right]) && isOperator(str[right+1]))
                printf("'%c%c' : OPERATOR\n", str[right], str[right+1]);
            else if (isOperator(str[right]) && str[right+1] == ' ' && str[right - 1] == ' ')
                printf("'%c' : OPERATOR\n", str[right]);
            else if (isOperator(str[right]) && isalpha(str[right+1]) && str[right - 1] == ' ')
                printf("'%c' : OPERATOR\n", str[right]);

            right++;
            left = right; 
        }
        else if (isDelimiter(str[right]) && left != right || (right == len && left != right)) {
            // printf("%c%c", str[right], str[right+2]);
            char *subStr = subString(str, left, right - 1);
            // printf("%s%c", subStr, str[right]);
  
            if (isKeyword(subStr))
                printf("'%s' : KEYWORD\n", subStr);
  
            else if (isInteger(subStr)) 
                printf("'%s' : INTEGER LITERAL\n", subStr); 
  
            else if (isFloat(subStr)) 
                printf("'%s' : FLOAT LITERAL\n", subStr);

            else if (isString(subStr))
                printf("'%s' : STRING LITERAL\n", subStr);
  
            else if (validIdentifier(subStr) && !isDelimiter(str[right - 1]))
                printf("'%s' : VALID IDENTIFIER\n", subStr);
  
            else if (!validIdentifier(subStr) && !isDelimiter(str[right - 1])) 
                printf("'%s' : NOT VALID IDENTIFIER\n", subStr); 

            left = right;
        }
    } 
    return; 
} 
  
int main() {
    char checker[255] = "";
    FILE *fp = fopen("LexicalAnalyser.txt", "r");
    int temp = 1;
    int flag = 0;
    while(fgets(checker, 255, fp) != NULL) {
        char buffer[255] = "";
        for (int i = 0; checker[i]; i++) {
            if (checker[i] == '*' && checker[i+1] == '/') {
                flag = 0;
                break;
            }
            if (checker[i] == '/' && checker[i+1] == '*') {
                flag = 1;
                break;
            }
            if (flag == 0) {
                if (checker[i] == '#' || (checker[i] == '/' && checker[i+1] == '/'))
                    break;
                buffer[i] = checker[i];
            }
        }
        // printf("%d ", strlen(buffer));
        // printf("%s", buffer);
        printf("LINE : %d\n", temp++);
        parse(buffer);   
        printf("\n");
    }
}