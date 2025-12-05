#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "functions.h"

void Print_helpMenu_or_Err(int choice)
{
    switch(choice)
    {
        case 1 :
        {
            printf(BOLD_WHITE".-----------------------------------.\n"RESET);
            printf("|             HELP MENU             |\n");
            printf(BOLD_WHITE"'-----------------------------------'\n"RESET);
            printf("| 1. -v -> to view mp3 file contents|\n");
            printf("| 2. -e -> to edit contents         |\n");
            printf("|    2.1. -t -> to edit string title|\n");
            printf("|    2.2. -a -> to edit artist name |\n");
            printf("|    2.3. -A -> to edit album name  |\n");
            printf("|    2.4. -y -> to edit year        |\n");
            printf("|    2.5. -m -> to edit content     |\n");
            printf("|    2.6. -c -> to edit comment     |\n");
            printf(BOLD_WHITE"'-----------------------------------'\n"RESET);
            break;
        }
        case 2 :
        {
            printf("./a.out : INVALID ARGUMENTS\n");
            printf("-> To view please pass like : ./a.out -v mp3Filename\n");
            printf("-> To edit please pass like : ./a.out -e -t/-a/-l/-y/-c changing_text mp3Filename\n");
            printf("-> To get help pass like    : ./a.out --help\n");
        }
        
    }
        
}

int Mp3_View(char *Filename)
{
    //Allocating variables
    int i, Content_size, j, k;
    char buffer[4], frameId[5], *ptr, ch;
    unsigned char temp;

    char atributes[6][15] = {"TITLE", "ARTIST", "ALBUM", "YEAR", "MUSIC", "COMMENT"};

    //Opening the mp3 file
    FILE *fptr;
    fptr = fopen(Filename, "r");
    if(fptr == NULL)
    {
        printf(RED"ERROR : "RESET"File Opening Failed!\n");
        return 0;
    }

    //Reading TAG and comparing
    fread(buffer, 3, 1, fptr);
    buffer[3] = '\0';
    if(strcmp(buffer, "ID3"))
    {
        printf(RED"ERROR : "RESET"This file is not supported!\n");
        return 0;
    }
    fseek(fptr, 7, SEEK_CUR);

    //Running loop to print file contents
    
    printf(BOLD_WHITE"============================================\n"RESET);
    printf(BLUE"               FILE CONTENTS                    \n"RESET);
    printf(BOLD_WHITE"============================================\n"RESET);
    for(i = 0; i < 6; i++)
    {
        fread(frameId, 4, 1, fptr);
        frameId[4] = '\0';

        printf(CYAN"%-7s"RESET" : ", atributes[i]);

        fread(&Content_size, sizeof(int), 1, fptr);
        ptr = (char*) &Content_size;
        for(k = 0; k < 2; k++)
        {
            temp = ptr[k];
            ptr[k] = ptr[3 - k];
            ptr[3 - k] = temp;
        }

        fseek(fptr, 2, SEEK_CUR);

        for(j = 0; j < Content_size; j++)
        {
            fread(&ch, sizeof(char), 1, fptr);
            putchar(ch);
        }
        printf("\n");
    }
    printf(BOLD_WHITE"============================================\n"RESET);
}

int substring(char *hay, char *nee)
{
    int len = strlen(hay);
    return (!(strcmp(hay+(len - 4), nee)));
}

void Mp3_Edit(char *FileName, char *NewName, char *FrameId)
{
    int size, Newsize_big, Newsize_lit;
    char buffer[12];
    char tag[5], *ptr, *ptr2, ch, temp;

    FILE *fptr, *dup_fptr;

    //Opening Originam Mp3 file
    fptr = fopen(FileName, "r");
    if(fptr == NULL)
    {
        printf(RED"ERROR : "RESET"File Not Found!\n");
        return;
    }

    //Creating duplicate file
    dup_fptr = fopen("duplicate.mp3", "w");
    
    //Reading and writitng header details
    fread(buffer, 10, 1, fptr);
    fwrite(buffer, 10, 1, dup_fptr);
    
    //Loops for 6 times
    for(int i = 0; i < 6; i++)
    {
        
        //Reading the Frame Id
        fread(tag, 4, 1, fptr);
        tag[4] = '\0';

        //Comparing the frame Id
        if(!strcmp(FrameId, tag))
        {
            // printf("hello");
            //Writitng the Frame Id
            fwrite(tag, 4, 1, dup_fptr);

            //Reading the size
            fread(&size, 4, 1, fptr);

            //Converting to little endian
            ptr = (char *)&size;
            for(int j = 0; j < 2; j++)
            {
                temp = ptr[j];
                ptr[j] = ptr[3 - j];
                ptr[3 - j] = temp;
            }
            

            //Getting the NewName size
            Newsize_big = strlen(NewName) ;
            Newsize_lit = strlen(NewName) ;

            //Converting the Newsize to Big endian
            ptr2 = (char*) &Newsize_big;
            for(int j = 0; j < 2; j++)
            {
                temp = ptr2[j];
                ptr2[j] = ptr2[3 - j];
                ptr2[3 - j] = temp;
            }

            //Writing New size
            fwrite(&Newsize_big, sizeof(int), 1, dup_fptr);

            //Reading and writitng flag and Null
            fread(tag, 2, 1, fptr);
            fwrite(tag, 2, 1, dup_fptr);

            //Writing the Newname to duplicate
            //fwrite(NewName, Newsize_lit, 1, dup_fptr);
            for(int j = 0; j < Newsize_lit; j++)
            {
                // fread(&ch, sizeof(char), 1, fptr);
                 fwrite(&NewName[j], sizeof(char), 1, dup_fptr);
            }
            fseek(fptr, size, SEEK_CUR);

            //Copying all the data to duplicate
            while((fread(&ch, sizeof(char), 1, fptr)) == 1)
            {
                fwrite(&ch, sizeof(char), 1, dup_fptr);
            }

            //Giving Greeting and breaaking the loop
            printf(BOLD_GREEN"SUCCESS : "RESET"Contact Edited successfully!\n");
            break;
        }
        else
        {
            //Writitng Frame Id
            fwrite(tag, 4, 1, dup_fptr);

            //Reading Size
            fread(&size, sizeof(int), 1, fptr);

            //Writitng size to duplicate
            fwrite(&size, sizeof(int), 1, dup_fptr);

            //Converting the size to Little endian
            ptr = (char *)&size;
            for(int j = 0; j < sizeof(int)/2; j++)
            {
                temp = ptr[j];
                ptr[j] = ptr[sizeof(int) - 1 - j];
                ptr[sizeof(int) - 1 - j] = temp;
            }

            //for flag and NULL
            fread(tag, 2, 1, fptr);
            fwrite(tag, 2, 1, dup_fptr);

            //Reading and writitng the Size bytes of content to duplicate file
            for(int j = 0; j < size; j++)
            {
                fread(&ch, sizeof(char), 1, fptr);
                fwrite(&ch, sizeof(char), 1, dup_fptr);
            }
        }
    }

    //Removing old file
    remove(FileName);

    //Renaming Duplicate file as original file
    rename("duplicate.mp3", FileName);
        
}