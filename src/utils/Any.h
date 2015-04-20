/**
 * @file   Any.h
 * @author Christopher Maier
 * @date   January 2015
 *
 * This file was provided by Karlheinz Wohlmuth (khwhth@gmail.com). The purpose of
 * this container class is that it can hold objects of arbitrary types. This is needed
 * in the visitor implementation to be able to return arbitrary objects in the visit method
 * without using void* as return type.
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
*/


#ifndef ANY_H_
#define ANY_H_

//TODO: Remove this for final version
#define ANY_DEBUG

#include <memory>
#include <utility>
#include <typeinfo>
#include <type_traits>
#include <stdexcept>
#ifdef ANY_DEBUG
#include <execinfo.h> // glibc extension
#include <cxxabi.h>   // GCC extension
#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include <algorithm>
#ifdef __APPLE__
#include <sstream>
#include <iterator>
#endif
#endif

namespace yagi {
namespace container {
#ifdef ANY_DEBUG

/**
 * Exception class for the Any container.
 */
class AnyException: public std::runtime_error
{
  public:
    AnyException(const std::string &msg, std::vector<std::string> st = { }) :
        runtime_error { msg }, stackTrace_ { std::move(st) }
    {
    }
    std::vector<std::string> getStackTrace() const
    {
      return stackTrace_;
    }
    void printStackTrace(std::ostream &os = std::cout) const
    {
      std::for_each(std::begin(stackTrace_), std::end(stackTrace_), [&os](const std::string &s)
      { os << s << std::endl;});
    }

  private:
    std::vector<std::string> stackTrace_;
};
#else
using AnyException = std::runtime_error;
#endif

/**
 * Container class for objects of arbitrary type.
 * This container was provided by Karlheinz Wohlmuth (khwhth@gmail.com).
 */
class Any
{
  private:
    template<typename Base, typename T>
    using remove_if_derived_or_equal = typename std::enable_if<!std::is_base_of<Base, typename std::remove_reference<T>::type>::value>::type;

    struct HolderBase
    {
        virtual ~HolderBase()
        {
        }
        virtual const std::type_info& getType() const noexcept = 0;
    };

    template<typename T>
    struct Holder final : HolderBase
    {
        template<typename H, typename = remove_if_derived_or_equal<Holder, H>>
        explicit Holder(H &&h) :
            t_ { std::forward<H>(h) }
        {
        }

        const std::type_info& getType() const noexcept override
        {
          return typeid(t_);
            }
            T t_;
        };

      public:
        Any() = default;
        Any(const Any &) = default;
        Any(Any &&other) noexcept: haveValue_
        { std::move(other.haveValue_)}, holder_
        { std::move(other.holder_)}
        { other.haveValue_ = false;}
        template<typename T, typename = remove_if_derived_or_equal<Any, T>>
        explicit Any(T &&t): haveValue_
        { true}, holder_
        { std::make_shared<Holder<typename std::remove_reference<T>::type>>(std::forward<T>(t))}
        {}
        virtual ~Any() = default;

        explicit operator bool() const noexcept
        { return !empty();}
        Any& operator=(const Any &) = default;
        Any& operator=(Any &&other) noexcept
        { haveValue_ = std::move(other.haveValue_); holder_ = std::move(other.holder_); other.haveValue_ = false; return *this;}

        friend bool operator==(const Any &a, const Any &b) noexcept
        { return a.haveValue_ == b.haveValue_ && a.holder_ == b.holder_;}
        friend bool operator!=(const Any &a, const Any &b) noexcept
        { return a.haveValue_ != b.haveValue_ || a.holder_ != b.holder_;}

        template<typename T>
        Any clone() const
        { return empty() ? Any
          {}: Any
          { T
            { get<T>()}};}
        template<typename T>
        bool hasType() const noexcept
        { return haveValue_ ? holder_->getType() == typeid(T) : false;}
        template<typename T>
        T& get()
        { check<T>(); return static_cast<Holder<T>*>(holder_.get())->t_;}
        template<typename T>
        const T& get() const
        { check<T>(); return static_cast<Holder<T>*>(holder_.get())->t_;}
        template<typename T>
        T tryGetCopy(T t = T
            {}) const
        { if (empty()) return std::move(t); return get<T>();}
        template<typename T>
        void set(T &&t)
        { holder_.reset(); holder_ = std::make_shared<Holder<typename std::remove_reference<T>::type>>(std::forward<T>(t));}
        bool empty() const noexcept
        { return !haveValue_;}
        void reset() noexcept
        { haveValue_= false; holder_.reset();}

        private:
        bool haveValue_ = false;
        std::shared_ptr<HolderBase> holder_;

        template<typename T>
        void check() const
        {
#ifdef ANY_DEBUG
          constexpr int BackTraceSize = 300;
          std::vector<std::string> backTraceLines;
          void *backTraceBuffer[BackTraceSize];
          auto backTraceDepth = backtrace(backTraceBuffer, BackTraceSize);
          std::unique_ptr<char*, void (*)(void*)> backTraceSymbols
          { backtrace_symbols(backTraceBuffer, backTraceDepth), std::free};
          if (backTraceSymbols)
          {
            backTraceLines.reserve(backTraceDepth);
            for (int lineIdx = 0; lineIdx < backTraceDepth; ++lineIdx)
            {
#ifdef __APPLE__
              std::istringstream ssLine(backTraceSymbols.get()[lineIdx]);
              std::istream_iterator<std::string> lineTokenIterator
              { ssLine};
              std::string recombinedLine, backTraceLine
              { backTraceSymbols.get()[lineIdx]};
              for (int lineTokenIdx = 0; lineTokenIterator != std::istream_iterator<std::string>
                  {}; ++lineTokenIterator, ++lineTokenIdx)
              if (lineTokenIdx == 3)
              {
                int status;
                const std::string functionName = *lineTokenIterator;
                std::unique_ptr<char, void(*)(void*)> demangledName
                { abi::__cxa_demangle(functionName.c_str(), nullptr, 0, &status), std::free};
                recombinedLine += (!status && demangledName ? std::string
                    { demangledName.get()}: functionName) + ' ';
              }
              else
              recombinedLine += std::string(*lineTokenIterator) + (lineTokenIdx < 3 ? '\t' : ' ');
              backTraceLines.push_back(recombinedLine);
#elif __linux
              std::string rawBacktraceLine
              { backTraceSymbols.get()[lineIdx]};
              auto startPos = rawBacktraceLine.find_first_of('('), endPos = rawBacktraceLine.find_first_of('+');
              if (startPos != std::string::npos && endPos != std::string::npos && endPos > startPos)
              {
                int status;
                const auto functionName = rawBacktraceLine.substr(startPos + 1, endPos - startPos - 1);
                std::unique_ptr<char, void(*)(void*)> demangledName
                { abi::__cxa_demangle(functionName.c_str(), nullptr, 0, &status), std::free};
                if (!status && demangledName)
                {
                  backTraceLines.push_back(rawBacktraceLine.replace(startPos + 1, endPos - startPos - 1, demangledName.get()));
                  continue;
                }
              }
              backTraceLines.emplace_back(backTraceSymbols.get()[lineIdx]);
#else
              backTraceLines.emplace_back(backTraceSymbols.get()[lineIdx]);
#endif
            }
          }
#define MAKE_EXCEPTION(msg) AnyException{msg, backTraceLines}
#else
#define MAKE_EXCEPTION(msg) AnyException{msg}
#endif
          if (empty())
          throw MAKE_EXCEPTION("[any] no value set");
          if (!hasType<T>())
          throw MAKE_EXCEPTION("[any] invalid type");
        }
      };
    }
    }
#endif //ANY_H_
