#pragma once

#include <QEvent>

namespace custom_qevent_type
{

auto refresh_content = static_cast<QEvent::Type>(QEvent::User + 1);

}
