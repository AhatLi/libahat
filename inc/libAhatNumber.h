#include <iostream>
#include <map>
#include <string.h>

#define MAX 16384

#define MAX_NUMBER 100000000

using namespace std;

class ANumber
{
public:
	map<int, int> itemlist;
	bool minus;

	ANumber(const char* num);
	ANumber(int num);

	bool toNum(const char* num);
	bool getHeight(int* max, int* min);
	bool toChar(char* result);
	std::string toStr();
	bool add(ANumber num);
	bool sub(ANumber num);

	int compareNumber(ANumber num);
	int compareNumber(int num);
	
	ANumber operator+(ANumber item);
	ANumber operator-(ANumber item);
	bool operator<(ANumber item);
	bool operator<=(ANumber item);
	bool operator>(ANumber item);
	bool operator>=(ANumber item);
	bool operator==(ANumber item);
	
	ANumber operator+(int item);
	ANumber operator-(int item);
	bool operator<(int item);
	bool operator<=(int item);
	bool operator>(int item);
	bool operator>=(int item);
	bool operator==(int item);

private:
	bool _add(ANumber *big, ANumber *small, int max);
	bool _sub(ANumber *big, ANumber *small, int max);
	int _compareNumber(ANumber num);
	
	int _getNumberLen(const char* num);
};