typedef struct
{
    DWORD Magic;            /* Magic number */
    DWORD ImageOffset;      /* Offset to start of image data in bytes */
    char Version[8];        /* Version stamp of header format */
    DWORD FileSize;         /* Total DPX file size in bytes */
    DWORD DittoKey;         /* Image content specifier */
    DWORD GenericSize;      /* Generic section header length in bytes */
    DWORD IndustrySize;     /* Industry-specific header length in bytes */
    DWORD UserSize;         /* User-defined data length in bytes */
    char  FileName[100];    /* Name of DPX file */
    char  TimeDate[24];     /* Time and date of file creation */
    char  Creator[100];     /* Name of file creator */
    char  Project[200];     /* Name of project */
    char  Copyright[200];   /* File contents copyright information */
    DWORD EncryptKey;       /* Encryption key */
    char  Reserved[104];    /* Reserved field used for padding */
} dpx_file_header;

typedef enum
{
    DPX_LittleEndian = 0x53445058,
    DPX_BigEndian = 0x58504453,
} dpx_format;

typedef enum
{
    DPX_Orientation_LeftToRightTopToBottom = 0,
    DPX_Orientation_RightToLeftTopToBottom = 1,
    DPX_Orientation_LeftToRightBottomToTop = 2,
    DPX_Orientation_RightToLeftBottomToTop = 3,
    DPX_Orientation_TopToBottomLeftToRight = 4,
    DPX_Orientation_TopToBottomRightToLeft = 5,
    DPX_Orientation_BottomToTopLeftToRight = 6,
    DPX_Orientation_BottomToTopRightToLeft = 7,
} dpx_orientation;

typedef enum
{
    DPX_Unsigned = 0,
    DPX_Signed = 1,
} dpx_signedness;

typedef enum
{
    DPX_Descriptor_UserDefined = 0,
    DPX_Descriptor_Red = 1,
    DPX_Descriptor_Green = 2,
    DPX_Descriptor_Blue = 3,
    DPX_Descriptor_Alpha = 4,
    DPX_Descriptor_Luminance = 6,
    DPX_Descriptor_Chrominance = 7,
    DPX_Descriptor_Depth = 8,
    DPX_Descriptor_CompositeVideo = 9,
    DPX_Descriptor_RGB = 50,
    DPX_Descriptor_RGBA = 51,
    DPX_Descriptor_ABGR = 52,
    DPX_Descriptor_CbYCrY = 100,
    DPX_Descriptor_CbYaCrYa = 101,
    DPX_Descriptor_CbYCr = 102,
    DPX_Descriptor_CbYCra = 103,
    DPX_Descriptor_UserDefined2ComponentElement = 150,
    DPX_Descriptor_UserDefined3ComponentElement = 151,
    DPX_Descriptor_UserDefined4ComponentElement = 152,
    DPX_Descriptor_UserDefined5ComponentElement = 153,
    DPX_Descriptor_UserDefined6ComponentElement = 154,
    DPX_Descriptor_UserDefined7ComponentElement = 155,
    DPX_Descriptor_UserDefined8ComponentElement = 156,
} dpx_descriptor;

typedef enum
{
    DPX_Transfer_UserDefined = 0,
    DPX_Transfer_PrintingDensity = 1,
    DPX_Transfer_Linear = 2,
    DPX_Transfer_Logarithmic = 3,
    DPX_Transfer_UnspecifiedVideo = 4,
    DPX_Transfer_SMPTE240M = 5,
    DPX_Transfer_CCIR709_1 = 6,
    DPX_Transfer_CCIR601_2_System_BorG = 7,
    DPX_Transfer_CCIR601_2_System_M = 8,
    DPX_Transfer_NTSC_CompositeVideo = 9,
    DPX_Transfer_PAL_CompositeVideo = 10,
    DPX_Transfer_Z_Linear = 11,
    DPX_Transfer_Z_Homogeneous = 12,
} dpx_transfer;

typedef enum
{
    DPX_Colorimetric_UserDefined = 0,
    DPX_Colorimetric_PrintingDensity = 1,
    DPX_Colorimetric_UnspecifiedVideo = 4,
    DPX_Colorimetric_SMPTE240M = 5,
    DPX_Colorimetric_CCIR709_1 = 6,
    DPX_Colorimetric_CCIR601_2_System_BorG = 7,
    DPX_Colorimetric_CCIR601_2_System_M = 8,
    DPX_Colorimetric_NTSC_CompositeVideo = 9,
    DPX_Colorimetric_PAL_CompositeVideo = 10,
} dpx_colorimetric;

typedef enum
{
    DPX_Packed_32Bit = 0,
    DPX_Filled_32Bit = 1,
} dpx_packing;

typedef enum
{
    DPX_Encoding_None = 0,
    DPX_Encoding_RLE = 1,
} dpx_encoding;

typedef struct
{
    DWORD  DataSign;          /* Data sign extension */
    DWORD  LowData;           /* Reference low data code value */
    SINGLE LowQuantity;       /* Reference low quantity represented */
    DWORD  HighData;          /* Reference high data code value */
    SINGLE HighQuantity;      /* Reference high quantity represented */
    BYTE   Descriptor;        /* Descriptor for image element */
    BYTE   Transfer;          /* Transfer characteristics for element */
    BYTE   Colorimetric;      /* Colormetric specification for element */
    BYTE   BitSize;           /* Bit size for element */
    WORD   Packing;           /* Packing for element */
    WORD   Encoding;          /* Encoding for element */
    DWORD  DataOffset;        /* Offset to data of element */
    DWORD  EndOfLinePadding;  /* End of line padding used in element */
    DWORD  EndOfImagePadding; /* End of image padding used in element */
    char   Description[32];   /* Description of element */
} dpx_image_element;

typedef struct
{
    WORD  Orientation;            /* Image orientation */
    WORD  NumberElements;         /* Number of image elements */
    DWORD PixelsPerLine;          /* Pixels per line */
    DWORD LinesPerElement;        /* Lines per image element */
    dpx_image_element ImageElement[8];
    BYTE Reserved[52];            /* Reserved field used for padding */
} dpx_image_header;
