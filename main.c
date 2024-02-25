#include "header.h"

int main(int argc, char** argv) {
    if (strcmp(argv[1], "-c1") == 0) {
        task1(argv[3], argv[4], atof(argv[2]));
    } else if (strcmp(argv[1], "-c2") == 0) {
        task2(argv[3], argv[4], atof(argv[2]));
    } else if (strcmp(argv[1], "-d") == 0) {
        task3(argv[2], argv[3]);
    }
}
