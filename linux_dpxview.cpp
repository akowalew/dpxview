#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "types.h"
#include "dpx.h"

#include "util.cpp"

static void
PrintInfoDPX(dpx_file_header* FileHeader, dpx_image_header* ImageHeader)
{
    const char* EndianString = "unknown";
    switch(FileHeader->Magic)
    {
        case DPX_LittleEndian: EndianString = "little"; break;
        case DPX_BigEndian: EndianString = "big"; break;
    }

    printf("\n======== DPX summary ========\n");
    printf("       Magic: 0x%08x - '%4s' (%s endian)\n", FileHeader->Magic, (char*)&FileHeader->Magic, EndianString);
    printf("Image offset: %u\n", FileHeader->ImageOffset);
    printf("     Version: \"%.8s\"\n", FileHeader->Version);
    printf("    FileSize: %u\n", FileHeader->FileSize);
    printf("    FileName: \"%.100s\"\n", FileHeader->FileName);
    printf("    TimeDate: \"%.24s\"\n", FileHeader->TimeDate);
    printf("     Creator: \"%.100s\"\n", FileHeader->Creator);
    printf("     Project: \"%.200s\"\n", FileHeader->Project);
    printf("   Copyright: \"%.200s\"\n", FileHeader->Copyright);

    const char* OrientationString = "unknown";
    switch(ImageHeader->Orientation)
    {
        case DPX_Orientation_LeftToRightTopToBottom: OrientationString = "Left to right, top to bottom"; break;
        case DPX_Orientation_RightToLeftTopToBottom: OrientationString = "Right to left, top to bottom"; break;
        case DPX_Orientation_LeftToRightBottomToTop: OrientationString = "Left to right, bottom to top"; break;
        case DPX_Orientation_RightToLeftBottomToTop: OrientationString = "Right to left, bottom to top"; break;
        case DPX_Orientation_TopToBottomLeftToRight: OrientationString = "Top to bottom, left to right"; break;
        case DPX_Orientation_TopToBottomRightToLeft: OrientationString = "Top to bottom, right to left"; break;
        case DPX_Orientation_BottomToTopLeftToRight: OrientationString = "Bottom to top, left to right"; break;
        case DPX_Orientation_BottomToTopRightToLeft: OrientationString = "Bottom to top, right to left"; break;
    }

    printf("\n======== DPX image ========\n");
    printf("    Orientation: %u\n", ImageHeader->Orientation);
    printf(" NumberElements: %u\n", ImageHeader->NumberElements);
    printf("  PixelsPerLine: %u\n", ImageHeader->PixelsPerLine);
    printf("LinesPerElement: %u\n", ImageHeader->LinesPerElement);

    Assert(ImageHeader->NumberElements < ArrayCount(ImageHeader->ImageElement));
    for(int Idx = 0;
        Idx < ImageHeader->NumberElements;
        Idx++)
    {
        dpx_image_element* ImageElement = &ImageHeader->ImageElement[Idx];

        const char* DataSignString = "unknown";
        switch(ImageElement->DataSign)
        {
            case DPX_Unsigned: DataSignString = "unsigned"; break;
            case DPX_Signed: DataSignString = "signed"; break;
        }

        const char* DescriptorString = "unknown";
        switch(ImageElement->Descriptor)
        {
            case DPX_Descriptor_UserDefined: DescriptorString = "User-defined"; break;
            case DPX_Descriptor_Red: DescriptorString = "Red"; break;
            case DPX_Descriptor_Green: DescriptorString = "Green"; break;
            case DPX_Descriptor_Blue: DescriptorString = "Blue"; break;
            case DPX_Descriptor_Alpha: DescriptorString = "Alpha"; break;
            case DPX_Descriptor_Luminance: DescriptorString = "Luminance"; break;
            case DPX_Descriptor_Chrominance: DescriptorString = "Chrominance"; break;
            case DPX_Descriptor_Depth: DescriptorString = "Depth"; break;
            case DPX_Descriptor_CompositeVideo: DescriptorString = "Composite video"; break;
            case DPX_Descriptor_RGB: DescriptorString = "RGB"; break;
            case DPX_Descriptor_RGBA: DescriptorString = "RGBA"; break;
            case DPX_Descriptor_ABGR: DescriptorString = "ABGR"; break;
            case DPX_Descriptor_CbYCrY: DescriptorString = "CbYCrY"; break;
            case DPX_Descriptor_CbYaCrYa: DescriptorString = "CbYaCrYa"; break;
            case DPX_Descriptor_CbYCr: DescriptorString = "CbYCr"; break;
            case DPX_Descriptor_CbYCra: DescriptorString = "CbYCra"; break;
            case DPX_Descriptor_UserDefined2ComponentElement: DescriptorString = "User-defined 2-component element"; break;
            case DPX_Descriptor_UserDefined3ComponentElement: DescriptorString = "User-defined 3-component element"; break;
            case DPX_Descriptor_UserDefined4ComponentElement: DescriptorString = "User-defined 4-component element"; break;
            case DPX_Descriptor_UserDefined5ComponentElement: DescriptorString = "User-defined 5-component element"; break;
            case DPX_Descriptor_UserDefined6ComponentElement: DescriptorString = "User-defined 6-component element"; break;
            case DPX_Descriptor_UserDefined7ComponentElement: DescriptorString = "User-defined 7-component element"; break;
            case DPX_Descriptor_UserDefined8ComponentElement: DescriptorString = "User-defined 8-component element"; break;
        }

        const char* TransferString = "unknown";
        switch(ImageElement->Transfer)
        {
            case DPX_Transfer_UserDefined: TransferString = "User-defined"; break;
            case DPX_Transfer_PrintingDensity: TransferString = "Printing density"; break;
            case DPX_Transfer_Linear: TransferString = "Linear"; break;
            case DPX_Transfer_Logarithmic: TransferString = "Logarithmic"; break;
            case DPX_Transfer_UnspecifiedVideo: TransferString = "Unspecified video"; break;
            case DPX_Transfer_SMPTE240M: TransferString = "SMPTE 240M"; break;
            case DPX_Transfer_CCIR709_1: TransferString = "CCIR 709-1"; break;
            case DPX_Transfer_CCIR601_2_System_BorG: TransferString = "CCIR 601-2 system B or G"; break;
            case DPX_Transfer_CCIR601_2_System_M: TransferString = "CCIR 601-2 system M"; break;
            case DPX_Transfer_NTSC_CompositeVideo: TransferString = "NTSC composite video"; break;
            case DPX_Transfer_PAL_CompositeVideo: TransferString = "PAL composite video"; break;
            case DPX_Transfer_Z_Linear: TransferString = "Z linear"; break;
            case DPX_Transfer_Z_Homogeneous: TransferString = "Z homogeneous"; break;
        }

        const char* ColorimetricString = "unknown";
        switch(ImageElement->Colorimetric)
        {
            case DPX_Colorimetric_UserDefined: ColorimetricString = "User-defined"; break;
            case DPX_Colorimetric_PrintingDensity: ColorimetricString = "Printing density"; break;
            case DPX_Colorimetric_UnspecifiedVideo: ColorimetricString = "Unspecified video"; break;
            case DPX_Colorimetric_SMPTE240M: ColorimetricString = "SMPTE 240M"; break;
            case DPX_Colorimetric_CCIR709_1: ColorimetricString = "CCIR 709-1"; break;
            case DPX_Colorimetric_CCIR601_2_System_BorG: ColorimetricString = "CCIR 601-2 system B or G"; break;
            case DPX_Colorimetric_CCIR601_2_System_M: ColorimetricString = "CCIR 601-2 system M"; break;
            case DPX_Colorimetric_NTSC_CompositeVideo: ColorimetricString = "NTSC composite video"; break;
            case DPX_Colorimetric_PAL_CompositeVideo: ColorimetricString = "PAL composite video"; break;
        }

        const char* PackingString = "unknown";
        switch(ImageElement->Packing)
        {
            case DPX_Packed_32Bit: PackingString = "Packed 32-bit words"; break;
            case DPX_Filled_32Bit: PackingString = "Filled 32-bit words"; break;
        }

        const char* EncodingString = "unknown";
        switch(ImageElement->Encoding)
        {
            case DPX_Encoding_None: EncodingString = "None"; break;
            case DPX_Encoding_RLE: EncodingString = "RLE"; break;
        }

        printf("\n======== Element #%d ========\n", Idx);
        printf(" DataSign: %d (%s)\n", ImageElement->DataSign, DataSignString);
        printf(" LowData: %d\n", ImageElement->LowData);
        printf(" LowQuantity: %f\n", ImageElement->LowQuantity);
        printf(" HighData: %d\n", ImageElement->HighData);
        printf(" HighQuantity: %f\n", ImageElement->HighQuantity);
        printf(" Descriptor: %d (%s)\n", ImageElement->Descriptor, DescriptorString);
        printf(" Transfer: %d (%s)\n", ImageElement->Transfer, TransferString);
        printf(" Colorimetric: %d (%s)\n", ImageElement->Colorimetric, ColorimetricString);
        printf(" BitSize: %d\n", ImageElement->BitSize);
        printf(" Packing: %d (%s)\n", ImageElement->Packing, PackingString);
        printf(" Encoding: %d (%s)\n", ImageElement->Encoding, EncodingString);
        printf(" DataOffset: %d\n", ImageElement->DataOffset);
        printf(" EndOfLinePadding: %d\n", ImageElement->EndOfLinePadding);
        printf(" EndOfImagePadding: %d\n", ImageElement->EndOfImagePadding);
        printf(" Description: \"%.*s\"\n", ArrayCount(ImageElement->Description), ImageElement->Description);
    }
}

int
main(int Argc, char** Argv)
{
    if(Argc < 2)
    {
        fprintf(stderr, "Missing filename\n");
        return -1;
    }

    char* FileName = Argv[1];

    int FileDescriptor = open(FileName, O_RDONLY);
    if(FileDescriptor == -1)
    {
        perror("Failed to open file");
        return -1;
    }

    struct stat Stat;
    if(fstat(FileDescriptor, &Stat))
    {
        perror("Failed to get file stat");
        return -1;
    }

    if(Stat.st_size < 0)
    {
        perror("File size negative");
        return -1;
    }
    else if(Stat.st_size == 0)
    {
        perror("File size zero");
        return -1;
    }

    sz FileSize = (sz) Stat.st_size;

    void* FileData = malloc(FileSize);
    if(!FileData)
    {
        perror("Failed to allocate memory for file data");
        return -1;
    }

    ssz ReadResult = read(FileDescriptor, FileData, FileSize);
    if(ReadResult < 0)
    {
        perror("Failed to read file");
        return -1;
    }

    sz ReadCount = (sz) ReadResult;
    if(ReadCount != FileSize)
    {
        perror("Read inssuficient number of file bytes");
        return -1;
    }

    close(FileDescriptor);

    size_t FileSizeMB = (FileSize / 1024 / 1024);
    printf("File size: %ld (%ldMB)\n", FileSize, FileSizeMB);

    dpx_file_header* OrigFileHeader = (dpx_file_header*)(FileData + 0);
    dpx_image_header* OrigImageHeader = (dpx_image_header*)(FileData + sizeof(*OrigFileHeader));

    dpx_file_header* FileHeader;
    dpx_image_header* ImageHeader;

    dpx_file_header TmpFileHeader;
    dpx_image_header TmpImageHeader;

    if(OrigFileHeader->Magic == DPX_LittleEndian)
    {
        FileHeader = OrigFileHeader;
        ImageHeader = OrigImageHeader;
    }
    else if(OrigFileHeader->Magic == DPX_BigEndian)
    {
        FileHeader = &TmpFileHeader;
        ImageHeader = &TmpImageHeader;

        FileHeader->Magic = OrigFileHeader->Magic;

        FileHeader->ImageOffset = Big2LittleU32(OrigFileHeader->ImageOffset);
        Copy(FileHeader->Version, OrigFileHeader->Version);
        FileHeader->FileSize = Big2LittleU32(OrigFileHeader->FileSize);
        FileHeader->DittoKey = Big2LittleU32(OrigFileHeader->DittoKey);
        FileHeader->GenericSize = Big2LittleU32(OrigFileHeader->GenericSize);
        FileHeader->IndustrySize = Big2LittleU32(OrigFileHeader->IndustrySize);
        FileHeader->UserSize = Big2LittleU32(OrigFileHeader->UserSize);
        Copy(FileHeader->FileName, OrigFileHeader->FileName);
        Copy(FileHeader->TimeDate, OrigFileHeader->TimeDate);
        Copy(FileHeader->Creator, OrigFileHeader->Creator);
        Copy(FileHeader->Project, OrigFileHeader->Project);
        Copy(FileHeader->Copyright, OrigFileHeader->Copyright);
        FileHeader->UserSize = Big2LittleU32(OrigFileHeader->EncryptKey);
        Copy(FileHeader->Reserved, OrigFileHeader->Reserved);

        ImageHeader->Orientation = Big2LittleU16(OrigImageHeader->Orientation);
        ImageHeader->NumberElements = Big2LittleU16(OrigImageHeader->NumberElements);
        ImageHeader->PixelsPerLine = Big2LittleU32(OrigImageHeader->PixelsPerLine);
        ImageHeader->LinesPerElement = Big2LittleU32(OrigImageHeader->LinesPerElement);

        for(int Idx = 0;
            Idx < ArrayCount(ImageHeader->ImageElement);
            Idx++)
        {
            dpx_image_element* ImageElement = &ImageHeader->ImageElement[Idx];
            dpx_image_element* OrigImageElement = &OrigImageHeader->ImageElement[Idx];

            ImageElement->DataSign = Big2LittleU32(OrigImageElement->DataSign);
            ImageElement->LowData = Big2LittleU32(OrigImageElement->LowData);
            ImageElement->HighData = Big2LittleU32(OrigImageElement->HighData);
            ImageElement->Descriptor = (OrigImageElement->Descriptor);
            ImageElement->Transfer = (OrigImageElement->Transfer);
            ImageElement->Colorimetric = (OrigImageElement->Colorimetric);
            ImageElement->BitSize = (OrigImageElement->BitSize);
            ImageElement->Packing = Big2LittleU16(OrigImageElement->Packing);
            ImageElement->Encoding = Big2LittleU16(OrigImageElement->Encoding);
            ImageElement->DataOffset = Big2LittleU32(OrigImageElement->DataOffset);
            ImageElement->EndOfLinePadding = Big2LittleU32(OrigImageElement->EndOfLinePadding);
            ImageElement->EndOfImagePadding = Big2LittleU32(OrigImageElement->EndOfImagePadding);
            Copy(ImageElement->Description, OrigImageElement->Description);
        }

        Copy(ImageHeader->Reserved, OrigImageHeader->Reserved);
    }
    else
    {
        fprintf(stderr, "Invalid file magic: 0x%08x\n", OrigFileHeader->Magic);
        return -1;
    }

    if(ImageHeader->NumberElements > ArrayCount(ImageHeader->ImageElement))
    {
        fprintf(stderr, "Invalid number of elements %d\n", ImageHeader->NumberElements);
        return -1;
    }

#if 1
    PrintInfoDPX(FileHeader, ImageHeader);
#endif


    if(ImageHeader->Orientation != DPX_Orientation_LeftToRightTopToBottom)
    {
        fprintf(stderr, "Not supported orientation: %d\n", ImageHeader->Orientation);
        return -1;
    }

    if(ImageHeader->NumberElements == 0)
    {
        fprintf(stderr, "Not supported number of elements: %d\n", ImageHeader->NumberElements);
        return -1;
    }

    return 0;
}
