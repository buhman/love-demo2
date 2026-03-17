#include <stdio.h>

#include "directxmath/directxmath.h"

#include "new.h"

#include "collada/node_state.h"

namespace collada::node_state {

  //////////////////////////////////////////////////////////////////////
  // transforms
  //////////////////////////////////////////////////////////////////////

  inline static void load_transform(types::transform const & transform,
                                    instance_types::transform * instance_transform)
  {
    switch (transform.type) {
    case types::transform_type::LOOKAT:
      instance_transform->lookat.eye = XMLoadFloat3((XMFLOAT3 *)&transform.lookat.eye);
      instance_transform->lookat.at = XMLoadFloat3((XMFLOAT3 *)&transform.lookat.at);
      instance_transform->lookat.up = XMLoadFloat3((XMFLOAT3 *)&transform.lookat.up);
      break;
    case types::transform_type::MATRIX:
      instance_transform->matrix = XMLoadFloat4x4((XMFLOAT4X4 *)&transform.matrix);
      break;
    case types::transform_type::ROTATE:
      instance_transform->vector = XMLoadFloat4((XMFLOAT4 *)&transform.rotate);
      break;
    case types::transform_type::SCALE:
      instance_transform->vector = XMLoadFloat3((XMFLOAT3*)&transform.scale);
      break;
    case types::transform_type::TRANSLATE:
      instance_transform->vector = XMLoadFloat3((XMFLOAT3*)&transform.translate);
      break;
    default:
      assert(false);
    }
    instance_transform->type = transform.type;
  }

  inline static void initialize_node_transforms(instance_types::node & node_instance)
  {
    for (int i = 0; i < node_instance.node->transforms_count; i++) {
      load_transform(node_instance.node->transforms[i], &node_instance.transforms[i]);
    }
  }

  inline static void allocate_node_instance(instance_types::node & node_instance,
                                            types::node const * const node)
  {
    node_instance.node = node;
    node_instance.transforms = New<instance_types::transform>(node->transforms_count);

    initialize_node_transforms(node_instance);
  }

  void state::allocate_node_instances(types::node const * const * const nodes, int nodes_count)
  {
    node_instances = New<instance_types::node>(nodes_count);
    for (int i = 0; i < nodes_count; i++) {
      allocate_node_instance(node_instances[i], nodes[i]);
    }
  }

  //////////////////////////////////////////////////////////////////////
  // world matrix
  //////////////////////////////////////////////////////////////////////

  inline static bool vector_equal(XMVECTOR V1, XMVECTOR V2)
  {
    uint32_t CR;
    XMVectorEqualR(&CR, V1, V2);
    return XMComparisonAllTrue(CR);
  }

  inline static XMMATRIX transform_matrix(instance_types::transform const& transform)
  {
    switch (transform.type) {
    case types::transform_type::TRANSLATE:
      return XMMatrixTranslationFromVector(transform.vector);
    case types::transform_type::ROTATE:
      //assert(!vector_equal(XMVectorSetW(transform.vector, 0), XMVectorZero()));
      if (vector_equal(XMVectorSetW(transform.vector, 0), XMVectorZero()))
        return XMMatrixIdentity();
      return XMMatrixRotationNormal(transform.vector,
                                    XMConvertToRadians(XMVectorGetW(transform.vector)));
    case types::transform_type::SCALE:
      return XMMatrixScalingFromVector(transform.vector);
    case types::transform_type::MATRIX:
      return transform.matrix;
    default:
      fprintf(stderr, "unknown transform type %d\n", (int)transform.type);
      assert(false);
      break;
    }
  }

  void state::update_node_world_transform(instance_types::node & node_instance)
  {
    XMMATRIX world;

    if (node_instance.node->parent_index >= 0)
      world = node_instances[node_instance.node->parent_index].world;
    else
      world = XMMatrixIdentity();

    for (int i = 0; i < node_instance.node->transforms_count; i++) {
      world = transform_matrix(node_instance.transforms[i]) * world;
    }

    node_instance.world = world;
  }
}
