#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#define Width 800
#define High  600												//游戏画面大小
#define BlockNum 13												//每行砖块个数
int border;														//边界
int ball_x,ball_y;												//小球中心坐标 
int radius;														//小球半径
int ballv_x,ballv_y;											//小球速度
int baffler_x,baffler_y;										//挡板左上角坐标
int baffler_width,baffler_high;									//挡板长度和宽度
int isOver=0;													//判断游戏是否结束
int blockWidth,blockHigh;										//每个砖块长度和宽度
int block[4][BlockNum];											//记录砖块是否被打掉
int score;														//分数
int life;
int bood[3]={0};
void startup();													//初始化变量
void show();													//游戏画面显示
void clean();													//清除画面
void updateWithoutInput();										//与用户无关的更新	
void updateWithInput();											//与用户有关的更新
void gameOver();												//游戏结束			
int main()
 {	startup();	
 	BeginBatchDraw();
 	while(1&&!isOver)
	{
 	clean();
 	updateWithoutInput();
 	updateWithInput();
 	show();
 	}
 	EndBatchDraw();
 	gameOver();
 	return 0;
 }
 void startup()
 	{	
 	initgraph(Width,High);
 	baffler_x=Width/2-25;
 	baffler_y=High-50;
 	baffler_width=150;
 	baffler_high=10;
 	ball_x=baffler_x+baffler_width/2;
 	ball_y=baffler_y-12;
 	radius=10;
 	ballv_x=0;
 	ballv_y=0;
 	blockWidth=40;
 	blockHigh=20;
 	int i,j;
 	for(i=0;i<4;i++)
 	{
 		for(j=0;j<BlockNum;j++)
 		{
 			block[i][j]=1;
 	}
 	}
 	border=BlockNum*blockWidth+10;
 	score=0;
 	life=3;
 }
 void drawBorder()
 {
 	setlinecolor(WHITE);
 	setlinestyle(PS_SOLID,3);
 	line(border,0,border,High);
 	}
 void drawBall()
 {
 	setlinestyle(PS_SOLID,1);
 	setlinecolor(YELLOW);
 	setfillcolor(YELLOW);
 	fillcircle(ball_x,ball_y,radius);							//画小球
 }
 void clearBall()
 	{
 	setlinestyle(PS_SOLID,1);
 	setlinecolor(BLACK);
 	setfillcolor(BLACK);
 	fillcircle(ball_x,ball_y,radius);
 }																//清除小球
 void drawBaffer()
 	{
 	setlinecolor(GREEN);
 	setlinestyle(PS_SOLID,2);
 	setfillcolor(GREEN);
 	fillrectangle(baffler_x,baffler_y,
 	baffler_x+baffler_width,baffler_y+baffler_high);
 	}															//画挡板
 void clearBaffer()
 	{
 	setlinecolor(BLACK);
 	setlinestyle(PS_SOLID,2);
 	setfillcolor(BLACK);
 	fillrectangle(baffler_x,baffler_y,
 	baffler_x+baffler_width,baffler_y+baffler_high);
 }																//清除挡板
 void drawBlock()
 	{
 		setlinecolor(BLACK);
 	    int i,j;
 	    for(i=0;i<4;i++)
 		{
 		for(j=0;j<BlockNum;j++)
 			{
 			if(block[i][j]==1)
			{      
					int c[3]={RGB(100,100,255),RGB(100,255,100),RGB(255,100,200)};
				setfillcolor(c[i]);		
 		        	fillrectangle(j*blockWidth,i*blockHigh,(j+1)*blockWidth,(i+1)*blockHigh);
 			}
 			else
 				{
 					setfillcolor(BLACK);
 		        	fillrectangle(j*blockWidth,i*blockHigh,(j+1)*blockWidth,(i+1)*blockHigh);
 				}
 			}
 		}
 }
void gameOver()
 {
 	Sleep(1000);
 	setbkcolor(BLACK);
 	cleardevice();	
	settextcolor(RED);
 	settextstyle(60,0,_T("黑体"));
 	outtextxy(Width/2-100,High/2-30,"Game Over");
 	getch();
 	closegraph();
 }
 void countSystem()
 { 
 	settextcolor(CYAN);
 	settextstyle(22,0,_T("黑体"));
 	char s[10];
 	sprintf(s,"分数 %d",score);
 	outtextxy(border+40,150,s);	
    outtextxy(border+40,190,"生命");
 	setlinecolor(BLACK);
 	int i;
 	int boodWidth=20;							//血条长宽
 	for(i=0;i<3;i++)
 	{
 			if(bood[i]==0)
 			setfillcolor(BLUE);
 			else
 			setfillcolor(BLACK);
 			fillrectangle(border+100+i*boodWidth,200,
 			border+100+(i+1)*boodWidth,210);
 		}
 }
 void show()
 	{
 	
 	drawBorder();
 	drawBlock();
 	drawBaffer();
 	drawBall();
 	FlushBatchDraw();
    Sleep(3);
 
 }
 void clean()
 {
 	setlinestyle(PS_SOLID,1);
 	setlinecolor(BLACK);
 	setfillcolor(BLACK);
 	fillcircle(ball_x,ball_y,radius);
 	setlinestyle(PS_SOLID,2);
 	fillrectangle(baffler_x,baffler_y,
 	baffler_x+baffler_width,baffler_y+baffler_high);
 	}
 void updateWithoutInput()
 {
 	if(ball_x-radius<=0||ball_x+radius>=border)
 	ballv_x=-ballv_x;
 	if(ball_y-radius<=0)
 	ballv_y=-ballv_y;
 	if(ball_y+radius>=baffler_y&&ball_y-radius<=baffler_y-baffler_high)
 	{
 		if(ball_x>=baffler_x-radius/2&&ball_x<=baffler_x+baffler_width+radius/2)
 		ballv_y=-ballv_y;
		else
 		{
 			if(life<=0)
 			isOver=1;
 			else
 			{
 				bood[life-1]=1;
 				life--;
 				clearBall();
 				Sleep(500);
 				ball_x=baffler_x+baffler_width/2;
 				ball_y=baffler_y-12;
 				ballv_x=0;														//复活
 				ballv_y=0;
 	}
 		}	
 		}
 	int i,j;
 	for(i=0;i<4;i++)
 	{
 			for(j=0;j<BlockNum;j++)
 		{
 				if(block[i][j]==1&&ball_x>=j*blockWidth&&ball_x<(j+1)*blockWidth
 					&&ball_y<=(i+1)*blockHigh+radius)
 			{
 				block[i][j]=0;
 				ballv_y=-ballv_y;
 				score++;
 				}
 			}
 		}
 		ball_x+=ballv_x;
 		ball_y+=ballv_y;
 		if(ball_y<=radius)
 		ball_y=radius;															//消除卡墙BUG
 		countSystem();															//更新数据
 	}
 void updateWithInput()
 	{
 	char input;
 	if(kbhit())
 	{
 		input=getch();
 		if(input=='a'&&baffler_x>0)
 		{
 			baffler_x-=50;
 			if(ballv_x==0&&ballv_y==0)
 				{
 				clearBall();
 			    ball_x=baffler_x+baffler_width/2;
 		}
 		}
 			if(input=='d'&&baffler_x+baffler_width<border)
 			{
 			baffler_x+=50;//速度
 			if(baffler_x+baffler_width>border)
 		     	baffler_x=border-baffler_width;
 			if(ballv_x==0&&ballv_y==0)
 				{
 			     	clearBall();
 					ball_x=baffler_x+baffler_width/2;
 				}
 		}
 		if(input==' '&&ballv_x==0&&ballv_y==0)
 			{
 			ballv_y=-4;
 		    ballv_x=(rand()%2==0)?4:-4;
 		}
 
 	}														
 }
