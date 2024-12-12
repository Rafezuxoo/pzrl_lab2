#include "lib2.h"

int main(int argc, char *argv[]) {

    char flag;
    checkOperationInput(argv[1]);

    FILE *file = fopen(argv[1], "a+");
    
    if (file == NULL) {
        printf("File does not exist\n");
        exit(1);
    }

    fprintf(file, "hello, wrld!\n");

    fclose(file);
    return 0;
}
