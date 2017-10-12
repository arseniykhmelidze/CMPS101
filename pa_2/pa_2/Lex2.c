//  File: Lex.c
//  Class: CMPS 101
//  Assignment: PA2
//  Student: Arseniy Khmelidze (akhmelid)
//  Date created: 01/23/17
//
//  Copyright © 2017 Arseniy Khmelidze. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"



int main ( int argc, char *argv[] )
{
	// Setting up the file stream
    char *inputFile = malloc(strlen(argv[1] + 5));
    char *outputFile = malloc(strlen(argv[2] + 5));

    sprintf(inputFile, "%s", argv[1]);
    sprintf(outputFile, "%s", argv[2]);

    FILE *fp; // File pointer

    if (argc < 2)
    {
        printf("Error: You must pass at least 2 arguments.");
        return 0;
    }

    fp = fopen(inputFile, "r");

    if (fp == NULL)
    {
        perror("Error: Input file not found.");
    }

    int line_num = 0; // Number of lines counter
    char buffer[255]; // Temp buffer

    while (fgets(buffer, 255, (FILE *) fp))
    {
        if(buffer[0] != '\n' && buffer[0] != '\0')
        {
            ++line_num;
        }
    }
    rewind(fp);

    char strArray[line_num - 1][255]; // Setting up a string array. Length depends on # of lines
    int count = 0;
    int MAX_LEN = 255;

//    while (fgets(buffer, MAX_LEN, fp) != NULL)
//    {
//        char * token = strtok(buffer, " \n");
//        char token_list[255];
//
//        token_list[0] = '\0';
//
//        while (token != NULL)
//        {
//            strcat(token_list, token);
//
//            token = strtok(NULL, "\n");
//
//            strcpy(strArray[count], tokenizer_list);
//            count++;
//        }
//    }

      while (fgets(buffer, MAX_LEN, fp) != NULL)
      {
    	  	char *tokenptr = strtok(buffer, " \n");
    		char tokenlist[MAX_LEN];
			tokenlist[0] = '\0';

    		while (tokenptr != NULL)
    		{
    			strcat(tokenlist, tokenptr);
    			tokenptr = strtok(NULL, " \n");

    			if (strcmp(tokenlist, "") != 0)
      	  	  	{
    				strcpy(strArray[count], tokenlist);
      	  	  	}

    			count++;
    		}
      }
      fclose(fp);




    // Adding & Sorting elements in the file
    List list = newList();

    append(list, 0);

    for (int i = 1; i < line_num; i++)
    {
        moveFront(list);

        while (index(list) >= 0)
        {
            int x = get(list);

            if(strcmp(strArray[i], strArray[x]) < 0)
            {
                if(index(list) == 0)
                {
                    prepend(list, i);
                    break;
                }

                insertBefore(list, i);
                break;
            }
            moveNext(list);
        }

        if(index(list) < 0)
        {
            append(list, i);
        }

    }

    moveFront(list);

    fp = fopen(outputFile, "w");

    if (fp == NULL)
    {
        perror("Error: Output file not found.");
    }

    if (fp == NULL)
    {
        printf("Could not open file.\n");
        exit(1);
    }

    for (int j = 0; j < line_num; j++)
    {
        fprintf(fp, "%s\n", strArray[get(list)]);
        moveNext(list);
    }
    fclose(fp);

    freeList(&list);
    free(outputFile);
    free(inputFile);
}
