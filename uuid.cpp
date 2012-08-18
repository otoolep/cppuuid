//
// uuid.cpp
//
// Implementation.
//

#include <string>
#include <stdio.h>
#include <time.h>
#include "uuid.hpp"

namespace uuid {

////////////////////////////////////////////////////////////////////////////////
// Constants
//

// Number of 100-ns intervals between the UUID epoch 1582-10-15 00:00:00 and
// the Unix epoch 1970-01-01 00:00:00. Ref: uuid.py
static const uint64_t kNum_100nsec_1582_1970 = 0x01b21dd213814000;
static const uint64_t kMax_node = 0xffffffffffff; // 48-bits, all 1s.
static const uint16_t kMax_clock_seq = 0x3fff; // 14-bits, all 1s.

////////////////////////////////////////////////////////////////////////////////
// Convenience functions.

// Returns number of 100ns intervals since 00:00:00.00 15 October 1582.
static uint64_t gettime()
{
    static uint64_t last_uuid_time = 0; // On the heap!
    int rc = 0;
    struct timespec tp;
    uint64_t uuid_time = 0;

    rc = clock_gettime(CLOCK_REALTIME, &tp);

    // Convert to 100-nanosecond intervals
    uuid_time = tp.tv_sec * 10000000;
    uuid_time = uuid_time + (tp.tv_nsec / 100);
    uuid_time = uuid_time + kNum_100nsec_1582_1970;

    // If the clock looks like it went backwards, or is the same, increment it.
    if (last_uuid_time <= uuid_time) {
        uuid_time = last_uuid_time + 1;
    }
    last_uuid_time = uuid_time;

    return uuid_time;
}

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
    // Validate node and clock_seq.

    if (node > kMax_node) {
        throw NodeOutOfRangeException();
    }

    if (clock_seq > kMax_clock_seq) {
        throw ClockSeqOutOfRangeException();
    }

    // Number of 100-ns intervals?
    uint64_t ns100_intervals = gettime();

    uint32_t time_low = ns100_intervals & 0xffffffff;
    uint16_t time_mid = (ns100_intervals >> 32) & 0xffff;
    uint16_t time_hi_version = (ns100_intervals >> 48) & 0xfff;
    uint8_t clock_seq_low = clock_seq & 0xff;
    uint8_t clock_seq_hi_variant = (clock_seq >> 8) & 0x3f;

    return Uuid(time_low, time_mid, time_hi_version, clock_seq_low,
                    clock_seq_hi_variant, node);
}

////////////////////////////////////////////////////////////////////////////////
// Constructing a UUID.
//

Uuid::Uuid(uint32_t time_low, uint16_t time_mid, uint16_t time_hi_version,
           uint8_t clock_seq_low, uint8_t clock_seq_hi_variant, uint64_t node)
{
    upper_ = 0;
    lower_ = 0;

    // Build the high 4 bytes.
    upper_ = (uint64_t) time_low << 32;
    upper_ |= (uint64_t) time_mid << 16;
    upper_ |= (uint64_t) time_hi_version;

    // Build the low 4 bytes, using the clock sequence number.
    uint16_t clock_seq = 0;
    clock_seq = clock_seq_hi_variant << 8;
    clock_seq |= clock_seq_low;

    lower_ = (uint64_t) clock_seq << 48;
    lower_ |= node;

    // Set the variant to RFC 4122.
    lower_ &= ~((uint64_t)0xc000 << 48);
    lower_ |= (uint64_t)0x8000 << 48;

    // Set the version number.
    upper_ &= ~0xf000;
    upper_ |= Uuid::version_ << 12;
}

std::string Uuid::hex()
{
    // 2 bytes per character in upper_ and lower_, plus '\0'.
    char buff[sizeof(upper_) * 4];
    sprintf(buff, "%llx%llx", upper_, lower_);
    return std::string(buff);
}

std::pair <uint64_t, uint64_t> Uuid::integer()
{
    return std::make_pair(upper_, lower_);
}

} // namespace uuid
