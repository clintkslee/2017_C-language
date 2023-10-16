#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define esc 27
#include <string.h>
#include <termios.h>
#include <sys/time.h>
#include <unistd.h>

void space(void);
void word(void);
void short_writing(void);
void long_writing(void);
int getch(void);
int main(void)
	/* 메인화면*/
{
	while(1)
	{
		int choice;//자리, 단어, 짧은 글, 긴 글 중 어떤걸 실행할지 받을 변수
		int c;//버퍼에 남은 '\n'을 비우기 위함
		printf(">>영문 타자 연습<<");
		printf("\n 1) 자리 연습 \n 2) 낱말 연습\n 3) 짧은 글 연습 \n 4) 긴 글 연습 \n 5) 프로그램 종료\n");
		printf("번호를 선택하세요 : ");
		scanf("%d",&choice);

		switch(choice)//choice에 따라 각 함수 실행
		{
			case 1 :
				system("clear");
				space();
				break;
			case 2 : 
				system("clear");
				word();
				break;
			case 3 :
				system("clear");
				short_writing();
				break;
			case 4 :
				system("clear");
				long_writing();
				break;
			case 5 : 
				system("clear");
				return 0;
			default :
				while(c= getchar() != '\n');
				printf("\n잘못된입력입니다.\n");
				sleep(1);
				system("clear");


		}
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*자리연습*/
void space(void)
{
	int n;
	srand(time(NULL));
	int progress=0;//진행도
	int error=0;//에러
	double accuracy=100;//정확도
	double acc=0;//맞은 개수
	int total=0;
	char arr[52];
	char input;
	char problem;
	for(n=0;n<52;n++)//배열에 문자 저장
	{
		if(n<26)
			arr[n]=n+97;
		else
			arr[n]=n+39;
	}
	while(1)
	{
		problem = arr[rand()%52];
		while(1)
		{
			system("clear");
			printf(">>영문 타자 연습 프로그램 : 자리 연습<<\n");
			printf("진행도 : %d%%  오타수 : %d  정확도 : %.2f%%\n\n\n", progress,error,accuracy);
			if(progress >= 100)//진행도가 100이 뜬상태에서 종료되도록 만듬
			{
				progress++;
				break;
			}
			printf("%c\n",problem);

			input = getch();
			sleep(0.5);
			if(input == '\n')//엔터에 의해 생긴 공백문자를 없애기 위함
				continue;
			if((int)input == esc)//esc에 의한 탈출
				break;
			if(input == problem)//맞았을때
			{
				progress +=5;
				acc++;
				total++;
				accuracy= 100*(acc/total);
				break;
			}
			else//틀렸을때
			{
				total++;
				error++;
				accuracy= 100*(acc/total);
				printf("\n");
				continue;//틀렸을 때 문자 바뀌지 않음
			}
		}
		if(progress>100)//진행도가 100이 뜬 상태에서 종료되도록 만듬
			break;
		if((int)input== esc)//esc에 의한 탈출
			break;

	}
	while(1)// 메뉴로 가기위해 엔터입력 구현
	{
		if((int)input == esc)//esc에 의한 탈출
		{
			system("clear");
			break;
		}
		sleep(2);
		system("clear");
		char goto_main;
		printf(">>영문 타자 연습프로그램 : 자리 연습<<\n");
		printf("진행도 : %d%% 오타수 : %d 정확도 : %.2f%%\n\n\n",100,error,accuracy);
		printf("메뉴로 가기위해서 엔터키를 입력하시오.");
		goto_main = getchar();
		if(goto_main == '\n')
		{
			system("clear");
			break;
		}

	}
	return;

}
//////////////////////////////////////////////////////////////////////////////////////////////////
void word(void)
{
	int e=0;//###탈출용 문자
	int progress=0;
	int error=0;
	int total=1;
	int problem;
	double accuracy=100;
	double acc=1;
	srand(time(NULL));
	char words[100][20]={
		"cat","dog","people","star","hello","world","monday","box","fox","song","quite","game",
		"phone","fruit","apple","orange","reaction","start","yogurt","blue","white","note","book",
		"wallet","money","bag","door","house","march", "watch","pencil","pocket","mouse","ear",
		"nose","face","eye","easy","wonderful","scratch","interest","hobby","school","banana",
		"shirt","language","sound","music","plant","flower","green","window","math","hat","shoes",
		"bread","noodle","ice","cream","sky","airplain","car","bus","subway","station","element",
		"hamberger","pizza","restaurant","vacation","party","room","number","vest","admit","absent",
		"shy","grade","score","mother","father","sister","brother","uncle","baby","big","small",
		"song","rain","rainbow","scale","piano","guitar","drum","dream","play","park","exercise",
		"navy","bottle"
	};
	char escape[]="###";//탈출 문자 ###
	while(1)
	{
		problem = rand()%100;//랜덤한 문제 생셩
		printf(">>영문 타자 연습 프로그램 : 낱말 연습 <<\n");
		printf("진행도 : %d%%  오타수 : %d  정확도 :  %.2f%%\n\n\n", progress,error,accuracy);

		if(progress>=100)//진행도 100이면 탈출
			break;

		printf("%s\n",words[problem]);
		char input[16];
		scanf("%s",input);

		if(strcmp(input,words[problem]))//틀린경우
		{
			error++;
			total++;
			progress +=5;
			accuracy = 100*(acc/total);
		}
		else//맞는경우
		{
			acc++;
			total++;
			progress += 5;
			accuracy = 100*(acc/total);
		}

		system("clear");
		if(!strcmp(input,escape))
		{
			e=1;
			break;
		}
	}
	while(1)// 메뉴로 가기위해 엔터입력 구현
	{
		if(e)
			break;
		sleep(2);
		system("clear");
		char goto_main;
		while(getchar() != '\n');
		printf("메뉴로 가기위해서 엔터키를 입력하시오.");
		goto_main = getchar();
		if(goto_main == '\n')
		{
			system("clear");
			break;
		}
	}

	return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void short_writing(void)
{
	int enter_remover = getchar();//시작할때 눌렀던 엔터값 버퍼에서 비우기용
	int e=0;//esc로 인한 탈출인지 \n에 의한 탈출인지 구분하는 변수
	int n;
	int total=0;//입력한 총수
	srand(time(NULL));
	int progress=0;//진행도
	int current_time=0;//현재타수
	int highest_current_time=0;//최고타수
	double accuracy=0;//정확도
	int acc=0;//맞은 개수
	int acc2=0;
	int p=0;//acc_or_error 배열의 값을 저장할 변수 (0, 1, 2)
	long long int start_s,start_m, end_s, end_m;//시간을 재는 변수, s는 초(sec) m은 밀리세컨드
	double diff;//시간차를 저장하는 변수
	char a;//문제의 각 자리문자를 받을 변수
	char input;//답의 각 자리입력값을 받을 변수
	char problem;//랜덤으로 문제를 생성하는데 쓸 변수
	char english_short[30][100]={
		"They are rich who have true friends.",
		"The only way to have a friend is to be one.",
		"All people smile in the same language.",
		"When you come to a roadblock, take a detour.",
		"The road is always shorter when two people walk it.",
		"Success is never permanent and failure is never final.",
		"If you fear failure, you shall never succeed.",
		"Fear of failure is the father of failure.",
		"Successful people are those good at failure.",
		"Failure is a detour not a dead-end street.",
		"Love all, trust a few do wrong to none.",
		"You can make more friends with your ears than your mouth.",
		"Treat your friends like family and your family like friends.",
		"Life is very short.",
		"And there's no time for fussing and fighting, my friends.",
		"Every things gonna be alright.","All in my dream.",
		"Keep a smile on your face till 10o'clock and it will stay there all day.",
		"Let him that would move the world first move himself.",
		"Tis better to have loved and lost than never to have loved at all.",
		"Learning is not attained by chance; it must be sought for with ardor and attended to with diligence.",
		"The more we study, the more we discover our ignorance.",
		"The man who goes the farthest is generaly the one who is willing to do and dare.",
		"Experience is the best of schoolmasters, only the school fees are heavy.",
		"Trust men and they will be true to you; treat them greatly and they will show themselves great.",
		"I am not discouraged, because every wrong attemptdiscarded is another step forward.",
		"There is always a better way.",
		"Thinking is not doing.",
		"One of these days is none of these days.",
		"Be quick, but don't hurry. The road to success is always under construction."
	};
	int l=0;
	struct timeval mytime;
	while(1)
	{

		int acc_or_error[100] = {0};//배열 초기화
		char inputarr[100] = "";//배열 초기화
		system("clear");
		problem = rand()%30;
		gettimeofday(&mytime, NULL);//시작 시간을 측정
		start_m = mytime.tv_usec;
		start_s = mytime.tv_sec;
		for(n=0;1;n++)
		{

			system("clear");
			printf(">>영문 타자 연습 프로그램 : 짧은 글 연습<<\n");
			printf("진행도 : %3d%%  현재타수 : %3d  최고타수 : %3d  정확도 : %f%%\n\n\n", progress,current_time,highest_current_time,accuracy);

			if(progress >= 100)//진행도가 100이 되면 탈출
			{
				sleep(2);
				l=1;
				break;
			}

			printf("%s\n",english_short[problem]);//문제 출력
			printf("%s",inputarr);//내가 입력한 문자열 출력
			input = getch();//답 받음
			inputarr[n] = input;//답을 저장
			gettimeofday(&mytime, NULL);//끝나는 시간을 측정
			end_m = mytime.tv_usec;
			end_s = mytime.tv_sec;
			diff = (end_m - start_m)+(end_s - start_s)*1000000;//시간차이 : 밀리세컨드 + 세컨드*100만;(세컨드 = 밀리세컨드*100만)
			current_time = (acc/diff)*60*1000000;//타수 : (맞은 수/ 시간차이)*6천만 ;분당 타수로 고쳐줌
			if(current_time > highest_current_time)//현재타수와 최고타수를 비교해 더 큰 쪽을 최고타수로 재지정
				highest_current_time = current_time;

			a=english_short[problem][n];
			total++;
			if(input == 127)//백스페이스 입력시 글자지우기
			{

				n -=2;
				total-=2;
				inputarr[n+1] ='\0';
				p=acc_or_error[n+1];
				if(total < 1)//아무것도 입력되지 않았을 때 백스페이스 입력시 초기화
				{
					n= -1;
					total=0;
					acc=0;
					int acc_or_error[100] = {0};

				}
				else if(p)//전에 친 문자가 맞았을 때
					acc--;
				else if(p==2)//전에 친 문자가 백스페이스일 때
				{
					p = acc_or_error[n];
					if(p)
						acc--;
					else;
				}
				else;
				acc_or_error[n+1]=2;
				accuracy=100*((double)acc/total);
				if(n==-1)
					accuracy=0;
			}

			else if(input == a)//맞을 때
			{
				acc++;
				accuracy=100*((double)acc/total);
				acc_or_error[n] = 1;
			}
			else if(input == '\n')//엔터 입력시
			{
				e=0;
				progress +=20;
				break;
			}
			else if(input == esc)//esc입력시
			{
				e=1;
				break;
			}
			else//틀릴 때
			{
				accuracy=100*((double)acc/total);
				acc_or_error[n] = 0;
			}
			acc2 +=acc;
		}
		
		current_time = 0;//현재 타수 초기화
		highest_current_time = 0;//최고 타수 초기화
		accuracy=0;//정확도 초기화
		total=0;//입력총수 초기화
		acc=0;//맞은 수 초기화

		if(e||l)//esc입력시 탈출, \n이면 반복문 계속수행
			break;
	}
	while(1)// 메뉴로 가기위해 엔터입력 구현
	{
		if(e)//esc일때 탈출
			break;
		system("clear");
		char goto_main;
		sleep(2);
		printf("맞은 수: %d",acc2);
		printf("메뉴로 가기위해서 엔터키를 입력하시오.");
		goto_main = getchar();
		if(goto_main == '\n')
		{
			system("clear");
			break;
		}
	}
	system("clear");

	return;
}
void long_writing(void)
{
	while(getchar() != '\n');//시작할때 눌렀던 엔터값 버퍼에서 비우기용
	int e=0;//
	int u=0;
	int m=0;
	int n;
	int total=0;
	srand(time(NULL));
	int current_time=0;
	double accuracy=0;
	int acc=0;
	int j;
	int acc2;
	int p=0;
	int b=0;
	int i=0;
	int total2[5]={0};
	int page=0;
	int ent=0;
	long long int start_s,start_m, end_s, end_m;
	double diff;
	char a;
	char input;
	char problem;
	char english_long[4][2][5][150]=
	{
		{//문제1
			{//1p
				{"Born into a working-class family in 1872, Albert C. BArnes grew up in"}
				,{"Philadelphia. He became interested in art when he became friends with"}
				,{"future artist William Glackens in high school. He earned a medical degree"}
				,{"from the University of Pennsylvania and qualified as a doctor in 1892."}
				,{"Barnes decided not to work as a doctor, and after further study he entered"}
			}
			,{//2p
				{"the business world. In 1901, he invented the antiseptic Argyrol with a German"}
				,{"chemist and made a fortune. Using his wealth, he began purchasing hundreds of"}
				,{"paintings. In 1922, he established the Barnes Foundation to promote the"}
				,{"education of fine arts. There he displayed his huge collection without"}
				,{"detailed explanation. He died in a car accident in 1951."}
			}
		}
		,{//문제2
			{//1p 
				{"The above graph shows direct expenditures on education as a percentage of"},
				{"GDP for the five OECD countries with the highest percentages in 2011, by level"},
				{"of education. All the fice countries spent over seven percent of their GDP on"},
				{"direct expenditures on education for all institutions combined. Of the five"},
				{"countries, Denmark spent the highest percentage of GDP for all institutions"}
			}
			,{//2p
				{"combined. In terms of direct expenditures on elementary and secondary education,"},
					{"New Zealand spent the highest percentage of GDP among the five countries."},
					{"As for direct expenditures on postsecondary education, Iceland spent a higher"},
					{"percentage of GDP than the other four countries. Compared with the Republic"},
					{"of korea, lsrael spent a lower percentage of GDP on postsecondary education."}
			}
		}
		,{//문제3
			{//1p
				{"Before I could get off my horse, I heard a disturbing sound. Charlie heard"},
					{"it, too. He stopped abruptly and backed quickly away from the sound."},
					{"The rattling sound seemed to echo down the river, AS I turned my head,"},
					{"I caught a glimpse of a brown and gray curled creature. The rattlesnake was"},
					{"in position to strike. FEar gripped my heart and it pounded furiously. My hands"}
			}
			,{//2p
				{"began to sweat and my legs were trembling. I knew any slight movement might"},
					{"make the deadly snake strike. I had only one choice: to get Charlie out of danger."},
					{"He had the same idea. He spun quickly, avoiding the rattlesnake's attack."},
					{"As we reached a safe distance, my heart rate began to slow to its regular"},
					{"rhythm. I patted Charlie's head and said, 'Good boy. You saved my life.'"}
			}
		}
		,{//문제4
			{//1p
				{"Lock ticked on toward a deadline knows that the more they struggle to find"},
					{"the missing pieces, the harder it is to find them. As soon as the clock stop,"},
					{"on the other hand, the pieces virtually find each other. Why do the answers"},
					{"we missed in an exam so often occur to us as soon as we turn in the test?"},
					{"The answer, surely, is that we are trying too hard. WE are trying"}
			}
			,{//2p
				{"in an anxious or frutrated way, and not surprisingly, this make us"},
					{"tense up. This kind of trying result from doubt. If we didn't doubt"},
					{"our ability to perform the task at hand, we wouldn't need to try. You"}, 
					{"don't 'try' to sit down and pick up the newspaper when you get home from"},
					{"work, do you?"}
			}
		}
	};
	struct timeval mytime;
	while(1)
	{


		int acc_or_error[100] = {0};

		m=0;
		system("clear");
		problem = rand()%4;
		gettimeofday(&mytime, NULL);
		start_m = mytime.tv_usec;
		start_s = mytime.tv_sec;
		char inputarr[5][200]={""};

		while(1)//전체 문제에 대한 시행
		{
			for(n=0;1;n++)//한페이지에 대한 시행
			{
				system("clear");
				printf(">>영문 타자 연습 프로그램 : 긴 글 연습<<\n");
				printf(" 현재타수 : %3d  정확도 : %.2f%%\n\n\n",current_time,accuracy);

				if(ent ==0)
				{
					for(m=0;m<5;m++)
						printf("%s\n",english_long[problem][page][m]);
					printf("\n");
					printf("%s",inputarr[0]);

					input = getch();
					inputarr[0][n] = input;
				}
				else if(ent ==1)
				{
					for(m=0;m<5;m++)
						printf("%s\n",english_long[problem][page][m]);
					printf("\n");
					printf("%s",inputarr[0]);
					printf("%s",inputarr[1]);
					input= getch();
					inputarr[1][n] = input;
				}
				else if(ent ==2)
				{
					for(m=0;m<5;m++)
						printf("%s\n",english_long[problem][page][m]);
					printf("\n");
					printf("%s%s",inputarr[0],inputarr[1]);
					printf("%s",inputarr[2]);
					input= getch();
					inputarr[2][n] = input;
				}
				else if(ent ==3)
				{
					for(m=0;m<5;m++)
						printf("%s\n",english_long[problem][page][m]);
					printf("\n");
					printf("%s%s%s",inputarr[0],inputarr[1],inputarr[2]);
					printf("%s",inputarr[3]);
					input= getch();
					inputarr[3][n] = input;
				}
				else
				{
					for(m=0;m<5;m++)
						printf("%s\n",english_long[problem][page][m]);
					printf("\n");
					printf("%s%s%s%s",inputarr[0],inputarr[1],inputarr[2],inputarr[3]);
					printf("%s",inputarr[4]);
					input= getch();
					inputarr[4][n] = input;
				}
				gettimeofday(&mytime, NULL);
				end_m = mytime.tv_usec;
				end_s = mytime.tv_sec;
				diff = (end_m - start_m)+(end_s - start_s)*1000000;
				current_time = (acc/diff)*60000000;

				a=english_long[problem][page][ent][n];
				total2[ent]++;
				total=0;
				for(m=0;m<5;m++)
					total +=total2[m];
				m=0;

				if(input == 127)//백스페이스 입력시 글자지우기
				{

					n -=2;
					total2[ent]-=2;
					inputarr[ent][n+1] ='\0';
					p=acc_or_error[n+1];
					b= total2[ent];
					if(b < 1)//아무것도 입력되지 않았을 때 백스페이스 입력시 초기화
					{
						n= -1;
						total2[ent]=0;
						acc=acc2;
						int acc_or_error[200] = {0};
						if(n==-1)
						{
							if(ent==0)
							{
								accuracy=0;
								continue;
							}
						}
					}
					else if(p==1)//전에 친 문자가 맞았을 때
						acc--;
					else if(p==2)//전에 친 문자가 백스페이스일 때
					{
						p = acc_or_error[n];
						if(p==1)
							acc--;
						else;
					}
					else;
					total=0;
					for(m=0;m<5;m++)
						total += total2[m];
					acc_or_error[n+1]=2;
					accuracy=100*((double)acc/total);
				}
				else if(input == a)//맞을 때
				{
					acc++;
					accuracy=100*((double)acc/total);
					acc_or_error[n] = 1;
				}
				else if(input == '\n')
				{
					e=0;
					acc2=acc;
					total2[ent]--;//엔터에 의해 늘어난 총 개수를 하나 줄임
					if(strlen(inputarr[ent]) <= strlen(english_long[problem][page][ent]))
					{
						total2[ent] +=(strlen(english_long[problem][page][ent]) - strlen(inputarr[ent]));
						total=0;
						for(m=0;m<5;m++)
							total += total2[m];
						accuracy = 100*((double)acc/total);

					}
					break;
				}
				else if(input == esc)
				{
					e=1;
					break;
				}
				else//틀릴 때
				{
					accuracy=100*((double)acc/total);
					acc_or_error[n] = 0;
				}
			}
			int acc_or_error[200] = {0};
			ent++;


			if(u)
			{
				if(ent==5)
					break;
			}
			if(ent==5)
			{
				ent=0;
				u=1;
				page=1;
				for(m=0;m<5;m++)
				{
					for(j=0;j<200;j++)
						inputarr[m][j]='\0';
				}

			}



			if(e)
				break;
		}
		if(e || u)
			break;
		current_time = 0;
		accuracy=0;//정확도 초기화
		total=0;//입력총수 초기화
		acc=0;//맞은 수 초기화
		system("clear");


	}
	while(1)// 메뉴로 가기위해 엔터입력 구현
	{
		if(e)
			break;
		sleep(1);//
		system("clear");
		char goto_main;
		printf(">>영문 타자 연습 프로그램 : 긴 글 연습<<\n");
		printf(" 현재타수 : %3d  정확도 : %.2f%%\n\n\n",current_time,accuracy);
		sleep(2);
		printf("메뉴로 가기위해서 엔터키를 입력하시오.");
		goto_main = getchar();
		if(goto_main == '\n')
		{
			system("clear");
			break;
		}
	}
	system("clear");


	return;

}

int getch(void)
{
	struct termios old;
	struct termios new;
	int ch;
	tcgetattr( 0, &old );
	new = old;
	new.c_lflag &= ~( ICANON|ECHO );
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	tcsetattr( 0, TCSAFLUSH, &new );
	ch = getchar();
	tcsetattr( 0, TCSAFLUSH, &old );
	return ch;
}



