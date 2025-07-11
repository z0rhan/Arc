#ifndef EVENT_DISPATCHER_HH
#define EVENT_DISPATCHER_HH

#include "defines.h"
#include "event.h"

#include <functional>
#include <vector>

class EventDispatcher
{
public:
    template<typename EventType>
    using EventHandler = std::function<void(const EventType&)>;

    // Subscribe to events
    template<typename EventType>
    static void subscribe(EventHandler<EventType> listener)
    {
        static_assert(std::is_base_of_v<Event, EventType>, "T must be derive from Event");

        getListeners<EventType>().emplace_back(std::move(listener));
    }

    // Dispatch events
    template<typename EventType>
    static void dispatch(const EventType& event)
    {
        static_assert(std::is_base_of_v<Event, EventType>, "T must derive from Event");

        auto& listeners = getListeners<EventType>();
        for (auto& listener : listeners)
        {
            listener(event);
            if (event.isHandled()) break;
        }
    }

    // Clear all listeners of a specific type (useful for testing)
    template<typename EventType>
    static void clearListeners()
    {
        static_assert(std::is_base_of_v<Event, EventType>, "T must derive from Event");
        getListeners<EventType>().clear();
    }

    // Clear all listeners (useful for testing)
    static void clearAllListeners()
    {
        // To be implemented
    }

private:
    template<typename EventType>
    static std::vector<EventHandler<EventType>>& getListeners()
    {
        static std::vector<EventHandler<EventType>> listeners;
        return listeners;
    }

};

#endif // EVENEventType_MANAGER_HH
