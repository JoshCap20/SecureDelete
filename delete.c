#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_PASSES 3

void print_binary(const char *label, const char *data, long size)
{
    printf("%s:\n", label);
    for (long i = 0; i < size; i++)
    {
        printf(" %02x", (unsigned char)data[i]);
    }
    printf("\n");
}

int secure_delete(const char *filename, int passes, int verbose)
{
    FILE *file;
    long file_size;
    char *random_data;
    int i, j;

    srand((unsigned int)time(NULL));

    file = fopen(filename, "rb+");
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);

    random_data = (char *)malloc(file_size);

    if (!random_data)
    {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }

    if (verbose)
    {
        fseek(file, 0, SEEK_SET);
        int read = fread(random_data, 1, file_size, file);
        if (read != file_size)
        {
            perror("Error reading file");
            free(random_data);
            fclose(file);
            return 1;
        }
        print_binary("Original data", random_data, file_size);
    }

    for (i = 0; i < passes; i++)
    {
        for (j = 0; j < file_size; j++)
        {
            random_data[j] = rand() % 256;
        }

        fseek(file, 0, SEEK_SET);
        fwrite(random_data, 1, file_size, file);
        fflush(file);
    }

    if (verbose)
    {
        print_binary("Random data", random_data, file_size);
    }

    free(random_data);
    fclose(file);
    return remove(filename);
}

void print_usage(const char *prog_name)
{
    printf("Usage: %s [options] <file>\n", prog_name);
    printf("Options:\n");
    printf("  -v, --verbose         Show original and edited binary content\n");
    printf("  -p NUM, --passes NUM  Set the number of overwrite passes (default: 3)\n");
    printf("  -h, --help            Show this help message\n");
}

int main(int argc, char *argv[])
{
    int verbose = 0;
    int passes = DEFAULT_PASSES;
    char *filename = NULL;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0)
        {
            verbose = 1;
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            print_usage(argv[0]);
            return 0;
        }
        else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--passes") == 0)
        {
            if (i + 1 < argc)
            {
                passes = atoi(argv[++i]);
                if (passes < 1)
                {
                    fprintf(stderr, "Invalid passes parameter: %s\n", argv[i]);
                    return 1;
                }
                printf("Running with %d passes\n", passes);
            }
            else
            {
                fprintf(stderr, "Missing argument for %s\n", argv[i]);
                return 1;
            }
        }
        else if (filename == NULL)
        {
            filename = argv[i];
        }
        else
        {
            fprintf(stderr, "Unrecognized option: %s\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }
    }

    if (!filename)
    {
        print_usage(argv[0]);
        return 1;
    }

    if (secure_delete(filename, passes, verbose) != 0)
    {
        perror("Error securely deleting file");
        return 1;
    }

    printf("File %s has been securely deleted.\n", filename);
    return 0;
}
