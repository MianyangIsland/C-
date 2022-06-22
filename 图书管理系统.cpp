#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#define N sizeof(struct BOOK)
 
struct BOOK        //ͼ����Ϣ 
{
	char number[10];   //��¼�� 
	char name[10];     //���� 
	char author[10];    //������ 
	char type[10];      //���� 
	char publish[10];  //���浥λ 
	char time[8];        //����ʱ�� 
	float price;       //�۸� 
	int num;         //���� 
	int x;
	struct BOOK *next;   //ָ���� 
};
typedef struct BOOK Book;
typedef Book *book;	 
 
void HideCursor();    //���ع��
void toxy(int x, int y);    //������ƶ���X,Y���괦
void color(short x);     //������ɫ
void over();             //�˳� 
void menu();           //�˵� 
void input_book();     //ͼ����� 
void save_book(book p);//��ͼ����Ϣ�����ļ� 
void find_book();      //��ѯ 
void print_book();    //ͼ������ 
void del_book();     //ɾ��ͼ�� 
void amend_book();    //�޸���Ϣ 
book ss();
void find_name_book();  //��������ѯ 
void find_author_book(); //�����߲�ѯ 
void find_number_book();  //����¼�Ų�ѯ
void find_publish_book();  //���������ѯ 
void fuzzy_search();     //ģ������ 
 
void HideCursor()     //���ع��
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
 
void toxy(int x, int y)      //������ƶ���X,Y���괦
{
COORD pos = { x , y };
HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(Out, pos); 
}
 
void menu()    //�˵� 
{
	do
	{
		system("cls");  //���� 
		HideCursor();  //���ع�� 
		color(15);    //����һ���ÿ�����ɫ 
		char t;
		toxy(50,5);//������ƶ�����50��5�����괦
		printf(" ͼ���ѯ����ϵͳ");
		toxy(48,8);
		printf("|     1.ͼ�����      |");
		toxy(48,10);
		printf("|     2.�޸���Ϣ      |");
		toxy(48,12);
		printf("|     3.ɾ����Ϣ      |");
		toxy(48,14);
		printf("|     4.ͼ���ѯ      |");
		toxy(48,16);
		printf("|     5.ͼ������      |");
		toxy(48,18);
		printf("|     6.�˳����      |");
		t=getch();    //�����Ժ��� 
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
 
book ss()      //���ļ��е����ݶ����������У�����ֵΪ��ͷ��ַ 
{
	FILE *fp;       //�ļ�ָ�� 
	int n=0;
	book head=NULL;
	book p2,p,pr=NULL;
	fp=fopen("mybook","ab+");     //��ֻ���ķ�ʽ���ļ� 
	if(fp==NULL)
	{
		printf("cannot open file\n");
	}
	while(!feof(fp))        //�ж��ļ�λ�ñ�־�Ƿ��ƶ����ļ�ĩβ 
	{
	   n++;
	   	p=(book)malloc(N); //���ڴ�����һ�οռ� 
	   fread(p,N,1,fp);     //��fp��ָ����ļ��е����ݸ���p 
	   if(n==1)
	   {
	      head=p;
	      p2=p;
	    }
	    else             //�������� 
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
    fclose(fp);    //�ر��ļ� 
    return head;   //����ͷָ�� 
}
 
void input_book()    //ͼ��¼�� 
{
	do
	{
		system("cls");
		color(10);
		char t;
		book p;
		p=(book)malloc(N);     //����ռ� 
		//����ͼ����Ϣ
		toxy(48,8);
		printf("������ͼ���¼��(С��10λ��)��");    
		scanf("%s",p->number);getchar();
		toxy(48,10);
		printf("����������(С��10λ��)��");
		scanf("%s",p->name);getchar();
		toxy(48,12);
		printf("������������(С��10λ��)��");
		scanf("%s",p->author);getchar();
		toxy(48,14);
		printf("������ͼ�����(С��10λ��)��");
		scanf("%s",p->type);getchar();
		toxy(48,16);
		printf("������ͼ����浥λ(С��10λ��)��");
		scanf("%s",p->publish);getchar();
		toxy(48,18);
		printf("������ͼ�����ʱ��(С��8λ��)��");
		scanf("%s",p->time);getchar();
		toxy(48,20);
		printf("������ͼ��۸�");
		scanf("%f",&p->price);getchar();
		toxy(48,22);
		printf("������ͼ��������");
		scanf("%d",&p->num);
		save_book(p);
		toxy(48,24);
		printf("���ڱ���....");
		Sleep(500);   //��ͣ0.5�� 
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("| ����ɹ����Ƿ������  |");
		toxy(46,12);
		printf("| 1.��             2.�� |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)    //������ѭ������Ч��ֹ������������ 
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
 
void amend_book()    //�޸�ͼ����Ϣ 
{
	do
	{
		system("cls");
		color(10);
		book head,p;
		int i=11,j=0,x;
		char ch,t;
		FILE *fp;    //�ļ�ָ�� 
		char _name[10];
		char number[10];   //��¼�� 
		char name[10];     //���� 
		char author[10];    //������ 
		char type[10];      //���� 
		char publish[10];  //���浥λ 
		char time[8];        //����ʱ�� 
		float price;       //�۸� 
		int num;         //���� 
		head=ss();
		p=head;
		toxy(48,10);
		printf("��������Ҫ�޸ĵ�ͼ���������");
		gets(_name); 
		while(p!=NULL)    //��ʼ��p->xΪ0 
		{
			p->x=0;
			p=p->next;
		}
		p=head;    //��p����ָ���ͷ 
		toxy(20,5);
		printf("***********************************************ͼ����Ϣ******************************************************");
		toxy(20,8);
		printf("-------------------------------------------------------------------------------------------------------------");
		toxy(20,9);
		printf("��¼��        ����        ������         ͼ�����         ���浥λ         ����ʱ��          �۸�        ����");
		toxy(20,10);
		printf("-------------------------------------------------------------------------------------------------------------");
		while(p!=NULL)
		{
			if(p!=NULL&&strcmp(p->name,_name)==0)
			{
				toxy(20,i);
				j++;
				printf("%d:%s%14s%14s%14s   %14s   %18s         %.2f%12d\n",j,p->number,p->name,p->author,p->type,p->publish,p->time,p->price,p->num);
				p->x=j;    //�����ϲ�ѯ��׼�Ľ���� 
				i++;
			}
			p=p->next;
		}
		if(j==0)                   //���j=0����û�н���ǰ�������ѭ����Ҳ����û���ҵ���Ӧ����Ϣ 
		{ 
			toxy(50,i);
			printf("û���ҵ���Ӧ����Ϣ��(��0���أ���1��������)");
			while(1)               //��ѭ����Ϊ�˷�ֹ��0��1�������������� 
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
			if(ch=='1')     //��������ch����1�����������ѭ�� 
			   continue;
		}
		while(1)
		{
			toxy(45,i);
			printf("��������Ҫ�޸ĵ�ͼ��ı�ţ�");
			scanf("%d",&x);getchar();
			if(x>j||x==0)     
			{
				toxy(45,++i);
				printf("�����������������!");
				Sleep(500);
			}
			else
			{
				break;
			}
		}
		p=head;     //��p����ָ���ͷ 
		while(p!=NULL&&p->x!=x)   //���������ѯ���������Ľ�� 
		{
			p=p->next;
		}
		if(p)    //���p��Ϊ�� 
		{
			system("cls");
			//����Ҫ�޸ĵ���Ϣ 
			toxy(48,8);
			printf("������ͼ���¼��(С��10λ��)��");
			scanf("%s",number);getchar();strcpy(p->number,number);
			toxy(48,10);
			printf("����������(С��10λ��)��");
			scanf("%s",name);getchar();strcpy(p->name,name);
			toxy(48,12);
			printf("������������(С��10λ��)��");
			scanf("%s",author);getchar();strcpy(p->author,author);
			toxy(48,14);
			printf("������ͼ�����(С��10λ��)��");
			scanf("%s",type);getchar();strcpy(p->type,type);
			toxy(48,16);
			printf("������ͼ����浥λ(С��10λ��)��");
			scanf("%s",publish);getchar();strcpy(p->publish,publish);
			toxy(48,18);
			printf("������ͼ�����ʱ��(С��8λ��)��");
			scanf("%s",time);getchar();strcpy(p->time,time);
			toxy(48,20);
			printf("������ͼ��۸�");
			scanf("%f",&price);getchar();p->price=price;
			toxy(48,22);
			printf("������ͼ��������");
			scanf("%d",&num);getchar();p->num=num;
		}
		color(7);
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("|     �Ƿ�ȷ���޸ģ�    |");
		toxy(46,12);
		printf("| 1.��             2.�� |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)   //������ѭ����ֹ������������ 
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
		printf("�����޸ģ����Ժ�....");
		fp=fopen("mybook","wb");   //��ֻд�ķ�ʽ����Ϊmybook�Ķ������ļ����򿪵�ͬʱ����ļ��е����� 
		if(fp==NULL)
		{
			printf("cannot open file"); 
		}
		if(fwrite(head,N,1,fp)!=1)   //��headд��fp��ָ����ļ��� 
		{
			printf("write error!"); 
		}
		fclose(fp);   //�ر��ļ� 
		if(head!=NULL)   //���head��Ϊ�� 
		{
			p=head->next;     //��pָ��ڶ������ 
			fp=fopen("mybook","ab");   //��׷�ӵķ�ʽ���ļ� 
			if(fp==NULL)
			{
				printf("cannot open file");
			}
			while(p!=NULL)
			{
				if(fwrite(p,N,1,fp)!=1)//��pд��fp��ָ����ļ���
				{
					printf("write error!");
				}
				p=p->next;
			}
			fclose(fp);  //�ر��ļ� 
		}
		Sleep(500);   //��ͣ0.5�� 
		system("cls");
		toxy(46,10);
		printf("�޸ĳɹ��������Զ��������˵�....");
		Sleep(500);
		break;
	}while(1);
}
 
void del_book()   //ɾ����Ϣ 
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
		head=ss();    //���ú��������ر�ͷ��ַ 
		toxy(48,10);
		printf("��������Ҫɾ����ͼ���������");
		scanf("%s",name);
		p=head;
		while(p!=NULL)
		{
			p->x=0;
			p=p->next;
		}
		p=head;
		toxy(20,5);
		printf("***********************************************ͼ����Ϣ******************************************************");
		toxy(20,8);
		printf("-------------------------------------------------------------------------------------------------------------");
		toxy(20,9);
		printf("��¼��        ����        ������         ͼ�����         ���浥λ         ����ʱ��          �۸�        ����");
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
		if(j==0)                   //���j=0����û�н���ǰ�������ѭ����Ҳ����û���ҵ���Ӧ����Ϣ 
		{ 
			toxy(50,i);
			printf("û���ҵ���Ӧ����Ϣ��(��0���أ���1��������)");
			while(1)               //��ѭ����Ϊ�˷�ֹ��0��1�������������� 
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
			if(ch=='1')     //��������ch����1�����������ѭ�� 
			   continue;
		}
		while(1)
		{
			toxy(45,i);
			printf("��������Ҫɾ����ͼ��ı�ţ�");
			scanf("%d",&x);getchar();
			if(x>j||x==0)
			{
				toxy(45,++i);
				printf("�����������������!");
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
		printf("|     �Ƿ�ȷ��ɾ����    |");
		toxy(46,12);
		printf("| 1.��             2.�� |");
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
		printf("����ɾ�������Ժ�....");
		Sleep(500);
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("|  ɾ���ɹ����Ƿ������ |");
		toxy(46,12);
		printf("| 1.��             2.�� |");
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
 
void print_book()   //ͼ������ 
{
	system("cls");
	color(6);
	book head,p;
	int i=11;
	int sum=0;
	head=ss();
	toxy(20,5);
	printf("***********************************************ͼ������******************************************************");
	toxy(20,8);
	printf("-------------------------------------------------------------------------------------------------------------");
	toxy(20,9);
	printf("��¼��        ����        ������         ͼ�����         ���浥λ         ����ʱ��          �۸�        ����");
	toxy(20,10);
	printf("-------------------------------------------------------------------------------------------------------------");
	if(head==NULL)
	{
		toxy(45,11);
		printf("�����ʱû����Ŷ~�Ͽ�ȥ��Ӽ�����^_^(�����������)");
		getch();
		menu();
	}
	p=head;
	while(p!=NULL)
	{
		toxy(20,i);
		printf("%s%14s%14s%14s   %14s   %18s         %.2f%12d\n",p->number,p->name,p->author,p->type,p->publish,p->time,p->price,p->num);
		i++;
		sum+=p->num;//����ͼ������ 
		p=p->next;
	}
	toxy(48,7);
	printf("ͼ������Ϊ��%d",sum);
	toxy(45,i);
	printf("�����������");
	getch();//�����Ժ��� 
}
 
void find_book()  //��ѯͼ�� 
{
	do
	{
		system("cls");  //���� 
		color(8);
		char t;
		toxy(50,5);
		printf(" ͼ���ѯ");
		toxy(48,8);
		printf("|     1.����  ��ѯ      |");
		toxy(48,10);
		printf("|     2.����  ��ѯ      |");
		toxy(48,12);
		printf("|     3.��¼�Ų�ѯ      |");
		toxy(48,14);
		printf("|     4.�������ѯ      |");
		toxy(48,16);
		printf("|     5.ģ��  ��ѯ      |");
		toxy(50,18);
		printf("��0�������˵�");
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
 
void find_name_book()  //�����ֲ�ѯ 
{
	system("cls");
	color(8);
	book head,p;
	int i=11;
	head=ss();
	char name[10];
	toxy(48,8);
	printf("��������Ҫ��ѯͼ���������");
	gets(name);
	toxy(48,10);
	printf("���ڲ�ѯ....");
	Sleep(500);
	p=head;
	toxy(20,5);
	printf("***********************************************ͼ������******************************************************");
	toxy(20,8);
	printf("-------------------------------------------------------------------------------------------------------------");
	toxy(20,9);
	printf("��¼��        ����        ������         ͼ�����         ���浥λ         ����ʱ��          �۸�        ����");
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
	printf("����������أ�");
	getch();
	find_book();
}
 
void find_author_book()   //����������ѯ 
{
	system("cls");
	color(8);
	book head,p;
	int i=11;
	head=ss();
	char author[10];
	toxy(48,8);
	printf("��������Ҫ��ѯͼ�����������");
	gets(author);
	toxy(48,10);
	printf("���ڲ�ѯ....");
	Sleep(500);
	p=head;
	toxy(20,5);
	printf("***********************************************ͼ������******************************************************");
	toxy(20,8);
	printf("-------------------------------------------------------------------------------------------------------------");
	toxy(20,9);
	printf("��¼��        ����        ������         ͼ�����         ���浥λ         ����ʱ��          �۸�        ����");
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
	printf("����������أ�");
	getch();
	find_book();
}
 
void find_number_book()   //��ͼ���Ų�ѯ 
{
	system("cls");
	color(8);
	book head,p;
	int i=11;
	head=ss();
	char number[10];
	toxy(48,8);
	printf("��������Ҫ��ѯͼ��ĵ�¼�ţ�");
	gets(number);
	toxy(48,10);
	printf("���ڲ�ѯ....");
	Sleep(500);
	p=head;
	toxy(20,5);
	printf("***********************************************ͼ������******************************************************");
	toxy(20,8);
	printf("-------------------------------------------------------------------------------------------------------------");
	toxy(20,9);
	printf("��¼��        ����        ������         ͼ�����         ���浥λ         ����ʱ��          �۸�        ����");
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
	printf("����������أ�");
	getch();
	find_book();
}
 
void find_publish_book()   //�������̲�ѯ 
{
	system("cls");
	color(8);
	book head,p;
	int i=11;
	head=ss();
	char publish[10];
	toxy(48,8);
	printf("��������Ҫ��ѯͼ��ĳ����磺");
	gets(publish);
	toxy(48,10);
	printf("���ڲ�ѯ....");
	Sleep(500);
	p=head;
	toxy(20,5);
	printf("***********************************************ͼ������******************************************************");
	toxy(20,8);
	printf("-------------------------------------------------------------------------------------------------------------");
	toxy(20,9);
	printf("��¼��        ����        ������         ͼ�����         ���浥λ         ����ʱ��          �۸�        ����");
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
	printf("����������أ�");
	getch();
	find_book();
}
 
void fuzzy_search()   //ģ����ѯ 
{
	system("cls");
	color(8);
	book head,p;
	int i=11;
	head=ss();
	char information[10];
	toxy(48,8);
	printf("��������Ҫ��ѯͼ�����Ϣ��");
	gets(information);
	toxy(48,10);
	printf("���ڲ�ѯ....");
	Sleep(500);
	p=head;
	toxy(20,5);
	printf("***********************************************ͼ������******************************************************");
	toxy(20,8);
	printf("-------------------------------------------------------------------------------------------------------------");
	toxy(20,9);
	printf("��¼��        ����        ������         ͼ�����         ���浥λ         ����ʱ��          �۸�        ����");
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
	printf("����������أ�");
	getch();
	find_book();
}
 
void save_book(book p)   //��p������д���ļ� 
{
	FILE *fp;    //�ļ�ָ�� 
	fp=fopen("mybook","ab");   //��׷�ӵķ�ʽ������Ϊmybook�Ķ������ļ� 
	if(fp==NULL)
	{
		printf("cannot open file");
	}
	if(fwrite(p,N,1,fp)!=1)   //��p��ָ���һ�δ�СΪN�����ݴ���fp��ָ����ļ��� 
	{
		printf("write error");
	}
	fclose(fp);    //�ر��ļ�  
 } 
 
void over()       //�˳���� 
{
	char t;
	toxy(48,11);
	printf("-----------------------");
	toxy(48,12);
	printf("|   ��ȷ��Ҫ�˳���  |");
	toxy(48,14);
	printf("| 1.ȷ��     2.ȡ��   |");
	toxy(48,15);
	printf("-----------------------");
	while(1)
	{
		t=getch();         //����t
		switch(t)
		{
			case '1':
			system("cls");
		    color(6);
			toxy(48,10);
			printf("���ڰ�ȫ�˳�....");
			Sleep(1000);     //��ͣ1�� 
			system("cls");
			color(8);
			toxy(48,10);
			printf("�Ѱ�ȫ�˳����");
			toxy(48,12);
			printf("ллʹ�ã�");
			toxy(48,14);
			printf("by-by^_^");
			exit(0);  break; //��ֹ���� 
			case '2':
			menu(); break;   //���ú���������˵� 
			default :break;
		}
	}
} 
 
main()   //������˵������� 
{
	menu();//�˵� 
}

