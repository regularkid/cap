#define LOG(s, ...) printf(s,  __VA_ARGS__); printf("\n");
#define COMPILE_ERROR(s, ...) LOG("[Compile Error] "##s, __VA_ARGS__); printf("\n");
#define RUNTIME_ERROR(s, ...) LOG("[Runtime Error] "##s, __VA_ARGS__); printf("\n");