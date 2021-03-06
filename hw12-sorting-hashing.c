/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a); // 초기화 함수
int freeArray(int *a); // 메모리 해제 함수
void printArray(int *a); // 배열 원소 출력 함수

int selectionSort(int *a); // 선택 정렬 함수
int insertionSort(int *a); // 삽입 정렬 함수
int bubbleSort(int *a); // 버블 정렬 함수
int shellSort(int *a); // 셸 정렬 함수
/* recursive function으로 구현 */
int quickSort(int *a, int n); // 퀵 정렬 함수


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command; // 명령어
	int *array = NULL; // 배열 포인터 변수
	int *hashtable = NULL; // 해쉬테이블 포인터 변수
	int key = -1; // key, index 초기화
	int index = -1;

	srand(time(NULL)); // 난수 생성 srand 함수 (인자 time)

	do{
		printf("\n[----- [Kim Hyeong Jin]  [2021041079] -----]\n"); // 학번 이름 출력
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z': // 메뉴 z :
			initialize(&array); // 초기화 함수 호출
			break;
		case 'q': case 'Q': // 메뉴 q :
			freeArray(array); // 메모리 해제 함수 호출
			break;
		case 's': case 'S': // 메뉴 s :
			selectionSort(array); // 선택 정렬 함수 호출
			break;
		case 'i': case 'I': // 메뉴 i :
			insertionSort(array); // 삽입 정렬 함수 호출
			break;
		case 'b': case 'B': // 메뉴 b :
			bubbleSort(array); // 버블 정렬 함수 호출
			break;
		case 'l': case 'L': // 메뉴 l
			shellSort(array); // 셸 정렬 함수 호출
			break;
		case 'k': case 'K': // 메뉴 k :
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); // 배열 원소 출력 함수 호출
			quickSort(array, MAX_ARRAY_SIZE); // 퀵 정렬 함수 호출
			printf("----------------------------------------------------------------\n");
			printArray(array); // 정렬 후 원소 출력

			break;

		case 'h': case 'H': // 메뉴 h :
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); // 배열 원소 출력
			hashing(array, &hashtable); // 해싱 함수 호출
			printArray(hashtable); // 해쉬테이블 원소 출력
			break;

		case 'e': case 'E': // 메뉴 e :
			printf("Your Key = ");
			scanf("%d", &key); // key 입력
			printArray(hashtable); // 해쉬테이블 원소 출력
			index = search(hashtable, key); // 해쉬테이블에서 검색하여 index에 저장
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]); // key, index, 해쉬테이블 인덱스 출력
			break;

		case 'p': case 'P': // 메뉴 p :
			printArray(array); // 배열 원소 출력 함수 호출
			break;
		default: // 이외의 경우 :
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 에러 메시지
			break;
		}

	}while(command != 'q' && command != 'Q'); // q 입력시 반복문 탈출 후 종료

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // 배열 사이즈 만큼 malloc으로 할당
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a; // *a가 NULL이 아니면 *a값을 temp에 저장

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL) // a가 NULL이 아니면
		free(a); // free()로 메모리 해제
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) { // a가 NULL이면 에러메시지
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // 배열 사이즈까지 인덱스 번호 출력
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // 배열 사이즈까지 원소 출력
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	int min; // 최솟값
	int minindex; // 최솟값의 인덱스
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 배열 원소 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; // 인덱스 초기값 1
		min = a[i]; // 첫번째 원소를 최솟값의 초기값
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) // 반복문으로 최솟값과 최솟값 인덱스 교체
		{
			if (min > a[j]) // a[j]가 min 보다 작으면
			{
				min = a[j]; // a[j]를 min으로 설정

				minindex = j; // 인덱스를 j로 설정
			}
		}
		a[minindex] = a[i]; // a[minindex]에 a[i] 저장
		a[i] = min; // a[i]엔 최솟값 저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 출력
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; // a[i] (초기값 1) 원소를 t에 대입
		j = i; // i 값 j에 대입
		while (a[j-1] > t && j > 0) //a[j-1]이 t보다 크고 j가 0이면 반복
		{
			a[j] = a[j-1]; // a[j-1] 원소를 a[j]에 대입하고 j 감소하여 인덱스를 줄이며 위치 찾아 삽입
			j--;
		}
		a[j] = t; // t를 a[j]에 대입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++) // i 배열 사이즈까지 반복
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++) // j 배열 사이즈까지 반복
		{
			if (a[j-1] > a[j]) // a[j-1] 원소가 a[j]원소보다 크면 t를 이용하여 교체
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 원소 출력

	return 0; // 종료
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 배열 원소 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // 배열 사이즈/2 부터 h>0 까지 h를 2로 나누며 반복
	{
		for (i = 0; i < h; i++) // i가 h보다 작아질 때 까지 반복
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) // j는 i+h 부터 j가 배열 사이즈보다 작아질 때 까지 j=j+h를 하며 반복
			{
				v = a[j]; // a[j] 원소 v에 저장
				k = j; // j를 k에 저장
				while (k > h-1 && a[k-h] > v) // k가 h-1보다 크고, a[k-h]의 원소가 v보다 크면 반복
				{
					a[k] = a[k-h]; // a[k-h]의 원소를 a[k]에 저장
					k -= h; // k=k-h
				}
				a[k] = v; // v를 a[k]에 저장
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 원소 출력

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1) // n이 1보다 크면
	{
		v = a[n-1]; // a[n-1] 원소 v에 저장
		i = -1; // i 초기값 -1
		j = n - 1; // j에 n-1 저장

		while(1)
		{
			while(a[++i] < v); // i 증가시키며 a[++i]가 v보다 작으면 반복하여 왼쪽정렬에서 기준보다 큰 수를 찾음
			while(a[--j] > v);// j 감소시키며 a[++i]가 v보다 작으면 반복하여 오른쪽정렬에서 기준보다 작은 수를 찾음

			if (i >= j) break; // i가 j보다 크거나 같으면 탈출
			t = a[i]; // t 이용하여 a[i]와 a[j] 교체
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i]; // t 이용하여 a[i]와 a[n-1] 교체
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i); // a부터 i까지 앞쪽 정렬
		quickSort(a+i+1, n-i-1); // a+i+1부터 n-i-1까지 뒷쪽 정렬
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; //key 나누기 최대 해쉬테이블 사이즈의 나머지 리턴
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL; // 해쉬테이블 변수 NULL 초기화

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // 배열 사이즈만큼 malloc으로 메모리 할당
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) // 최대 해쉬테이블 사이즈까지 반복
		hashtable[i] = -1; // 배열 원소들에 -1 저장

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1; // 값 -1로 초기화
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) // 배열 사이즈까지 반복
	{
		key = a[i]; // a[i]를 key에 대입
		hashcode = hashCode(key); // hashcode 함수 리턴값을 변수에 저장
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) // 원소가 초기값 -1이면
		{
			hashtable[hashcode] = key; // key값을 저장
		} else 	{

			index = hashcode; // 인덱스에 해쉬코드 저장

			while(hashtable[index] != -1) // -1이 아니면 반복
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; // (++index) % MAX_HASH_TABLE_SIZE 인덱스에 저장
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //hashtable[index]에 key값 대입
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key); // hashcode 함수 리턴값 인덱스에 저장

	if(ht[index] == key) // ht[index]가 key와 같으면
		return index; // index 리턴

	while(ht[++index] != key) // key와 다르면 반복
	{
		index = index % MAX_HASH_TABLE_SIZE; // index 나누기 MAX_HASH_TABLE_SIZE의 나머지를 인덱스에 대입
	}
	return index; // 인덱스 리턴
}



