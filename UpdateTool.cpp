#include "../lcf/lcf.h"
#include "../lcf/lcf.c"

#define CHECK_MATCHES(start_range, end_range, action)  \
    for (u32 t = start_range; t < end_range; t++) {  \
        if (Skip[t] > 0) {  \
            Skip[t] -= 1;  \
            continue;  \
        } else if (c == Find[t].str[MatchProgress[t]]) {  \
            MatchProgress[t]++;  \
            if (MatchProgress[t] == Find[t].len) {  \
                action  \
                break;  \
            }  \
       } else {  \
           MatchProgress[t] = 0;  \
           Skip[t] = 0; \
        } \
    } /* end CHECK_MATCHES */

enum Targets {
    PREFIX_TYPE, PREFIX_FUNCTION,
    PREFIXES_Size,
    /* Struct/Union types */
    TYPE_VEC, TYPE_MAT, TYPE_QUATERNION, TYPE_BOOL,
    TYPES_Size,
    /* Types in Function Names */
    FUN_VEC, FUN_MAT, FUN_QUATERNION, FUN_FLOAT, 
    /* Function Names for Common Operations */
    FUN_EQUALS, FUN_SUBTRACT, FUN_MULTIPLY, FUN_DIVIDE,
    FUN_INVERSE, FUN_R_SQUARE_ROOT, FUN_SQUARE_ROOT,
    FUN_LENGTH_SQUARED, FUN_LENGTH, FUN_NORM,
    FUNCTIONS_Size
};
str8 update_file_content(Arena* arena, str8 file_content) {
    Str8List out = {0};

    str8 Find[FUNCTIONS_Size];
    str8 Repl[FUNCTIONS_Size];
    { /* NOTE: Initialization */
        Find[PREFIX_TYPE] = str8_lit("hmm_");
        Find[PREFIX_FUNCTION] = str8_lit("HMM_");
        Repl[PREFIX_TYPE] = Find[PREFIX_FUNCTION];
        
        Find[TYPE_VEC] = str8_lit("vec");
        Repl[TYPE_VEC] = str8_lit("Vec");

        Find[TYPE_MAT] = str8_lit("mat");
        Repl[TYPE_MAT] = str8_lit("Mat");

        Find[TYPE_QUATERNION] = str8_lit("quaternion");
        Repl[TYPE_QUATERNION] = str8_lit("Quat");

        Find[TYPE_BOOL] = str8_lit("bool");
        Repl[TYPE_BOOL] = str8_lit("Bool");
        
        Find[FUN_VEC] = str8_lit("Vec");
        Repl[FUN_VEC] = str8_lit("V");

        Find[FUN_MAT] = str8_lit("Mat");
        Repl[FUN_MAT] = str8_lit("M");

        Find[FUN_QUATERNION] = str8_lit("Quaternion");
        Repl[FUN_QUATERNION] = str8_lit("Q");

        Find[FUN_FLOAT] = str8_lit("Float");
        Repl[FUN_FLOAT] = str8_lit("F");
         
        Find[FUN_EQUALS] = str8_lit("Equals");
        Repl[FUN_EQUALS] = str8_lit("Eq");

        Find[FUN_SUBTRACT] = str8_lit("Subtract");
        Repl[FUN_SUBTRACT] = str8_lit("Sub");

        Find[FUN_MULTIPLY] = str8_lit("Multiply");
        Repl[FUN_MULTIPLY] = str8_lit("Mul");

        Find[FUN_DIVIDE] = str8_lit("Divide");
        Repl[FUN_DIVIDE] = str8_lit("Div");

        Find[FUN_INVERSE] = str8_lit("Inverse");
        Repl[FUN_INVERSE] = str8_lit("Invq");

        Find[FUN_R_SQUARE_ROOT] = str8_lit("RSquareRoot"); 
        Repl[FUN_R_SQUARE_ROOT] = str8_lit("InvSqrt"); 

        Find[FUN_SQUARE_ROOT] = str8_lit("SquareRoot");
        Repl[FUN_SQUARE_ROOT] = str8_lit("Sqrt");

        Find[FUN_LENGTH_SQUARED] = str8_lit("LengthSquared");
        Repl[FUN_LENGTH_SQUARED] = str8_lit("SqrLen");

        Find[FUN_LENGTH] = str8_lit("Length");
        Repl[FUN_LENGTH] = str8_lit("Len");

        Find[FUN_NORM] = str8_lit("Normalize");
        Repl[FUN_NORM] = str8_lit("Norm");

    }

    /* Match with a bunch of sliding windows, skipping when there can't be a match */
    s64 Skip[FUNCTIONS_Size] = {0};
    u64 MatchProgress[FUNCTIONS_Size] = {0};
    b32 FoundTypePrefix = false;
    b32 FoundFunctionPrefix = false;
    
    str8_iter(file_content) {
        if (FoundTypePrefix || FoundFunctionPrefix) {
            if (chr8_is_whitespace(c)
                || str8_contains_char(str8_lit("(){}[]:;,.<>~?!@#$%^&+-*/'\""), c)) {
                FoundTypePrefix = false;
                FoundFunctionPrefix = false;
            }
        }

        CHECK_MATCHES(0, PREFIXES_Size, {
                if (t == PREFIX_TYPE) {
                    FoundTypePrefix = true;
                } else if (t == PREFIX_FUNCTION) {
                    FoundFunctionPrefix = true;
                }
            });

        if (FoundTypePrefix) {
            CHECK_MATCHES(PREFIXES_Size+1, TYPES_Size, {
                    Str8List_add(arena, &out,
                                 str8_first(file_content,
                                            i + 1 - Find[t].len - Find[PREFIX_TYPE].len));
                    Str8List_add(arena, &out, Repl[PREFIX_TYPE]);
                    Str8List_add(arena, &out, Repl[t]);
                    file_content = str8_skip(file_content, i+1);
                    i = 0;
                });
        }

        /* If in a HMM_ function, do function name replacements */
        if (FoundFunctionPrefix) {
            CHECK_MATCHES(TYPES_Size+1, FUNCTIONS_Size, {
                    Str8List_add(arena, &out, str8_first(file_content, i + 1 - Find[t].len));
                    Str8List_add(arena, &out, Repl[t]);
                    file_content = str8_skip(file_content, i+1);
                    i = 0;

                    if (t == FUN_VEC) {
                        /* if pattern is vec2i, this is now i */
                        c = file_content.str[1];
                        if (c == 'i') {
                            Str8List_add(arena, &out, str8_first(file_content, 1));
                            Str8List_add(arena, &out, str8_lit("I"));
                            file_content = str8_skip(file_content, 2);
                        } else if (c == 'v') {
                            Str8List_add(arena, &out, str8_first(file_content, 1));
                            Str8List_add(arena, &out, str8_lit("V"));
                            file_content = str8_skip(file_content, 2);
                        }
                    }
                });
        }
    }
    Str8List_add(arena, &out, file_content);
    
    return Str8List_join(arena, out, str8_lit(""), str8_lit(""), str8_lit(""));
}

int main() {
    Arena *tempa = Arena_create_default();
    str8 file_content = str8_lit(R"(
#include "../HandmadeTest.h"

... Some normal code ...
{
    hmm_vec2 x = HMM_Vec2i(1, 2);
    hmm_vec2 y = HMM_Vec2(3.0, 5.0);
    
    hmm_vec2 Vector = HMM_Subtract(y, x);
}
)");

    printf("BEFORE:\n%s", file_content.str);
    str8 result = update_file_content(tempa, file_content);
    printf("AFTER:\n%s", result.str);
    if (0) {}
}
