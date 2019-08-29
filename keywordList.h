#ifndef __KEYWORD_LIST__
#define __KEYWORD_LIST__

/*
char* auxil_beVerb_article[26] = { "a","an", "A","An", "the",
"The", "is", "are", "was", "were", "am", "will", "would"
, "can","Can", "could","Could", "may","May", "might", "should",
"Should","need", "Need","shall", "Shall"};
char symbol_arr[100] = { '.', '?', '!',',', '~', '#', '&'};
*/
typedef struct keyword
{
	char keyword[100];
	//int location; //��ġ �κ��� ��� ��ġ�� �����ϱ� ���� ��ũ�帮��Ʈ�� �����ϸ� ������!
	int frequency;
}Keyword;

typedef struct keywordList
{
	Keyword* keyword;
	int numOfKeywords;
	int numLimit;
}KeywordList;

//�Լ�
//����Ʈ �ʱ�ȭ
void Init(KeywordList* keywordList);

//����Ʈ�� �� á����
int isFull(KeywordList* keywordList);

//����Ʈ�� ������ �� �ִ� Ű���� ���� �ø���
int expandList(KeywordList* keywordList);

//Ű���� �˻�(Ű���� ������ Ű���� ���� ��ȯ)
void Search(char* searchWord, KeywordList* keywordList);

//����Ʈ ���
void printList(KeywordList* keywordList);

//������ Ű���带 ����
void saveKeywords(KeywordList* keywordList, char* fileName);

//�ܾ ���Ե� ��ȣ ���ֱ�
void deleteSymbol(char* word);

//Ű���带 ��Ͽ��� �����

//�󵵼� �������� ����
//void SortByFrequency(KeywordList* keywordList);

//�����ټ����� ����
//void SortByAlphabeticalOrder();
#endif // !__KEYWORD_LIST__
