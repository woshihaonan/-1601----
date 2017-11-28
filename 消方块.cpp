#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#define Width 800
#define High  600												//��Ϸ�����С
#define BlockNum 13												//ÿ��ש�����
int border;														//�߽�
int ball_x,ball_y;												//С���������� 
int radius;														//С��뾶
int ballv_x,ballv_y;											//С���ٶ�
int baffler_x,baffler_y;										//�������Ͻ�����
int baffler_width,baffler_high;									//���峤�ȺͿ��
int isOver=0;													//�ж���Ϸ�Ƿ����
int blockWidth,blockHigh;										//ÿ��ש�鳤�ȺͿ��
int block[4][BlockNum];											//��¼ש���Ƿ񱻴��
int score;														//����
int life;
int bood[3]={0};
void startup();													//��ʼ������
void show();													//��Ϸ������ʾ
void clean();													//�������
void updateWithoutInput();										//���û��޹صĸ���	
void updateWithInput();											//���û��йصĸ���
void gameOver();												//��Ϸ����			
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
 	fillcircle(ball_x,ball_y,radius);							//��С��
 }
 void clearBall()
 	{
 	setlinestyle(PS_SOLID,1);
 	setlinecolor(BLACK);
 	setfillcolor(BLACK);
 	fillcircle(ball_x,ball_y,radius);
 }																//���С��
 void drawBaffer()
 	{
 	setlinecolor(GREEN);
 	setlinestyle(PS_SOLID,2);
 	setfillcolor(GREEN);
 	fillrectangle(baffler_x,baffler_y,
 	baffler_x+baffler_width,baffler_y+baffler_high);
 	}															//������
 void clearBaffer()
 	{
 	setlinecolor(BLACK);
 	setlinestyle(PS_SOLID,2);
 	setfillcolor(BLACK);
 	fillrectangle(baffler_x,baffler_y,
 	baffler_x+baffler_width,baffler_y+baffler_high);
 }																//�������
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
 	settextstyle(60,0,_T("����"));
 	outtextxy(Width/2-100,High/2-30,"Game Over");
 	getch();
 	closegraph();
 }
 void countSystem()
 { 
 	settextcolor(CYAN);
 	settextstyle(22,0,_T("����"));
 	char s[10];
 	sprintf(s,"���� %d",score);
 	outtextxy(border+40,150,s);	
    outtextxy(border+40,190,"����");
 	setlinecolor(BLACK);
 	int i;
 	int boodWidth=20;							//Ѫ������
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
 				ballv_x=0;														//����
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
 		ball_y=radius;															//������ǽBUG
 		countSystem();															//��������
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
 			baffler_x+=50;//�ٶ�
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
