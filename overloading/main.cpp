#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
class InvalidDateException
{
};
#endif /* __PROGTEST__ */

//------------------------------------------------------------------------------------------------------------------------------------------
//				Leap year checking 
//------------------------------------------------------------------------------------------------------------------------------------------


bool isLeap (int _y)
{
	if((_y%4==0 && _y%100!=0) ||
	 (_y%400==0 && _y%4000!=0))
		return true;
return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//				Body of monitoring function for catching invalided input date
//------------------------------------------------------------------------------------------------------------------------------------------

bool controlDate(int y, int m, int d)
{
int maxDay;
if(y < 1600)
	return false;
	
        switch(m) 
	{
	case 1 : maxDay=31;
		break;
	case 2 : maxDay = isLeap(y) ? 29 : 28;
		break;
	case 3 : maxDay=31;
		break;
	case 4 : maxDay=30;
		break;
	case 5 : maxDay=31;
		break;
	case 6 : maxDay=30;
		break;
	case 7 : maxDay=31;
		break;
	case 8 : maxDay=31;
		break;
	case 9 : maxDay=30;
		break;
	case 10 : maxDay=31;
		break;
	case 11 :maxDay=30;
		break;
	case 12 : maxDay=31;
		break;
	default:
		return false;
	}
if(d>maxDay || d < 1)
	return false;
return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//				Funkcion for find a value of days in actual month in actual year
//------------------------------------------------------------------------------------------------------------------------------------------

long long int howManyDays ( int year, int month)
{
switch (month)
{
case 0:
return 31;

case 1:
return 31;

case 2:
if(isLeap(year))
	return 29;
else
	return 28;

case 3:
return 31;

case 4:
return 30;

case 5:
return 31;

case 6:
return 30;

case 7:
return 31;

case 8:
return 31;

case 9:
return 30;

case 10:
return 31;

case 11:
return 30;

case 12:
return 31;
}
return 0;
}
//---------------------------------------------------------------------------------------------------------------------------------------
class CDate;
class Day;
class Month;
class Year;

//------------------------------------------------------------------------------------------------------------------------------------------
//				Temp class for make right operand for unary plus  
//------------------------------------------------------------------------------------------------------------------------------------------
class CDateTemp
{
public:
int m_year;
int m_month;
int m_day;
	
	CDateTemp(int year, int month, int day)
	:m_year(year), m_month(month), m_day(day){}
	
	friend const vector<CDateTemp> operator+(const vector<CDateTemp>& left,  const Day& right);
	friend const vector<CDateTemp> operator+(const vector<CDateTemp>& left,  const Month& right);
	friend const vector<CDateTemp> operator+(const vector<CDateTemp>& left,  const Year& right);
	friend const vector<CDateTemp> operator-(const vector<CDateTemp>& left,  const Day& right);
	friend const vector<CDateTemp> operator-(const vector<CDateTemp>& left,  const Month& right);
	friend const vector<CDateTemp> operator-(const vector<CDateTemp>& left,  const Year& right);

};



//------------------------------------------------------------------------------------------------------------------------------------------
//				Class represent shift's value by day's 
//------------------------------------------------------------------------------------------------------------------------------------------
class Day
{
public:
int m_value;
	
	Day(int value)
	:m_value(value){}

		friend const vector<CDateTemp> operator+(const Day& left,  const Day& right);
		friend const vector<CDateTemp> operator+(const Day& left,  const Month& right);
		friend const vector<CDateTemp> operator+(const Day& left,  const Year& right);
		friend const vector<CDateTemp> operator-(const Day& left,  const Day& right);
		friend const vector<CDateTemp> operator-(const Day& left,  const Month& right);
		friend const vector<CDateTemp> operator-(const Day& left,  const Year& right);	
};



//------------------------------------------------------------------------------------------------------------------------------------------
//				Class represent shift's value by month's 
//------------------------------------------------------------------------------------------------------------------------------------------

class Month
{
public:
int m_value;
	
	Month(int value)
	:m_value(value){}

		friend const vector<CDateTemp> operator+(const Month& left,  const Day& right);
		friend const vector<CDateTemp> operator+(const Month& left,  const Month& right);
		friend const vector<CDateTemp> operator+(const Month& left,  const Year& right);
		friend const vector<CDateTemp> operator-(const Month& left,  const Day& right);
		friend const vector<CDateTemp> operator-(const Month& left,  const Month& right);
		friend const vector<CDateTemp> operator-(const Month& left,  const Year& right);
};

//------------------------------------------------------------------------------------------------------------------------------------------
//				Class represent shift's value by year's 
//------------------------------------------------------------------------------------------------------------------------------------------
class Year
{
public:
int m_value;
	
	Year(int value)
	:m_value(value){}

		friend const vector<CDateTemp> operator+(const Year& left,  const Day& right);
		friend const vector<CDateTemp> operator+(const Year& left,  const Month& right);
		friend const vector<CDateTemp> operator+(const Year& left,  const Year& right);
		friend const vector<CDateTemp> operator-(const Year& left,  const Day& right);
		friend const vector<CDateTemp> operator-(const Year& left,  const Month& right);
		friend const vector<CDateTemp> operator-(const Year& left,  const Year& right);
};

//-----------------------------------------------------------------------------------------------------------------------------------------

	const vector<CDateTemp> operator+(const Day& left,  const Day& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp(0, 0, left.m_value));
arguments.push_back(CDateTemp(0, 0, right.m_value));
return arguments;
}
	const vector<CDateTemp> operator+(const Day& left,  const Month& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp( 0, 0, left.m_value ));
arguments.push_back(CDateTemp( 0, right.m_value, 0 ));
return arguments;
}
	const vector<CDateTemp> operator+(const Day& left,  const Year& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp( 0, 0, left.m_value ));
arguments.push_back(CDateTemp( right.m_value, 0, 0 ));
return arguments;
}

const vector<CDateTemp> operator-(const Day& left,  const Day& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp(0, 0, left.m_value));
arguments.push_back(CDateTemp(0, 0, - right.m_value));
return arguments;
}
	const vector<CDateTemp> operator-(const Day& left,  const Month& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp( 0, 0, left.m_value ));
arguments.push_back(CDateTemp( 0, -right.m_value, 0 ));
return arguments;
}
	const vector<CDateTemp> operator-(const Day& left,  const Year& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp( 0, 0, left.m_value ));
arguments.push_back(CDateTemp( -right.m_value, 0, 0 ));
return arguments;
}

//------------------------------------------------------------------------------------------------------------------------------------------

const vector<CDateTemp> operator+(const Month& left,  const Day& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp(0, left.m_value, 0));
arguments.push_back(CDateTemp(0, 0, right.m_value));
return arguments;
}
	const vector<CDateTemp> operator+(const Month& left,  const Month& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp( 0, left.m_value, 0 ));
arguments.push_back(CDateTemp( 0, right.m_value, 0 ));
return arguments;
}
	const vector<CDateTemp> operator+(const Month& left,  const Year& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp( 0, left.m_value, 0 ));
arguments.push_back(CDateTemp( right.m_value, 0, 0 ));
return arguments;
}

const vector<CDateTemp> operator-(const Month& left,  const Day& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp(0, left.m_value, 0));
arguments.push_back(CDateTemp(0, 0, -right.m_value));
return arguments;
}
	const vector<CDateTemp> operator-(const Month& left,  const Month& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp( 0, left.m_value , 0 ));
arguments.push_back(CDateTemp( 0, - right.m_value, 0 ));
return arguments;
}
	const vector<CDateTemp> operator-(const Month& left,  const Year& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp( 0,  left.m_value, 0 ));
arguments.push_back(CDateTemp( -right.m_value, 0, 0 ));
return arguments;
}

//------------------------------------------------------------------------------------------------------------------------------------------

const vector<CDateTemp> operator+(const Year& left, const Day& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp(left.m_value, 0, 0));
arguments.push_back(CDateTemp(0, 0, right.m_value));
return arguments;
}
	const vector<CDateTemp> operator+(const Year& left,  const Month& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp(  left.m_value, 0, 0 ));
arguments.push_back(CDateTemp(  0, right.m_value, 0 ));
return arguments;
}
	const vector<CDateTemp> operator+(const Year& left,  const Year& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp( left.m_value, 0, 0 ));
arguments.push_back(CDateTemp( right.m_value, 0, 0 ));
return arguments;
}

const vector<CDateTemp> operator-(const Year& left,  const Day& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp(left.m_value, 0, 0));
arguments.push_back(CDateTemp(0, 0, -right.m_value));
return arguments;
}
	const vector<CDateTemp> operator-(const Year& left,  const Month& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp(  left.m_value, 0, 0 ));
arguments.push_back(CDateTemp(  0, -right.m_value, 0 ));
return arguments;
}
	const vector<CDateTemp> operator-(const Year& left,  const Year& right)
{
vector<CDateTemp> arguments;
arguments.push_back(CDateTemp( left.m_value, 0, 0 ));
arguments.push_back(CDateTemp( -right.m_value, 0, 0 ));
return arguments;
}

//------------------------------------------------------------------------------------------------------------------------------------------

	const vector<CDateTemp> operator+(const vector<CDateTemp>& arguments,  const Day& right)
{
vector<CDateTemp> tmp(arguments);
tmp.push_back(CDateTemp(0, 0, right.m_value));
return tmp;
}
	const vector<CDateTemp> operator+(const vector<CDateTemp>& arguments,  const Month& right)
{
vector<CDateTemp> tmp(arguments);
tmp.push_back(CDateTemp( 0, right.m_value, 0 ));
return tmp;
}
	const vector<CDateTemp> operator+(const vector<CDateTemp>& arguments,  const Year& right)
{
vector<CDateTemp> tmp(arguments);
tmp.push_back(CDateTemp( right.m_value, 0, 0 ));
return tmp;
}

const vector<CDateTemp> operator-(const vector<CDateTemp>& arguments,  const Day& right)
{
vector<CDateTemp> tmp(arguments);
tmp.push_back(CDateTemp(0, 0, -right.m_value));
return tmp;
}
	const vector<CDateTemp> operator-(const vector<CDateTemp>& arguments,  const Month& right)
{
vector<CDateTemp> tmp(arguments);
tmp.push_back(CDateTemp( 0, -right.m_value, 0 ));
return tmp;
}
	const vector<CDateTemp> operator-(const vector<CDateTemp>& arguments,  const Year& right)
{
vector<CDateTemp> tmp(arguments);
tmp.push_back(CDateTemp( -right.m_value, 0, 0 ));
return tmp;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//				Class represent date  
//------------------------------------------------------------------------------------------------------------------------------------------

class CDate
{
  public:
	CDate(int year, int month, int day)
	:m_year(year), m_month(month), m_day(day)
	{	
		if(!controlDate( m_year, m_month, m_day ))
		throw InvalidDateException(); 
	}

//------------------------------------------------------------------------------------------------------------------------------------------
//				Declaration of operator overloading + ( Binary plus )
//------------------------------------------------------------------------------------------------------------------------------------------

	friend const CDate operator+(const CDate& left, const Year& right);
	friend const CDate operator+(const CDate& left, const Month& right);
	friend const CDate operator+(const CDate& left, const Day& right);

//------------------------------------------------------------------------------------------------------------------------------------------
//				Declaration of operator overloading - ( Benary minus )
//------------------------------------------------------------------------------------------------------------------------------------------

	friend const CDate operator-(const CDate& left, const Year& right);
	friend const CDate operator-(const CDate& left, const Month& right);
	friend const CDate operator-(const CDate& left, const Day& right);

//------------------------------------------------------------------------------------------------------------------------------------------
//				Declaration of operator overloading - ( Unary minus )
//------------------------------------------------------------------------------------------------------------------------------------------

	friend const Day operator-(const Day& target);
	friend const Month operator-(const Month& target);
	friend const Year operator-(const Year& target);

//------------------------------------------------------------------------------------------------------------------------------------------
//				Declaration of operator overloading - ( Diff between two dates in days)
//------------------------------------------------------------------------------------------------------------------------------------------

	friend const long long int operator-(const CDate& left, const CDate& right);

//------------------------------------------------------------------------------------------------------------------------------------------
//				Declaration of operator overloading == ( Check is two dates equal )
//------------------------------------------------------------------------------------------------------------------------------------------
	
	friend bool operator==(const CDate& left, const CDate& right);

//------------------------------------------------------------------------------------------------------------------------------------------
//				Declaration of operator overloading != ( Check is two dates non equal )
//------------------------------------------------------------------------------------------------------------------------------------------

	friend bool operator!=(const CDate& left, const CDate& right);

//------------------------------------------------------------------------------------------------------------------------------------------
//				Declaration of operator overloading < ( Compare two dates )
//------------------------------------------------------------------------------------------------------------------------------------------

	friend bool operator<(const CDate& left, const CDate& right);

//------------------------------------------------------------------------------------------------------------------------------------------
//				Declaration operator overloading +=  ( Unary plus )			
//------------------------------------------------------------------------------------------------------------------------------------------   

	friend CDate& operator+=(CDate& left, const Year& right);
	friend CDate& operator+=(CDate& left, const Month& right);
	friend CDate& operator+=(CDate& left, const Day& right);
	friend CDate& operator+=(CDate& left, const vector<CDateTemp>& right);

//------------------------------------------------------------------------------------------------------------------------------------------
//				Declaration operator overloading <<  ( Writing to out stream )			
//------------------------------------------------------------------------------------------------------------------------------------------   

	friend ostream& operator<<(ostream&	   _oss, const CDate& 	_x);

//------------------------------------------------------------------------------------------------------------------------------------------
	
	friend ostringstream& operator<<(ostringstream&	   _oss, const CDate& 	_x);

//------------------------------------------------------------------------------------------------------------------------------------------

private:
	int m_year;
	int m_month;
	int m_day;

//------------------------------------------------------------------------------------------------------------------------------------------
//				Declaration monitoring function for catching invalided input date
//------------------------------------------------------------------------------------------------------------------------------------------

	friend bool controlDate(int, int, int);
};






//------------------------------------------------------------------------------------------------------------------------------------------
//				Body of operator overloading <<  ( Writing to out stream )
//------------------------------------------------------------------------------------------------------------------------------------------

	ostream& operator<<(ostream&	_oss, const CDate&	_x)  
{  

_oss << _x.m_year << (_x.m_month >= 10 ? "-" : "-0" ) << _x.m_month << (_x.m_day >= 10 ? "-" : "-0" ) << _x.m_day;  
	return _oss;  
}  
//------------------------------------------------------------------------------------------------------------------------------------------

	ostringstream& operator<<(ostringstream&	_oss, const CDate&	_x)  
{  

_oss << _x.m_year << (_x.m_month >= 10 ? "-" : "-0" ) << _x.m_month << (_x.m_day >= 10 ? "-" : "-0" ) << _x.m_day;  
	return _oss;  
}

//------------------------------------------------------------------------------------------------------------------------------------------
//				Body of operator overloading ==  ( Check is two dates equal )
//------------------------------------------------------------------------------------------------------------------------------------------
	
	bool operator==(const CDate& left, const CDate& right)
{
	if 
		(left.m_year == right.m_year 	&&
		left.m_month == right.m_month	&&
		left.m_day == right.m_day)
		return true;
	else	
	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//				Body of operator overloading !=  ( Check is two dates non equal )
//------------------------------------------------------------------------------------------------------------------------------------------
	
	bool operator!=(const CDate& left, const CDate& right)
{
	if 
		(left.m_year != right.m_year 	||
		left.m_month != right.m_month	||
		left.m_day != right.m_day)
		return true;
	else	
	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//				Body of operator overloading < ( Compare two dates )
//------------------------------------------------------------------------------------------------------------------------------------------

	bool operator<(const CDate& left, const CDate& right)
{
	if(left.m_year < right.m_year)
		return true;
		else if(left.m_year == right.m_year	&&
			left.m_month < right.m_month	)
			return true;
			else if(left.m_year == right.m_year 	&&
				left.m_month == right.m_month	&&
				left.m_day < right.m_day	)
				return true;
	else	
	return false;
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//				Body of operator overloading +  ( Binary plus )
//-----------------------------------------------------------------------------------------------------------------------------------------
//                              Plus for years
//-----------------------------------------------------------------------------------------------------------------------------------------	
	
	const CDate operator+(const CDate& left, const Year& right)
{
	if(!controlDate(left.m_year + right.m_value, left.m_month, left.m_day))
		throw InvalidDateException(); 	
	return CDate(left.m_year + right.m_value, left.m_month, left.m_day);
}
//------------------------------------------------------------------------------------------------------------------------------------------
//                              Plus for months
//-----------------------------------------------------------------------------------------------------------------------------------------

	const CDate operator+(const CDate& left, const Month& right)
{
int yearInc = right.m_value / 12;
int newMonth = left.m_month + right.m_value % 12;
	if ( newMonth > 12 )
	{
	newMonth -= 12;
	yearInc++;	
	}
	if ( newMonth < 0 )
	{
	newMonth += 12;
	yearInc--;	
	}
	if(!controlDate(left.m_year + yearInc, newMonth, left.m_day))
		throw InvalidDateException(); 	
	return CDate(left.m_year + yearInc, newMonth, left.m_day);
}

//------------------------------------------------------------------------------------------------------------------------------------------
//                              Plus for days
//-----------------------------------------------------------------------------------------------------------------------------------------
	
	const CDate operator+(const CDate& left, const Day& right)
{
long long int dayInc;
long long int newMonth = left.m_month;
long long int newYear;

		dayInc= (left.m_year-1)*365 + (left.m_year-1)/4 - (left.m_year-1)/100 + (left.m_year-1)/400 - (left.m_year-1)/4000;
		dayInc += right.m_value;
		newYear=1;
	


	while((dayInc>=366 && isLeap(newYear)) || (dayInc>=365 && !isLeap(newYear)))
	{
		if(isLeap(newYear))
		{
		newYear++;
		dayInc -= 366;
		}
		else
		{
		newYear++;
		dayInc -= 365;
		}
	}
	while(dayInc>howManyDays(newYear, newMonth))
	{	
		if(newMonth==13)
		{
		newMonth=1;
		newYear++;
		}
		dayInc -= howManyDays(newYear, newMonth);
		newMonth++;
	}
long long int newDay = left.m_day + dayInc;
	if(newDay > howManyDays(newYear, newMonth))
	{
	newDay -= howManyDays(newYear, newMonth);
	newMonth++;
		if(newMonth == 13)
		{
			newMonth = 1;
			newYear++;
		}
	}
	
	if(newDay > howManyDays(newYear, newMonth))
	{
	newDay -= howManyDays(newYear, newMonth);
	newMonth++;
		if(newMonth == 13)
		{
			newMonth = 1;
			newYear++;
		}
	}

	if(!controlDate(newYear, newMonth , newDay))
		throw InvalidDateException();

	return CDate(newYear, newMonth , newDay);
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//				Body of operator overloading -  ( Binary minus )
//-----------------------------------------------------------------------------------------------------------------------------------------
//				Minus for years
//-----------------------------------------------------------------------------------------------------------------------------------------	

	const CDate operator-(const CDate& left, const Year& right)
{
	if(!controlDate(left.m_year - right.m_value, left.m_month, left.m_day))
		throw InvalidDateException(); 	
	return CDate(left.m_year - right.m_value, left.m_month, left.m_day);
}
//------------------------------------------------------------------------------------------------------------------------------------------
//				Minus for months
//-----------------------------------------------------------------------------------------------------------------------------------------

	const CDate operator-(const CDate& left, const Month& right)
{
int yearInc = right.m_value / 12;
int newMonth = left.m_month - right.m_value % 12;
	if ( newMonth < 1 )
	{
	newMonth += 12;
	yearInc++;	
	}
	if ( newMonth > 12 )
	{
	newMonth -= 12;
	yearInc--;	
	}
	if(!controlDate(left.m_year - yearInc, newMonth, left.m_day))
		throw InvalidDateException(); 	
	return CDate(left.m_year - yearInc, newMonth, left.m_day);
}

//------------------------------------------------------------------------------------------------------------------------------------------
//				Minus for days
//-----------------------------------------------------------------------------------------------------------------------------------------
	
	const CDate operator-(const CDate& left, const Day& right)
{
long long int dayInc;
long long int newMonth  = left.m_month;
long long int newYear;
	

		dayInc = (left.m_year-1)*365 + (left.m_year-1)/4 - (left.m_year-1)/100 + (left.m_year-1)/400 - (left.m_year-1)/4000;
		dayInc -= right.m_value;
		newYear=1;
		
		while((dayInc>=366 && isLeap(newYear)) || (dayInc>=365 && !isLeap(newYear)))
		{
			if(isLeap(newYear))
			{
			newYear++;
			dayInc -= 366;
			}
			else
			{
			newYear++;
			dayInc -= 365;
			}
		}
	while(dayInc>howManyDays(newYear, newMonth))
	{	
		if(newMonth==13)
		{
		newMonth=1;
		newYear++;
		}
		dayInc -= howManyDays(newYear, newMonth);
		newMonth++;
	}
long long int newDay = left.m_day + dayInc;
	if(newDay > howManyDays(newYear, newMonth))
	{
	newDay -= howManyDays(newYear, newMonth);
	newMonth++;
		if(newMonth == 13)
		{
			newMonth = 1;
			newYear++;
		}
	}
	
	if(newDay > howManyDays(newYear, newMonth))
	{
	newDay -= howManyDays(newYear, newMonth);
	newMonth++;
		if(newMonth == 13)
		{
			newMonth = 1;
			newYear++;
		}
	}

	if(!controlDate(newYear, newMonth , newDay))
		throw InvalidDateException();

	return CDate(newYear, newMonth , newDay);
}


//------------------------------------------------------------------------------------------------------------------------------------------
//				Diff between two dates ( in days )
//-----------------------------------------------------------------------------------------------------------------------------------------
	
	const long long int operator-(const CDate& left, const CDate& right)
{
long long int daysFormat1;
long long int daysFormat2;
daysFormat1 = (left.m_year-1)*365 + (left.m_year-1)/4 - (left.m_year-1)/100 + (left.m_year-1)/400 - (left.m_year-1)/4000;
int n = 1;
while(n<left.m_month)
{
daysFormat1 += howManyDays(left.m_year, n);
n++;
}
daysFormat1 += left.m_day;
daysFormat2 = (right.m_year-1)*365 + (right.m_year-1)/4 - (right.m_year-1)/100 + (right.m_year-1)/400 - (right.m_year-1)/4000;
 n = 1;
while(n<right.m_month)
{
daysFormat2 += howManyDays(right.m_year, n);
n++;
}
daysFormat2 += right.m_day;
daysFormat1 -= daysFormat2;
return daysFormat1;
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//				Body of operator overloading -  ( Unary minus )
//-----------------------------------------------------------------------------------------------------------------------------------------
//				Minus for day
//-----------------------------------------------------------------------------------------------------------------------------------------

	const Day operator-(const Day& target)
{
return Day(-target.m_value);
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//				Minus for month
//-----------------------------------------------------------------------------------------------------------------------------------------

	const Month operator-(const Month& target)
{
return Month(-target.m_value);
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//				Minus for year ( Unary minus )
//-----------------------------------------------------------------------------------------------------------------------------------------

	const Year operator-(const Year& target)
{
return Year(-target.m_value);
}
	
//-----------------------------------------------------------------------------------------------------------------------------------------
//				Body of operator overloading +=  ( Unary plus )
//-----------------------------------------------------------------------------------------------------------------------------------------
//				Plus for set of right operands   ( Unary plus )
//------------------------------------------------------------------------------------------------------------------------------------------
	
	CDate& operator+=(CDate& left, const vector<CDateTemp>& right)
{
uint32_t i=0;
	while(i < right.size())
	{
	if(!controlDate(left.m_year + right[i].m_year, left.m_month, left.m_day))
				throw InvalidDateException();
	left.m_year += right[i].m_year;
		if(right[i].m_month!=0)
		{
		int yearInc = right[i].m_month / 12;
		int newMonth = left.m_month + right[i].m_month % 12;
			if ( newMonth > 12 )
			{
			newMonth -= 12;
			yearInc++;	
			}
				if ( newMonth < 0 )
				{	
				newMonth += 12;
				yearInc--;	
				}
					if(!controlDate(left.m_year + yearInc, newMonth, left.m_day))
						throw InvalidDateException(); 
		left.m_year = left.m_year + yearInc;
		left.m_month = newMonth;

		}
		if(right[i].m_day!=0)
		{
		long long int dayInc;
		long long int newMonth = left.m_month;
		long long int newYear;

		dayInc= (left.m_year-1)*365 + (left.m_year-1)/4 - (left.m_year-1)/100 + (left.m_year-1)/400 - (left.m_year-1)/4000;
		dayInc += right[i].m_day;
		newYear=1;
	


	while((dayInc>=366 && isLeap(newYear)) || (dayInc>=365 && !isLeap(newYear)))
	{
		if(isLeap(newYear))
		{
		newYear++;
		dayInc -= 366;
		}
		else
		{
		newYear++;
		dayInc -= 365;
		}
	}
	while(dayInc>howManyDays(newYear, newMonth))
	{	
		if(newMonth==13)
		{
		newMonth=1;
		newYear++;
		}
		dayInc -= howManyDays(newYear, newMonth);
		newMonth++;
	}
			long long int newDay = left.m_day + dayInc;
			if(newDay > howManyDays(newYear, newMonth))
			{
			newDay -= howManyDays(newYear, newMonth);
			newMonth++;
			if(newMonth == 13)
			{
				newMonth = 1;
				newYear++;
			}
			}
	
		if(newDay > howManyDays(newYear, newMonth))
		{
		newDay -= howManyDays(newYear, newMonth);
		newMonth++;
			if(newMonth == 13)
			{
				newMonth = 1;
				newYear++;
			}
		}

		if(!controlDate(newYear, newMonth , newDay))
			throw InvalidDateException();
		left.m_year = newYear;
		left.m_month = newMonth;
		left.m_day = newDay;

		}
	i++;
	}
return left;
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//				Plus for year
//-----------------------------------------------------------------------------------------------------------------------------------------	

	CDate& operator+=(CDate& left, const Year& right)
{
	if(!controlDate(left.m_year + right.m_value, left.m_month, left.m_day))
		throw InvalidDateException(); 	
	left.m_year = left.m_year + right.m_value;	
	return left;
}
//------------------------------------------------------------------------------------------------------------------------------------------
//                              Plus for month
//-----------------------------------------------------------------------------------------------------------------------------------------
	CDate& operator+=(CDate& left, const Month& right)
{
int yearInc = right.m_value / 12;
int newMonth = left.m_month + right.m_value % 12;
	if ( newMonth > 12 )
	{
	newMonth -= 12;
	yearInc++;	
	}
	if ( newMonth < 0 )
	{
	newMonth += 12;
	yearInc--;	
	}
	if(!controlDate(left.m_year + yearInc, newMonth, left.m_day))
		throw InvalidDateException(); 
	left.m_year = left.m_year + yearInc;
	left.m_month = newMonth;
	return left;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//                              Plus for day
//-----------------------------------------------------------------------------------------------------------------------------------------
	
	CDate& operator+=(CDate& left, const Day& right)
{
long long int dayInc;
long long int newMonth = left.m_month;
long long int newYear;

		dayInc= (left.m_year-1)*365 + (left.m_year-1)/4 - (left.m_year-1)/100 + (left.m_year-1)/400 - (left.m_year-1)/4000;
		dayInc += right.m_value;
		newYear=1;
	


	while((dayInc>=366 && isLeap(newYear)) || (dayInc>=365 && !isLeap(newYear)))
	{
		if(isLeap(newYear))
		{
		newYear++;
		dayInc -= 366;
		}
		else
		{
		newYear++;
		dayInc -= 365;
		}
	}
	while(dayInc>howManyDays(newYear, newMonth))
	{	
		if(newMonth==13)
		{
		newMonth=1;
		newYear++;
		}
		dayInc -= howManyDays(newYear, newMonth);
		newMonth++;
	}
long long int newDay = left.m_day + dayInc;
	if(newDay > howManyDays(newYear, newMonth))
	{
	newDay -= howManyDays(newYear, newMonth);
	newMonth++;
		if(newMonth == 13)
		{
			newMonth = 1;
			newYear++;
		}
	}
	
	if(newDay > howManyDays(newYear, newMonth))
	{
	newDay -= howManyDays(newYear, newMonth);
	newMonth++;
		if(newMonth == 13)
		{
			newMonth = 1;
			newYear++;
		}
	}

	if(!controlDate(newYear, newMonth , newDay))
		throw InvalidDateException();
	left.m_year = newYear;
	left.m_month = newMonth;
	left.m_day = newDay;
	return left;
}


//------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------END--OF--HOME--TASK------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------



#ifndef __PROGTEST__
string             toString                                ( const CDate     & x )
{
	ostringstream oss;
	oss << x;
	return oss . str ();
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

int                main                                    ( void )
{
  CDate tmp ( 2000, 1, 1 );

  assert ( toString ( CDate ( 2000, 1, 1 ) )  == "2000-01-01" );
  assert ( toString ( CDate ( 2500, 12, 21 ) )  == "2500-12-21" );
  assert ( toString ( CDate ( 1685, 7, 11 ) )  == "1685-07-11" );
  try
  {
    tmp = CDate ( 1900, 2, 29 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2000, 2, 29 ) )  == "2000-02-29" );
  assert ( toString ( CDate ( 2004, 2, 29 ) )  == "2004-02-29" );
  try
  {
    tmp = CDate ( 4000, 2, 29 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2018, 3, 15 ) + Year ( 1 ) )  == "2019-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Year ( 7 ) )  == "2025-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Year ( 73 ) )  == "2091-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Month ( 3 ) )  == "2018-06-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Month ( 1 ) )  == "2018-04-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Month ( 285 ) )  == "2041-12-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 1 ) )  == "2018-03-16" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 12 ) )  == "2018-03-27" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 1234567 ) )  == "5398-05-02" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 3 ) + Year ( 2 ) + Month ( 3 ) + Day ( 5 ) + Month ( 11 ) )  == "2021-05-23" );
  try
  {
    tmp = CDate ( 2000, 2, 29 ) + Year ( 300 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  try
  {
    tmp = CDate ( 2000, 3, 30 ) + Month ( 11 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2001, 2, 20 ) + Day ( 9 ) )  == "2001-03-01" );
  assert ( toString ( CDate ( 2000, 1, 1 ) + Day ( 28 ) + Month ( 1 ) )  == "2000-02-29" );
  assert ( toString ( CDate ( 1999, 1, 1 ) + Year ( 1 ) + Day ( 28 ) + Month ( 1 ) )  == "2000-02-29" );
  assert ( toString ( CDate ( 2001, 1, 1 ) + Day ( 1095 ) + Day ( 28 ) + Month ( 1 ) )  == "2004-02-29" );
  try
  {
    tmp = CDate ( 2001, 1, 1 ) + Day ( 28 ) + Month ( 1 ) + Day ( 1095 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  try
  {
    tmp = CDate ( 2000, 1, 1 ) + Day ( 28 ) + Month ( 1 ) + Year ( 1 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2000, 1, 1 );
  assert ( toString ( tmp - Year ( 5 ) + Month ( 2 ) )  == "1995-03-01" );
  assert ( toString ( tmp ) == "2000-01-01" );
  assert ( toString ( CDate ( 2000, 1, 1 ) - Year ( 1 ) - Month ( 3 ) - Day ( 10 ) )  == "1998-09-21" );
  assert ( toString ( CDate ( 2000, 1, 1 ) - Year ( 2 ) - Month ( -3 ) + Day ( -10 ) )  == "1998-03-22" );
  assert ( toString ( CDate ( 2000, 1, 1 ) + Day ( 59 ) - Month ( 1 ) - Year ( 2 ) )  == "1998-01-29" );
  try
  {
    tmp = CDate ( 2000, 1, 1 ) + Day ( 59 ) - Year ( 2 ) - Month ( 1 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2000, 1, 1 );
  tmp +=  - Year ( 2 ) - Month ( -3 ) + Day ( -10 );
  assert ( toString ( tmp ) == "1998-03-22" );
  tmp = CDate ( 2000, 1, 1 );
  tmp += Day ( 59 ) - Month ( 1 ) - Year ( 2 );
  assert ( toString ( tmp ) == "1998-01-29" );
  try
  {
    tmp = CDate ( 2000, 1, 1 );
    tmp += Day ( 59 ) - Year ( 2 ) - Month ( 1 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2018, 3, 15 ) + Day ( -3 );
  assert ( toString ( tmp ) == "2018-03-12" );
  assert ( !( CDate ( 2018, 3, 15 ) == CDate ( 2000, 1, 1 ) ) );
  assert ( CDate ( 2018, 3, 15 ) != CDate ( 2000, 1, 1 ) );
  assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2000, 1, 1 ) ) );
  assert ( CDate ( 2018, 3, 15 ) == CDate ( 2018, 3, 15 ) );
  assert ( !( CDate ( 2018, 3, 15 ) != CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) + Day ( 1 ) == CDate ( 2018, 3, 15 ) ) );
  assert ( CDate ( 2018, 3, 15 ) + Day ( 1 ) != CDate ( 2018, 3, 15 ) );
  assert ( !( CDate ( 2018, 3, 15 ) + Day ( 1 ) < CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) + Day ( -1 ) == CDate ( 2018, 3, 15 ) ) );
  assert ( CDate ( 2018, 3, 15 ) + Day ( -1 ) != CDate ( 2018, 3, 15 ) );
  assert ( CDate ( 2018, 3, 15 ) + Day ( -1 ) < CDate ( 2018, 3, 15 ) );
  assert ( CDate ( 2018, 3, 15 ) - CDate ( 2000, 1, 1 ) == 6648 );
  assert ( CDate ( 2000, 1, 1 ) - CDate ( 2018, 3, 15 ) == -6648 );
  assert ( CDate ( 2018, 3, 15 ) + Year ( 3 ) + Month ( -18 ) - CDate ( 2000, 1, 1 ) == 7197 );
  assert ( CDate ( 5398, 5, 2 ) - CDate ( 2018, 3, 15 ) == 1234567 );

  try
  {
    tmp = CDate ( 2000, 1, 1 );
    tmp += Day(59) - Year ( 2 ) - Month( 1 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2018, 3, 15 ) + Day( -3 );
  assert ( toString ( tmp ) == "2018-03-12" );
  assert ( !( CDate ( 2018, 3, 15 ) == CDate ( 2000, 1, 1 ) ) );
  assert ( CDate ( 2018, 3, 15 ) != CDate ( 2000, 1, 1 ) );
  assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2000, 1, 1 ) ) );
  assert ( CDate ( 2018, 3, 15 ) == CDate ( 2018, 3, 15 ) );
  assert ( !( CDate ( 2018, 3, 15 ) != CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2018, 3, 15 ) ) );
  assert ( CDate ( 2018, 3, 15 ) + Day ( -1 ) != CDate ( 2018, 3, 15 ) );
  assert ( CDate ( 2018, 3, 15 ) + Day ( -1 ) < CDate ( 2018, 3, 15 ) );
  assert ( CDate ( 2018, 3, 15 ) - CDate ( 2000, 1, 1 ) == 6648 );
  assert ( CDate ( 2000, 1, 1 ) - CDate ( 2018, 3, 15 ) == -6648 );
  assert ( CDate ( 2018, 3, 15 ) + Year ( 3 ) + Month( -18 ) - CDate ( 2000, 1, 1 ) == 7197 );
  assert ( CDate ( 5398, 5, 2 ) - CDate ( 2018, 3, 15 ) == 1234567 );
  return 0;
}
#endif /* __PROGTEST__ */

