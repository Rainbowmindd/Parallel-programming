#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Wywolany program:\n");

    const char *imie_nazwisko="Martyna Kindrat";

    for (int i = 0; i < argc; i++) {
        printf(" %d: %s\n", i, argv[i]);
    }

    printf("Imie i nazwisko: %s\n",imie_nazwisko);

    return 0;
}
