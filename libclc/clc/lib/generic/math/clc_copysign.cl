//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <clc/internal/clc.h>

#define FUNCTION __clc_copysign
#define __IMPL_FUNCTION(x) __builtin_elementwise_copysign
#define __CLC_BODY <clc/shared/binary_def.inc>

#include <clc/math/gentype.inc>
