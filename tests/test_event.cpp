#include "event/event.h"
#include "event/event_dispatcher.h"
#include "event/event_key.h"

#include <gtest/gtest.h>

TEST(EventSystemTest, BasicEventSubscriptionAndDispatch)
{
    // Clear any existing listeners to ensure test isolation
    EventDispatcher::clearListeners<KeyPressedEvent>();
    
    bool eventReceived = false;
    KeyCode keyReceived = KeyCode::Space;

    EventDispatcher::subscribe<KeyPressedEvent>(
        [&](const KeyPressedEvent &e)
        {
            eventReceived = true;
            keyReceived = e.getKeyCode();
        });

    KeyPressedEvent testEvent(KeyCode::Space, 0);
    EventDispatcher::dispatch(testEvent);

    EXPECT_EQ(keyReceived, KeyCode::Space);
    EXPECT_TRUE(eventReceived);
}

