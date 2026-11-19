
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char name[20];

    printf("Enter donor name: ");
    if (fgets(name, sizeof(name), stdin) == NULL)
        return 1;

    name[strcspn(name, "\n")] = '\0';

    printf("Donor name: %s\n", name);

    FILE *fp = fopen("donors.txt", "r");

    if (fp == NULL)
    {
        perror("File error");
    }
    else
    {
        printf("File opened successfully\n");
        fclose(fp);
    }

    if (argc != 3)
    {
        printf("Invalid arguments\n");
        return 1;
    }

    if (strcmp(argv[1], "find") != 0 &&
        strcmp(argv[1], "issue") != 0)
    {
        printf("Invalid command\n");
        return 1;
    }

    printf("Command: %s\n", argv[1]);
    printf("Blood group: %s\n", argv[2]);

    return 0;
}
