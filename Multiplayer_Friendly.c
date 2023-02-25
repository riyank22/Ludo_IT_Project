//program for ludo (terminal based)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int i,j;
void display(int); //for displaying (giving input the four char arrays)

void area_finder(int, int,char); //value, initial kingdomn(kingdom number and postion)

void area_g(int, char, int); //navigation function in green kingdom
void area_r(int, char, int); //navigation function in red kingdom
void area_b(int, char, int); //navigation function in blue kingdom
void area_y(int, char, int); //navigation function in yellow kingdom

void homelock_manipulator(int); //for manipulating the homelock strings
void player(int); //game console

int dice(void); //dice

int tokens[16][5]; //coords of tokens (sequence/area/location/colourcode/coor symbol/coords x/ coord y)
int homecount[4]={0,0,0,0}; //declaring count of homecount tokens (won tokens) (g,r,b,y)
int choices[4]={0,0,0,0}; //showing no. of choices (g,r,b,y)

char *gr_ptr, *bl_ptr, *re_ptr, *ye_ptr;//pointers pointing to the area arrays
char *homelock_ptr; //pointer pointing to the arrays storing data for homelock ptr.
    
int main(void)
{
    //defining areas
    char green_area[6][3],blue_area[6][3],red_area[3][6], yellow_area[3][6];
    gr_ptr=&green_area[0][0];bl_ptr=&blue_area[0][0];re_ptr=&red_area[0][0];ye_ptr=&yellow_area[0][0];

    for(i=0;i<18;i++)
    {
        *(gr_ptr+i)=*(bl_ptr+i)=*(re_ptr+i)=*(ye_ptr+i)='_';//assigning the blank spaces.
    }

    for(i=0;i<16;i++) //feeding sequence data
    {
        tokens[i][0]=i+1;
    }

    for(i=0;i<4;i++) //feeding colourcode
    {
        tokens[i][3]=1;
        tokens[i+4][3]=2;
        tokens[i+8][3]=3;
        tokens[i+12][3]=4;
    }

    for(i=0;i<4;i++) //feeding coloursymbol
    {
        tokens[i][4]=(int)'*';
        tokens[i+4][4]=(int)'+';
        tokens[i+8][4]=(int)'/';
        tokens[i+12][4]=(int)'?';
    }

    char homelock [4][4]={ //assigning sybmols
                            {"****"},
                            {"++++"},
                            {"////"},
                            {"????"}
                         };
    homelock_ptr=&homelock[0][0]; //mapping pointer

    system("cls"); //for windows users replease clear to cls

    int k=0;

    while((homecount[0]!=4 && homecount[1]!=4 && homecount[2]!=4) || (homecount[1]!=4 && homecount[2]!=4 && homecount[3]!=4)
    || (homecount[2]!=4 && homecount[3]!=4 && homecount[0]!=4) || (homecount[3]!=4 && homecount[0]!=4 && homecount[1]!=4))
    {
        player(k%4+1);
        k++;
    }
    system("cls");
    display(0);
}

void player(int colourcode) //game event handler
{
    bool flag=1;

    printf("Player %d's turn\n", colourcode);
    colourcode--;
    char dummy; //for handling enter of getchar
    int user_choice=1; //default choice of user
    int value; //dice value

    int unique_id=4*(colourcode) + (user_choice-1); //storing unique value

    if (homecount[colourcode]>=4) //if the player has won
    {
        goto end;
    }

    value=dice(); //getting random dice value

    printf("\nLUDO GAME (TERMINAL BASED)\n");

    display(colourcode+1); //displaying board

    printf("PRESS ENTER TO CONTINUE.");
    dummy=getchar();

    if(value==6 && choices[colourcode]+homecount[colourcode]<5) //terminating conditon for inreasing choice
    {
        choices[colourcode]++; //max choices =4
    }

    /*for(int i=0;i<16;i++)
    {
        printf("\nThe Coords for %d are %d %d", tokens[i][0], tokens[i][1], tokens[i][2]); //for debuging process
    }*/ //for debugging

    printf("\nThe Dice Value is %d\n", value);

    if(choices[colourcode]>0)
    {
        if(choices[colourcode]>1||homecount[colourcode]>1)
        {
            begin:
            printf("Enter the choice: ");
            scanf("%d", &user_choice);
            flag=0;

            if(user_choice<=homecount[colourcode])
            {
                printf("\nThis token is already in the home.\n");
                goto begin;
            }

            else if(user_choice>choices[colourcode])
            {
                printf("\nThis token is in homelock.\n");
                goto begin;
            }

            unique_id=4*(colourcode) + (user_choice-1);
        }

/*if the player gets dice value to 6 and she/he wishes to not to put a token out of homelock
then decreasing the choice.*/

        if(value==6 && user_choice!=homecount[colourcode]+choices[colourcode]) 
        {
            choices[colourcode]--;
        }

        else if(value==6 && choices[colourcode]!=5) //bringing the token out of homelock
        {
            tokens[unique_id][1]=colourcode+1; //assigning the spawn area to new token
            tokens[unique_id][2]=14; //assigning the spawn location to new token
            homelock_manipulator(tokens[unique_id][3]-1);
            value=0;
        }

        //continuing the game
        area_finder(value, unique_id, tokens[unique_id][4]); //value, sequence, colour symbol
    }   

        if(choices[colourcode]<2 && flag) //for only one choice
        {
        printf("\nPRESS ENTER TO CONTINUE.");
        dummy=getchar();
        }

         end: //if the player had won //multiplayer

        system("cls");
}

//based upon no of tokens out of hoemlock, changing the array of homelock
void homelock_manipulator(int colourcode)
{
    switch (4-homecount[colourcode]-choices[colourcode]) // no of homelock_tokens colorcode(0,1,2,3)
    {
    case 0:
        *(homelock_ptr+4*colourcode)='_';
        break;

    case 1:
        *(homelock_ptr+4*colourcode+1)='_';
        break;

    case 2:
        *(homelock_ptr+4*colourcode+2)='_';
        break;
    
    case 3:
        *(homelock_ptr+4*colourcode+3)='_';
        break;
    
    default:
        break;
    }
}

//identifying location(area) of token from its area and calling the respective area function
void area_finder(int value, int user_choice,char c)
{
    switch(tokens[user_choice][1])
    {
        case 1:
        area_g(value,c,user_choice);
        break;

        case 2:
        area_r(value,c,user_choice);
        break;

        case 3:
        area_b(value,c,user_choice);
        break;

        case 4:
        area_y(value,c,user_choice);
        break;
    }
}

void area_g(int value, char c, int user_choice)
{
    int temp=tokens[user_choice][2]; //temp for clearing past place
    tokens[user_choice][2]+=value; //calculating the final position
    int x=tokens[user_choice][2]; //taking x as a replica of token[user_choice][2]

    if(x>18) //checking the value eligible for next area
    {
        *(gr_ptr+(18-temp)*3)='_';//clearing past record

        value=x-18; //finding the coordinates to move in next kingdom

        tokens[user_choice][2]=value; //assigning the coords of the next kingdom

        value=0; //as coordinates are already assigned, putting value = 0
        
        tokens[user_choice][1]++;

        area_r(value, c, user_choice);
        goto end;
        //to move to next kingdom
    }

    //moving pice to new location
    if(x<=6) //for lane 0
    {   
        *(gr_ptr+2+3*(x-1))=c;
    }

    else if(x==7) //for lane 1
    {
        *(gr_ptr+1+3*5)=c;
    }

    else if(tokens[user_choice][3]==1 && (x<13 || temp<13)) //for home lane
    {
        if(x==13)  //condition for reaching homecount
        {
            homecount[0]++; //increasing count by 1
            tokens[user_choice][1]=0;
            tokens[user_choice][2]=0;
        }

        else if(x>13) //if value is larger then ignoring the increament
        {
            x=temp;
            value=0;
        }

        else //for moving in home lane
        {
        *(gr_ptr+(12-x)*3+1)=c;
        }
    }

    else //for lane 2
    {
        if(x>7 && x<13)
        {
            x+=5;
        }

        else if(x==13 && temp==7)
        {
            x=18;
        }
        *(gr_ptr+(18-x)*3)=c;
    }

    tokens[user_choice][2]=x;

    end:
    //clearing previous location
    //for finding temp coordinate, we have used the same approcah as done to find x

    if(value!=0)
    {
    if(temp<=6) //for lane 1
    {   
        *(gr_ptr+2+3*(temp-1))='_';
    }

    else if(temp==7) //for value is equal to 7
    {
        *(gr_ptr+1+3*5)='_';
    }

    else if(tokens[user_choice][3]==1 && temp<13) //for home lane
    {
        *(gr_ptr+(12-temp)*3+1)='_';
    }

    else //for values between 13 to 18
    {
        if(temp>7 && temp<13)
        {
        temp+=5;
        }
        
        *(gr_ptr+(18-temp)*3)='_';
    }
    }
}

void area_r(int value, char c, int user_choice)
{
    int temp=tokens[user_choice][2];
    tokens[user_choice][2]+=value;
    int x=tokens[user_choice][2];

    if(x>18)
    {
        *(re_ptr+(temp-13))='_';//clearing past record

        value=x-18;

        tokens[user_choice][2]=value; //assigning the coords of the next kingdom;

        value=0;
        tokens[user_choice][1]+=1;
        area_b(value,c,user_choice);
        goto end;
        //to move to next kingdom
    }

    //moving pice to new location
    if(x<=6) 
    {   
        *(re_ptr+18-x)=c;
    }

    else if(x==7)
    {
        *(re_ptr+6)=c;
    }

    else if(tokens[user_choice][3]==2 && (x<13 || temp<13)) //for home lane
    {
        if(x==13)  //condition for reaching homecount
        {
            homecount[1]++;; //increasing count by 1
            tokens[user_choice][1]=0;
            tokens[user_choice][2]=0;
        }

        else if(tokens[user_choice][2]>13) //if value is larger then dumping the increament
        {
            x=temp;
            value=0;
        }

        else
        {
            *(re_ptr+x-1)=c;
        }
    }

    else
    {
        if(x>7 && x<13)
        {
            x+=5;
        }

        else if(x==13 && temp==7)
        {
            x=18;
        }

        *(re_ptr+(x-13))=c;
    }

    tokens[user_choice][2]=x;

    //clearing previous location

    end:

    if(value!=0)
    {
    if(temp<=6)
    {   
        *(re_ptr+18-temp)='_';
    }

    else if(temp==7)
    {
        *(re_ptr+6)='_';
    }

    else if(tokens[user_choice][3]==2 && temp<13)
    {
        *(re_ptr+temp-1)='_';
    }

    else
    {
        if(temp>7 && temp<13)
        {
            temp+=5;
        }
        *(re_ptr+temp-13)='_';
    }
    }
}

void area_b(int value, char c, int user_choice)
{
    int temp=tokens[user_choice][2];
    tokens[user_choice][2]+=value;
    int x=tokens[user_choice][2];

    if(x>18)
    {
        *(bl_ptr+3*temp-37)='_';//clearing past record

        value=x-18;
        tokens[user_choice][2]=value;
        value=0;
        tokens[user_choice][1]++;
        area_y(value, c, user_choice);
        goto end;
        //to move to next kingdom
    }

    if(x<=6) //moving pice to new location
    {   
        *(bl_ptr+18-(3*(x)))=c;
    }

    else if(x==7)
    {
        *(bl_ptr+1)=c;
    }

    else if(tokens[user_choice][3]==3 && (x<13 || temp<13))
    {
        if(x==13)  //condition for reaching homecount
        {
            homecount[2]++;; //increasing count by 1
            tokens[user_choice][1]=0;
            tokens[user_choice][2]=0;
        }

        else if(x>13) //if value is larger then dumping the increament
        {
            x=temp;
            value=0;
        }

        else
        {
        *(bl_ptr+1+(x-7)*3)=c;
        }
    }

    else
    {
        if(x>7 && x<13)
        {
        x+=5;
        }

        else if(x==13 && temp==7)
        {
            x=18;
        }

        *(bl_ptr+3*(x)-37)=c;
    }

    tokens[user_choice][2]=x;

    end: //for moving to next kingdom

    //clearing previous location    

    if(value!=0)
    {

    if(temp <= 6) //moving pice to new location
    {   
        *(bl_ptr+18-(3*temp))='_';
    }

    else if(temp == 7)
    {
        *(bl_ptr+1)='_';
    }

    else if(tokens[user_choice][3]==3 && temp<13)
    {
        *(bl_ptr+1+(temp-7)*3)='_';
    }

    else
    {
        if(temp>7 && temp<13)
        {
        temp+=5;
        }
        *(bl_ptr+3*temp-37)='_';
    }
    }
}

void area_y(int value, char c, int user_choice)
{
    int temp=tokens[user_choice][2];
    tokens[user_choice][2]+=value;
    int x=tokens[user_choice][2];

    if(x>18)
    {
        *(ye_ptr+30-temp)='_';

        value=x-18;
        tokens[user_choice][2]=value;
        value=0;
        tokens[user_choice][1]=1;
        area_g(value,c,user_choice);
        goto end;
        //to move to next kingdom
    }

    if(x<=6) //moving pice to new location
    {   
        *(ye_ptr+x-1)=c;
    }

    else if(x==7)
    {
        *(ye_ptr+11)=c;
    }

    else if(tokens[user_choice][3]==4 && (x<13 || temp<13))
    {
        if(x==13)  //condition for reaching homecount
        {
            homecount[3]++;; //increasing count by 1
            tokens[user_choice][1]=0;
            tokens[user_choice][2]=0;
        }

        else if(x>13) //if value is larger then dumping the increament
        {
            x=temp;
            value=0;
        }

        else
        {
        *(ye_ptr + 18 - x)=c;
        }
    }

    else
    {
        if(x>7 && x<13)
        {
        x+=5;
        }

       else if(x==13 && temp==7)
        {
            x=18;
        } 

        *(ye_ptr+30-x)=c;
    }

    tokens[user_choice][2]=x;

    end:

    //clearing previous location    

    if(value!=0)
    {
        if(temp<=6) //moving pice to new location
        {   
            *(ye_ptr+temp-1)='_';
        }

        else if(temp==7)
        {
            *(ye_ptr+11)='_';
        }

        else if(tokens[user_choice][3]==4 && temp<13)
        {
            *(ye_ptr + 18 - temp)='_';
        }

        else
        {
            if(temp>=7 && temp<13)
            {
            temp+=5;
            }
            *(ye_ptr+30-temp)='_';
        }
    }
}

int dice(void)
{
    float f;
    unsigned short int r;

    r = rand();
    //As modules of 6 results in (0,1,2,3,4,5). So it gives almost equal probability distribution of probability
    r = 1 + (r % 6); //increasing by 1 to get (1,2,3,4,5,6)
    
    return (r);
}

void display(int turn)
{
    printf(" ");
    for(i=0;i<32;i++)
    {
        printf("_"); //top line
    }
    printf(" \n");
    for(i=0;i<6;i++) //blue area 
    {
        printf("| "); //for each line

        if(turn==2)
        {
            if(i==1 || i==3)
            {
                printf(" |       |  ");
            }

            if(i==0)
            {
                printf("  _______   ");
            }

            if(i==2) //homelock of red
            {
                printf(" | %c   %c |  ", *(homelock_ptr+4),*(homelock_ptr+4+1));
            }
            else if(i==4) //homelock of red
            {
                printf(" | %c   %c |  ", *(homelock_ptr+4+2),*(homelock_ptr+4+3));
            }

            else if(i==5)
            {
                printf(" |_______|  ");
            }
        }

        else
        {
            for(j=0;j<12 && i!=2 && i!=4;j++)//spaces
            {
                printf(" ");
            }

            if(i==2) //homelock of red
            {
                printf("   %c   %c    ", *(homelock_ptr+4),*(homelock_ptr+4+1));
            }
            else if(i==4) //homelock of red
            {
                printf("   %c   %c    ", *(homelock_ptr+4+2),*(homelock_ptr+4+3));
            }
        }

        for(j=0;j<3;j++) //displaying blue area
        {
            printf("%c ", *(bl_ptr+j+i*3));
        }

        if(turn==3)
        {
            if(i==1 || i==3)
            {
                printf("  |       | ");
            }

            if(i==0)
            {
                printf("   _______  ");
            }

            if(i==2) //homelock of red
            {
                printf("  | %c   %c | ", *(homelock_ptr+8),*(homelock_ptr+8+1));
            }
            else if(i==4) //homelock of red
            {
                printf("  | %c   %c | ", *(homelock_ptr+8+2),*(homelock_ptr+8+3));
            }

            else if(i==5)
            {
                printf("  |_______| ");
            }
        }
        else
        {
            for(j=0;j<12 && i!=2 && i!=4;j++)
            {
                printf(" "); //spaces
            }

            if(i==2) //homlock of blue
            {
                printf("    %c   %c   ", *(homelock_ptr+8),*(homelock_ptr+8+1));
            }
            else if(i==4) //homlock of blue
            {
                printf("    %c   %c   ", *(homelock_ptr+8+2),*(homelock_ptr+8+3));
            }
        }

        printf(" |");

        printf("\n");
    }

    for(i=0;i<3;i++) //red and blue area
    {
        printf("| ");
        for(j=0;j<6;j++) //red area
        {
            printf("%c ", *(re_ptr+j+i*6));
        }

        if(i==0) //homecount (won token) count of blue
        {
            printf("  %d   ", homecount[2]);
        }
        
        else if(i==1) //homecount (won token) count of red and yellow
        {
            printf("%d   %d ", homecount[1], homecount[3]);
        }

        else //homecount (won token) count of green
        {
            printf("  %d   ", homecount[0]);
        }

        for(j=0;j<6;j++) //yellow area
        {
            printf("%c ", *(ye_ptr+j+i*6));
        }
        printf(" |");
        printf("\n");
    }

    for(i=0;i<6;i++) //green
    {
        printf("| ");
        
        if(turn==1)
        {
            if(i==1 || i==3)
            {
                printf(" |       |  ");
            }

            if(i==0)
            {
                printf("  _______   ");
            }

            if(i==2) //homelock of red
            {
                printf(" | %c   %c |  ", *(homelock_ptr),*(homelock_ptr+1));
            }
            else if(i==4) //homelock of red
            {
                printf(" | %c   %c |  ", *(homelock_ptr+2),*(homelock_ptr+3));
            }

            else if(i==5)
            {
                printf(" |_______|  ");
            }
        }

        else
        {
            for(j=0;j<12 && i!=2 && i!=4;j++) //spaces
            {
                printf(" ");
            }

            if(i==2) //green homelock area
            {
                printf("   %c   %c    ", *(homelock_ptr),*(homelock_ptr+1)); //green home
            }
            else if(i==4) //green homelock area
            {
                printf("   %c   %c    ", *(homelock_ptr+2),*(homelock_ptr+3));
            }
        }

        for(j=0;j<3;j++) //green area
        {
            printf("%c ", *(gr_ptr+j+i*3));
        }

        if(turn==4)
        {
            if(i==1 || i==3)
            {
                printf("  |       | ");
            }

            if(i==0)
            {
                printf("   _______  ");
            }

            if(i==2) //homelock of red
            {
                printf("  | %c   %c | ", *(homelock_ptr+12),*(homelock_ptr+12+1));
            }
            else if(i==4) //homelock of red
            {
                printf("  | %c   %c | ", *(homelock_ptr+12+2),*(homelock_ptr+12+3));
            }

            else if(i==5)
            {
                printf("  |_______| ");
            }
        }
        else
        {
            for(j=0;j<12 && i!=2 && i!=4;j++)
            {
                printf(" "); //spaces
            }

            if(i==2) //homlock of blue
            {
                printf("    %c   %c   ", *(homelock_ptr+12),*(homelock_ptr+12+1));
            }
            else if(i==4) //homlock of blue
            {
                printf("    %c   %c   ", *(homelock_ptr+12+2),*(homelock_ptr+12+3));
            }
        }

        printf(" |");
        printf("\n");
    }

    printf("|");
    for(i=0;i<32;i++)
    {
        printf("_");
    }
    printf("|");
    printf(" \n");
}