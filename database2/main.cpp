#ifndef __PROGTEST__
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <climits>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <functional>
#include <iterator>
using namespace std;

class CDate 
{
  public:
                             CDate                         ( int               y,
                                                             int               m,
                                                             int               d )
                             : m_Y ( y ),
                               m_M ( m ),
                               m_D ( d )
    {
    }
    
    int                      CompareTo                     ( const CDate     & other ) const
    {
      if ( m_Y != other . m_Y )
        return ( other . m_Y < m_Y ) - ( m_Y < other . m_Y );
      if ( m_M != other . m_M )
        return ( other . m_M < m_M ) - ( m_M < other . m_M );
      return ( other . m_D < m_D ) - ( m_D < other . m_D );  
    }
    
    friend ostream         & operator <<                   ( ostream         & os,
                                                             const CDate     & d )
    {
      return os << d . m_Y << '-' << d . m_M << '-' << d . m_D;
    }
    
  private:
    int                      m_Y;
    int                      m_M;
    int                      m_D;
};
enum class ESortKey
{
  NAME,
  BIRTH_DATE,
  ENROLL_YEAR
};

//=====================================================================================================

#endif /* __PROGTEST__ */

static uint64_t cur_ID = 0;

//=================================================================================================
class CDateCompare
{
public:
bool operator() ( const CDate &lhs,
const CDate &rhs ) const;
};
//-------------------------------------------------------------------------------------------------
bool CDateCompare::operator() ( const CDate &lhs,
const CDate &rhs ) const
{
if (lhs.CompareTo(rhs) < 0)
return true;

return false;
}

//=====================================================================================================

uint64_t                     hashing                       (const string & orginalName)
{

	
	const char* f_Ptr = orginalName.c_str();
  uint64_t outHash = 31;
	while (*f_Ptr) 
  {
    	uint64_t hash = 31;
    while(*f_Ptr && f_Ptr[0] != ' ')
      {
		if (f_Ptr[0] >= 65 && f_Ptr[0] <= 90)
			hash = (hash * 67751) ^ ((f_Ptr[0] + 32) * 86719);
		else hash = (hash * 67751) ^ (f_Ptr[0] * 86719);
		++f_Ptr;
      }
      outHash += hash;
      
      if(*f_Ptr && f_Ptr[0] == ' ')
          ++f_Ptr;
  }
	return outHash;
}

//=====================================================================================================

uint64_t                     hashing                       (const string & orginalName , vector < uint64_t > & hashSingleNames)
{

	
	const char* f_Ptr = orginalName.c_str();
  uint64_t outHash = 31;
	while (*f_Ptr) 
  {
    	uint64_t hash = 31;
    while(*f_Ptr && f_Ptr[0] != ' ')
      {
		if (f_Ptr[0] >= 65 && f_Ptr[0] <= 90)
			hash = (hash * 67751) ^ ((f_Ptr[0] + 32) * 86719);
		else hash = (hash * 67751) ^ (f_Ptr[0] * 86719);
		++f_Ptr;
      }
      hashSingleNames.push_back(hash);
      outHash += hash;
      if(*f_Ptr && f_Ptr[0] == ' ')
          ++f_Ptr;
  }
	return outHash;
}

//=====================================================================================================


class CStudent
{
  public:
                              CStudent                     ( const string    & name,
                                                             const CDate     & born,
                                                             int               enrolled )
                                                             :
                        m_name     ( name     ),
                        m_born     ( born     ),
                        m_enrolled ( enrolled )
                                               {
                                                         m_ID = cur_ID ++;
                                                         this->setHashName(hashing(this->m_name,  this->hashSingleNames));
                                               }

    bool                      operator ==                   ( const CStudent  & other ) const;
    bool                      operator !=                   ( const CStudent  & other ) const;
    friend  bool              operator <                    ( const CStudent  & left, const CStudent & right );
    
    const   string            getName                      ( void ) const;
    const   CDate    &        getBorn                      ( void ) const;
    int                       getEnrolled                  ( void ) const;
    uint64_t                  getHashName                  ( void ) const;
    uint64_t                  getID                        ( void ) const;
    vector <uint64_t>             getHashSingleName            ( void ) const;

    void                      setHashName                  ( uint64_t hash );
  
  friend uint64_t             hashing                       ( const string & orginalName , set < uint64_t > & hashSingleNames);
  friend uint64_t             hashing                       ( const string & orginalName);

  private:
  vector<uint64_t> hashSingleNames;
  const string  m_name;
  const CDate   m_born;
  int           m_enrolled;
  uint64_t      m_hashName; 
  uint64_t      m_ID;
};

//----------------------------------------------------------------------------------------------------

const string               CStudent::getName                      ( void ) const
{
  return m_name;
}

//----------------------------------------------------------------------------------------------------`

uint64_t                   CStudent::getHashName                  ( void ) const
{
  return m_hashName;
}

//----------------------------------------------------------------------------------------------------`

vector<uint64_t>           CStudent::getHashSingleName            ( void ) const
{
  return hashSingleNames;
}

//----------------------------------------------------------------------------------------------------


const CDate   &            CStudent::getBorn                        ( void ) const
{ 
  return  m_born;
}

//----------------------------------------------------------------------------------------------------


int                        CStudent::getEnrolled                    ( void ) const
{
  return m_enrolled;
}

//----------------------------------------------------------------------------------------------------

uint64_t                   CStudent::getID                        ( void ) const
{
  return m_ID;
}

//----------------------------------------------------------------------------------------------------

void                       CStudent::setHashName                  ( uint64_t hash )
{
  m_hashName = hash;
}


//----------------------------------------------------------------------------------------------------

bool                      CStudent::operator ==                   ( const CStudent  & other ) const
{
  if                ( this->getBorn().CompareTo(other.getBorn()) == 0   &&
                    this->m_enrolled == other.getEnrolled()           &&
                    this->m_name.compare(other.getName())      == 0    )
                    return true;
  else
                    return false;
}


//----------------------------------------------------------------------------------------------------

bool                      CStudent::operator !=                   ( const CStudent  & other ) const
{
  if            (!( this->getBorn().CompareTo(other.getBorn()) == 0  &&
                    this->m_enrolled == other.getEnrolled()          &&
                    this->m_name.compare(other.getName())      == 0  ))
                    return true;
  else
                    return false;
}








//=====================================================================================================


  typedef map < CDate   ,  set  <   CStudent*    >, CDateCompare  > MapStudentsByBorn;
  typedef map < int     ,  set  <   CStudent*    >                > MapStudentsByEnrolled;
  typedef map < uint64_t,  set  <   CStudent*    >                > MapStudentsByHashName;

  

//=====================================================================================================
/*  CFilter class represent settings of our filter
 *  Starting value of enrolled before/after is max/min int value coz in case filtering without this pars
 *  all students will be meet the condition
 *
 */

class CFilter 
{
  public:
                  explicit         CFilter                       ( void )
                  {
                   m_haveName            = false ;
                   m_yearEnrolledAfter       = 0 ;
                   m_yearEnrolledBefore      = 0 ;
                   choosingOperandsForFilter = 0 ;
                  }
    CFilter                & Name                          ( const string    & name );
    CFilter                & BornBefore                    ( const CDate     & date );
    CFilter                & BornAfter                     ( const CDate     & date );
    CFilter                & EnrolledBefore                ( int               year );
    CFilter                & EnrolledAfter                 ( int               year );

   multiset<uint64_t>         getName                      ( void )     const        ;
   const CDate             &  getDateBornAfter             ( void )     const        ;
   const CDate             &  getDateBornBefore            ( void )     const        ;
   int                        getYearEnrolledAfter         ( void )     const        ;
   int                        getYearEnrolledBefore        ( void )     const        ;
   int                        getChoosingParamForFltr      ( void )     const        ;


  private:
   multiset  < uint64_t  >  m_name                ;
   const CDate    *    m_dateBornAfter            ;
   const CDate    *    m_dateBornBefore           ;
   int                 m_yearEnrolledAfter        ;
   int                 m_yearEnrolledBefore       ;
   uint8_t             choosingOperandsForFilter  ;
   bool                m_haveName                 ;
};

//----------------------------------------------------------------------------------------------------

multiset<uint64_t>          CFilter::getName                      ( void )      const
{
  return m_name;
}

//----------------------------------------------------------------------------------------------------

const CDate             &  CFilter::getDateBornAfter                ( void )     const
{
  return *m_dateBornAfter;
}

//----------------------------------------------------------------------------------------------------

const CDate             &  CFilter::getDateBornBefore               ( void )     const
{
  return *m_dateBornBefore;
}

//----------------------------------------------------------------------------------------------------

int                        CFilter::getYearEnrolledAfter            ( void )     const
{
  return m_yearEnrolledAfter;
}

//----------------------------------------------------------------------------------------------------

int                        CFilter::getYearEnrolledBefore           ( void )     const
{
  return m_yearEnrolledBefore;
}

//----------------------------------------------------------------------------------------------------

int                        CFilter::getChoosingParamForFltr         ( void )     const
{
  return choosingOperandsForFilter;
}

//----------------------------------------------------------------------------------------------------

    CFilter                & CFilter::BornBefore                    ( const CDate     & date )
    {
      choosingOperandsForFilter = ( choosingOperandsForFilter | 1 );
      m_dateBornBefore = &date;
      return *this;
    }


//----------------------------------------------------------------------------------------------------

    CFilter                & CFilter::BornAfter                     ( const CDate     & date )
    {
      choosingOperandsForFilter = ( choosingOperandsForFilter | 2 );
      m_dateBornAfter = &date;
      return *this;
    }

//----------------------------------------------------------------------------------------------------


    CFilter                & CFilter::EnrolledBefore                ( int               year )
    {
      choosingOperandsForFilter = ( choosingOperandsForFilter | 4 );
      m_yearEnrolledBefore = year;
      return *this;
    }


//----------------------------------------------------------------------------------------------------

    CFilter                & CFilter::EnrolledAfter                 ( int               year )
    {
      choosingOperandsForFilter = ( choosingOperandsForFilter | 8 );
      m_yearEnrolledAfter = year;
      return *this;
    }

//----------------------------------------------------------------------------------------------------

    CFilter                & CFilter::Name                          ( const string    & name )
    {
      if ( !m_haveName )
      choosingOperandsForFilter += 16;
      m_haveName = true;
      m_name.emplace( hashing( name ) );
      return *this;
    }

//=====================================================================================================

class CSort
{
  public:
                             CSort                         ( void ){}
    CSort                  & AddKey                        ( ESortKey          key,
                                                             bool              ascending );
    
vector <pair <ESortKey, bool>>               getParametrs                  ( void ) const;
  private:
    vector <pair <ESortKey, bool>> m_paramsSort;
};


//----------------------------------------------------------------------------------------------------

    CSort                  &            CSort::AddKey                 ( ESortKey    key, bool   ascending )
{
pair <ESortKey, bool>  tmpPair;
tmpPair.first  = key;
tmpPair.second = ascending;   
m_paramsSort.push_back(tmpPair);
return *this; 
}

//----------------------------------------------------------------------------------------------------

vector <pair <ESortKey, bool>>          CSort::getParametrs                  ( void ) const
{
  return m_paramsSort;
}





//=====================================================================================================

class CStudyDept 
{
  public:
              explicit      CStudyDept                    ( void )
                             {
                               counterStud = 0;
                             }
                            ~CStudyDept                    ( void );

    bool             AddStudent                       ( const CStudent  & x );
    bool             DelStudent                       ( const CStudent  & x );
    list<CStudent>   Search                           ( const CFilter   & flt,    const CSort     & sortOpt ) const;
    void             insertStudentsByBorn             ( list<CStudent> &forOrder, const CFilter   & flt) const;
    void             insertStudentsByName             ( list<CStudent> &forOrder, const CFilter   & flt) const;
    void             filteringStudents                ( list<CStudent> &forOrder, const CFilter   & flt) const;
    void             insertStudentsByEnrolled         ( list<CStudent> &forOrder, const CFilter   & flt) const;
    void             Multi_sort                       ( list<CStudent> &forOrder, const CSort     & sortOpt ) const ;

    set<string>             Suggest                       ( const string    & name ) const;
  
   private:
   uint64_t counterStud;
   MapStudentsByBorn       m_studentsByBorn     ;
   MapStudentsByEnrolled   m_studentsByEnrolled ;
   MapStudentsByHashName   m_studentsByHashName ;

};


                         CStudyDept::~CStudyDept                    ( void )
{
 for ( auto it : m_studentsByEnrolled)  
  {
    for ( auto itSet : it.second)
    delete itSet;
  }

}                         

//----------------------------------------------------------------------------------------------------

list<CStudent>           CStudyDept::Search                        ( const CFilter   & flt,
                                                             const CSort     & sortOpt ) const
    {
      

      list<CStudent> resultList;
      filteringStudents(resultList,    flt) ;
      Multi_sort(resultList, sortOpt);
      return resultList;
    }

//------------------------------------------------------------------------------------------------------------------


     void             CStudyDept::insertStudentsByName         ( list<CStudent> &forOrder, const CFilter   & flt) const
      {
        for( auto it : flt.getName())
        {
            auto itName = m_studentsByHashName.find(it);
            if( itName == m_studentsByHashName.end())
                 continue;
             for ( auto itSet : itName.operator*().second )
             {                  
        if  ((  flt.getChoosingParamForFltr() &  1 ) != 0 && itSet->getBorn().CompareTo(flt.getDateBornBefore()) >= 0)
          {
            continue;
          }
        if  ((  flt.getChoosingParamForFltr() &  2 ) != 0 && itSet->getBorn().CompareTo(flt.getDateBornAfter ()) <= 0)
          {
            continue;
          }
        if  ((  flt.getChoosingParamForFltr() &  4 ) != 0 && itSet->getEnrolled() >= flt.getYearEnrolledBefore()     )
          {
            continue;
          }
        if  ((  flt.getChoosingParamForFltr() &  8 ) != 0 && itSet->getEnrolled() <= flt.getYearEnrolledAfter ()     )
          {
            continue;
          }

              forOrder.push_back( *itSet );
        }
        }        
      }  

//----------------------------------------------------------------------------------------------------
 
      void             CStudyDept::insertStudentsByBorn         ( list<CStudent> &forOrder, const CFilter   & flt) const
      {
        auto itlow =   m_studentsByBorn.begin();
        auto itupr =   m_studentsByBorn.end();
                
                
                if  ((  flt.getChoosingParamForFltr() &  1 ) != 0 && (  flt.getChoosingParamForFltr() &  2 ) != 0)
                        if(flt.getDateBornAfter().CompareTo(flt.getDateBornBefore()) >= 0)
                          return ;
                
                if  ((  flt.getChoosingParamForFltr() &  2 ) != 0)
        {
            itlow = m_studentsByBorn.upper_bound (flt.getDateBornAfter());

        }


                if  ((  flt.getChoosingParamForFltr() &  1 ) != 0)
        {
            itupr = m_studentsByBorn.lower_bound (flt.getDateBornBefore());
        }

        if(itlow.operator*().first.CompareTo(itupr.operator*().first) >= 0) 
                                      return;

                while(  itlow != itupr && itlow != m_studentsByBorn.end()  )
        {
          for ( auto it : itlow.operator*().second)
          {
        if  ((  flt.getChoosingParamForFltr() &  4 ) != 0 && it->getEnrolled() >= flt.getYearEnrolledBefore()     )
          {

            continue;
          }
        if  ((  flt.getChoosingParamForFltr() &  8 ) != 0 && it->getEnrolled() <= flt.getYearEnrolledAfter ()     )
          {

            continue;
          }
            forOrder.push_back( *it );
              
         }
              itlow++;
        } 
        }


//----------------------------------------------------------------------------------------------------

      void             CStudyDept::insertStudentsByEnrolled         ( list<CStudent> &forOrder, const CFilter   & flt) const
      {
         auto itlow =   m_studentsByEnrolled.begin();
         auto itupr =   m_studentsByEnrolled.end();
          if  ((  flt.getChoosingParamForFltr() &  8 ) != 0)
        {
            itlow = m_studentsByEnrolled.upper_bound (flt.getYearEnrolledAfter());
        } 
          if  ((  flt.getChoosingParamForFltr() &  4 ) != 0)
        {
            itupr = m_studentsByEnrolled.lower_bound (flt.getYearEnrolledBefore());
        }
      
        if  ((  flt.getChoosingParamForFltr() &  4 ) != 0 && (  flt.getChoosingParamForFltr() &  8 ) != 0)
            if(flt.getYearEnrolledAfter() >= flt.getYearEnrolledBefore())
                return ;

                if(itlow.operator*().first >= itupr.operator*().first)
                              return;

          while(itlow != itupr && itlow != m_studentsByEnrolled.cend())
        {
              for( auto it : itlow.operator*().second )
              {
              forOrder.push_back(*it);
              }
              itlow++;
        }     
      }

//----------------------------------------------------------------------------------------------------

      void             CStudyDept::filteringStudents          ( list<CStudent> &forOrder, const CFilter   & flt) const
      {
        if  ((  flt.getChoosingParamForFltr() &  16 ) != 0 )
                    {
                      insertStudentsByName(forOrder, flt);
                      return;
                    }
        if  ((  flt.getChoosingParamForFltr() &  1 ) != 0 || ( flt.getChoosingParamForFltr() &  2 ) != 0 )
                    {
                      insertStudentsByBorn(forOrder, flt);  
                      return ;
                    }
        if  (  (  flt.getChoosingParamForFltr() &  4 ) != 0 || (  flt.getChoosingParamForFltr() &  8 ) != 0   )
                    {
                      insertStudentsByEnrolled(forOrder, flt);  
                      return ;
                    }
        for ( auto it : m_studentsByEnrolled)
        {
             for ( auto itSet : it.second )
                             forOrder.push_back(*itSet);
        }
      }

//----------------------------------------------------------------------------------------------------



void CStudyDept::Multi_sort(list<CStudent> &forOrder, const CSort     & sortOpt ) const 
{
        	uint32_t f_SizeSort = sortOpt.getParametrs().size();
          forOrder.sort(
  			[&](const CStudent &left, const CStudent &right) -> bool {
				for (uint32_t f_IndSort = 0; f_IndSort < f_SizeSort + 1; f_IndSort++) {
					if (f_IndSort == f_SizeSort) return left.getID() < right.getID();

                if(sortOpt.getParametrs()[f_IndSort].first == ESortKey::NAME )
                {
              	if (left.getName() == right.getName()) continue;

                                  if(sortOpt.getParametrs()[f_IndSort].second == true  )
                                  {
                                  string compLeft =  left.getName();
	                    						string compRight = right.getName();
	                    						transform(compLeft.begin(), compLeft.end(), compLeft.begin(), ::tolower);
	                    						transform(compRight.begin(), compRight.end(), compRight.begin(), ::tolower);
	                    						return (strcmp(compLeft.c_str(), compRight.c_str()) < 0);
	                    					  }
                                  else
                                  {
                                  string compLeft =  left.getName();
	                    						string compRight = right.getName();
	                    						transform(compLeft.begin(), compLeft.end(), compLeft.begin(), ::tolower);
	                    						transform(compRight.begin(), compRight.end(), compRight.begin(), ::tolower);
	                    						return (strcmp(compLeft.c_str(), compRight.c_str()) > 0);
	                    					  }
                }

                if(sortOpt.getParametrs()[f_IndSort].first == ESortKey::BIRTH_DATE )
                {
                if ((left.getBorn().CompareTo(right.getBorn())) == 0) continue;

                                  if(sortOpt.getParametrs()[f_IndSort].second == true  )
                                  return ((left.getBorn().CompareTo(right.getBorn())) < 0);
                                  else
                                  return ((left.getBorn().CompareTo(right.getBorn())) > 0);
                }
                if(sortOpt.getParametrs()[f_IndSort].first == ESortKey::ENROLL_YEAR )
                {
                if (left.getEnrolled()  ==  right.getEnrolled() ) continue;

                                  if(sortOpt.getParametrs()[f_IndSort].second == true  )
                                  return ((left.getEnrolled() - right.getEnrolled()) < 0);
                                  else
                                  return ((left.getEnrolled() - right.getEnrolled()) > 0);
                }
               return false;
        }
      return false;
			});
}


//----------------------------------------------------------------------------------------------------


set<string>              CStudyDept::Suggest                       ( const string    & name ) const
{
set<string> result;

vector < uint64_t > findingNames;
hashing( name,  findingNames);

for ( auto it : m_studentsByHashName)
    {
        for( auto iteratInVector : it.second)
        {
          int m_size = (int)findingNames.size();
         for( auto itHashName : iteratInVector->getHashSingleName())
          { 
            for( auto itWord : findingNames)
            {
            if( itWord == itHashName)
              {
               m_size--;
              }
            }

      }
                    if(m_size == 0)
            result.insert(iteratInVector->getName() );     
    }
    }

return result;



}


//----------------------------------------------------------------------------------------------------

 bool                     CStudyDept::AddStudent                    ( const CStudent  & x )
    {

        CStudent * tmpStudent = new CStudent (x);
        counterStud++;

        auto it = m_studentsByHashName.find(tmpStudent->getHashName());
        if( it != m_studentsByHashName.end() )
          {
          for ( auto itSerch : it.operator*().second )
            if( *tmpStudent == *itSerch )
              {
              delete tmpStudent;
              return false;
              }
            it.operator*().second.insert(tmpStudent); 
          }
          else
            {
              set < CStudent* > tmpSet;
              tmpSet.insert(tmpStudent);
              m_studentsByHashName.emplace(tmpStudent->getHashName(), tmpSet);
            }



          auto itBorn = m_studentsByBorn.find(tmpStudent->getBorn());
        if( itBorn != m_studentsByBorn.end() )
          {
            itBorn.operator*().second.insert(tmpStudent); 
          }
          else
            {
              set < CStudent* > tmpSet;
              tmpSet.insert(tmpStudent);
              m_studentsByBorn.emplace(tmpStudent->getBorn(), tmpSet);
            }



          auto itEnr = m_studentsByEnrolled.find(tmpStudent->getEnrolled());
        if( itEnr != m_studentsByEnrolled.end() )
          {
            itEnr.operator*().second.insert(tmpStudent); 
          }
          else
            {
              set < CStudent* > tmpSet;
              tmpSet.insert(tmpStudent);
              m_studentsByEnrolled.emplace(tmpStudent->getEnrolled(), tmpSet);
            }

        return true;  
    }

//----------------------------------------------------------------------------------------------------

    bool                     CStudyDept::DelStudent                    ( const CStudent  & x )
    {
        CStudent * tmpStudent = nullptr;
        auto itName = m_studentsByHashName.find(x.getHashName());
        if( itName == m_studentsByHashName.end()) 
                return false;
        else
           for ( auto itSerch : itName.operator*().second )
            {
              if( * itSerch == x)
              {
                tmpStudent = itSerch;
                break;
              }
            }
         if(!tmpStudent)
              return false;

        if(itName.operator*().second.size() == 1 )
              m_studentsByHashName.erase(itName);
        else
        {
            itName.operator*().second.erase(tmpStudent);

        }  


        auto itBorn = m_studentsByBorn.find(x.getBorn());
        if(itBorn.operator*().second.size() == 1 )
              m_studentsByBorn.erase(itBorn);
        else
        {
            itBorn.operator*().second.erase(tmpStudent);

        }  

        auto itEnrol = m_studentsByEnrolled.find(x.getEnrolled());
        if(itEnrol.operator*().second.size() == 1 )
              m_studentsByEnrolled.erase(itEnrol);
        else
        {
            itEnrol.operator*().second.erase(tmpStudent);

        }

        delete tmpStudent;

        return true;  
    }



//=====================================================================================================

#ifndef __PROGTEST__
int main ( void )
{
  CStudyDept x0;
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) ) );
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "Peter Peterson", CDate ( 1980, 4, 11), 2010 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "Peter Peterson", CDate ( 1980, 4, 11), 2010 ) ) );
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "James Bond", CDate ( 1997, 6, 17), 2010 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "James Bond", CDate ( 1997, 6, 17), 2010 ) ) );
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "James Bond", CDate ( 1980, 4, 11), 2016 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "James Bond", CDate ( 1980, 4, 11), 2016 ) ) );
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "Peter Peterson", CDate ( 1980, 4, 11), 2016 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "Peter Peterson", CDate ( 1980, 4, 11), 2016 ) ) );
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "Peter Peterson", CDate ( 1997, 6, 17), 2010 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "Peter Peterson", CDate ( 1997, 6, 17), 2010 ) ) );
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "James Bond", CDate ( 1997, 6, 17), 2016 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "James Bond", CDate ( 1997, 6, 17), 2016 ) ) );
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "Peter Peterson", CDate ( 1997, 6, 17), 2016 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "Peter Peterson", CDate ( 1997, 6, 17), 2016 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "John Peter Taylor", CDate ( 1983, 7, 13), 2014 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "Peter Taylor", CDate ( 1982, 2, 23), 2011 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "Peter John Taylor", CDate ( 1984, 1, 17), 2017 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ) ) );
  assert ( !( x0 . AddStudent ( CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ) ) ));
  assert ( x0 . DelStudent ( CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ) ) );
  
 assert ( x0 . Search ( CFilter () .  BornAfter ( CDate ( 2000, 7, 16) ) . BornBefore ( CDate ( 2000, 7, 16) ) , CSort () . AddKey ( ESortKey::NAME, true ) ) == (list<CStudent>
  {
  }) );

  assert ( x0 . Search ( CFilter () .  EnrolledAfter ( 2013 ) . EnrolledBefore ( 2013 ) , CSort () . AddKey ( ESortKey::NAME, true ) ) == (list<CStudent>
  {
  }) );


  assert ( x0 . Search ( CFilter (), CSort () ) == (list<CStudent>
  {
    CStudent ( "John Peter Taylor", CDate ( 1983, 7, 13), 2014 ),
    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 ),
    CStudent ( "Peter Taylor", CDate ( 1982, 2, 23), 2011 ),
    CStudent ( "Peter John Taylor", CDate ( 1984, 1, 17), 2017 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 )
  }) );

    assert ( x0 . Search ( CFilter () . Name ( "james bond" ), CSort ()) == (list<CStudent>
  {
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 )
  }) );


  assert ( x0 . Search ( CFilter (), CSort () . AddKey ( ESortKey::NAME, true ) ) == (list<CStudent>
  {
    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
    CStudent ( "John Peter Taylor", CDate ( 1983, 7, 13), 2014 ),
    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 ),
    CStudent ( "Peter John Taylor", CDate ( 1984, 1, 17), 2017 ),
    CStudent ( "Peter Taylor", CDate ( 1982, 2, 23), 2011 )
  }) );
  assert ( x0 . Search ( CFilter (), CSort () . AddKey ( ESortKey::NAME, false ) ) == (list<CStudent>
  {
    CStudent ( "Peter Taylor", CDate ( 1982, 2, 23), 2011 ),
    CStudent ( "Peter John Taylor", CDate ( 1984, 1, 17), 2017 ),
    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 ),
    CStudent ( "John Peter Taylor", CDate ( 1983, 7, 13), 2014 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 )
  }) );
  assert ( x0 . Search ( CFilter (), CSort () . AddKey ( ESortKey::ENROLL_YEAR, false ) . AddKey ( ESortKey::BIRTH_DATE, false ) . AddKey ( ESortKey::NAME, true ) ) == (list<CStudent>
  {
    CStudent ( "Peter John Taylor", CDate ( 1984, 1, 17), 2017 ),
    CStudent ( "John Peter Taylor", CDate ( 1983, 7, 13), 2014 ),
    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 ),
    CStudent ( "Peter Taylor", CDate ( 1982, 2, 23), 2011 )
  }) );

  assert ( x0 . Search ( CFilter () . Name ( "james bond" ), CSort () . AddKey ( ESortKey::ENROLL_YEAR, false ) . AddKey ( ESortKey::BIRTH_DATE, false ) . AddKey ( ESortKey::NAME, true ) ) == (list<CStudent>
  {
    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 )
  }) );
  assert ( x0 . Search ( CFilter () . BornAfter ( CDate ( 1980, 4, 11) ) . BornBefore ( CDate ( 1983, 7, 13) ) . Name ( "John Taylor" ) . Name ( "james BOND" ), CSort () . AddKey ( ESortKey::ENROLL_YEAR, false ) . AddKey ( ESortKey::BIRTH_DATE, false ) . AddKey ( ESortKey::NAME, true ) ) == (list<CStudent>
  {
    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 )
  }) );
  assert ( x0 . Search ( CFilter () . Name ( "james" ), CSort () . AddKey ( ESortKey::NAME, true ) ) == (list<CStudent>
  {
  }) );
  assert ( x0 . Suggest ( "peter" ) == (set<string>
  {
    "John Peter Taylor",
    "Peter John Taylor",
    "Peter Taylor"
  }) );
  assert ( x0 . Suggest ( "bond" ) == (set<string>
  {
    "Bond James",
    "James Bond"
  }) );
  assert ( x0 . Suggest ( "peter joHn" ) == (set<string>
  {
    "John Peter Taylor",
    "Peter John Taylor"
  }) );
  assert ( x0 . Suggest ( "peter joHn bond" ) == (set<string>
  {
  }) );
  assert ( x0 . Suggest ( "pete" ) == (set<string>
  {
  }) );
  assert ( x0 . Suggest ( "peter joHn PETER" ) == (set<string>
  {
    "John Peter Taylor",
    "Peter John Taylor"
  }) );
  assert ( ! x0 . AddStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ) ) );
  assert ( x0 . DelStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ) ) );
  assert ( x0 . Search ( CFilter () . BornAfter ( CDate ( 1980, 4, 11) ) . BornBefore ( CDate ( 1983, 7, 13) ) . Name ( "John Taylor" ) . Name ( "james BOND" ), CSort () . AddKey ( ESortKey::ENROLL_YEAR, false ) . AddKey ( ESortKey::BIRTH_DATE, false ) . AddKey ( ESortKey::NAME, true ) ) == (list<CStudent>
  {
    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 )
  }) );
  assert ( ! x0 . DelStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ) ) ); 
  return 0;
}
#endif /* __PROGTEST__ */
