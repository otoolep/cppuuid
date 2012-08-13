//
// uuid.hpp
//
// Header file for the UUID generator class.
//

#pragma once

#include <inttypes.h>
#include <map>
#include <string>

namespace uuid {

enum variant {
    RESERVED_NCS,
    RFC_4122,
    RESERVED_MICROSOFT,
    RESERVED_FUTURE
};

class Uuid
{
  public:

    static uint64_t gettime();

    std::string bytes();
    std::string bytes_le();
    std::map<std::string, uint64_t> fields();
    std::string hex();
    std::string integer();
    std::string urn();
    //variant();
    //version();
    //getnode();

  private:
    // Number of 100-ns intervals between the UUID epoch 1582-10-15 00:00:00 and
    // the Unix epoch 1970-01-01 00:00:00. Ref: uuid.py
    static uint64_t num_100nsec_1582_1970;
    static uint64_t last_uuid_time;

    static uint16_t getclockseq();
};

////////////////////////////////////////////////////////////////////////////////
// Generate a UUID from a host ID, sequence number, and the current time.
// If node is not given, getnode() is used to obtain the hardware address. If
// clock_seq is given, it is used as the sequence number; otherwise a random
// 14-bit sequence number is chosen.

Uuid uuid1();
Uuid uuid1(uint64_t node);
Uuid uuid1(uint64_t node, uint16_t clock_seq);

} // namespace uuid
