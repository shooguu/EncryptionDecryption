#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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
    printf("File created and written to successfully\n\n");
}


void create_new_file(FILE *fp, char* filename)
{
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


void edit_existing_file()
{
    
}

void print_existing_file(FILE *fp)
{
    int line_number = 1;
    printf("\nDECRYPTED TEXT\n--------------\n");
    char buffer[DATASIZE];

    while (fgets(buffer, DATASIZE, fp))
    {
        decrypt_text(buffer);
        printf("\t%d: %s", line_number++, buffer);
    }
    printf("\n");
}

void view_existing_file(FILE *fp, char *filename)
{
    if (strlen(filename) == 0)
    {
        printf("Enter a file directory: ");
        scanf("%s", filename);
    }
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
        timer(300);
        printf(".");
    }
    printf("\n");
    print_existing_file(fp);
}


int main()
{
    char option_1;
    FILE *active_fp = NULL;
    char active_filename[FILENAMESZ];

    while (1)
    {
        printf("Currently active file: %s\n", active_filename);
        printf("[1] Create new file\n[2] Edit existing file\n[3] View existing file\n[4] Quit\n$: ");
        scanf("%c", &option_1);

        if (option_1 == '1')
        {
            create_new_file(active_fp, active_filename);
        }
        else if (option_1 == '2')
        {
            //read_existing_file();
            break;
        }
        else if (option_1 == '3')
        {
            view_existing_file(active_fp, active_filename);
        }
        else if (option_1 == '4')
        {
            printf("Successfully exited\n");
            exit(1);
        }
        else
        {
            printf("\nPlease enter a valid number\n");
        }
        fflush(stdin);
    }

    return 0;
}
