// RUN: %clang_cc1 -triple x86_64-unknown-unknown -fopenmp -ast-dump %s | FileCheck --match-full-lines -implicit-check-not=openmp_structured_block %s

void test_one(int x) {
#pragma omp distribute
  for (int i = 0; i < x; i++)
    ;
}

void test_two(int x, int y) {
#pragma omp distribute
  for (int i = 0; i < x; i++)
    for (int i = 0; i < y; i++)
      ;
}

void test_three(int x, int y) {
#pragma omp distribute collapse(1)
  for (int i = 0; i < x; i++)
    for (int i = 0; i < y; i++)
      ;
}

void test_four(int x, int y) {
#pragma omp distribute collapse(2)
  for (int i = 0; i < x; i++)
    for (int i = 0; i < y; i++)
      ;
}

void test_five(int x, int y, int z) {
#pragma omp distribute collapse(2)
  for (int i = 0; i < x; i++)
    for (int i = 0; i < y; i++)
      for (int i = 0; i < z; i++)
        ;
}

// CHECK: TranslationUnitDecl {{.*}} <<invalid sloc>> <invalid sloc>
// CHECK: |-FunctionDecl {{.*}} <{{.*}}ast-dump-openmp-distribute.c:3:1, line:7:1> line:3:6 test_one 'void (int)'
// CHECK-NEXT: | |-ParmVarDecl {{.*}} <col:15, col:19> col:19 used x 'int'
// CHECK: | `-CompoundStmt {{.*}} <col:22, line:7:1>
// CHECK-NEXT: |   `-OMPDistributeDirective {{.*}} <line:4:1, col:23>
// CHECK-NEXT: |     `-CapturedStmt {{.*}} <line:5:3, line:6:5>
// CHECK-NEXT: |       |-CapturedDecl {{.*}} <<invalid sloc>> <invalid sloc>
// CHECK-NEXT: |       | |-ForStmt {{.*}} <line:5:3, line:6:5>
// CHECK-NEXT: |       | | |-DeclStmt {{.*}} <line:5:8, col:17>
// CHECK-NEXT: |       | | | `-VarDecl {{.*}} <col:8, col:16> col:12 used i 'int' cinit
// CHECK: |       | | |   |-IntegerLiteral {{.*}} <col:16> 'int' 0
// CHECK: |       | | |-<<<NULL>>>
// CHECK-NEXT: |       | | |-BinaryOperator {{.*}} <col:19, col:23> 'int' '<'
// CHECK-NEXT: |       | | | |-ImplicitCastExpr {{.*}} <col:19> 'int' <LValueToRValue>
// CHECK-NEXT: |       | | | | `-DeclRefExpr {{.*}} <col:19> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT: |       | | | `-ImplicitCastExpr {{.*}} <col:23> 'int' <LValueToRValue>
// CHECK-NEXT: |       | | |   `-DeclRefExpr {{.*}} <col:23> 'int' lvalue ParmVar {{.*}} 'x' 'int' refers_to_enclosing_variable_or_capture
// CHECK-NEXT: |       | | |-UnaryOperator {{.*}} <col:26, col:27> 'int' postfix '++'
// CHECK-NEXT: |       | | | `-DeclRefExpr {{.*}} <col:26> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT: |       | | `-NullStmt {{.*}} <line:6:5>
// CHECK-NEXT: |       | |-ImplicitParamDecl {{.*}} <line:4:1> col:1 implicit __context 'struct (unnamed at {{.*}}ast-dump-openmp-distribute.c:4:1) *const restrict'
// CHECK: |       | `-VarDecl {{.*}} <line:5:8, col:16> col:12 used i 'int' cinit
// CHECK-NEXT: |       |   |-IntegerLiteral {{.*}} <col:16> 'int' 0
// CHECK: |       `-DeclRefExpr {{.*}} <col:3> 'int' lvalue ParmVar {{.*}} 'x' 'int'
// CHECK-NEXT: |-FunctionDecl {{.*}} <line:9:1, line:14:1> line:9:6 test_two 'void (int, int)'
// CHECK-NEXT: | |-ParmVarDecl {{.*}} <col:15, col:19> col:19 used x 'int'
// CHECK: | |-ParmVarDecl {{.*}} <col:22, col:26> col:26 used y 'int'
// CHECK: | `-CompoundStmt {{.*}} <col:29, line:14:1>
// CHECK-NEXT: |   `-OMPDistributeDirective {{.*}} <line:10:1, col:23>
// CHECK-NEXT: |     `-CapturedStmt {{.*}} <line:11:3, line:13:7>
// CHECK-NEXT: |       |-CapturedDecl {{.*}} <<invalid sloc>> <invalid sloc>
// CHECK-NEXT: |       | |-ForStmt {{.*}} <line:11:3, line:13:7>
// CHECK-NEXT: |       | | |-DeclStmt {{.*}} <line:11:8, col:17>
// CHECK-NEXT: |       | | | `-VarDecl {{.*}} <col:8, col:16> col:12 used i 'int' cinit
// CHECK-NEXT: |       | | |   |-IntegerLiteral {{.*}} <col:16> 'int' 0
// CHECK: |       | | |-<<<NULL>>>
// CHECK-NEXT: |       | | |-BinaryOperator {{.*}} <col:19, col:23> 'int' '<'
// CHECK-NEXT: |       | | | |-ImplicitCastExpr {{.*}} <col:19> 'int' <LValueToRValue>
// CHECK-NEXT: |       | | | | `-DeclRefExpr {{.*}} <col:19> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT: |       | | | `-ImplicitCastExpr {{.*}} <col:23> 'int' <LValueToRValue>
// CHECK-NEXT: |       | | |   `-DeclRefExpr {{.*}} <col:23> 'int' lvalue ParmVar {{.*}} 'x' 'int' refers_to_enclosing_variable_or_capture
// CHECK-NEXT: |       | | |-UnaryOperator {{.*}} <col:26, col:27> 'int' postfix '++'
// CHECK-NEXT: |       | | | `-DeclRefExpr {{.*}} <col:26> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT: |       | | `-ForStmt {{.*}} <line:12:5, line:13:7>
// CHECK-NEXT: |       | |   |-DeclStmt {{.*}} <line:12:10, col:19>
// CHECK-NEXT: |       | |   | `-VarDecl {{.*}} <col:10, col:18> col:14 used i 'int' cinit
// CHECK-NEXT: |       | |   |   |-IntegerLiteral {{.*}} <col:18> 'int' 0
// CHECK: |       | |   |-<<<NULL>>>
// CHECK-NEXT: |       | |   |-BinaryOperator {{.*}} <col:21, col:25> 'int' '<'
// CHECK-NEXT: |       | |   | |-ImplicitCastExpr {{.*}} <col:21> 'int' <LValueToRValue>
// CHECK-NEXT: |       | |   | | `-DeclRefExpr {{.*}} <col:21> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT: |       | |   | `-ImplicitCastExpr {{.*}} <col:25> 'int' <LValueToRValue>
// CHECK-NEXT: |       | |   |   `-DeclRefExpr {{.*}} <col:25> 'int' lvalue ParmVar {{.*}} 'y' 'int' refers_to_enclosing_variable_or_capture
// CHECK-NEXT: |       | |   |-UnaryOperator {{.*}} <col:28, col:29> 'int' postfix '++'
// CHECK-NEXT: |       | |   | `-DeclRefExpr {{.*}} <col:28> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT: |       | |   `-NullStmt {{.*}} <line:13:7>
// CHECK-NEXT: |       | |-ImplicitParamDecl {{.*}} <line:10:1> col:1 implicit __context 'struct (unnamed at {{.*}}ast-dump-openmp-distribute.c:10:1) *const restrict'
// CHECK: |       | |-VarDecl {{.*}} <line:11:8, col:16> col:12 used i 'int' cinit
// CHECK-NEXT: |       | | |-IntegerLiteral {{.*}} <col:16> 'int' 0
// CHECK: |       | `-VarDecl {{.*}} <line:12:10, col:18> col:14 used i 'int' cinit
// CHECK-NEXT: |       |   |-IntegerLiteral {{.*}} <col:18> 'int' 0
// CHECK: |       |-DeclRefExpr {{.*}} <line:11:3> 'int' lvalue ParmVar {{.*}} 'x' 'int'
// CHECK-NEXT: |       `-DeclRefExpr {{.*}} <line:12:25> 'int' lvalue ParmVar {{.*}} 'y' 'int'
// CHECK-NEXT: |-FunctionDecl {{.*}} <line:16:1, line:21:1> line:16:6 test_three 'void (int, int)'
// CHECK-NEXT: | |-ParmVarDecl {{.*}} <col:17, col:21> col:21 used x 'int'
// CHECK: | |-ParmVarDecl {{.*}} <col:24, col:28> col:28 used y 'int'
// CHECK: | `-CompoundStmt {{.*}} <col:31, line:21:1>
// CHECK-NEXT: |   `-OMPDistributeDirective {{.*}} <line:17:1, col:35>
// CHECK-NEXT: |     |-OMPCollapseClause {{.*}} <col:24, col:34>
// CHECK-NEXT: |     | `-ConstantExpr {{.*}} <col:33> 'int'
// CHECK-NEXT: |     | |-value: Int 1
// CHECK-NEXT: |     |   `-IntegerLiteral {{.*}} <col:33> 'int' 1
// CHECK-NEXT: |     `-CapturedStmt {{.*}} <line:18:3, line:20:7>
// CHECK-NEXT: |       |-CapturedDecl {{.*}} <<invalid sloc>> <invalid sloc>
// CHECK-NEXT: |       | |-ForStmt {{.*}} <line:18:3, line:20:7>
// CHECK-NEXT: |       | | |-DeclStmt {{.*}} <line:18:8, col:17>
// CHECK-NEXT: |       | | | `-VarDecl {{.*}} <col:8, col:16> col:12 used i 'int' cinit
// CHECK-NEXT: |       | | |   |-IntegerLiteral {{.*}} <col:16> 'int' 0
// CHECK: |       | | |-<<<NULL>>>
// CHECK-NEXT: |       | | |-BinaryOperator {{.*}} <col:19, col:23> 'int' '<'
// CHECK-NEXT: |       | | | |-ImplicitCastExpr {{.*}} <col:19> 'int' <LValueToRValue>
// CHECK-NEXT: |       | | | | `-DeclRefExpr {{.*}} <col:19> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT: |       | | | `-ImplicitCastExpr {{.*}} <col:23> 'int' <LValueToRValue>
// CHECK-NEXT: |       | | |   `-DeclRefExpr {{.*}} <col:23> 'int' lvalue ParmVar {{.*}} 'x' 'int' refers_to_enclosing_variable_or_capture
// CHECK-NEXT: |       | | |-UnaryOperator {{.*}} <col:26, col:27> 'int' postfix '++'
// CHECK-NEXT: |       | | | `-DeclRefExpr {{.*}} <col:26> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT: |       | | `-ForStmt {{.*}} <line:19:5, line:20:7>
// CHECK-NEXT: |       | |   |-DeclStmt {{.*}} <line:19:10, col:19>
// CHECK-NEXT: |       | |   | `-VarDecl {{.*}} <col:10, col:18> col:14 used i 'int' cinit
// CHECK-NEXT: |       | |   |   |-IntegerLiteral {{.*}} <col:18> 'int' 0
// CHECK: |       | |   |-<<<NULL>>>
// CHECK-NEXT: |       | |   |-BinaryOperator {{.*}} <col:21, col:25> 'int' '<'
// CHECK-NEXT: |       | |   | |-ImplicitCastExpr {{.*}} <col:21> 'int' <LValueToRValue>
// CHECK-NEXT: |       | |   | | `-DeclRefExpr {{.*}} <col:21> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT: |       | |   | `-ImplicitCastExpr {{.*}} <col:25> 'int' <LValueToRValue>
// CHECK-NEXT: |       | |   |   `-DeclRefExpr {{.*}} <col:25> 'int' lvalue ParmVar {{.*}} 'y' 'int' refers_to_enclosing_variable_or_capture
// CHECK-NEXT: |       | |   |-UnaryOperator {{.*}} <col:28, col:29> 'int' postfix '++'
// CHECK-NEXT: |       | |   | `-DeclRefExpr {{.*}} <col:28> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT: |       | |   `-NullStmt {{.*}} <line:20:7>
// CHECK-NEXT: |       | |-ImplicitParamDecl {{.*}} <line:17:1> col:1 implicit __context 'struct (unnamed at {{.*}}ast-dump-openmp-distribute.c:17:1) *const restrict'
// CHECK: |       | |-VarDecl {{.*}} <line:18:8, col:16> col:12 used i 'int' cinit
// CHECK-NEXT: |       | | |-IntegerLiteral {{.*}} <col:16> 'int' 0
// CHECK: |       | `-VarDecl {{.*}} <line:19:10, col:18> col:14 used i 'int' cinit
// CHECK-NEXT: |       |   |-IntegerLiteral {{.*}} <col:18> 'int' 0
// CHECK: |       |-DeclRefExpr {{.*}} <line:18:3> 'int' lvalue ParmVar {{.*}} 'x' 'int'
// CHECK-NEXT: |       `-DeclRefExpr {{.*}} <line:19:25> 'int' lvalue ParmVar {{.*}} 'y' 'int'
// CHECK-NEXT: |-FunctionDecl {{.*}} <line:23:1, line:28:1> line:23:6 test_four 'void (int, int)'
// CHECK-NEXT: | |-ParmVarDecl {{.*}} <col:16, col:20> col:20 used x 'int'
// CHECK: | |-ParmVarDecl {{.*}} <col:23, col:27> col:27 used y 'int'
// CHECK: | `-CompoundStmt {{.*}} <col:30, line:28:1>
// CHECK-NEXT: |   `-OMPDistributeDirective {{.*}} <line:24:1, col:35>
// CHECK-NEXT: |     |-OMPCollapseClause {{.*}} <col:24, col:34>
// CHECK-NEXT: |     | `-ConstantExpr {{.*}} <col:33> 'int'
// CHECK-NEXT: |     | |-value: Int 2
// CHECK-NEXT: |     |   `-IntegerLiteral {{.*}} <col:33> 'int' 2
// CHECK-NEXT: |     `-CapturedStmt {{.*}} <line:25:3, line:27:7>
// CHECK-NEXT: |       |-CapturedDecl {{.*}} <<invalid sloc>> <invalid sloc>
// CHECK-NEXT: |       | |-ForStmt {{.*}} <line:25:3, line:27:7>
// CHECK-NEXT: |       | | |-DeclStmt {{.*}} <line:25:8, col:17>
// CHECK-NEXT: |       | | | `-VarDecl {{.*}} <col:8, col:16> col:12 used i 'int' cinit
// CHECK-NEXT: |       | | |   |-IntegerLiteral {{.*}} <col:16> 'int' 0
// CHECK: |       | | |-<<<NULL>>>
// CHECK-NEXT: |       | | |-BinaryOperator {{.*}} <col:19, col:23> 'int' '<'
// CHECK-NEXT: |       | | | |-ImplicitCastExpr {{.*}} <col:19> 'int' <LValueToRValue>
// CHECK-NEXT: |       | | | | `-DeclRefExpr {{.*}} <col:19> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT: |       | | | `-ImplicitCastExpr {{.*}} <col:23> 'int' <LValueToRValue>
// CHECK-NEXT: |       | | |   `-DeclRefExpr {{.*}} <col:23> 'int' lvalue ParmVar {{.*}} 'x' 'int' refers_to_enclosing_variable_or_capture
// CHECK-NEXT: |       | | |-UnaryOperator {{.*}} <col:26, col:27> 'int' postfix '++'
// CHECK-NEXT: |       | | | `-DeclRefExpr {{.*}} <col:26> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT: |       | | `-ForStmt {{.*}} <line:26:5, line:27:7>
// CHECK-NEXT: |       | |   |-DeclStmt {{.*}} <line:26:10, col:19>
// CHECK-NEXT: |       | |   | `-VarDecl {{.*}} <col:10, col:18> col:14 used i 'int' cinit
// CHECK-NEXT: |       | |   |   |-IntegerLiteral {{.*}} <col:18> 'int' 0
// CHECK: |       | |   |-<<<NULL>>>
// CHECK-NEXT: |       | |   |-BinaryOperator {{.*}} <col:21, col:25> 'int' '<'
// CHECK-NEXT: |       | |   | |-ImplicitCastExpr {{.*}} <col:21> 'int' <LValueToRValue>
// CHECK-NEXT: |       | |   | | `-DeclRefExpr {{.*}} <col:21> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT: |       | |   | `-ImplicitCastExpr {{.*}} <col:25> 'int' <LValueToRValue>
// CHECK-NEXT: |       | |   |   `-DeclRefExpr {{.*}} <col:25> 'int' lvalue ParmVar {{.*}} 'y' 'int' refers_to_enclosing_variable_or_capture
// CHECK-NEXT: |       | |   |-UnaryOperator {{.*}} <col:28, col:29> 'int' postfix '++'
// CHECK-NEXT: |       | |   | `-DeclRefExpr {{.*}} <col:28> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT: |       | |   `-NullStmt {{.*}} <line:27:7>
// CHECK-NEXT: |       | |-ImplicitParamDecl {{.*}} <line:24:1> col:1 implicit __context 'struct (unnamed at {{.*}}ast-dump-openmp-distribute.c:24:1) *const restrict'
// CHECK: |       | |-VarDecl {{.*}} <line:25:8, col:16> col:12 used i 'int' cinit
// CHECK-NEXT: |       | | |-IntegerLiteral {{.*}} <col:16> 'int' 0
// CHECK: |       | `-VarDecl {{.*}} <line:26:10, col:18> col:14 used i 'int' cinit
// CHECK-NEXT: |       |   |-IntegerLiteral {{.*}} <col:18> 'int' 0
// CHECK: |       |-DeclRefExpr {{.*}} <line:25:3> 'int' lvalue ParmVar {{.*}} 'x' 'int'
// CHECK-NEXT: |       `-DeclRefExpr {{.*}} <line:26:5> 'int' lvalue ParmVar {{.*}} 'y' 'int'
// CHECK-NEXT: `-FunctionDecl {{.*}} <line:30:1, line:36:1> line:30:6 test_five 'void (int, int, int)'
// CHECK-NEXT:   |-ParmVarDecl {{.*}} <col:16, col:20> col:20 used x 'int'
// CHECK:   |-ParmVarDecl {{.*}} <col:23, col:27> col:27 used y 'int'
// CHECK:   |-ParmVarDecl {{.*}} <col:30, col:34> col:34 used z 'int'
// CHECK:   `-CompoundStmt {{.*}} <col:37, line:36:1>
// CHECK-NEXT:     `-OMPDistributeDirective {{.*}} <line:31:1, col:35>
// CHECK-NEXT:       |-OMPCollapseClause {{.*}} <col:24, col:34>
// CHECK-NEXT:       | `-ConstantExpr {{.*}} <col:33> 'int'
// CHECK-NEXT:       | |-value: Int 2
// CHECK-NEXT:       |   `-IntegerLiteral {{.*}} <col:33> 'int' 2
// CHECK-NEXT:       `-CapturedStmt {{.*}} <line:32:3, line:35:9>
// CHECK-NEXT:         |-CapturedDecl {{.*}} <<invalid sloc>> <invalid sloc>
// CHECK-NEXT:         | |-ForStmt {{.*}} <line:32:3, line:35:9>
// CHECK-NEXT:         | | |-DeclStmt {{.*}} <line:32:8, col:17>
// CHECK-NEXT:         | | | `-VarDecl {{.*}} <col:8, col:16> col:12 used i 'int' cinit
// CHECK-NEXT:         | | |   |-IntegerLiteral {{.*}} <col:16> 'int' 0
// CHECK:         | | |-<<<NULL>>>
// CHECK-NEXT:         | | |-BinaryOperator {{.*}} <col:19, col:23> 'int' '<'
// CHECK-NEXT:         | | | |-ImplicitCastExpr {{.*}} <col:19> 'int' <LValueToRValue>
// CHECK-NEXT:         | | | | `-DeclRefExpr {{.*}} <col:19> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT:         | | | `-ImplicitCastExpr {{.*}} <col:23> 'int' <LValueToRValue>
// CHECK-NEXT:         | | |   `-DeclRefExpr {{.*}} <col:23> 'int' lvalue ParmVar {{.*}} 'x' 'int' refers_to_enclosing_variable_or_capture
// CHECK-NEXT:         | | |-UnaryOperator {{.*}} <col:26, col:27> 'int' postfix '++'
// CHECK-NEXT:         | | | `-DeclRefExpr {{.*}} <col:26> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT:         | | `-ForStmt {{.*}} <line:33:5, line:35:9>
// CHECK-NEXT:         | |   |-DeclStmt {{.*}} <line:33:10, col:19>
// CHECK-NEXT:         | |   | `-VarDecl {{.*}} <col:10, col:18> col:14 used i 'int' cinit
// CHECK-NEXT:         | |   |   |-IntegerLiteral {{.*}} <col:18> 'int' 0
// CHECK:         | |   |-<<<NULL>>>
// CHECK-NEXT:         | |   |-BinaryOperator {{.*}} <col:21, col:25> 'int' '<'
// CHECK-NEXT:         | |   | |-ImplicitCastExpr {{.*}} <col:21> 'int' <LValueToRValue>
// CHECK-NEXT:         | |   | | `-DeclRefExpr {{.*}} <col:21> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT:         | |   | `-ImplicitCastExpr {{.*}} <col:25> 'int' <LValueToRValue>
// CHECK-NEXT:         | |   |   `-DeclRefExpr {{.*}} <col:25> 'int' lvalue ParmVar {{.*}} 'y' 'int' refers_to_enclosing_variable_or_capture
// CHECK-NEXT:         | |   |-UnaryOperator {{.*}} <col:28, col:29> 'int' postfix '++'
// CHECK-NEXT:         | |   | `-DeclRefExpr {{.*}} <col:28> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT:         | |   `-ForStmt {{.*}} <line:34:7, line:35:9>
// CHECK-NEXT:         | |     |-DeclStmt {{.*}} <line:34:12, col:21>
// CHECK-NEXT:         | |     | `-VarDecl {{.*}} <col:12, col:20> col:16 used i 'int' cinit
// CHECK-NEXT:         | |     |   |-IntegerLiteral {{.*}} <col:20> 'int' 0
// CHECK:         | |     |-<<<NULL>>>
// CHECK-NEXT:         | |     |-BinaryOperator {{.*}} <col:23, col:27> 'int' '<'
// CHECK-NEXT:         | |     | |-ImplicitCastExpr {{.*}} <col:23> 'int' <LValueToRValue>
// CHECK-NEXT:         | |     | | `-DeclRefExpr {{.*}} <col:23> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT:         | |     | `-ImplicitCastExpr {{.*}} <col:27> 'int' <LValueToRValue>
// CHECK-NEXT:         | |     |   `-DeclRefExpr {{.*}} <col:27> 'int' lvalue ParmVar {{.*}} 'z' 'int' refers_to_enclosing_variable_or_capture
// CHECK-NEXT:         | |     |-UnaryOperator {{.*}} <col:30, col:31> 'int' postfix '++'
// CHECK-NEXT:         | |     | `-DeclRefExpr {{.*}} <col:30> 'int' lvalue Var {{.*}} 'i' 'int'
// CHECK-NEXT:         | |     `-NullStmt {{.*}} <line:35:9>
// CHECK-NEXT:         | |-ImplicitParamDecl {{.*}} <line:31:1> col:1 implicit __context 'struct (unnamed at {{.*}}ast-dump-openmp-distribute.c:31:1) *const restrict'
// CHECK:         | |-VarDecl {{.*}} <line:32:8, col:16> col:12 used i 'int' cinit
// CHECK-NEXT:         | | |-IntegerLiteral {{.*}} <col:16> 'int' 0
// CHECK:         | |-VarDecl {{.*}} <line:33:10, col:18> col:14 used i 'int' cinit
// CHECK-NEXT:         | | |-IntegerLiteral {{.*}} <col:18> 'int' 0
// CHECK:         | `-VarDecl {{.*}} <line:34:12, col:20> col:16 used i 'int' cinit
// CHECK-NEXT:         |   |-IntegerLiteral {{.*}} <col:20> 'int' 0
// CHECK:         |-DeclRefExpr {{.*}} <line:32:3> 'int' lvalue ParmVar {{.*}} 'x' 'int'
// CHECK-NEXT:         |-DeclRefExpr {{.*}} <line:33:5> 'int' lvalue ParmVar {{.*}} 'y' 'int'
// CHECK-NEXT:         `-DeclRefExpr {{.*}} <line:34:27> 'int' lvalue ParmVar {{.*}} 'z' 'int'
