
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char name[30];
    char group[5];
} Donor;

typedef struct
{
    int group_code;
    int units;
} Stock;

int update_units(FILE *fp, int index, int units)
{
    Stock s;

    if (fseek(fp, index * sizeof(Stock), SEEK_SET) != 0)
        return 0;

    if (fread(&s, sizeof(Stock), 1, fp) != 1)
        return 0;

    s.units = units;

    if (fseek(fp, -(long)sizeof(Stock), SEEK_CUR) != 0)
        return 0;

    if (fwrite(&s, sizeof(Stock), 1, fp) != 1)
        return 0;

    return 1;
}

int main()
{
    Donor d[10], temp;
    FILE *fp;
    int i;

    for (i = 0; i < 10; i++)
    {
        d[i].id = 1001 + i;
        sprintf(d[i].name, "Donor%d", i + 1);
        strcpy(d[i].group, "O+");
    }

    fp = fopen("donors.txt", "w");

    if (fp == NULL)
    {
        perror("donors.txt");
        return 1;
    }

    for (i = 0; i < 10; i++)
        fprintf(fp, "%d %s %s\n",
                d[i].id, d[i].name, d[i].group);

    fclose(fp);

    fp = fopen("donors.txt", "r");

    if (fp == NULL)
    {
        perror("donors.txt");
        return 1;
    }

    printf("Text file records:\n");

    while (fscanf(fp, "%d %29s %4s",
                  &temp.id, temp.name, temp.group) == 3)
    {
        printf("%d %s %s\n",
               temp.id, temp.name, temp.group);
    }

    fclose(fp);

    fp = fopen("donors.dat", "wb");

    if (fp == NULL)
    {
        perror("donors.dat");
        return 1;
    }

    fwrite(d, sizeof(Donor), 10, fp);
    fclose(fp);

    fp = fopen("donors.dat", "rb");

    if (fp == NULL)
    {
        perror("donors.dat");
        return 1;
    }

    printf("\nBinary file records:\n");

    while (fread(&temp, sizeof(Donor), 1, fp) == 1)
    {
        printf("%d %s %s\n",
               temp.id, temp.name, temp.group);
    }

    fclose(fp);

    fp = tmpfile();

    if (fp == NULL)
    {
        perror("tmpfile");
        return 1;
    }

    Stock initial[5] =
    {
        {1, 40}, {2, 25}, {3, 12}, {4, 8}, {5, 30}
    };

    fwrite(initial, sizeof(Stock), 5, fp);

    printf("\nupdate record 3: %s\n",
           update_units(fp, 3, 20) ? "done" : "failed");

    printf("update record 9: %s\n",
           update_units(fp, 9, 20) ? "done" : "failed");

    rewind(fp);

    printf("\nStock records:\n");

    Stock s;

    while (fread(&s, sizeof(Stock), 1, fp) == 1)
        printf("%d:%d ", s.group_code, s.units);

    printf("\n");

    fclose(fp);

    return 0;
}
