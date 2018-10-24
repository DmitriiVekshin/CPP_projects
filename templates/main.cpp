#ifndef __PROGTEST__
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

#define MULTIPLE_STOPS

//=================================================================================================

template <typename _T, typename _E>
class CAccess;


//=================================================================================================
/*    Class represent relation between objects and type of relation,
 *    like a map where keys are objects and value is type of relation ( object type _E)
 *    All object have minimum one relation (CRelation) with minimum one items map
 *    That class have only one method for added relations
 */
//=================================================================================================

template <typename _T, typename _E>
class CRelation
{
    public:

                                CRelation ( const _T * myName     )
                                        {
                                            m_myName = myName;
                                            m_visited = false;
                                        }

    void                        addRelation                             (   CRelation< _T, _E > *  point     ,
                                                                            const   _E *  connection          );
    friend  CAccess< _T, _E >;
    
   private:
        
        bool m_visited;
        const _T * m_myName;
        map < CRelation< _T, _E > * ,  vector < const  _E * > >   m_relations;
};


//-------------------------------------------------------------------------------------------------


template <typename _T, typename _E>
    void                       CRelation< _T, _E >::addRelation     (   CRelation< _T, _E > *  point     ,
                                                                        const   _E *  connection          )
{
auto it = m_relations.find(point);
  if( it == m_relations.end() )
  {
    vector < const _E * > tmpVector;
    tmpVector.push_back( connection ); 
    m_relations.emplace(   point , tmpVector       );
  }

  else
  {
    it->second.push_back(  connection  );
  }                                           
}

//=================================================================================================
/*    Class represent map of objects;
 *    Methods : 3 time overloaded Find ( by parametrs of task) 
 *    1st case  3 param = Comparator, range of finding, start;
 *    2nd case  2 param = Range of finding, start;
 *    3rd case  1 param = Start;
 *    Add new two objects and connection between them
 *    and cleanMemory for cleaning
 */
//=================================================================================================

template <typename _T, typename _E>
class CAccess
{
    
  public:


                         CAccess                        ( void  ){}
                        ~CAccess                        ( void  );


    void  AddTwoObj                                       ( const   _E   connection ,
                                                            const   _T   obj1       ,
                                                            const   _T   obj2       );

   template <typename... _rest_T>  
   CAccess< _T, _E > &    Add                            ( const   _E       connection ,                                                                                                                      
                                                           const   _rest_T  &    ...    restObj     );
    
    template <typename _F>
    map < _T,int   >       Find                           ( const   _T     start    ,
                                                            int            range    ,      
                                                            _F             filter   ) const;
    

    map < _T,int   >       Find                           ( const   _T     start    ,
                                                            int            range    ) const;
    

    map < _T,int   >       Find                           ( const   _T     start    ) const;

   
  void                     cleanMemory                        ( void  );

  private:
   
   map < _T , CRelation< _T, _E > * > m_collectionRelation;
    

};

//-------------------------------------------------------------------------------------------------


template <typename _T, typename _E>
  CAccess< _T, _E >::~CAccess                        ( void  )
  {
    cleanMemory();  
  }

//-------------------------------------------------------------------------------------------------
template <typename _T, typename _E>
template <typename... _rest_T>  
   CAccess< _T, _E > &    CAccess< _T, _E >::Add                            ( const   _E       connection ,                                                                                                                      
                                                                              const   _rest_T  &    ...    restObj     )
   {
   const unsigned numargs = sizeof ... (restObj);
   
   vector < _T > allObjects;
   
   allObjects = {restObj ...};
   
        for ( uint64_t i = 0; i < numargs; i++ )
              for ( uint64_t l = i+1; l < numargs; l++ )
                   AddTwoObj( connection, allObjects[i], allObjects[l]);               
   
   
   return *this;
  }

//-------------------------------------------------------------------------------------------------

template <typename _T, typename _E>
  void   CAccess< _T, _E >::AddTwoObj                     ( const   _E    connection , 
                                                            const   _T    obj1    ,     
                                                            const   _T    obj2    ) 
{

        const _E * ptrConnection = new _E ( connection  );


        auto   itObj1 = m_collectionRelation.find(  obj1  );
        auto   itObj2 = m_collectionRelation.find(  obj2  );
        if ( itObj1 == m_collectionRelation.end() && itObj2 == m_collectionRelation.end() )
        {
            
            _T * ptrObj1       = new _T ( obj1  );
            _T * ptrObj2       = new _T ( obj2  );

            CRelation< _T, _E >    *    ptrTable1 = new CRelation<  _T, _E  >     (  ptrObj1 );
            CRelation< _T, _E >    *    ptrTable2 = new CRelation<  _T, _E  >     (  ptrObj2 );
            
            ptrTable1->addRelation( ptrTable2 ,  ptrConnection );
            ptrTable2->addRelation( ptrTable1 ,  ptrConnection );
            
            m_collectionRelation.emplace(  *ptrObj1 ,      ptrTable1 );
            m_collectionRelation.emplace(  *ptrObj2 ,      ptrTable2 );

        }
        
        else  if 
        ( itObj1 == m_collectionRelation.end() && itObj2 != m_collectionRelation.end() )
        {
          
          _T * ptrObj1       = new _T ( obj1  );
          
          CRelation< _T, _E >    *    ptrTable1 = new CRelation<  _T, _E  >     (  ptrObj1 );

          ptrTable1->addRelation( itObj2->second ,  ptrConnection );
          itObj2->second->addRelation( ptrTable1 ,  ptrConnection );
          
          m_collectionRelation.emplace(  *ptrObj1 ,      ptrTable1 );

        }

        else  if 
        ( itObj1 != m_collectionRelation.end() && itObj2 == m_collectionRelation.end() )
        {
          
          _T * ptrObj2       = new _T ( obj2  ); 

          CRelation< _T, _E >    *    ptrTable2 = new CRelation<  _T, _E  >     (  ptrObj2 );

          itObj1->second->addRelation(  ptrTable2,  ptrConnection );
          ptrTable2->addRelation( itObj1->second ,  ptrConnection );
          
          m_collectionRelation.emplace(  *ptrObj2 ,      ptrTable2 );

        }

        else
        {

          itObj1->second->addRelation( itObj2->second,   ptrConnection );
          itObj2->second->addRelation( itObj1->second ,  ptrConnection );
    
        }


        
}                                                            

 

                                                         


//-------------------------------------------------------------------------------------------------

    template <typename _T, typename _E>
    template <typename _F>
    map < _T,int   >       CAccess< _T, _E >::Find                           ( const   _T     start    ,
                                                                               int            range    ,      
                                                                               _F             filter   ) const
    {
    auto itStartVertex = m_collectionRelation.find(start);
          if( itStartVertex == m_collectionRelation.end() )
          {
            ostringstream oss;
            oss << start;
            throw invalid_argument( "unknown " + oss.str() );  
          }
    map < _T,int   > m_resultMap;  


    itStartVertex->second->m_visited = true;
    int nRound = 0;
    queue   <  CRelation< _T, _E > *  > nextVertexs;
    vector  <  CRelation< _T, _E > *  > readyVertexs; 
    nextVertexs.push( itStartVertex->second );
    readyVertexs.push_back( itStartVertex->second );
    m_resultMap.emplace(  * (  itStartVertex->second->m_myName  ), nRound  );


    while(  nextVertexs.size()  != 0 && nRound < range  )
    {
      uint64_t  actualSize = nextVertexs.size();
      nRound++;
        for(  uint64_t i = 0; i < actualSize; i++ )
        {
          auto itActualVertex = nextVertexs.front();
          for(  auto it : itActualVertex->m_relations )
          {
                
              if(!it.first->m_visited)
              {
                  for(  auto itConroling : it.second )
                  {
                        if(  filter(  *itConroling   ))
                        {
                              nextVertexs.push(it.first);
                              it.first->m_visited = true;
                              m_resultMap.emplace(  * (  it.first->m_myName  ), nRound  );
                              readyVertexs.push_back(it.first);
                              break;

                        }
                  }   
              }
          }
        nextVertexs.pop();
        }
    }
    for( auto itCleaner : readyVertexs)
          itCleaner->m_visited = false;
    
    
    return m_resultMap;
    }

//-------------------------------------------------------------------------------------------------

    template <typename _T, typename _E>
    map < _T,int   >       CAccess< _T, _E >::Find                           ( const   _T     start    ,
                                                                               int            range    ) const
    {
    auto itStartVertex = m_collectionRelation.find(start);
          if( itStartVertex == m_collectionRelation.end() )
          {
            ostringstream oss;
            oss << start;
            throw invalid_argument( "unknown " + oss.str() );  
          }
    map < _T,int   > m_resultMap;  


    itStartVertex->second->m_visited = true;
    int nRound = 0;
    queue   <  CRelation< _T, _E > *  > nextVertexs;
    vector  <  CRelation< _T, _E > *  > readyVertexs; 
    nextVertexs.push( itStartVertex->second );
    readyVertexs.push_back( itStartVertex->second );
    m_resultMap.emplace(  * (  itStartVertex->second->m_myName  ), nRound  );


    while(  nextVertexs.size()  != 0 && nRound < range  )
    {
      uint64_t  actualSize = nextVertexs.size();
      nRound++;
        for(  uint64_t i = 0; i < actualSize; i++ )
        {
          auto itActualVertex = nextVertexs.front();
          for(  auto it : itActualVertex->m_relations )
          {
              if(!it.first->m_visited)
              {
              nextVertexs.push(it.first);
              it.first->m_visited = true;
              m_resultMap.emplace(  * (  it.first->m_myName  ), nRound  );
              readyVertexs.push_back(it.first);
              }
          }
        nextVertexs.pop();
        }
    }
    for( auto itCleaner : readyVertexs)
          itCleaner->m_visited = false;
    
    
    return m_resultMap;
    }

//-------------------------------------------------------------------------------------------------

    template <typename _T, typename _E>
    map < _T,int   >       CAccess< _T, _E >::Find                           ( const   _T     start    ) const
    {
    auto itStartVertex = m_collectionRelation.find(start);
          if( itStartVertex == m_collectionRelation.end() )
          {
            ostringstream oss;
            oss << start;
            throw invalid_argument( "unknown " + oss.str() );  
          }
    map < _T,int   > m_resultMap;  


    itStartVertex->second->m_visited = true;
    int nRound = 0;
    queue   <  CRelation< _T, _E > *  > nextVertexs;
    vector  <  CRelation< _T, _E > *  > readyVertexs; 
    nextVertexs.push( itStartVertex->second );
    readyVertexs.push_back( itStartVertex->second );
    m_resultMap.emplace(  * (  itStartVertex->second->m_myName  ), nRound  );


    while(  nextVertexs.size()  != 0  )
    {
      uint64_t  actualSize = nextVertexs.size();
      nRound++;
        for(  uint64_t i = 0; i < actualSize; i++ )
        {
          auto itActualVertex = nextVertexs.front();
          for(  auto it : itActualVertex->m_relations )
          {
              if(!it.first->m_visited)
              {
              nextVertexs.push(it.first);
              it.first->m_visited = true;
              m_resultMap.emplace(  * (  it.first->m_myName  ), nRound  );
              readyVertexs.push_back(it.first);
              }
          }
        nextVertexs.pop();
        }
    }
    for( auto itCleaner : readyVertexs)
          itCleaner->m_visited = false;
    
    
    return m_resultMap;
    }

//-----------------------------------------------------------------------------------------------------

template <typename _T, typename _E>
  void                    CAccess< _T, _E >::cleanMemory                        ( void  )
  {
    set < const _E * > forDelete;
    for ( auto itPoint : m_collectionRelation)
    {
      for ( auto itTrain : itPoint.second->m_relations)
          for ( auto itItainInside : itTrain.second )
          {
            if(forDelete.insert(itItainInside).second == false)
                  delete itItainInside;
          }       

      delete itPoint.second->m_myName;
      delete itPoint.second;

    }
    
  }


#ifndef __PROGTEST__
//=================================================================================================
class CTrain
{
  public:
                             CTrain                        ( const string    & company, 
                                                             int               speed )
                             : m_Company ( company ), 
                               m_Speed ( speed ) 
    { 
    }
    //---------------------------------------------------------------------------------------------
    string                   m_Company;
    int                      m_Speed; 
};
//=================================================================================================
class TrainFilterCompany
{
  public:
                             TrainFilterCompany            ( const set<string> & companies ) 
                             : m_Companies ( companies ) 
    { 
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain & train ) const
    { 
      return m_Companies . find ( train . m_Company ) != m_Companies . end (); 
    }
    //---------------------------------------------------------------------------------------------
  private:  
    set <string>             m_Companies;    
};
//=================================================================================================
class TrainFilterSpeed
{
  public:
                             TrainFilterSpeed              ( int               min, 
                                                             int               max )
                             : m_Min ( min ), 
                               m_Max ( max ) 
    { 
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain    & train ) const
    { 
      return train . m_Speed >= m_Min && train . m_Speed <= m_Max; 
    }
    //---------------------------------------------------------------------------------------------
  private:  
    int                      m_Min;
    int                      m_Max; 
};
//=================================================================================================
bool                         NurSchnellzug                 ( const CTrain    & zug )
{
  return ( zug . m_Company == "OBB" || zug . m_Company == "DB" ) && zug . m_Speed > 100;
}
//=================================================================================================
int                          main                          ( void )
{
  CAccess<string,CTrain> lines;
  lines . Add ( CTrain (   "DB", 120 ), "Berlin", "Prague"   )
        . Add ( CTrain (   "CD",  80 ), "Berlin", "Prague"   )
        . Add ( CTrain (   "DB", 160 ), "Berlin", "Dresden"  )
        . Add ( CTrain (   "DB", 160 ), "Dresden", "Munchen" )
        . Add ( CTrain (   "CD",  90 ), "Munchen", "Prague"  )
        . Add ( CTrain (   "DB", 200 ), "Munchen", "Linz"    )
        . Add ( CTrain (  "OBB",  90 ), "Munchen", "Linz"    )
        . Add ( CTrain (   "CD",  50 ), "Linz", "Prague"     )
        . Add ( CTrain (   "CD", 100 ), "Prague", "Wien"     )
        . Add ( CTrain (  "OBB", 160 ), "Linz", "Wien"       )
        . Add ( CTrain ( "SNCF", 300 ), "Paris", "Marseille" )
        . Add ( CTrain ( "SNCF", 250 ), "Paris", "Dresden"   )
        . Add ( CTrain ( "SNCF", 200 ), "London", "Calais"   );


  
  assert ( lines . Find ( "Berlin" ) == (map<string,int>
  {
    make_pair ( "Berlin", 0 ),
    make_pair ( "Dresden", 1 ),
    make_pair ( "Linz", 2 ),
    make_pair ( "Marseille", 3 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Paris", 2 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 2 )
  }) );
  
  
  assert ( lines . Find ( "London" ) == (map<string,int>
  {
    make_pair ( "Calais", 1 ),
    make_pair ( "London", 0 )
  }) );
  
  assert ( lines . Find ( "Wien" ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Marseille", 5 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Paris", 4 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 0 )
  }) );

  
  assert ( lines . Find ( "Wien", 3 ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 0 )
  }) );

  assert ( lines . Find ( "Berlin", 2 ) == (map<string,int>
  {
    make_pair ( "Berlin", 0 ),
    make_pair ( "Dresden", 1 ),
    make_pair ( "Linz", 2 ),
  //  make_pair ( "Marseille", 3 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Paris", 2 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 2 )
  }) );  
  
  
  assert ( lines . Find ( "Wien", 5, NurSchnellzug ) == (map<string,int>
  {
    make_pair ( "Berlin", 4 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Prague", 5 ),
    make_pair ( "Wien", 0 )
  }) );
  assert ( lines . Find ( "Prague", 3,  TrainFilterCompany ( { "CD", "DB" } ) ) == (map<string,int>
  {
    make_pair ( "Berlin", 1 ),
    make_pair ( "Dresden", 2 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 1 ),
    make_pair ( "Prague", 0 ),
    make_pair ( "Wien", 1 )
  }) );
  assert ( lines . Find ( "Munchen", 4, TrainFilterSpeed ( 160, 250 ) ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 1 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 0 ),
    make_pair ( "Paris", 2 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "Munchen", 4, [] ( const CTrain & x ) { return x . m_Company == "CD"; } ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Linz", 2 ),
    make_pair ( "Munchen", 0 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "London", 20, [] ( const CTrain & x ) { return x . m_Company == "CD"; } ) == (map<string,int>
  {
    make_pair ( "London", 0 )
  }) );
  
  try
  {
     auto res = lines . Find ( "Salzburg" );
     assert ( "No exception thrown" == NULL );
  }
  
  catch ( const invalid_argument & e )
  {
    assert ( string ( e . what () ) == "unknown Salzburg" );
  } 
#ifdef MULTIPLE_STOPS
  lines . Add ( CTrain ( "RZD",  80 ), "Prague", "Kiev", "Moscow", "Omsk", "Irkutsk", "Vladivostok" );
  lines . Add ( CTrain ( "LAV", 160 ), "Malaga", "Cordoba", "Toledo", "Madrid", "Zaragoza", "Tarragona", "Barcelona", "Montpellier", "Marseille" );
  assert ( lines . Find ( "Madrid" ) == (map<string,int>
  {
    make_pair ( "Barcelona", 1 ),
    make_pair ( "Berlin", 4 ),
    make_pair ( "Cordoba", 1 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Irkutsk", 6 ),
    make_pair ( "Kiev", 6 ),
    make_pair ( "Linz", 5 ),
    make_pair ( "Madrid", 0 ),
    make_pair ( "Malaga", 1 ),
    make_pair ( "Marseille", 1 ),
    make_pair ( "Montpellier", 1 ),
    make_pair ( "Moscow", 6 ),
    make_pair ( "Munchen", 4 ),
    make_pair ( "Omsk", 6 ),
    make_pair ( "Paris", 2 ),
    make_pair ( "Prague", 5 ),
    make_pair ( "Tarragona", 1 ),
    make_pair ( "Toledo", 1 ),
    make_pair ( "Vladivostok", 6 ),
    make_pair ( "Wien", 6 ),
    make_pair ( "Zaragoza", 1 )
  }) );
  assert ( lines . Find ( "Omsk", 4 ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Irkutsk", 1 ),
    make_pair ( "Kiev", 1 ),
    make_pair ( "Linz", 2 ),
    make_pair ( "Moscow", 1 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Omsk", 0 ),
    make_pair ( "Paris", 4 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Vladivostok", 1 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "Moscow", 10, TrainFilterCompany ( { "RZD", "DB" } ) ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Irkutsk", 1 ),
    make_pair ( "Kiev", 1 ),
    make_pair ( "Linz", 5 ),
    make_pair ( "Moscow", 0 ),
    make_pair ( "Munchen", 4 ),
    make_pair ( "Omsk", 1 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Vladivostok", 1 )
  }) );
#endif /* MULTIPLE_STOPS */
  return 0;
}
#endif  /* __PROGTEST__ */