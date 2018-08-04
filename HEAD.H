#include <dos.h>

#define COLS 80
#define ROWS 25
#define VIDEO 0x10
// The head.h header file should always be included AFTER stdio.h
struct stats {
       int hp;                  // Hit Points
       int hp_max;              // This is coded in so that the character's HP wont go above 100
       int attack;              // Attack value
       int defense;             // Defense value
       int agility;             // Agility value
       int luck;                // Luck value, the higher this gets, the better chance of landing a critical
       int weapon_bonus;        // Bonus caused by Basilius' weapon
       int armor_bonus;         // Bonus caused by Basilius' armor
       int xpos;                // The x position on the ASCII maps
       int ypos;                // The y position on the ASCII maps
       unsigned long exp;       // Experience points
       int gold;                // Gold!
       int map;                 // Which ASCII map to put the character in
       int level;               // Basilius' level
       unsigned int level_up;   // How many experience points you need to level up
       int level_up_number;     // The number by which Basilius' stats are increased when he levels up
       int pilums;              // Ancient Roman spear, this will be used as a sort of special weapon, the sort of thing you'd only pull out at a boss fight
       int pilum_bonus;         // How much more damage you caused because you threw a pilum
       int medical_herbs;       // Number of medical herbs (1 medical herb restores 20 HP)
       int medical_berries;     // Number of medical berries (1 medical berry restores 40 HP)
       };
struct stats hero;

cls()  // Clear screen function, used for redrawing the screen for example
     {
        union REGS regs;

        regs.h.ah=0x06;
        regs.h.al=0x00;
        regs.h.bh=0x07;
        regs.h.ch=0x00;
        regs.h.cl=0x00;
        regs.h.dh=ROWS-1;
        regs.h.dl=COLS-1;
        int86(VIDEO,&regs,&regs);

        locate(0,0);
     }
locate(int row, int col) // Moves the cursor to a specific XY coordinate on the screen
           {
                union REGS regs;

                regs.h.ah=0x02;
                regs.h.bh=0x00;
                regs.h.dh=col;
                regs.h.dl=row;
                int86(VIDEO,&regs,&regs);
           }
char readchar() // Returns the hexidecmal code of the character located at the current cursor position
          {
                char c;
                union REGS regs;

                regs.h.ah=0x08;
                regs.h.bh=0x00;
                int86(VIDEO,&regs,&regs);
                c=regs.h.al;

                return(c);
          }
dcolor(char ch,unsigned char color,int page)
     { // Example function, should probably be deleted to save space
        union REGS regs;
        int x,y;

        regs.h.ah=0x03;
        regs.h.bh=page;
        int86(VIDEO,&regs,&regs);
        y=regs.h.dl;
        x=regs.h.dh;

        regs.h.ah=0x09;
        regs.h.al=ch;
        regs.h.bh=page;
        regs.h.bl=color;
        regs.x.cx=1;
        int86(VIDEO,&regs,&regs);

        y++;

        regs.h.ah=0x02;
        regs.h.bh=page;
        regs.h.dh=x;
        regs.h.dl=y;
        int86(VIDEO,&regs,&regs);
     }


write2page(char *string,int page)
     {  // Writes to a specific memory page, should also probably be deleted
        union REGS regs;

        while(*string)
        {
                dcolor(*string,0x07,page);
                string++;
        }
     }
set_screen(unsigned char i)
     {
         union REGS regs;

         regs.h.ah=0x00;
         regs.h.al=i;
         int86(VIDEO,&regs,&regs);
     }
switch_page(int page)
    {  //  Changes pages, should also probably be deleted on memory issues
        union REGS regs;

        regs.h.ah=0x05;
        regs.h.al=page;
        int86(VIDEO,&regs,&regs);
    }
read_pos_y_minus()
    {   // Brings the cursor one y coordinate up, however, if the y coordinate is 0, merely locates the cursor to its own coordinates
        int x,y;
        union REGS regs;
        regs.h.ah=0x03;
        regs.h.bh=0x00;
        int86(VIDEO,&regs,&regs);
        x=regs.h.dl;
        y=regs.h.dh;
        if(y>4)
             y--;
        locate(x,y);
        return(0);

    }
int x_check_a() //Find the x coordinate of the cursor and return it
    {
        int x,y;
        union REGS regs;
        regs.h.ah=0x03;
        regs.h.bh=0x00;
        int86(VIDEO,&regs,&regs);
        x=regs.h.dl;
        y=regs.h.dh;
        return(x);
    }
int x_check_left()       // Checks the cursor's x coordinate,
    {                    // If the x is at the far left edge of the map, return 0
        int xpos;        // if the x coordinate is to the right of the far left edge of the map, return 1
        union REGS regs; // and if the x coordinate is to the left of the far left edge of the map, then something's seriously wrong with the map alignment, return 2
        regs.h.ah=0x03;
        regs.h.bh=0x00;
        int86(VIDEO,&regs,&regs);
        xpos=regs.h.dl;
        if(xpos==19)
                      return(0);
        if(xpos>19)
                      return(1);
        if(xpos<19)
                      return(2);
    }
int x_check_right() // Highly similar to x_check_left(), but checks to see if the cursor is at the far right edge of the map
    {
        int xpos;                // Find the cursor's x coordinate
        union REGS regs;
        regs.h.ah=0x03;
        regs.h.bh=0x00;
        int86(VIDEO,&regs,&regs);
        xpos=regs.h.dl;          // Save it to the variable xpos
        if(xpos==59)             // If it's 59, return 0
                      return(0);
        if(xpos<59)              // If it's less than 59, return 1
                      return(1);
        if(xpos>59)              // Just an error check, if the x coordinate is greater than 59
                      return(2); // then you're at the far right edge of the map, return 2
    }
read_cursor_pos_check_y() // Figure out the cursor's y coordinate
    {                     // If the cursor is at the bottom y coordinate...
        int ypos;         // Make the speaker beep
        union REGS regs;
        regs.h.ah=0x03;
        regs.h.bh=0x00;
        int86(VIDEO,&regs,&regs);
        ypos=regs.h.dh;
        if(ypos==19)
                       printf("\a");
    }
write_coordinates()  // Writes the xy coordinates of the cursor to a file
     {               // called coord.txt
        FILE *file;
        int x,y;
//        locate(hero.xpos,hero.ypos);
        union REGS regs;
        regs.h.ah=0x03;
        regs.h.bh=0x00;
        int86(VIDEO,&regs,&regs);
        x=regs.h.dl;
        y=regs.h.dh;
        file=fopen("coord.txt","w");
        if(file==NULL)
        {
                cls();
                printf("AAAAHHHH!!!! Real Memory Errors!");
                getch();
                exit(0);
        }
        fprintf(file,"%i %i",x,y);
        fclose(file);
     }
read_pos_carriage_return() // Records the cursor's xy coords, and figure out
     {                     // the distance from the cursor's x position to
        int x,y,a;         // the left edge of the map, then locate the map
        union REGS regs;   // said distance to the left
        regs.h.ah=0x03;
        regs.h.bh=0x00;
        int86(VIDEO,&regs,&regs);
        x=regs.h.dl;       //  Find the x
        y=regs.h.dh;       //  and y coordinates
        a=x;               //  Set a to the x coordinate
        while(x!=19)       //  decrement the value of x
                   x--;    //  to 19
        locate(x,y);       //  Locate the cursor there
        return(a);         //  Return the old x coordinate
     }
read_pos_n_check() // Checks to see if the cursor position is in the
     {             // Absolute bottom right hand corner of the map
        int x,y,i; // Returns 1 if true, 0 if false
        union REGS regs;
        regs.h.ah=0x03;
        regs.h.bh=0x00;
        int86(VIDEO,&regs,&regs);
        x=regs.h.dl;
        y=regs.h.dh;
        if(x==59 && y==19)
        {
                 i=1;
                 return(i);
        }
        i=0;
        return(i);
     }
int xy_coords(int a)
    {
        int x,y,q;
        union REGS regs;
        regs.h.ah=0x03;
        regs.h.bh=0x00;
        int86(VIDEO,&regs,&regs);
        x=regs.h.dl;
        y=regs.h.dh;
        if(a==0) // This was read_pos_y_minus()
        {
                if(y>5)
                       y--;
                locate(x,y);
                return(0);
        }
        if(a==1) // This was x_check_left()
        {
              if(x==20)
                      return(0);
              if(x>20)
                      return(1);
              if(x<20)
                      return(2);

        }
        if(a==2)     // This was x_check_right()
        {
                if(x==49)             // If it's 49, return 0
                      return(0);
                if(x<49)              // If it's less than 49, return 1
                      return(1);
                if(x>49)              // Just an error check, if the x coordinate is greater than 49
                      return(2); // then you're at the far right edge of the map, return 2
        }
        if(a==3)  // This was read_cursor_pos_check_y()
        {
                if(y==19)
                       printf("\a");
                return(0);
        }
        if(a==4)  // This was read_pos_carriage_return()
        {
                a=x;               //  Set a to the x coordinate
                while(x!=20)       //  decrement the value of x
                       x--;        //  to 20
                locate(x,y);       //  Locate the cursor there
                return(a);         //  Return the old x coordinate
        }
        if(a==5)  // This was read_pos_n_check()
        {
                if(x==20 && y==20)
                {
                          a=1;
                          return(a);
                }
                a=0;
                return(a);
        }
        if(a==6)
        {
                y++;
                locate(20,y);
        }
        return(0);
    }
