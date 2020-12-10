
#ifndef edid_H_
#define edid_H_

#include <stdio.h>
#include <stdlib.h>



void EdidPrint(FILE *input);
//void EdidPrint();
//int  FixIDID (int numberByte, unsigned char Byte_0_7 );

int i_Bit_Depth(unsigned char Bit_Depth);
//void DesriptorTiminDef(unsigned char Desk[18]);
void DesriptorTiminDef(unsigned char *data);
void DeskriptorRead(unsigned char *data);
void ExtansionRead(unsigned char *Arr);


void SerialNumberDeskriptor(unsigned char *data);
void AlfanumericData(unsigned char *data);
void DisplaRangeLimits(unsigned char *data);
void DisplayProductName(unsigned char *data, char **ar, size_t *arr_len);
void ColorPointDeskriptor(unsigned char *data);
void ColorManageDeskriptor(unsigned char *data);


typedef struct 
{
    unsigned char Byte_0;
    unsigned char Byte_1;
    unsigned char Byte_2;
    unsigned char Byte_3;
    unsigned char Byte_4;
    unsigned char Byte_5;
    unsigned char Byte_6;
    unsigned char Byte_7;
} EDID_fix;


typedef struct 
{
    unsigned char redX      : 2;
    unsigned char RedY      : 2;
    unsigned char GreenX    : 2;
    unsigned char GreenY    : 2;
    unsigned char BluX      : 2;
    unsigned char BluY      : 2;
    unsigned char WhiteX    : 2;
    unsigned char WhiteY    : 2;

    unsigned char redX_senior ;
    unsigned char redY_senior ;
    unsigned char GreenX_senior ;
    unsigned char GreenY_senior ;
    unsigned char BluX_senior ;
    unsigned char BluY_senior ;
    unsigned char WhiteX_senior ;
    unsigned char WhiteY_senior ;


} Color;

 
typedef struct 
{
    unsigned char VGA_70_720_40   : 1;
    unsigned char XGA_88_720_400  : 1;
    unsigned char XVA_60_640_480  : 1;
    unsigned char MAC_67_640_480   : 1;
    unsigned char Hz_72_640_480    : 1;
    unsigned char Hz_75_640_480    : 1;
    unsigned char Hz_56_800_600    : 1;
    unsigned char Hz_60_800_600    : 1;
    unsigned char Hz_72_800_600    : 1;
    unsigned char Hz_75_800_600    : 1;
    unsigned char Hz_75_832_624    : 1;
    unsigned char Hz_88_024_768    : 1;
    unsigned char Hz_60_024_768    : 1;
    unsigned char Hz_70_024_768    : 1;
    unsigned char Hz_75_024_768    : 1;
    unsigned char Hz_75_280_024    : 1;
    unsigned char Hz_75_152_870    : 1;
    unsigned char Hz_other    : 7;


} BitTimeHz;

typedef struct 
{
    unsigned char vertical : 6;
    unsigned char ratio    : 2;
    unsigned char resolution;
    
} standartInfTime;

typedef struct 
{
    unsigned char PixelLSB;
    unsigned char PixelMSB;
    unsigned short GorizontalPixel;
    unsigned char GorizontaExti;
    unsigned char GorizontaActiv    : 4;
    unsigned char GorizontaActivPix : 4;

    unsigned short VerticalPixel;
    unsigned char VerticalExti;
    unsigned char VerticalActiv    : 4;
    unsigned char VerticalActivPix : 4;

    unsigned char HorizontalSyncOffset;
    unsigned char HorizontalWidthPix;
    unsigned char VerticalSyncOffset    : 4;
    unsigned char VerticalWidthPix : 4;

    unsigned char Byte_11_76    : 2;
    unsigned char Byte_11_54    : 2;
    unsigned char Byte_11_32    : 2;
    unsigned char Byte_11_10    : 2;

    unsigned char Byte_12 ;
    unsigned char Byte_13 ;

    unsigned char Byte_14 ;
    unsigned char Byte_15 ;
    unsigned char Byte_16 ;
    unsigned char Byte_17 ;

    
} Deskriptor;


struct EDID
{
    EDID_fix        Byte0_7;
    unsigned char   reserved  : 1;
    unsigned char   FirstWord : 5;
    unsigned char   TwoWord   : 5;
    unsigned char   ThreeWord : 5;
    unsigned short  KodeTovara ;
    unsigned int    SerialNumber;
    unsigned char   WeekManufac;
    unsigned char   YearManufac;
    unsigned char   Version_0;
    unsigned char   Version_1;
    unsigned int    Parametr;
    Color           ColorRead;      //  25 - 34
    BitTimeHz       BitTimeHzRead;  //  35 - 37
    standartInfTime Read;           //  38 - 53
    Deskriptor      Deskriptor_1;
    Deskriptor      Deskriptor_2;
    Deskriptor      Deskriptor_3;
    Deskriptor      Deskriptor_4;
    unsigned char   NumberExtansion;
    unsigned char   CheckSumm;      // 127

} uup;




typedef struct 
{
    char EXTENSIONBlockTagNumber;
    char RevisionNumber;
    char NumberByteStartDTV;
    char Bit7DwScan             :1;
    char BasicAudio             :1;
    char YCbCr444               :1;
    char YCbCr422               :1;
    char NumberNativeFormats    :4;
    Deskriptor      Deskriptor_1;
    Deskriptor      Deskriptor_2;
    Deskriptor      Deskriptor_3;
    Deskriptor      Deskriptor_4;
    unsigned char   CheckSumm;      // 127
} EDID_EXTENSION;










#endif