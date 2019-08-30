#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keywordList.h"
#include "quickSort.h"

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

//대소문자 구별 없이 찾기
void Search(char* searchWord, KeywordList* keywordList)
{
	int flag = 0;
	for (int i = 0; i < keywordList->numOfKeywords; i++)
	{
		if (!strcicmp(searchWord, keywordList->keyword[i].keyword))
		{
			printf("%s를 찾았습니다!!\n", searchWord);
			printf("-단어 정보-\n");
			printf("단어: %s\n", keywordList->keyword[i].keyword);
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
		printf("%3d - 단어: %15s     빈도수: %3d\n", i + 1, keywordList->keyword[i].keyword, keywordList->keyword[i].frequency);
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
	int aux = 0;

	while (feof(fp) == 0)
	{
		fgets(line, sizeof(line), fp);

		word = strtok(line, " ");

		while (word != NULL)
		{
			deleteSymbol(word);

			aux = deleteNeedlessWords(word);

			if (aux == 1)
			{
				flag = 0;
				word = strtok(NULL, " ");
				aux = 0;
				continue;
			}
			//원래 있던 단어와 같은지 검사
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

			//같은 단어가 없다면 새로 저장
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

void SortByFrequency(KeywordList* keywordList)
{
	QuickSort(keywordList->keyword, 0, keywordList->numOfKeywords - 1);
}

void topFrequency(KeywordList* keywordList)
{
	Keyword result;
	result.frequency = 0;

	for (int i = 0; i < keywordList->numOfKeywords; i++)
	{
		if (result.frequency < keywordList->keyword[i].frequency)
		{
			result.frequency = keywordList->keyword[i].frequency;
			strcpy(result.keyword, keywordList->keyword[i].keyword);
		}
	}

	printf("중요 단어: %s\n", result.keyword);
	printf("빈도수: %d\n", result.frequency);
}

int deleteNeedlessWords(char* word)
{
	char* beverb[5] = { "is", "are", "was", "were", "am" };
	char* auxiliaryVerb[15] = { "will", "would", "can","Can","could",
	"Could", "may","May", "might", "should","Should","need", "Need","shall","Shall" };
	char* article[6] = { "a","an", "A","An", "the","The" };
	char* conjunction[46] = { "and","And","but", "But","or"
	,"Or","nor","Nor","for","For"
	,"so","So","yet","Yet","after"
	,"After","as","As","before","Before"
	,"since","Since","until","Until","when"
	,"When","whenever","Whenever","while","While"
	,"once","Once","because","Because","although"
	,"Although","though","Though","even","Even"
	,"whereas","Whereas","if","If","unless",
	"Unless" };
	char* preposition[48] = { "in","In","at","At","on"
	,"On","beneath","Beneath","between","Between"
	,"among","Among","to","To","into"
	,"Into","for","For","from","From"
	,"off","Off","across","Across","along"
	,"Along","through","Through","toward","Toward"
	,"towards","Towards","against","Against","during"
	,"During","within","Within","till","Till"
	,"untill","Untill","by","By" ,"of"
	,"Of","with","With" };

	char* pronouns[78] = { "i", "I","my","My","me"
	,"Me","mine","Mine","Myself","myself"
	,"we","We","our","Our","us"
	,"Us","ours","Ours","ourselves","Ourselves"
	,"you","You","your","Your","yours"
	,"Yours","yourself","Yourself","he","He"
	,"his","His","him","Him","himself"
	,"Himself","she","She","her","Her"
	,"hers","Hers","Herself","herself","it"
	,"It","its","Its","itself","Itself"
	,"they","They","their","Their","them"
	,"Them","theirs","Theirs","themselves","Themselves" 
	,"who","Who","whose","Whose","whom"
	,"Whom","which","Which","what","What"
	,"that", "That","this","This","these"
	,"These","those","Those"};

	int aux = 0;
	//be동사, 조동사, 관사인지 검사
	for (int i = 0; i < 5; i++)
	{
		if (strcmp(word, beverb[i]) == 0)
		{
			aux = 1;
			break;
		}
	}
	if (aux != 1)
		for (int i = 0; i < 15; i++)
		{
			if (strcmp(word, auxiliaryVerb[i]) == 0)
			{
				aux = 1;
				break;
			}
		}
	if (aux != 1)
		for (int i = 0; i < 6; i++)
		{
			if (strcmp(word, article[i]) == 0)
			{
				aux = 1;
				break;
			}
		}
	if (aux != 1)
		for (int i = 0; i < 46; i++)
		{
			if (strcmp(word, conjunction[i]) == 0)
			{
				aux = 1;
				break;
			}
		}
	if (aux != 1)
		for (int i = 0; i < 48; i++)
		{
			if (strcmp(word, preposition[i]) == 0)
			{
				aux = 1;
				break;
			}
		}
	if (aux != 1)
		for (int i = 0; i < 78; i++)
		{
			if (strcmp(word, pronouns[i]) == 0)
			{
				aux = 1;
				break;
			}
		}
	return aux;
}