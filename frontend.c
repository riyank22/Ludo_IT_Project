#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
#include<time.h>
void framework();
int dice_roll();
void R1(int diceroll);
void R2(int diceroll)
{
}
void R3(int diceroll)
{
}

void R4(int diceroll);

void red();
void green()
{
}
void blue();
void yellow();
void red();
int posx_r1=45;
int posy_r1=195;
int posx_r2=45;
int posy_r2=195;
int posx_r3=45;
int posy_r3=195;
int posx_r4=45;
int posy_r4=195;
void red()
	{
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"c:\\tc\\bgi");
	framework();
	delay(1000);
       static six_red=0;
       int diceroll_red=dice_roll();
	cleardevice();
	printf("CONGRATULATIONS! YOUR DICE SHOWS %d",diceroll_red);
	if(diceroll_red==6)
	{
		six_red++;
	}
      if(six_red==0)
	{
	printf("\n YOU CANNOT MOVE \n GREEN PLAYER NOW YOUR TURN ");
	 // green();
	}
	if(six_red>0 )
	{
		printf("\n NOW PRESS 1 for R1 \n 2 for R2 \n 3 for r3 \n 4 for R4");
		while(1)
		{
		int entry_r;
		scanf("%d",&entry_r);
		if(entry_r==1)
		{
			printf("\n YOU CHOOSE R1");
			R1(diceroll_red);
			break;
		}
		else if(entry_r==2)
		{
			printf("\n YOU CHOOSE R2");
			R2(diceroll_red);
			break;
		}
		else if(entry_r==3)
		{
			printf("\nYOU CHOOSE R3");
			R3(diceroll_red);
			break;
		}
		else if(entry_r==4)
		{
			printf("\n YOU CHOOSE R4");
			R4(diceroll_red);
			break;
		}
		else
		{
			printf("\n READ THE INSTRUCTIONS AND TRY AGAIN");
		}
		}
		}
		delay(1000);
	}

	int main()
	{
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"c:\\tc\\bgi");
       //	framework();
	red();
	red();
	red();
	red();
	red();
	red();
	getch();
	closegraph();
	return 0;
	}
	void R1(int diceroll)
	{
		static start=0;
		if(diceroll==6)
		{
			start=1;
		}
		if(start==0)
		{
			printf("\n YOU CANNOT MOVE THIS PIECE UNTILL YOUR DICE SHOWS 6");
			red();
		}
		int ini=1;
		int long=0;
		int short=0;
		if(start>0)
		{
			if(ini==1 && long==0 && short==0)
			{
				static counter=0;
				counter=diceroll;
				if(counter>4)
				{
					posy_r1=posy_r1+150;
					counter=diceroll-4;
					long++;
				}
				else
				{
					posy_r1=posy_r1+(counter*30);
				}
				setcolor(8);
				setfillstyle(SOLID_FILL,8);
				circle(posx_r1,posy_r1);
				floodfill(posx_r1,posy_r1,8);
				}
      }
	void framework()
{
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"c:\\tc\\bgi");
	setcolor(BLUE);
	setfillstyle(SOLID_FILL,WHITE);
	rectangle(450,450,0,0);
	floodfill(1,1,BLUE);
	setcolor(4);
	setfillstyle(SOLID_FILL,4);
	rectangle(180,180,0,0);
	floodfill(1,1,4);
	setcolor(0);
	rectangle(180,0,210,180);
	rectangle(210,0,240,180);
	rectangle(240,0,270,180);
	setcolor(2);
	setfillstyle(SOLID_FILL,2);
	rectangle(270,0,450,180);
	floodfill(271,1,2);
	setcolor(0);
	rectangle(0,180,180,210);
	rectangle(0,210,180,240);
	rectangle(0,240,180,270);
	setcolor(1);
	setfillstyle(SOLID_FILL,1);
	rectangle(0,270,180,450);
	floodfill(1,271,1);
	rectangle(180,180,270,270);
	setcolor(14);
	setfillstyle(SOLID_FILL,14);
	rectangle(270,270,450,450);
	floodfill(271,271,14);
	setcolor(0);
	rectangle(180,270,210,450);
	rectangle(210,270,240,450);
	rectangle(240,270,270,450);
	rectangle(270,180,450,210);
	rectangle(270,210,450,240);
	rectangle(270,240,450,270);
	for(int i=0;i<=180;i=i+30)
	{
		line((0+i),180,(0+i),270);
	}
	for(int j=0;j<=180;j=j+30)
	{
		line(180,(0+j),270,(0+j));
	}
	for(int k=0;k<=180;k=k+30)
	{
		line(180,(270+k),270,(270+k));
	}
	for(int l=0;l<=180;l=l+30)
	{
		line((270+l),180,(270+l),270);
	}
	line(180,180,270,270);
	line(180,270,270,180);
	setcolor(WHITE);
	setfillstyle(SOLID_FILL,WHITE);
	rectangle(30,30,150,150);
	floodfill(31,31,WHITE);
	setcolor(4);
	setfillstyle(SOLID_FILL,4);
	circle(60,60,15);
	floodfill(60,60,4);
	circle(120,120,15);
	floodfill(120,120,4);
	circle(120,60,15);
	floodfill(120,60,4);
	circle(60,120,15);
	floodfill(60,120,4);
	setcolor(15);
	setfillstyle(SOLID_FILL,15);
	rectangle(300,30,420,150);
	floodfill(301,31,15);
	setcolor(2);
	setfillstyle(SOLID_FILL,2);
	circle(330,60,15);
	floodfill(330,60,2);
	circle(390,120,15);
	floodfill(390,120,2);
	circle(390,60,15);
	floodfill(390,60,2);
	circle(330,120,15);
	floodfill(330,120,2);
	setcolor(15);
	setfillstyle(SOLID_FILL,15);
	rectangle(300,300,420,420);
	floodfill(301,301,15);
	setcolor(14);
	setfillstyle(SOLID_FILL,14);
	circle(330,330,15);
	floodfill(330,330,14);
	circle(390,390,15);
	floodfill(390,390,14);
	circle(390,330,15);
	floodfill(390,330,14);
	circle(330,390,15);
	floodfill(330,390,14);
	setcolor(15);
	setfillstyle(SOLID_FILL,15);
	rectangle(30,300,150,420);
	floodfill(31,301,15);
	setcolor(1);
	setfillstyle(SOLID_FILL,1);
	circle(60,330,15);
	floodfill(60,330,1);
	circle(120,390,15);
	floodfill(120,390,1);
	circle(60,390,15);
	floodfill(60,390,1);
	circle(120,330,15);
	floodfill(120,330,1);
	setcolor(1);
	setfillstyle(SOLID_FILL,1);
	rectangle(180,390,210,420);
	floodfill(181,391,1);
	setcolor(1);
	setfillstyle(SOLID_FILL,1);
	rectangle(210,270,240,420);
	floodfill(211,271,1);
	setcolor(2);
	setfillstyle(SOLID_FILL,2);
	rectangle(240,30,270,60);
	floodfill(241,31,2);
	rectangle(210,30,240,180);
	floodfill(211,31,2);
	setcolor(14);
	setfillstyle(SOLID_FILL,14);
	rectangle(390,240,420,270);
	floodfill(391,241,14);
	rectangle(270,210,420,240);
	floodfill(271,211,14);
	setcolor(RED);
	setfillstyle(SOLID_FILL,RED);
	rectangle(30,180,60,210);
	floodfill(31,181,RED);
	rectangle(30,210,180,240);
	floodfill(31,211,RED);
	}
	int dice_roll()
	{
		 srand(time(NULL));
	int diceroll=rand()%6;
	if(diceroll==0)
	{
		diceroll=6;
	}
	return diceroll;
	}