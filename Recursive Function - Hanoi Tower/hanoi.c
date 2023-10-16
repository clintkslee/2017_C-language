#include <stdio.h>

int move_cnt = 0;

int hanoi(int, int, int);

int main (void)
{	
	int floor;
	int from = 1, to = 3;
	
	printf("\n input tower floor : ");
	scanf("%d", &floor);
	
	printf("\n\n");
	printf("\n        floor    from     to\n\n");
	
	hanoi(floor, from, to);
	printf("\n	총 %d 회 이동\n\n\n", move_cnt);
	
	return 0;
}


int hanoi(int floor , int from , int to)
{
	int temp;

	if(floor == 1)

	{
		printf("        %-8d %-8d %-8d\n\n", floor, from, to);
		move_cnt++;
		return 0;	
	}

	else
	{
		temp = 6 - (from + to);
		hanoi(floor-1,from,temp);
		printf("        %-8d %-8d %-8d\n\n", floor, from, to);
		move_cnt++;
		hanoi(floor-1, temp ,to);
	}

}


