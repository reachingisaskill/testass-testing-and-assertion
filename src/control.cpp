
#include "testass_control.h"

#include <sstream>
#include <cstdlib>

namespace testass
{

  control::control() :
    singleton< control >(),
    _name( "" ),
    _description( "" ),
    _allTests(),
    _output( &std::cout ),
    _sectionNum( 0 ),
    _testCount( 0 ),
    _successCount( 0 ),
    _failureCount( 0 ),
    _success( '*' ),
    _failure( '!' ),
    _verbosity( control::verb_short )
  {
    _allTests.push_back( std::make_pair( "Initial Tests", sectionListT() ) );
  }

  void control::init( std::string name, std::string desc )
  {
    control* inst = control::getInstance();
    if ( ! inst ) inst = control::createInstance();

    inst->_name = name;
    inst->_description = desc;

    std::ostream& out = *inst->_output;

    out << "\nCommencing Tests of " << name << "\n" << desc << "\n" << inst->_indent( 2 ) << std::flush;
  }

  void control::setSuccessChar( char s )
  {
    _success = s;
  }

  void control::setFailureChar( char f )
  {
    _failure = f;
  }

  void control::setInitialSectionName( std::string name )
  {
    _allTests.front().first = name;
  }

  void control::setVerbosity( verbosityT v )
  {
    _verbosity = v;
  }

  void control::setOutput( std::ostream& out )
  {
    _output = &out;
  }

////////////////////////////////////////////////////////////////////////////////

  bool control::summarize()
  {
    control* inst = control::getInstance();
    if ( inst )
    {
      ++inst->_sectionNum;

      inst->_event( event_completion );

      if ( inst->_failureCount > 0 ) return false;
    }
    return true;
  }

  void control::start_section( std::string name )
  {
    control* inst = control::getInstance();
    if ( inst )
    {
      ++inst->_sectionNum;

      inst->_allTests.push_back( std::make_pair( name, sectionListT() ) );

      inst->_event( event_section, name );
    }
    else
    {
      std::cout << "\n    Section :  " << name << "\n" << std::endl;
    }
  }

  void control::assertion( bool result, std::string message, std::string value )
  {
    control* inst = control::getInstance();
    if ( inst )
    {
      inst->_allTests.back().second.push_back( eventT( message, value, result ) );

      ++inst->_testCount;
      if ( result ) 
        ++inst->_successCount;
      else
        ++inst->_failureCount;

      inst->_event( event_assertion, message, result );
    }
    else
    {
      if ( ! result )
      {
        std::cout << "\nAssertion Failed: " << message << std::endl;
        abort();
      }
    }
  }


////////////////////////////////////////////////////////////////////////////////


  void control::_event( eventTypeT type, std::string message, bool result )
  {
    if ( _verbosity == verb_quiet ) return;

    switch( type )
    {
      case event_assertion :
        switch( _verbosity )
        {
          case verb_quiet :
            break;
          case verb_short :
            (*_output) << ( result ? _success : _failure );
            break;

          case verb_detailed :
            (*_output) << "\n" << _indent( 2 ) << ( result ? _success : _failure ) << " ASSERTION : " << message;
            break;
          case verb_abort :
            if ( result )
              (*_output) << _success;
            else
            {
              (*_output) << _failure << "\n";
              (*_output) << "FAILURE : " << message << "\n";
              abort();
            }
            break;

          default :
            (*_output) << _indent( 2 ) << "ERROR - Unknown Verbosity Setting.\n";
        }
        break;

      case event_section :
        (*_output) << std::endl << "\n" << _indent( 1 ) << "Section " << _sectionNum << ". " << message << "\n" << _indent( 2 );
        break;

      case event_completion :
        (*_output) << std::endl << "\nAll Tests Completed. " << _successCount << " Succeeded. " << _failureCount << " Failed.\n";
        break;

      default: 
        (*_output) << "ERROR - Unknown Event Occured.\n";
    }

  }


  void control::printReport( std::ostream& out )
  {
    control* inst = control::getInstance();
    if ( inst )
    {
      std::stringstream sectionBreakdown( "" );

      unsigned int numTests = 0;
      unsigned int numSuccess = 0;
      unsigned int numFailures = 0;
      unsigned int numSections = 1; // Initial Section Dealt With.
      unsigned int numFailedSections = 0;

      listT::iterator allIt = inst->_allTests.begin();

      if ( allIt->second.size() > 0 )
      {
        bool hasFail = false;
        unsigned int numSectionFails = 0;
        unsigned int numSectionSuccess = 0;
        unsigned int numSectionTotal = 0;
        std::stringstream sectionDetails( "" );

        sectionBreakdown << "\nSection 0. " << allIt->first << " : ";

        for ( sectionListT::iterator secIt = allIt->second.begin(); secIt != allIt->second.end(); ++secIt )
        {
          ++numSectionTotal;
          ++numTests;
          if ( secIt->result == false ) 
          {
            hasFail = true;
            ++numSectionFails;
            ++numFailures;
              sectionDetails << "\n    FAILED No. " << numSectionTotal << " : (" << secIt->expression << ") With value(s) : " << secIt->value;
          }
          else
          {
            ++numSuccess;
            ++numSectionSuccess;
          }
        }

        if ( hasFail )
        {
          ++numFailedSections;
          sectionBreakdown << "Failed " << numSectionFails << " Tests of " << numSectionTotal << " : " << sectionDetails.str() << "\n";
        }
        else
        {
          sectionBreakdown << "Succeeded all " << numSectionSuccess << " tests";
        }
        ++numSections;
      }
      ++allIt;

      for ( ; allIt != inst->_allTests.end(); ++allIt )
      {
        bool hasFail = false;
        unsigned int numSectionFails = 0;
        unsigned int numSectionSuccess = 0;
        unsigned int numSectionTotal = 0;
        std::stringstream sectionDetails( "" );

        sectionBreakdown << "\nSection " << numSections << ". " << allIt->first << " : ";

        if ( allIt->second.size() == 0 )
        {
          sectionBreakdown << "No Tests Performed.";
        }
        else
        {
          for ( sectionListT::iterator secIt = allIt->second.begin(); secIt != allIt->second.end(); ++secIt )
          {
            ++numSectionTotal;
            ++numTests;
            if ( secIt->result == false ) 
            {
              hasFail = true;
              ++numSectionFails;
              ++numFailures;
              sectionDetails << "\n    FAILED No. " << numSectionTotal << " : (" << secIt->expression << ") With value(s) : " << secIt->value;
            }
            else
            {
              ++numSuccess;
              ++numSectionSuccess;
            }
          }

          if ( hasFail )
          {
            ++numFailedSections;
            sectionBreakdown << "Failed " << numSectionFails << " Tests of " << numSectionTotal << " : " << sectionDetails.str() << "\n";
          }
          else
          {
            sectionBreakdown << "Succeeded all " << numSectionSuccess << " tests";
          }
        }

        ++numSections;
      }

      out << "\nTestAss Report\n\n";
      out << "Program : " << inst->_name << "\n" << inst->_description << "\n\n\n";
      out << "Global Test Performance : " << ( numTests ? ( ( (double)numSuccess / (double)numTests ) * 100.0  ) : 0.0 )<< "%\n\n\n";
      out << "Stats :\n\n";
      out << "   Number Tests     : " << numTests << "\n";
      out << "   Number Sections  : " << numSections << "\n";
      out << "   Succeeded        : " << numSuccess << "\n";
      out << "   Failed           : " << numFailures << "\n";
      out << "   Failed Sections  : " << numFailedSections << "\n\n\n";
      out << "Section Details:\n" << sectionBreakdown.str() << "\n" << std::endl;
    }
  }


  std::string control::_indent( unsigned int indents )
  {
    std::string str;
    for ( unsigned int i = 0; i < indents; ++i )
    {
      str += "  ";
    }
    return str;
  }

}

