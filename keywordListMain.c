#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keywordList.h"

int main(void)
{
	KeywordList keywordList;
	Init(&keywordList);

	char* fileName = "tedtalk.txt";
	saveKeywords(&keywordList, fileName);

	Search("this", &keywordList);

	printf("\n");
	printList(&keywordList);

	return 0;
}