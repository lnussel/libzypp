#include "TestSetup.h"
#include <zypp/ExternalProgram.h>

#include <chrono>
#include <thread>
#include <sys/types.h>
#include <sys/wait.h>

#define BOOST_TEST_MODULE CleanerThread

using zypp::ExternalProgram;

BOOST_AUTO_TEST_CASE( CleanerThread_default )
{
  pid_t pid = -1;
  {
    ExternalProgram proc( "bash -c 'sleep 2'", ExternalProgram::Normal_Stderr );
    BOOST_CHECK( proc.running() );
    pid = proc.getpid();
  }
  std::this_thread::sleep_for( std::chrono::seconds(4) );
  int status = 0;
  int res = waitpid( pid, &status, WNOHANG );
  BOOST_CHECK_EQUAL( res, -1 );
  BOOST_CHECK_EQUAL( errno, ECHILD );
}
