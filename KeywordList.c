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
	printf("����Ʈ �ʱ�ȭ �Ϸ�!!\n");
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
		printf("Ű���� ����� ���� �Ѱ踦 �ø��� ���߽��ϴ�.\n");
		return -1;
	}
	printf("Ű���� ����� ���� �Ѱ谡 �þ���ϴ�.\n");

	for (int i = keywordList->numLimit; i < keywordList->numLimit + 10; i++)
		keywordList->keyword[i].frequency = 0;

	keywordList->numLimit = keywordList->numLimit + 10;
	printf("���� Ű���� ��� ���� �Ѱ�: %d\n", keywordList->numLimit);
	return 0;
}

void Search(char* searchWord, KeywordList* keywordList)
{
	int flag = 0;
	for (int i = 0; i < keywordList->numOfKeywords; i++)
	{
		if (!strcmp(searchWord, keywordList->keyword[i].keyword))
		{
			printf("%s�� ã�ҽ��ϴ�!!\n", searchWord);
			printf("-�ܾ� ����-\n");
			printf("�ܾ�: %s\n", searchWord);
			printf("�󵵼�: %d\n", keywordList->keyword[i].frequency);
			//printf("��ġ: %d��° �ܾ�\n", keywordList->keyword[i].location);
			flag = 1;
			break;
		}
	}

	if (flag == 0)
	{
		printf("ã�� �ܾ ��Ͽ� �����ϴ�.\n");
	}
}

void printList(KeywordList* keywordList)
{
	printf("Ű���� ��� ��ü--\n");
	for (int i = 0; i < keywordList->numOfKeywords; i++)
	{
		//printf("%d - �ܾ�: %s  ��ġ: %d��° �ܾ�\n", i + 1, keywordList->keyword[i].keyword, keywordList->keyword[i].location);
		printf("%d - �ܾ�: %10s �󵵼�: %2d\n", i + 1, keywordList->keyword[i].keyword, keywordList->keyword[i].frequency);
	}
	printf("\n��� �Ϸ�!!\n");
}

void saveKeywords(KeywordList* keywordList, char* fileName)
{
	FILE* fp = fopen(fileName, "rt");
	if (fp == NULL)
	{
		puts("���� ���� ����!!\n");
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
					//��ġ ������ ���߿� ������Ʈ
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
						printf("����Ʈ�� ���̻� �ø� �� �����ϴ�.\n");
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