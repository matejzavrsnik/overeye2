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
type to_type(String type_string)
{
   if(type_string == L"webport") return type::webport;
   if(type_string == L"twitter") return type::twitter;
   if(type_string == L"clock") return type::clock;
   throw mzlib::exception::parse_error("not a known gauge type");
}

}
