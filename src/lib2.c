#include "lib2.h"

void checkOperationInput(const char *str) {
    const size_t exCount = 4;
    char *examples[exCount]; 
    examples[0] = "s/old_text_regex/new_text/";
    examples[1] = "/regex/d";
    examples[2] = "s/^/prefix/";
    examples[3] = "s/$/suffix/";
    
    regex_t regex;
    int reti;

    for (size_t i = 0; i < exCount; ++i) {
        reti = regcomp(&regex, examples[i], REG_EXTENDED);
        if (reti) {
            printf("Could not compiled regex\n");
            exit(1);
        }
    }
}

