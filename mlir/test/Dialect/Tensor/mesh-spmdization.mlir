// RUN: mlir-opt \
// RUN:   --pass-pipeline="builtin.module(func.func(mesh-spmdization,test-single-fold))" \
// RUN:   %s | FileCheck %s

mesh.mesh @mesh_1d_4(shape = 4)

// CHECK-LABEL: func @tensor_empty_static_sharded_dims_offsets
func.func @tensor_empty_static_sharded_dims_offsets() -> () {
  %b = tensor.empty() : tensor<8x16xf32>
  %sharding = mesh.sharding @mesh_1d_4 split_axes = [[0]] sharded_dims_offsets = [0, 1, 4, 7, 8] : !mesh.sharding
  %sharded= mesh.shard %b to %sharding : tensor<8x16xf32>
  // CHECK:  %[[sharding:.*]] = mesh.sharding @mesh_1d_4 split_axes = {{\[\[}}0]] sharded_dims_offsets = [0, 1, 4, 7, 8] : !mesh.sharding
  // CHECK:  %[[proc_multi_idx:.*]] = mesh.process_multi_index on @mesh_1d_4 : index
  // CHECK:  %[[V0:.*]]:2 = mesh.shard_shape dims = [8, 16] sharding = %[[sharding]] device = [%[[proc_multi_idx]]
  // CHECK-SAME: ] : index, index
  // CHECK:  tensor.empty(%[[V0]]#0) : tensor<?x16xf32>

  return
}

// CHECK-LABEL: func @tensor_empty_dynamic_sharded_dims_offsets
// CHECK-SAME: %[[A0:.*]]: index
func.func @tensor_empty_dynamic_sharded_dims_offsets(%arg0 : index) -> () {
  %b = tensor.empty(%arg0) : tensor<8x?xf32>
  %sharding = mesh.sharding @mesh_1d_4 split_axes = [[0]] sharded_dims_offsets = [0, 1, 4, 7, 8] : !mesh.sharding
  %sharded= mesh.shard %b to %sharding : tensor<8x?xf32>
  // CHECK:  %[[sharding:.*]] = mesh.sharding @mesh_1d_4 split_axes = {{\[\[}}0]] sharded_dims_offsets = [0, 1, 4, 7, 8] : !mesh.sharding
  // CHECK:  %[[proc_multi_idx:.*]] = mesh.process_multi_index on @mesh_1d_4 : index
  // CHECK:  %[[V0:.*]]:2 = mesh.shard_shape dims = [8, %[[A0]]
  // CHECK-SAME: ] sharding = %[[sharding]] device = [%[[proc_multi_idx]]
  // CHECK-SAME: ] : index, index
  // CHECK:  tensor.empty(%[[V0]]#0, %[[A0]]) : tensor<?x?xf32>

  return
}

// CHECK-LABEL: func @tensor_empty_same_static_dims_sizes
func.func @tensor_empty_same_static_dims_sizes() -> () {
  %b = tensor.empty() : tensor<16x16xf32>
  %sharding = mesh.sharding @mesh_1d_4 split_axes = [[0]] sharded_dims_offsets = [0, 4, 8, 12, 16] : !mesh.sharding
  %sharded= mesh.shard %b to %sharding : tensor<16x16xf32>
  // CHECK-NEXT:  tensor.empty() : tensor<4x16xf32>

  return
}

// CHECK-LABEL: func @tensor_empty_0d
func.func @tensor_empty_0d() -> () {
  tensor.empty() : tensor<f32>
  // CHECK-NEXT:  tensor.empty() : tensor<f32>
  return
}
