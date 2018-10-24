#ifndef __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <pthread.h>
#include <semaphore.h>
#include <cstdint>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <atomic>
using namespace std;


class CFITCoin;
class CCVUTCoin;
class CCustomer;

typedef struct shared_ptr<CFITCoin>                        AFITCoin;
typedef struct shared_ptr<CCVUTCoin>                       ACVUTCoin;
typedef struct shared_ptr<CCustomer>                       ACustomer;
//=================================================================================================
class CFITCoin
{
  public:
                             CFITCoin                      ( const vector<uint32_t> & vectors,
                                                             int               distMax )
                             : m_Vectors ( vectors ),
                               m_DistMax ( distMax ),
                               m_Count ( 0 )
    {
    }
    virtual                  ~CFITCoin                     ( void ) = default;
    vector<uint32_t>         m_Vectors;
    int                      m_DistMax;
    uint64_t                 m_Count;
};
//=================================================================================================
class CCVUTCoin       
{
  public:
                             CCVUTCoin                     ( const vector<uint8_t> & data,
                                                             int               distMin,
                                                             int               distMax )
                             : m_Data ( data ),
                               m_DistMin ( distMin ),
                               m_DistMax ( distMax ),
                               m_Count ( 0 )
    {
    }
    virtual                  ~CCVUTCoin                    ( void ) = default;
    vector<uint8_t>          m_Data;
    int                      m_DistMin;
    int                      m_DistMax;
    uint64_t                 m_Count;
};
//=================================================================================================
class CCustomer
{
  public:
    virtual                  ~CCustomer                    ( void ) = default;
    virtual AFITCoin         FITCoinGen                    ( void ) = 0;
    virtual ACVUTCoin        CVUTCoinGen                   ( void ) = 0;
  
    virtual void             FITCoinAccept                 ( AFITCoin          x ) = 0;
    virtual void             CVUTCoinAccept                ( ACVUTCoin         x ) = 0;
};
#endif /* __PROGTEST__ */
//=================================================================================================
uint64_t           countBinomialCoef                       ( uint32_t n, 
                                                             uint32_t k )
{
  uint64_t result = 0;
  uint64_t i = 0, l = 0, ri, rl;

  while ( k > 0 ) {

    if (k == n)
      result++;
    else if (k == 1)
      result += n;
    else {
      if ( k < (n - k)) {
        i = n - k + 1;
        ri = i;
        l = k;
        rl = l;
      }
      else {
        i = k + 1;
        ri = i;
        l = n - k;
        rl = l;
      }

      while (i < n || l > 1) {
        while (ri % 2 == 0 && rl % 2 == 0) {
          ri /= 2;
          rl /= 2;
        }
        if (i < n) {
          i++;
          ri *= i;
        }
        if (l > 1) {
          l--;
          rl *= l;
        }
      }
      result += (ri / rl);
    }
    k--;
  }

  result++;

  return result;
}
//=================================================================================================
int                min                                     ( int x, 
                                                             int y, 
                                                             int z )
{
  if (x < y)
    if (x < z)
      return x;
    else
      return z;
  else if (y < z)
    return y;
  else
    return z;  
}
//=================================================================================================
int                editDist                                ( string str1, 
                                                             string str2 )
{
  /*
   * @str1 -> prefix
   * @str2 -> suffix
  */

  //------------------------------------------------
  // Preparing table
  int len1 = str1.length();
  int len2 = str2.length();

  vector<vector<int>> d(len1 + 1, vector<int>(len2 + 1));

  //------------------------------------------------
  // Filling str1 d
  for (int i = 0; i <= len1; i++)
    d[i][0] = i;

  //------------------------------------------------
  // Filling str2 d
  for (int j = 0; j <= len2; j++)
    d[0][j] = j;

  //------------------------------------------------
  // Filling 2-d array
  for (int j = 1; j <= len2; j++) {

    for (int i = 1; i <= len1; i++) {

      if (str1[i - 1] == str2[j - 1])
        d[i][j] = d[i - 1][j - 1];
      else
        d[i][j] = min( d[i - 1][j] + 1,       // a deletion
                       d[i][j - 1] + 1,       // an insertion
                       d[i - 1][j - 1] + 1 ); // a substitution
    }
  }

  return d[len1][len2];
}
//=================================================================================================
int                getCntDiffBits                          ( uint32_t a,
                                                             uint32_t b )
{
  int count = 0;

  for (int c = a ^ b; c != 0; c = c & (c - 1))
    count++;

  return count;
}
//=================================================================================================
void               printIntToBin                           ( int num,
                                                             int uiCntUnconst )
{
  for (int j = 0; j < uiCntUnconst; j++)
    cout << (bool)((num >> (uiCntUnconst - j - 1)) & 1);
}
//=================================================================================================
class CRig
{
  public:
    //----------------------------------------------------------------------------------------
    static void              Solve                         ( ACVUTCoin         x );
    static void              Solve                         ( AFITCoin          x );
  
                             CRig                          ( void );
                             ~CRig                         ( void );

    void                     Start                         ( int               thrCnt );
    void                     Stop                          ( void );
    void                     AddCustomer                   ( ACustomer         c );
  
  private:
    //----------------------------------------------------------------------------------------
    void                       workerFunction                    ( void );
    void                       FITCoinThreadFunction             ( ACustomer cust );
    void                       CVUTCoinThreadFunction            ( ACustomer cust );
    void                       ResultCoinThreadFunction          ( ACustomer cust );
    //----------------------------------------------------------------------------------------
    class CProblem
    {
      public:
                               CProblem                      ( AFITCoin        & fit, 
                                                               ACustomer       & cust ) 
                               : m_FITCoin  ( fit     ), 
                                 m_CVUTCoin ( nullptr ),
                                 m_Customer ( cust    ){} 
     
                               CProblem                      ( ACVUTCoin       & cvut, 
                                                               ACustomer       & cust)     
                               : m_FITCoin  ( nullptr ), 
                                 m_CVUTCoin ( cvut    ),
                                 m_Customer ( cust    ){} 
      
        AFITCoin               getFITCoin                    ( void ) { return m_FITCoin ; }
        ACVUTCoin              getCVUTCoin                   ( void ) { return m_CVUTCoin; }
        ACustomer              getCustomer                   ( void ) { return m_Customer; }

      private:

        AFITCoin               m_FITCoin;  
        ACVUTCoin              m_CVUTCoin;
        ACustomer              m_Customer;
    };
    //----------------------------------------------------------------------------------------
    vector<thread>             m_workingThreads;

    atomic_bool                m_lastCustomerDied;
    atomic_bool                m_stopped;
    atomic<size_t>             m_numberOfCustomers;

    queue<CProblem>            m_problemQueue;
    mutex                      m_Mtx;

    condition_variable         m_consumerCV;
    condition_variable         m_producerCV;
};
//-------------------------------------------------------------------------------------------------
                   CRig::CRig                              ( void )
{
  m_numberOfCustomers = 0;
  m_stopped           = false;
  m_lastCustomerDied  = false;
}
//-------------------------------------------------------------------------------------------------
                   CRig::~CRig                             ( void )
{

  if (!m_stopped) Stop();
}
//-------------------------------------------------------------------------------------------------
void               CRig::Solve                             ( AFITCoin x )
{
  if (x->m_Vectors.size() == 0)
    return;

  //------------------------------------------------
  // Searching for the constant bits
  bool      bBits[32] = {0};
  bool      bSearchingBit;
  uint32_t  uiCntUnconst = 0;

  //--------------------------------------
  // We are searching for the '0' or '1' geted from the first vector
  // and if one of the others vectors hasn't the same bit
  // that's mean that this vector's column isn't consists of const bits
  for (int i = 0; i < 32; i++) {

    // Take bit-by-bit from the first vector and compare with others vectors bits
    bSearchingBit = (x->m_Vectors[0] >> i) & 1;

    for (auto j : x->m_Vectors) {

      if (((j >> i) & 1) != bSearchingBit) {
        bBits[i] = 1;
        uiCntUnconst++;
        break;
      }
    }

  }

  //------------------------------------------------
  // Creating tmp vectors without const bits
  vector<uint32_t> tmpVectorWithoutConstBits;
  vector<bool>     tmpVectorBool;

  tmpVectorWithoutConstBits.resize(x->m_Vectors.size());

  //--------------------------------------
  for (uint32_t i = 0; i < x->m_Vectors.size(); i++) {

    //--------------------------------------
    // Clear and filling the vector
    tmpVectorBool.clear();

    for (int j = 0; j < 32; j++)
      if (bBits[j] == 1)
        tmpVectorBool.push_back((x->m_Vectors[i] >> j) & 1);

    // Just increment i
    if (tmpVectorBool.size() == 0) {
      i++;
      continue;
    }

    //--------------------------------------
    // Filling tmp vector without const bits
    for (uint32_t k = 0; k < uiCntUnconst; k++)
      if (tmpVectorBool[k] == 1)
        tmpVectorWithoutConstBits[i] += ((uint32_t)pow(2, uiCntUnconst - k - 1));
  }

  //------------------------------------------------
  // Searching for the all numbers with suitable difference
  uint32_t uiBound;
  uint64_t uiResult = 0;
  int      iBitDiffCnt;

  // If we have more than one vector
  if (tmpVectorWithoutConstBits.size() > 1) {

    // Number of all unconst bits
    uiBound = (int)pow(2, uiCntUnconst) - 1;

    //--------------------------------------
    // Comparison our vectors with every possible option ( @uiBound )
    for (uint32_t i = 0; i <= uiBound; i++) {

      //--------------------------------------
      // Calculating if all bits differencies <= max distantion
      iBitDiffCnt = 0;

      for (uint32_t j = 0; j < tmpVectorWithoutConstBits.size(); j++) {

        // Calculating bits difference
        int tmpBitDiffCnt = getCntDiffBits(tmpVectorWithoutConstBits[j], i);

        if (tmpBitDiffCnt > x->m_DistMax){
          // cout << "BREAK" << endl;
          break;
        }

        if (tmpBitDiffCnt > iBitDiffCnt)
          iBitDiffCnt = tmpBitDiffCnt;

        //--------------------------------------
        // If difference is suitable
        if (iBitDiffCnt <= x->m_DistMax && j == tmpVectorWithoutConstBits.size() - 1) {

          uint32_t n, k;
          uint64_t tmp;

          n = 32 - uiCntUnconst;
          k = x->m_DistMax - iBitDiffCnt;

          k > n ? k = n : k = k;

          tmp = countBinomialCoef(n, k);
          uiResult += tmp;

        }
      }

    }
  } else { // If we have the only one vector
    uiResult = countBinomialCoef(32, x->m_DistMax);
  }

  // Set result
  x->m_Count = uiResult;
}
//-------------------------------------------------------------------------------------------------
void               CRig::Solve                             ( ACVUTCoin x )
{
  if (x->m_Data.size() == 0)
    return;

  //--------------------------------------
  string tmpStr, str1, str2;
  int    cntDist = 0;
  int    ed;

  // Preparing string with all bits in datasize.
  // Start from the last number of our data
  for (int i = x->m_Data.size() - 1; i >= 0; i--)
    for (int j = 7; j >= 0; j--)
      (((x->m_Data[i] >> j) & 1) == 1) ? tmpStr.push_back('1') : tmpStr.push_back('0');


  //--------------------------------------
  // Checking all prefix and suffix
  // prefix
  for (int i = 1; i <= (int)tmpStr.length(); i++) {

    // Preparing @str1 (prefix)
    str1 = tmpStr.substr(0, i);

    //--------------------------------------
    // suffix
    for (int j = 1; j <= (int)tmpStr.length(); j++) {

      // Preparing @str2 (suffix)
      str2 = tmpStr.substr(tmpStr.length() - j, j);

      //--------------------------------------
      // Check editDist 
      if (!(((i > j && i - j > x->m_DistMax) 	||
	 (j > i && j - i > x->m_DistMax)) 	||
	 (j < x->m_DistMin && i < x->m_DistMin) )) 
	{

        // If our prefix and suffix are suitable we need to calculate editation distance between @str1 and @str2
        ed = editDist(str1, str2);

        // Check suitable editDist
        if ((x->m_DistMin <= ed) && (ed <= x->m_DistMax))
          cntDist++;
	}
    }
  }

  x->m_Count = cntDist;
}
//-------------------------------------------------------------------------------------------------
void               CRig::Start                             ( int thrCnt )
{
  for (int i = 0; i < thrCnt; i++)
    m_workingThreads.push_back(thread(&CRig::workerFunction, this));
}
//-------------------------------------------------------------------------------------------------
void               CRig::Stop                              ( void )
{
  unique_lock<mutex> locker(m_Mtx);

  m_stopped = true;
  m_consumerCV.notify_one();
  m_producerCV.notify_one();
  locker.unlock();

  for (auto thread = m_workingThreads.begin(); thread != m_workingThreads.end(); thread++)
    if (thread->joinable()) thread->join();
}
//-------------------------------------------------------------------------------------------------
void               CRig::AddCustomer                       ( ACustomer cust )
{
  unique_lock<mutex> locker(m_Mtx);

  m_numberOfCustomers += 3;
  m_consumerCV.notify_one();
  m_producerCV.notify_one();
  locker.unlock();

  thread(&CRig::FITCoinThreadFunction,    this, cust).detach();
  thread(&CRig::CVUTCoinThreadFunction,   this, cust).detach();
  thread(&CRig::ResultCoinThreadFunction, this, cust).detach();
}
//-------------------------------------------------------------------------------------------------
void               CRig::workerFunction                    ( void )
{
  while (true) {

    unique_lock<mutex> lock(m_Mtx);
    m_consumerCV.wait(lock, [=]{ return m_lastCustomerDied || m_problemQueue.size() > 0; });

    if (m_lastCustomerDied) {
      if (m_problemQueue.size() == 0) {
        m_consumerCV.notify_all();
        lock.unlock();
        return;
      }
      m_consumerCV.notify_one();
    }

    //--------------------------------------
    CProblem task(m_problemQueue.front());
    m_problemQueue.pop();

    m_producerCV.notify_one();
    lock.unlock();

    AFITCoin  fit  = task.getFITCoin();
    ACVUTCoin cvut = task.getCVUTCoin();
    ACustomer cust = task.getCustomer();

    if (fit.get() != nullptr) {
      Solve(fit);
      cust->FITCoinAccept(fit);
    }

    if (cvut.get() != nullptr) {
      Solve(cvut);
      cust->CVUTCoinAccept(cvut);
    }

  }
}
//-------------------------------------------------------------------------------------------------
void               CRig::FITCoinThreadFunction             ( ACustomer cust )
{
  if (cust.get() == nullptr)
    return;

  while (true) {
    AFITCoin fitProblem = cust->FITCoinGen();
    unique_lock<mutex> lock(m_Mtx);
    m_producerCV.wait(lock, [ = ] { return m_problemQueue.size() <= 50; });

    if (fitProblem.get() == nullptr) {
      m_numberOfCustomers--;

      if (m_numberOfCustomers == 0 && m_stopped)
        m_lastCustomerDied = true;

      m_consumerCV.notify_one();
      lock.unlock();
      return;
    }

    CProblem prob(fitProblem, cust);
    m_problemQueue.push(prob);
    m_consumerCV.notify_one();
  }
}
//-------------------------------------------------------------------------------------------------
void               CRig::CVUTCoinThreadFunction            ( ACustomer cust ) 
{
  if (cust.get() == nullptr)
    return;

  while (true) {
    ACVUTCoin cvutProblem = cust->CVUTCoinGen();
    unique_lock<mutex> lock(m_Mtx);
    m_producerCV.wait(lock, [=] { return m_problemQueue.size() <= 50; });

    if (cvutProblem.get() == nullptr) {
      m_numberOfCustomers--;

      if (m_numberOfCustomers == 0 && m_stopped)
        m_lastCustomerDied = true;

      m_consumerCV.notify_one();
      lock.unlock();
      return;
    }

    CProblem prob(cvutProblem, cust);
    m_problemQueue.push(prob);
    m_consumerCV.notify_one();
  }
}
//-------------------------------------------------------------------------------------------------
void               CRig::ResultCoinThreadFunction          ( ACustomer cust ) 
{
  if (cust.get() == nullptr)
    return;

  while (true) {
    ACVUTCoin cvutProblem = cust->CVUTCoinGen();
    unique_lock<mutex> lock(m_Mtx);
    m_producerCV.wait(lock, [=] { return m_problemQueue.size() <= 50; });

    if (cvutProblem.get() == nullptr) {
      m_numberOfCustomers--;

      if (m_numberOfCustomers == 0 && m_stopped)
        m_lastCustomerDied = true;

      m_consumerCV.notify_one();
      lock.unlock();
      return;
    }

    CProblem prob(cvutProblem, cust);
    m_problemQueue.push(prob);
    m_consumerCV.notify_one();
  }
}
//=================================================================================================
#ifndef __PROGTEST__
class CCustomerTest : public CCustomer
{
  public:
    //---------------------------------------------------------------------------------------------
                             CCustomerTest                 ( void )
                             : m_FITIdx ( 0 ),
                               m_CVUTIdx ( 0 )
    {

      prepareTests ();
    }
    //---------------------------------------------------------------------------------------------
    virtual AFITCoin         FITCoinGen                    ( void ) override
    {
      if ( m_FITIdx < m_TestsFIT . size () )
        return AFITCoin ( m_TestsFIT[m_FITIdx++] . first );
      else
        return AFITCoin ();
    }
    //---------------------------------------------------------------------------------------------
    virtual ACVUTCoin        CVUTCoinGen                   ( void ) override
    {
      if ( m_CVUTIdx < m_TestsCVUT . size () )
        return m_TestsCVUT[m_CVUTIdx++] . first;
      else
        return ACVUTCoin ();
    }
    //---------------------------------------------------------------------------------------------
    virtual void             FITCoinAccept                 ( AFITCoin          x ) override
    {
      auto it = find_if ( m_TestsFIT . begin (), m_TestsFIT . end (), 
                          [ x ] ( const pair<AFITCoin, size_t> & v )
      {
        return v . first == x;
      });
      if ( it == m_TestsFIT . end () )
        printf ( "FITCoin: an unknown problem returned\n" );
      else if ( it -> second != x -> m_Count )
        printf ( "FITCoin: count mismatch, %zu != %zu\n", x -> m_Count, it -> second );
    }
    //---------------------------------------------------------------------------------------------
    virtual void             CVUTCoinAccept                ( ACVUTCoin         x ) override
    {
      auto it = find_if ( m_TestsCVUT . begin (), m_TestsCVUT . end (), 
                          [ x ] ( const pair<ACVUTCoin, size_t> & v )
      {
        return v . first == x;
      });
      if ( it == m_TestsCVUT . end () )
        printf ( "CVUTCoin: an unknown problem returned\n" );
      else if ( it -> second != x -> m_Count )
        printf ( "CVUTCoin: count mismatch, %zu != %zu\n", x -> m_Count, it -> second );
    }
    //---------------------------------------------------------------------------------------------
  private:
    vector<pair<AFITCoin, uint64_t> >  m_TestsFIT;
    vector<pair<ACVUTCoin, uint64_t> > m_TestsCVUT;
    size_t                             m_FITIdx;
    size_t                             m_CVUTIdx;
    //---------------------------------------------------------------------------------------------
    void                     prepareTests                  ( void )
    {
      // m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x6b8b4567 }, 0 ), 1 );
      // m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x327b23c6 }, 1 ), 33 );
      // m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x643c9869 }, 15 ), 1846943453 );
      // m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x66334873 }, 16 ), 2448023843 );
      // m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x74b0dc51 }, 17 ), 3013746563 );
      // m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x19495cff }, 31 ), 4294967295 );
      // m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x2ae8944a }, 32 ), 4294967296 );
      // m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x406518a4, 0x412f1ca1, 0x406d1ca5 }, 2 ), 0 );
      // m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x5cad9aeb, 0x7da99afb, 0x5d2992cb, 0x5d2992cb }, 4 ), 147 );
      // m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x396070f3, 0x3b6070f2, 0x796070a2, 0x796470b2, 0x3a6470f3 }, 9 ), 3294848 );
      // m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x408543d7, 0x428543d6, 0x4a81c3d7, 0x48a1c3d6, 0x4aa143d7, 0x4a8dc3d7 }, 21 ), 3985193193 );
      // m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0xe31d5fdc, 0xe1891fdc, 0xa19b7fde, 0xe3091ddc, 0xa39f6ddc, 0xe19b4fdc, 0xa11d5ddc }, 6 ), 337 );
      // m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x5ba85e68, 0x3aa85e78, 0x5aaa5ef8, 0x1baa5efa, 0x7ba856ea, 0x5baa5e68, 0x5bb85678, 0x3aaa5668, 0x5aaa56fa, 0x1bba5e6a }, 1 ), 0 );
      // m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x72d8aa96, 0x64c8a296, 0x76d8aaf6, 0x64c0aafe, 0x76d8aa9a, 0x76d0aaba, 0x74c0aab2, 0x70c8aaba, 0x64d0aa96, 0x76c0aad2, 0x62c0a2be, 0x74d0aa96, 0x76c8a2f2, 0x74c8aafe, 0x76c8aada, 0x66c0aaf6, 0x70d0aab2, 0x66c0aab6, 0x60d0a29a, 0x76c8aad2, 0x74c8aab2, 0x66c0a2f2, 0x62d8aa96, 0x60d8a2d2, 0x76d8aada, 0x62c0aab6, 0x72d8aaf6, 0x74d0a2de, 0x64c8aab2, 0x60c0a2f2, 0x72d8a292, 0x60c8a2ba, 0x64c8aaf6, 0x72d0a296, 0x66c8a296, 0x64c0a292, 0x62c8aabe, 0x62c8a2b6, 0x76d0aabe, 0x76d8a2d6, 0x62d0aafa, 0x60d8a2fa, 0x74d0aada, 0x60c0aafa, 0x76c0a2f6, 0x74c0aab2, 0x70c0a2d2, 0x70d0aa9a, 0x62c0aada, 0x72d8aafa }, 12 ), 8084682 );
  
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x45, 0x23, 0x98, 0x48, 0xdc }, 0, 1 ), 10 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x5c, 0x94, 0x58, 0x1f, 0x7c }, 3, 8 ), 277 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x58, 0xd7, 0x41, 0x1e, 0xa9 }, 1, 12 ), 704 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xe1, 0x00, 0x62, 0x08, 0x27 }, 0, 25 ), 1390 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x23, 0xe9, 0xcd, 0x43, 0x0f }, 0, 70 ), 1600 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x25, 0xf9, 0x72, 0xc2, 0xd7 }, 7, 7 ), 76 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xc4, 0x07, 0xfb, 0x5d, 0x50, 0xd7 }, 9, 14 ), 597 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xba, 0xe4, 0x30, 0xd9, 0x61, 0x89 }, 9, 29 ), 1549 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xb1, 0xa3, 0xa8, 0x5a, 0x84, 0xa8, 0xbd }, 15, 20 ), 729 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x8c, 0xd0, 0xe0, 0x76, 0x9e, 0x24, 0x86, 0xc4 }, 19, 37 ), 1771 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x1d, 0xf8, 0x86, 0xf5, 0xbd, 0x8d, 0xf0, 0x1a, 0xdd }, 6, 16 ), 1209 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xc8, 0xd4, 0xc2, 0xf8, 0xad, 0x23, 0x82, 0x5f, 0xc6, 0x2a }, 5, 43 ), 4970 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xb9, 0x4a, 0xd3, 0x77, 0xd7, 0xa4, 0x58, 0x4e, 0x42, 0x7c, 0xd4 }, 27, 70 ), 3806 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x06, 0x9a, 0xcc, 0x8d, 0x8f, 0x89, 0x1b, 0x7f, 0xa4, 0xf9, 0x48, 0x78 }, 50, 100 ), 2167 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xbb, 0x40, 0x26, 0xde, 0xc3, 0x85, 0xa5, 0xed, 0x3f, 0xf0, 0xc1, 0xb7, 0xc7 }, 42, 99 ), 4074 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x65, 0x0f, 0x15, 0xa8, 0x8c, 0xe9, 0xaf, 0x26, 0xb6, 0x3c, 0xb6, 0x40, 0x57, 0x35 }, 6, 42 ), 7397 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xe4, 0x50, 0x7e, 0x5d, 0x0b, 0xbf, 0x84, 0xea, 0x82, 0x0a, 0x8f, 0x70, 0x4a, 0x7f, 0x31 }, 29, 120 ), 10254 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x02, 0x47, 0x96, 0x12, 0x5d, 0x3f, 0x9e, 0x47, 0xee, 0xc5, 0xfd, 0x2b, 0x7b, 0x3e, 0x82, 0xb1 }, 47, 95 ), 5992 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x23, 0xd3, 0x2f, 0x81, 0xdf, 0xee, 0x06, 0xca, 0x70, 0x11, 0x59, 0xe0, 0x5b, 0xd9, 0x11, 0x5e, 0x21 }, 87, 101 ), 1260 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xa8, 0x70, 0x7e, 0xe7, 0x0e, 0xc5, 0xd6, 0xd4, 0xc3, 0x01, 0x4f, 0x01, 0x84, 0x01, 0x24, 0x57, 0x30, 0xa5 }, 55, 130 ), 8277 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x37, 0x1e, 0xac, 0x01, 0x8f, 0xbd, 0x5a, 0x70, 0x18, 0x34, 0x82, 0x77, 0x55, 0x2a, 0xe7, 0xd3, 0x12, 0xf6, 0x99 }, 41, 140 ), 14161 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xe8, 0xca, 0x5c, 0xea, 0x1a, 0x5d, 0x6e, 0x1b, 0x82, 0xc5, 0x4b, 0x28, 0xfd, 0x6a, 0xd4, 0xfe, 0xfa, 0x91, 0x59, 0x6a }, 67, 111 ), 6494 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xaa, 0x8d, 0xec, 0x21, 0xe3, 0x17, 0x09, 0xb7, 0x29, 0xff, 0x50, 0x12, 0xc9, 0xac, 0xfc, 0xe3, 0x0a, 0x6b, 0xff, 0x8d, 0x31, 0x4a, 0xb5, 0x2e, 0xb5 }, 29, 127 ), 30444 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x8a, 0x2c, 0xaf, 0x1b, 0x85, 0x1a, 0xc6, 0x13, 0x06, 0xe8, 0xf6, 0x1d, 0xf1, 0xae, 0x47, 0xf0, 0xfe, 0x5a, 0xb9, 0xab, 0x57, 0x9d, 0xb6, 0xc2, 0x9d, 0x43, 0xf3, 0xe8, 0xf8, 0x22 }, 33, 200 ), 50188 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x9d, 0x82, 0x4e, 0x4d, 0x9e, 0xd4, 0x67, 0x64, 0xe7, 0x6e, 0x4c, 0xde, 0x8c, 0x3d, 0x8c, 0xd3, 0x2e, 0x8a, 0x2e, 0xe8, 0x36, 0x85, 0x85, 0xec, 0x48, 0x23, 0x2f, 0x3b, 0x0b, 0x28, 0x5e, 0xa8, 0xab, 0xac, 0xf6 }, 100, 210 ), 28425 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x4a, 0x80, 0x5d, 0xae, 0x68, 0xcc, 0xfb, 0x46, 0x58, 0x39, 0xd2, 0x2c, 0x67, 0x5d, 0x5a, 0x4f, 0x94, 0xdf, 0xd5, 0x81, 0x27, 0xf8, 0xb1, 0x63, 0x04, 0xd9, 0xc1, 0xac, 0x85, 0x6e, 0xa2, 0xcf, 0xef, 0x00, 0x7e, 0x57, 0xcd, 0x79, 0x9e, 0x25 }, 45, 300 ), 91049 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xb3, 0x71, 0x51, 0x1b, 0xcf, 0xab, 0x6b, 0x63, 0x8b, 0x41, 0xe4, 0xb2, 0x3a, 0x95, 0x16, 0x3e, 0x6f, 0xd8, 0xea, 0xf4, 0x46, 0x8d, 0xc3, 0x36, 0x8e, 0x42, 0x8d, 0x5b, 0xbb, 0x2c, 0x81, 0x6f, 0x9d, 0xd2, 0x8a, 0x6c, 0x7e, 0xf5, 0xd0, 0x09, 0x37, 0xb4, 0xbc, 0x71, 0x4a }, 176, 218 ), 14019 );
      // m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xd3, 0xaf, 0xb9, 0xab, 0x9a, 0xae, 0xf2, 0x28, 0x72, 0x28, 0xb7, 0xb4, 0xb6, 0x13, 0x70, 0xe2, 0x94, 0xdf, 0x80, 0x67, 0x6a, 0xed, 0xe5, 0x60, 0xbd, 0xef, 0x97, 0x72, 0xac, 0x08, 0xbd, 0x7f, 0xb8, 0x76, 0x2b, 0x53, 0x25, 0x1d, 0x7b, 0x97, 0x46, 0x32, 0x4c, 0xfc, 0x45, 0xbc, 0xdf, 0xda, 0x9c, 0x60 }, 245, 365 ), 22990 );
    }
};
//=================================================================================================
void               TestParallel                            ( void )
{
  CRig   s;
  
  s . AddCustomer ( make_shared<CCustomerTest> () );
  s . Start ( 2 );
  s . AddCustomer ( make_shared<CCustomerTest> () );
  s . Stop ();
}
//=================================================================================================
void               TestSequential                          ( void )
{
  CCustomerTest c;
  
  for ( AFITCoin x = c . FITCoinGen (); x ; x = c . FITCoinGen () )
  {
    CRig::Solve ( x );
    c . FITCoinAccept ( x );
  }

  for ( ACVUTCoin x = c . CVUTCoinGen (); x ; x = c . CVUTCoinGen () )
  {
    CRig::Solve ( x );
    c . CVUTCoinAccept ( x );
  }
}
//=================================================================================================
int                main                                    ( void )
{
  TestSequential ();
  TestParallel ();
  return 0;
}
#endif /* __PROGTEST__ */
