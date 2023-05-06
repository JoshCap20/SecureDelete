#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_PASSES 3

int secure_delete(const char *filename, int passes) {
    FILE *file;
    long file_size;
    char *random_data;
    int i, j;

    srand((unsigned int)time(NULL));

    file = fopen(filename, "rb+");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);

    random_data = (char *)malloc(file_size);
    if (!random_data) {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }

    for (i = 0; i < passes; i++) {
        for (j = 0; j < file_size; j++) {
            random_data[j] = rand() % 256;
        }

        fseek(file, 0, SEEK_SET);
        fwrite(random_data, 1, file_size, file);
        fflush(file);
    }

    free(random_data);
    fclose(file);
    return remove(filename);
}

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        printf("Usage: %s <file> [<passes>]\n", argv[0]);
        return 1;
    }

    int passes = (argc == 3) ? atoi(argv[2]) : DEFAULT_PASSES;

    if (passes < 1) {
        fprintf(stderr, "Invalid passes parameter: %s\n", argv[2]);
        return 1;
    }

    if (secure_delete(argv[1], passes) != 0) {
        perror("Error securely deleting file");
        return 1;
    }

    printf("File %s has been securely deleted.\n", argv[1]);
    return 0;
}
