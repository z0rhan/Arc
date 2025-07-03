#include <core/logger.h>
#include <core/asserts.h>

int main()
{
    ARC_FATAL("A test message: {}", "Testing");
    ARC_ERROR("A test message: {} {}", "Testing", 1);
    ARC_WARN("A test message: {}", "Testing");
    ARC_INFO("A test message: {}", "Testing");

    ARC_ASSERT_MSG(1 == 0, "1 is not equal to 0");
    return 0;
}
