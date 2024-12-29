#pragma once
#include <instrumentation/InstrumentationExport.h>

#include <sstream>
#include <exception>
#include <string>

#ifdef SWIG
%typemap(csbase) Instrumentation::SystemException "System.Exception"
%exception{
  try {
    $action
  }
  catch (ApplicationException& e) {
    SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.what());
  }
  catch (ArgumentException& e) {
    SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentException, e.what(), e.which());
  }
  catch (std::exception& e) {
    SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.what());
  }
  catch (...) {
    SWIG_CSharpSetPendingException(SWIG_CSharpSystemException, "Unexpected C++ exception thrown.");
  }
}
#endif

#pragma warning(push)
#pragma warning(disable: 4275) //non dll-interface class used as base for dll-interface class

#ifndef SWIG
namespace Instrumentation
{
  class INSTRUMENTATION_API SystemException
#ifndef SWIG
    : public std::exception
#endif
  {
public:
    virtual ~SystemException() {};

#ifndef SWIG
    using std::exception::exception;
#endif

  protected:
    explicit SystemException(const std::string& msg);
  };

  class UnknownException : public SystemException
  {
  public:
    explicit UnknownException(const std::string& msg) : SystemException(msg) {};
    virtual ~UnknownException() {};
  };

  class ApplicationException : public SystemException
  {
  public:
    explicit ApplicationException(const std::string& msg) : SystemException(msg) {};
    virtual ~ApplicationException() {};
  };

  class ArgumentException : public SystemException
  {
  public:
    ArgumentException(const std::string& arg, const std::string& msg) : SystemException(msg), m_ArgumentName(arg) {};
    virtual ~ArgumentException() {};

    const char* which() const { return m_ArgumentName.c_str(); };
  private:
    std::string m_ArgumentName;
  };
}
#endif
#pragma warning(pop)
