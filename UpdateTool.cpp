#include "../lcf/lcf.h"
#include "../lcf/lcf.c"
/* TODO: why does scalar math get fucked
   TODO: what is wrong with tests */

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
Str8List update_file_content(Arena* arena, str8 file_content, str8 function_prefix) {
    Str8List out = {0};

    str8 Find[FUNCTIONS_Size];
    str8 Repl[FUNCTIONS_Size];
    { /* NOTE: Initialization */
        Find[PREFIX_TYPE] = str8_lit("hmm_");
        Find[PREFIX_FUNCTION] = str8_lit("HMM_");
        if (str8_not_empty(function_prefix)) {
            Find[PREFIX_FUNCTION] = function_prefix;
        }
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
        Repl[FUN_INVERSE] = str8_lit("Inv");
        Find[FUN_R_SQUARE_ROOT] = str8_lit("RSquareRoot"); 
        Repl[FUN_R_SQUARE_ROOT] = str8_lit("InvSqrt"); 
        Find[FUN_SQUARE_ROOT] = str8_lit("SquareRoot");
        Repl[FUN_SQUARE_ROOT] = str8_lit("Sqrt");
        Find[FUN_LENGTH_SQUARED] = str8_lit("Squared");
        Repl[FUN_LENGTH_SQUARED] = str8_lit("Sqr"); /* FIXME: not working for some reason */
        Find[FUN_LENGTH] = str8_lit("Length");
        Repl[FUN_LENGTH] = str8_lit("Len");
        Find[FUN_NORM] = str8_lit("Normalize");
        Repl[FUN_NORM] = str8_lit("Norm");
    }

    /* Match with a bunch of sliding windows, skipping when there can't be a match */
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
        for (u32 t = 0; t < PREFIXES_Size; t++) {  
            if (c == Find[t].str[MatchProgress[t]]) {  
                MatchProgress[t]++;  
                if (MatchProgress[t] == Find[t].len) {  
                    if (t == PREFIX_TYPE) {
                        FoundTypePrefix = true;
                    } else if (t == PREFIX_FUNCTION) {
                        FoundFunctionPrefix = true;
                    }  
                    MatchProgress[t] = 0; 
                }  
            } else {  
                MatchProgress[t] = 0;  
            } 
        } 

        /* Replace hmm_ types */
        if (FoundTypePrefix) {
            for (u32 t = PREFIXES_Size+1; t < TYPES_Size; t++) {  
                if (c == Find[t].str[MatchProgress[t]]) {  
                    MatchProgress[t]++;  
                    if (MatchProgress[t] == Find[t].len) {  
                        Str8List_add(arena, &out,
                                     str8_first(file_content,
                                                i + 1 - Find[t].len - Find[PREFIX_TYPE].len));
                        Str8List_add(arena, &out, Repl[PREFIX_TYPE]);
                        Str8List_add(arena, &out, Repl[t]);
                        file_content = str8_skip(file_content, i+1);
                        i = -1;
                    }  
                } else {  
                    MatchProgress[t] = 0;  
                } 
            } 
        }

        /* If in a HMM_ (or user prefix) function, do function name replacements */
        if (FoundFunctionPrefix) {
            for (u32 t = TYPES_Size+1; t < FUNCTIONS_Size; t++) {  
                if (c == Find[t].str[MatchProgress[t]]) {  
                    MatchProgress[t]++;  
                    if (MatchProgress[t] == Find[t].len) {  
                        Str8List_add(arena, &out, str8_first(file_content, i + 1 - Find[t].len));
                        Str8List_add(arena, &out, Repl[t]);
                        file_content = str8_skip(file_content, i+1);
                        i = -1;

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
                            } else if (c == 'f') {
                                Str8List_add(arena, &out, str8_first(file_content, 1));
                                Str8List_add(arena, &out, str8_lit("F"));
                                file_content = str8_skip(file_content, 2);
                            }
                        }
                    }  
                } else {  
                    MatchProgress[t] = 0;  
                } 
            } 
        }
    }
    Str8List_add(arena, &out, file_content);
    
    return out;
}

int main(int argc, char* argv[]) {
    Arena *tempa = Arena_create_default();

    if (argc == 1) {
        return 1;
    }

    u32 argi = 1;
    str8 arg = str8_from_cstring(argv[argi]);
    str8 prefixmark = str8_lit("prefix=");
    str8 prefix = str8_EMPTY;
    if (str8_has_prefix(arg, prefixmark)) {
        prefix = str8_skip(arg, prefixmark.len);
        argi++;
    }

    for (; argi < argc; argi++) {
        arg = str8_from_cstring(argv[argi]);
        /* TODO: portable version instead */
        str8 file_content = win32_load_entire_file(tempa, arg);
        Str8List result = update_file_content(tempa, file_content, prefix);
        win32_write_file(arg, result);
    }
}
