#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */
class CEmployer
{
public:
    string m_email;
    string m_name;
    string m_surname;
    unsigned int m_salary;

    void setData (const string &surname, const string &name, const string &email, unsigned salary)
    {

        m_name = name;
        m_surname = surname;
        m_salary = salary;
        m_email = email;

    }
    void changeName (  const string &name, const string &surname)
    {

        m_name = name;
        m_surname = surname;
    }
    void changeEmail ( const string &email)
    {
        m_email = email;
    }
};




 bool Email_lesser(  CEmployer a,  CEmployer b )
{
    int tmp = a.m_email.compare(b.m_email);
    return tmp < 0 ?  true : false;
}  

 bool Name_lesser(  CEmployer a,  CEmployer b )
{
    int tmp = a.m_surname.compare(b.m_surname);

	if(tmp==0)
	tmp = a.m_name.compare(b.m_name);
	
    return tmp < 0 ?  true : false;
}  



//------------------------------------------------------------------------------------------------------------------------------------------

class CPersonalAgenda
{
private:
    uint16_t realSize = 0;
    uint16_t maxSize = 512;


public:

    CPersonalAgenda  (){
        EmployersNames.reserve(512);
	EmployersEmails.reserve(512);
    }
    mutable vector<CEmployer>::iterator I_temp;    
    mutable vector<CEmployer>::iterator I_Emails;
    mutable vector<CEmployer>::iterator I_Names;
    mutable vector<CEmployer>EmployersNames;
    mutable vector<CEmployer>EmployersEmails;
    
 


//------------------------------------------------------------------------------------------------------------------------------------------

    bool          Add              ( const string    & name,
                                     const string    & surname,
                                     const string    & email,
                                     unsigned int      salary )
    {
      			
	 int  i = 0, l = 0;


        if(realSize==maxSize)
        {
            maxSize=maxSize*2;
            EmployersNames.reserve(maxSize);
	    EmployersEmails.reserve(maxSize);
        }

        int tmp = -1;
        while(l<realSize && tmp < 0)
        {

            tmp = EmployersNames[l].m_surname.compare(surname);	            
		if(tmp==0)
            {
                tmp = EmployersNames[l].m_name.compare(name); 
	    }	
		l++;

        }
       if(tmp == 0)
        	{
        	    return false;
        	}   
	else if(tmp>0)
	l--;


        tmp = -1;
        while(i<realSize && tmp < 0)
        {

            tmp = EmployersEmails[i].m_email.compare(email);
		i++;

        }
       if(tmp == 0)
        	{
        	    return false;
        	}
	else if(tmp>0)
	i--;	   



        CEmployer emp;
        emp.setData(surname, name, email, salary);
        EmployersNames.insert(EmployersNames.begin()+(l), emp);
        EmployersEmails.insert(EmployersEmails.begin()+(i), emp);
	realSize++;


        
        
        return true;
    }
//------------------------------------------------------------------------------------------------------------------------------------------

    bool          Del              ( const string    & email )
    {
				
	CEmployer tmp;
	tmp.m_email=email;
        I_Emails = lower_bound(EmployersEmails.begin(), EmployersEmails.end(), tmp, Email_lesser);
	if(I_Emails == EmployersEmails.end()||
	I_Emails->m_email!=email  )
		return false;	
	tmp.m_surname=I_Emails->m_surname;
	tmp.m_name=I_Emails->m_name;
	I_Names = lower_bound(EmployersNames.begin(), EmployersNames.end(), tmp, Name_lesser);
	
	
	EmployersEmails.erase(I_Emails);
	EmployersNames.erase(I_Names);
	
	
	
	realSize--;
	return true;
    }

//------------------------------------------------------------------------------------------------------------------------------------------




    bool          Del              ( const string    & name,
                                     const string    & surname )    
	{
				
	CEmployer tmp;
	tmp.m_surname=surname;
	tmp.m_name=name;
	I_Names = lower_bound(EmployersNames.begin(), EmployersNames.end(), tmp, Name_lesser);
	if(I_Names == EmployersNames.end()||
	I_Names->m_name!=name	||
	I_Names->m_surname!=surname	)
		return false;	
	
	
	tmp.m_email=I_Names->m_email;
	
	
        I_Emails = lower_bound(EmployersEmails.begin(), EmployersEmails.end(), tmp, Email_lesser);
	
		

	EmployersEmails.erase(I_Emails);
	EmployersNames.erase(I_Names);
	realSize--;	
		
	return true;
	}

//------------------------------------------------------------------------------------------------------------------------------------------


    bool          ChangeName       ( const string    & email,
                                     const string    & newName,
                                    const string    & newSurname )
     {
				
	CEmployer tmp;
	tmp.m_email=email;
        I_Emails = lower_bound(EmployersEmails.begin(), EmployersEmails.end(), tmp, Email_lesser);
	
	if(	I_Emails == EmployersEmails.end() ||
	I_Emails->m_email!=email 	||
	(I_Emails->m_name==newName && I_Emails->m_surname==newSurname) )
		return false;	
	

	tmp.m_surname=I_Emails->m_surname;
	tmp.m_name=I_Emails->m_name;
	tmp.m_salary=I_Emails->m_salary;
	
	I_temp = lower_bound(EmployersNames.begin(), EmployersNames.end(), tmp, Name_lesser);
	
	tmp.changeName(newName, newSurname);	
	I_Names = lower_bound(EmployersNames.begin(), EmployersNames.end(), tmp, Name_lesser);
	
	if(I_Names->m_name==newName||I_Names->m_surname==newSurname)
		return false;	

	EmployersNames.erase(I_temp);
	EmployersNames.insert(I_Names, tmp);	
	I_Emails->changeName(newName, newSurname);
	return true;
    }
//------------------------------------------------------------------------------------------------------------------------------------------

    bool          ChangeEmail      ( const string    & name,
                                     const string    & surname,
                                     const string    & newEmail )
    {
				
	CEmployer tmp;
	tmp.m_surname=surname;
	tmp.m_name=name;
	I_Names = lower_bound(EmployersNames.begin(), EmployersNames.end(), tmp, Name_lesser);
	if(I_Names == EmployersNames.end() ||
	I_Names->m_name!=name		   ||
	I_Names->m_surname!=surname        ||
	I_Names->m_email==newEmail     )
		return false;
	
	tmp.m_email=I_Names->m_email;
	tmp.m_salary=I_Names->m_salary;

        I_temp = lower_bound(EmployersEmails.begin(), EmployersEmails.end(), tmp, Email_lesser);

	tmp.changeEmail(newEmail);
	I_Emails = lower_bound(EmployersEmails.begin(), EmployersEmails.end(), tmp, Email_lesser);	
	if(I_Emails->m_email==newEmail)
		return false;	
		
	EmployersEmails.erase(I_temp);
	I_Names->changeEmail(newEmail);	
	EmployersEmails.insert(I_Emails, tmp);
	return true;
    }




//------------------------------------------------------------------------------------------------------------------------------------------


    bool          SetSalary        ( const string    & name,
                                     const string    & surname,
                                     unsigned int      salary )
{
				
	CEmployer tmp;
	tmp.m_surname=surname;
	tmp.m_name=name;
	I_Names = lower_bound(EmployersNames.begin(), EmployersNames.end(), tmp, Name_lesser);
	if(I_Names == EmployersNames.end()  ||   
	I_Names->m_name!=name         ||
	I_Names->m_surname!=surname      )
		return false;	
		
	tmp.m_email=I_Names->m_email;
        I_Emails = lower_bound(EmployersEmails.begin(), EmployersEmails.end(), tmp, Email_lesser);
	I_Emails->m_salary=salary;
	I_Names->m_salary=salary;
	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------


    bool          SetSalary        ( const string    & email,
                                     unsigned int      salary )
    {
				
	CEmployer tmp;
	tmp.m_email=email;
        I_Emails = lower_bound(EmployersEmails.begin(), EmployersEmails.end(), tmp, Email_lesser);
	if(I_Emails == EmployersEmails.end()||
	I_Emails->m_email!=email     )
		return false;	
	tmp.m_surname=I_Emails->m_surname;
	tmp.m_name=I_Emails->m_name;
	I_Names = lower_bound(EmployersNames.begin(), EmployersNames.end(), tmp, Name_lesser);
	I_Emails->m_salary=salary;
	I_Names->m_salary=salary;	
	return true;
    }

//------------------------------------------------------------------------------------------------------------------------------------------


    unsigned int  GetSalary        ( const string    & name,
                                     const string    & surname ) const
{
	   			
	CEmployer tmp;
	tmp.m_surname=surname;
	tmp.m_name=name;
	I_Names = lower_bound(EmployersNames.begin(), EmployersNames.end(), tmp, Name_lesser);
	
	if(I_Names == EmployersNames.end() ||
	I_Names->m_name!=name	||
	I_Names->m_surname!=surname     )
		return 0;
	return I_Names->m_salary;
}
//------------------------------------------------------------------------------------------------------------------------------------------


    unsigned int  GetSalary        ( const string    & email ) const
{
				
	CEmployer tmp;
	tmp.m_email=email;
	I_Emails = lower_bound(EmployersEmails.begin(), EmployersEmails.end(), tmp, Email_lesser);
	
	if(I_Emails == EmployersEmails.end()	||
	I_Emails->m_email!=email	)
		return 0;
	return I_Emails->m_salary;
}

//------------------------------------------------------------------------------------------------------------------------------------------


    bool          GetRank          ( const string    & name,
                                     const string    & surname,
                                     int             & rankMin,
                                     int             & rankMax ) const
{
				
	CEmployer tmp;
	tmp.m_surname=surname;
	tmp.m_name=name;
	I_Names = lower_bound(EmployersNames.begin(), EmployersNames.end(), tmp, Name_lesser);
	if(I_Names == EmployersNames.end() ||
	I_Names->m_name!=name	||
	I_Names->m_surname!=surname    )
		return false;
	rankMin = 0;
	rankMax = 0;
	for(uint32_t i=0;i<realSize;i++)
	{
		if(I_Names->m_salary>EmployersNames[i].m_salary)
		{
		rankMin++;
		rankMax++;
		}	
		else if(I_Names->m_salary==EmployersNames[i].m_salary)
		rankMax++;
	}
	rankMax--;
	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------

    bool          GetRank          ( const string    & email,
                                     int             & rankMin,
                                     int             & rankMax ) const
{
				
	CEmployer tmp;
	tmp.m_email=email;
	I_Emails = lower_bound(EmployersEmails.begin(), EmployersEmails.end(), tmp, Email_lesser);
	
	if(I_Emails == EmployersEmails.end()	||
	I_Emails->m_email!=email	)
		return false;
	
	rankMin = 0;
	rankMax = 0;
	for(uint32_t i=0;i<realSize;i++)
	{
		if(I_Emails->m_salary>EmployersEmails[i].m_salary)
		{
		rankMin++;
		rankMax++;
		}	
		else if(I_Emails->m_salary==EmployersEmails[i].m_salary)
		rankMax++;
	}
	rankMax--;
	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------


    bool          GetFirst         ( string          & outName,
                                     string          & outSurname ) const
    {
				

        if(!EmployersNames.empty())
        {
            outName=EmployersNames[0].m_name;
            outSurname=EmployersNames[0].m_surname;
            return true;
        }
        else
            return false;
    }


//------------------------------------------------------------------------------------------------------------------------------------------



    bool          GetNext          ( const string    & name,
                                     const string    & surname,
                                     string          & outName,
                                     string          & outSurname ) const
{
				
	CEmployer tmp;
	tmp.m_surname=surname;
	tmp.m_name=name;
	I_Names = lower_bound(EmployersNames.begin(), EmployersNames.end(), tmp, Name_lesser);
	if(I_Names == EmployersNames.end()||
	I_Names->m_name!=name	||
	I_Names->m_surname!=surname	)
		return false;
	I_Names++;	
	if(I_Names == EmployersNames.end())
		return false;
	outName = I_Names->m_name;
	outSurname = I_Names->m_surname;
	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------


 

  
};

#ifndef __PROGTEST__
int main ( void )
{
  string outName, outSurname;
  int lo, hi;

  CPersonalAgenda b1;
  assert ( b1 . Add ( "John", "Smith", "john", 30000 ) );
    assert ( b1 . Del ( "john" ) );
	assert ( b1 . Add ( "John", "Smith", "john", 30000 ) );
    assert ( b1 . Del ( "john" ) );
assert ( b1 . Add ( "John", "Smith", "john", 30000 ) );
    assert ( b1 . Del ( "john" ) );
  assert ( b1 . Add ( "John", "Miller", "johnm", 35000 ) );
	  assert ( b1 . Del ( "johnm" ) );
return 0;	
  assert ( b1 . Add ( "Peter", "Smith", "peter", 23000 ) );
  assert ( b1 . GetFirst ( outName, outSurname )
           && outName == "John"
           && outSurname == "Miller" );
 assert ( b1 . GetNext ( "John", "Miller", outName, outSurname )
          && outName == "John"
         && outSurname == "Smith" );
  assert ( b1 . GetNext ( "John", "Smith", outName, outSurname )
         && outName == "Peter"
        && outSurname == "Smith" );
  assert ( ! b1 . GetNext ( "Peter", "Smith", outName, outSurname ) );
  assert ( b1 . SetSalary ( "john", 32000 ) );
  assert ( b1 . GetSalary ( "john" ) ==  32000 );
  assert ( b1 . GetSalary ( "John", "Smith" ) ==  32000 );
  assert ( b1 . GetRank ( "John", "Smith", lo, hi )
           && lo == 1
           && hi == 1 );
  assert ( b1 . GetRank ( "john", lo, hi )
           && lo == 1
           && hi == 1 );
  assert ( b1 . GetRank ( "peter", lo, hi )
           && lo == 0
           && hi == 0 );
  assert ( b1 . GetRank ( "johnm", lo, hi )
           && lo == 2
           && hi == 2 );
  assert ( b1 . SetSalary ( "John", "Smith", 35000 ) );
  assert ( b1 . GetSalary ( "John", "Smith" ) ==  35000 );
  assert ( b1 . GetSalary ( "john" ) ==  35000 );
  assert ( b1 . GetRank ( "John", "Smith", lo, hi )
           && lo == 1
           && hi == 2 );
  assert ( b1 . GetRank ( "john", lo, hi )
           && lo == 1
           && hi == 2 );
  assert ( b1 . GetRank ( "peter", lo, hi )
           && lo == 0
           && hi == 0 );
  assert ( b1 . GetRank ( "johnm", lo, hi )
           && lo == 1
           && hi == 2 );
  assert ( b1 . ChangeName ( "peter", "James", "Bond" ) );
  assert ( b1 . GetSalary ( "peter" ) ==  23000 );
  assert ( b1 . GetSalary ( "James", "Bond" ) ==  23000 );
  assert ( b1 . GetSalary ( "Peter", "Smith" ) ==  0 );
  assert ( b1 . GetFirst ( outName, outSurname )
           && outName == "James"
           && outSurname == "Bond" );
  assert ( b1 . GetNext ( "James", "Bond", outName, outSurname )
      && outName == "John"
        && outSurname == "Miller" );
  assert ( b1 . GetNext ( "John", "Miller", outName, outSurname )
       && outName == "John"
       && outSurname == "Smith" );
  assert ( ! b1 . GetNext ( "John", "Smith", outName, outSurname ) );
  assert ( b1 . ChangeEmail ( "James", "Bond", "james" ) );
  assert ( b1 . GetSalary ( "James", "Bond" ) ==  23000 );
  assert ( b1 . GetSalary ( "james" ) ==  23000 );
  assert ( b1 . GetSalary ( "peter" ) ==  0 );
  assert ( b1 . Del ( "james" ) );
  assert ( b1 . GetRank ( "john", lo, hi )
           && lo == 0
           && hi == 1 );
  assert ( b1 . Del ( "John", "Miller" ) );
  assert ( b1 . GetRank ( "john", lo, hi )
           && lo == 0
           && hi == 0 );
  assert ( b1 . GetFirst ( outName, outSurname )
           && outName == "John"
            && outSurname == "Smith" );
  assert ( ! b1 . GetNext ( "John", "Smith", outName, outSurname ) );
  assert ( b1 . Del ( "john" ) );
  assert ( ! b1 . GetFirst ( outName, outSurname ) );
  assert ( b1 . Add ( "John", "Smith", "john", 31000 ) );
  assert ( b1 . Add ( "john", "Smith", "joHn", 31000 ) );
  assert ( b1 . Add ( "John", "smith", "jOhn", 31000 ) );

  CPersonalAgenda b2;
  assert ( ! b2 . GetFirst ( outName, outSurname ) );
  assert ( b2 . Add ( "James", "Bond", "james", 70000 ) );
  assert ( b2 . Add ( "James", "Smith", "james2", 30000 ) );
  assert ( b2 . Add ( "Peter", "Smith", "peter", 40000 ) );
  assert ( ! b2 . Add ( "James", "Bond", "james3", 60000 ) );
  assert ( ! b2 . Add ( "Peter", "Bond", "peter", 50000 ) );
  assert ( ! b2 . ChangeName ( "joe", "Joe", "Black" ) );
  assert ( ! b2 . ChangeEmail ( "Joe", "Black", "joe" ) );
  assert ( ! b2 . SetSalary ( "Joe", "Black", 90000 ) );
  assert ( ! b2 . SetSalary ( "joe", 90000 ) );
  assert ( b2 . GetSalary ( "Joe", "Black" ) ==  0 );
  assert ( b2 . GetSalary ( "joe" ) ==  0 );
  assert ( ! b2 . GetRank ( "Joe", "Black", lo, hi ) );
  assert ( ! b2 . GetRank ( "joe", lo, hi ) );
  assert ( ! b2 . ChangeName ( "joe", "Joe", "Black" ) );
  assert ( ! b2 . ChangeEmail ( "Joe", "Black", "joe" ) );
  assert ( ! b2 . Del ( "Joe", "Black" ) );
  assert ( ! b2 . Del ( "joe" ) );
  assert ( ! b2 . ChangeName ( "james2", "James", "Bond" ) );
  assert ( ! b2 . ChangeEmail ( "Peter", "Smith", "james" ) );
  assert ( ! b2 . ChangeName ( "peter", "Peter", "Smith" ) );
  assert ( ! b2 . ChangeEmail ( "Peter", "Smith", "peter" ) );
  assert ( b2 . Del ( "Peter", "Smith" ) );
  assert ( ! b2 . ChangeEmail ( "Peter", "Smith", "peter2" ) );
  assert ( ! b2 . SetSalary ( "Peter", "Smith", 35000 ) );
  assert ( b2 . GetSalary ( "Peter", "Smith" ) ==  0 );
  assert ( ! b2 . GetRank ( "Peter", "Smith", lo, hi ) );
  assert ( ! b2 . ChangeName ( "peter", "Peter", "Falcon" ) );
  assert ( ! b2 . SetSalary ( "peter", 37000 ) );
  assert ( b2 . GetSalary ( "peter" ) ==  0 );
  assert ( ! b2 . GetRank ( "peter", lo, hi ) );
  assert ( ! b2 . Del ( "Peter", "Smith" ) );
  assert ( ! b2 . Del ( "peter" ) );
  assert ( b2 . Add ( "Peter", "Smith", "peter", 40000 ) );
  assert ( b2 . GetSalary ( "peter" ) ==  40000 );

  return 0;
}
#endif /* __PROGTEST__ */
