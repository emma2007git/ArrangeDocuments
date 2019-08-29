#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keywordList.h"

void Init(KeywordList* keywordList)
{
	keywordList->numLimit = 100;
	keywordList->keyword = (Keyword*)malloc(sizeof(Keyword) * (keywordList->numLimit));
	keywordList->numOfKeywords = 0;

	for (int i = 0; i < keywordList->numLimit; i++)
		keywordList->keyword[i].frequency = 0;
	printf("리스트 초기화 완료!!\n");
}

int isFull(KeywordList* keywordList)
{
	if (keywordList->numLimit <= keywordList->numOfKeywords)
		return 1;
	else
		return 0;
}

int expandList(KeywordList* keywordList)
{
	if (!(keywordList->keyword = (Keyword*)realloc(keywordList->keyword, sizeof(Keyword) * (keywordList->numLimit + 10))))
	{
		printf("키워드 목록의 저장 한계를 늘리지 못했습니다.\n");
		return -1;
	}
	printf("키워드 목록의 저장 한계가 늘어났습니다.\n");

	for (int i = keywordList->numLimit; i < keywordList->numLimit + 10; i++)
		keywordList->keyword[i].frequency = 0;

	keywordList->numLimit = keywordList->numLimit + 10;
	printf("현재 키워드 목록 저장 한계: %d\n", keywordList->numLimit);
	return 0;
}

void Search(char* searchWord, KeywordList* keywordList)
{
	int flag = 0;
	for (int i = 0; i < keywordList->numOfKeywords; i++)
	{
		if (!strcmp(searchWord, keywordList->keyword[i].keyword))
		{
			printf("%s를 찾았습니다!!\n", searchWord);
			printf("-단어 정보-\n");
			printf("단어: %s\n", searchWord);
			printf("빈도수: %d\n", keywordList->keyword[i].frequency);
			//printf("위치: %d번째 단어\n", keywordList->keyword[i].location);
			flag = 1;
			break;
		}
	}

	if (flag == 0)
	{
		printf("찾는 단어가 목록에 없습니다.\n");
	}
}

void printList(KeywordList* keywordList)
{
	printf("키워드 목록 전체--\n");
	for (int i = 0; i < keywordList->numOfKeywords; i++)
	{
		//printf("%d - 단어: %s  위치: %d번째 단어\n", i + 1, keywordList->keyword[i].keyword, keywordList->keyword[i].location);
		printf("%d - 단어: %10s 빈도수: %2d\n", i + 1, keywordList->keyword[i].keyword, keywordList->keyword[i].frequency);
	}
	printf("\n출력 완료!!\n");
}

void saveKeywords(KeywordList* keywordList, char* fileName)
{
	FILE* fp = fopen(fileName, "rt");
	if (fp == NULL)
	{
		puts("파일 오픈 실패!!\n");
		return;
	}

	char* word = NULL;
	char line[1000];
	int flag = 0;

	while (feof(fp) == 0)
	{
		fgets(line, sizeof(line), fp);

		word = strtok(line, " ");

		while (word != NULL)
		{
			deleteSymbol(word);
			for (int i = 0; i < keywordList->numOfKeywords; i++)
			{
				if (strcicmp(word, keywordList->keyword[i].keyword) == 0)
				{
					//위치 정보도 나중에 업데이트
					keywordList->keyword[i].frequency++;
					flag = 1;
					break;
				}
			}

			if (flag == 0)
			{
				if (isFull(keywordList))
				{
					if (expandList(keywordList) == -1)
					{
						printf("리스트를 더이상 늘릴 수 없습니다.\n");
						return;
					}
					else
					{
						strcpy(keywordList->keyword[keywordList->numOfKeywords].keyword, word);
						keywordList->keyword[keywordList->numOfKeywords].frequency++;
						keywordList->numOfKeywords++;
					}
				}
				strcpy(keywordList->keyword[keywordList->numOfKeywords].keyword, word);
				keywordList->keyword[keywordList->numOfKeywords].frequency++;
				keywordList->numOfKeywords++;
			}

			flag = 0;
			word = strtok(NULL, " ");
		}
	}
	fclose(fp);
}

void deleteSymbol(char* word)
{
	for (; *word != '\0'; word++)
	{
		if (*word == ',' || *word == '.' || *word == '\n' || *word == '?' || *word == '"')
		{
			strcpy(word, word + 1);
			word--;
		}
	}
}

int strcicmp(char const* a, char const* b)
{
	for (;; a++, b++) {
		int d = tolower((unsigned char)* a) - tolower((unsigned char)* b);
		if (d != 0 || !*a)
			return d;
	}
}