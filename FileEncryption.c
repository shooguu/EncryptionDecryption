#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "FileEncryption.h"

#define DATASIZE 1000
#define FILENAMESZ 100
#define OFFSET 99


void timer(int interval)
{
    int msec = 0;
    clock_t before = clock();

    while (msec < interval)
    {
        clock_t difference = clock() - before;
        msec = difference * 1000 / CLOCKS_PER_SEC;
    }
}

void encrypt_text(char *data)
{
    int counter = 0;
    while (data[counter] != '\n')
    {
        data[counter] = data[counter] + OFFSET;
        counter++;
    }
}

void decrypt_text(char *data)
{
    int counter = 0;
    while (data[counter] != '\n')
    {
        data[counter] = data[counter] - OFFSET;
        counter++;
    }
}


void write_to_file(FILE *fp)
{
    char data[DATASIZE];
    bool eof = false;

    while (!eof)
    {
        printf("$: ");
        fgets(data, DATASIZE, stdin);

        if (data[0] == ':' && data[1] == 'w' && data[2] == 'q')
            break;
        encrypt_text(data);
        fputs(data, fp);
    }
    fclose(fp);
    printf("File created and written to successfully\n");
}


void create_new_file()
{
    char filename[FILENAMESZ];
    FILE *fp;

    printf("Enter a file directory: ");
    scanf("%s", filename);

    fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("File could not be created\n");
        exit(1);
    }

    printf("File created successfully\nUse :wq to write and quit the file\n");
    fflush(stdin);
    write_to_file(fp);
}


void print_exising_file(FILE *fp)
{
    
}

void read_existing_file()
{
    char filename[FILENAMESZ];
    FILE *fp;

    printf("Enter a file directory: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File does not exist");
        exit(1);
    }

    printf("File found successfully\nDecrypting");
    for (int i = 0; i < 3; ++i)
    {
        fflush(stdout);
        timer(500);
        printf(".");
    }
    printf("\n");
}


int main()
{
    char filename[100];
    char option_1;
    FILE *fp;

    while (1)
    {
        printf("[1] Create new file\n[2] Edit existing file\n[3] Quit\n$: ");
        scanf("%c", &option_1);

        if (option_1 == '1')
        {
            create_new_file();
            break;
        }
        else if (option_1 == '2')
        {
            read_existing_file();
            break;
        }
        else if (option_1 == '3')
        {
            printf("Successfully exited\n");
            exit(1);
        }
        printf("Please enter a valid inter\n");
        fflush(stdin);
    }

    return 0;
}