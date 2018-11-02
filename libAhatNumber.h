#include <iostream>
#include <map>

#define MAX 16384

#define MAX_NUMBER 100000000

using namespace std;

bool sub(char* num1, char* num2, char* result);
char* add(char* num1, char* num2, char* result);
void division(char* num1, char* num2, int digit, char* result);
int getNumberLen(char* num);
int isDecimal(char* num);
bool isNumber(char* num);
void mod(char* num1, char* num2, char* result);
bool sub(char* num1, char* num2, char* result);
int compareNumber(char* num1, char* num2);
char* getDecimal(char* num);

class ANumber
{
public:
	ANumber(char* num);
	ANumber(int num);

	map<int, int> itemlist;
	bool minus;

	bool toNum(char* num);
	bool getHeight(int* max, int* min);
	char* toChar(char* result);
	bool add(ANumber num);
	bool sub(ANumber num);
	int compareNumber(ANumber num);
	
	ANumber operator+(ANumber item);
	ANumber operator-(ANumber item);
	bool operator<(ANumber item);
	bool operator<=(ANumber item);
	bool operator>(ANumber item);
	bool operator>=(ANumber item);
	bool operator==(ANumber item);

private:
	bool _add(ANumber *big, ANumber *small, int max);
	bool _sub(ANumber *big, ANumber *small, int max);
};