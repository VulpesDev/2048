#include <stdio.h>

char ascii_art[][11] = {
    " 0000",
    "00  00",
    "00  00",
    "00  00",
    " 0000",

    "1111",
    "  11",
    "  11",
    "  11",
    "111111",

    " 2222",
    "22  22",
    "   22",
    "  22",
    "222222",

    " 3333",
    "33  33",
    "   333",
    "33  33",
    " 3333",

    "44  44",
    "44  44",
    "444444",
    "    44",
    "    44",

    "555555",
    "55",
    "55555",
    "    55",
    "55555",

    " 6666",
    "66",
    "66666",
    "66  66",
    " 6666",

    "777777",
    "   77",
    "  77",
    " 77",
    "77",

    " 8888",
    "88  88",
    " 8888",
    "88  88",
    " 8888",

    " 9999",
    "99  99",
    " 99999",
    "    99",
    " 9999",

    ""
};

#include <string.h>
#include <stdlib.h>
char* print_ascii_digit(char array[][11], int num, int size) {
    char *result = calloc(1, sizeof(char) * size*size*2);
    if (result == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        strcat(result, array[num * size + i]);
        strcat(result, "\n");
    }
    return result;
}

int main() {
    printf("%s", print_ascii_digit(ascii_art, 2, 5));
    printf("\n");
    printf("%s", print_ascii_digit(ascii_art, 0, 5));
    printf("\n");
    printf("%s", print_ascii_digit(ascii_art, 0, 5));
    printf("\n");
    printf("%s", print_ascii_digit(ascii_art, 4, 5));
    printf("\n");
    return 0;
}