#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <typeinfo>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <memory>
#include <algorithm>
#include <type_traits>
using namespace std;

class CRect 
{
  public:
                             CRect                         ( double            x,
                                                             double            y,
                                                             double            w,
                                                             double            h )
                             : m_X ( x ),
                               m_Y ( y ),
                               m_W ( w ),
                               m_H ( h )
    {
    }
    friend ostream         & operator <<                   ( ostream         & os,
                                                             const CRect     & x )
    {
      return os << '(' << x . m_X << ',' << x . m_Y << ',' << x . m_W << ',' << x . m_H << ')';
    }
    double                   m_X;
    double                   m_Y;
    double                   m_W;
    double                   m_H;
};
#endif /* __PROGTEST__ */
//====================================================================================================================================

class CWindow;

class CPatternElement    
{

public:
                                                          
                                            CPatternElement                                   ( const CRect     &    ,
                                                                                                const string    &    ); 
//------------------------------------------------------------------------------------------------------------------------------------

                                            CPatternElement                                   ( const CRect     &    );
//------------------------------------------------------------------------------------------------------------------------------------

virtual                                     ~CPatternElement                                  ( void ){} 
//------------------------------------------------------------------------------------------------------------------------------------

virtual    void                             setPosValue                                       ( const CRect     &  ) = 0;
//------------------------------------------------------------------------------------------------------------------------------------

virtual CPatternElement *                   clone                                             ( void ) const = 0;
//------------------------------------------------------------------------------------------------------------------------------------

virtual string                              printElement                                      ( string ) const = 0;
//------------------------------------------------------------------------------------------------------------------------------------

virtual CPatternElement *                   getElementByID                                    ( int                  ,
                                                                                                CPatternElement *    ) const = 0;
//------------------------------------------------------------------------------------------------------------------------------------

friend ostream                            & operator <<                                       ( ostream         & os           ,
                                                                                                const CPatternElement     & x  )
    {
        string prefix = "";
        os << x.printElement( prefix );
        return os;
    }
//------------------------------------------------------------------------------------------------------------------------------------

friend ostringstream                      & operator <<                                       ( ostringstream         & oss     ,
                                                                                                const CWindow     & x           );
//------------------------------------------------------------------------------------------------------------------------------------

protected:          
    CRect       m_relPos;
    string      m_name;
    CRect       m_actualPosValue;

};

//------------------------------------------------------------------------------------------------------------------------------------

                                            CPatternElement::CPatternElement                  ( const CRect     & relPos,
                                                                                                const string    & name )
                                                                                              :
                                                                                                 m_relPos ( relPos )          ,
                                                                                                 m_name   ( name )            ,
                                                                                                 m_actualPosValue (CRect(0,0,0,0))                
                                                                                               {
                                                                                               }                                                            
 //------------------------------------------------------------------------------------------------------------------------------------

                                            CPatternElement::CPatternElement                  ( const CRect     & relPos )
                                                                                              :
                                                                                                 m_relPos ( relPos )          ,
                                                                                                 m_actualPosValue (CRect(0,0,0,0))
                                                                                              {        
                                                                                              }                                            
//=====================================================================================================================================

class CWindow
{


  public:
                                            CWindow                                           ( const string    & ,
                                                                                                const CRect     & );
//-------------------------------------------------------------------------------------------------------------------------------------

                                            CWindow                                           ( void );
//-------------------------------------------------------------------------------------------------------------------------------------

                                            CWindow                                           ( const CWindow   & );
//-------------------------------------------------------------------------------------------------------------------------------------

                                            ~CWindow                                          ( void );
//-------------------------------------------------------------------------------------------------------------------------------------

    CWindow                               & Add                                               ( const CPatternElement  & );
//-------------------------------------------------------------------------------------------------------------------------------------

    CPatternElement *                       Search                                            ( int ) const;
//-------------------------------------------------------------------------------------------------------------------------------------    

    void                                    SetPosition                                       ( const CRect     & );
//-------------------------------------------------------------------------------------------------------------------------------------  

    const CRect                           & GetPosition                                       ( void ) const;
//-------------------------------------------------------------------------------------------------------------------------------------

    const string                          & GetName                                           ( void ) const;
//-------------------------------------------------------------------------------------------------------------------------------------

    const vector  < CPatternElement * >   & GetElements                                       ( void ) const;
//-------------------------------------------------------------------------------------------------------------------------------------

    CWindow                               & operator =                                        ( const CWindow     & other)
    {
        for    ( auto it :  m_elements  )
            delete it;
            m_elements.clear();

            m_relPos = other.GetPosition();
            m_name = other.GetName();

         for    ( auto it :  other.GetElements()  )
         {
                m_elements.push_back(it->clone());   
         }
            return *this;
    }
//-------------------------------------------------------------------------------------------------------------------------------------

    friend ostringstream                  & operator <<                                       ( ostringstream         & oss ,
                                                                                                const CWindow    & x        )
    {   
        oss << "Window \"" << x.m_name << "\" " << x.m_relPos << '\n';
        string prefix;
        for (unsigned i = 0; i < x.m_elements.size(); i++)
            {
            if (i == x.m_elements.size() - 1)
            prefix = "   ";
            else
            prefix = "|  ";
            oss << "+- " << x.m_elements[i]->printElement(prefix);
            }
        return oss;
    }
//------------------------------------------------------------------------------------------------------------------------------------

    private:
    vector  < CPatternElement *  >  m_elements;
    string      m_name;
    CRect       m_relPos;
};
//------------------------------------------------------------------------------------------------------------------------------------

                                            CWindow::CWindow                                  ( const string    & title,
                                                                                                const CRect     & absPos )
                                                                                                :
                                                                                                m_name   ( title ),
                                                                                                m_relPos ( absPos )
                                                                                                {                                                                
                                                                                                }

//-------------------------------------------------------------------------------------------------------------------------------------

                                            CWindow::CWindow                                  ( void )
                                                                                              :
                                                                                              m_relPos  (CRect(0,0,0,0))
                                                                                              {                                                                
                                                                                              }

//-------------------------------------------------------------------------------------------------------------------------------------

                                            CWindow::CWindow                                  ( const CWindow   & other )
                                                                                              :
                                                                                              m_name (other.GetName()),
                                                                                              m_relPos  (other.GetPosition())
                                                                                              {
                                                                                                for (auto it : other.GetElements())
                                                                                                    m_elements.push_back(it->clone());
                                                                                              }

//-------------------------------------------------------------------------------------------------------------------------------------

                                            CWindow::~CWindow                                 ( void )
    {                            
        for(auto it: m_elements)
            delete it;
    }
//-------------------------------------------------------------------------------------------------------------------------------------

    CWindow                               & CWindow::Add                                      ( const CPatternElement  & element )
    {
        m_elements.push_back( element.clone());
        m_elements.back()->setPosValue( m_relPos);
        return * this;
    }
//-------------------------------------------------------------------------------------------------------------------------------------

    CPatternElement                       * CWindow::Search                                   ( int ID ) const
    {
        for ( CPatternElement* it : m_elements )
        {
            CPatternElement * tmpPtr = it->getElementByID( ID, it );
            if( tmpPtr != nullptr )
                	return tmpPtr;
        }	
        return nullptr;    
    }
//-------------------------------------------------------------------------------------------------------------------------------------    

    void                                    CWindow::SetPosition                              ( const CRect     & newPos )
    {
        m_relPos = newPos;
        for ( auto it : m_elements )
            it->setPosValue( m_relPos);
    }
//-------------------------------------------------------------------------------------------------------------------------------------  

    const CRect                           & CWindow::GetPosition                              ( void ) const
    {
        return m_relPos;
    }
//-------------------------------------------------------------------------------------------------------------------------------------

    const string                          & CWindow::GetName                                  ( void ) const
    {
        return m_name;
    }
//-------------------------------------------------------------------------------------------------------------------------------------

    const vector  < CPatternElement * >   & CWindow::GetElements                              ( void ) const
    {
        return m_elements;
    }
//=====================================================================================================================================

class CPanel : public CPatternElement
{
    public:
                                            CPanel                                            ( int               id,
                                                                                                const CRect     & relPos );                
//------------------------------------------------------------------------------------------------------------------------------------

                                            CPanel                                            ( void );                              
//------------------------------------------------------------------------------------------------------------------------------------

                                            ~CPanel                                           ( void );
//-------------------------------------------------------------------------------------------------------------------------------------    
    
    CPanel &                                Add                                               ( const CPatternElement  & element );
//------------------------------------------------------------------------------------------------------------------------------------

    CPanel                                * clone                                             ( void ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    string                                  printElement                                      ( string ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    CPatternElement *                       getElementByID                                    ( int               , 
                                                                                                CPatternElement * ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    void                                    setPosValue                                       ( const CRect     & );
//------------------------------------------------------------------------------------------------------------------------------------

    private:
    vector  < CPatternElement *  >  m_elements; 
    int     m_id;
};
//------------------------------------------------------------------------------------------------------------------------------------

    string                                  CPanel::printElement                              ( string prefix ) const
    {
        ostringstream oss;
        oss << "[" << m_id << "] Panel " << m_actualPosValue << '\n';

        unsigned i = 0;
            for ( i = 0; i < m_elements.size()-1; i++)
            {
                oss << prefix << "+- " << m_elements[i]->printElement( prefix + "|  ");
            }

            for ( i = i; i < m_elements.size(); i++)
            {
                oss << prefix << "+- " << m_elements[i]->printElement( prefix + "   ");
            }  
                return oss.str();
    }
//------------------------------------------------------------------------------------------------------------------------------------

    CPatternElement                       * CPanel::getElementByID                            ( int ID               ,
                                                                                                CPatternElement * mi ) const
    {
        if( m_id == ID  )
            return mi;
        else 
            for ( CPatternElement * it : m_elements )
                if( it->getElementByID(  ID  ,   it   ) != nullptr )
                {
                    return it;
                }
            return nullptr;
    }
//------------------------------------------------------------------------------------------------------------------------------------

    CPanel                                * CPanel::clone                                     ( void ) const
    {
        CPanel    * m_clone = new CPanel() ;

            m_clone->m_relPos = m_relPos;
            m_clone->m_id = m_id ;
            m_clone->m_actualPosValue = m_actualPosValue;

        for    ( CPatternElement * it :  m_elements  )
        {
            m_clone->m_elements.push_back(it->clone());   
        }

            return m_clone;
    }
//------------------------------------------------------------------------------------------------------------------------------------    
  
    void                                    CPanel::setPosValue                               ( const CRect     &  windowSize )
    {
        double x, y, w, h;
        w = this->m_relPos.m_W * windowSize.m_W;
        h = this->m_relPos.m_H * windowSize.m_H;
        x = this->m_relPos.m_X * windowSize.m_W + windowSize.m_X;
        y = this->m_relPos.m_Y * windowSize.m_H + windowSize.m_Y;
        m_actualPosValue = CRect (x, y, w, h);
        for ( auto it : m_elements )
            it->setPosValue( m_actualPosValue );

    }
                                            CPanel::CPanel                                    ( int               id,
                                                                                                const CRect     & relPos )
                                                                                              :
                                            CPatternElement                                   (                   relPos )
                                                                                              {
                                                                                                m_id = id;
                                                                                              }                
//------------------------------------------------------------------------------------------------------------------------------------

                                            CPanel::CPanel                                    ( void )
                                                                                              :
                                            CPatternElement                                   (   CRect(0,0,0,0))
                                                                                              {
                                                                                                m_id = 0;
                                                                                              }                                      
//------------------------------------------------------------------------------------------------------------------------------------

                                            CPanel::~CPanel                                   ( void )
    {                            
        for(auto it: m_elements)
            delete it;
    }
//-------------------------------------------------------------------------------------------------------------------------------------    
    
    CPanel &                                CPanel::Add                                       ( const CPatternElement  & element)
    {
        m_elements.push_back(element.clone());
        m_elements.back()->setPosValue( m_actualPosValue);

        return *this;
    } 
//=====================================================================================================================================

class CButton : public CPatternElement 
{
    
    public:
                                            CButton                                           ( int                   ,
                                                                                                const CRect         & ,
                                                                                                const string        & );
//------------------------------------------------------------------------------------------------------------------------------------

    CButton                               * clone                                             ( void ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    string                                  printElement                                      ( string ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    CPatternElement *                       getElementByID                                    ( int               ,
                                                                                                CPatternElement * ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    void                                    setPosValue                                       ( const CRect     & );
//------------------------------------------------------------------------------------------------------------------------------------

    private:
    int         m_id;
};
//------------------------------------------------------------------------------------------------------------------------------------

    void                                    CButton::setPosValue                              (const CRect     &  windowSize )
    {
      double x, y, w, h;
      w = this->m_relPos.m_W * windowSize.m_W;
      h = this->m_relPos.m_H * windowSize.m_H;
      x = this->m_relPos.m_X * windowSize.m_W + windowSize.m_X;
      y = this->m_relPos.m_Y * windowSize.m_H + windowSize.m_Y;
      m_actualPosValue = CRect (x, y, w, h);
    }
//------------------------------------------------------------------------------------------------------------------------------------

                                            CButton::CButton                                  ( int               id,
                                                                                                const CRect     & relPos,
                                                                                                const string    & name )
                                                                                               :
                                            CButton::CPatternElement                          ( relPos                  ,
                                                                                                name                    )
                                                                                              { 
                                                                                               m_id = id ;                            
                                                                                              }
//------------------------------------------------------------------------------------------------------------------------------------

    CButton                               * CButton::clone                                    ( void ) const
    {
        return new CButton( * this );
    }
//------------------------------------------------------------------------------------------------------------------------------------

    string                                  CButton::printElement                             ( string prefix ) const
    {
        ostringstream oss;
        oss << "[" << to_string(m_id) << "] Button \"" << m_name << "\" " << m_actualPosValue << '\n';
        return oss.str();
    }
//------------------------------------------------------------------------------------------------------------------------------------

    CPatternElement *                       CButton::getElementByID                           ( int ID               ,
                                                                                                CPatternElement * mi ) const
    {
        if(m_id== ID)
            return mi;
        return nullptr;
    }
//=====================================================================================================================================

class CInput : public CPatternElement
{
    public:
                                            CInput                                            ( int               ,
                                                                                                const CRect     & ,
                                                                                                const string    & );
//------------------------------------------------------------------------------------------------------------------------------------

    void                                    SetValue                                          ( const string    &  );
//------------------------------------------------------------------------------------------------------------------------------------

    const string                          & GetValue                                          ( void ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    CInput                                * clone                                             ( void ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    string                                  printElement                                      ( string ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    CPatternElement                       * getElementByID                                    ( int, CPatternElement * ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    void                                    setPosValue                                       ( const CRect     & );
//------------------------------------------------------------------------------------------------------------------------------------

    private:
    int         m_id;                                                             
};
//------------------------------------------------------------------------------------------------------------------------------------

    void                                    CInput::setPosValue                               ( const CRect     &  windowSize )
    {
        double x, y, w, h;
        w = this->m_relPos.m_W * windowSize.m_W;
        h = this->m_relPos.m_H * windowSize.m_H;
        x = this->m_relPos.m_X * windowSize.m_W + windowSize.m_X;
        y = this->m_relPos.m_Y * windowSize.m_H + windowSize.m_Y;
        m_actualPosValue = CRect (x, y, w, h);
    }
//------------------------------------------------------------------------------------------------------------------------------------

                                            CInput::CInput                                    ( int               id,
                                                                                                const CRect     & relPos,
                                                                                                const string    & value )
                                                                                                :
                                            CPatternElement                                   ( relPos                  ,
                                                                                                value                   )
                                                                                              {
                                                                                                  m_id = id ;
                                                                                              }
//------------------------------------------------------------------------------------------------------------------------------------

    void                                    CInput::SetValue                                  ( const string    & inputValue )
    {
        this->m_name = inputValue;

    }
//------------------------------------------------------------------------------------------------------------------------------------

    const string                          & CInput::GetValue                                  ( void ) const
    {   
        return m_name;
    }
//------------------------------------------------------------------------------------------------------------------------------------

    CInput                                * CInput::clone                                     ( void ) const
    {
        return new CInput( * this );
    }
//------------------------------------------------------------------------------------------------------------------------------------

    string                                  CInput::printElement                              ( string prefix ) const
    {
        ostringstream oss;
        oss << "[" << to_string(m_id) << "] Input \"" << m_name << "\" " << m_actualPosValue << '\n';
        return oss.str();
    }
//------------------------------------------------------------------------------------------------------------------------------------

    CPatternElement *                       CInput::getElementByID                            ( int ID               ,
                                                                                                CPatternElement * mi ) const
    {
        if(m_id== ID)
            return mi;
        return nullptr;
    }
//=====================================================================================================================================

class CLabel : public CPatternElement
{
    public:
                                            CLabel                                            ( int               ,
                                                                                                const CRect     & ,
                                                                                                const string    & );
//------------------------------------------------------------------------------------------------------------------------------------

    CLabel                                * clone                                             ( void ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    string                                  printElement                                      ( string             ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    CPatternElement                       * getElementByID                                    ( int                 ,
                                                                                                CPatternElement   * ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    void                                    setPosValue                                       ( const CRect     & );
//------------------------------------------------------------------------------------------------------------------------------------

    private:
    int         m_id;
};
//------------------------------------------------------------------------------------------------------------------------------------

    void                                    CLabel::setPosValue                               ( const CRect     &  windowSize )
    {
        double x, y, w, h;
        w = this->m_relPos.m_W * windowSize.m_W;
        h = this->m_relPos.m_H * windowSize.m_H;
        x = this->m_relPos.m_X * windowSize.m_W + windowSize.m_X;
        y = this->m_relPos.m_Y * windowSize.m_H + windowSize.m_Y;
        m_actualPosValue = CRect (x, y, w, h);
    }
//------------------------------------------------------------------------------------------------------------------------------------

                                            CLabel::CLabel                                    ( int               id,
                                                                                                const CRect     & relPos,
                                                                                                const string    & label )
                                                                                              :  
                                            CPatternElement                                   (                  relPos  ,
                                                                                                                 label   )
                                                                                              {
                                                                                                  m_id = id ;
                                                                                              }
//------------------------------------------------------------------------------------------------------------------------------------

    CLabel                                  * CLabel::clone                                   ( void ) const
    {
        return new CLabel( * this );
    }
//------------------------------------------------------------------------------------------------------------------------------------

    string                                  CLabel::printElement                              ( string prefix ) const
    {
        ostringstream oss;
        oss << "[" << to_string(m_id) << "] Label \"" << m_name << "\" " << m_actualPosValue << '\n';
        return oss.str(); 
    }
//------------------------------------------------------------------------------------------------------------------------------------

    CPatternElement                       * CLabel::getElementByID                            ( int ID               ,
                                                                                                CPatternElement * mi ) const
    {
        if(m_id== ID)
            return mi;
        return nullptr;
    }
//=====================================================================================================================================

class CComboBox : public CPatternElement
{

  public:
                                            CComboBox                                         ( int               ,
                                                                                                const CRect     & );
//------------------------------------------------------------------------------------------------------------------------------------

    CPatternElement                       * getElementByID                                    ( int               ,
                                                                                                CPatternElement * ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    CComboBox                             * clone                                             ( void ) const;
//------------------------------------------------------------------------------------------------------------------------------------
	
    string                                  printElement                                      ( string ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    CComboBox  &                            Add                                               ( const string    & );
//------------------------------------------------------------------------------------------------------------------------------------ 

    void                                    SetSelected                                       ( int );
//------------------------------------------------------------------------------------------------------------------------------------

    int                                     GetSelected                                       ( void ) const;
//------------------------------------------------------------------------------------------------------------------------------------

    void                                    setPosValue                                       ( const CRect     & );
//------------------------------------------------------------------------------------------------------------------------------------

    private:
    vector < string > m_menu;
    int         m_id;
    int m_selected;
};
//------------------------------------------------------------------------------------------------------------------------------------

    void                                    CComboBox::setPosValue                            ( const CRect     &  windowSize )
    {
        double x, y, w, h;
        w = this->m_relPos.m_W * windowSize.m_W;
        h = this->m_relPos.m_H * windowSize.m_H;
        x = this->m_relPos.m_X * windowSize.m_W + windowSize.m_X;
        y = this->m_relPos.m_Y * windowSize.m_H + windowSize.m_Y;
        m_actualPosValue = CRect (x, y, w, h);
    }
//------------------------------------------------------------------------------------------------------------------------------------
                                            CComboBox::CComboBox                              ( int               id,
                                                                                                const CRect     & relPos )
                                                                                                :
                                            CPatternElement                                   (                    relPos )
                                                                                              {
                                                                                                  m_selected = 0;
                                                                                                  m_id = id ;
                                                                                              }   
//------------------------------------------------------------------------------------------------------------------------------------

    CPatternElement                       * CComboBox::getElementByID                         ( int ID                   ,
                                                                                                CPatternElement     * mi ) const
    {
        if(m_id== ID)
            return mi;
        return nullptr;
    }
//------------------------------------------------------------------------------------------------------------------------------------

    CComboBox                             * CComboBox::clone                                  ( void ) const
    {
        return new CComboBox( * this );
    }

//------------------------------------------------------------------------------------------------------------------------------------

    string                                  CComboBox::printElement                           ( string prefix ) const
    {
        ostringstream oss;
        oss << "[" << m_id << "] ComboBox " << m_actualPosValue << '\n';
        for ( int i = 0; i < (int)m_menu.size(); i++)
        {
            oss << prefix <<  "+-";
        ( i == m_selected ) ? oss << '>' << m_menu[i] << "<\n" : oss << ' ' << m_menu[i] << '\n';
        }
        return oss.str();
    }
//------------------------------------------------------------------------------------------------------------------------------------

    CComboBox                             & CComboBox::Add                                    ( const string & inputString )
    {
        m_menu.push_back(inputString);
        return * this;        
    }                                                                              

//------------------------------------------------------------------------------------------------------------------------------------ 

    void                                    CComboBox::SetSelected                            ( int target )
    {
        m_selected = target;
    }      
//------------------------------------------------------------------------------------------------------------------------------------

    int                                     CComboBox::GetSelected                            ( void ) const
    {
        return m_selected;        
    }
//=//=====================================================================================================================================
//=====================================================================================================================================

#ifndef __PROGTEST__
template <typename _T>
string toString ( const _T & x )
{
  ostringstream oss;
  oss << x;
  return oss . str ();
}

int main ( void )
{
  assert ( sizeof ( CButton ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
  assert ( sizeof ( CInput ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
  assert ( sizeof ( CLabel ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
  assert ( sizeof ( CButton ) - sizeof ( string ) <= sizeof ( CPanel ) - sizeof ( vector<void*> ) );
  assert ( sizeof ( CInput ) - sizeof ( string ) <= sizeof ( CPanel ) - sizeof ( vector<void*> ) );
  assert ( sizeof ( CLabel ) - sizeof ( string ) <= sizeof ( CPanel ) - sizeof ( vector<void*> ) );
 
  CWindow a ( "Sample window", CRect ( 10, 10, 600, 480 ) );
  a . Add ( CButton ( 1, CRect ( 0.1, 0.8, 0.3, 0.1 ), "Ok" ) ) . Add ( CButton ( 2, CRect ( 0.6, 0.8, 0.3, 0.1 ), "Cancel" ) );
  a . Add ( CLabel ( 10, CRect ( 0.1, 0.1, 0.2, 0.1 ), "Username:" ) );
  a . Add ( CInput ( 11, CRect ( 0.4, 0.1, 0.5, 0.1 ), "chucknorris" ) );
  a . Add ( CPanel ( 12, CRect ( 0.1, 0.3, 0.8, 0.7 ) ) . Add ( CComboBox ( 20, CRect ( 0.1, 0.3, 0.8, 0.1 ) ) . Add ( "Karate" ) . Add ( "Judo" ) . Add ( "Box" ) . Add ( "Progtest" ) ) );
  CWindow b = a;

  assert ( dynamic_cast<CComboBox &> ( *b . Search ( 20 ) ) . GetSelected () == 0 );
  dynamic_cast<CComboBox &> ( *b . Search ( 20 ) ) . SetSelected ( 3 );
  assert ( dynamic_cast<CInput &> ( *b . Search ( 11 ) ) . GetValue () == "chucknorris" );
  dynamic_cast<CInput &> ( *b . Search ( 11 ) ) . SetValue ( "chucknorris@fit.cvut.cz" );
  CPanel & p = dynamic_cast<CPanel &> ( *b . Search ( 12 ) );
  p . Add ( CComboBox ( 21, CRect ( 0.1, 0.5, 0.8, 0.1 ) ) . Add ( "PA2" ) . Add ( "OSY" ) . Add ( "Both" ) );
  
	cout << toString ( b ) << endl;
  assert ( toString ( b ) ==
    "Window \"Sample window\" (10,10,600,480)\n"
    "+- [1] Button \"Ok\" (70,394,180,48)\n"
    "+- [2] Button \"Cancel\" (370,394,180,48)\n"
    "+- [10] Label \"Username:\" (70,58,120,48)\n"
    "+- [11] Input \"chucknorris@fit.cvut.cz\" (250,58,300,48)\n"
    "+- [12] Panel (70,154,480,336)\n"
    "   +- [20] ComboBox (118,254.8,384,33.6)\n"
    "   |  +- Karate\n"
    "   |  +- Judo\n"
    "   |  +- Box\n"
    "   |  +->Progtest<\n"
    "   +- [21] ComboBox (118,322,384,33.6)\n"
    "      +->PA2<\n"
    "      +- OSY\n"
    "      +- Both\n" );
  assert ( toString ( a ) ==
    "Window \"Sample window\" (10,10,600,480)\n"
    "+- [1] Button \"Ok\" (70,394,180,48)\n"
    "+- [2] Button \"Cancel\" (370,394,180,48)\n"
    "+- [10] Label \"Username:\" (70,58,120,48)\n"
    "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
    "+- [12] Panel (70,154,480,336)\n"
    "   +- [20] ComboBox (118,254.8,384,33.6)\n"
    "      +->Karate<\n"
    "      +- Judo\n"
    "      +- Box\n"
    "      +- Progtest\n" );
  assert ( toString ( p ) ==
    "[12] Panel (70,154,480,336)\n"
    "+- [20] ComboBox (118,254.8,384,33.6)\n"
    "|  +- Karate\n"
    "|  +- Judo\n"
    "|  +- Box\n"
    "|  +->Progtest<\n"
    "+- [21] ComboBox (118,322,384,33.6)\n"
    "   +->PA2<\n"
    "   +- OSY\n"
    "   +- Both\n" );
  b . SetPosition ( CRect ( 20, 30, 640, 520 ) );
  assert ( toString ( b ) ==
    "Window \"Sample window\" (20,30,640,520)\n"
    "+- [1] Button \"Ok\" (84,446,192,52)\n"
    "+- [2] Button \"Cancel\" (404,446,192,52)\n"
    "+- [10] Label \"Username:\" (84,82,128,52)\n"
    "+- [11] Input \"chucknorris@fit.cvut.cz\" (276,82,320,52)\n"
    "+- [12] Panel (84,186,512,364)\n"
    "   +- [20] ComboBox (135.2,295.2,409.6,36.4)\n"
    "   |  +- Karate\n"
    "   |  +- Judo\n"
    "   |  +- Box\n"
    "   |  +->Progtest<\n"
    "   +- [21] ComboBox (135.2,368,409.6,36.4)\n"
    "      +->PA2<\n"
    "      +- OSY\n"
    "      +- Both\n" );
  p . Add ( p );
  assert ( toString ( p ) ==
    "[12] Panel (84,186,512,364)\n"
    "+- [20] ComboBox (135.2,295.2,409.6,36.4)\n"
    "|  +- Karate\n"
    "|  +- Judo\n"
    "|  +- Box\n"
    "|  +->Progtest<\n"
    "+- [21] ComboBox (135.2,368,409.6,36.4)\n"
    "|  +->PA2<\n"
    "|  +- OSY\n"
    "|  +- Both\n"
    "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
    "   +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
    "   |  +- Karate\n"
    "   |  +- Judo\n"
    "   |  +- Box\n"
    "   |  +->Progtest<\n"
    "   +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
    "      +->PA2<\n"
    "      +- OSY\n"
    "      +- Both\n" );
  p . Add ( p );
  assert ( toString ( p ) ==
    "[12] Panel (84,186,512,364)\n"
    "+- [20] ComboBox (135.2,295.2,409.6,36.4)\n"
    "|  +- Karate\n"
    "|  +- Judo\n"
    "|  +- Box\n"
    "|  +->Progtest<\n"
    "+- [21] ComboBox (135.2,368,409.6,36.4)\n"
    "|  +->PA2<\n"
    "|  +- OSY\n"
    "|  +- Both\n"
    "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
    "|  +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
    "|  |  +- Karate\n"
    "|  |  +- Judo\n"
    "|  |  +- Box\n"
    "|  |  +->Progtest<\n"
    "|  +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
    "|     +->PA2<\n"
    "|     +- OSY\n"
    "|     +- Both\n"
    "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
    "   +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
    "   |  +- Karate\n"
    "   |  +- Judo\n"
    "   |  +- Box\n"
    "   |  +->Progtest<\n"
    "   +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
    "   |  +->PA2<\n"
    "   |  +- OSY\n"
    "   |  +- Both\n"
    "   +- [12] Panel (176.16,371.64,327.68,178.36)\n"
    "      +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
    "      |  +- Karate\n"
    "      |  +- Judo\n"
    "      |  +- Box\n"
    "      |  +->Progtest<\n"
    "      +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
    "         +->PA2<\n"
    "         +- OSY\n"
    "         +- Both\n" );
  p . Add ( p );
  assert ( toString ( p ) ==
    "[12] Panel (84,186,512,364)\n"
    "+- [20] ComboBox (135.2,295.2,409.6,36.4)\n"
    "|  +- Karate\n"
    "|  +- Judo\n"
    "|  +- Box\n"
    "|  +->Progtest<\n"
    "+- [21] ComboBox (135.2,368,409.6,36.4)\n"
    "|  +->PA2<\n"
    "|  +- OSY\n"
    "|  +- Both\n"
    "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
    "|  +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
    "|  |  +- Karate\n"
    "|  |  +- Judo\n"
    "|  |  +- Box\n"
    "|  |  +->Progtest<\n"
    "|  +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
    "|     +->PA2<\n"
    "|     +- OSY\n"
    "|     +- Both\n"
    "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
    "|  +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
    "|  |  +- Karate\n"
    "|  |  +- Judo\n"
    "|  |  +- Box\n"
    "|  |  +->Progtest<\n"
    "|  +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
    "|  |  +->PA2<\n"
    "|  |  +- OSY\n"
    "|  |  +- Both\n"
    "|  +- [12] Panel (176.16,371.64,327.68,178.36)\n"
    "|     +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
    "|     |  +- Karate\n"
    "|     |  +- Judo\n"
    "|     |  +- Box\n"
    "|     |  +->Progtest<\n"
    "|     +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
    "|        +->PA2<\n"
    "|        +- OSY\n"
    "|        +- Both\n"
    "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
    "   +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
    "   |  +- Karate\n"
    "   |  +- Judo\n"
    "   |  +- Box\n"
    "   |  +->Progtest<\n"
    "   +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
    "   |  +->PA2<\n"
    "   |  +- OSY\n"
    "   |  +- Both\n"
    "   +- [12] Panel (176.16,371.64,327.68,178.36)\n"
    "   |  +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
    "   |  |  +- Karate\n"
    "   |  |  +- Judo\n"
    "   |  |  +- Box\n"
    "   |  |  +->Progtest<\n"
    "   |  +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
    "   |     +->PA2<\n"
    "   |     +- OSY\n"
    "   |     +- Both\n"
    "   +- [12] Panel (176.16,371.64,327.68,178.36)\n"
    "      +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
    "      |  +- Karate\n"
    "      |  +- Judo\n"
    "      |  +- Box\n"
    "      |  +->Progtest<\n"
    "      +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
    "      |  +->PA2<\n"
    "      |  +- OSY\n"
    "      |  +- Both\n"
    "      +- [12] Panel (208.928,425.148,262.144,124.852)\n"
    "         +- [20] ComboBox (235.142,462.604,209.715,12.4852)\n"
    "         |  +- Karate\n"
    "         |  +- Judo\n"
    "         |  +- Box\n"
    "         |  +->Progtest<\n"
    "         +- [21] ComboBox (235.142,487.574,209.715,12.4852)\n"
    "            +->PA2<\n"
    "            +- OSY\n"
    "            +- Both\n" );
  assert ( toString ( b ) ==
    "Window \"Sample window\" (20,30,640,520)\n"
    "+- [1] Button \"Ok\" (84,446,192,52)\n"
    "+- [2] Button \"Cancel\" (404,446,192,52)\n"
    "+- [10] Label \"Username:\" (84,82,128,52)\n"
    "+- [11] Input \"chucknorris@fit.cvut.cz\" (276,82,320,52)\n"
    "+- [12] Panel (84,186,512,364)\n"
    "   +- [20] ComboBox (135.2,295.2,409.6,36.4)\n"
    "   |  +- Karate\n"
    "   |  +- Judo\n"
    "   |  +- Box\n"
    "   |  +->Progtest<\n"
    "   +- [21] ComboBox (135.2,368,409.6,36.4)\n"
    "   |  +->PA2<\n"
    "   |  +- OSY\n"
    "   |  +- Both\n"
    "   +- [12] Panel (135.2,295.2,409.6,254.8)\n"
    "   |  +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
    "   |  |  +- Karate\n"
    "   |  |  +- Judo\n"
    "   |  |  +- Box\n"
    "   |  |  +->Progtest<\n"
    "   |  +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
    "   |     +->PA2<\n"
    "   |     +- OSY\n"
    "   |     +- Both\n"
    "   +- [12] Panel (135.2,295.2,409.6,254.8)\n"
    "   |  +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
    "   |  |  +- Karate\n"
    "   |  |  +- Judo\n"
    "   |  |  +- Box\n"
    "   |  |  +->Progtest<\n"
    "   |  +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
    "   |  |  +->PA2<\n"
    "   |  |  +- OSY\n"
    "   |  |  +- Both\n"
    "   |  +- [12] Panel (176.16,371.64,327.68,178.36)\n"
    "   |     +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
    "   |     |  +- Karate\n"
    "   |     |  +- Judo\n"
    "   |     |  +- Box\n"
    "   |     |  +->Progtest<\n"
    "   |     +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
    "   |        +->PA2<\n"
    "   |        +- OSY\n"
    "   |        +- Both\n"
    "   +- [12] Panel (135.2,295.2,409.6,254.8)\n"
    "      +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
    "      |  +- Karate\n"
    "      |  +- Judo\n"
    "      |  +- Box\n"
    "      |  +->Progtest<\n"
    "      +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
    "      |  +->PA2<\n"
    "      |  +- OSY\n"
    "      |  +- Both\n"
    "      +- [12] Panel (176.16,371.64,327.68,178.36)\n"
    "      |  +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
    "      |  |  +- Karate\n"
    "      |  |  +- Judo\n"
    "      |  |  +- Box\n"
    "      |  |  +->Progtest<\n"
    "      |  +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
    "      |     +->PA2<\n"
    "      |     +- OSY\n"
    "      |     +- Both\n"
    "      +- [12] Panel (176.16,371.64,327.68,178.36)\n"
    "         +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
    "         |  +- Karate\n"
    "         |  +- Judo\n"
    "         |  +- Box\n"
    "         |  +->Progtest<\n"
    "         +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
    "         |  +->PA2<\n"
    "         |  +- OSY\n"
    "         |  +- Both\n"
    "         +- [12] Panel (208.928,425.148,262.144,124.852)\n"
    "            +- [20] ComboBox (235.142,462.604,209.715,12.4852)\n"
    "            |  +- Karate\n"
    "            |  +- Judo\n"
    "            |  +- Box\n"
    "            |  +->Progtest<\n"
    "            +- [21] ComboBox (235.142,487.574,209.715,12.4852)\n"
    "               +->PA2<\n"
    "               +- OSY\n"
    "               +- Both\n" );
  assert ( toString ( a ) ==
    "Window \"Sample window\" (10,10,600,480)\n"
    "+- [1] Button \"Ok\" (70,394,180,48)\n"
    "+- [2] Button \"Cancel\" (370,394,180,48)\n"
    "+- [10] Label \"Username:\" (70,58,120,48)\n"
    "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
    "+- [12] Panel (70,154,480,336)\n"
    "   +- [20] ComboBox (118,254.8,384,33.6)\n"
    "      +->Karate<\n"
    "      +- Judo\n"
    "      +- Box\n"
    "      +- Progtest\n" );
  return 0;
}
#endif /* __PROGTEST__ */
