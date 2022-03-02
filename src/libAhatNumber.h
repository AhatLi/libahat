#include <iostream>
#include <map>

#define MAX 16384

#define MAX_NUMBER 100000000

using namespace std;

class ANumber
{
public:
	map<int, int> itemlist;
	bool minus;

	ANumber(char* num);
	ANumber(int num);

	bool toNum(char* num);
	bool getHeight(int* max, int* min);
	bool toChar(char* result);
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
	
	int _getNumberLen(char* num);
};