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
	int size = _getNumberLen(num);
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

bool ANumber::toChar(char* result)
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

	return true;
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

ANumber ANumber::operator+(int item)
{
	return *this + ANumber(item);
}

ANumber ANumber::operator-(int item)
{
	return *this - ANumber(item);
}

bool ANumber::operator<(int item)
{
	return *this < ANumber(item);
}

bool ANumber::operator<=(int item)
{
	return *this <= ANumber(item);
}

bool ANumber::operator>(int item)
{
	return *this > ANumber(item);
}

bool ANumber::operator>=(int item)
{
	return *this >= ANumber(item);
}

bool ANumber::operator==(int item)
{
	return *this == ANumber(item);
}

int ANumber::_compareNumber(ANumber num)
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

int ANumber::compareNumber(ANumber num)
{
	if(this->minus && num.minus)
	{
		return !_compareNumber(num);
	}
	else if(!this->minus && num.minus)
	{
		return -1;
	}
	else if(!this->minus && num.minus)
	{
		return 1;
	}

	return _compareNumber(num);
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
		big = this;
		small = &num;
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
	bool process = false;

	if(tmp == 1)
	{
		big = this;
		small = &num;
	}
	else if(tmp == -1)
	{
		big = &num;
		small = this;
		process = true;
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

	if(process)
	{
		this->minus = !this->minus;
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

int ANumber::_getNumberLen(char* num)
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