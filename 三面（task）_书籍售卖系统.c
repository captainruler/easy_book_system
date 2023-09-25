#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 各数组大小
#define NAME_MAX 20
#define AUTHOR_MAX 20
#define INSTR_MAX 20
#define BOOK_MAX 100
// 函数声明
int storebook();
void printbook();
void findbook();
void deletebook();
void insertbook();
void changebook();
void storedata();
// 创建结构体数组
typedef struct
{
	char name[NAME_MAX];
	char author[AUTHOR_MAX];
	double prize;
	char instroduction[INSTR_MAX];
	int love;
} stru;

stru book[BOOK_MAX]; // 创建一个结构体数组进行存放

int num = 0; // 计数
FILE *fp;

// 主函数
int main()
{

	int flag;

	// 循环选择菜单
	while (1)
	{
		printf("please input 1-8 to pick your choice:\n");
		printf("\n================================\n");
		printf("1--store  book.\n");
		printf("2--print information of book\n");
		printf("3--find book.\n");
		printf("4--delete book\n");
		printf("5--exit.\n");
		printf("6--insert book.\n");
		printf("7--store data book.\n");
		printf("8--changebook.\n");
		printf("\n================================\n");
		printf("your choice:");
		scanf("%d", &flag);
		switch (flag)
		{
		case 1:
			flag = storebook();
			if (flag == 0)
				break;
		case 2:
			printbook();
			break;
		case 3:
			findbook();
			break;
		case 4:
			deletebook();
			break;
		case 5:
			printf("Byebye");
			exit(0);
		case 6:
			insertbook();
			break;
		case 7:
			storedata();
			break;
		case 8:
			changebook();
			break;
		default:
			printf("Please input a valid choice\n");
		}
	}
	return 0;
}

// 寻找函数，寻找书名
int findname(stru *book, char name[])
{
	int i = 0;
	for (i = 0; i < num; i++)
	{
		if (strcmp(book[i].name, name) == 0)
		{

			return i;
		}
	}

	return -1; // 如果找不到我们需要的书名
}
// 操作一，储存书本信息
int storebook(int *p)
{
	int h, i;
	printf("How many book do you want to add?\n");
	scanf_s("%d", &h);
	for (i = 0; i < h; i++)
	{
		printf("please input the book%d's name, author and price:", num + 1);
		scanf("%20s %20s %lf", &book[num].name, &book[num].author, &book[num].prize);
		printf("please input the introduction to the book:");
		scanf("%s", &book[num].instroduction);
		printf("if it is the book you love? (1 to flag love and 0 to not):");
		scanf("%d", &book[num].love);
		num++;
		if (book[num].love != 0 && book[num].love != 1)
			break;
	}

	return 0;
}

// 操作二，打印书本信息

void printbook()
{
	int i;
	printf("================================\n");
	printf("There are %d books in total\n", num);
	printf("number\t\t name\t\t author\t\t price\n");
	for (i = 0; i < num; i++)
	{
		printf("%d\t\t %s\t\t %s\t\t %.2f\n", i + 1, book[i].name, book[i].author, book[i].prize);

		printf("instroduction: %s\n", book[i].instroduction);
		printf("love: %d\n", book[i].love);
	}
	printf("================================\n");
}

// 操作三，用书名查找书本信息
void findbook()
{
	char name[NAME_MAX];
	int pos;
	printf("Please input the book's name you want to find: ");
	scanf("%s", name);

	pos = findname(book, name);
	if (pos == -1)
	{
		printf("not found!\n");
		return;
	}
	else
	{
		printf("found!\n");
		printf("number\t\t name\t\t author\t\t price\n");
		printf("%d\t\t %s\t\t %s\t\t %.2f\n", pos,
			   book[pos].name,
			   book[pos].author,
			   book[pos].prize);

		printf("instroduction: %s\n", book[pos].instroduction);
		printf("love: %d\n", book[pos].love);

		printf("================================\n");
	}
}

// 操作四，用书名删除书本
void deletebook()
{
	char name[NAME_MAX];
	int pos, i;

	printf("Please input the book's name you want to delete:");
	scanf("%s", name);

	pos = findname(book, name);

	if (pos == -1)
	{
		printf("can't find the book you want to delete!\n");
		return;
	}

	for (i = pos; i < num - 1; i++)
	{
		book[i] = book[i + 1];
	}

	num--;
	printf("deleted!\n");
}

// 操作六，插入书本信息
void insertbook()
{
	int i, n;
	if (num == 0)
	{
		printf("Please add some book first\n");
		return;
	}
	else
	{
		printf("where do you want to insert a book(1~%d<include %d>)", num, num);
		scanf("%d", &n);

		if (n > num)
		{
			printf("please input the book's name, author and price:");
			scanf("%20s %20s %lf", &book[0].name, &book[0].author, &book[0].prize);
			printf("please input the introduction to the book:");
			scanf("%s", &book[0].instroduction);
			printf("if it is the book you love? (1 to flag love and 0 to not):");
			scanf("%d", &book[0].love);
			printf("Segmentation fault\n");
			exit(0);
		}

		for (i = num;; i--)
		{
			book[i] = book[i - 1];
			if (i == n)
				break;
		}
		printf("please input the book's name, author and price:");
		scanf("%20s %20s %lf", &book[n - 1].name, &book[n - 1].author, &book[n - 1].prize);
		printf("please input the introduction to the book:");
		scanf("%s", &book[n - 1].instroduction);
		printf("if it is the book you love? (1 to flag love and 0 to not):");
		scanf("%d", &book[n - 1].love);

		num++;
	}
}

// 操作七，储存数据
void storedata()
{
	int i;
	fp = fopen("file", "w+");
	fprintf(fp, "number\t\t name\t\t author\t\t price\n");

	for (i = 0; i < num; i++)
	{

		fprintf(fp, "%d\t\t %s\t\t %s\t\t %.2f\n", i,
				book[i].name,
				book[i].author,
				book[i].prize);
		fprintf(fp, "instroduction: %s\n", book[i].instroduction);
		fprintf(fp, "love: %d\n", book[i].love);
	}

	printf("Output the data to file\n\n");
	printf("ok you have store the information!\n");

	fclose(fp);
}

// 操作八，修改数据
void changebook()
{

	char name[NAME_MAX];
	int pos, i;

	printf("Please input the book's name you what to change information:\n");
	scanf("%s", name);

	pos = findname(book, name);

	if (pos == -1)
	{
		printf("Can not find book!\n");
		return;
	}
	else
	{
		printf("please input the book's new name, author and price:");
		scanf("%20s %20s %lf", &book[pos].name, &book[pos].author, &book[pos].prize);
		printf("please input the new introduction to the book:");
		scanf("%s", &book[pos].instroduction);
		printf("if it is the book you love? (1 to flag love and 0 to not):");
		scanf("%d", &book[pos].love);

		printf("change success\n");
	}
}
