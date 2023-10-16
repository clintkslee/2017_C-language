#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termio.h>
/////////////////////////////////////////////////////////////////////
typedef struct _node
{
	char* ep;//영단어 가리킬 포인터
	char* kp;//한글 뜻 가리킬 포인터
	struct _node* next;//다음 노드 가리킬 포인터
	struct _node* prev;//이전 노드 가리킬 포인터
}NODE;//노드 구조체
/////////////////////////////////////////////////////////////////////
typedef struct{
	NODE* head;//헤드
	NODE* tail;//테일
	NODE* cur;//커서
	int size;//단어 개수
}DLL;//연결리스트 구조체
/////////////////////////////////////////////////////////////////////
void menu(int *);//메뉴
void printmenu(void);//메뉴 형식 출력
FILE* fileopen(int);//인자로 받은 번호의 파일 열어 파일포인터 리턴
int optioncheck(int);//정렬(1), 셔플(2) 이외의 입력 예외처리
int listcount(void);//단어 파일 개수 리턴
int getch(void);//getch 함수
/////////////////////////////////////////////////////////////////////
NODE* makenode(void);//노드 하나 크기의 공간 할당
NODE* datasave(FILE*);//단어와 뜻을 받아 하나의 노드 생성
DLL* makelist(DLL*, FILE*);//단어 파일 열어 연결리스트 생성
void nodeswap(NODE*, NODE*);//두 노드간 데이터 교환
void sortlist(DLL*);//리스트 사전식 정렬
void sufflelist(DLL*);//리스트 무작의로 섞기
void dellist(DLL*);//연결리스트 구조체 포인터 받아 리스트 전체 삭제
/////////////////////////////////////////////////////////////////////
void wordcorrect(int, int);//단어맞추기
/////////////////////////////////////////////////////////////////////
void print_word(DLL*, int);
void flashcard(int, int, int);//플래시카드
/////////////////////////////////////////////////////////////////////
void hangman(int filenum);//행맨
void wordCount(int *, int);
void getrandom(int *, int *);
void myanswerInit(char *myanswer,int wordCnt);
void printAll(int incorrect, char *myanswer, int wordCnt, char inputW, char *hint);
void wordCheck(char inputW, int cnt, char *wordE, char *myAnswer, int *incorrect);
/////////////////////////////////////////////////////////////////////
void printmanage(void);//단어장 관리 형식 출력
void wordmanage(void);//단어장 관리
/////////////////////////////////////////////////////////////////////
int main (void)
{
	int n=0;//메뉴 함수 내에서 출력 옵션 체크용 변수; 5 이면 반복문 종료
	while(1)
	{
		menu(&n);
		if(n==5)
			break;
		else
			continue;
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////
void menu(int*n)
{
	system("clear");
	int inputcheck, select, num1, num2, num3;
	int listcnt;//단어 파일 개수 
	listcnt=listcount();
	printmenu();
	if(*n==-1)
	{
		printf("잘못된 입력입니다\n");
		printf("번호를 선택하세요 : ");
	}
	else if(*n==-2)
	{
		printf("잘못된 파일번호입니다\n");
		printf("번호를 선택하세요 : ");
	}
	else if(*n==-3)
	{
		printf("잘못된 옵션입니다\n");
		printf("번호를 선택하세요 : ");
	}
	else if(*n==-4)
	{
		printf("속도(초)는 정수만 입력할 수 있습니다\n");
		printf("번호를 선택하세요 : ");
	}
	else
		printf("\n번호를 선택하세요 : ");
	inputcheck=scanf("%d", &select);
	while(getchar()!='\n');
	if(inputcheck!=1||!(1<=select&&select<=5))
	{
		*n=-1;
		return;
	}
	*n=0;
	switch(select)
	{
		case 1://영어 단어 맞추기 
			printf("파일명(일차) : ");
			scanf("%d", &num1);
			while(getchar()!='\n');
			if(num1>listcnt||num1<1)
			{
				*n=-2;
				break;
			}
			printf("출력 방식(알파벳 순서대로 : 1, 무작위 : 2) : ");
			scanf("%d", &num2);
			while(getchar()!='\n');
			*n=optioncheck(num2);
			if(*n==-3) break;
			wordcorrect(num1, num2);
			break;
		case 2://플래쉬카드
			printf("파일명(일차) : ");
			scanf("%d", &num1);
			while(getchar()!='\n');
			if(num1>listcnt||num1<1)
			{
				*n=-2;
				break;
			}
			printf("속도(초) : ");
			inputcheck=scanf("%d", &num2);
			if(num2<1||inputcheck==0||inputcheck==1&&getchar()!='\n')//0이하 정수 또는 소수점(실수 입력 시 버퍼에 남는 '.') 또는 문자 입력될 경우 예외처리
			{
				while(getchar()!='\n');
				*n=-4;
				break;
			}//////////////////////////////////////////////////////// 출력 속도 정수 입력 받을 때 getchar() 수행되는 것 예외처리
			printf("출력 방식(알파벳 순서대로 : 1, 무작위 : 2) : ");
			scanf("%d", &num3);
			while(getchar()!='\n');
			*n=optioncheck(num3);
			if(*n==-3) break;
			flashcard(num1, num2, num3);
			break;
		case 3://행맨(hangman)
			printf("파일명(일차) : ");
			scanf("%d", &num1);
			while(getchar()!='\n');
			if(num1>listcnt||num1<1)
			{
				*n=-2;
				break;
			}
			hangman(num1);
			break;	
		case 4://단어장 관리
			wordmanage();
			break;
		case 5://프로그램 종료
			printf("프로그램이 종료됩니다.\n");
			*n=5;
			return;
	}
}
void printmenu(void)//메뉴 출력
{
	printf(">> 영어 단어 암기 프로그램 <<\n\n");
	printf("1. 영어 단어 맞추기  2. 플래쉬카드\n");
	printf("3. 행맨(hangman)     4. 단어장 관리\n");
	printf("5. 프로그램 종료\n\n");
}
FILE* fileopen(int filenum)//입력받은 번호의 단어장 열어 파일포인터 리턴하는 함수
{
	FILE* fp=NULL;
	char str1[15];
	sprintf(str1, "%d.dic", filenum);
	fp=fopen(str1, "rt");
	if(fp==NULL)
		return NULL;
	return fp;
}
int optioncheck(int num)//입력 예외처리용
{
	if(num==1||num==2)
		return 1;
	else
		return -3;
}
int listcount(void)//dic.list파일에서 단어장 개수 세서 리턴하는 함수
{
	int check, listcnt=0;
	char listbuff[100];
	FILE* listp=fopen("dic.list", "r");
	while(1)
	{
		check=fscanf(listp, "%s", listbuff);
		if(check==EOF)
			break;
		listcnt++;
	}
	fclose(listp);
	return listcnt;
}
int getch(void)//getch()함수
{
	int ch;
	struct termios buf;
	struct termios save;
	tcgetattr(0, &save);
	buf = save;
	buf.c_lflag &= ~(ICANON|ECHO);
	buf.c_cc[VMIN] =1;
	buf.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &buf);
	ch=getchar();
	tcsetattr(0, TCSAFLUSH, &save);
	return ch;
}
/////////////////////////////////////////////////////////////////////
NODE* makenode(void)//NODE 크기의 공간 할당 후 그 공간을 가리키는 포인터 리턴
{
	NODE* node=NULL;
	node=(NODE*)malloc(sizeof(NODE));
	return node;
}
NODE* datasave(FILE* fp)//단어와 뜻을 받아 하나의 노드 생성
{
	char engbuff[15];
	char korbuff[90];
	int check;
	char* cp;
	NODE* node;
	
	check=fscanf(fp, "%s", engbuff);
	if(check!=1)//파일에서 읽어온 단어가 없으면 NULL포인터 반환
		return NULL;
	
	fgets(korbuff, 89, fp);
	korbuff[strlen(korbuff)-1]='\0';
	
	node = makenode();

	cp=(char*)malloc(strlen(engbuff)+1);
	strcpy(cp, engbuff);
	node->ep=cp;
	
	cp=(char*)malloc(strlen(korbuff)+1);
	strcpy(cp, korbuff);
	node->kp=cp;
	
	return node;
}
DLL* makelist(DLL* list, FILE* fp)//파일 포인터를 인자로 받아 해당 파일의 단어들로 연결리스트 생성
{
	NODE* node;
	list->head=NULL;
	list->tail=NULL;
	list->cur=NULL;
	list->size=0;
	
	while(1)
	{
		node=datasave(fp);//하나의 노드 생성
		if(node==NULL)
			break;
		if(list->head==NULL)
		{
			list->tail=node;
			node->next=list->tail;
		}
		else
		{
			list->head->prev=node;
			node->next=list->head;
		}
		node->prev=list->head;
		list->head=node;
		list->size+=1;
	}
	
	list->cur=list->head;
	return list;
}
void nodeswap(NODE*node1, NODE*node2) //두 노드의 data 부분 스왑
{
	char* temp;//데이터를 담을 변수
	
	temp=node1->ep;//node1의 영어 데이터 이동
	node1->ep=node2->ep; // node2의 영어 데이터를 node1로 이동
	node2->ep=temp;//temp의 데이터를 node2의 영어 데이터로 이동
	
	temp=node1->kp;//node1의 뜻 데이터 이동
	node1->kp=node2->kp;//node2의 뜻 데이터를 node1로 이동
	node2->kp=temp;//temp의 데이터를 node2의 뜻 데이터로 이동
}
void sortlist(DLL* list)//리스트 정렬
{
	int i, j;//버블 정렬을 위한 변수
	int num=list->size-1; //단어개수-1
	list->cur=list->head;//커서를 맨 앞으로
	
	for(i=0; i<num; i++)//단어개수-1만큼 반복
	{
		for(j=0; j<num-i; j++)//단어개수-정렬된 개수 반복
		{
			if(strcmp(list->cur->ep, list->cur->next->ep)>0)//내림차순
				nodeswap(list->cur, list->cur->next);//두 노드의 데이터 스왑
			list->cur=list->cur->next;//다음 노드로 이동
		}
		list->cur=list->head;//커서 헤드로 이동
	}
}

void sufflelist(DLL* list)//무작위로 섞기(랜덤한 노드를 가리킨 후 해당 노드와 그 다음 노드의 데이터 스왑)
{
	srand(time(NULL));
	int i,j;//스왑을 위한 변수
	int number=list->size;//단어 개수
	int range=((rand()%30)*100);//랜덤한 큰 정수 지정
	while(1)
	{
		if(range==0)//0이 나올 경우를 대비
		{
			range=((rand()%30)*100);//다시 랜덤한 큰 정수를 지정
			continue;
		}
		else//그렇지 않을경우 반복 안 함
			break;
	}
	for(i=0; i<range; i++)//랜덤한 큰 정수만큼 반복
	{
		list->cur=list->head;//커서를 헤더로 이동
		
		for(j=0; j<(rand()%30)*10; j++)//랜덤한 정수만큼 반복
			list->cur = list->cur->next;//커서를 다음 노드로 이동
		nodeswap(list->cur, list->cur->next);//데이터를 바꿈
	}
	list->cur=list->head;//커서를 헤드로 이동
}
void dellist(DLL* list)//인자로 받은 리스트구조체의 모든 노드 삭제
{
	while(1)
	{
		if(list->size==0)
			break;//사이즈 0이면 종료
		list->cur=list->head;//헤드가 가리키는 노드를 삭제함
		free(list->cur->ep);//데이터 free
		free(list->cur->kp);//데이터 free
		list->head=list->cur->next;
		if(list->size==1)
			list->tail=list->head;
		else
			list->cur->next->prev=list->head;
		free(list->cur);
		list->cur=list->head;
		list->size-=1;
	}
	return;
}
/////////////////////////////////////////////////////////////////////
void wordcorrect(int filenum, int option)
{
	FILE* fp=NULL;
	DLL D;
	DLL* dp=&D;
	char input[15];
	int i=1, cnt=0;
	double score=0.0;
	fp=fileopen(filenum);//파일 열기
	dp=makelist(dp, fp);//리스트 만들기
	dp->cur=dp->head;
	fclose(fp);//파일 닫기
	system("clear");
	printf(">> 영어 단어 암기 프로그램 : 영어 단어 맞추기 <<\n\n");
	sortlist(dp);//리스트 정렬
	if(option==2)//2번이면 셔플
		sufflelist(dp); 
	while(1)
	{
		printf("%d %s ",i++ ,dp->cur->kp);
		printf("-> ");
		scanf("%s", input);
		while(getchar()!='\n');
		if(strcmp(input, ".quit")==0)
			break;
		else if(strcmp(input, dp->cur->ep)==0)
		{
			printf(" correct!\n\n");
			score+=1;
			cnt++;
		}
		else
		{
			printf(" incorrect!\n\n");
			cnt++;
		}
		if(dp->cur==dp->tail)
			break;
		dp->cur=dp->cur->next;
	}
	if(cnt==0)
		printf("당신의 점수는 0점 입니다.\n");//아무것도 입력하지 않고 바로 종료할 경우 0점
	else
		printf("당신의 점수는 %.2f 점 입니다.\n", score/cnt*100);//맞춘 개수/문제 개수 * 100 점으로 출력
	dellist(dp);//리스트 삭제
	printf("\nPress Enter to Continue...\n");
	while(1) {if(getch()=='\n') break;}//ENTER 입력 시 break
	return;
}
/////////////////////////////////////////////////////////////////////
void print_word(DLL* list, int speed)//프린트
{
	system("clear"); //화면 지우기
	printf(">> 영어 단어 암기 프로그램 : 플래쉬카드 <<\n");//UI
	printf("\n\n\n\n\t   %s\n\n\n\n\n\n", list->cur->ep);//영어 출력
	if(speed==0)
		return;//종료 후 출력 카운트 세기 위한 return
	sleep(speed);//대기시간동안 보여줌
	system("clear"); //화면지우기
	printf(">> 영어 단어 암기 프로그램 : 플래쉬카드 <<\n");//UI
	printf("\n\n\n\n\t  %s\n\n\n\n\n\n", list->cur->kp);//뜻 출력
	sleep(speed);//대기시간동안 보여줌
	list->cur=list->cur->next;//다음 단어
	return;//함수 종료
}
void flashcard(int speed, int fnum, int form)//플래시카드
{
	FILE* fp=NULL;
	fp = fileopen(fnum);//입력값(fnum)의 파일 열기
	DLL D;
	DLL* dp=&D;
	dp=makelist(dp,fp);//리스트에 데이터 넣기
	fclose(fp);
	dp->cur=dp->head;//커서를 처음으로
	int number=dp->size;//number : 단어 개수
	int i; // i: 단어 개수만큼 반복
	if(form==1)//알파벳 순서일 때
	{
		sortlist(dp);//알파벳 순서대로 정렬
		for(i=0; i<number; i++)//단어 개수만큼 반복
			print_word(dp, speed);//단어 출력 함수
	}
	else if(form==2)//무작위 일 때
	{
		sufflelist(dp); // 리스트를 무작위로 정렬
		for(i=0; i<number+3; i++)//단어 개수만큼 반복
			print_word(dp, speed);//단어 출력 함수
	}
	for(i=3; i>0; i--)//출력 끝난 후 종료 카운트세기
	{
		print_word(dp, 0);
		printf("%d초 뒤에 종료됩니다.\n", i);
		sleep(1);
	}
	dellist(dp);//출력 완료 후 리스트 삭제
	return;
}
/////////////////////////////////////////////////////////////////////
void hangman(int filenum)
{
	FILE *fp = NULL;
	NODE *node;
	DLL D;
	DLL *dp = &D;
	char strAnswer[100], strHint[100], strmyAnswer[100];//순서대로 답, 힌트, 사용자가 맞춘 단어 출력하는 배열
	char inputW;//입력받을 알파벳을 저장
	int cnt = 1, wordCnt = 0, random, incorrect = 0;
	int i, error = 0;	
	
	wordCount(&wordCnt, filenum);//wordCnt 변수에 단어 개수 배정
	getrandom(&wordCnt, &random);//random  변수에 무작위 숫자 배정
	i = random;//i에 random의 값 배정
	
	fp = fileopen(filenum);
	dp = makelist(dp, fp);//연결리스트 생성(fp포인터가 가리키는 단어장의 단어들로 연결리스트 생성 후 dp가 가리키게 함)
	dp -> cur = dp -> head;//리스트 초기화
	
	while(i--)
		dp->cur = dp->cur->next;//랜덤한 수 i만큼 cur포인터 이동
	strcpy(strAnswer, dp->cur->ep);//cur이 현재 가리키는 노드의 영단어를 strAnswer에 복사
	strcpy(strHint, dp->cur->kp);//cur이 현재 가리키는 노드의 뜻을 strHint에 복사
	dellist(dp);//만들어진 연결리스트 삭제
	
	myanswerInit(strmyAnswer, strlen(strAnswer));//_ _ _ ...으로 초기화	

	while(incorrect != 6)
  	{
	  	 printAll(incorrect, strmyAnswer, wordCnt, inputW, strHint);//행맨 화면 출력
		 printf("\n%d번째 시도 : ", cnt);
		 scanf("%c", &inputW);
		 cnt++;
		 for(int i = 0; i < wordCnt; i++)
		 {
			 if(strmyAnswer[i] == inputW)
				 error = 1;
		 }//입력했던 알파벳 예외 처리
		 if(error == 1)
		 {	error=0;
			 --cnt;
		 }//입력했던 알파벳이면 cnt 증가를 하지 않음
		 wordCheck(inputW, wordCnt, strAnswer, strmyAnswer, &incorrect);//입력받은 단어가 맞는지 틀린지 확인하는 함수
		 if((strcmp(strAnswer, strmyAnswer) == 0))//정답 시 축하메시지 출력
		 {
			 printf("\n");
			 printf("#######################\n");
			 printf("###Congratulation!!!###\n");
			 printf("#######################\n");
			 break;
		 }//다 맞췄을 때 출력
	}
	printf("\nPress Enter to Continue...\n");
	while(1) {if(getch()=='\n') break;}//ENTER 입력 시 break
}
void wordCount(int *wordCnt,int filenum)//단어장 단어 개수 세는 함수
{
	FILE *fp = NULL;
	char strEng[100], strKor[100];
	fp = fileopen(filenum);
	while(1)
	{
		fscanf(fp, "%s %s", strEng, strKor);
		if(feof(fp) != 0)//
			break;
		(*wordCnt)++;
	}
	fclose(fp);
}
void getrandom(int *wordCnt, int *random)//wordCnt에 랜덤한 수 배정하는 함수
{	
	srand(time(NULL));
	(*random) = rand()%(*wordCnt);
}
void myanswerInit(char *myanswer,int wordCnt)//사용자가 맞춘 단어 출력하는 배열 '_'로 초기화하는 함수
{
	int i;
	for(i = 0; i < wordCnt; i++)
		myanswer[i] = '_';
}
void printAll(int incorrect, char *myanswer, int wordCnt, char inputW, char *hint)//행맨 출력 함수
{	
	   system("clear");
		int i, j;
		j = wordCnt;
		printf(">> 영어 단어 암기 프로그램 : 행맨 <<\n");
		printf("(힌트) %s\n\n", hint);
		printf("-------------------+\n");//오타 개수 따른 행맨 출력
			switch(incorrect)
			{
				case 0:
					printf("\n\n\n\n\n\n");
					break;
				case 1:
					printf("                   O\n\n\n\n\n\n");
					break;
				case 2:
					printf("                   O\n");
					printf("                  /\n\n\n\n\n");
					break;
				case 3:
					printf("                   O\n");
					printf("                  /|\n\n\n\n\n");
					break;
				case 4:
					printf("                   O\n");
					printf("                  /|\\\n\n\n\n\n");
					break;
				case 5:
					printf("                   O\n");
					printf("                  /|\\\n");
					printf("                  / \n\n\n\n");
					break;
				case 6:
					printf("                   O\n");
					printf("                  /|\\\n");
					printf("                  / \\\n\n\n\n");
					break;
			}
	
	for(i = 0; i < strlen(myanswer); i++)
	printf(" %c", myanswer[i]);
	printf("\n");
	return;
			
}
void wordCheck(char inputW, int cnt, char *answer, char *myAnswer,int *incorrect)//입력한 문자가 영단어에 있는지 확인하는 함수
{
	int i;
	int check=0, error = 0;
	while(getchar() != '\n');
	for(i = 0; i < cnt; i++)
	{
		if(answer[i] == (inputW))
		{	
			myAnswer[i] = (inputW);
			check = 1;
		}
	}
	if(check != 1)
		(*incorrect)++;
}
/////////////////////////////////////////////////////////////////////
void printmanage(void)
{
	printf(">> 영어 단어 암기 프로그램 : 단어장 관리 <<\n\n");
	printf("1. 새 파일 추가하기  2. 새 단어 추가하기\n");
	printf("3. 단어장 보기       4. 단어 파일 목록보기\n");
	printf("5. 단어장 관리 종료\n\n");
}
void wordmanage(void)
{
	int num, filenum, listcnt, i, che;
	char listbuff[100];//(4)단어 파일 목록 임시 저장하는 배열
	char numbuff[10];//(1),(2)새 파일 추가 또는  입력받은 번호의 단어장 열기 위해 사용되는 배열
	char strbuff[200];//새 단어 추가시 사용되는 배열
	void* check;//(3),(4)fgets가 잘못 수행되어 NULL반환시 반복문 종료조건으로 사용
	FILE *fp=NULL, *listp=NULL;
	system("clear");
	listcnt=listcount();//dic.list에서 단어장 개수 세서 리턴
	while(1)
	{
		system("clear");
		printmanage();
		printf("\n번호를 입력하세요 : ");
		che=scanf("%d", &num);
		if(che!=1||num>5||num<1)
		{
			system("clear");
			while(getchar()!='\n');
			continue;
		}
		getchar();
		if(num==5)
		break;

		switch (num)
		{
			case 1:
				system("clear");
				printf(">> 영어 단어 암기 프로그램 : 단어장 관리 : 새 파일 추가 (%d.dic) <<\n\n", listcnt+1);
				sprintf(numbuff, "%d.dic", listcnt+1);//추가되는 파일명 numbuff배열에 저장
				listp=fopen("dic.list", "a+");//dic.list 열어서 파일명 추가
				if(listcnt%5==0)
					fprintf(listp, "\n");
				fprintf(listp, "%s	", numbuff);
				fclose(listp);//dic.list 닫기
				fp=fopen(numbuff, "w");
				printf(".add 시 입력종료");
				for(i=0; i<20; ++i)//한 번에 최대 20개 단어 입력
				{
					printf("\n(%d/20) : ", i+1);
					fgets(strbuff, 200, stdin);
					strbuff[strlen(strbuff)-1]='\0';
					if(0==strcmp(strbuff, ".add"))
						break;
					fprintf(fp, "%s\n", strbuff);
				}
				fclose(fp);//단어장 파일 닫기
				listcnt++;
				break;
			case 2:
				printf("파일명(일차) : ");
				scanf("%d", &filenum);
				while(getchar()!='\n');
				if(filenum<0 || filenum>listcnt)//없는 파일 번호 예외처리
				{
					printf("## 존재하지 않는 파일입니다 ##\n");
					sleep(2);
					break;
				}
				sprintf(numbuff, "%d.dic", filenum);
				fp=fopen(numbuff, "a");
				system("clear");
				printf(">> 영어 단어 암기 프로그램 : 단어장 관리 : 새 단어 추가 (%d.dic) <<\n\n", filenum);
				printf(".add 시 입력종료");
				for(i=0; i<20; i++)//한 번에 최대 20개 단어 입력
				{
					printf("\n(%d/20) : ", i+1);
					fgets(strbuff, 200, stdin);
					strbuff[strlen(strbuff)-1]='\0';
					if(0==strcmp(strbuff, ".add"))//.add 입력 시 단어 임력 종료
						break;
					fprintf(fp, "%s\n", strbuff);
				}
				fclose(fp);//단어장 파일 닫기
				break;
			case 3:
				printf("파일명(일차) : ");
				scanf("%d", &filenum);
				while(getchar()!='\n');
				if(filenum<0 || filenum>listcnt)//입력받은 번호가 단어장 개수보다 크거나 0이하 정수이면 예외처리
				{
					printf("## 존재하지 않는 파일입니다 ##\n");
					sleep(2);
					break;
				}
				printf("\n-----단어장-----------\n");
				fp=fileopen(filenum);
				while(1)//출력
				{
					check = fgets(strbuff, 200, fp);
					if(check==NULL)//fgets함수가 파일에서 가져올 문자가 없으면 break
						break;
					printf("%s", strbuff);
				}
				fclose(fp);
				printf("\nPress Any Key to Continue...");
				getchar();
				break;
			case 4:
				printf("\n-----단어 파일 목록-----------\n");
				listp=fopen("dic.list", "rt");
				while(1)//출력 
				{
					check = fgets(listbuff, 100, listp);
					if(check==NULL)//fgets함수가 파일에서 가져올 문자가 없으면 break
						break;
					printf("%s", listbuff);
				}
				fclose(listp);
				printf("\n\n");
				printf("Press Any Key to Continue...");
				getchar();
				break;
		}
	}
	return;
}
/////////////////////////////////////////////////////////////////////끝
