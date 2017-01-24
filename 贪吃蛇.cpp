/***************************************************************************************************************************************/
/*头文件*/
/***************************************************************************************************************************************/
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
/***************************************************************************************************************************************/
/*宏定义*/
/***************************************************************************************************************************************/
#define N 200//最大长度
#define NOFOOD 0//食物不存在
#define FOOD 1//食物存在
#define UP 72//方向键
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define ENTER 13
#define ESC 27
/***************************************************************************************************************************************/
/*函数声明*/
/***************************************************************************************************************************************/
void first();/*游戏开场画面*/
void showarrow(int a,int b);/*箭头显示*/
void hidearrow(int a,int b);/*箭头隐藏*/
int  option();/*选择模式确认*/
void background();/*游戏背景*/
void begin();/*开始游戏*/
void brick(int x,int y);/*砖*/
void wall();/*围墙*/
void speedbar();/*速度条*/
void speedbrick(int x);/*速度长条*/
void hidespeedbrick(int x);/*隐藏速度长条*/
void egg(int x,int y);/*食物/蛇身*/
void hideegg(int x,int y);/*隐藏食物/蛇身*/
/***************************************************************************************************************************************/
/*主函数*/
/***************************************************************************************************************************************/
/*定义全局变量*/
struct/*食物信息*/
{
	int x;//横坐标
	int y;//纵坐标
	int flag;//放食与否
}food;
struct/*蛇信息*/
{
	int x[N];//横坐标
	int y[N];//纵坐标
	int xlast,ylast;//蛇尾上次坐标
	int node;//节数
	int direction;//方向
}snake;
int choose,picture,speed,key,longpress;//模式选项,选择画面,速度大小,捕获用户按键变量
/***************************************************************************************************************************************/
void main()
{
	initgraph(640,480);
	choose=1;picture=1;//初始化模式选项,选择画面
	first();//游戏开场画面
	cleardevice();//清屏开始游戏
	background();//初始化
	begin();//开始游戏
}
/***************************************************************************************************************************************/
/*函数定义*/
/***************************************************************************************************************************************/
void first()
{
	//蛇图样
	setlinestyle(PS_NULL);//边缘线条不可见
	setfillstyle(YELLOW,24);
	
	//蛇头
	fillellipse(167,120,233,239);
	setfillstyle(BLACK);
	bar(167,120,233,180);bar(200,180,233,239);
	setfillstyle(YELLOW,24);
	fillcircle(200,180,33);
	//蛇身蛇尾
	bar(200,213,430,239);
	fillcircle(430,213,26);
	setfillstyle(BLACK);
	fillcircle(430,200,12);
	bar(404,187,430,212);
	fillcircle(215,163,5);
	//蛇嘴
	int points[6];
	points[0]=200;points[1]=180;points[2]=270;points[3]=167;points[4]=270;points[5]=193;
	fillpolygon(3,points);

	outtextxy(263,170,"贪        吃        蛇");//"贪吃蛇"字样	
	outtextxy(279,250,"By Chicken");//"By Chicken"字样
	outtextxy(289,320,"1  Option");
	outtextxy(289,350,"2  Exit");
	showarrow(270,322);

	//游动字样
	IMAGE tmp;
	getimage(&tmp,0,0,textwidth("按回车键选择"),textheight("按回车键选择"));/*保存当前图像*/
	while(true)/*如果不选择就一直移动*/
	{
		for(int i=0;i<510;i++)/*字样在横坐标0-510范围移动*/
		{
			outtextxy(i,450,"按回车键选择");/*"按任意键进入"字样*/
			Sleep(20);/*延时*/
			putimage(i,450,&tmp);/*打印当前图像*/
			if(option()==1)/*如果已经选择好则开始游戏*/
				return;
		}

		for(;i>0;i--)/*循环移动*/
		{
			outtextxy(i,450,"按回车键选择");
			Sleep(20); 
			putimage(i,450,&tmp);
			if(option()==1)
				return;
		}
	}
}
/***************************************************************************************************************************************/
void showarrow(int a,int b)/*箭头显示*/
{
	int points[6];
	points[0]=a;points[1]=b;points[2]=a;points[3]=b+10;points[4]=a+10;points[5]=b+5;
	setfillstyle(WHITE);
	fillpolygon(3,points);
}
/***************************************************************************************************************************************/
void hidearrow(int a,int b)/*箭头隐藏*/
{
	int points[6];
	points[0]=a;points[1]=b;points[2]=a;points[3]=b+10;points[4]=a+10;points[5]=b+5;
	setfillstyle(BLACK);
	fillpolygon(3,points);
}
/***************************************************************************************************************************************/
int option()/*选择模式确认*/
{
	if(kbhit())/*按键信息*/
	{
		key=getch();/*获取按键*/			
		if(key==UP||key==DOWN)/*按上下键移动*/
		{
			switch(picture)/*进到第几个选择画面了*/
			{
				case 1:/*选择画面1*/
				{
					switch(choose)/*选项响应*/
					{	
						case 1:
						{
							choose=2;
							hidearrow(270,322);
							showarrow(270,352);
						}break;
						case 2:
						{
							choose=1;
							hidearrow(270,352);
							showarrow(270,322);
						}break;
					}
				}break;
				case 2:/*选择画面2*/
				{
					switch(choose)
					{
						case 1:
						{
							hidearrow(270,322);
							if(key==DOWN)/*若按向下键*/
							{
								choose=2;
								showarrow(270,352);
							}
							else/*若按向上键*/
							{
								choose=4;
								showarrow(270,412);
							}
						}break;
						case 2:
						{
							hidearrow(270,352);
							if(key==DOWN)
							{
								choose=3;
								showarrow(270,382);
							}
							else
							{
								choose=1;
								showarrow(270,322);
							}
						}break;
						case 3:
						{
							hidearrow(270,382);
							if(key==DOWN)
							{
								choose=4;
								showarrow(270,412);
							}
							else
							{
								choose=2;
								showarrow(270,352);
							}
						}break;
						case 4:
						{
							hidearrow(270,412);
							if(key==DOWN)
							{
								choose=1;
								showarrow(270,322);
							}
							else
							{
								choose=3;
								showarrow(270,382);
							}
						}break;
					}
				}break;
				case 3:/*选择画面3*/
				{
					switch(choose)
					{
						case 1:
						{
							hidearrow(270,322);
							if(key==DOWN)
							{
								choose=2;
								showarrow(270,352);
							}
							else
							{
								choose=4;
								showarrow(270,412);
							}
						}break;
						case 2:
						{
							hidearrow(270,352);
							if(key==DOWN)
							{
								choose=3;
								showarrow(270,382);
							}
							else
							{
								choose=1;
								showarrow(270,322);
							}
						}break;
						case 3:
						{
							hidearrow(270,382);
							if(key==DOWN)
							{
								choose=4;
								showarrow(270,412);
							}
							else
							{
								choose=2;
								showarrow(270,352);
							}
						}break;
						case 4:
						{
							hidearrow(270,412);
							if(key==DOWN)
							{
								choose=1;
								showarrow(270,322);
							}
							else
							{
								choose=3;
								showarrow(270,382);
							}
						}break;
					}
				}break;						
			}
		}
		else if(key==ENTER||key==SPACE)/*按回车或空格确定*/
		{
			switch(picture)
			{
				case 1:/*选择画面1*/
				{
					switch(choose)
					{
						case 1:/*Option*/
						{
							picture=2;
							choose=1;
							setfillstyle(BLACK);
							bar(270,322,370,430);
							outtextxy(289,320,"1  Balance");
							outtextxy(289,350,"2  Gaining");
							outtextxy(289,380,"3  Free");
							outtextxy(289,410,"4  Return");
							showarrow(270,322);
						}break;
						case 2:/*Exit*/
						{
							closegraph();
							exit(0);
						}break;
					}
				}break;
				case 2:/*选择画面2*/
				{
					switch(choose)
					{
						case 1:/*Balance*/
						{
							picture=3;
							setfillstyle(BLACK);
							bar(270,322,370,430);
							outtextxy(289,320,"1  Slow");
							outtextxy(289,350,"2  Middle");
							outtextxy(289,380,"3  Fast");
							outtextxy(289,410,"4  Return");
							showarrow(270,322);choose=1;
						}break;
						case 2:/*Gaining*/
						{
							return 1;
						}break;
						case 3:/*Free*/
						{
							return 1;
						}break;
						case 4:/*Return*/
						{
							picture=1;
							choose=1;
							setfillstyle(BLACK);
							bar(270,322,370,430);
							outtextxy(289,320,"1  Option");
							outtextxy(289,350,"2  Exit");
							showarrow(270,322);
						}break;
					}
				}break;
				case 3:/*选择画面3*/
				{
					switch(choose)
					{
						/*选择难度后进入(记录的choose以后有用)*/
						case 1:/*Slow*/
						case 2:/*Middle*/
						case 3:/*Fast*/
						{
							return 1;
						}break;
						case 4:/*Return*/
						{
							picture=2;
							choose=1;
							setfillstyle(BLACK);
							bar(270,322,370,430);
							outtextxy(289,320,"1  Balance");
							outtextxy(289,350,"2  Gaining");
							outtextxy(289,380,"3  Free");
							outtextxy(289,410,"4  Return");
							showarrow(270,322);
						}break;
					}
				}break;
			}
		}
	}
}
/***************************************************************************************************************************************/
void background()/*游戏背景*/
{
	//画围墙
	wall();
	//速度条
	setfillstyle(WHITE);bar(10,440,63,470);setfillstyle(BLACK);bar(13,443,60,467);
	outtextxy(16,448,"Speed");
	speedbar();
	//按键条
	setfillstyle(WHITE);bar(240,440,630,470);setfillstyle(BLACK);bar(243,443,627,467);
	outtextxy(352,448,"Pause:S");
	outtextxy(430,448,"Replay:Enter");
	outtextxy(538,448,"Return:Space");

	//游戏模式字样确定、速度确定、速度条确定
	switch(picture)
	{
		case 2://Gaining、Free
		{
			switch(choose)
			{
				case 2:
				{
					outtextxy(250,448,"Mode:Gaining");
					speed=210;
				}break;
				case 3:
				{
					outtextxy(250,448,"Mode:Free");
					speed=210;
				}break;
			}
		}break;
		case 3://Balance
		{
			switch(choose)
			{
				case 1://Slow
				{
					outtextxy(250,448,"Mode:Slow");
					speed=150;
					for(int j=63;j<=99;j+=18)
						speedbrick(j);
				}break;
				case 2://Middle
				{
					outtextxy(250,448,"Mode:Middle");
					speed=90;
					for(int j=63;j<=153;j+=18)
						speedbrick(j);
				}break;
				case 3://Fast
				{
					outtextxy(250,448,"Mode:Fast");
					speed=30;
					for(int j=63;j<=207;j+=18)
						speedbrick(j);
				}break;
			}
		}break;
	}
}
/***************************************************************************************************************************************/
void begin()/*开始游戏*/
{
	if(picture==2)//清空上次游戏的速度条及速度
	{
		speed=210;
		setfillstyle(BLACK);bar(63,443,222,467);
	}
	setfillstyle(BLACK);bar(30,30,610,410);//清空游戏区

    int m=63;/*速度长条推移显示用*/
	food.flag=NOFOOD;//需要出现食物
	snake.direction=UP;//初始化向上移动
	snake.node=1;//初始化一节蛇身
	snake.x[0]=320;//蛇头初始化位置	
	snake.y[0]=200;
	
	srand((unsigned)time(NULL));//食物随机种子
	food.x=40+(((40+rand()%561)-35)/10)*10; 
	food.y=40+(((40+rand()%361)-35)/10)*10;//(40-x-590,40-y-390)食物随机坐标

	//倒计时
	setfillstyle(BLACK);
	outtextxy(300,150,"Ready!");Sleep(1000);
	bar(300,150,300+textwidth("Ready!"),150+textheight("Ready!"));
	outtextxy(320,150,"3");Sleep(1000);
	bar(320,150,340,180);
	outtextxy(320,150,"2");Sleep(1000);
	bar(320,150,340,180);
	outtextxy(320,150,"1");Sleep(1000);
	bar(320,150,340,180);
	outtextxy(300,150,"Begin!");Sleep(1000);
	bar(300,150,300+textwidth("Begin!"),150+textheight("Begin!"));
	
	//游戏开始
	while(true)
	{
		longpress=(snake.direction==LEFT  && GetAsyncKeyState(VK_LEFT)  & 0x8000)
				 +(snake.direction==RIGHT && GetAsyncKeyState(VK_RIGHT) & 0x8000)
				 +(snake.direction==UP    && GetAsyncKeyState(VK_UP)    & 0x8000)
				 +(snake.direction==DOWN  && GetAsyncKeyState(VK_DOWN)  & 0x8000);//上下左右其一是否长按键
		if(!kbhit()||longpress!=0)//如果未按键或是长按键
		{
			if(picture==2&&choose==3)//Free模式长按加速处理
			{
				if(longpress==0)//未长按键,是因为!kbhit()进入
				{
					speed=210;//速度还原
					setfillstyle(BLACK);bar(63,443,222,467);//隐藏速度条					
				}
				else//长按键,是因为longpress!=0进入
				{
					speed=50;//加速效果
					for(m=63;m<=207;m+=18)
						speedbrick(m);//显示速度条
				}
			}
			if(food.flag==NOFOOD)//需要出现食物
			{
				food.flag=FOOD;//已存在食物
RERAND:         food.x=40+(((40+rand()%561)-35)/10)*10;//(40-x-590,40-y-390)食物随机坐标
				food.y=40+(((40+rand()%361)-35)/10)*10;
				for(int i=0;i<=snake.node-1;i++)//检查食物是否和蛇身重合
					if(food.x==snake.x[i]&&food.y==snake.y[i])
						goto RERAND;//返回重新随机
				egg(food.x,food.y);//画食物	
			}
			if(snake.x[0]==food.x&&snake.y[0]==food.y)//吃到食物
			{
				puts("\a");//响铃一次
				food.flag=NOFOOD;//标记无食物
				hideegg(food.x,food.y);//隐藏食物
				snake.node++;//节数增1
				if(picture==2&&choose==2&&(snake.node-1)%3==0&&snake.node<=28)//速度条逐加加速(Gaining模式)
				{
					speedbrick(m);
					m+=18;
					speed-=20;
				}
				snake.x[snake.node-1]=food.x;//添加蛇尾坐标
				snake.y[snake.node-1]=food.y;
				egg(snake.x[snake.node-1],snake.y[snake.node-1]);//蛇尾出现
			}

			snake.xlast=snake.x[snake.node-1];//上一时刻的蛇尾保留,之后闪动用
			snake.ylast=snake.y[snake.node-1];
			for(int i=snake.node-1;i>0;i--)//蛇身依次承接上一节的坐标(蛇头还是以前的坐标)
			{
				snake.x[i]=snake.x[i-1];
				snake.y[i]=snake.y[i-1];
			}
			switch(snake.direction)//根据此时移动方向赋予蛇头新的坐标
			{
				case UP:
				{
					snake.y[0]-=10;
				}break;
				case DOWN:
				{
					snake.y[0]+=10;
				}break;
				case LEFT:
				{
					snake.x[0]-=10;
				}break;
				case RIGHT:
				{
					snake.x[0]+=10;
				}break;
			}
			for(i=1;i<=snake.node-1;i++)//蛇头碰到蛇身
			{
				if(snake.x[0]==snake.x[i]&&snake.y[0]==snake.y[i])//碰到蛇身
				{
					//蛇身闪动效果
					m=0;
					while(m++!=4)//闪动四次
					{
						for(i=snake.node-1;i>=1;i--)//蛇身出现
							egg(snake.x[i],snake.y[i]);
						egg(snake.xlast,snake.ylast);//上一时刻的蛇尾补全(snake.xy[snake.node-1])已经承接了)
						Beep(500,200);//蜂鸣
						for(i=snake.node-1;i>=1;i--)//蛇身消失
							hideegg(snake.x[i],snake.y[i]);
						hideegg(snake.xlast,snake.ylast);
						Sleep(200);
					}
					HWND wnd=GetHWnd();/*游戏结束对话框*/
					if (MessageBox(wnd,"游戏失败!\n是否重来?","询问",MB_YESNO|MB_ICONQUESTION)==IDYES)
					{begin();}//重来当前游戏
					else
					{closegraph();exit(0);}//退出操作系统
				}
			}
			if(snake.x[0]<35||snake.x[0]>605||snake.y[0]<35||snake.y[0]>405)//蛇头是否撞墙
			{	
				//蛇身闪动效果
				m=0;
				while(m++!=4)
				{
					for(i=snake.node-1;i>=1;i--)
						egg(snake.x[i],snake.y[i]);
					egg(snake.xlast,snake.ylast);
					Beep(500,200);
					for(i=snake.node-1;i>=1;i--)
						hideegg(snake.x[i],snake.y[i]);
					hideegg(snake.xlast,snake.ylast);
					Sleep(200);
				}
				HWND wnd=GetHWnd();
				if (MessageBox(wnd,"游戏失败!\n是否重来?","询问",MB_YESNO|MB_ICONQUESTION)==IDYES)
				{begin();}
				else
				{closegraph();exit(0);}
			}
			
			//画蛇移动
			egg(snake.x[0],snake.y[0]);//蛇头出现
			Sleep(speed);//暂留一定时间
			hideegg(snake.x[snake.node-1],snake.y[snake.node-1]);//隐藏蛇尾
		}
		else//如果按键
		{
			key=getch();//获取按键

			if(key==UP&&snake.direction!=UP&&snake.direction!=DOWN)//蛇移动方向不是该方向极其反方向
				snake.direction=UP;//改变蛇方向
			else if(key==DOWN&&snake.direction!=DOWN&&snake.direction!=UP)
				snake.direction=DOWN;
			else if(key==LEFT&&snake.direction!=LEFT&&snake.direction!=RIGHT)
				snake.direction=LEFT;
			else if(key==RIGHT&&snake.direction!=RIGHT&&snake.direction!=LEFT)
				snake.direction=RIGHT;
			else if(key=='s'||key=='S')//暂停
			{
				egg(snake.x[snake.node-1],snake.y[snake.node-1]);//蛇尾补足
				while(true)
				{
					key=getch();//等待用户再次按键
					if(key=='s'||key=='S')//再次开启
					{
						hideegg(snake.x[snake.node-1],snake.y[snake.node-1]);
						break;
					}
					else if(key==ENTER)//重来
						begin();
					else if(key==SPACE)//返回
						main();
					else if(key==ESC)//退出
						{closegraph();exit(0);}
				}
			}
			else if(key==ENTER)//重来
				begin();
			else if(key==SPACE)//返回
				main();
			else if(key==ESC)//退出
				{closegraph();exit(0);}
		}
	}
}
/***************************************************************************************************************************************/
void brick(int x,int y)/*砖*/
{
	setfillstyle(LIGHTBLUE,24);
	bar(x,y,x+20,y+20);
}
/***************************************************************************************************************************************/
void wall()/*围墙*/
{
	//上下横墙
	for(int x=10;x<=610;x+=25)
	{
		brick(x,10);
		brick(x,410);
	}
	//左右竖墙
	for(int y=10;y<=410;y+=25)
	{
		brick(10,y);
		brick(610,y);
	}
}
/***************************************************************************************************************************************/
void speedbar()/*速度条*/
{
	setfillstyle(WHITE);
	bar(60,440,225,470);
	setfillstyle(BLACK);
	bar(63,443,222,467);
}
/***************************************************************************************************************************************/
void speedbrick(int x)/*速度长条*/
{
	setfillstyle(LIGHTGREEN,24);
	bar(x,443,x+15,467);
}
/***************************************************************************************************************************************/
void hidespeedbrick(int x)/*隐藏速度长条*/
{
	setfillstyle(BLACK);
	bar(x,443,x+15,467);	
}
/***************************************************************************************************************************************/
void egg(int x,int y)/*食物/蛇身*/
{
	setfillstyle(YELLOW);
	fillcircle(x,y,5);
}
/***************************************************************************************************************************************/
void hideegg(int x,int y)/*隐藏食物/蛇身*/
{
	setfillstyle(BLACK);
	fillcircle(x,y,5);
}
/***************************************************************************************************************************************/