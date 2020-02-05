
#ifndef __TESTASS__ASSERT_H__
#define __TESTASS__ASSERT_H__


#include <string>
#include <cmath>

#include "testass_control.h"


namespace testass
{

  template < typename T1 >
  void assert( T1, std::string );

  template < typename T1, typename T2 >
  void assert_equal( T1, T2, std::string, std::string );

  template < typename T1, typename T2 >
  void assert_approx_equal( T1, T2, std::string, std::string, double = TESTASS_APPROX_LIMIT );

  template < typename T1, typename T2 >
  void assert_not_equal( T1, T2, std::string, std::string );

  template < typename T1 >
  void assert_true( T1, std::string );

  template < typename T1 >
  void assert_false( T1, std::string );


////////////////////////////////////////////////////////////////////////////////
// Defintions
////////////////////////////////////////////////////////////////////////////////

  
  template < typename T1 >
  void assert( T1 a, std::string aName )
  {
    std::stringstream ss( "" );
    ss << a;
    testass::control::assertion( (bool)a, aName, ss.str() );
  }

  template < typename T1, typename T2 >
  void assert_equal( T1 a, T2 b, std::string aName, std::string bName )
  {
    std::stringstream ss( "" );
    ss << a << " == " << b;
    testass::control::assertion( ( a == b ), ( aName + " equal to " + bName ), ss.str() );
  }

  template < typename T1, typename T2 >
  void assert_approx_equal( T1 a, T2 b, std::string aName, std::string bName, double limit )
  {
    std::stringstream ss( "" );
    ss << a << " approx " << b;
    testass::control::assertion( ( ( std::fabs( a - b )  ) < limit ), ( aName + " approximately equal to " + bName ), ss.str() );
  }

  template < typename T1, typename T2 >
  void assert_not_equal( T1 a, T2 b, std::string aName, std::string bName )
  {
    std::stringstream ss( "" );
    ss << a << " != " << b;
    testass::control::assertion( ( a != b ), ( aName + " not equal to " + bName ), ss.str() );
  }

  template < typename T1 >
  void assert_true( T1 a, std::string aName )
  {
    std::stringstream ss( "" );
    ss << a;
    testass::control::assertion( a == true, ( aName + " is true" ), ss.str() );
  }

  template < typename T1 >
  void assert_false( T1 a, std::string aName )
  {
    std::stringstream ss( "" );
    ss << a;
    testass::control::assertion( ( a == false ), ( aName + " is false" ), ss.str() );
  }

  template < typename T1, typename T2 >
  void assert_greaterthan( T1 a, T2 b, std::string aName, std::string bName )
  {
    std::stringstream ss( "" );
    ss << a << " > " << b;
    testass::control::assertion( ( a > b ), ( aName + " greater than " + bName ), ss.str() );
  }

  template < typename T1, typename T2 >
  void assert_lessthan( T1 a, T2 b, std::string aName, std::string bName )
  {
    std::stringstream ss( "" );
    ss << a << " < " << b;
    testass::control::assertion( ( a < b ), ( aName + " less than " + bName ), ss.str() );
  }

  template < typename T1 >
  void assert_positive( T1 a, std::string aName )
  {
    std::stringstream ss( "" );
    ss << a;
    testass::control::assertion( ( (int)a ) >= 0, ( aName + " is positive" ), ss.str() );
  }

  template < typename T1 >
  void assert_negative( T1 a, std::string aName )
  {
    std::stringstream ss( "" );
    ss << a;
    testass::control::assertion( ( (int)a ) < 0, ( aName + " is negative" ), ss.str() );
  }
}

#endif // __TESTASS__ASSERT_H__

