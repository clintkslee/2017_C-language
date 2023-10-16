#include<stdio.h>
#include<stdlib.h>
#define N 100

int path_arr[N][N]; //경로배열
int onezero_arr[N][N]; //
int ham_arr[N]; //해밀턴 순환 출력용 배열
int city; //도시 수
int number = 0; //해밀턴 순환 개수

int linear_search(void); //선형탐색
void hamiltonian(int, int); //해밀턴 재귀
void array(int arr[N][N], int, int, int);

int main (void)
{
	int i, j; //for문 2차원배열 초기화 시 사용
	int a = 1; //for문 경로 입력시 사용
	int getter; //for길입력 탈출
/////
	while(1)
	{	
		system("clear");
		printf("\n\n도시 개수를 입력하세요(2개 이상) : ");
		scanf("%d", &city);
		while(getchar() != '\n');
		if(city<=1)
		{
			printf("잘못된 입력입니다.");
			continue;
		}
		printf("\n\n");
	
		for(i = 1; i <= city; i++)
		{   
			for(j = 1; j <= city; j++)
				array(path_arr, i, j, 0);
				array(onezero_arr, i, j, 0);
		}
		if(city >= 2)
			break;
	}
		system("clear");
/////
	while(1)
	{
		system("clear");
		printf("\n두 도시의 번호로 경로를 입력합니다. x 입력 시 경로 입력을 종료합니다.\n");
		printf("%-2d번째 경로 입력( i <--> j ) : ", a);
		scanf("%d %d", &i, &j);
		getter = getchar();
		
		if(getter == 120)
		{
			system("clear");
			break;
		}
		array(path_arr, i, j, 1);
		array(path_arr, j, i, 1);
		a++;
		system("clear");
	}
	printf("\n<도시들의 인접행렬> \n\n");
	for(i = 1; i <= city; i++)
	{
		for(j = 1; j <= city; j++)
		{	
			printf("  %2d", path_arr[i][j]);
			if(j != 0 && j % city == 0)
				printf("\n\n\n");
		} 
	}
/////	
	hamiltonian(1,1);

	if(number == 0)
	printf("해밀턴 순환 그래프가 아닙니다.\n");
	else	
	printf("총 %d개의 경로가 존재합니다.\n\n", number);
	
	return 0;
}
/////
int linear_search(void)
{
	int a, b;
	for(a = 1; a < city; a++)
	{
		for(b = a+1; b < city; b++)
		{
			if(ham_arr[a] == ham_arr[b])
				return 2;
		}
	}
	return 1;
}
/////
void hamiltonian(int cur_pos, int cnt)
{ 
    int i;
    if(cur_pos == 1) 
    {	
    	if(cnt > city) 
        {
			if(ham_arr[city] == 1)
			{
				if(linear_search() == 1)
				{
            		ham_arr[0] = 1;
					printf("\n");
            		printf("%2d번 경로 : ", number+1);
					for(i = 0; i < city; i++)
						printf("%2d ㅡ", ham_arr[i]);
					printf("%2d\n\n", ham_arr[city]);
					number++;
				}
			}
     	}    
    }
    else if(cur_pos == 1 && cnt <= city) 
    	return;
	for(i = 1; i <= city; i++)
    {
        if(path_arr[cur_pos][i]==1 && onezero_arr[cur_pos][i] == 0) 
        {
            array(onezero_arr, cur_pos, i, 1);
            array(onezero_arr, i, cur_pos, 1);
            ham_arr[cnt] = i;
            hamiltonian(i, cnt+1);
			array(onezero_arr, cur_pos, i, 0);
            array(onezero_arr, i, cur_pos, 0);

        }
    }
}
/////
void array(int arr[N][N], int x, int y, int input)
{
	arr[x][y] = input;
}
