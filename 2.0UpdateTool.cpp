#include "../lcf/lcf.h"
#include "../lcf/lcf.c"

/* NOTE(lcf): Earlier Targets have priority. */
enum Targets {
    /* Types in Function Names */
    FUN_VEC, FUN_MAT, FUN_QUATERNION, FUN_FLOAT, 
    /* Function Names for Common Operations */
    FUN_EQUALS, FUN_SUBTRACT, FUN_MULTIPLY, FUN_DIVIDE,
    FUN_INVERSE, FUN_R_SQUARE_ROOT, FUN_SQUARE_ROOT,
    FUN_LENGTH_SQUARED, FUN_LENGTH, FUN_NORM,
    /* Struct/Union types */
    TYPE_VEC, TYPE_MAT, TYPE_QUATERNION, TYPE_BOOL,

    Targets_SIZE
};
str8 update_file_content(Arena* arena, str8 file_content) {
    Str8List out = {0};

    str8 Find[Targets_SIZE];
    str8 Repl[Targets_SIZE];
    { /* NOTE: Initialization */
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

        Find[TYPE_VEC] = str8_lit("hmm_vec");
        Repl[TYPE_VEC] = str8_lit("HMM_Vec");

        Find[TYPE_MAT] = str8_lit("hmm_mat");
        Repl[TYPE_MAT] = str8_lit("HMM_Mat");

        Find[TYPE_QUATERNION] = str8_lit("hmm_quaternion");
        Repl[TYPE_QUATERNION] = str8_lit("HMM_Quat");

        Find[TYPE_BOOL] = str8_lit("hmm_bool");
        Repl[TYPE_BOOL] = str8_lit("HMM_Bool");
    }

    /* Match with a bunch of sliding windows, skipping when there can't be a match */
    s64 Skip[Targets_SIZE] = {0};
    u64 MatchProgress[Targets_SIZE] = {0};
    str8_iter(file_content) {
        for (u32 t = 0; t < Targets_SIZE; t++) {
            if (Skip[t] > 0) {
                Skip[t]--;
                continue;            
            } else if (c == Find[t].str[MatchProgress[t]]) {
                MatchProgress[t]++;
                if (MatchProgress[t] == Find[t].len) {
                    /* TODO: Do replacement */
                    /* Everything up to what we are replacing */
                    Str8List_add(arena, &out, str8_first(file_content, i + 1 - Find[t].len));

                    Str8List_add(arena, &out, Repl[t]);

                    file_content = str8_skip(file_content, i+1);
                    i = 0;

                    if (t == FUN_VEC) {
                        c = file_content.str[1]; /* if pattern is vec2i, this is now i */
                        if (c == 'i') {
                            Str8List_add(arena, &out, str8_first(file_content, 1));
                            Str8List_add(arena, &out, str8_lit("I"));
                            file_content = str8_skip(file_content, 2);
                        }
                        if (c == 'v') {
                            Str8List_add(arena, &out, str8_first(file_content, 1));
                            Str8List_add(arena, &out, str8_lit("V"));
                            file_content = str8_skip(file_content, 2);
                        }
                    }
                }
            } else {
                MatchProgress[t] = 0;
                Skip[t] = 0;
                // Skip[t] = Find[t].len - 1 - MatchProgress[t];
            }
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
    
    hmm_vec2 z = HMM_Subtract(y, x);
}
)");

    printf("BEFORE:\n%s", file_content.str);
    str8 result = update_file_content(tempa, file_content);
    printf("AFTER:\n%s", result.str);
    if (0) {}
}
