#include <stdio.h>
#include <stdlib.h>

int i,j;
void display(); //for displaying (giving input the four char arrays)

void area_finder(int,int *); //value, initial kingdomn(kingdom number and postion)
void area_g(int,int *, char); //navigation function in green kingdom
void area_r(int,int *, char); //navigation function in red kingdom
void area_b(int,int *, char); //navigation function in blue kingdom
void area_y(int,int *, char); //navigation function in yellow kingdom

int dice(void); //dice

//declaring count of homecount tokens (won tokens)
    int homecount[4];
    int *ptr_homecount;
    char *gr_ptr, *bl_ptr, *re_ptr, *ye_ptr;
    
int main(void)
{
    char green_area[6][3],blue_area[6][3],red_area[3][6], yellow_area[3][6];
    gr_ptr=&green_area[0][0];bl_ptr=&blue_area[0][0];re_ptr=&red_area[0][0];ye_ptr=&yellow_area[0][0];

    for(i=0;i<18;i++)
    {
        *(gr_ptr+i)=*(bl_ptr+i)=*(re_ptr+i)=*(ye_ptr+i)='_';//assigning the blank spaces.
    }

    int tokens[16][4]; //coords of tokens (kingdom/coord)
    int *ptr_tokens; //for storing posititon of tokens (kingdom,location)
    ptr_tokens=&tokens[0][0]; //liking pointer

    //assiging count 0.
    ptr_homecount=&homecount[0];
    for(i=0;i<4;i++)
    {
        *(ptr_homecount+i)=0;
    }

    //1-green
    //2-red
    //3-blue
    //4-yellow
    
    int value=0;

    printf("Enter colour code (1,2,3,4): ");
    scanf("%d", (ptr_tokens+2));

    printf("Enter spawn area and location: ");
    scanf("%d %d", (ptr_tokens), (ptr_tokens+1));


    printf("%d %d", tokens[0][0], tokens[0][1]);

   char null='\0';

    while(*(ptr_homecount+*(ptr_tokens)-1)!=1)
    {
        area_finder(value, ptr_tokens);
        display();
        printf("\nThe Coords are %d %d\n\n", tokens[0][0], tokens[0][1]);
        
        value=dice();
        printf("The Dice Value is %d\n\n", value);

        printf("PRESS ENTER TO CONTINUE.");
        null=getchar();
        
        system("clear");
    }
    system("clear");
    display();
}

void area_finder(int value, int *initial_kingdom)
{
    char c;
    switch (*(initial_kingdom+2))
    {
    case 1:
        c='*';
        break;
    
    case 2:
        c='+';
        break;
    
    case 3:
        c='/';
        break;
    
    case 4:
        c='?';
        break;
    }

    switch(*(initial_kingdom))
    {
        case 1:
        area_g(value, initial_kingdom,c);
        break;

        case 2:
        area_r(value, initial_kingdom,c);
        break;

        case 3:
        area_b(value, initial_kingdom,c);
        break;

        case 4:
        area_y(value, initial_kingdom,c);
        break;
    }

}

void area_g(int value,int *initial,char c)
{
    int temp=*(initial+1);
    *(initial+1)+=value;

    if(*(initial+1)>18)
    {
        *(gr_ptr+(18-temp)*3)='_';//clearing past record

        value=*(initial+1)-18; //finding the coordinates to move in next kingdom
        *(initial+1)=value; //assigning the coords of the next kingdom
        value=0; //as coordinates are already assigned, putting value = 0
        *(initial)+=1;

        area_r(value, initial, c);
        goto end;
        //to move to next kingdom
    }

    if(*(initial+1)<=6 && *(initial)==1) //moving pice to new location
    {   
        *(gr_ptr+2+3*(*(initial+1)-1))=c;
    }

    else if(*(initial+1)==7)
    {
        *(gr_ptr+1+3*5)=c;
    }

    else if(*(initial+2)==1 && (*(initial+1)<13 || temp<13))
    {
        if(*(initial+1)==13)  //condition for reaching homecount
        {
            *(ptr_homecount)+=1; //increasing count by 1
        }

        else if(*(initial+1)>13) //if value is larger then dumping the increament
        {
            *(initial+1)=temp;
            value=0;
        }

        else
        {
        *(gr_ptr+(12-*(initial+1))*3+1)=c;
        }
    }

    else
    {
        if(*(initial+1)>7 && *(initial+1)<13)
        {
        *(initial+1)+=5;
        }

        else if(*(initial+1)==13 && temp==7)
        {
            *(initial+1)=18;
        }

        *(gr_ptr+(18-*(initial+1))*3)=c;
    }

    if(value!=0)
    {
    //clearing previous location
    if(temp<=6) //moving pice to new location
    {   
        *(gr_ptr+2+3*(temp-1))='_';
    }

    else if(temp==7)
    {
        *(gr_ptr+1+3*5)='_';
    }

    else if(*(initial+2)==1 && temp<13)
    {
        *(gr_ptr+(12-temp)*3+1)='_';
    }

    else
    {
        if(temp>7 && temp<13)
        {
        temp+=5;
        }
        
        *(gr_ptr+(18-temp)*3)='_';
    }
    }

    end:
}

void area_r(int value,int *initial, char c)
{
    int temp=*(initial+1);
    *(initial+1)+=value;

    if(*(initial+1)>18)
    {
        *(re_ptr+(temp-13))='_';//clearing past record

        value=*(initial+1)-18;
        *(initial+1)=value;
        value=0;
        *(initial)+=1;
        area_b(value, initial,c);
        goto end;
        //to move to next kingdom
    }

    //moving pice to new location
    if(*(initial+1)<=6 && *(initial)==2)  //if it is in the same kingdom
    {   
        *(re_ptr+18-*(initial+1))=c;
    }

    else if(*(initial+1)==7)
    {
        *(re_ptr+6)=c;
    }

    else if(*(initial+2)==2 && (*(initial+1)<13 || temp<13))
    {
        if(*(initial+1)==13)  //condition for reaching homecount
        {
            *(ptr_homecount+1)+=1; //increasing count by 1
        }

        else if(*(initial+1)>13) //if value is larger then dumping the increament
        {
            *(initial+1)=temp;
            value=0;
        }

        else
        {
        *(re_ptr+*(initial+1)-1)=c;
        }
    }

    else
    {
        if(*(initial+1)>7 && *(initial+1)<13)
        {
            *(initial+1)+=5;
        }

        else if(*(initial+1)==13 && temp==7)
        {
            *(initial+1)=18;
        }

        *(re_ptr+(*(initial+1)-13))=c;
    }

    //clearing previous location

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

    else if(*(initial+2)==2 && temp<13)
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

    end:
}

void area_b(int value,int *initial, char c)
{
    int temp=*(initial+1);
    *(initial+1)+=value;

    if(*(initial+1)>18)
    {
        *(bl_ptr+3*temp-37)='_';//clearing past record

        value=*(initial+1)-18;
        *(initial+1)=value;
        value=0;
        *(initial)+=1;
        area_y(value, initial, c);
        goto end;
        //to move to next kingdom
    }

    if(*(initial+1)<=6 && *(initial)==3) //moving pice to new location
    {   
        *(bl_ptr+18-(3*(*(initial+1))))=c;
    }

    else if(*(initial+1)==7)
    {
        *(bl_ptr+1)=c;
    }

    else if(*(initial+2)==3 && (*(initial+1)<13 || temp<13))
    {
        if(*(initial+1)==13)  //condition for reaching homecount
        {
            *(ptr_homecount+2)+=1; //increasing count by 1
        }

        else if(*(initial+1)>13) //if value is larger then dumping the increament
        {
            *(initial+1)=temp;
            value=0;
        }

        else
        {
        *(bl_ptr+1+(*(initial+1)-7)*3)=c;
        }
    }

    else
    {
        if(*(initial+1)>7 && *(initial+1)<13)
        {
        *(initial+1)+=5;
        }

        else if(*(initial+1)==13 && temp==7)
        {
            *(initial+1)=18;
        }

        *(bl_ptr+3*(*(initial+1))-37)=c;
    }

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

    else if(*(initial+2)==3 && temp<13)
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

    end:
}

void area_y(int value,int *initial, char c)
{
    int temp=*(initial+1);
    *(initial+1)+=value;

    if(*(initial+1)>18)
    {
        *(ye_ptr+30-temp)='_';

        value=*(initial+1)-18;
        *(initial+1)=value;
        value=0;
        *(initial)=1;
        area_g(value, initial,c);
        goto end;
        //to move to next kingdom
    }

    if(*(initial+1)<=6 && *(initial)==4) //moving pice to new location
    {   
        *(ye_ptr+*(initial+1)-1)=c;
    }

    else if(*(initial+1)==7)
    {
        *(ye_ptr+11)=c;
    }

    else if(*(initial+2)==4 && (*(initial+1)<13 || temp<13))
    {
        if(*(initial+1)==13)  //condition for reaching homecount
        {
            *(ptr_homecount+3)+=1; //increasing count by 1
        }

        else if(*(initial+1)>13) //if value is larger then dumping the increament
        {
            *(initial+1)=temp;
            value=0;
        }

        else
        {
        *(ye_ptr + 18 - *(initial+1))=c;
        }
    }

    else
    {
        if(*(initial+1)>7 && *(initial+1)<13)
        {
        *(initial+1)+=5;
        }

       else if(*(initial+1)==13 && temp==7)
        {
            *(initial+1)=18;
        } 

        *(ye_ptr+30-*(initial+1))=c;
    }

    //clearing previous location    

    if(value!=0)
    {
        if(temp<=6 && *(initial)==4) //moving pice to new location
        {   
            *(ye_ptr+temp-1)='_';
        }

        else if(temp==7)
        {
            *(ye_ptr+11)='_';
        }

        else if(*(initial+2)==4 && temp<13)
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

    end:
}

int dice(void)
{
    float f;
    unsigned short int r;

    r = rand();
    //f = r / 65536.0;
    r = 1 + (r % 6);

    return (r);
}

void display()
{
    for(i=0;i<6;i++) //blue
    {
        for(j=0;j<12;j++)
        {
            printf(" ");
        }

        for(j=0;j<3;j++)
        {
            printf("%c ", *(bl_ptr+j+i*3));
        }

        for(j=0;j<12;j++)
        {
            printf(" ");
        }
        printf("\n");
    }

    for(i=0;i<3;i++) //red and blue
    {

        for(j=0;j<6;j++)
        {
            printf("%c ", *(re_ptr+j+i*6));
        }

        if(i==0)
        {
            printf("  %d   ", *(ptr_homecount+2));
        }
        
        else if(i==1)
        {
            printf("%d   %d ", *(ptr_homecount+1), *(ptr_homecount+3));
        }

        else
        {
            printf("  %d   ", *(ptr_homecount));
        }

        for(j=0;j<6;j++)
        {
            printf("%c ", *(ye_ptr+j+i*6));
        }
        printf("\n");
    }

    for(i=0;i<6;i++) //green
    {
        for(j=0;j<12;j++)
        {
            printf(" ");
        }

        for(j=0;j<3;j++)
        {
            printf("%c ", *(gr_ptr+j+i*3));
        }

        for(j=0;j<12;j++)
        {
            printf(" ");
        }
        printf("\n");
    }
}