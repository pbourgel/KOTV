//Map Editor for King of the Visigoths
//An ASCII game from Flakesoft
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include "head.h"

#define BACKSPACE 0x08
#define YUP 1
#define FALSE 0
#define CR 0x0d
#define BLANK 0x20

char *map_array;
int length=2000;


int main()
    {
        FILE *file_handle;
        char c;
        int done=FALSE;
        int index=0;
        char ch;
        int x,y,q,x_check,ii;
        map_array=(char *)malloc(2000);
        if(map_array==NULL)
        {
                printf("Error: Malloc couldn't allocate neccesary memory.  Press any key to abort program.");
                getch();
                exit(0);
        }
        cls();
        do
        {
                read_cursor_pos_check_y();

                ch=getch();

                switch(ch)
                {
                        case BACKSPACE:
                                x_check=x_check_a(); // Find out the cursor's x coordinate
                                if(x_check==0)       // If it's at the far left corner of the screen...
                                     break;          // Do nothing
                                if(index==0)         // Ditto if you're at the start of the array
                                     break;
                                printf("\b");
                                printf(" ");
                                printf("\b");
                                index--;
                                map_array[index]=BLANK;
                                break;
                        case '~':
                                printf("\xC9");
                                map_array[index]=0xC9;
                                index++;
                                break;
                        case '@':
                                printf("\xCD");
                                map_array[index]=0xCD;
                                index++;
                                break;
                        case '#':
                                printf("\xBB");
                                map_array[index]=0xBB;
                                index++;
                                break;
                        case '$':
                                printf("\xBA");
                                map_array[index]=0xBA;
                                index++;
                                break;
                        case '%':
                                printf("\xC8");
                                map_array[index]=0xC8;
                                index++;
                                break;
                        case '^':
                                printf("\xBC");
                                map_array[index]=0xBC;
                                index++;
                                break;
                        case '+':
                                ii=read_pos_n_check();
                                if(ii==1)
                                {
                                        map_array[index]=NULL;
                                        done=YUP;
                                        break;
                                }
                                break;
                        case '&':
                                printf("\xB2");
                                map_array[index]=0xB2;
                                index++;
                                break;
                        case '=':
                                read_pos_y_minus();
                                index-=80;
                                break;
                        case '/':
                                printf("\x2F");
                                map_array[index]=0x2F;
                                index++;
                                break;
                        case CR:
                                q=read_pos_carriage_return();
                                index-=q;
                                break;
                        default:
                                printf("%c",ch);
                                map_array[index]=ch;
                                index++;
                                break;
                }


        }
        while(!done);

        cls();
        printf("Save file (Y/N)?");
        c=toupper(getch());
        if(c=='N')
        {
                  cls();
                  free(map_array);
                  map_array=NULL;
                  exit(0);
        }
        if(c=='Y')
        {
/*         for(;;)
           {
                cls();
                printf("Which file?\n\n");

                printf("A. map_t.txt (Title screen)\n");
                printf("B. map_00.txt\n");
                printf("C. map_01.txt\n");
                printf("D. map_02.txt\n");
                printf("E. map_03.txt\n");
                printf("F. map_04.txt\n");
                printf("G. map_05.txt\n");
                printf("H. map_06.txt\n");
                printf("I. map_07.txt\n");
                printf("J. map_08.txt\n");
                printf("K. map_09.txt\n");
                printf("L. map_10.txt\n");
                printf("M. map_11.txt\n");
                printf("N. map_12.txt\n");
                printf("O. map_13.txt\n");
                printf("P. map_14.txt\n");
                printf("Q. map_15.txt\n");
                printf("R. map_16.txt\n");
                printf("S. map_17.txt\n");

                c=toupper(getch());
                if(c=='A');
                {
                        file_handle=fopen("map_t.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='B')
                {
                        file_handle=fopen("map_00.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='C')
                {
                        file_handle=fopen("map_01.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='D')
                {
                        file_handle=fopen("map_02.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='E')
                {
                        file_handle=fopen("map_03.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='F')
                {
                        file_handle=fopen("map_04.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='G')
                {
                        file_handle=fopen("map_05.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='H')
                {
                        file_handle=fopen("map_06.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='I')
                {
                        file_handle=fopen("map_07.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='J')
                {
                        file_handle=fopen("map_08.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='K')
                {
                        file_handle=fopen("map_09.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='L')
                {
                        file_handle=fopen("map_10.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='M')
                {
                        file_handle=fopen("map_11.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='N')
                {
                        file_handle=fopen("map_12.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);

                }
                if(c=='O')
                {
                        file_handle=fopen("map_13.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='P')
                {
                        file_handle=fopen("map_14.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='Q')
                {
                        file_handle=fopen("map_15.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                if(c=='R')
                {
                        file_handle=fopen("map_16.txt","w");
                        if(file_handle==NULL)
                        {
                                printf("AAAHHHHH!!!!! Real Memory Errors!!");
                                getch();
                                exit(0);
                        }
                        fprintf(file_handle,map_array);
                        fclose(file_handle);
                        free(map_array);
                        exit(0);
                }
                */
                file_handle=fopen("map_03.txt","w");
                if(file_handle==NULL)
                {
                     printf("AAAHHHHH!!!!! Real Memory Errors!!");
                     getch();
                     free(map_array);
                     map_array=NULL;
                     exit(0);
                }
                fprintf(file_handle,map_array);
                fclose(file_handle);
                free(map_array);
                map_array=NULL;
                cls();
                exit(0);

        //   }
        }
    }
