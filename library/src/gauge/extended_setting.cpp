#include "extended_setting.h"

gauge::extended_setting::extended_setting (
   std::string tag,
   std::string value,
   bool user_setting,
   std::string friendly_name
) :
   m_basic_setting{std::move(tag),std::move(value)},
   m_user_setting{user_setting},
   m_name{std::move(friendly_name)} {}

const std::string&
gauge::extended_setting::get_value () const
{
   return m_basic_setting.value;
}

void
gauge::extended_setting::set_value (const std::string& v)
{
   m_basic_setting.value = v;
}

bool
gauge::extended_setting::is_user_setting () const
{
   return m_user_setting;
}

void
gauge::extended_setting::set_user_setting (bool v)
{
   m_user_setting = v;
}

const std::string&
gauge::extended_setting::get_name () const
{
   return m_name;
}

void
gauge::extended_setting::set_name (const std::string& name)
{
   m_name = name;
}
