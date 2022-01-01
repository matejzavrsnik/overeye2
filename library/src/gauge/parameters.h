#pragma once

#include "basic_setting.h"
#include "extended_setting.h"
#include "i_user_parameters.h"
#include "i_gauge_parameters.h"

#include <string>
#include <vector>
#include <optional>
#include <map>

namespace gauge
{

/**
 * @brief A collection of gauges parameters.
 *
 * @details The class implements two interfaces to serve two audiences. When gauges use it, they need access
 * to all parameters and everything about them, even changing some from user-controlled parameter to internal
 * one, as in the case of twitter gauge taking over the "content" parameter away from the user. However, when
 * the gauge hands out access to it's parameters to a dialog through which user will be setting them, that
 * level of access would be inappropriate. To list and allow edit of user-controlled parameters only, that
 * dialog needs access to user-controlled parameters only.
 *
 * One alternative solution would be that gauges sent a copy of parameters and configuration dialog sent a copy
 * of the changes back. This was attempted but it resulted in additional complications due to complete decoupling
 * of logical gauges from the visuals. Logical gauge does not know when visual gauge gets a click on configuration
 * button. Visual gauge would first need to request user parameters through sigslot system, which is the only means
 * of communication, then wait for logical gauge to respond with parameters and then send them back when they are
 * changed. I felt that's too convoluted.
 *
 * Another alternative solution would be that gauges keep two separate collections of parameters, one for users
 * and one for internal use. Gauge could then share just the users' collection of parameters with the configuration
 * dialog and keep reading both collections when rendering. This wasn't attempted.
 */
class parameters : public i_gauge_parameters, public i_user_parameters
{

public:

   parameters () = default;

private:

   std::map<std::string, extended_setting> m_settings;

   std::map<std::string, extended_setting>::iterator
   find (const std::string& tag);

   extended_setting&
   find_or_add (const std::string& tag);

   void
   set_or_add_user_setting (
      const std::string& tag,
      const std::string& value,
      const std::string& name
   ) override;

   void
   set_or_add_internal_setting(
      const std::string& tag,
      const std::string& value
   ) override;

   bool
   set(
      const std::string& tag,
      const std::string& value
   ) override;

   // sets tag value if exists and is available as user basic_setting
   bool
   user_setting_set (
      const basic_setting& setting
   ) override;

   std::optional<std::string>
   get_value(const std::string &tag) override;

   std::optional<std::string>
   user_setting_get_name (
      const std::string& tag
   ) override;

   std::vector<basic_setting>
   user_setting_get_all() override;

};

}
