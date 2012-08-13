//
// uuid.cpp
//
// Implementation.
//

#include <time.h>
#include "uuid.hpp"

namespace uuid {

////////////////////////////////////////////////////////////////////////////////
//
uint64_t Uuid::num_100nsec_1582_1970 = 0x01b21dd213814000;
uint64_t Uuid::last_uuid_time = 0;

////////////////////////////////////////////////////////////////////////////////
// Free functions for generating UUIDs.
//

Uuid uuid1()
{
}

Uuid uuid1(uint64_t node)
{
}

Uuid uuid1(uint64_t node, uint16_t clock_seq)
{
    uint64_t time = 0;

    time = Uuid::gettime();
}

////////////////////////////////////////////////////////////////////////////////
// Constructing a UUID.
//


////////////////////////////////////////////////////////////////////////////////
// Returns number of 100ns intervals since 00:00:00.00 15 October 1582.

uint64_t Uuid::gettime()
{
    int rc = 0;
    struct timespec tp;
    uint64_t uuid_time = 0;

    rc = clock_gettime(CLOCK_REALTIME, &tp);

    // Convert to 100-nanosecond intervals
    uuid_time = tp.tv_sec * 10000000;
    uuid_time = uuid_time + (tp.tv_nsec / 100);
    uuid_time = uuid_time + Uuid::num_100nsec_1582_1970;

    // If the clock looks like it went backwards, or is the same, increment it.
    if (last_uuid_time != 0 && uuid_time <= uuid_time) {
        uuid_time = last_uuid_time + 1;
    }
    last_uuid_time = uuid_time;

    return uuid_time;
}

} // namesapce uuid
