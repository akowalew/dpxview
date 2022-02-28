#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "dpx.h"

static void
AssertEqualCheck(int A, int B, const char* AStr, const char* BStr, const char* File, int Line)
{
    if(A != B)
    {
        printf("%s:%d: Assertion \"%s != %s\" failed\n", File, Line, AStr, BStr);
        printf("Value of: %d\n", A);
        printf("Expected: %d\n", B);
        exit(-1);
    }
}

#define AssertEqual(a, b) AssertEqualCheck(a, b, #a, #b, __FILE__, __LINE__)

int
main()
{
    AssertEqual(sizeof(DWORD), 4);
    AssertEqual(sizeof(WORD), 2);
    AssertEqual(sizeof(BYTE), 1);
    AssertEqual(sizeof(SINGLE), 4);

    AssertEqual(sizeof(u64), 8);
    AssertEqual(sizeof(i64), 8);
    AssertEqual(sizeof(u32), 4);
    AssertEqual(sizeof(i32), 4);
    AssertEqual(sizeof(u16), 2);
    AssertEqual(sizeof(i16), 2);
    AssertEqual(sizeof(u8), 1);
    AssertEqual(sizeof(i8), 1);

    AssertEqual(sizeof(dpx_file_header), 768);
    AssertEqual(sizeof(dpx_image_header), 640);

    return 0;
}
