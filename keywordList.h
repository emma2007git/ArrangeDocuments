#ifndef __KEYWORD_LIST__
#define __KEYWORD_LIST__


//char symbol_arr[100] = { '.', '?', '!',',', '~', '#', '&'};

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
//Keyword delete(KeywordList* keywordList);

//�󵵼� �������� ����
void SortByFrequency(KeywordList* keywordList);

//�����ټ����� ����
//void SortByAlphabeticalOrder();

//�󵵼� 1�� �ܾ� ���
void topFrequency(KeywordList* keywordList);

//����, ���� ��� �ʿ� ���� �ܾ� ����
int deleteNeedlessWords(char* word);
#endif // !__KEYWORD_LIST__
