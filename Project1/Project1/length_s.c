#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define name_size 11
#define data_size 6
#define node_size 20
#pragma warning(disable:4996)
#pragma warning(disable:4013)

typedef struct Node
{
	int x;
	int y;
	int index;
} Nodes;

Nodes Node[node_size] = { 0 };
int size, arr_ind[node_size];
double cmp_len = 0;

FILE *openfile();
void closefile(FILE *f);
int get_data(FILE *f);
void swap(int k, int i);
void get_tour(int k);
double distance();
void print();

int main()
{
	FILE *file_s = NULL;

	file_s = openfile();

	size = get_data(file_s);

	closefile(file_s);

	get_tour(0);

	print();

	return 0;
}

FILE *openfile()
{
	char file_name[name_size] = { 0 };
	FILE *file = NULL;

	printf("읽을 파일을 입력하십시오: ");
	gets(file_name);
	file = fopen(file_name, "r");

	if (file == NULL)
	{
		puts("파일 열기 오류입니다.");
		return openfile();
	}

	return file;
}

void closefile(FILE *f)
{
	fclose(f);

	if (f == NULL)
		puts("파일 닫기 오류입니다.");
}

int get_data(FILE *f)
{
	char data[data_size] = { 0 };
	int nodes = 0, i, size;
	fgets(data, sizeof(data), f);
	size = atoi(data);

	for (i = 0; i < size; i++)
	{
		fscanf(f, "%d %d", &Node[i].x, &Node[i].y);
		Node[i].index = i;
	}

	return size;
}

void swap(int k, int i)
{
	Nodes temp;

	temp = Node[k];

	Node[k] = Node[i];

	Node[i] = temp;
}

void get_tour(int k)
{
	int i, j;
	double dist;

	if (k == size)
	{

		dist = distance();

		if (cmp_len == 0 || cmp_len > dist)
		{
			cmp_len = dist;
			for (j = 0; j < size; j++)
				arr_ind[j] = Node[j].index;
			return;
		}
	}

	for (i = k; i < size; i++)
	{
		swap(k, i);
		get_tour(k + 1);
		swap(k, i);
	}
}

double distance()
{
	int i;
	double dist = 0;
	for (i = 0; i < size; i++)
		dist += sqrt(pow(Node[i].x - Node[i + 1].x, 2) + pow(Node[i].y - Node[i + 1].y, 2));
	dist += sqrt(pow(Node[0].x - Node[size - 1].x, 2) + pow(Node[0].y - Node[size - 1].y, 2));
	return dist;
}

void print()
{
	int i;

	printf("answer: %lf\n", cmp_len);
	printf("[ ");

	for (i = 0; i < size; i++)
		printf("%d ", arr_ind[i]);

	printf(" ]");
}