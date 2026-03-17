#include "directxmath/directxmath.h"

#include "collada/types.h"
#include "collada/instance_types.h"

namespace collada::node_state {
  inline static void load_transform(instance_types::transform * instance_transform,
                                    types::transform const & transform)
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
  }

  void initialize_node_transforms(types::node const * const node,
                                  instance_types::node_instance * const node_instance)
  {
    for (int i = 0; i < node->transforms_count; i++) {
      load_transform(&node_instance->transforms[i],
                     node->transforms[i]);
    }
  }

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
      assert(!vector_equal(XMVectorSetW(transform.vector, 0), XMVectorZero()));
      return XMMatrixRotationNormal(transform.vector,
                                    XMConvertToRadians(XMVectorGetW(transform.vector)));
    case types::transform_type::SCALE:
      return XMMatrixScalingFromVector(transform.vector);
    case types::transform_type::MATRIX:
      return transform.matrix;
    default:
      assert(false);
      break;
    }
  }
}
