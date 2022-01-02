#include "extended_setting.h"

gauge::extended_setting::extended_setting (
   std::string value
) :
   m_value{std::move(value)} {}

const std::string&
gauge::extended_setting::get_value () const
{
   return m_value;
}

void
gauge::extended_setting::set_value (const std::string& v)
{
   m_value = v;
}
