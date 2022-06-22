#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#define N sizeof(struct BOOK)
 
struct BOOK        //图书信息 
{
	char number[10];   //登录号 
	char name[10];     //书名 
	char author[10];    //作者名 
	char type[10];      //类型 
	char publish[10];  //出版单位 
	char time[8];        //出版时间 
	float price;       //价格 
	int num;         //数量 
	int x;
	struct BOOK *next;   //指针域 
};
typedef struct BOOK Book;
typedef Book *book;	 
 
void HideCursor();    //隐藏光标
void toxy(int x, int y);    //将光标移动到X,Y坐标处
void color(short x);     //设置颜色
void over();             //退出 
void menu();           //菜单 
void input_book();     //图书入库 
void save_book(book p);//将图书信息存入文件 
void find_book();      //查询 
void print_book();    //图书总览 
void del_book();     //删除图书 
void amend_book();    //修改信息 
book ss();
void find_name_book();  //按书名查询 
void find_author_book(); //按作者查询 
void find_number_book();  //按登录号查询
void find_publish_book();  //按出版社查询 
void fuzzy_search();     //模糊查找 
 
void HideCursor()     //隐藏光标
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
 
void color(short x)
{
	if(x>=0&&x<=15)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	}
} 
 
void toxy(int x, int y)      //将光标移动到X,Y坐标处
{
COORD pos = { x , y };
HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(Out, pos); 
}
 
void menu()    //菜单 
{
	do
	{
		system("cls");  //清屏 
		HideCursor();  //隐藏光标 
		color(15);    //设置一个好看的颜色 
		char t;
		toxy(50,5);//将光标移动到（50，5）坐标处
		printf(" 图书查询管理系统");
		toxy(48,8);
		printf("|     1.图书入库      |");
		toxy(48,10);
		printf("|     2.修改信息      |");
		toxy(48,12);
		printf("|     3.删除信息      |");
		toxy(48,14);
		printf("|     4.图书查询      |");
		toxy(48,16);
		printf("|     5.图书总览      |");
		toxy(48,18);
		printf("|     6.退出软件      |");
		t=getch();    //不回显函数 
		switch(t)
		{
			case '1':input_book();break;
			case '2':amend_book();break;
			case '3':del_book();break;
			case '4':find_book();break;
			case '5':print_book();break; 
			case '6':over();break;
			default :break;
		}
	}while(1);
} 
 
book ss()      //将文件中的内容读出到链表中，返回值为表头地址 
{
	FILE *fp;       //文件指针 
	int n=0;
	book head=NULL;
	book p2,p,pr=NULL;
	fp=fopen("mybook","ab+");     //以只读的方式打开文件 
	if(fp==NULL)
	{
		printf("cannot open file\n");
	}
	while(!feof(fp))        //判断文件位置标志是否移动到文件末尾 
	{
	   n++;
	   	p=(book)malloc(N); //向内存申请一段空间 
	   fread(p,N,1,fp);     //将fp所指向的文件中的内容赋给p 
	   if(n==1)
	   {
	      head=p;
	      p2=p;
	    }
	    else             //创建链表 
	    {
	    	pr=p2;
	    	p2->next=p;
	    	p2=p;
		}
    }
    if(pr!=NULL)
       pr->next=NULL;
    else
       head=NULL;
    fclose(fp);    //关闭文件 
    return head;   //返回头指针 
}
 
void input_book()    //图书录入 
{
	do
	{
		system("cls");
		color(10);
		char t;
		book p;
		p=(book)malloc(N);     //申请空间 
		//输入图书信息
		toxy(48,8);
		printf("请输入图书登录号(小于10位数)：");    
		scanf("%s",p->number);getchar();
		toxy(48,10);
		printf("请输入书名(小于10位数)：");
		scanf("%s",p->name);getchar();
		toxy(48,12);
		printf("请输入作者名(小于10位数)：");
		scanf("%s",p->author);getchar();
		toxy(48,14);
		printf("请输入图书类别(小于10位数)：");
		scanf("%s",p->type);getchar();
		toxy(48,16);
		printf("请输入图书出版单位(小于10位数)：");
		scanf("%s",p->publish);getchar();
		toxy(48,18);
		printf("请输入图书出版时间(小于8位数)：");
		scanf("%s",p->time);getchar();
		toxy(48,20);
		printf("请输入图书价格：");
		scanf("%f",&p->price);getchar();
		toxy(48,22);
		printf("请输入图书数量：");
		scanf("%d",&p->num);
		save_book(p);
		toxy(48,24);
		printf("正在保存....");
		Sleep(500);   //暂停0.5秒 
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("| 保存成功！是否继续？  |");
		toxy(46,12);
		printf("| 1.是             2.否 |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)    //利用死循环可有效防止其他按键干扰 
		{
			t=getch();
			if(t=='1')
			{
				break;
			 } 
			 else if(t=='2')
			 {
			 	menu();
			 }
		}
	}while(1);
	
} 
 
void amend_book()    //修改图书信息 
{
	do
	{
		system("cls");
		color(10);
		book head,p;
		int i=11,j=0,x;
		char ch,t;
		FILE *fp;    //文件指针 
		char _name[10];
		char number[10];   //登录号 
		char name[10];     //书名 
		char author[10];    //作者名 
		char type[10];      //类型 
		char publish[10];  //出版单位 
		char time[8];        //出版时间 
		float price;       //价格 
		int num;         //数量 
		head=ss();
		p=head;
		toxy(48,10);
		printf("请输入你要修改的图书的书名：");
		gets(_name); 
		while(p!=NULL)    //初始化p->x为0 
		{
			p->x=0;
			p=p->next;
		}
		p=head;    //让p重新指向表头 
		toxy(20,5);
		printf("***********************************************图书信息******************************************************");
		toxy(20,8);
		printf("-------------------------------------------------------------------------------------------------------------");
		toxy(20,9);
		printf("登录号        书名        作者名         图书类别         出版单位         出版时间          价格        数量");
		toxy(20,10);
		printf("-------------------------------------------------------------------------------------------------------------");
		while(p!=NULL)
		{
			if(p!=NULL&&strcmp(p->name,_name)==0)
			{
				toxy(20,i);
				j++;
				printf("%d:%s%14s%14s%14s   %14s   %18s         %.2f%12d\n",j,p->number,p->name,p->author,p->type,p->publish,p->time,p->price,p->num);
				p->x=j;    //给符合查询标准的结点标号 
				i++;
			}
			p=p->next;
		}
		if(j==0)                   //如果j=0，即没有进入前面的搜索循环，也就是没有找到相应的信息 
		{ 
			toxy(50,i);
			printf("没有找到相应的信息！(按0返回，按1重新搜索)");
			while(1)               //死循环是为了防止除0和1的其他按键干扰 
			{
				ch=getch();
				if(ch=='0')
				{
					menu();break;
				}
				else if(ch=='1')
				{
					break;
				}
			}
			if(ch=='1')     //如果输入的ch等于1，则结束本次循环 
			   continue;
		}
		while(1)
		{
			toxy(45,i);
			printf("请输入您要修改的图书的编号：");
			scanf("%d",&x);getchar();
			if(x>j||x==0)     
			{
				toxy(45,++i);
				printf("输入错误，请重新输入!");
				Sleep(500);
			}
			else
			{
				break;
			}
		}
		p=head;     //让p重新指向表头 
		while(p!=NULL&&p->x!=x)   //遍历链表查询符合条件的结点 
		{
			p=p->next;
		}
		if(p)    //如果p不为空 
		{
			system("cls");
			//输入要修改的信息 
			toxy(48,8);
			printf("请输入图书登录号(小于10位数)：");
			scanf("%s",number);getchar();strcpy(p->number,number);
			toxy(48,10);
			printf("请输入书名(小于10位数)：");
			scanf("%s",name);getchar();strcpy(p->name,name);
			toxy(48,12);
			printf("请输入作者名(小于10位数)：");
			scanf("%s",author);getchar();strcpy(p->author,author);
			toxy(48,14);
			printf("请输入图书类别(小于10位数)：");
			scanf("%s",type);getchar();strcpy(p->type,type);
			toxy(48,16);
			printf("请输入图书出版单位(小于10位数)：");
			scanf("%s",publish);getchar();strcpy(p->publish,publish);
			toxy(48,18);
			printf("请输入图书出版时间(小于8位数)：");
			scanf("%s",time);getchar();strcpy(p->time,time);
			toxy(48,20);
			printf("请输入图书价格：");
			scanf("%f",&price);getchar();p->price=price;
			toxy(48,22);
			printf("请输入图书数量：");
			scanf("%d",&num);getchar();p->num=num;
		}
		color(7);
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("|     是否确认修改？    |");
		toxy(46,12);
		printf("| 1.是             2.否 |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)   //利用死循环防止其他按键干扰 
		{
			t=getch();
			if(t=='1')
			{
				break;
			} 
			else if(t=='2')
			{
				menu();
			}
		}
		system("cls");
		toxy(46,10);
		printf("正在修改，请稍后....");
		fp=fopen("mybook","wb");   //以只写的方式打开名为mybook的二进制文件，打开的同时清空文件中的内容 
		if(fp==NULL)
		{
			printf("cannot open file"); 
		}
		if(fwrite(head,N,1,fp)!=1)   //将head写入fp所指向的文件中 
		{
			printf("write error!"); 
		}
		fclose(fp);   //关闭文件 
		if(head!=NULL)   //如果head不为空 
		{
			p=head->next;     //让p指向第二个结点 
			fp=fopen("mybook","ab");   //以追加的方式打开文件 
			if(fp==NULL)
			{
				printf("cannot open file");
			}
			while(p!=NULL)
			{
				if(fwrite(p,N,1,fp)!=1)//将p写入fp所指向的文件中
				{
					printf("write error!");
				}
				p=p->next;
			}
			fclose(fp);  //关闭文件 
		}
		Sleep(500);   //暂停0.5秒 
		system("cls");
		toxy(46,10);
		printf("修改成功！即将自动返回主菜单....");
		Sleep(500);
		break;
	}while(1);
}
 
void del_book()   //删除信息 
{
	do
	{
		system("cls");
		color(9);
		FILE *fp;
		book head,p,pre=NULL; 
		int j=0,x,i=11;
		char name[10];
		char t,c,ch;
		head=ss();    //调用函数，返回表头地址 
		toxy(48,10);
		printf("请输入你要删除的图书的书名：");
		scanf("%s",name);
		p=head;
		while(p!=NULL)
		{
			p->x=0;
			p=p->next;
		}
		p=head;
		toxy(20,5);
		printf("***********************************************图书信息******************************************************");
		toxy(20,8);
		printf("-------------------------------------------------------------------------------------------------------------");
		toxy(20,9);
		printf("登录号        书名        作者名         图书类别         出版单位         出版时间          价格        数量");
		toxy(20,10);
		printf("-------------------------------------------------------------------------------------------------------------");
		while(p!=NULL)
		{
			if(p!=NULL&&strcmp(p->name,name)==0)
			{
				toxy(20,i);
				j++;
				printf("%d:%s%14s%14s%14s   %14s   %18s         %.2f%12d\n",j,p->number,p->name,p->author,p->type,p->publish,p->time,p->price,p->num);
				p->x=j;
				i++;
			}
			p=p->next;
		}
		if(j==0)                   //如果j=0，即没有进入前面的搜索循环，也就是没有找到相应的信息 
		{ 
			toxy(50,i);
			printf("没有找到相应的信息！(按0返回，按1重新搜索)");
			while(1)               //死循环是为了防止除0和1的其他按键干扰 
			{
				ch=getch();
				if(ch=='0')
				{
					menu();break;
				}
				else if(ch=='1')
				{
					break;
				}
			}
			if(ch=='1')     //如果输入的ch等于1，则结束本次循环 
			   continue;
		}
		while(1)
		{
			toxy(45,i);
			printf("请输入您要删除的图书的编号：");
			scanf("%d",&x);getchar();
			if(x>j||x==0)
			{
				toxy(45,++i);
				printf("输入错误，请重新输入!");
				Sleep(500);
			}
			else
			{
				break;
			}
		}
		color(7);
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("|     是否确认删除？    |");
		toxy(46,12);
		printf("| 1.是             2.否 |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)
		{
			t=getch();
			if(t=='1')
			{
				break;
			} 
			else if(t=='2')
			{
				menu();
			}
		}
		p=head;
		while(p!=NULL&&p->x!=x)
		{
			pre=p;
			p=p->next;
		}
		if(p!=NULL)
		{
			if(pre==NULL)
			{
				head=head->next;
			}
			else
			{
				pre->next=p->next;
			}
		}
		free(p);
		fp=fopen("mybook","wb");
		if(fp==NULL)
		{
			printf("cannot open file"); 
		}
		if(fwrite(head,N,1,fp)!=1)
		{
			printf("write error!"); 
		}
		fclose(fp);
		if(head!=NULL)
		{
			p=head->next;
			fp=fopen("mybook","ab");
			if(fp==NULL)
			{
				printf("cannot open file");
			}
			while(p!=NULL)
			{
				if(fwrite(p,N,1,fp)!=1)
				{
					printf("write error!");
				}
				p=p->next;
			}
			fclose(fp);
		}
		system("cls");
		toxy(46,10);
		printf("正在删除，请稍后....");
		Sleep(500);
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("|  删除成功，是否继续？ |");
		toxy(46,12);
		printf("| 1.是             2.否 |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)
		{
			c=getch();
			if(c=='1')
			{
				break;
			}
			else if(c=='2')
			{
				menu();
			}
		}
	}while(1);
}
 
void print_book()   //图书总览 
{
	system("cls");
	color(6);
	book head,p;
	int i=11;
	int sum=0;
	head=ss();
	toxy(20,5);
	printf("***********************************************图书总览******************************************************");
	toxy(20,8);
	printf("-------------------------------------------------------------------------------------------------------------");
	toxy(20,9);
	printf("登录号        书名        作者名         图书类别         出版单位         出版时间          价格        数量");
	toxy(20,10);
	printf("-------------------------------------------------------------------------------------------------------------");
	if(head==NULL)
	{
		toxy(45,11);
		printf("书库暂时没有书哦~赶快去添加几本吧^_^(按任意键返回)");
		getch();
		menu();
	}
	p=head;
	while(p!=NULL)
	{
		toxy(20,i);
		printf("%s%14s%14s%14s   %14s   %18s         %.2f%12d\n",p->number,p->name,p->author,p->type,p->publish,p->time,p->price,p->num);
		i++;
		sum+=p->num;//计算图书总量 
		p=p->next;
	}
	toxy(48,7);
	printf("图书总量为：%d",sum);
	toxy(45,i);
	printf("按任意键返回");
	getch();//不回显函数 
}
 
void find_book()  //查询图书 
{
	do
	{
		system("cls");  //清屏 
		color(8);
		char t;
		toxy(50,5);
		printf(" 图书查询");
		toxy(48,8);
		printf("|     1.书名  查询      |");
		toxy(48,10);
		printf("|     2.作者  查询      |");
		toxy(48,12);
		printf("|     3.登录号查询      |");
		toxy(48,14);
		printf("|     4.出版社查询      |");
		toxy(48,16);
		printf("|     5.模糊  查询      |");
		toxy(50,18);
		printf("按0返回主菜单");
		t=getch();
		switch(t)
		{
			case '0':menu();break;
			case '1':find_name_book();break;
			case '2':find_author_book();break;
			case '3':find_number_book();break;
			case '4':find_publish_book();break;
			case '5':fuzzy_search();break;
			default :break;
		 } 
	}while(1);
}
 
void find_name_book()  //按名字查询 
{
	system("cls");
	color(8);
	book head,p;
	int i=11;
	head=ss();
	char name[10];
	toxy(48,8);
	printf("请输入您要查询图书的书名：");
	gets(name);
	toxy(48,10);
	printf("正在查询....");
	Sleep(500);
	p=head;
	toxy(20,5);
	printf("***********************************************图书总览******************************************************");
	toxy(20,8);
	printf("-------------------------------------------------------------------------------------------------------------");
	toxy(20,9);
	printf("登录号        书名        作者名         图书类别         出版单位         出版时间          价格        数量");
	toxy(20,10);
	printf("-------------------------------------------------------------------------------------------------------------");
	while(p!=NULL)
	{
		if(p!=NULL&&strcmp(p->name,name)==0)
		{
			toxy(20,i);
			printf("%s%14s%14s%14s   %14s   %18s         %.2f%12d\n",p->number,p->name,p->author,p->type,p->publish,p->time,p->price,p->num);
			i++;
		}
		p=p->next;
	}
	toxy(45,i);
	printf("按任意键返回！");
	getch();
	find_book();
}
 
void find_author_book()   //按作者名查询 
{
	system("cls");
	color(8);
	book head,p;
	int i=11;
	head=ss();
	char author[10];
	toxy(48,8);
	printf("请输入您要查询图书的作者名：");
	gets(author);
	toxy(48,10);
	printf("正在查询....");
	Sleep(500);
	p=head;
	toxy(20,5);
	printf("***********************************************图书总览******************************************************");
	toxy(20,8);
	printf("-------------------------------------------------------------------------------------------------------------");
	toxy(20,9);
	printf("登录号        书名        作者名         图书类别         出版单位         出版时间          价格        数量");
	toxy(20,10);
	printf("-------------------------------------------------------------------------------------------------------------");
	while(p!=NULL)
	{
		if(p!=NULL&&strcmp(p->author,author)==0)
		{
			toxy(20,i);
			printf("%s%14s%14s%14s   %14s   %18s         %.2f%12d\n",p->number,p->name,p->author,p->type,p->publish,p->time,p->price,p->num);
			i++;
		}
		p=p->next;
	}
	toxy(45,i);
	printf("按任意键返回！");
	getch();
	find_book();
}
 
void find_number_book()   //按图书编号查询 
{
	system("cls");
	color(8);
	book head,p;
	int i=11;
	head=ss();
	char number[10];
	toxy(48,8);
	printf("请输入您要查询图书的登录号：");
	gets(number);
	toxy(48,10);
	printf("正在查询....");
	Sleep(500);
	p=head;
	toxy(20,5);
	printf("***********************************************图书总览******************************************************");
	toxy(20,8);
	printf("-------------------------------------------------------------------------------------------------------------");
	toxy(20,9);
	printf("登录号        书名        作者名         图书类别         出版单位         出版时间          价格        数量");
	toxy(20,10);
	printf("-------------------------------------------------------------------------------------------------------------");
	while(p!=NULL)
	{
		if(p!=NULL&&strcmp(p->number,number)==0)
		{
			toxy(20,i);
			printf("%s%14s%14s%14s   %14s   %18s         %.2f%12d\n",p->number,p->name,p->author,p->type,p->publish,p->time,p->price,p->num);
			i++;
		}
		p=p->next;
	}
	toxy(45,i);
	printf("按任意键返回！");
	getch();
	find_book();
}
 
void find_publish_book()   //按出版商查询 
{
	system("cls");
	color(8);
	book head,p;
	int i=11;
	head=ss();
	char publish[10];
	toxy(48,8);
	printf("请输入您要查询图书的出版社：");
	gets(publish);
	toxy(48,10);
	printf("正在查询....");
	Sleep(500);
	p=head;
	toxy(20,5);
	printf("***********************************************图书总览******************************************************");
	toxy(20,8);
	printf("-------------------------------------------------------------------------------------------------------------");
	toxy(20,9);
	printf("登录号        书名        作者名         图书类别         出版单位         出版时间          价格        数量");
	toxy(20,10);
	printf("-------------------------------------------------------------------------------------------------------------");
	while(p!=NULL)
	{
		if(p!=NULL&&strcmp(p->publish,publish)==0)
		{
			toxy(20,i);
			printf("%s%14s%14s%14s   %14s   %18s         %.2f%12d\n",p->number,p->name,p->author,p->type,p->publish,p->time,p->price,p->num);
			i++;
		}
		p=p->next;
	}
	toxy(45,i);
	printf("按任意键返回！");
	getch();
	find_book();
}
 
void fuzzy_search()   //模糊查询 
{
	system("cls");
	color(8);
	book head,p;
	int i=11;
	head=ss();
	char information[10];
	toxy(48,8);
	printf("请输入您要查询图书的信息：");
	gets(information);
	toxy(48,10);
	printf("正在查询....");
	Sleep(500);
	p=head;
	toxy(20,5);
	printf("***********************************************图书总览******************************************************");
	toxy(20,8);
	printf("-------------------------------------------------------------------------------------------------------------");
	toxy(20,9);
	printf("登录号        书名        作者名         图书类别         出版单位         出版时间          价格        数量");
	toxy(20,10);
	printf("-------------------------------------------------------------------------------------------------------------");
	while(p!=NULL)
	{
		if(p!=NULL&&(strcmp(p->name,information)==0||strcmp(p->author,information)==0||strcmp(p->number,information)==0||strcmp(p->publish,information)==0))
		{
			toxy(20,i);
			printf("%s%14s%14s%14s   %14s   %18s         %.2f%12d\n",p->number,p->name,p->author,p->type,p->publish,p->time,p->price,p->num);
			i++;
		}
		p=p->next;
	}
	toxy(45,i);
	printf("按任意键返回！");
	getch();
	find_book();
}
 
void save_book(book p)   //将p中内容写入文件 
{
	FILE *fp;    //文件指针 
	fp=fopen("mybook","ab");   //以追加的方式打开名字为mybook的二进制文件 
	if(fp==NULL)
	{
		printf("cannot open file");
	}
	if(fwrite(p,N,1,fp)!=1)   //将p所指向的一段大小为N的内容存入fp所指向的文件中 
	{
		printf("write error");
	}
	fclose(fp);    //关闭文件  
 } 
 
void over()       //退出软件 
{
	char t;
	toxy(48,11);
	printf("-----------------------");
	toxy(48,12);
	printf("|   您确定要退出吗？  |");
	toxy(48,14);
	printf("| 1.确定     2.取消   |");
	toxy(48,15);
	printf("-----------------------");
	while(1)
	{
		t=getch();         //输入t
		switch(t)
		{
			case '1':
			system("cls");
		    color(6);
			toxy(48,10);
			printf("正在安全退出....");
			Sleep(1000);     //暂停1秒 
			system("cls");
			color(8);
			toxy(48,10);
			printf("已安全退出软件");
			toxy(48,12);
			printf("谢谢使用！");
			toxy(48,14);
			printf("by-by^_^");
			exit(0);  break; //终止程序 
			case '2':
			menu(); break;   //调用函数，进入菜单 
			default :break;
		}
	}
} 
 
main()   //简洁明了的主函数 
{
	menu();//菜单 
}

