
#ifndef __TESTASS__DEFINITIONS_H__
#define __TESTASS__DEFINITIONS_H__


#ifndef TESTASS_APPROX_LIMIT
#define TESTASS_APPROX_LIMIT 1.0e-9
#endif


////////////////////////////////////////////////////////////////////////////////
 // Assertions
////////////////////////////////////////////////////////////////////////////////

#define ASSERT( term ) testass::assert( term, #term )

#define ASSERT_EQUAL( term1, term2 ) testass::assert_equal( term1, term2, #term1, #term2 )

#define ASSERT_APPROX_EQUAL( term1, term2 ) testass::assert_approx_equal( term1, term2, #term1, #term2 )

#define ASSERT_NOT_EQUAL( term1, term2 ) testass::assert_not_equal( term1, term2, #term1, #term2 )

#define ASSERT_TRUE( term ) testass::assert_true( term, #term )

#define ASSERT_FALSE( term ) testass::assert_false( term, #term )

#define ASSERT_LESSTHAN( term1, term2 ) testass::assert_lessthan( term1, term2, #term1, #term2 )

#define ASSERT_GREATERTHAN( term1, term2 ) testass::assert_greaterthan( term1, term2, #term1, #term2 )

#define ASSERT_POSITIVE( term ) testass::assert_positive( term, #term )

#define ASSERT_NEGATIVE( term ) testass::assert_negative( term, #term )


////////////////////////////////////////////////////////////////////////////////
 // Organisation
////////////////////////////////////////////////////////////////////////////////

#define SECTION( name ) testass::control::start_section( name )


#endif // __TESTASS__DEFINITIONS_H__

