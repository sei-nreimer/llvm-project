// Test without serialization:
// RUN: %clang_cc1 -std=gnu11 -ast-dump %s \
// RUN: | FileCheck -strict-whitespace %s
//
// Test with serialization:
// RUN: %clang_cc1 -std=gnu11 -emit-pch -o %t %s
// RUN: %clang_cc1 -x c -std=gnu11 -include-pch %t -ast-dump-all /dev/null \
// RUN: | sed -e "s/ <undeserialized declarations>//" -e "s/ imported//" \
// RUN: | FileCheck -strict-whitespace %s

int TestLocation = 0;
// CHECK:      VarDecl{{.*}}TestLocation
// CHECK-NEXT:   IntegerLiteral 0x{{[^ ]*}} <col:20> 'int' 0
// CHECK-NEXT:   typeDetails: BuiltinType 0x{{[^ ]*}} 'int'

int TestIndent = 1 + (1);
// CHECK: |-VarDecl {{.*}} TestIndent 'int' cinit
// CHECK: | |-BinaryOperator {{.*}} 'int' '+'
// CHECK: | | |-IntegerLiteral {{.*}} 'int' 1
// CHECK: | | `-ParenExpr {{.*}} 'int'
// CHECK: | |   `-IntegerLiteral {{.*}} 'int' 1
// CHECK: | `-typeDetails: BuiltinType {{.*}} 'int'

void TestDeclStmt(void) {
  int x = 0;
  int y, z;
}

// CHECK: |-FunctionDecl {{.*}} TestDeclStmt 'void (void)'
// CHECK: | `-CompoundStmt {{.*}}
// CHECK: |   |-DeclStmt {{.*}}
// CHECK: |   | `-VarDecl {{.*}} x 'int' cinit
// CHECK: |   |   |-IntegerLiteral {{.*}} 'int' 0
// CHECK: |   |   `-typeDetails: BuiltinType {{.*}} 'int'
// CHECK: |   `-DeclStmt {{.*}} 
// CHECK: |     |-VarDecl {{.*}} y 'int'
// CHECK: |     | `-typeDetails: BuiltinType {{.*}} 'int'
// CHECK: |     `-VarDecl {{.*}} z 'int'
// CHECK: |       `-typeDetails: BuiltinType {{.*}} 'int'

int TestOpaqueValueExpr = 0 ?: 1;
// CHECK: |-VarDecl {{.*}} TestOpaqueValueExpr 'int' cinit
// CHECK: | |-BinaryConditionalOperator {{.*}} 'int'
// CHECK: | | |-IntegerLiteral {{.*}} 'int' 0
// CHECK: | | |-OpaqueValueExpr {{.*}} 'int'
// CHECK: | | | `-IntegerLiteral {{.*}} 'int' 0
// CHECK: | | |-OpaqueValueExpr {{.*}} 'int'
// CHECK: | | | `-IntegerLiteral {{.*}} 'int' 0
// CHECK: | | `-IntegerLiteral {{.*}} 'int' 1
// CHECK: | `-typeDetails: BuiltinType {{.*}} 'int'

void TestUnaryOperatorExpr(void) {
  char T1 = 1;
  int T2 = 1;

  T1++;
  T2++;

  -T1;
  -T2;

  ~T1;
  ~T2;
}

// CHECK: |-FunctionDecl {{.*}} TestUnaryOperatorExpr 'void (void)'
// CHECK: | `-CompoundStmt {{.*}}
// CHECK: |   |-DeclStmt {{.*}}
// CHECK: |   | `-VarDecl {{.*}} used T1 'char' cinit
// CHECK: |   |   |-ImplicitCastExpr {{.*}} 'char' <IntegralCast>
// CHECK: |   |   | `-IntegerLiteral {{.*}} 'int' 1
// CHECK: |   |   `-typeDetails: BuiltinType {{.*}} 'char'
// CHECK: |   |-DeclStmt {{.*}} 
// CHECK: |   | `-VarDecl {{.*}} used T2 'int' cinit
// CHECK: |   |   |-IntegerLiteral {{.*}} <col:12> 'int' 1
// CHECK: |   |   `-typeDetails: BuiltinType {{.*}} 'int'
// CHECK: |   |-UnaryOperator {{.*}} 'char' postfix '++' cannot overflow
// CHECK: |   | `-DeclRefExpr {{.*}} 'char' lvalue Var {{.*}} 'T1' 'char'
// CHECK: |   |-UnaryOperator {{.*}} 'int' postfix '++'
// CHECK: |   | `-DeclRefExpr {{.*}} 'int' lvalue Var {{.*}} 'T2' 'int'
// CHECK: |   |-UnaryOperator {{.*}} 'int' prefix '-' cannot overflow
// CHECK: |   | `-ImplicitCastExpr {{.*}} 'int' <IntegralCast>
// CHECK: |   |   `-ImplicitCastExpr {{.*}} 'char' <LValueToRValue>
// CHECK: |   |     `-DeclRefExpr {{.*}} 'char' lvalue Var {{.*}} 'T1' 'char'
// CHECK: |   |-UnaryOperator {{.*}} 'int' prefix '-'
// CHECK: |   | `-ImplicitCastExpr {{.*}} 'int' <LValueToRValue>
// CHECK: |   |   `-DeclRefExpr {{.*}} 'int' lvalue Var {{.*}} 'T2' 'int'
// CHECK: |   |-UnaryOperator {{.*}} 'int' prefix '~' cannot overflow
// CHECK: |   | `-ImplicitCastExpr {{.*}} 'int' <IntegralCast>
// CHECK: |   |   `-ImplicitCastExpr {{.*}} 'char' <LValueToRValue>
// CHECK: |   |     `-DeclRefExpr {{.*}} 'char' lvalue Var {{.*}} 'T1' 'char'
// CHECK: |   `-UnaryOperator {{.*}} 'int' prefix '~' cannot overflow
// CHECK: |     `-ImplicitCastExpr {{.*}} 'int' <LValueToRValue>
// CHECK: |       `-DeclRefExpr {{.*}} 'int' lvalue Var {{.*}} 'T2' 'int'

void TestGenericSelectionExpressions(int i) {
  _Generic(i, int : 12);
  // CHECK: GenericSelectionExpr 0x{{[^ ]*}} <line:[[@LINE-1]]:3, col:23> 'int'
  // CHECK-NEXT: ImplicitCastExpr 0x{{[^ ]*}}
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:12> 'int' lvalue ParmVar 0x{{[^ ]*}} 'i' 'int'
  // CHECK-NEXT: BuiltinType 0x{{[^ ]*}} 'int'
  // FIXME: note that the following test line has a spurious whitespace.
  // CHECK-NEXT: case  'int' selected
  // CHECK-NEXT: BuiltinType 0x{{[^ ]*}} 'int'
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:21> 'int' 12
  _Generic(i, int : 12, default : 0);
  // CHECK: GenericSelectionExpr 0x{{[^ ]*}} <line:[[@LINE-1]]:3, col:36> 'int'
  // CHECK-NEXT: ImplicitCastExpr 0x{{[^ ]*}}
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:12> 'int' lvalue ParmVar 0x{{[^ ]*}} 'i' 'int'
  // CHECK-NEXT: BuiltinType 0x{{[^ ]*}} 'int'
  // FIXME: note that the following test line has a spurious whitespace.
  // CHECK-NEXT: case  'int' selected
  // CHECK-NEXT: BuiltinType 0x{{[^ ]*}} 'int'
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:21> 'int' 12
  // CHECK-NEXT: default
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:35> 'int' 0
  _Generic(i, default : 0, int : 12);
  // CHECK: GenericSelectionExpr 0x{{[^ ]*}} <line:[[@LINE-1]]:3, col:36> 'int'
  // CHECK-NEXT: ImplicitCastExpr 0x{{[^ ]*}}
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:12> 'int' lvalue ParmVar 0x{{[^ ]*}} 'i' 'int'
  // CHECK-NEXT: BuiltinType 0x{{[^ ]*}} 'int'
  // CHECK-NEXT: default
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:25> 'int' 0
  // FIXME: note that the following test line has a spurious whitespace.
  // CHECK-NEXT: case  'int' selected
  // CHECK-NEXT: BuiltinType 0x{{[^ ]*}} 'int'
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:34> 'int' 12
  _Generic(i, int : 12, float : 10, default : 100);
  // CHECK: GenericSelectionExpr 0x{{[^ ]*}} <line:[[@LINE-1]]:3, col:50> 'int'
  // CHECK-NEXT: ImplicitCastExpr 0x{{[^ ]*}}
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:12> 'int' lvalue ParmVar 0x{{[^ ]*}} 'i' 'int'
  // CHECK-NEXT: BuiltinType 0x{{[^ ]*}} 'int'
  // FIXME: note that the following test line has a spurious whitespace.
  // CHECK-NEXT: case  'int' selected
  // CHECK-NEXT: BuiltinType 0x{{[^ ]*}} 'int'
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:21> 'int' 12
  // FIXME: note that the following test line has a spurious whitespace.
  // CHECK-NEXT: case  'float'
  // CHECK-NEXT: BuiltinType 0x{{[^ ]*}} 'float'
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:33> 'int' 10
  // CHECK-NEXT: default
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:47> 'int' 100

  int j = _Generic(i, int : 12);
  // CHECK: DeclStmt 0x{{[^ ]*}} <line:[[@LINE-1]]:3, col:32>
  // CHECK-NEXT: VarDecl 0x{{[^ ]*}} <col:3, col:31> col:7 j 'int' cinit
  // CHECK-NEXT: GenericSelectionExpr 0x{{[^ ]*}} <col:11, col:31> 'int'
  // CHECK-NEXT: ImplicitCastExpr 0x{{[^ ]*}}
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:20> 'int' lvalue ParmVar 0x{{[^ ]*}} 'i' 'int'
  // CHECK-NEXT: BuiltinType 0x{{[^ ]*}} 'int'
  // FIXME: note that the following test line has a spurious whitespace.
  // CHECK-NEXT: case  'int' selected
  // CHECK-NEXT: BuiltinType 0x{{[^ ]*}} 'int'
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:29> 'int' 12
}

void TestLabelsAndGoto(void) {
  // Note: case and default labels are handled by TestSwitch().

label1:
  ;
  // CHECK: LabelStmt 0x{{[^ ]*}} <line:[[@LINE-2]]:1, line:[[@LINE-1]]:3> 'label1'
  // CHECK-NEXT: NullStmt 0x{{[^ ]*}} <col:3>

  goto label2;
  // CHECK-NEXT: GotoStmt 0x{{[^ ]*}} <line:[[@LINE-1]]:3, col:8> 'label2' 0x{{[^ ]*}}

label2:
  0;
  // CHECK-NEXT: LabelStmt 0x{{[^ ]*}} <line:[[@LINE-2]]:1, line:[[@LINE-1]]:3> 'label2'
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:3> 'int' 0

  void *ptr = &&label1;
  // CHECK-NEXT: DeclStmt
  // CHECK-NEXT: VarDecl
  // CHECK-NEXT: AddrLabelExpr 0x{{[^ ]*}} <col:15, col:17> 'void *' label1 0x{{[^ ]*}}
  // CHECK-NEXT: typeDetails: PointerType 0x{{[^ ]*}} 'void *' 
  // CHECK-NEXT: typeDetails: BuiltinType 0x{{[^ ]*}} 'void'

  goto *ptr;
  // CHECK-NEXT: IndirectGotoStmt 0x{{[^ ]*}} <line:[[@LINE-1]]:3, col:9>
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:9> 'void *' lvalue Var 0x{{[^ ]*}} 'ptr' 'void *'

label3:
  // CHECK-NEXT: LabelStmt 0x{{[^ ]*}} <line:[[@LINE-1]]:1, col:7> 'label3'
  // CHECK-NEXT: NullStmt 0x{{[^ ]*}} <col:7>
}

void TestSwitch(int i) {
  switch (i) {
  // CHECK: SwitchStmt 0x{{[^ ]*}} <line:[[@LINE-1]]:3, line:[[@LINE+37]]:3>
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:11> 'int' lvalue ParmVar 0x{{[^ ]*}} 'i' 'int'
  // CHECK-NEXT: CompoundStmt 0x{{[^ ]*}} <col:14, line:[[@LINE+34]]:3>
  case 0:
    break;
  // CHECK-NEXT: CaseStmt 0x{{[^ ]*}} <line:[[@LINE-2]]:3, line:[[@LINE-1]]:5>
  // CHECK-NEXT: ConstantExpr
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:8> 'int' 0
  // CHECK-NEXT: BreakStmt 0x{{[^ ]*}} <line:[[@LINE-4]]:5>
  case 1:
  case 2:
    break;
  // CHECK-NEXT: CaseStmt 0x{{[^ ]*}} <line:[[@LINE-3]]:3, line:[[@LINE-1]]:5>
  // CHECK-NEXT: ConstantExpr
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:8> 'int' 1
  // CHECK-NEXT: CaseStmt 0x{{[^ ]*}} <line:[[@LINE-5]]:3, line:[[@LINE-4]]:5>
  // CHECK-NEXT: ConstantExpr
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:8> 'int' 2
  // CHECK-NEXT: BreakStmt 0x{{[^ ]*}} <line:[[@LINE-7]]:5>
  default:
    break;
  // CHECK-NEXT: DefaultStmt 0x{{[^ ]*}} <line:[[@LINE-2]]:3, line:[[@LINE-1]]:5>
  // CHECK-NEXT: BreakStmt 0x{{[^ ]*}} <col:5>
  case 3 ... 5:
    break;
  // CHECK-NEXT: CaseStmt 0x{{[^ ]*}} <line:[[@LINE-2]]:3, line:[[@LINE-1]]:5> gnu_range
  // CHECK-NEXT: ConstantExpr
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:8> 'int' 3
  // CHECK-NEXT: ConstantExpr
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:14> 'int' 5
  // CHECK-NEXT: BreakStmt 0x{{[^ ]*}} <line:[[@LINE-6]]:5>
  case 6:
  // CHECK-NEXT: CaseStmt 0x{{[^ ]*}} <line:[[@LINE-1]]:3, col:9>
  // CHECK-NEXT: ConstantExpr
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:8> 'int' 6
  // CHECK-NEXT: NullStmt 0x{{[^ ]*}} <col:9>
  }

  switch(i){
  // CHECK: SwitchStmt 0x{{[^ ]*}} <line:[[@LINE-1]]:3, line:[[@LINE+7]]:3>
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:10> 'int' lvalue ParmVar 0x{{[^ ]*}} 'i' 'int'
  // CHECK-NEXT: CompoundStmt 0x{{[^ ]*}} <col:12, line:[[@LINE+4]]:3>
  default:
  // CHECK-NEXT: DefaultStmt 0x{{[^ ]*}} <line:[[@LINE-1]]:3, col:10>
  // CHECK-NEXT: NullStmt 0x{{[^ ]*}} <col:10>
  }
}

void TestIf(_Bool b) {
  if (b)
    ;
  // CHECK: IfStmt 0x{{[^ ]*}} <line:[[@LINE-2]]:3, line:[[@LINE-1]]:5>
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:7> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: NullStmt

  if (b) {}
  // CHECK: IfStmt 0x{{[^ ]*}} <line:[[@LINE-1]]:3, col:11>
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:7> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: CompoundStmt

  if (b)
    ;
  else
    ;
  // CHECK: IfStmt 0x{{[^ ]*}} <line:[[@LINE-4]]:3, line:[[@LINE-1]]:5> has_else
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:7> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: NullStmt 0x{{[^ ]*}} <line:[[@LINE-6]]:5>
  // CHECK-NEXT: NullStmt 0x{{[^ ]*}} <line:[[@LINE-5]]:5>

  if (b) {}
  else {}
  // CHECK: IfStmt 0x{{[^ ]*}} <line:[[@LINE-2]]:3, line:[[@LINE-1]]:9> has_else
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:7> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: CompoundStmt 0x{{[^ ]*}} <col:10, col:11>
  // CHECK-NEXT: CompoundStmt 0x{{[^ ]*}} <line:[[@LINE-5]]:8, col:9>

  if (b)
    ;
  else if (b)
    ;
  // CHECK: IfStmt 0x{{[^ ]*}} <line:[[@LINE-4]]:3, line:[[@LINE-1]]:5> has_else
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:7> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: NullStmt 0x{{[^ ]*}} <line:[[@LINE-6]]:5>
  // CHECK-NEXT: IfStmt 0x{{[^ ]*}} <line:[[@LINE-6]]:8, line:[[@LINE-5]]:5>
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:12> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: NullStmt 0x{{[^ ]*}} <line:[[@LINE-8]]:5>

  if (b)
    ;
  else if (b)
    ;
  else
    ;
  // CHECK: IfStmt 0x{{[^ ]*}} <line:[[@LINE-6]]:3, line:[[@LINE-1]]:5> has_else
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:7> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: NullStmt 0x{{[^ ]*}} <line:[[@LINE-8]]:5>
  // CHECK-NEXT: IfStmt 0x{{[^ ]*}} <line:[[@LINE-8]]:8, line:[[@LINE-5]]:5> has_else
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:12> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: NullStmt 0x{{[^ ]*}} <line:[[@LINE-10]]:5>
  // CHECK-NEXT: NullStmt 0x{{[^ ]*}} <line:[[@LINE-9]]:5>
}

void TestIteration(_Bool b) {
  while (b)
    ;
  // CHECK: WhileStmt 0x{{[^ ]*}} <line:[[@LINE-2]]:3, line:[[@LINE-1]]:5>
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:10> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: NullStmt 0x{{[^ ]*}} <line:[[@LINE-4]]:5>

  do
    ;
  while (b);
  // CHECK: DoStmt 0x{{[^ ]*}} <line:[[@LINE-3]]:3, line:[[@LINE-1]]:11>
  // CHECK-NEXT: NullStmt 0x{{[^ ]*}} <line:[[@LINE-3]]:5>
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:10> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'

  for (int i = 0; i < 10; ++i)
    ;
  // CHECK: ForStmt 0x{{[^ ]*}} <line:[[@LINE-2]]:3, line:[[@LINE-1]]:5>
  // CHECK-NEXT: DeclStmt
  // CHECK-NEXT: VarDecl 0x{{[^ ]*}} <col:8, col:16> col:12 used i 'int' cinit
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:16> 'int' 0
  // CHECK-NEXT: typeDetails: BuiltinType 0x{{[^ ]*}} 'int'
  // CHECK-NEXT: <<<NULL>>>
  // CHECK-NEXT: BinaryOperator 0x{{[^ ]*}} <col:19, col:23> 'int' '<'
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:19> 'int' lvalue Var 0x{{[^ ]*}} 'i' 'int'
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:23> 'int' 10
  // CHECK-NEXT: UnaryOperator 0x{{[^ ]*}} <col:27, col:29> 'int' prefix '++'
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:29> 'int' lvalue Var 0x{{[^ ]*}} 'i' 'int'
  // CHECK-NEXT: NullStmt

  for (b; b; b)
    ;
  // CHECK: ForStmt 0x{{[^ ]*}} <line:[[@LINE-2]]:3, line:[[@LINE-1]]:5>
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:8> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: <<<NULL>>>
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:11> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:14> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: NullStmt

  for (; b; b = !b)
    ;
  // CHECK: ForStmt 0x{{[^ ]*}} <line:[[@LINE-2]]:3, line:[[@LINE-1]]:5>
  // CHECK-NEXT: <<<NULL>>>
  // CHECK-NEXT: <<<NULL>>>
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:10> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: BinaryOperator 0x{{[^ ]*}} <col:13, col:18> '_Bool' '='
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:13> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: UnaryOperator 0x{{[^ ]*}} <col:17, col:18> 'int' prefix '!' cannot overflow
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:18> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: NullStmt

  for (; b;)
    ;
  // CHECK: ForStmt 0x{{[^ ]*}} <line:[[@LINE-2]]:3, line:[[@LINE-1]]:5>
  // CHECK-NEXT: <<<NULL>>>
  // CHECK-NEXT: <<<NULL>>>
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:10> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: <<<NULL>>>
  // CHECK-NEXT: NullStmt

  for (;; b = !b)
    ;
  // CHECK: ForStmt 0x{{[^ ]*}} <line:[[@LINE-2]]:3, line:[[@LINE-1]]:5>
  // CHECK-NEXT: <<<NULL>>>
  // CHECK-NEXT: <<<NULL>>>
  // CHECK-NEXT: <<<NULL>>>
  // CHECK-NEXT: BinaryOperator 0x{{[^ ]*}} <line:[[@LINE-6]]:11, col:16> '_Bool' '='
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:11> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: UnaryOperator 0x{{[^ ]*}} <col:15, col:16> 'int' prefix '!' cannot overflow
  // CHECK-NEXT: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:16> '_Bool' lvalue ParmVar 0x{{[^ ]*}} 'b' '_Bool'
  // CHECK-NEXT: NullStmt

  for (;;)
    ;
  // CHECK: ForStmt 0x{{[^ ]*}} <line:[[@LINE-2]]:3, line:[[@LINE-1]]:5>
  // CHECK-NEXT: <<<NULL>>>
  // CHECK-NEXT: <<<NULL>>>
  // CHECK-NEXT: <<<NULL>>>
  // CHECK-NEXT: <<<NULL>>>
  // CHECK-NEXT: NullStmt
}

void TestJumps(void) {
  // goto and computed goto was tested in TestLabelsAndGoto().

  while (1) {
    continue;
    // CHECK: ContinueStmt 0x{{[^ ]*}} <line:[[@LINE-1]]:5>
    break;
    // CHECK: BreakStmt 0x{{[^ ]*}} <line:[[@LINE-1]]:5>
  }
  return;
  // CHECK: ReturnStmt 0x{{[^ ]*}} <line:[[@LINE-1]]:3>

  return TestSwitch(1);
  // CHECK: ReturnStmt 0x{{[^ ]*}} <line:[[@LINE-1]]:3, col:22>
  // CHECK-NEXT: CallExpr 0x{{[^ ]*}} <col:10, col:22> 'void'
}

void TestMiscStmts(void) {
  ({int a = 10; a;});
  // CHECK: StmtExpr 0x{{[^ ]*}} <line:[[@LINE-1]]:3, col:20> 'int'
  // CHECK-NEXT: CompoundStmt
  // CHECK-NEXT: DeclStmt
  // CHECK-NEXT: VarDecl 0x{{[^ ]*}} <col:5, col:13> col:9 used a 'int' cinit
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:13> 'int' 10
  // CHECK: ImplicitCastExpr 0x{{[^ ]*}}
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:17> 'int' lvalue Var 0x{{[^ ]*}} 'a' 'int'  
  ({int a = 10; a;;; });
  // CHECK-NEXT: StmtExpr 0x{{[^ ]*}} <line:[[@LINE-1]]:3, col:23> 'int'
  // CHECK-NEXT: CompoundStmt
  // CHECK-NEXT: DeclStmt
  // CHECK-NEXT: VarDecl 0x{{[^ ]*}} <col:5, col:13> col:9 used a 'int' cinit
  // CHECK-NEXT: IntegerLiteral 0x{{[^ ]*}} <col:13> 'int' 10
  // CHECK: ImplicitCastExpr
  // CHECK-NEXT: DeclRefExpr 0x{{[^ ]*}} <col:17> 'int' lvalue Var 0x{{[^ ]*}} 'a' 'int'
  // CHECK-NEXT: NullStmt
  // CHECK-NEXT: NullStmt
}
