
#ifndef TESTASS_DEFINITIONS_H_
#define TESTASS_DEFINITIONS_H_


#ifndef TESTASS_APPROX_LIMIT
#define TESTASS_APPROX_LIMIT 1.0e-9
#endif


////////////////////////////////////////////////////////////////////////////////
 // Assertions
////////////////////////////////////////////////////////////////////////////////

#define ASSERT( term ) testass::testass_assert( term, #term )

#define ASSERT_EQUAL( term1, term2 ) testass::testass_assert_equal( term1, term2, #term1, #term2 )

#define ASSERT_APPROX_EQUAL( term1, term2 ) testass::testass_assert_approx_equal( term1, term2, #term1, #term2 )

#define ASSERT_NOT_EQUAL( term1, term2 ) testass::testass_assert_not_equal( term1, term2, #term1, #term2 )

#define ASSERT_TRUE( term ) testass::testass_assert_true( term, #term )

#define ASSERT_FALSE( term ) testass::testass_assert_false( term, #term )

#define ASSERT_LESSTHAN( term1, term2 ) testass::testass_assert_lessthan( term1, term2, #term1, #term2 )

#define ASSERT_GREATERTHAN( term1, term2 ) testass::testass_assert_greaterthan( term1, term2, #term1, #term2 )

#define ASSERT_POSITIVE( term ) testass::testass_assert_positive( term, #term )

#define ASSERT_NEGATIVE( term ) testass::testass_assert_negative( term, #term )

#define ASSERT_NULL( term ) testass::testass_assert_null( term, true, #term )

#define ASSERT_NOT_NULL( term ) testass::testass_assert_null( term, false, #term )

////////////////////////////////////////////////////////////////////////////////
 // Organisation
////////////////////////////////////////////////////////////////////////////////

#define SECTION( name ) testass::control::start_section( name )


#endif // TESTASS_DEFINITIONS_H_

