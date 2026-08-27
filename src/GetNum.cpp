#include <cctype>

int GetNum(char * str){
    int finalvalue = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i])) {
            finalvalue = (finalvalue * 10) + (str[i] - '0');
        }
    }
    return finalvalue;
}