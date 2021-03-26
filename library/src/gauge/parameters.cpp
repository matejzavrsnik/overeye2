#include "parameters.h"


gauge::parameter::parameter (
   std::wstring  tag,
   std::wstring  value,
   bool user_setting,
   std::wstring  friendly_name
) :
   m_tag(std::move(tag)),
   m_value(std::move(value)),
   m_user_setting(user_setting),
   m_name(std::move(friendly_name)) {}

const std::wstring&
gauge::parameter::get_tag () const
{
   return m_tag;
}

const std::wstring&
gauge::parameter::get_value () const
{
   return m_value;
}

void
gauge::parameter::set_value (const std::wstring& v)
{
   m_value = v;
}

bool
gauge::parameter::is_user_setting () const
{
   return m_user_setting;
}

void
gauge::parameter::set_user_setting (bool v)
{
   m_user_setting = v;
}

const std::wstring&
gauge::parameter::get_name () const
{
   return m_name;
}

void
gauge::parameter::set_name (const std::wstring& name)
{
   m_name = name;
}
