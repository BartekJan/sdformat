/*
 * Copyright 2011 Nate Koenig
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef _SDF_CONSOLE_HH_
#define _SDF_CONSOLE_HH_

#include <iostream>
#include <fstream>
#include <string>

namespace sdf
{
  /// \addtogroup sdf SDF
  /// \{

  /// \brief Output a debug message
  #define sdfdbg (sdf::Console::Instance()->Log("Dbg", \
    __FILE__, __LINE__))

  /// \brief Output a message
  #define sdfmsg (sdf::Console::Instance()->ColorMsg("Msg", \
    __FILE__, __LINE__, 32))

  /// \brief Output a warning message
  #define sdfwarn (sdf::Console::Instance()->ColorMsg("Warning", \
        __FILE__, __LINE__, 33))

  /// \brief Output an error message
  #define sdferr (sdf::Console::Instance()->ColorMsg("Error", \
        __FILE__, __LINE__, 31))

  /// start marker
  #define sdfclr_start(clr) "\033[1;33m"
  /// end marker
  #define sdfclr_end "\033[0m"


  /// \brief Message, error, warning, and logging functionality
  class Console
  {
    /// \brief An ostream-like class that we'll use for logging.
    public: class ConsoleStream
    {
      private:
        /// \brief The ostream to log to; can be NULL.
        std::ostream* stream;

      public:
        /// \brief Constructor
        ConsoleStream(std::ostream* _stream) :
          stream(_stream) {}

        /// \brief Redirect whatever is passed in to both our ostream 
        ///        (if non-NULL) and the log file (if open).
        /// \param[in] rhs Content to be logged
        /// \return Reference to myself.
        template <class T>
        ConsoleStream &operator<<(const T& rhs)
        {
          if(stream)
            *stream << rhs;
          if(Console::Instance()->logFileStream.is_open())
            Console::Instance()->logFileStream << rhs;
          return *this;
        }
    };
  
    /// \brief Default constructor
    private: Console();

    /// \brief Destructor
    private: virtual ~Console();

    /// \brief Return an instance to this class
    public: static Console *Instance();

    /// \brief Set quiet output
    /// \param[in] q True to prevent warning
    public: void SetQuiet(bool _q);

    /// \brief Use this to output a colored message to the terminal
    /// \param[in] _lbl Text label
    /// \param[in] _file File containing the error
    /// \param[in] _line Line containing the error
    /// \param[in] _color Color to make the label
    /// \return Reference to an output stream
    public: ConsoleStream &ColorMsg(const std::string &lbl, 
                                    const std::string &file,
                                    unsigned int line, int color);

    /// \brief Use this to output a message to a log file
    /// \return Reference to output stream
    public: ConsoleStream &Log(const std::string &lbl,
                               const std::string &file,
                               unsigned int line);

    /// \brief message stream
    private: ConsoleStream msgStream;

    /// \brief error stream
    private: ConsoleStream errStream;

    /// \brief log stream
    private: ConsoleStream logStream;

    /// \brief logfile stream
    private: std::ofstream logFileStream;

    /// \brief Pointer to myself
    private: static Console *myself;
  };
  /// \}
}
#endif
