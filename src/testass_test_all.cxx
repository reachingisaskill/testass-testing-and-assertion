
#include "testass.h"

#include <fstream>
#include <iostream>


int main( int, char** )
{
  testass::control::init( "TestAss Testing", "Testing the Testing and Assertion Library. Good eh?" );
  // testass::control::get()->setVerbosity( testass::control::verb_short );
  testass::control::get()->setVerbosity( testass::control::verb_detailed );
  testass::control::get()->setInitialSectionName( "Initial Assertion Tests" );


  ASSERT_TRUE( true );
  ASSERT_TRUE( true );
  ASSERT_TRUE( false );
  ASSERT_TRUE( true );
  ASSERT_APPROX_EQUAL( -1.0000000000000001, -1.0 );


  SECTION( "Assertion Tests 1" );

  ASSERT_TRUE( true );
  ASSERT_TRUE( true );
  ASSERT_TRUE( true );
  ASSERT_TRUE( true );
  ASSERT_GREATERTHAN( 10, 2 );
  ASSERT_LESSTHAN( 10, 2 );
  ASSERT_POSITIVE( -234326.3423 );
  ASSERT_NEGATIVE( -234326.3423 );

  SECTION( "Empty Section" );

  SECTION( "Assertion Tests 2" );

  ASSERT_FALSE( false );
  ASSERT_EQUAL( 27, 27 );
  ASSERT_NOT_EQUAL( 1, 4 );
  ASSERT_APPROX_EQUAL( 43.456, 43.456 );

  SECTION( "Assertion Tests 3" );

  ASSERT_FALSE( false );
  ASSERT_EQUAL( 27, 27 );
  ASSERT_NOT_EQUAL( 1, 4 );
  ASSERT_EQUAL( 543, 10 );
  ASSERT_APPROX_EQUAL( 43.456, 43.456 );

  SECTION( "Assertion Tests 4" );

  ASSERT_FALSE( false );
  ASSERT_EQUAL( 27, 27 );
  ASSERT_NOT_EQUAL( 1, 4 );
  ASSERT_APPROX_EQUAL( 43.456, 43.456 );

  SECTION( "Assertion Tests 5" );
  int* test_p = nullptr;
  ASSERT_NULL( test_p );
  ASSERT_NOT_NULL( test_p );
  test_p = new int( 10 );
  ASSERT_NULL( test_p );
  ASSERT_NOT_NULL( test_p );
  delete test_p;

  if ( ! testass::control::summarize() )
  {
    std::cout << "Failures Found. Printing Report:\n\n";
  }
  else
  {
    std::cout << "No Failures Found. Printing Report:\n\n";
  }

  std::ofstream report( "test_report.txt" );

  testass::control::printReport( report );

  testass::control::kill();

  std::cout << "Tests Complete.\n";
  std::cout << std::endl;
  return 0;
}

