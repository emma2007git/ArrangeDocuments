#ifndef __KEYWORD_LIST__
#define __KEYWORD_LIST__


//char symbol_arr[100] = { '.', '?', '!',',', '~', '#', '&'};

typedef struct keyword
{
	char keyword[100];
	//int location; //위치 부분은 모든 위치를 저장하기 위해 링크드리스트로 구성하면 좋을듯!
	int frequency;
}Keyword;

typedef struct keywordList
{
	Keyword* keyword;
	int numOfKeywords;
	int numLimit;
}KeywordList;

//함수
//리스트 초기화
void Init(KeywordList* keywordList);

//리스트가 꽉 찼는지
int isFull(KeywordList* keywordList);

//리스트에 저장할 수 있는 키워드 개수 늘리기
int expandList(KeywordList* keywordList);

//키워드 검색(키워드 있으면 키워드 정보 반환)
void Search(char* searchWord, KeywordList* keywordList);

//리스트 출력
void printList(KeywordList* keywordList);

//문서의 키워드를 저장
void saveKeywords(KeywordList* keywordList, char* fileName);

//단어에 포함된 기호 없애기
void deleteSymbol(char* word);

//키워드를 목록에서 지우기
//Keyword delete(KeywordList* keywordList);

//빈도수 기준으로 정렬
void SortByFrequency(KeywordList* keywordList);

//가나다순으로 정렬
//void SortByAlphabeticalOrder();

//빈도수 1위 단어 출력
void topFrequency(KeywordList* keywordList);

//관사, 대명사 등등 필요 없는 단어 삭제
int deleteNeedlessWords(char* word);
#endif // !__KEYWORD_LIST__
