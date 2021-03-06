#pragma once

#include <string>
#include <boost/signals.hpp>
#include <boost/signals/connection.hpp>
#include <darc/id.hpp>
#include <boost/uuid/name_generator.hpp>

namespace darc
{
class ns_service;

class local_tag;
typedef boost::shared_ptr<local_tag> local_tag_ptr;

// manages lifetime of a local tag
class local_tag
{
protected:
  boost::uuids::name_generator gen_;
  ns_service * ns_service_;

  ID id_;
  std::string name_;

public:
  typedef void (callback_type)(const ID&, const ID&, const ID&);
  typedef boost::function<callback_type> functor_type;

protected:
  typedef boost::signal<callback_type> signal_type;
  signal_type new_tag_signal_;
  signal_type removed_tag_signal_;

public:
  local_tag(ns_service *,
            const std::string name);

  static local_tag_ptr create(ns_service *,
                              const std::string name);
  ~local_tag();

  void trigger_new_tag(const ID& tag_id, const ID& peer_id)
  {
    // Original tag ID, Remote tag ID, Remote Peer ID
    new_tag_signal_(id_, tag_id, peer_id);
  }

  void trigger_removed_tag(const ID& tag_id, const ID& peer_id)
  {
    removed_tag_signal_(id_, tag_id, peer_id);
  }

  signal_type& new_tag_signal()
  {
    return new_tag_signal_;
  }

  signal_type& removed_tag_signal()
  {
    return removed_tag_signal_;
  }

  const ID& id() const
  {
    return id_;
  }

  const std::string& name() const
  {
    return name_;
  }

};

}
