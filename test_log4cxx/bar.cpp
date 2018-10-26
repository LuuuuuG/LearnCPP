// file bar.cpp
#include "bar.h"

using namespace com::foo;
using namespace log4cxx;

LoggerPtr Bar::logger(Logger::getLogger("IN_bar"));


void Bar::doIt() {
	//LOG4CXX_INFO(logger, "Did it again!");
}