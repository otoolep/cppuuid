//
// uuid.hpp
//
// Header file for the UUID generator class.
//

#pragma once

#include <inttypes.h>
#include <map>
#include <string>
#include <exception>

namespace uuid {

////////////////////////////////////////////////////////////////////////////////
// Exceptions
//

class NodeOutOfRangeException : public std::exception
{
    const char* what() { return ("Node out of range"); }
};

class ClockSeqOutOfRangeException : public std::exception
{
    const char* what() { return ("Clock sequence out of range"); }
};


////////////////////////////////////////////////////////////////////////////////
// UUID Class definition.

class Uuid
{
  public:
    Uuid(uint32_t time_low, uint16_t time_mid, uint16_t time_hi_version,
         uint8_t clock_seq_low, uint8_t clock_seq_hi_variant, uint64_t node);
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
    static const uint64_t version_ = 1;
    // Store the 128-bit UUID as two 64-bit integers.
    uint64_t upper_;
    uint64_t lower_;

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
