/** LCF stuff **/
/* I used my personally library when writing this so I am dumping the necessary things here
   so that it's all in one file. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Types */
#define global static
#define internal static
typedef int32_t s32; global s32 s32_MAX = 0x7FFFFFFF; global s32 s32_MIN = -1 - 0x7FFFFFFF;
typedef int64_t s64; global s64 s64_MAX = 0x7FFFFFFFFFFFFFFF; global s64 s64_MIN = -1 - 0x7FFFFFFFFFFFFFFF;
typedef uint32_t u32; global u32 u32_MAX = 0xFFFFFFFF; global u32 u32_MIN = 0;
typedef uint64_t u64; global u64 u64_MAX = 0xFFFFFFFFFFFFFFFF; global u64 u64_MIN = 0;
typedef u32 b32;
typedef u64 b64;
#define MIN(a,b) (((a)<(b))?(a):(b))
#define CLAMPTOP(a,b) MIN(a,b)

/* Memory */
struct lcf_Arena {
    u64 pos;
    u64 size;
    u64 alignment;
    u64 commited_pos;
};
typedef struct lcf_Arena Arena;
#define KB(x) ((x) << 10)
#define GB(x) ((x) << 30)
Arena* Arena_create(u64 size);
void* Arena_take(Arena *a, u64 size);
void* Arena_take_custom(Arena *a, u64 size, u64 alignment);
#define Arena_take_array(a, type, count) ((type*) Arena_take(a, sizeof(type)*count))
void Arena_reset_all(Arena *a);

#define LCF_MEMORY_PROVIDE_MEMORY "stdlib"
#define LCF_MEMORY_RESERVE_MEMORY(name) void* name(u64 size)
#define LCF_MEMORY_COMMIT_MEMORY(name) b32 name(void* memory, u64 size)
#define LCF_MEMORY_DECOMMIT_MEMORY(name) void name(void* memory, u64 size)
#define LCF_MEMORY_FREE_MEMORY(name) void name(void* memory, u64 size)
internal LCF_MEMORY_RESERVE_MEMORY(_lcf_memory_default_reserve) {
    return malloc(size);
}
internal LCF_MEMORY_COMMIT_MEMORY(_lcf_memory_default_commit) {
    (void) size, memory;
    return 1; /* malloc commits memory automatically */
}
internal LCF_MEMORY_DECOMMIT_MEMORY(_lcf_memory_default_decommit) {
    (void) size, memory;
    return;
}
internal LCF_MEMORY_FREE_MEMORY(_lcf_memory_default_free) {
    (void) size;
    free(memory);
}
#define LCF_MEMORY_reserve _lcf_memory_default_reserve
#define LCF_MEMORY_commit _lcf_memory_default_commit
#define LCF_MEMORY_decommit _lcf_memory_default_decommit
#define LCF_MEMORY_free _lcf_memory_default_free
#define LCF_MEMORY_RESERVE_SIZE GB(1)
#define LCF_MEMORY_COMMIT_SIZE KB(4)
 #define LCF_MEMORY_ALIGNMENT (sizeof(void*))

Arena* Arena_create(u64 size) {
    Arena* a = (Arena*) LCF_MEMORY_reserve(size);
    LCF_MEMORY_commit(a, LCF_MEMORY_COMMIT_SIZE);
    a->size = size;
    a->pos = sizeof(Arena);
    a->commited_pos = LCF_MEMORY_COMMIT_SIZE;
    a->alignment = LCF_MEMORY_ALIGNMENT;
    return a;
}
#define B_PTR(p) (u8*)(p)

internal b32 is_power_of_2(u64 x) {
    return ((x & (x-1)) == 0);
}
internal u64 next_alignment(u64 ptr, u64 alignment) {
    /* Fast replacement for mod because alignment is power of 2 */
    u64 modulo = ptr & (alignment-1);

    if (modulo != 0) {
        ptr += alignment - modulo;
    }

    return ptr;
}
void* Arena_take_custom(Arena *a, u64 size, u64 alignment) {
    void* result = 0;
    
    /* Align pos pointer to check if "size" can fit */
    u64 mem = (u64) a;
    u64 aligned_pos = next_alignment(mem + a->pos, alignment) - mem;
    u64 new_pos = aligned_pos + size;
        
    /* Check that there is space */
    if (new_pos < a->size) {
        u64 commited_pos = a->commited_pos;

        /* Commit memory if needed */
        if (new_pos > commited_pos) {
            u64 new_commited_pos = next_alignment(mem + new_pos, LCF_MEMORY_COMMIT_SIZE)-mem;
            if (LCF_MEMORY_commit(a, new_commited_pos)) {
                a->commited_pos = commited_pos = new_commited_pos;
            }
        }

        /* If enough memory is commited, set result and pos. */
        if (new_pos <= commited_pos) {
            result = (void*)(mem + aligned_pos);
            a->pos = new_pos;
        }
    }
    return result;
}
void* Arena_take(Arena *a, u64 size) {
    return Arena_take_custom(a, size, LCF_MEMORY_ALIGNMENT);
}
void Arena_reset_all(Arena *a) {
    a->pos = 0;
}

/* String */
typedef char chr8;
struct str8 { 
    u64 len;
    chr8 *str;
};
typedef struct str8 str8;
#define str8_PRINTF_ARGS(s) (int)(s).len, (s).str
#define str8_lit(s) str8_from((chr8*)(s),(u64)sizeof(s)-1) /* -1 to exclude null character */
#define str8_is_empty(s) ((b32)((s).len == 0))
#define LCF_STRING_NO_MATCH 0x8000000000000000
#define str8_iter_custom(s, i, c)                           \
    s64 i = 0;                                              \
    chr8 c = s.str[i];                                      \
    for (; (i < (s64) s.len); i++, c = s.str[i])

#define str8_iter(s) str8_iter_custom(s, i, c)

str8 str8_from(chr8* s, u64 len);
str8 str8_from_cstring(chr8 *cstr);
str8 str8_first(str8 s, u64 len);
str8 str8_skip(str8 s, u64 len);
b32 chr8_is_whitespace(chr8 c);
b32 str8_contains_char(str8 s, chr8 c);
u64 str8_char_location(str8 s, chr8 c);

#define RET_STR8(s,l)             \
    str8 _str8;                   \
    _str8.str = (s);              \
    _str8.len = (l);              \
    return _str8
str8 str8_from(chr8* s, u64 len) {
    RET_STR8(s, len);
}
str8 str8_from_cstring(chr8 *cstr) {
    chr8* p2 = cstr;
    while(*p2 != 0)
        p2++;
    RET_STR8(cstr, (u64)(p2 - cstr));
}
str8 str8_first(str8 s, u64 len) {
    u64 len_clamped = CLAMPTOP(len, s.len);
    RET_STR8(s.str, len_clamped);
}
str8 str8_skip(str8 s, u64 len) {
    u64 len_clamped = CLAMPTOP(len, s.len);
    RET_STR8(s.str + len_clamped, s.len - len_clamped);
}
b32 chr8_is_whitespace(chr8 c) {
    switch (c) {
    case ' ':
    case '\n':
    case '\t':
    case '\r':
        return true;
    default:
        return false;
    }
}
b32 str8_contains_char(str8 s, chr8 find) {
    return str8_char_location(s,find) != LCF_STRING_NO_MATCH;
}
u64 str8_char_location(str8 s, chr8 find) {
    str8_iter(s) {
        if (c == find) {
            return i;
        }
    }
    return LCF_STRING_NO_MATCH;
}
#undef RET_STR8

struct Str8Node {
    struct Str8Node *next;
    struct str8 str;
};
struct Str8List {
    struct Str8Node *first;
    struct Str8Node *last;
    u64 count;
    u64 total_len;
};
typedef struct Str8Node Str8Node;
typedef struct Str8List Str8List;

void Str8List_add_node(Str8List *list, Str8Node *n);
void Str8List_add(Arena *arena, Str8List *list, str8 str);
void Str8List_add_node(Str8List *list, Str8Node *n) {
    if (list->last) {
        list->last->next = n;
    } else {
        list->first = n;
    }
    list->last = n;
    list->count++;
    list->total_len += n->str.len;
}
void Str8List_add(Arena *arena, Str8List *list, str8 str) {
    Str8Node *n = Arena_take_array(arena, Str8Node, 1);
    n->str = str;
    n->next = 0;
    Str8List_add_node(list, n);
}

/* CRT - stdio */
str8 stdio_load_entire_file(Arena *arena, str8 filepath);
b32 stdio_write_file(str8 filepath, Str8List text);

str8 stdio_load_entire_file(Arena *arena, str8 filepath) {
    str8 file_content = {0};

    FILE *file = fopen(filepath.str, "rb");
    if (file != 0) {
        fseek(file, 0, SEEK_END);
        u64 file_len = ftell(file);
        fseek(file, 0, SEEK_SET);
        file_content.str = (chr8*) Arena_take(arena, file_len+1);
        if (file_content.str != 0) {
            file_content.len = file_len;
            fread(file_content.str, 1, file_len, file);
            file_content.str[file_content.len] = 0;
        }
        fclose(file);
    }
    return file_content;
}
b32 stdio_write_file(str8 filepath, Str8List text) {
    u64 bytes_written = 0;
    FILE *file = fopen(filepath.str, "wb");
    if (file != 0) {
        Str8Node* n = text.first;
        for (s64 i = 0; i < text.count; i++, n = n->next) {
            if (!fwrite(n->str.str, n->str.len, 1, file)) {
                break;
            }
            bytes_written += n->str.len;
        }
        fclose(file);
    }
    return bytes_written == text.total_len;
}

/** HMM2.0 Update Tool **/
enum Targets {
    /* hmm_ and HMM_ prefixes */
    PREFIX_TYPE, PREFIX_FUNCTION,
    PREFIXES_Size,
    /* Struct/Union types */
    TYPE_VEC, TYPE_MAT, TYPE_QUATERNION, TYPE_BOOL,
    TYPES_Size,
    /* Types in Function Names */
    FUN_VEC, FUN_MAT, FUN_QUATERNION,  
    /* Function Names for Common Operations */
    FUN_EQUALS, FUN_SUBTRACT, FUN_MULTIPLY, FUN_DIVIDE,
    FUN_INVERSE, FUN_R_SQUARE_ROOT, FUN_SQUARE_ROOT,
    FUN_LENGTH_SQUARED, FUN_LENGTH, FUN_FAST_NORM, FUN_NORM,
    FUN_SLERP, FUN_BY,
    FUN_LINEAR_COMBINE_SSE, FUN_TRANSPOSE,
    FUNCTIONS_Size,
    /* Handedness */
    HAND_PERSPECTIVE, HAND_ROTATE,
    HAND_ORTHO, HAND_LOOK_AT, HAND_QUAT_AXIS_ANGLE, HAND_MAT_TO_QUAT,
    HAND_Size,
};

Str8List update_file_content(Arena* arena, str8 file_content) {
    Str8List out = {0};

    str8 Find[HAND_Size];
    str8 Repl[HAND_Size];
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
        
        Find[FUN_SLERP] = str8_lit("Slerp");
        Repl[FUN_SLERP] = str8_lit("SLerp");
        Find[FUN_BY] = str8_lit("By");
        Repl[FUN_BY] = str8_lit("");
        Find[FUN_LINEAR_COMBINE_SSE] = str8_lit("LinearCombineSSE"); /* TODO: emit warning */
        Repl[FUN_LINEAR_COMBINE_SSE] = str8_lit("LinearCombineV4M4");
        Find[FUN_TRANSPOSE] = str8_lit("Transpose");
        Repl[FUN_TRANSPOSE] = str8_lit("TransposeM4");
        Find[FUN_FAST_NORM] = str8_lit("Fast"); /* TODO: emit warning, lower precision. */
        Repl[FUN_FAST_NORM] = str8_lit("");
        Find[FUN_NORM] = str8_lit("Normalize");
        Repl[FUN_NORM] = str8_lit("Norm");
    
        Find[HAND_PERSPECTIVE] = str8_lit("Perspective");
        Find[HAND_ROTATE] = str8_lit("Rotate");
        Find[HAND_ORTHO] = str8_lit("Orthographic");
        Find[HAND_LOOK_AT] = str8_lit("LookAt");
        Find[HAND_QUAT_AXIS_ANGLE] = str8_lit("FromAxisAngle");
        Find[HAND_MAT_TO_QUAT] = str8_lit("ToQuaternion");
    }

    /* Match with a bunch of sliding windows, skipping when there can't be a match */
    u64 MatchProgress[HAND_Size] = {0};
    b32 FoundTypePrefix = false;
    b32 FoundFunctionPrefix = false;
    u64 Line = 1;
    str8_iter(file_content) {
        if (c == '\n') {
            Line++;
        }
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
                        MatchProgress[t] = 0;
                        printf("\t[%lld]: Find: %.*s, Repl: %.*s.\n", Line, str8_PRINTF_ARGS(Find[t]), str8_PRINTF_ARGS(Repl[t]));
                        Str8List_add(arena, &out,
                                     str8_first(file_content,
                                                i + 1 - (Find[t].len + Find[PREFIX_TYPE].len)));
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

        /* If in a HMM_ function, do function name replacements */
        if (FoundFunctionPrefix) {
            for (u32 t = TYPES_Size+1; t < FUNCTIONS_Size; t++) {  
                if (c == Find[t].str[MatchProgress[t]]) {  
                    MatchProgress[t]++;  
                    if (MatchProgress[t] == Find[t].len) {  
                        MatchProgress[t] = 0;
                        printf("\t[%lld]: Find: %.*s, Repl: %.*s.\n", Line, str8_PRINTF_ARGS(Find[t]), str8_PRINTF_ARGS(Repl[t]));
                        Str8List_add(arena, &out, str8_first(file_content, i + 1 - Find[t].len));
                        Str8List_add(arena, &out, Repl[t]);
                        file_content = str8_skip(file_content, i+1);
                        i = -1;

                        /* NOTE(lcf): Special case because Find[] overlaps here */
                        if (t == FUN_R_SQUARE_ROOT) {
                            MatchProgress[FUN_SQUARE_ROOT] = 0;
                        }

                        if (t == FUN_LINEAR_COMBINE_SSE) {
                            printf("\t[%lld]: HMM_LinearCombineSSE is now HMM_LinearCombineV4M4, and will now use a fallback method when SSE is not available. \n\tYou no longer need to check for the availability of SSE.\n", Line);
                        }

                        if (t == FUN_VEC) {
                            /* NOTE(lcf): if pattern is Vec2i, this is now i */
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
                        } else if (t == FUN_MAT) {
                            /* if pattern is Mat4d, this is now d */
                            c = file_content.str[1];
                            if (c == 'd') {
                                Str8List_add(arena, &out, str8_first(file_content, 1));
                                Str8List_add(arena, &out, str8_lit("D"));
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

        /* Handedness cases. */
        if (FoundFunctionPrefix) {
            for (u32 t = FUNCTIONS_Size+1; t < HAND_Size; t++) {  
                if (c == Find[t].str[MatchProgress[t]]) {  
                    MatchProgress[t]++;  
                    if (MatchProgress[t] == Find[t].len) {
                        MatchProgress[t] = 0;
                        
                        chr8 check = file_content.str[i+1];
                        if (check == '(') {
                            printf("\t[%lld]: Find: %.*s, Appending: _RH for old default handedness.\n", Line, str8_PRINTF_ARGS(Find[t]));
                            Str8List_add(arena, &out, str8_first(file_content, i + 1));
                            Str8List_add(arena, &out, str8_lit("_RH("));
                            file_content = str8_skip(file_content, i+2);
                            i = -1;

                            if (t == HAND_PERSPECTIVE || t == HAND_ROTATE) {
                                printf("\t[%lld]: ", Line);
                                if (t == HAND_PERSPECTIVE) {
                                    printf("HMM_Perspective_RH()");
                                } else {
                                    printf("HMM_Rotate_RH()");
                                }
                                printf(" now takes Radians. Wrapping Degrees with HMM_AngleDeg()\n");
                                u64 end_arg = str8_char_location(file_content, ',');
                                if (end_arg != LCF_STRING_NO_MATCH) {
                                    Str8List_add(arena, &out, str8_lit("HMM_AngleDeg("));
                                    Str8List_add(arena, &out, str8_first(file_content, end_arg));
                                    Str8List_add(arena, &out, str8_lit(")"));
                                    file_content = str8_skip(file_content, end_arg);
                                } 
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
    Arena *tempa = Arena_create(GB(1));

    if (argc == 1) {
        return 1;
    }

    s32 argi = 1;
    str8 arg = str8_from_cstring(argv[argi]);

    for (; argi < argc; argi++) {
        arg = str8_from_cstring(argv[argi]);
        str8 file_content = stdio_load_entire_file(tempa, arg);
        if (str8_is_empty(file_content)) {
            printf("X - Invalid file name: %.*s\n\n", str8_PRINTF_ARGS(arg));
            continue;
        }
        printf("O - Updating file: %.*s -------------------\n", str8_PRINTF_ARGS(arg));
        Str8List result = update_file_content(tempa, file_content);
        printf("\n");
        stdio_write_file(arg, result);
        
        Arena_reset_all(tempa);
    }

    return 0;
}
