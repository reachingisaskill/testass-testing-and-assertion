
#ifndef TESTASS_CONTROL_H_
#define TESTASS_CONTROL_H_


#include "testass_singleton.h"

#include <iostream>
#include <list>
#include <utility>


namespace testass
{

  class control : protected singleton< control >
  {
    friend class singleton< control >;

    struct eventT 
    {
      std::string expression;
      std::string value;
      bool result;
      eventT() : expression( "" ), value( "" ), result( true ) {}
      eventT( std::string exp, std::string val, bool res ) : expression( exp ), value( val ), result( res ) {}
    };

    //typedef std::pair< std::string, bool > eventT;
    typedef std::list< eventT > sectionListT;
    typedef std::pair< std::string, sectionListT > sectionT;
    typedef std::list< sectionT > listT;

    enum eventTypeT { event_assertion, event_section, event_completion };

    public:
      enum verbosityT { verb_quiet, verb_short, verb_detailed, verb_abort };

    private:
      control();

      std::string _name;
      std::string _description;

      listT _allTests;

      std::ostream* _output;

      unsigned int _sectionNum;
      unsigned int _testCount;
      unsigned int _successCount;
      unsigned int _failureCount;

      char _success;
      char _failure;

      verbosityT _verbosity;

      std::string _indent( unsigned int );
      void _event( eventTypeT, std::string = "", bool = true );

    public:

      static void init( std::string, std::string );

      static control* get() { return control::getInstance(); }
      static void kill() { control::killInstance(); }

      void setSuccessChar( char );
      void setFailureChar( char );

      void setInitialSectionName( std::string );

      void setVerbosity( verbosityT );
      void setOutput( std::ostream& );

      static bool summarize(); // True if all passed.
      static void printReport( std::ostream& );


      static void start_section( std::string );
      static void assertion( bool, std::string, std::string );
  };

}

#endif // TESTASS_CONTROL_H_

