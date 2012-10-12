#pragma once

#include <darc/id.hpp>

namespace darc
{

struct entry
{
  const static uint32_t namespace_type = 0;
  const static uint32_t tag_type = 1;
  const static uint32_t tag_link_type = 2;

  uint32_t type;
  std::string name;

  entry()
  {
  }

  entry(uint32_t type) :
    type(type)
  {
  }

  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & type;
    ar & name;
  }
};

}

#include <beam/arg.hpp>

namespace beam
{

template<>
std::string to_string(const arg<darc::entry>& e);

}
