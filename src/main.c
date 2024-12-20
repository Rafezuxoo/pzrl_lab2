#include "lib2.h"

int main(int argc, char *argv[]) {
    if (argc > 3) {
        fprintf(stderr, "too many args\n");
        exit(1);
    } 

    if (argc < 3) {
        fprintf(stderr, "too few args\n");
        exit(1);
    }

    isFileExist(argv[1]);

    getCmd(argv);

    return 0;
}
