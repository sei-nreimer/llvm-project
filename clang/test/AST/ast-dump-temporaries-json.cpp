// RUN: %clang_cc1 -triple x86_64-linux-gnu -fsyntax-only -ast-dump=json %s | FileCheck %s

struct S {
  S() {}
  ~S() {}
};

void func(const int &);

void BindTemp() {
  const S &s = S();
}

void MaterializeTemp() {
  const int &i = 1.0;

  float f = 1.0f;
  func(f);
}

// NOTE: CHECK lines have been autogenerated by gen_ast_dump_json_test.py
// using --filters=ExprWithCleanups


// CHECK-NOT: {{^}}Dumping
// CHECK:  "kind": "ExprWithCleanups",
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "offset": {{[0-9]+}},
// CHECK-NEXT:    "col": 16,
// CHECK-NEXT:    "tokLen": 1
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "offset": {{[0-9]+}},
// CHECK-NEXT:    "col": 18,
// CHECK-NEXT:    "tokLen": 1
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "type": {
// CHECK-NEXT:   "qualType": "const S"
// CHECK-NEXT:  },
// CHECK-NEXT:  "valueCategory": "lvalue",
// CHECK-NEXT:  "cleanupsHaveSideEffects": true,
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "MaterializeTemporaryExpr",
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "offset": {{[0-9]+}},
// CHECK-NEXT:      "col": 16,
// CHECK-NEXT:      "tokLen": 1
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "offset": {{[0-9]+}},
// CHECK-NEXT:      "col": 18,
// CHECK-NEXT:      "tokLen": 1
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "const S"
// CHECK-NEXT:    },
// CHECK-NEXT:    "valueCategory": "lvalue",
// CHECK-NEXT:    "extendingDecl": {
// CHECK-NEXT:     "id": "0x{{.*}}",
// CHECK-NEXT:     "kind": "VarDecl",
// CHECK-NEXT:     "name": "s",
// CHECK-NEXT:     "type": {
// CHECK-NEXT:      "qualType": "const S &"
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "storageDuration": "automatic",
// CHECK-NEXT:    "boundToLValueRef": true,
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ImplicitCastExpr",
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "offset": {{[0-9]+}},
// CHECK-NEXT:        "col": 16,
// CHECK-NEXT:        "tokLen": 1
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "offset": {{[0-9]+}},
// CHECK-NEXT:        "col": 18,
// CHECK-NEXT:        "tokLen": 1
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "const S"
// CHECK-NEXT:      },
// CHECK-NEXT:      "valueCategory": "prvalue",
// CHECK-NEXT:      "castKind": "NoOp",
// CHECK-NEXT:      "inner": [
// CHECK-NEXT:       {
// CHECK-NEXT:        "id": "0x{{.*}}",
// CHECK-NEXT:        "kind": "CXXBindTemporaryExpr",
// CHECK-NEXT:        "range": {
// CHECK-NEXT:         "begin": {
// CHECK-NEXT:          "offset": {{[0-9]+}},
// CHECK-NEXT:          "col": 16,
// CHECK-NEXT:          "tokLen": 1
// CHECK-NEXT:         },
// CHECK-NEXT:         "end": {
// CHECK-NEXT:          "offset": {{[0-9]+}},
// CHECK-NEXT:          "col": 18,
// CHECK-NEXT:          "tokLen": 1
// CHECK-NEXT:         }
// CHECK-NEXT:        },
// CHECK-NEXT:        "type": {
// CHECK-NEXT:         "qualType": "S"
// CHECK-NEXT:        },
// CHECK-NEXT:        "valueCategory": "prvalue",
// CHECK-NEXT:        "temp": "0x{{.*}}",
// CHECK-NEXT:        "dtor": {
// CHECK-NEXT:         "id": "0x{{.*}}",
// CHECK-NEXT:         "kind": "CXXDestructorDecl",
// CHECK-NEXT:         "name": "~S",
// CHECK-NEXT:         "type": {
// CHECK-NEXT:          "qualType": "void () noexcept"
// CHECK-NEXT:         }
// CHECK-NEXT:        },
// CHECK-NEXT:        "inner": [
// CHECK-NEXT:         {
// CHECK-NEXT:          "id": "0x{{.*}}",
// CHECK-NEXT:          "kind": "CXXTemporaryObjectExpr",
// CHECK-NEXT:          "range": {
// CHECK-NEXT:           "begin": {
// CHECK-NEXT:            "offset": {{[0-9]+}},
// CHECK-NEXT:            "col": 16,
// CHECK-NEXT:            "tokLen": 1
// CHECK-NEXT:           },
// CHECK-NEXT:           "end": {
// CHECK-NEXT:            "offset": {{[0-9]+}},
// CHECK-NEXT:            "col": 18,
// CHECK-NEXT:            "tokLen": 1
// CHECK-NEXT:           }
// CHECK-NEXT:          },
// CHECK-NEXT:          "type": {
// CHECK-NEXT:           "qualType": "S"
// CHECK-NEXT:          },
// CHECK-NEXT:          "valueCategory": "prvalue",
// CHECK-NEXT:          "ctorType": {
// CHECK-NEXT:           "qualType": "void ()"
// CHECK-NEXT:          },
// CHECK-NEXT:          "hadMultipleCandidates": true,
// CHECK-NEXT:          "constructionKind": "complete"
// CHECK-NEXT:         }
// CHECK-NEXT:        ]
// CHECK-NEXT:       }
// CHECK-NEXT:      ]
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK-NOT: {{^}}Dumping
// CHECK:  "kind": "ExprWithCleanups",
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "offset": {{[0-9]+}},
// CHECK-NEXT:    "col": 18,
// CHECK-NEXT:    "tokLen": 3
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "offset": {{[0-9]+}},
// CHECK-NEXT:    "col": 18,
// CHECK-NEXT:    "tokLen": 3
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "type": {
// CHECK-NEXT:   "qualType": "const int"
// CHECK-NEXT:  },
// CHECK-NEXT:  "valueCategory": "lvalue",
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "MaterializeTemporaryExpr",
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "offset": {{[0-9]+}},
// CHECK-NEXT:      "col": 18,
// CHECK-NEXT:      "tokLen": 3
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "offset": {{[0-9]+}},
// CHECK-NEXT:      "col": 18,
// CHECK-NEXT:      "tokLen": 3
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "const int"
// CHECK-NEXT:    },
// CHECK-NEXT:    "valueCategory": "lvalue",
// CHECK-NEXT:    "extendingDecl": {
// CHECK-NEXT:     "id": "0x{{.*}}",
// CHECK-NEXT:     "kind": "VarDecl",
// CHECK-NEXT:     "name": "i",
// CHECK-NEXT:     "type": {
// CHECK-NEXT:      "qualType": "const int &"
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "storageDuration": "automatic",
// CHECK-NEXT:    "boundToLValueRef": true,
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ImplicitCastExpr",
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "offset": {{[0-9]+}},
// CHECK-NEXT:        "col": 18,
// CHECK-NEXT:        "tokLen": 3
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "offset": {{[0-9]+}},
// CHECK-NEXT:        "col": 18,
// CHECK-NEXT:        "tokLen": 3
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "const int"
// CHECK-NEXT:      },
// CHECK-NEXT:      "valueCategory": "prvalue",
// CHECK-NEXT:      "castKind": "FloatingToIntegral",
// CHECK-NEXT:      "inner": [
// CHECK-NEXT:       {
// CHECK-NEXT:        "id": "0x{{.*}}",
// CHECK-NEXT:        "kind": "FloatingLiteral",
// CHECK-NEXT:        "range": {
// CHECK-NEXT:         "begin": {
// CHECK-NEXT:          "offset": {{[0-9]+}},
// CHECK-NEXT:          "col": 18,
// CHECK-NEXT:          "tokLen": 3
// CHECK-NEXT:         },
// CHECK-NEXT:         "end": {
// CHECK-NEXT:          "offset": {{[0-9]+}},
// CHECK-NEXT:          "col": 18,
// CHECK-NEXT:          "tokLen": 3
// CHECK-NEXT:         }
// CHECK-NEXT:        },
// CHECK-NEXT:        "type": {
// CHECK-NEXT:         "qualType": "double"
// CHECK-NEXT:        },
// CHECK-NEXT:        "valueCategory": "prvalue",
// CHECK-NEXT:        "value": "1"
// CHECK-NEXT:       }
// CHECK-NEXT:      ]
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK-NOT: {{^}}Dumping
// CHECK:  "kind": "ExprWithCleanups",
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "offset": {{[0-9]+}},
// CHECK-NEXT:    "line": 18,
// CHECK-NEXT:    "col": 3,
// CHECK-NEXT:    "tokLen": 4
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "offset": {{[0-9]+}},
// CHECK-NEXT:    "col": 9,
// CHECK-NEXT:    "tokLen": 1
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "type": {
// CHECK-NEXT:   "qualType": "void"
// CHECK-NEXT:  },
// CHECK-NEXT:  "valueCategory": "prvalue",
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CallExpr",
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "offset": {{[0-9]+}},
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "tokLen": 4
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "offset": {{[0-9]+}},
// CHECK-NEXT:      "col": 9,
// CHECK-NEXT:      "tokLen": 1
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void"
// CHECK-NEXT:    },
// CHECK-NEXT:    "valueCategory": "prvalue",
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ImplicitCastExpr",
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "offset": {{[0-9]+}},
// CHECK-NEXT:        "col": 3,
// CHECK-NEXT:        "tokLen": 4
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "offset": {{[0-9]+}},
// CHECK-NEXT:        "col": 3,
// CHECK-NEXT:        "tokLen": 4
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "void (*)(const int &)"
// CHECK-NEXT:      },
// CHECK-NEXT:      "valueCategory": "prvalue",
// CHECK-NEXT:      "castKind": "FunctionToPointerDecay",
// CHECK-NEXT:      "inner": [
// CHECK-NEXT:       {
// CHECK-NEXT:        "id": "0x{{.*}}",
// CHECK-NEXT:        "kind": "DeclRefExpr",
// CHECK-NEXT:        "range": {
// CHECK-NEXT:         "begin": {
// CHECK-NEXT:          "offset": {{[0-9]+}},
// CHECK-NEXT:          "col": 3,
// CHECK-NEXT:          "tokLen": 4
// CHECK-NEXT:         },
// CHECK-NEXT:         "end": {
// CHECK-NEXT:          "offset": {{[0-9]+}},
// CHECK-NEXT:          "col": 3,
// CHECK-NEXT:          "tokLen": 4
// CHECK-NEXT:         }
// CHECK-NEXT:        },
// CHECK-NEXT:        "type": {
// CHECK-NEXT:         "qualType": "void (const int &)"
// CHECK-NEXT:        },
// CHECK-NEXT:        "valueCategory": "lvalue",
// CHECK-NEXT:        "referencedDecl": {
// CHECK-NEXT:         "id": "0x{{.*}}",
// CHECK-NEXT:         "kind": "FunctionDecl",
// CHECK-NEXT:         "name": "func",
// CHECK-NEXT:         "type": {
// CHECK-NEXT:          "qualType": "void (const int &)"
// CHECK-NEXT:         }
// CHECK-NEXT:        },
// CHECK-NEXT:        "qualType": {
// CHECK-NEXT:         "id": "0x{{.*}}",
// CHECK-NEXT:         "kind": "QualType",
// CHECK-NEXT:         "type": {
// CHECK-NEXT:          "qualType": "void (const int &)"
// CHECK-NEXT:         },
// CHECK-NEXT:         "qualifiers": "",
// CHECK-NEXT:         "qualDetails": []
// CHECK-NEXT:        }
// CHECK-NEXT:       }
// CHECK-NEXT:      ]
// CHECK-NEXT:     },
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "MaterializeTemporaryExpr",
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "offset": {{[0-9]+}},
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "tokLen": 1
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "offset": {{[0-9]+}},
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "tokLen": 1
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "const int"
// CHECK-NEXT:      },
// CHECK-NEXT:      "valueCategory": "lvalue",
// CHECK-NEXT:      "storageDuration": "full expression",
// CHECK-NEXT:      "boundToLValueRef": true,
// CHECK-NEXT:      "inner": [
// CHECK-NEXT:       {
// CHECK-NEXT:        "id": "0x{{.*}}",
// CHECK-NEXT:        "kind": "ImplicitCastExpr",
// CHECK-NEXT:        "range": {
// CHECK-NEXT:         "begin": {
// CHECK-NEXT:          "offset": {{[0-9]+}},
// CHECK-NEXT:          "col": 8,
// CHECK-NEXT:          "tokLen": 1
// CHECK-NEXT:         },
// CHECK-NEXT:         "end": {
// CHECK-NEXT:          "offset": {{[0-9]+}},
// CHECK-NEXT:          "col": 8,
// CHECK-NEXT:          "tokLen": 1
// CHECK-NEXT:         }
// CHECK-NEXT:        },
// CHECK-NEXT:        "type": {
// CHECK-NEXT:         "qualType": "const int"
// CHECK-NEXT:        },
// CHECK-NEXT:        "valueCategory": "prvalue",
// CHECK-NEXT:        "castKind": "FloatingToIntegral",
// CHECK-NEXT:        "inner": [
// CHECK-NEXT:         {
// CHECK-NEXT:          "id": "0x{{.*}}",
// CHECK-NEXT:          "kind": "ImplicitCastExpr",
// CHECK-NEXT:          "range": {
// CHECK-NEXT:           "begin": {
// CHECK-NEXT:            "offset": {{[0-9]+}},
// CHECK-NEXT:            "col": 8,
// CHECK-NEXT:            "tokLen": 1
// CHECK-NEXT:           },
// CHECK-NEXT:           "end": {
// CHECK-NEXT:            "offset": {{[0-9]+}},
// CHECK-NEXT:            "col": 8,
// CHECK-NEXT:            "tokLen": 1
// CHECK-NEXT:           }
// CHECK-NEXT:          },
// CHECK-NEXT:          "type": {
// CHECK-NEXT:           "qualType": "float"
// CHECK-NEXT:          },
// CHECK-NEXT:          "valueCategory": "prvalue",
// CHECK-NEXT:          "castKind": "LValueToRValue",
// CHECK-NEXT:          "inner": [
// CHECK-NEXT:           {
// CHECK-NEXT:            "id": "0x{{.*}}",
// CHECK-NEXT:            "kind": "DeclRefExpr",
// CHECK-NEXT:            "range": {
// CHECK-NEXT:             "begin": {
// CHECK-NEXT:              "offset": {{[0-9]+}},
// CHECK-NEXT:              "col": 8,
// CHECK-NEXT:              "tokLen": 1
// CHECK-NEXT:             },
// CHECK-NEXT:             "end": {
// CHECK-NEXT:              "offset": {{[0-9]+}},
// CHECK-NEXT:              "col": 8,
// CHECK-NEXT:              "tokLen": 1
// CHECK-NEXT:             }
// CHECK-NEXT:            },
// CHECK-NEXT:            "type": {
// CHECK-NEXT:             "qualType": "float"
// CHECK-NEXT:            },
// CHECK-NEXT:            "valueCategory": "lvalue",
// CHECK-NEXT:            "referencedDecl": {
// CHECK-NEXT:             "id": "0x{{.*}}",
// CHECK-NEXT:             "kind": "VarDecl",
// CHECK-NEXT:             "name": "f",
// CHECK-NEXT:             "type": {
// CHECK-NEXT:              "qualType": "float"
// CHECK-NEXT:             }
// CHECK-NEXT:            },
// CHECK-NEXT:            "qualType": {
// CHECK-NEXT:             "refId": "0x{{.*}}",
// CHECK-NEXT:             "qualDetails": [
// CHECK-NEXT:              "fpp"
// CHECK-NEXT:             ]
// CHECK-NEXT:            }
// CHECK-NEXT:           }
// CHECK-NEXT:          ]
// CHECK-NEXT:         }
// CHECK-NEXT:        ]
// CHECK-NEXT:       }
// CHECK-NEXT:      ]
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }
