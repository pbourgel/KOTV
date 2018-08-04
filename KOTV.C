#include <stdio.h> // For printf, fgets, fwrite, fopen, fclose, and fread
#include <stdlib.h> // For srand and rand
#include <time.h>  // for time
#include <string.h> // For strcpy and strcat
#include <malloc.h> // For malloc and free
#include <allegro.h> // For the KEY defines, allegro_init, install_keyboard and readkey
#include "head.h" // For cls, locate, and most of the other functions there

#define CR 0x0d        // Carriage return
#define ESCAPE 0x1b    // Escape character
#define BACKSPACE 0x08 // Backspace character
#define LENGTH 199     // max length allowed for the get_string function
#define BASILIUS 0x01  // The hexidecimal code for the Player Character (PC) sprite
#define COLS 80        // Max number of x coordinates on screen
#define ROWS 25        // Max number of y coordinates on screen
#define BLANK 0x20     // Hexidecimal code for a blank space, used for collsion detection and input routines
#define YUP 1          // Substitute for TRUE as it's already defined
#define NOPE 0         // Substitute for FALSE as it's already defined
#define CLOSED_TREASURE_CHEST 0x16 // Well, yeah, a tentative closed treasure chest icon
#define OPEN_TREASURE_CHEST 0xDC // A tentative open treasure chest icon

FILE *bloing;
int c,chance;
/***************************************************************************************************************
*int c: used to read the keyboard in the main function and all the variables in the treasure_chests array to 0.*
*int chance: random number to determine whether to start a fight                                               *
***************************************************************************************************************/
char map_array_a[2001]; // Array for holding the ASCII maps
int section=0;          // Determines which set of enemies to choose from in the battle function
struct statsv {         // Villain's stats (see head.h)
        int hp;         // Villain's HP
        int attack;     // Villain's attack power
        int defense;
        int agility;
        int exp;
        int gold;
        };
struct statsv villain;
unsigned char treasure_chests[10]= {CLOSED_TREASURE_CHEST}; // Marker variables for treasure chests
int x;
int y;
int map_index;



get_string(char *string,int length)
     {  // Meant to be an input routine that's compatible with Allegro
        int esc_check=NOPE;
        int done=NOPE;
        int index=0;
        char ch;

        string[0]=NULL;

        do
        {
                ch=(char)readkey();

                if(index==length)
                {
                        switch(ch)
                        {
                                case CR:
                                     break;
                                default:
                                     ch=NULL;
                                     break;
                        }
                }
                switch(ch)
                {
                        case CR:
                             printf("\r");
                             string[index]=NULL;
                             done=YUP;
                             break;
                        case BACKSPACE:
                             if(index==0)
                                    break;
                             else
                             {
                                printf("\b");
                                printf(" ");
                                printf("\b");
                                index--;
                                break;
                             }
                        case ESCAPE:
                             printf("\r");
                             string[index]=NULL;
                             done=YUP;
                             esc_check=YUP;
                             break;
                        case NULL:
                             break;
                        case BLANK:
                             break;
                        default:
                                printf("%c",ch);
                                string[index]=ch;
                                index++;
                                break;
                }
        }
        while(done!=YUP);
        if(esc_check==YUP)
                          return(esc_check);
        return(esc_check);
     }
// Battle engine
battle(int q)
        {
           char name[20];
           int r,i,w,damage;
           cls();

           if(q==0)
           {
                r=rand()%3;
                //This part determines the stats of the enemies and what to call them, the hero's stats are up for comparison
                if(r==0)
                {               //assassin

                                strcpy(name,"assassin");
                                villain.hp=30;            // hero.hp=100;        Hit Points
                                villain.attack=12;         // hero.attack=12;     Attack value
                                villain.defense=8;        // hero.defense=10;    Defense value
                                villain.agility=9;        // hero.agility=11;    Agility value
                                villain.exp=15;
                                villain.gold=10;
                }
                if(r==1)
                {
                                strcpy(name,"rabid dog");
                                villain.hp=20;             // hero.hp=100;        Hit Points
                                villain.attack=9;          // hero.attack=12;     Attack value
                                villain.defense=5;         // hero.defense=10;    Defense value
                                villain.agility=10;         // hero.agility=11;    Agility value
                                villain.exp=15;
                                villain.gold=0;
                }
                if(r==2)
                {
                                strcpy(name,"praetorian guard");
                                villain.hp=40;               // hero.hp=100;        Hit Points
                                villain.attack=11;           // hero.hp_max=100;    This is programmed in so that the character's HP wont go above 100
                                villain.defense=9;          // hero.attack=12;     Attack value
                                villain.agility=6;          // hero.defense=10;    Defense value
                                villain.exp=10;              // hero.agility=11;    Agility value
                                villain.gold=20;
                }
                /*
                if(r==3)
                {
                      name_m=(char *)malloc(strlen(""));
                      strcpy(name_m,"");
                      villain.hp=70;
                      villain.attack=7;
                      villain.defense=5;
                      villain.agility=4;
                }
                if(r==4)
                {
                      name_m=(char *)malloc(strlen("")
                */

           }
           printf("An %s approaches!\n\n",name);
           while(1)
           {
                printf("You can:\n\n");
                printf("A - Attack\n");
                printf("I - Use an item\n");
                if(hero.pilums>0)
                                 printf("P - Use a pilum\n");
                printf("R - Run\n\n");
                printf("Your HP is %i\n",hero.hp);
                while(1)
                {
                        w=readkey();    //I didn't know W could read a book, let alone the keyboard
                        if(key[KEY_A] || key[KEY_I] || key[KEY_P] || key[KEY_R])
                                      break;
                }
                cls();
                if(key[KEY_ESC])
                {
                        cls();
                        exit(0);
                }
                if(key[KEY_A])
                {
                        i=(hero.agility+(rand()%15+1))-(villain.agility+(rand()%3+1));
                        printf("i=%i villain.agility=%i\n",i,villain.agility);
                        if(i<villain.agility)  //If you don't miss the enemy
                               printf("You missed the %s!\n\n",name);
                        if(i>=villain.agility)
                        {
                               i=(rand()%25+1);
                               if(i==5)       //If you land a critical, the amount of damage is increased because your strength is multiplied by 2.
                               {
                                       damage=((hero.attack*2)+hero.weapon_bonus+(rand()%10+1))-(villain.defense+(rand()%3+1));
                                       if(damage<=0)
                                                    printf("You missed the %s!\n\n",name);
                                       if(damage>0)
                                       {
                                                villain.hp-=damage;
                                                printf("You landed a critical hit on the %s and caused %i damage\n\n",name,damage);
                                                if(villain.hp<=0)
                                                {
                                                        hero.exp+=villain.exp;
                                                        hero.gold+=villain.gold;
                                                        printf("You defeated the %s, and got:\n\n\n%i experience points\n%i Denarii\n\n",name,villain.exp,villain.gold);
                                                        if(hero.exp>=hero.level_up)
                                                        {
                                                                hero.level_up*=2;
                                                                hero.level++;
                                                                hero.attack+=hero.level_up_number;
                                                                hero.defense+=hero.level_up_number;
                                                                hero.agility+=hero.level_up_number;
                                                                hero.hp_max+=(hero.level_up_number*10);
                                                                printf("You are now level %i  \n\nAll your stats went up by %i \n\nYour HP is now %i/%i",hero.level,hero.level_up_number,hero.hp,hero.hp_max);
                                                                hero.level_up_number*=2;
                                                        }
                                                        readkey();
                                                        break;
                                                }
                                       }
                               }
                               if(i!=5)  // If your luck isn't good enough to land a critical
                               {
                                        damage=(hero.attack+hero.weapon_bonus+(rand()%7+1)-(villain.defense+(rand()%3+1)));
                                        if(damage<=0)
                                                     printf("You missed the %s!\n\n",name);
                                        if(damage>0)
                                        {
                                                villain.hp-=damage;
                                                printf("You hit the %s and caused %i damage.\n\n",name,damage);
                                                if(villain.hp<=0)
                                                {
                                                        hero.exp+=villain.exp;
                                                        hero.gold+=villain.gold;
                                                        printf("You defeated the %s, and got:\n\n\n%i experience points\n%i Denarii\n\n",name,villain.exp,villain.gold);
                                                        if(hero.exp>=hero.level_up)
                                                        {
                                                                hero.level_up*=2;
                                                                hero.level++;
                                                                hero.attack+=hero.level_up_number;
                                                                hero.defense+=hero.level_up_number;
                                                                hero.agility+=hero.level_up_number;
                                                                hero.hp_max+=(hero.level_up_number*10);
                                                                printf("You are now level %i  \n\nAll your stats went up by %i \n\nYour HP is now %i/%i",hero.level,hero.level_up_number,hero.hp,hero.hp_max);
                                                                hero.level_up_number*=2;
                                                        }
                                                        readkey();
                                                        break;
                                                }

                                        }
                               }
                        }
                        i=(villain.agility+(rand()%10+1))-(hero.agility+(rand()%2+1));
                        printf("i=%i hero.agility=%i\n",i,hero.agility);
                        if(i>0)
                        {
                               i=(rand()%25+1); //Determines the enemies chance of getting a critical.  If its random-number-assisted luck is greater than your random-number assisted luck, then you land a critical.
                               if(i==5)       //If the enemy lands a critical, the amount of damage is increased because your strength is multiplied by 2.
                               {
                                       damage=((villain.attack*2)+(rand()%10+1))-((hero.defense+(rand()%3+1)+hero.armor_bonus));
                                       if(damage<=0)
                                                    printf("The %s just missed you!\n\n",name);
                                       if(damage>0)
                                       {
                                                hero.hp-=damage;
                                                printf("POW!  The %s landed a critical on you and caused %i damage\n\n",name,damage);
                                                if(hero.hp<=0)
                                                {
                                                        printf("You were killed by the %s, Game Over.",name);
                                                        readkey();
                                                        cls();
                                                        exit(0);
                                                }
                                       }
                               }
                               if(i!=5)
                               {
                                        damage=(villain.attack+(rand()%15+1))-(hero.defense+(rand()%3+1)+hero.armor_bonus);
                                        printf("damage=%i hero.defense=%i\n",damage,hero.defense);
                                        if(damage<=0)
                                                     printf("The %s just missed you!\n\n",name);
                                        if(damage>0)
                                        {
                                                hero.hp-=damage;
                                                printf("The %s hit you and caused %i damage.\n\n",name,damage);
                                                if(hero.hp<=0)
                                                {
                                                        printf("You were killed by the %s, Game Over.",name);
                                                        readkey();
                                                        cls();
                                                        exit(0);
                                                }
                                        }
                               }
                        }
                        else
                                printf("The %s just missed you!\n\n",name);
                }
                if(key[KEY_I])
                {
                  use_item();
                  cls();
                  i=(villain.agility+(rand()%10+1))-(hero.agility+(rand()%2+1));
                  printf("i=%i hero.agility=%i\n\n",i,hero.agility);
                  if(i>0)
                  {
                     i=(rand()%25+1); //Determines the enemies chance of getting a critical.  If its random-number-assisted luck is greater than your random-number assisted luck, then you land a critical.
                     if(i==5)       //If the enemy lands a critical, the amount of damage is increased because your strength is multiplied by 2.
                     {
                             damage=((villain.attack*2)+(rand()%10+1))-(hero.defense+(rand()%3+1)+hero.armor_bonus);
                             if(damage<=0)
                                printf("The %s just missed you!\n\n",name);
                             if(damage>0)
                             {
                                hero.hp-=damage;
                                printf("POW!  The %s landed a critical on you and caused %i damage\n\n",name,damage);
                                if(hero.hp<=0)
                                {
                                      printf("You were killed by the %s, Game Over.",name);
                                      readkey();
                                      cls();
                                      exit(0);
                                }

                             }
                     }
                     if(i!=5)
                     {
                         damage=(villain.attack+(rand()%15+1)-(hero.defense+(rand()%3+1)+hero.armor_bonus));
                         printf("damage=%i hero.defense=%i\n",damage,(hero.defense+hero.armor_bonus));
                         if(damage<=0)
                                printf("The %s just missed you!\n\n",name);
                         if(damage>0)
                         {
                                hero.hp-=damage;
                                printf("The %s hit you and caused %i damage.\n\n",name,damage);
                                if(hero.hp<=0)
                                {
                                        printf("You were killed by the %s, Game Over.",name);
                                        readkey();
                                        cls();
                                        exit(0);
                                }

                         }
                     }
                  }
                  else
                        printf("The %s missed.\n\n",name);
                }
                if(key[KEY_P])
                {
                               if(hero.pilums<=0)
                                       printf("You don't have any pilums!\n\n");
                               if(hero.pilums>0)
                               {
                                       hero.pilums--;
                                       i=(rand()%50+1);
                                       if(i==5)       //If you land a critical, the amount of damage is increased because your strength is multiplied by 2.
                                       {
                                                damage=((hero.attack*2)+hero.weapon_bonus+hero.pilum_bonus+(rand()%10+1))-(villain.defense+(rand()%3+1));
                                                if(damage<=0)
                                                    printf("You missed the %s!\n\n",name);
                                                if(damage>0)
                                                {
                                                        villain.hp-=damage;
                                                        printf("POW!  You threw a pilum and landed a critical on the %s, causing %i damage\n\n",name,damage);
                                                        if(villain.hp<=0)
                                                        {
                                                                hero.exp+=villain.exp;
                                                                hero.gold+=villain.gold;
                                                                printf("You defeated the %s, and got:\n\n\n%i experience points\n %i Denarii\n\n",name,villain.exp,villain.gold);
                                                                if(hero.exp>=hero.level_up)
                                                                {
                                                                        hero.level_up*=2;
                                                                        hero.level++;
                                                                        hero.attack+=hero.level_up_number;
                                                                        hero.defense+=hero.level_up_number;
                                                                        hero.agility+=hero.level_up_number;
                                                                        hero.hp_max+=(hero.level_up_number*10);
                                                                        printf("You are now level %i  \n\nAll your stats went up by %i \n\nYour HP is now %i/%i",hero.level,hero.level_up_number,hero.hp,hero.hp_max);
                                                                        hero.level_up_number*=2;
                                                                }
                                                                readkey();
                                                                break;
                                                        }
                                                }
                                       }
                                       if(i!=5)  // If your luck isn't good enough to land a critical
                                       {
                                                damage=(hero.attack+hero.weapon_bonus+hero.pilum_bonus+(rand()%3+1)-(villain.defense+(rand()%3+1)));
                                                if(damage<=0)
                                                     printf("You missed the %s!\n\n",name);
                                                if(damage>0)
                                                {
                                                        villain.hp-=damage;
                                                        printf("You threw a pilum at the %s and caused %i damage.\n\n",name,damage);
                                                        if(villain.hp<=0)
                                                        {
                                                                hero.exp+=villain.exp;
                                                                hero.gold+=villain.gold;
                                                                printf("You defeated the %s, and got:\n\n\n%i experience points\n%i Denarii\n\n",name,villain.exp,villain.gold);
                                                                if(hero.exp>=hero.level_up)
                                                                {
                                                                        hero.level_up*=2;
                                                                        hero.level++;
                                                                        hero.attack+=hero.level_up_number;
                                                                        hero.defense+=hero.level_up_number;
                                                                        hero.agility+=hero.level_up_number;
                                                                        hero.hp_max+=(hero.level_up_number*10);
                                                                        printf("You are now level %i  \n\nAll your stats went up by %i \n\nYour HP is now %i/%i",hero.level,hero.level_up_number,hero.hp,hero.hp_max);
                                                                        hero.level_up_number*=2;
                                                                }
                                                                readkey();
                                                                break;
                                                        }

                                                }
                                       }
                               }
                               damage=(villain.attack+(rand()%10+1)-(hero.defense+(rand()%3+1)+hero.armor_bonus));
                               if(i>0)
                               {
                                        i=(rand()%25+1); //Determines the enemies chance of getting a critical.  If its random-number-assisted luck is greater than your random-number assisted luck, then you land a critical.
                                        if(i==5)       //If the enemy lands a critical, the amount of damage is increased because your strength is multiplied by 2.
                                        {
                                                damage=((villain.attack*2)+(rand()%10+1))-((hero.defense+(rand()%3+1)+hero.armor_bonus));
                                                if(damage<=0)
                                                    printf("The %s just missed you!\n\n",name);
                                                if(damage>0)
                                                {
                                                        hero.hp-=damage;
                                                        printf("POW!  The %s landed a critical on you and caused %i damage\n\n",name,damage);
                                                        if(hero.hp<=0)
                                                        {
                                                                printf("You were killed by the %s, Game Over.",name);
                                                                readkey();
                                                                cls();
                                                                exit(0);
                                                        }
                                                }
                                        }
                                        if(i!=5)
                                        {
                                                damage=(villain.attack+(rand()%15+1))-(hero.defense+(rand()%3+1)+hero.armor_bonus);
                                                if(damage<=0)
                                                     printf("The %s just missed you!\n\n",name);
                                                if(damage>0)
                                                {
                                                        hero.hp-=damage;
                                                        printf("The %s hit you and caused %i damage.\n\n",name,damage);
                                                        if(hero.hp<=0)
                                                        {
                                                                printf("You were killed by the %s, Game Over.",name);
                                                                readkey();
                                                                cls();
                                                                exit(0);
                                                        }
                                                }
                                        }
                               }
                               else
                                   printf("The %s just missed you!\n\n",name);
                }
                if(key[KEY_R])
                {
                  i=(hero.agility+(rand()%15+1))-(villain.agility+(rand()%7+1));
                  if(i>villain.agility)
                  {
                       printf("You escaped from the %s!\n\n",name);
                       readkey();
                       break;
                  }
                  else
                  {
                       printf("You tried to run away from the %s, but couldn't.\n\n",name);
                       //i=(villain.agility+(rand()%10+1))+hero.level;
                       i=(villain.attack+(rand()%10+1)-(hero.defense+(rand()%3+1)+hero.armor_bonus));
                       if(i>0)
                       {
                                i=(rand()%25+1); //Determines the enemies chance of getting a critical.  If its random-number-assisted luck is greater than your random-number assisted luck, then you land a critical.
                                if(i==5)       //If the enemy lands a critical, the amount of damage is increased because your strength is multiplied by 2.
                                {
                                        damage=((villain.attack*2)+(rand()%10+1))-((hero.defense+(rand()%3+1)+hero.armor_bonus));
                                        if(damage<=0)
                                        printf("The %s just missed you!\n\n",name);
                                        if(damage>0)
                                        {
                                                hero.hp-=damage;
                                                printf("POW!  The %s landed a critical on you and caused %i damage\n\n",name,damage);
                                                if(hero.hp<=0)
                                                {
                                                        printf("You were killed by the %s, Game Over.",name);
                                                        readkey();
                                                        cls();
                                                        exit(0);
                                                }
                                        }
                                }
                                if(i!=5)
                                {
                                        damage=(villain.attack+(rand()%15+1))-(hero.defense+(rand()%3+1)+hero.armor_bonus);
                                        if(damage<=0)
                                        printf("The %s just missed you!\n\n",name);
                                        if(damage>0)
                                        {
                                                hero.hp-=damage;
                                                printf("The %s hit you and caused %i damage.\n\n",name,damage);
                                                if(hero.hp<=0)
                                                {
                                                        printf("You were killed by the %s, Game Over.",name);
                                                        readkey();
                                                        cls();
                                                        exit(0);
                                                }

                                        }
                                }
                       }
                       else
                              printf("The %s just missed you!\n\n",name);
                  }
                }

           }
          cls();
        }

           
show_status()
       {
                cls();
                printf("Level: %i\n",hero.level);
                printf("HP: %i/%i\n",hero.hp,hero.hp_max);
                printf("Attack: %i\n",hero.attack);
                printf("Defense: %i\n",hero.defense);
                printf("Agility: %i\n",hero.agility);
                printf("Experience: %i/%i\n",hero.exp,hero.level_up);
                printf("Denarii: %i\n",hero.gold);
                printf("\nPress any key to return to the map.");
                readkey();
                if(key[KEY_ESC])
                {
                        cls();
                        exit(0);
                }
                cls();
       }
use_item()
          {
                  int y_coord=0;
                  int temp; // Don't need to set this to anything right now, it's given a value in the switch case comparisons.
                  char s;
                  
                  for(;;)
                  {
                        cls();
                        printf("Medical Herbs: %i\n",hero.medical_herbs);
                        printf("Medical Berries: %i\n",hero.medical_berries);
                        locate(0,24);
                        printf("Use which item?  Press Esc to return to menu.");
                        locate(20,y_coord);
                        printf("<----");
                        s=readkey();
                        if(key[KEY_UP] && y_coord>0)
                                    y_coord--;
                        if(key[KEY_DOWN] && y_coord<1)
                                    y_coord++;
                        if(key[KEY_ENTER]) // here's the meat of item usage, a select case comparison follows to determine the type of item based on the value of y_coord
                        {
                              switch(y_coord)
                              {
                                    case 0: // If it's a medical herb, which you can use in game mode...
                                         if(hero.medical_herbs==0) // First, check to see if you don't have any medical herbs...
                                         {
                                             printf("You don't have any medical herbs.");
                                             readkey();
                                             break;
                                         }
                                         if(hero.hp>=hero.hp_max) // If you're at or above your maximum HP...
                                         {
                                             printf("You're already at full health.\n");
                                             readkey();
                                             break;
                                         }
                                         temp=hero.hp_max-hero.hp; // Find out how much damage there is...
                                         if(temp<20) // If there's less damage than the maximum amount that a medical herb can fix...
                                         {
                                             hero.hp+=temp; // Increment the HP by the amount of damage
                                             cls();  // Clear the screen
                                             printf("Your HP is now %i/%i.",hero.hp,hero.hp_max); // Display the new HP
                                             hero.medical_herbs--;
                                             readkey();  // Let the player see it
                                             break;  // Go back to the item usage menu.
                                         }
                                         if(temp>=20)  // If there's 20 or more damage (the maximum amount a medical herb can fix)...
                                         {
                                             hero.hp+=20; // Increment the HP by 20
                                             cls();       // Clear the screen
                                             printf("Your HP is now %i/%i",hero.hp,hero.hp_max);  // Display the new HP
                                             hero.medical_herbs--;
                                             readkey();   // Let the player see it
                                             break;       // Go back to the item usage menu.
                                         }
                                         readkey();
                                         break;
                                    case 1: // If it's a medical berry, which you can use in game mode...
                                         if(hero.medical_berries==0) // First, check to see if you don't have any medical herbs...
                                         {
                                             printf("You don't have any medical berries.");
                                             readkey();
                                             break;
                                         }
                                         if(hero.hp>=hero.hp_max) // If you're at or above your maximum HP...
                                         {
                                             printf("You're already at full health.\n");
                                             readkey();
                                             break;
                                         }
                                         temp=hero.hp_max-hero.hp; // Find out how much damage there is...
                                         if(temp<40) // If there's less damage than the maximum amount that a medical herb can fix...
                                         {
                                             hero.hp+=temp; // Increment the HP by the amount of damage
                                             cls();  // Clear the screen
                                             printf("Your HP is now %i/%i.",hero.hp,hero.hp_max); // Display the new HP
                                             hero.medical_berries--;
                                             readkey();  // Let the player see it
                                             break;  // Go back to the item usage menu.
                                         }
                                         if(temp>=40)  // If there's 40 or more damage (the maximum amount a medical herb can fix)...
                                         {
                                             hero.hp+=40; // Increment the HP by 40
                                             cls();       // Clear the screen
                                             printf("Your HP is now %i/%i",hero.hp,hero.hp_max);  // Display the new HP
                                             hero.medical_berries--;
                                             readkey();   // Let the player see it
                                             break;       // Go back to the item usage menu.
                                         }
                                         break;
                              }
                        }
                        if(key[KEY_ESC])
                           break;
                  }
          }
inventory()
           {
                char armor_name[20];
                char weapon_name[20];
                for(;;)
                {
                        cls();
                        printf("You have:\n\n");
                        printf("Medical Herbs: %i\n",hero.medical_herbs);
                        printf("Medical Berries: %i\n",hero.medical_berries);
                        printf("\n\n\nOptions: (U)se, View (E)quipment, Exit (Escape)");
                        readkey();
                        if(key[KEY_ESC])
                                  break;
                        if(key[KEY_U])
                              use_item();
                        if(key[KEY_E])
                        {
                              cls();
                              // Figure out what kind of weapon and armor you have
                              if(hero.weapon_bonus==3)
                                           strcpy(weapon_name,"Blunted Sword");
                              if(hero.weapon_bonus==6)
                                           strcpy(weapon_name,"Damascus Sword");
                              if(hero.weapon_bonus==9)
                                           strcpy(weapon_name,"Wizard's Sword");
                              if(hero.weapon_bonus==12)
                                           strcpy(weapon_name,"Eastern Sword");
                              if(hero.armor_bonus==1)
                                           strcpy(armor_name,"Rusted Armor");
                              if(hero.armor_bonus==4)
                                           strcpy(armor_name,"Damascus Armor");
                              if(hero.armor_bonus==7)
                                           strcpy(armor_name,"Wizard's Armor");
                              if(hero.armor_bonus==10)
                                           strcpy(armor_name,"Eastern Armor");
                              printf("Weapon: %s\n\n",weapon_name);
                              printf("Armor: %s\n\n",armor_name);

                              printf("You have:\n\n");
                              printf("%i Small Pilums",hero.pilums);
                              readkey();
                        }
                }
           }
int load_map(int i)
     {
        // 0 = map_t.txt: starts up after introduction
        // 1 = map_00.txt: title screen
        // 2 = last screen?
        if(i==0)
        {
             bloing=fopen("map_t.txt","r");
             if(bloing==NULL)
             {
                   cls();
                   printf("Memory errors!  Abandon program!  Women and integers first!");
                   readkey();
                   exit(0);
             }
             fgets(map_array_a,2001,bloing);
             fclose(bloing);
        }
        if(i==1)
        {
             bloing=fopen("map_00.txt","r");
             if(bloing==NULL)
             {
                   printf("Memory errors! Abandon program! Women and integers first!");
                   readkey();
                   exit(0);
             }
             fgets(map_array_a,2001,bloing);
             fclose(bloing);
        }
        if(i==2)
        {
             bloing=fopen("map_03.txt","r");
             if(bloing==NULL)
             {
                   printf("Memory errors! Abandon program! Women and integers first!");
                   readkey();
                   exit(0);
             }
             fgets(map_array_a,2001,bloing);
             fclose(bloing);
        }
        return(i);
     }
save_game()
    {
        FILE *handel;
        char w[200];
        char *boing;
        int v,esc_check;
        v=0;

        cls();
        for(;;)
        {
                printf("\nWhat do you want to call this file?\n\n");
                esc_check=get_string(w,LENGTH);
                if(esc_check==YUP)
                {
                        cls();
                        break;
                }
                strcat(w,".dat");   // Add a .dat extension to it
                boing=(char *)malloc(strlen(w+1));  // Malloc a pointer to the correct size
                strcpy(boing,w);  // Copy the string to the pointer
                handel=fopen(boing,"r"); // Open the file with that name, it's in "a" mode so that the file is created
                if(handel==NULL) // Check for a null pointer error
                {
                        fclose(handel);
                        handel=fopen(boing,"w");
                        fwrite(&hero,sizeof(hero),1,handel);
                        fclose(handel);
                        printf("\n\nGame saved\n");
                        readkey();
                        break;
                }
                if(handel)
                {
                        for(;;)
                        { //Check to see if it already exists
                                  printf("\n\n%s already exists. Overwrite[Y/N]?\n",boing);
                                  readkey();
                                  if(key[KEY_Y])        // Aw, go ahead and overwrite it
                                  {       // So this is what is means to be a "hero", to be a "hero" is to be a really big C struct
                                          fclose(handel);
                                          handel=fopen(boing,"w");
                                          fwrite(&hero,sizeof(hero),1,handel); // Write the struct to disk
                                          fclose(handel);  // Close the file pointer
                                          printf("\nGame saved\n");
                                          v=30000;
                                          readkey();
                                          break;
                                  }
                                  if(key[KEY_N])
                                  {
                                        fclose(handel);
                                        break;
                                  }
                        }
                }
                if(v=30000) break;

        }
    }
load_game()
    {
        FILE *fiddler;
        char w[200];
        char *car;
        int esc_check;

        cls();
        for(;;)
        {
              printf("\nWhich file do you want to load?\n\n");
              esc_check=get_string(w,LENGTH);
              if(esc_check==YUP)
                      return(esc_check);
              strcat(w,".dat");
              car=(char *)malloc(strlen(w+1));
              strcpy(car,w);
              fiddler=fopen(car,"r");
              if(!fiddler)
              {
                        fclose(fiddler);
                        cls();
                        printf("\nThat file doesn't exist\n");
              }
              if(fiddler)
              {
                        fread(&hero,sizeof(hero),1,fiddler);
                        printf("\n\nGame loaded  Press any key to continue");
                        fclose(fiddler);
                        readkey();
                        break;
              }
        }
        return(esc_check);
    }
startup()
    {
        int a;
        int esc_check;
        for(;;)
        {
                cls();
                hero.map=load_map(1);
                printf("%s",map_array_a);
                a=readkey();
                if(key[KEY_S])
                {

                        cls();
                        printf("I, Basilius, am the last hope of Rome.");
                        readkey();
                        cls();
                        printf("The date is August 20, 410 AD.  For 10 years, the Western Roman Empire has been at war with the Visigoths and their king, Alaric.");
                        readkey();
                        cls();
                        // When the Goths came streaming from Illyricum in 400 AD,
                        // I was one of the generals under the command of Stilicho,
                        // Master-General of the armies of the Western Empire, who spent
                        // 4 long years fending off that invasion, which concluded
                        // in the battle of Pollentia, where I led the band of several thousand
                        // legionnaries which destroyed a significant part of Alaric's infantry and,
                        // her bodyguards killed or severely injured, captured Alaric's wife.
                        // However, with his cavalry still mostly intact, Alaric was planned to
                        // pillage the rich town of Tuscany before retreating to Illyricum.  But with
                        // his wife as a bargaining chip, Stilicho, the Emperor Honorius having no
                        // compotence for diplomacy, convinced Alaric to sign a peace treaty that
                        // bribed Alaric off and kept him as a servant of the Western Empire.
                                                                                                                                /*.*/ /*!and*/      /*.*/
                        printf("For 3 years, we fought an uphill battle to prevent the Goths from invading the \nItalian peninsula.  We nearly fell.  Then Alaric was humiliated at the battle ofPollentia, where we bought a few years peace, mostly thanks to the efforts of\nStilicho, Master-General of the armies of the West, and myself, the only other \ncompetent general.");
                        readkey();
                        // 4 years hence, I still have little clue as to why Olympius, the Emperor's
                        // chief advisor (and therefore the one person who had as much influence
                        // over Honorius as Stilicho) plotted to kill the late Master-General.
                        // He has consistently gone out of his way to undermine our defences against
                        // a barbarian invasion.  I only know that the scoundrel convinced Honorius
                        // that Stilicho was planning to assassinate him and place the son of the
                        // Master-General, Eucherius, on the throne.
                        // In his fourth and last appearance before the Senate and the people of
                        // Rome, Honorius proclaimed Stilicho an enemy of the Empire and issued a
                        // warrant for his immediate execution.  After a long train of murder,
                        // treason, and sacreilege, Stilicho was lured out of the Vatican and
                        // decapitated just short of 2 years ago.

                        // "The troops, who still assumed the name and prerogatives of the Roman legions, were exasperated by the partial affection of Stilicho for the barbarians"
                        cls();                                                                                                                                                                                                                                                                                                                                                                                                                                             /* What does the fact that he's an indolent have to do with his bigotry? */
                        printf("But, 5 years after we bribed Alaric off, Olympius, that despicable advisor to \nHonorius, tricked the Emperor into ordering Stilicho's execution, claiming that Stilicho was planning to assassinate the Emperor.  After a long train of murdersand treason ordered by Honorius and executed by Olympius among numerous \nco-conspirators, Stilicho was lured out of the Vatican and killed just short of two years ago.  Furthermore, Honorius, although an indolent all his life, had a deep hatred for those not of the Orthodox faith.  Shortly after the death of \nStilicho, Honorius executed the families of the pagan soldiers of the Empire.  \nTotalling nearly 3,000, they had been held in the strongholds of Italy as part \nof a system dating back to the reign of the Emperor Constantine.  The death of \nStilicho, and the death of their wives and children prompted the defection of \n30,000 not only pagan, but Orthodox, Arian, and Jewish troops, with whom we \ncould have certainly kept the Goths at bay, to the camp of Alaric.");
                        readkey();
                        cls();
                        printf("Honorius' motives are obvious enough, but I cannot tell what Olympius' motives \nare.  On the face of it he is the first to display any sign of devout \nspirituality and zeal for the Empire, and yet he has taken every opportunity to not only undermine our defenses, but to batter his wife, Placidia.");
                        readkey();
                        cls();
                        printf("With the legions occupying the Italian peninsula almost entirely defected to theVisigoths, Alaric had the perfect chance of breaking the treaty and sacking \nRome.  One does not have to spend long in the aristocracy to acquire certain \nconnections, if one desires them.  I am told that Alaric had entertained this \nidea ever since the death of Stilicho, and also since the Emperor had neglected to pay the 4,000 pounds of gold required under the terms of the peace treaty, \nbut certain Gothic nobles were unwilling to commit to another campaign.  Yet \nwhen 30,000 former Roman troops came to his camp clamoring for the blood of the Emperor, Alaric persuaded the defected Romans to forgo a hopeless attack on the fortress of Ravenna, where the Emperor had moved after the first invasion, and \ngo south to Rome, where most of the native aristocrats had supported the Emperor's actions, and more importantly, where there was wealth beyond their dreams.");
                        readkey();
                        cls();
                        printf("First, Alaric's troops surrounded the City and cut it off from the Tiber, where,the roads blocked by the Visigoths, the City would have imported its food \nsupply.  It would seem that he planned to starve most of the City's inhabitants to death, then his troops would sack the City and take any survivors as slaves. I was in Rome at the time, there was enough food circulating in the markets and public granaries to last a few weeks, then...");
                        readkey();
                        cls();
                        printf("...some of the less advantaged in the City, and then the more advantaged, began to kill...harvest others to live.");
                        readkey();
                        cls();
                        printf("My wife, Livia, she...");
                        readkey();
                        cls();
                        printf("...");
                        readkey();
                        cls();
                        printf("Soon after, the Senate was so desparate to lift the blockade that they voted to send me here to Ravenna to negotiate terms for lifting the siege.  I had retiredfrom the military and become a Senator shortly after \nthe first Visigoth invasion.");
                        readkey();
                        /*
                        cls();
                        printf("Alaric is far from the common man's picture of a barbarian, the unreasoning brute who has no respect for the civilised world.  He is a cunning diplomat, as well as");
                        readkey();
                        if(key[KEY_ESC]) // Remember to delete this comparison when I'm through checking for spacing and spelling errors.
                        {
                                cls();
                                exit(0);
                        }
                        cls();
                        printf("But those conditions would only lift the siege of Rome, for the Visigoths to withdraw from Italy, the treaty had to be brought to Ravenna for approval by the Emperor.");
                        readkey();
                        if(key[KEY_ESC]) // Remember to delete this comparison when I'm through checking for spacing and spelling errors.
                        {
                                cls();
                                exit(0);
                        }
                        cls();
                        printf("The negotiations were doomed the moment the moved to Ravenna.  You see, one of Alaric's conditions for withdrawal from Italy was complete control of the province of Rhaetia, he no doubt promised this to certain of the pagan Gothic nobles in his court, as certain oak groves in that region have a deep religious value to the Goths.  Honorius was outraged that Alaric would indulge his pagan troops so, and at one point the arguments between those two became so heated at one point that Alaric struck Honorius straight across his upper jaw.  Honorius might have tried to grab a sword and kill Alaric had I not intervened.");
                        readkey();
                        if(key[KEY_ESC]) // Remember to delete this comparison when I'm through checking for spacing and spelling errors.
                        {
                                cls();
                                exit(0);
                        }
                        cls();
                        printf("Alaric made an attempt to intimidate Honorius: a mere two days after the talks moved to Ravenna, Alaric staged a coup in Rome and installed a puppet, Attalus.  Yet while Attalus was supported by Alaric's troops in Italy, there were several Imperial governors that were unwilling to accept the change in Emperors, the most powerful among them being Heraclian, count of Africa.  Attalus did send a large body of Visigoth soldiers to deal with him, and that was the last mistake of his reign of 3 weeks.  Not only did Heraclian's troops defeat the Visigoth troops, but Honorius, practically walled up in the fortress of Ravenna, received a reinforcement of several Huns from the Eastern Empire.  With that number, Honorius was able to oust and later execute Attalus.");
                        readkey();
                        if(key[KEY_ESC]) // Remember to delete this comparison when I'm through checking for spacing and spelling errors.
                        {
                                cls();
                                exit(0);
                        }
                        cls();
                        printf("For the last two weeks peace talks continued between Alaric and Honorius.  However, they have gone nowhere, today Alaric made a serious threat to sack Rome unless Honorius declared him governor of Rhaetia by 3 hours to midnight (the date is August 20, 410 AD).  The water clock has just struck that time, the Emperor has made no such announcement, and Alaric has just now left Ravenna.");
                        readkey();
                        if(key[KEY_ESC]) // Remember to delete this comparison when I'm through checking for spacing and spelling errors.
                        {
                                cls();
                                exit(0);
                        }
                        cls();
                        printf("However, the Eternal City does have one last chance that Alaric, I pray, has no knowledge of.  The African troops sent by Heraclian have not left the Italian peninsula, as I have gone to great lengths to make Alaric think.  A force to match the Visigoth army is scattered in and around Rome, yet they under orders to stay undercover until I arrive.  With about 3 hours to reach the City before the Visigoths arrive, I have no time to lose.");
                        // For the threat Alaric poses is not confined to the safety and security of the former capital, in its entire history, the Eternal City has never been taken by a foreign soverign.  Should that happen, the image of a great and terrible Roman Empire would collapse under its own weight, along with the West.
                        readkey();
                        */
                        cls();
                        printf("Although I was able to convince Alaric to allow the free flow of goods into the City, the peace talks failed in large part thanks to the arrogance of the \nEmperor and Olympius.  Just this afternoon, Alaric left Ravenna, and as I speak,the Visigoth army should be about 3 hours march from Rome.");
                        readkey();
                        if(key[KEY_ESC])
                        {
                                cls();
                                exit(0);
                        }
                        cls();
                        printf("Fortunately, I, the Eastern Emperor Arcadius, and Heraclian, the count of \nAfrica, have, I pray, convinced Alaric that a force to match his army has gone \nto Africa, while it is really scattered in and around the City.  However, they \nare under orders not to deploy until my arrival.  There is a stable just outsidemy villa, but even on horseback, time is critical.");
                        readkey();
                        if(key[KEY_ESC])
                        {
                                cls();
                                exit(0);
                        }
                        hero.map=load_map(0);
                        cls();
                        break;
                }
                if(key[KEY_L])
                {
                        esc_check=load_game();
                        if(esc_check!=YUP)
                        {
                                 hero.map=load_map(hero.map);
                                 break;
                        }
                        else
                            continue;
                }
                if(key[KEY_C])
                {
                        cls();
                        printf("Cursor keys - Up, Down, Left, and Right\n\n");
                        printf("Q - Quit\n\n");
                        printf("S - Status\n\n");
                        printf("W - Save\n\n");
                        printf("L - Load (during the game)\n\n");
                        printf("Enter - Open chests\n\n");
                        printf("I - Inventory\n\n\n\n");
                        printf("Press any key to return");
                        readkey();
                }
                if(key[KEY_ESC])
                {
                        cls();
                        exit(0);
                }
        }
    }
int main()
    {
        srand((unsigned)(time)(NULL)); // Create a random number seed

        allegro_init();         // Start up allegro
        install_keyboard();     // Install the keyboard


        hero.hp=100;                         // Hit Points
        hero.hp_max=100;                     // This is programmed in so that the character's HP wont go above 100
        hero.attack=12;                      // Attack value
        hero.defense=10;                     // Defense value
        hero.agility=11;                     // Agility value
        hero.weapon_bonus=3;                 // Attack bonus caused by Basilius' weapon.
        hero.armor_bonus=1;                  // Armor bonus caused by his armor.
        hero.exp=0;                          // Experience points
        hero.xpos=25;                        // X position at the start of the game
        hero.ypos=9;                         // Y position at the start of the game
        hero.gold=0;                         // Gold!
        hero.level=1;                        // Basilius' level
        hero.level_up=50;                    // How many experience points you need to level up
        hero.level_up_number=1;              // The number by which Basilius' stats are increased when he levels up
        hero.pilums=5;                       // Ancient Roman spear, used as a special weapon for boss fights and last resort weapons if your HP is really low.
        hero.pilum_bonus=(hero.attack*2);    // This is put into the equation for pilum use, making its effect near equal to the damage caused by a critical.
        hero.medical_herbs=1;                // How many medical herbs you have at startup
        hero.medical_berries=1;              // How many medical berries you have at startup

        
        if(treasure_chests[0]!=CLOSED_TREASURE_CHEST)
                                                     exit(0);

        cls();  // Clear any gobbledegook on the screen (probably not necessary now that it's a runnable .exe, but necessary to clear the RHIDE junk while I'm still editing it
        startup();
        // 0 = map_t.txt: starts up after introduction
        // 1 = map_00.txt: title screen
        // 2 = last screen?
//        set_screen(13);

        for(;;)
        {
// Beginning of comparisons for moving between maps
                if(hero.map==0)
                {
                        if(hero.xpos==0)
                        {
                              hero.map=load_map(1);
                              hero.xpos=77;
                              hero.ypos=10;
                        }
                }
                if(hero.map==1)
                {
                        if(hero.xpos==78)
                        {
                              hero.map=load_map(0);
                              hero.xpos=1;
                              hero.ypos=10;
                        }
                }
// End of comparisons for moving between maps
                locate(0,0);
                printf("%s",map_array_a);
                /*for(y=4;y<=19;y++)
                {
                        for(x=5;x<=34;x++)
                        {
                              locate(x,y);
                              printf("%c",map_array_a[map_index]);
                              map_index++;
                        }
                }
                map_index=0;*/
                if(hero.map==0)  // If on the first map...
                {
                        if(treasure_chests[0]==CLOSED_TREASURE_CHEST) // If the treasure chest hasn't been opened yet...
                        {
                              locate(22,8);  // Find the spot...
                              printf("%c",CLOSED_TREASURE_CHEST); // Print the closed treasure chest char
                        }
                        if(treasure_chests[0]==OPEN_TREASURE_CHEST)  // If the treasure chest has been opened...
                        {
                              locate(22,8);  // Find the spot...
                              printf("%c",OPEN_TREASURE_CHEST);  // Print the opened treasure chest char
                        }
                }
                // These next three lines have to be after the treasure chest comparisons or the cursor will be just after the chest character
                locate(hero.xpos,hero.ypos); // move the cursor to the player position
                printf("%c",BASILIUS); // Print the player char
                locate(0,0); // Home the cursor again, so that it doesn't get in the way

                for(;;)
                {
                        c=readkey(); // Wait for input
                        if(key[KEY_ESC]) // Quit option
                        {
                                        cls();   // Clear screen (see head.h)
                                        exit(0); // Quit
                        }
                        if(key[KEY_UP]) // Go up
                        {
                                // Start of collision detection routine
                                // 1. Decrement the player's y variable by 1 (equivalent to going up one space on the screen)
                                // 2. Check the new player position to see if there's something other than the blank space character ("#define BLANK 0x20")
                                // 3. If there's no blank space in that direction, you don't move (the change in coordinates is reversed)
                                hero.ypos--; // 1.
                                locate(hero.xpos,hero.ypos); // 2.
                                if(readchar()!=BLANK)  // both lines 3.
                                          hero.ypos++; //
                                // End of collision detection routine
                                // Start of random battle routine
                                // 1. Generate a random number between 0 and 19
                                // 2. If you get 10, call the battle function (the section variable is an indicator so that I can program tougher enemies as I progress through the game.
                                chance=rand()%20; // 1.
                                if(chance==10)
                                             battle(section);
                                break;
                        }
                        if(key[KEY_LEFT]) // For documentation, see "if(key[KEY_UP])"
                        {
                                hero.xpos--;
                                locate(hero.xpos,hero.ypos);
                                if(readchar()!=BLANK)
                                          hero.xpos++;
                                chance=rand()%20;
                                if(chance==10)
                                             battle(section);
                                break;
                        }
                        if(key[KEY_DOWN]) // For documentation, see "if(key[KEY_UP])"
                        {
                                hero.ypos++;
                                locate(hero.xpos,hero.ypos);
                                if(readchar()!=BLANK)
                                          hero.ypos--;
                                chance=rand()%20;
                                if(chance==10)
                                             battle(section);
                                break;
                        }
                        if(key[KEY_RIGHT]) // For documentation, see "if(key[KEY_UP])"
                        {
                                hero.xpos++;
                                locate(hero.xpos,hero.ypos);
                                if(readchar()!=BLANK)
                                          hero.xpos--;
                                chance=rand()%20;
                                if(chance==10)
                                             battle(section);
                                break;
                        }
                        if(key[KEY_I])  // Call to inventory function in game mode
                        {
                                inventory();
                                break;
                        }
                        if(key[KEY_W]) // Save game, w is for Write saved game file to hard drive
                        {
                                save_game();
                                break;
                        }
                        if(key[KEY_L]) // Load game
                        {
                                load_game();
                                break;
                        }
                        if(key[KEY_S]) // Status display
                        {
                                show_status();
                                break;
                        }
                        if(key[KEY_X]) // Displays position, meant for figuring out XY position for scripting
                        {
                                cls();
                                printf("X Position: %i\n\n",hero.xpos);
                                printf("Y Position: %i",hero.ypos);
                                readkey();
                                break;
                        }
                        if(key[KEY_ENTER]) // Comparison for all events requiring pressing Enter (certain cutscenes, treasure chests, etc.)
                        {
                                if(hero.map==0) // Comparison for all events in first game map
                                {
                                        // The next four comparisons determine if the player 1 y coordinate under or above one of the chests on the map, or if the player is 1 x coordinate to the left or right of one of the chests on the map
                                        // The chest coordinates are at (22,8)
                                        // If you're 1 y coordinate down and it's closed                                     if you're one y coordinate up and it's closed                                        if you're one x coordinate to the left and it's closed                          if you're one x coordinate to the right and it's closed
                                        if((hero.xpos==22 && hero.ypos==9 && treasure_chests[0]==CLOSED_TREASURE_CHEST) || (hero.xpos==22 && hero.ypos==7 && treasure_chests[0]==CLOSED_TREASURE_CHEST) || (hero.xpos==21 && hero.ypos==8 && treasure_chests[0]==CLOSED_TREASURE_CHEST) || (hero.xpos==23 && hero.ypos==8 && treasure_chests[0]==CLOSED_TREASURE_CHEST))
                                        {
                                                cls();
                                                printf("Found a Medical Herb!"); //Well, tell the player already!
                                                hero.medical_herbs++; // Increment the number of medical herbs  (this may be changed when I finish the inventory() function)
                                                readkey(); // Same as getch(), remember?
                                                treasure_chests[0]=OPEN_TREASURE_CHEST;  // Mark the first treasure chest in the game as open
                                                break;
                                        }
                                }
                        }
                }
        }
    }
END_OF_MAIN();
