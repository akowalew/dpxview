#define ArrayCount(x) (int)(sizeof(x)/sizeof(x[0]))

static u16
Big2LittleU16(u16 Value)
{
    u16 SrcByte0 = (u16)(Value & 0x00FF);
    u16 SrcByte1 = (u16)(Value & 0xFF00);

    u16 DstByte0 = (u16)(SrcByte1 >> 8);
    u16 DstByte1 = (u16)(SrcByte0 << 8);

    u16 Result = (DstByte0 | DstByte1);

    return Result;
}

static u32
Big2LittleU32(u32 Value)
{
    /* TODO: Do it in assembly */

    u32 SrcByte0 = (Value & 0x000000FF);
    u32 SrcByte1 = (Value & 0x0000FF00);
    u32 SrcByte2 = (Value & 0x00FF0000);
    u32 SrcByte3 = (Value & 0xFF000000);

    u32 DstByte0 = (SrcByte3 >> 24);
    u32 DstByte1 = (SrcByte2 >> 8);
    u32 DstByte2 = (SrcByte1 << 8);
    u32 DstByte3 = (SrcByte3 << 24);

    u32 Result = (DstByte0 | DstByte1 | DstByte2 | DstByte3);

    return Result;
}

static void
AssertionFailed(const char* Expression, const char* File, int Line)
{
    fprintf(stderr, "%s[%d]: Assertion '%s' failed\n", File, Line, Expression);
    exit(-1);
}

#define Assert(x) if(!(x)) { AssertionFailed(#x, __FILE__, __LINE__); }

static void
CopyMemory(void* Dst, void* Src, sz Size)
{
    Assert((Size % sizeof(int)) == 0);
    int* Dsti = (int*) Dst;
    int* Srci = (int*) Src;

    int* DstiEnd = Dsti + Size / sizeof(int);
    while(Dsti != DstiEnd)
    {
        *(Dsti++) = *(Srci++);
    }
}

#define Copy(A, B) \
{ \
    Assert(sizeof(A) == sizeof(B)); \
    CopyMemory(A, B, sizeof(A)); \
} \

