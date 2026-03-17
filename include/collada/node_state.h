#pragma once

#include "collada/types.h"
#include "collada/instance_types.h"

namespace collada::node_state {
  struct state {
    instance_types::node * node_instances;

    void allocate_node_instances(types::node const * const * const nodes, int nodes_count);
    void update_node_world_transform(instance_types::node & node_instance);
  };
};
