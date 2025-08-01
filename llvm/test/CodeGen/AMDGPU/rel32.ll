; RUN: llc -mtriple=amdgcn -mcpu=gfx900 < %s | FileCheck %s
; RUN: llc -mtriple=amdgcn -mcpu=gfx1010 < %s | FileCheck %s
; RUN: llc -mtriple=amdgcn -mcpu=gfx1100 < %s | FileCheck %s

@g = protected local_unnamed_addr addrspace(4) externally_initialized global i32 0, align 4

; CHECK-LABEL: rel32_neg_offset:
; CHECK: s_getpc_b64 s[[[LO:[0-9]+]]:[[HI:[0-9]+]]]
; CHECK-NEXT: s_add_u32 s[[LO]], s[[LO]], g@rel32@lo+4
; CHECK-NEXT: s_addc_u32 s[[HI]], s[[HI]], g@rel32@hi+12
; CHECK-NEXT: s_add_u32 s[[LO]], s[[LO]], -16
; CHECK-NEXT: s_addc_u32 s[[HI]], s[[HI]], -1
define ptr addrspace(4) @rel32_neg_offset() {
  %r = getelementptr i32, ptr addrspace(4) @g, i64 -4
  ret ptr addrspace(4) %r
}

; CHECK-LABEL: rel32_large_offset:
; CHECK: s_getpc_b64 s[[[LO:[0-9]+]]:[[HI:[0-9]+]]]
; CHECK-NEXT: s_add_u32 s[[LO]], s[[LO]], g@rel32@lo+4
; CHECK-NEXT: s_addc_u32 s[[HI]], s[[HI]], g@rel32@hi+12
; CHECK-NEXT: s_add_u32 s[[LO]], s[[LO]], 0x502f9000
; CHECK-NEXT: s_addc_u32 s[[HI]], s[[HI]], 9
define ptr addrspace(4) @rel32_large_offset() {
  %r = getelementptr i32, ptr addrspace(4) @g, i64 10000000000
  ret ptr addrspace(4) %r
}
