#pragma once

#include <lang/exceptions.h>

namespace gauge
{

enum class type
{
   webport,
   twitter,
   clock
};

template<typename String>
type
to_type(String type_string)
{
   if(type_string == L"webport") return type::webport;
   else if(type_string == L"twitter") return type::twitter;
   else if(type_string == L"clock") return type::clock;

   throw mzlib::exception::parse_error("not a known gauge type");
}

inline
std::wstring
from_type(type type)
{
   if(type == type::webport) return L"webport";
   else if(type == type::twitter) return L"twitter";
   else if(type == type::clock) return L"clock";

   throw mzlib::exception::parse_error("not a known gauge type");
}

}
