#include "stdio.h"

int main(int argc, char **argv) {
        if (argc < 2) { return -2; }
        printf("%s\n", argv[1]);
        return 2;
}
