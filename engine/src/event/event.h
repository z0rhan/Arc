#ifndef EVENT_HH
#define EVENT_HH

#include "defines.h"

#include <typeindex>

class Event
{
public:
    virtual ~Event() = default;
    inline bool isHandled() const { return m_handled; }
    inline void setHandled(bool h) { m_handled = h; }

    virtual std::type_index getType() const = 0;

    mutable bool m_handled = false;
};

#endif // EVENT_HH
