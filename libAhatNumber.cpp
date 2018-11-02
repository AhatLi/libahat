#include "libAhatNumber.h"


ANumber::ANumber(char* num)
{
	toNum(num);
}

ANumber::ANumber(int num)
{
	int i = 0;
	this->minus = false;
	if(num < 0)
	{
		this->minus = true;
	}
	else if(num == 0)
	{
		this->itemlist[0] = 0;
		return;
	}

	while(1)
	{
		int value = num % MAX;
		this->itemlist[i] = value;

		num /= MAX;

		if(!num)
		{
			break;
		}
	}
}

bool ANumber::toNum(char* num)
{
	int size = getNumberLen(num);
	this->minus = false;

	int n = 0;
	int d = 1;
	int count = 0;

	for(int i = 0; i < size; i++)
	{
		if(((size - i - 1) == 0) && (num[size - i - 1] == '-'))
		{
			this->minus = true;
			continue;
		}

		n += d * (num[size - i - 1] - 48);
		d *= 10;

		if(d > MAX_NUMBER/10)
		{
			this->itemlist[count] = n;

			count++;
			d = 1;
			n = 0;
		}
	}
	if(n != 0)
	{
		this->itemlist[count] = n;
	}

	return true;
}

char* ANumber::toChar(char* result)
{
	int max = 0;
	int min = 0;
	int c = 0;
	
	getHeight(&max, &min);
	int value = this->itemlist[max];
	bool find = false;

	if(this->minus == true)
	{
		result[c++] = '-';
	}
	for(int i = MAX_NUMBER/10; i != 0; i/=10)
	{
		if(value / i != 0 || find)
		{
			find = true;
			result[c++] = ((value / i) % 10) + 48;
		}
	}

	for(int i = max-1; i >= min; i--)
	{		
		value = this->itemlist[i];
		if(this->itemlist[i] == NULL)
		{
			for(int i = 0; i < 7; i++)
			{
				result[c++] = 48;
			}
		}
		else
		{
			for(int i = MAX_NUMBER/10; i != 0; i/=10)
			{
				result[c++] = ((value / i) % 10) + 48;
			}
		}
	}

	return result;
}

bool ANumber::getHeight(int* max, int* min)
{
	for(map<int, int>::iterator itr = this->itemlist.begin(); itr != this->itemlist.end(); itr++)
	{
		if(*max < itr->first)
		{
			*max = itr->first;
		}
		if(*min > itr->first)
		{
			*min = itr->first;
		}
	}

	return true;
}

ANumber ANumber::operator+(ANumber item)
{
	ANumber buf(*this);

	buf.add(item);

	return buf;
}

ANumber ANumber::operator-(ANumber item)
{
	ANumber buf(*this);

	buf.sub(item);

	return buf;
}

bool ANumber::operator<(ANumber item)
{
	return compareNumber(item) == -1;
}

bool ANumber::operator<=(ANumber item)
{
	int result = compareNumber(item);
	return (result == -1 || result == 0);
}

bool ANumber::operator>(ANumber item)
{
	return compareNumber(item) == 1;
}

bool ANumber::operator>=(ANumber item)
{
	int result = compareNumber(item);
	return (result == 1 || result == 0);
}

bool ANumber::operator==(ANumber item)
{
	return compareNumber(item) == 0;
}

int ANumber::compareNumber(ANumber num)
{
	int size1 = 0;
	int size2 = 0;
	int tmp = 0;

	getHeight(&size1, &tmp);
	num.getHeight(&size2, &tmp);

	if(size1 > size2)
	{
		return 1;
	}
	else if(size1 < size2)
	{
		return -1;
	}
	else
	{
		for(int i = 0; i < size1 + 1; i++)
		{
			if(this->itemlist[size1 - i] > num.itemlist[size1 - i])
			{
				return 1;
			}
			else if(this->itemlist[size1 - i] < num.itemlist[size1 - i])
			{
				return -1;
			}
		}
	}

	return 0;
}

bool ANumber::add(ANumber num)
{
	int max = 0;
	int min = 0;
	int carry = 0;
	bool reverse = false;

	int tmp = this->compareNumber(num);

	ANumber* big;
	ANumber* small;
	if(tmp == 1)
	{
		big = this;
		small = &num;
	}
	else if(tmp == -1)
	{
		big = &num;
		small = this;
	}
	else
	{
		this->toNum("0");
		return true;
	}

	getHeight(&max, &min);
	num.getHeight(&max, &min);

	if(big->minus == false)
	{
		if(small->minus == false)
		{
			this->_add(big, small, max);
		}
		else
		{
			this->_sub(big, small, max);
		}
		this->minus = false;
	}
	else
	{
		if(small->minus == false)
		{
			this->_sub(big, small, max);
		}
		else
		{
			this->_add(big, small, max);
		}
		this->minus = false;
	}
	return true;
}

bool ANumber::sub(ANumber num)
{
	int max = 0;
	int min = 0;
	int carry = 0;

	int tmp = this->compareNumber(num);

	ANumber* big;
	ANumber* small;
	if(tmp == 1)
	{
		big = this;
		small = &num;
	}
	else if(tmp == -1)
	{
		big = &num;
		small = this;
	}
	else
	{
		this->toNum("0");
		return true;
	}
	
	getHeight(&max, &min);
	num.getHeight(&max, &min);
	
	if(big->minus == false)
	{
		if(small->minus == false)
		{
			this->_sub(big, small, max);
		}
		else
		{
			this->_add(big, small, max);
		}
		this->minus = false;
	}
	else
	{
		if(small->minus == false)
		{
			this->_add(big, small, max);
		}
		else
		{
			this->_sub(big, small, max);
		}
		this->minus = true;
	}

	return true;
}

//자기자신(큰수)에서 작은수를 더하는 함수 
bool ANumber::_add(ANumber *big, ANumber *small, int max)
{
	int carry = 0;
	int i = 0;

	for(i = 0; i < max+1; i++)
	{
		int value = 0;
		
		if(big->itemlist.find(i) == big->itemlist.end())
		{
			value = small->itemlist[i] + carry;
		}
		else if(small->itemlist.find(i) == small->itemlist.end())
		{
			value = big->itemlist[i] + carry;
		}
		else
		{
			value = big->itemlist[i] + small->itemlist[i] + carry;
		}
		
		this->itemlist[i] = value % MAX_NUMBER;
		carry = value / MAX_NUMBER;
	}
	if(carry)
	{
		this->itemlist[i] = carry;
	}

	return true;
}

//자기자신(큰수)에서 작은수를 빼는 함수 
bool ANumber::_sub(ANumber *big, ANumber *small, int max)
{
	int carry = 0;

	for(int i = 0; i < max+1; i++)
	{
		int n1 = 0;
		int n2 = 0;

		if(big->itemlist.find(i) != big->itemlist.end())
		{
			n1 = big->itemlist[i];
		}
		if(small->itemlist.find(i) != small->itemlist.end())
		{
			n2 = small->itemlist[i];
		}

		n1 -= carry;
		carry = 0;

		if(n1 < n2)
		{
			n1 += MAX_NUMBER;
			carry = 1;
		}

		this->itemlist[i] = n1 - n2;
	}

	return true;
}



/*
bool sub(char* num1, char* num2, char* result)
{
	int size1 = strlen(num1);
	int size2 = strlen(num2);
	int max = size1 > size2 ? size1 : size2;
	bool minus = false;
	int count = 0;

	char *data1, *data2;

	if(size1 < size2)
	{
		minus = true;
	}
	else if(size1 == size2)
	{
		for(int i = 0; i < size1; i++)
		{
			if(num1[i] < num2[i])
			{
				minus = true;
				break;
			}
		}
	}

	if(minus == false)
	{
		data1 = num1;
		data2 = num2;
	}
	else
	{
		data1 = num2;
		data2 = num1;

		int c = size2;
		size2 = size1;
		size1 = c;
	}

	for(int i = 0; i < max; i++)
	{
		char n1 = 0;
		char n2 = 0;
		int r = 0;
		
		if(size1 - max + i >= 0)
		{
			n1 = data1[size1 - max + i] - 48;
		}
		if(size2 - max + i >= 0)
		{
			n2 = data2[size2 - max + i] - 48;
		}

		if(n1 < n2)
		{
			r = n1 - n2 + 10;
			int c = i-1;

			while(1)
			{
				if(result[c] == '0')
				{
					result[c] = '9';
				}
				else
				{
					result[c] = result[c] - 1;
					break;
				}
				c--;
			}
		}
		else
		{
			r = n1 - n2;
		}

		result[count++] = r + 48;
	}

	result[count] = '\0';

	count = 0;
	while(1)
	{
		if(result[count] == '0')
		{
			count++;
		}
		else
		{
			break;
		}
	}

	if(count != 0)
	{
		int size = strlen(result) - count + 1;
		for(int i = 0; i < size; i++)
		{
			result[i] = result[i + count];
		}
	}

	return !minus;
}

char* add(char* num1, char* num2, char* result)
{
	int carry = 0;
	int count = 0;
	int size1 = strlen(num1);
	int size2 = strlen(num2);

	char buf[MAX+1] = {0, };
	int max = size1 > size2 ? size1 : size2;

	for(int i = 0; i < max; i++)
	{
		char n1 = 0;
		char n2 = 0;
		char n3 = carry;

		if(size1 - i - 1 >= 0)
		{
			n1 = num1[size1 - i - 1] - 48;
		}
		if(size2 - i - 1 >= 0)
		{
			n2 = num2[size2 - i - 1] - 48;
		}

		buf[count++] = ((n1 + n2 + n3) % 10) + 48;
		carry = (n1 + n2 + n3) / 10;
	}
	if(carry > 0)
	{
		buf[count] = carry + 48;
	}

	max = strlen(buf);
	for(int i = 0; i < max; i++)
	{
		result[i] = buf[max - i - 1];
	}

	return result;
}

void division(char* num1, char* num2, int digit, char* result)
{
	char re[MAX+1] = {0, };

	int size1 = getNumberLen(num1);

	strcpy_s(result, MAX+1, num1);

	while(sub(num1, num2, re))
	{
		strcpy_s(result, MAX+1, re);
		strcpy_s(num1, MAX+1, re);
	}
}

void mod(char* num1, char* num2, char* result)
{
	char re[MAX+1] = {0, };



	strcpy_s(result, MAX+1, num1);

	while(sub(num1, num2, re))
	{
		strcpy_s(result, MAX+1, re);
		strcpy_s(num1, MAX+1, re);
	}
}

int getNumberLen(char* num)
{
	int result = 0;
	int size = strlen(num);

	for(int i = 0; i < size; i++)
	{
		if(num[i] == '.')
		{
			break;
		}
			
		result++;
	}

	return result;
}

int compareNumber(char* num1, char* num2)
{
	int size1 = getNumberLen(num1);
	int size2 = getNumberLen(num2);

	if(size1 > size2)
	{
		return 1;
	}
	else if(size1 == size2)
	{
		for(int i = 0; i < size1; i++)
		{
			if(num1[i] < num2[i])
			{
				return -1;
			}
		}

		if(isDecimal(num1))
		{
			if(isDecimal(num2))
			{
				char *p1 = getDecimal(num1);
				char *p2 = getDecimal(num2);
				int i = 0;

				while(1)
				{
					if(!*p1 && *p2)
					{
						return -1;
					}
					else if(*p1 && !*p2)
					{
						return 1;
					}
					else if(!*p1 && !*p2)
					{
						return 0;
					}

					if(*p1 < *p2)
					{
						return -1;
					}
					else if(*p1 > *p2)
					{
						return 1;
					}

					p1++;
					p2++;
				}
			}
			else
			{
				return 1;
			}
		}

		return 0;
	}

	return -1;
}

char* getDecimal(char* num)
{
	for(char* p = num ;p != NULL; p++)
	{
		if(*p == '.')
			return ++p;
	}

	return NULL;
}

int isDecimal(char* num)
{
	int size = strlen(num);
	int result = 0;

	for(int i = 0; i < size; i++)
	{
		if(num[i] == '.')
		{
			if(result == 0)
			{
				result = 1;
			}
			else
			{
				return 2;
			}
		}
		else if(num[i] < 47 || num[i] > 58)
		{
			return 2;
		}
	}

	return result;
}

bool isNumber(char* num)
{
	int size = strlen(num);
	bool decimal = false;

	for(int i = 0; i < size; i++)
	{
		if(num[i] == '.')
		{
			if(decimal == false)
			{
				decimal = true;
			}
			else
			{
				return false;
			}
		}
		else if(num[i] < 47 || num[i] > 58)
		{
			return false;
		}
	}

	return true;
}
*/