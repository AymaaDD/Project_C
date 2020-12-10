
#include "edid.h"


unsigned char Space1;

Deskriptor TestDeskriptor;

Deskriptor* DeskptrTest = &TestDeskriptor;


/* FixIDID
    input 
       int param_1 - numberByte, number 0 - 7 byte EDID
       uc  param_2 - Byte_0_7, byte EDID

    output INT
        0 - good
        1 - error package
*/

int  FixIDID (int numberByte, int Byte_0_7 ) {

    if ( (( 0 == numberByte ) || (  7 == numberByte)) && (Byte_0_7 == 0) ) {
        return 0;
    } else if ( (( numberByte > 0) && (numberByte <= 6)) && (Byte_0_7 == 255) ) {
        return 0;   // 
    } else {
        return 1; // error
    }
}





void EdidPrint(FILE *input){

    unsigned char ARR [128];
    
    //FILE *input = NULL;
    //input = fopen("/home/davaa/Desktop/Project_1/test.edid", "rb");
    int NumberReadByte = 128;
    int NumberExtansion = 0;

    for (int i = 0; i < NumberReadByte; i++) {

        ARR[i] = getc(input);
        
        if (i < 8) {
            if ( FixIDID(i,(int)ARR[i] ) != 0){
                printf("\n FIX ID Error \n");
                break;
            } else {
                if (i == 7) {
                    printf("\n FIX ID CORRECTLY \n");
                }
            }
        } else if ( 9 == i) {

            if (( ARR[8] & 0x80) == 0x80) {
                printf("\nReserved bit error \n");
            } else {
                printf("\nReserved bit CORRECTLY \n");
            }
            unsigned int Int_8_9 = (ARR[8] << 8) | ARR[9];
            unsigned char ucWORD = ((Int_8_9 >> 10) & 0x1f) + 64;
            printf("ID fabricator - ");
            printf("%c",ucWORD);
            ucWORD = ((Int_8_9 >> 5) & 0x1f) + 64;
            printf("%c",ucWORD);
            ucWORD = (Int_8_9 & 0x1f) + 64;
            printf("%c",ucWORD);
            

        } else if ( 11 == i) {
            unsigned int Int_10_11 = (ARR[10] << 8) | ARR[11];
            printf("\nCode fabricator - %d",Int_10_11);
        } else if ( 15 == i) {
            unsigned int Int_12_15 = (ARR[12] << 24) | (ARR[13] << 16) | (ARR[13] << 8) | ARR[13];
            printf("\nSerial number - %d", Int_12_15);
            
        } else if ( 17 == i) {
            if (ARR[16] == 0xff) {
                printf("\n Model year -");
                printf("%d",( 1990 + ARR[17]));
                
            } else {
                printf("\nManufacturing - ");
                printf("%d", ARR[17] );
                printf(" week ");
                printf("%d",( 1990 + ARR[17]));
                printf(" year ");
            }
        } else if ( 19 == i) {
            printf("\nVersion EDID - %d,%d ",ARR[18],ARR[19]);
            
        } else if ( 24 == i) {
            printf("\n \n Parametr display \n");
            printf("%s","\n     ");
            if ( 0x80 == (ARR[20] & 0x80) ) {
                unsigned char Bit_Depth = (ARR[20] >> 4) & 0x07;
                printf(" Bit Depth - ");
                printf("%d",i_Bit_Depth( Bit_Depth ) ); 
                unsigned char Video_int = ARR[20] & 0xf;


                printf("%s","\n     ");
                printf(" Video interfaces - ");
                if( 0 == Video_int ) {
                    printf("%s","undefined ");
                } else if( 2 == Video_int ) {
                    printf("%s","HDMIa ");
                } else if( 3 == Video_int ) {
                    printf("%s","HDMIb ");
                } else if( 4 == Video_int ) {
                    printf("%s","MDDI ");
                } else if( 5 == Video_int ) {
                    printf("%s","DisplayPort ");
                } else {
                    printf("%s","Not read ");
                }
                printf("%s","\n     ");
            } else {

                unsigned char WhiteSin = (ARR[20] >> 5) & 0x03;
                printf("- White levels ");
                if( 0 == WhiteSin ) {
                    printf("%s"," +0,7 / -0,3 B ");
                } else if( 1 == WhiteSin ) {
                    printf("%s"," +0,714 / -0,286 B ");
                } else if( 2 == WhiteSin ) {
                    printf("%s"," +1,0 / -0,4 B ");
                } else if( 3 == WhiteSin ) {
                    printf("%s"," +0,7 / 0 B ");
                }
                


                printf("%s","\n     ");
                printf(" Pending installation from blank to black -");
                if((ARR[20] >> 4) & 0x01){
                    printf("%s"," Yes");
                } else {
                    printf("%s"," Not ");
                }


                printf("%s","\n     ");
                printf(" Separate sync supported -");
                if((ARR[20] >> 3) & 0x01){
                    printf("%s"," Yes");
                } else {
                    printf("%s"," Not ");
                }
                
                printf("%s","\"     ");
                printf(" Composite sync supported - ");
                if((ARR[20] >> 2) & 0x01){
                    printf("%s"," Yes");
                } else {
                    printf("%s"," Not ");
                }
                

                printf("%s","\n     ");
                printf(" Sync on green supported ");
                if((ARR[20] >> 1) & 0x01){
                    printf("%s"," Yes");
                } else {
                    printf("%s"," Not ");
                }
                printf("%s","\n     ");


                printf(" VSync is jagged if composite signal or sync on green ");
                if((ARR[20] >> 0) & 0x01){
                    printf("%s"," Yes");
                } else {
                    printf("%s"," Not ");
                }
                printf("%s","\n     ");
            }

            if (0 == ARR[21]) {
                printf("%s", "Album (1,00 - 3,54) Range aspect ratio \n");
            } else {
                printf("%s", " Horizontal size in centimeters - ");
                printf("%d", ARR[21]);
            }

            printf("%s","\n     ");
            if (0 == ARR[22]) {
                printf("%s", "Portrait (0,28 - 0,99) Range aspect ratio \n");
            } else {
                printf("%s", " Vertical size in centimeters - ");
                printf("%d", ARR[22]);
            }


            printf("%s","\n     ");
            if (225 == ARR[23]) {
                printf("%s", " Gamma in DI-EXT \n");
            } else {
                printf("%s", " Gamma - ");
                printf("%d", (ARR[23]-1)*100);
                
            }


            printf("%s","\n     ");
            printf("%s", " Standby support DPMS - ");
            if((ARR[24] >> 7) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }
            
            
            printf("%s","\n     ");
            printf("%s", " Pause DPMS supported - ");
            if((ARR[24] >> 6) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }
            
            printf("%s","\n     ");
            printf("%s", " Type display (digital) -");
            unsigned char TypeDispDig = (ARR[24] >> 3 ) & 0x03;

            if ( 0 == TypeDispDig ) {
                printf("%s"," RGB 4: 4: 4 \n");
            } else if ( 1 == TypeDispDig ){
                 printf("%s"," RGB 4: 4: 4 + YCrCb 4: 4: 4 \n");
            } else if ( 2 == TypeDispDig ){
                 printf("%s"," RGB 4: 4: 4 + YCrCb 4: 2: 2 \n");
            } else if ( 3 == TypeDispDig ){
                 printf("%s"," RGB 4: 4: 4 + YCrCb 4: 4: 4 + YCrCb 4: 2: 2 \n");
            }

            printf("%s","     ");
            printf("%s", " Type display (analog) -");
            if ( 0 == TypeDispDig ) {
                printf("%s"," monochrom n");
            } else if ( 1 == TypeDispDig ){
                 printf("%s"," RGB \n");
            } else if ( 2 == TypeDispDig ){
                 printf("%s"," not RGB \n");
            } else if ( 3 == TypeDispDig ){
                 printf("%s","undefined \n");
            }

            printf("%s","     ");
            printf("%s", " sRGB -");
            if((ARR[24] >> 2) & 0x01){
                printf("%s"," Yes, byte 25-34 sRGB");
            } else {
                printf("%s"," Not");
            }

            printf("%s","\n     ");
            printf("%s", " Native pixel format -");
            if((ARR[24] >> 1) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }


            printf("%s","\n     ");
            printf("%s", " Continius timings -");
            if((ARR[24] >> 1) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }

        } else if ( 34 == i) {
            unsigned int RedX = (ARR[27] << 2) | (ARR[25] >> 6);
            unsigned int RedY = (ARR[28] << 2) | ((ARR[25] >> 4) & 0x03);
            unsigned int GreenX = (ARR[29] << 2) | ((ARR[25] >> 2) & 0x03);
            unsigned int GreenY = (ARR[30] << 2) | ((ARR[25] >> 0) & 0x03);

            unsigned int BluX = (ARR[31] << 2) | (ARR[26] >> 6);
            unsigned int BluY = (ARR[32] << 2) | ((ARR[26] >> 4) & 0x03);
            unsigned int WhitX = (ARR[33] << 2) | ((ARR[26] >> 2) & 0x03);
            unsigned int WhitY = (ARR[34] << 2) | ((ARR[26] >> 0) & 0x03);

            printf("%s","\n \n");
            printf("%s", " Chromaticity coordinates: \n");
            printf("%s", "             X      Y \n");
            printf("    RED     %d   %d \n", RedX, RedY );
            printf("    Green   %d   %d \n", GreenX, GreenY );
            printf("    Blu     %d   %d \n", BluX, BluY );
            printf("    White   %d   %d \n", WhitX, WhitY );

        } else if ( 37 == i) {
            printf("%s","\n \n");
            printf("%s", " Supported bitmap: \n");
            
            printf("%s","\n     ");  
            printf("%s", "VGA 720 x 400 in 70Hz - "); 
            if((ARR[35] >> 7) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }

            printf("%s","\n     ");  
            printf("%s", "XGA 720 x 400 in 88Hz - "); 
            if((ARR[35] >> 6) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }

   
            printf("%s","\n     ");  
            printf("%s", "VGA 640 x 480 in 60Hz - "); 
            if((ARR[35] >> 5) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }        
    

            printf("%s","\n     ");  
            printf("%s", "    640 x 480 in 67Hz - "); 
            if((ARR[35] >> 4) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }

            printf("%s","\n     ");  
            printf("%s", "    720 x 480 in 72Hz - "); 
            if((ARR[35] >> 3) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }
            
            printf("%s","\n     ");  
            printf("%s", "    720 x 480 in 75Hz - "); 
            if((ARR[35] >> 2) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }


            printf("%s","\n     ");  
            printf("%s", "    800 x 600 in 56Hz - "); 
            if((ARR[35] >> 1) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }

            printf("%s","\n     ");  
            printf("%s", "    800 x 600 in 60Hz - "); 
            if((ARR[35] >> 0) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }

            printf("%s","\n     ");  
            printf("%s", "    800 x 600 in 72Hz - "); 
            if((ARR[36] >> 7) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }

            printf("%s","\n     ");  
            printf("%s", "    800 x 600 in 75Hz - "); 
            if((ARR[36] >> 6) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }

            printf("%s","\n     ");  
            printf("%s", "    832 x 624 in 75Hz - "); 
            if((ARR[36] >> 5) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }

            printf("%s","\n     ");  
            printf("%s", "    1024 x 768 in 87Hz - "); 
            if((ARR[36] >> 4) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }

            printf("%s","\n     ");  
            printf("%s", "    1024 x 768 in 60Hz - "); 
            if((ARR[36] >> 3) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }

            printf("%s","\n     ");  
            printf("%s", "    1024 x 768 in 70Hz - "); 
            if((ARR[36] >> 2) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }

            printf("%s","\n     ");  
            printf("%s", "    1280 x 768 in 75Hz - "); 
            if((ARR[36] >> 1) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }

            printf("%s","\n     ");  
            printf("%s", "    1280 x 1024 in 75Hz - "); 
            if((ARR[36] >> 0) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }

            printf("%s","\n     ");  
            printf("%s", "    1152 x 870 in 75Hz - "); 
            if((ARR[37] >> 3) & 0x01){
                printf("%s"," Yes");
            } else {
                printf("%s"," Not");
            }

            printf("%s","\n     ");  
            printf("%s", "  37 BYTE  bit 6...0 not decod"); 


        } else if ( 53 == i) { 

            printf(" \n Standart mode : \n"  );
            for(int k = 0; k < 9; k++) {
                if (ARR[38+k*2] != 1) {
                    printf("        %d pix, %d Hz ", (ARR[38 + k*2] + 31) * 8, (ARR[39+k*2] & 0x1f) + 60 );
                    if ( ((ARR[39+k*2] >> 6) & 0x03) == 0) {
                        printf(", 16:10  FOR EDID MORE 1.3 \n" ); 
                    } else if ( ((ARR[39+k*2] >> 6) & 0x03) == 1) {
                        printf(", 4:3 \n"  );
                    } else if ( ((ARR[39+k*2] >> 6) & 0x03) == 2) {
                        printf(", 5:4 \n" );
                    } else {
                        printf(", 16:9 \n"  );
                    }
                    
                } else {
                    printf("        Not set \n"  );
                }    
            }
        } else if ( 125 == i) {
            
            printf("\n  Deskriptor time EDID : "  );

            for (int t =  0; t < 4; t++) {
                printf("\n\n     Deskriptor %d : ", t );
                DeskriptorRead(&ARR[54 + t*18]);
            }

        } else if ( 126 == i) { 
            NumberExtansion = (int)ARR[126];
            printf("\nNumber Extension - %d \n",NumberExtansion );
        } else if ( 127 == i) { 
            unsigned char CheckSumm = 0;
            for (int k = 1; k<=127; k++) {
                CheckSumm += ARR[k];
            }

            if (CheckSumm == 0) {
                printf("Check Summ right ");
            } else {
                printf("Check Summ fault ");
            }
        }
    }

    char CheckSumExtan = 0;
    if (NumberExtansion > 0) {
        for (int i = 0; i < NumberExtansion; i++ ) {

            for (int k = 0; k < 128; k++) {
                 ARR[k] = getc(input);
            }

            for (int k = 0; k < 128; k++) {
                CheckSumExtan += ARR[k];
            }

            if ( 0 == CheckSumExtan ) {
                printf("\n\n    Check Summ Extension %d right ", i);
                ExtansionRead(&ARR[0]);
            } else {
                printf("\n\n    Check Summ Extension %d fault ", i);
                continue;
            }

        }
    } 


    if (fclose(input) == EOF)
        printf("\n\n\n File close error \n");
    else 
        printf("\n\n\n File close done \n");

}


void ExtansionRead(unsigned char *Arr) {
    printf("\nEXTENSION Block Tag Code %d", *Arr);
    printf("\n    Number Version- %d", *Arr);

    if ( 0x01 == *(Arr+3) >> 7) {
        printf("\n    Underscan is supported ");
    } else {
        printf("\n    Underscan is not supported");
    }

    if ( 0x01 == ((*(Arr+3) >> 6) & 0x01)) {
        printf("\n    Basic Audio is supported");
    } else {
        printf("\n    Basic Audio is not supported");
    }
     

    if ( 0x01 == ((*(Arr+3) >> 5) & 0x01)) {
        printf("\n    YCbCr 4:4:4 is supported");
    } else {
        printf("\n    YCbCr 4:4:4 is not supported");
    }

    if ( 0x01 == ((*(Arr+3) >> 4) & 0x01)) {
        printf("\n    YCbCr 4:2:2 is supported");
    } else {
        printf("\n    YCbCr 4:2:2 is not supported");
    }

    int DeskExtEDIDstart = *(Arr+2);
    
    if (0x00 == *(Arr+2)) {
        printf("\n    Deskription be away : %d", DeskExtEDIDstart);
    } else if (0x04 == *(Arr+2)) {
        printf("\n    Block Data be away : %d", DeskExtEDIDstart);
    } else {
        printf("\n    Number byte Start Deskription +1 : %d", DeskExtEDIDstart);
    }

    int NumberBlockNative = *(Arr+3) & 0x0f;
    printf("\n    Number of native formats is %d", NumberBlockNative);

    if ( 0x04 != DeskExtEDIDstart ) {
        char TegTypeBlock = 0;
        int NByteClockData = 0;
        int StartBlockData = 4;
        int IndexDataBlock = 0;
        for (; ; ) {
            if (StartBlockData >= *(Arr+2)  ) {
                printf("  \n Break");
                break;    
            }
            
            if (0x04 == *(Arr + StartBlockData)) {
                StartBlockData++;
                NByteClockData = 0;
                printf("\n  Null Block Data");
                continue;
            }
            
            TegTypeBlock = *(Arr + StartBlockData) >> 5;
            NByteClockData = *(Arr + StartBlockData) & 0x1f;
            IndexDataBlock = StartBlockData + 1;
            
            printf("\n    Number Bytes Block Data  %d", NByteClockData);

            printf("\n    Teg type is -");
            if ( 1 == TegTypeBlock ) {
                printf("  AUDIO");
                for (int n = 0; n < (NByteClockData/3); n++) {
                    for (int k = 0; k < (NByteClockData); k++) {
                        printf("\n              AUDIO Descriptor Byte %d %d", k, *(Arr + IndexDataBlock + k + n*3 ) );
                    }
                }
            } else if ( 2 == TegTypeBlock ) {
                printf("  VIDEO");
                for (int n = 0; n < NByteClockData; n++) {
                    printf("\n              Video Descriptor Byte %d = 0x%X", n, (*(Arr + IndexDataBlock + n)) & 0x7f);
                } 
            } else if ( 3 == TegTypeBlock ) {
                printf("  Depends on the supplier");
                for (int n = 0; n < NByteClockData; n++) {
                    printf("\n              Depends on the supplier Byte %d = 0x%X", n, *(Arr + IndexDataBlock + n));
                } 
            } else if ( 4 == TegTypeBlock ) {
                printf("  Distribution of speakers");
                for (int n = 0; n < NByteClockData; n++) {
                    printf("\n              Distribution of speakers %d = 0x%X", n, *(Arr + IndexDataBlock + n));
                } 
            } else if ( 5 == TegTypeBlock ) {
                printf("  Characteristic VESA");
                for (int n = 0; n < NByteClockData; n++) {
                    printf("\n              Characteristic VESA %d = 0x%X", n, *(Arr + IndexDataBlock + n));
                } 
            }

            StartBlockData = StartBlockData + NByteClockData + 1;

        }
    }

    
    if (0 != DeskExtEDIDstart ) 
    printf("\n  Deskriptor time EDID extansion : "  );

    for (int t =  0; t < 4; t++) {
            printf("\n\n     Deskriptor %d : ", t );
            DeskriptorRead(&Arr[DeskExtEDIDstart]);
            DeskExtEDIDstart += (t*18);
            if (DeskExtEDIDstart > 128 || ( (*(Arr + DeskExtEDIDstart) == 0x00) && ( *(Arr + DeskExtEDIDstart +1) == 0x00) ) ) {
                break;
            }
        }
    


    



}


void PrintBlockDataAudio ( unsigned char *data ) {
/*
    printf("\n    Format -");
    int TagCodeAudio = (*(Arr + 5 + i * 4 + NVideoDesk) >> 3) & 0x0f;
    printf("\n      Audio Data Block Tag Code is %d", TagCodeAudio);
    int MaxChAudio = (*(Arr + 5 + i * 4 + NVideoDesk)) & 0x07;
    printf("\n      Maximum number of audio channels is %d", MaxChAudio);

    int SupSamFreq = (*(Arr + 6 + i * 4 + NVideoDesk));
    printf("\n      Supported Sampling Frequencies include ");
    if (0x01 == (SupSamFreq & 0x01))
        printf(" 32 kHz");
    if (0x02 == (SupSamFreq & 0x02))
        printf(" 44,1 kHz");
    if (0x04 == (SupSamFreq & 0x04))
        printf(" 48 kHz");
    if (0x08 == (SupSamFreq & 0x08))
        printf(" 88 kHz");
    if (0x10 == (SupSamFreq & 0x10))
        printf(" 96 kHz");
    if (0x20 == (SupSamFreq & 0x20))
        printf(" 176 kHz");
    if (0x40 == (SupSamFreq & 0x40))
        printf(" 192 kHz");

    int SSBRates = (*(Arr + 7 + i * 4 + NVideoDesk)) & 0x03;
    printf("\n      Supported Sampling Bit Rates include is :");
    if (0x01 == (SSBRates & 0x01))
        printf(" 24 bit;");
    if (0x02 == (SSBRates & 0x02))
        printf(" 20 bit;");
    if (0x04 == (SSBRates & 0x04))
        printf(" 16 bit;");
        */
}


void DeskriptorRead(unsigned char *data) {
    char *ar;
    size_t ar_len = 0;

    if ( (*data == 0) && (*data == 0) ) {
        if ( *(data+2) == 0 ) {
            if (*(data+3) == 0xFF) {
                SerialNumberDeskriptor(data);
            } else if (*(data+3) == 0xFE) {
                AlfanumericData(data);
            } else if (*(data+3) == 0xFD) {
                DisplaRangeLimits(data);
            } else if (*(data+3) == 0xFC) {
                DisplayProductName(data, &ar, &ar_len);
            } else if (*(data+3) == 0xFB) {
                ColorPointDeskriptor(data);
            } else if (*(data+3) == 0xFA) {
                printf("\n Other 0xFA ");
            } else if (*(data+3) == 0xF9) {
                ColorManageDeskriptor(data);
            } else if (*(data+3) == 0xF8) {
                printf("\n Other 0xF8 ");
            } else if (*(data+3) == 0xF7) {
                printf("\n Other 0xF7 ");
            } else if ( (*(data+3) >= 0x11) && (*(data+2) <= 0xF6) ) {
                printf("\n Other 0x0x11F9 ");
            } else if (*(data+3) == 0x10) {
                printf("\n Other 0x10 ");
            //} else if ( (*(data+2) >= 0x00) && (*(data+2) <= 0x0f) ) {

            } else {
                printf("\n Other else ");
            }

        } else {
            printf("\n Other Deskriptor ");
        }
        
    } else {
        DeskptrTest = (Deskriptor*)data;
        DesriptorTiminDef(data); 
    }
    
    if (ar_len > 0) {
        for (int d=0; d < (int)ar_len; d++) {
            printf("%c", ar[d]);
        }
        free(ar);
    }
}

int i_Bit_Depth(unsigned char Bit_Depth){
    if ( 0 == Bit_Depth ) {
        return 0;
    } else if ( 1 == Bit_Depth ) {
       return 6;
    } else if ( 2 == Bit_Depth ) {
        return 8;
    } else if ( 3 == Bit_Depth ) {
        return 10;
    } else if ( 4 == Bit_Depth ) {
        return 12;
    } else if ( 5 == Bit_Depth ) {
        return 14;
    } else if ( 6 == Bit_Depth ) {
        return 16;
    } else if ( 7 == Bit_Depth ) {
        return 1;
    } else {
        return 1;
    }
}

void DesriptorTiminDef(unsigned char *data)
{

    printf("\n         Pixel clock = ");
    unsigned int PixelTime = (*(data+1) << 8) | *(data);
    printf(" %f, MHz", ((float)PixelTime * 0.01));

    printf("\n         Horizontal Active Pixel = ");
    unsigned int HorizontalActivPixel = ((*(data+4) >> 4) << 8) | *(data+2);
    printf(" %d", (HorizontalActivPixel));

    printf("\n         Horizontal blanking Pixel = ");
    unsigned int HorizontalBlankPixel = ((*(data+4) & 0x0f) << 8) | *(data+3);
    printf(" %d", (HorizontalBlankPixel));

    printf("\n         Vertical Active Line = ");
    unsigned int VertikalActivLine = ((*(data+7) >> 4) << 8) | *(data+5);
    printf(" %d", (VertikalActivLine));

    printf("\n         Vertical blanking Line = ");
    unsigned int VerticalBlankLine = ((*(data+7) & 0x0f) << 8) | *(data+6);
    printf(" %d", (VerticalBlankLine));

    printf("\n         Horizontal front porch = ");
    unsigned int HorizontalFrontPorch = ((*(data+11) >> 6) << 8) | *(data+8);
    printf(" %d", (HorizontalFrontPorch));

    printf("\n         Pixel width Hor.Sync = ");
    unsigned int PixelWidthHorSync = ((*(data+11) & 0x30) << 4) | *(data+9);
    printf(" %d", (PixelWidthHorSync));

    printf("\n         Vertical front porch = ");
    unsigned int VerticalFrontPorch = ((*(data+11) & 0x0C) << 2) | (*(data+10) >> 4);
    printf(" %d", (VerticalFrontPorch));

    printf("\n         Width line Ver.Sync = ");
    unsigned int WidthLineVerSync = ((*(data+11) & 0x03) << 4) | (*(data+10) & 0x0f);
    printf(" %d", (WidthLineVerSync));

    printf("\n         Horizontal Addr Video Image Size in mm = ");
    unsigned int SizeHorVid = ((*(data+14) & 0xf0) << 4) | *(data+12);
    printf(" %d", (SizeHorVid));

    printf("\n         Vertical Addr Video Image Size in mm = ");
    unsigned int SizeVerVid = ((*(data+14) & 0x0f) << 8) | *(data+13);
    printf(" %d", (SizeVerVid));

    printf("\n         Pixel Horizontal border (R or L) = %d ", *(data+15));
    printf("\n         Pixel Vertical border (T or B) = %d ", *(data+16));

    printf("\n         Signal interface type - ");
    if (0x00 == (*(data+17) & 0x80))
    {
        printf("Non-Interlaced (1frame = 1 field ");
    }
    else
    {
        printf("nterlaced (1frame = 2 field ");
    }
    printf("\n         Stereo Viewing support - ");
    unsigned char StVsupport = (*(data+17) >> 5) & 0x03;
    unsigned char StVbit = *(data+17) & 0x01;
    if (0 == StVsupport)
    {
        printf("Normal Display - No Stereo ");
    }
    else if (1 == StVsupport)
    {
        if (StVbit)
            printf("2-way interleaved stereo, right  image on even lines");
        else
            printf("Field sequental stereo, right  image when stereo sync signa = 1");
    }
    else if (2 == StVsupport)
    {
        if (StVbit)
            printf("2-way interleaved stereo, left  image on even lines");
        else
            printf("Field sequental stereo, left  image when stereo sync signa = 1");
    }
    else if (3 == StVsupport)
    {
        if (StVbit)
            printf("Side-by-Side interleaved stereo");
        else
            printf("4 - way interleaved stereo");
    }

    printf("\n         Sync Signal Definition - ");
    unsigned char SyncSDef = (*(data+17) >> 1) & 0x0f;
    if (SyncSDef == 0)
    {
        printf("Analog Composite Sync Without Serration Sync On Green Signal only");
    }
    else if (SyncSDef == 1)
    {
        printf("Analog Composite Sync Without Serration Sync On all three (RGB) video signal");
    }
    else if (SyncSDef == 2)
    {
        printf("Analog Composite Sync With Serration Sync On Green Signal only");
    }
    else if (SyncSDef == 3)
    {
        printf("Analog Composite Sync With Serration Sync On all three (RGB) video signal");
    }
    else if (SyncSDef == 4)
    {
        printf("Bipolar Analog Composite Sync Without Serration Sync On Green Signal only");
    }
    else if (SyncSDef == 5)
    {
        printf("Bipolar Analog Composite Sync Without Serration Sync On all three (RGB) video signal");
    }
    else if (SyncSDef == 6)
    {
        printf("Bipolar Analog Composite Sync With Serration Sync On Green Signal only");
    }
    else if (SyncSDef == 7)
    {
        printf("Bipolar Analog Composite Sync With Serration Sync On all three (RGB) video signal");
    }
    else if ((8 == SyncSDef) || (9 == SyncSDef))
    {
        printf("Digital Composite Sync Without Serration ");
    }
    else if ((10 == SyncSDef) || (11 == SyncSDef))
    {
        printf("Digital Composite Sync With Serration ");
    }
    else if (12 == SyncSDef)
    {
        printf("Digital Separate Sync Vertical Sync is Neg  Vertical Sync is Neg ");
    }
    else if (13 == SyncSDef)
    {
        printf("Digital Separate Sync Vertical Sync is Neg  Vertical Sync is Pos ");
    }
    else if (14 == SyncSDef)
    {
        printf("Digital Separate Sync Vertical Sync is Pos  Vertical Sync is Neg ");
    }
    else if (15 == SyncSDef)
    {
        printf("Digital Separate Sync Vertical Sync is Neg  Vertical Sync is Pos ");
    }
}


void DeskriptorDisplayData(unsigned char *data)
{
    printf("\n This decryptor is not scheduled %d", *data );
}

void SerialNumberDeskriptor(unsigned char *data) {
    
    printf("\n S/N is:");
    for (int i = 5; i < 18;i++) {
        data++;
        printf("%c",*data);
    }

}

void AlfanumericData(unsigned char *data) {
    printf("\n ASCII data String is:");
    for (int i = 5; i < 18;i++) {
        data++;
        printf("%10c",*data);
    }
}


// In ptr arr deskriptor
void DisplaRangeLimits(unsigned char *data) {
    
    printf("\n %9c %s" , Space1, "Display Range Limits offsets:");

    if ( (*(data+4) & 0x03) == 0x00) {
        printf(" Vertical Rate Offsets are zero ");
    } else if ( (*(data+4) & 0x03) == 0x02) {
        printf(" Max. Vertical Rate + 255 Hz Offset; Min. Vertical Rate is not offset");
    } else if ( (*(data+4) & 0x03) == 0x03) {
        printf(" Max. Vertical Rate + 255 Hz Offset; Min. Vertical Rate + 255 Hz Offset ");
    } else if ( ((*(data+4) >> 2) & 0x03) == 0x00) {
        printf(" Horizontal Rate Offsets are zero. ");
    } else if ( ((*(data+4) >> 2) & 0x03) == 0x02) {
        printf(" Max. Horizontal Rate + 255 kHz Offset; Min. Horizontal Rate is not offset ");
    } else if ( ((*(data+4) >> 2) & 0x03) == 0x03) {
        printf(" Max. Horizontal Rate + 255 kHz Offset; Min. Horizontal Rate + 255 kHz offset ");
    }

    printf("\n %9c %s" , Space1, "Minimum Vertical Rate:");
    if (*(data+5) != 0) {
        if ( ((*(data+4) & 0x03) == 0x03) ) {
            printf("%d", *(data+5) );
        } else {
            printf("%d", (*(data+5)) *2 );
        }
    } else {
        printf(" Reserved: Do Not Use ");
    }

    printf("\n %9c %s" , Space1, "Maximum Vertical Rate:");
    if (*(data+6) != 0) {
        if ( ((*(data+4) & 0x01) != 0x01) ) {
            printf("%d", *(data+6) );
        } else {
            printf("%d", (*(data+6)) * 2 );
        }
    } else {
        printf(" R      eserved: Do Not Use ");
    }


    printf("\n %9c %s" , Space1, "Minimum Horizontal Rate:");
    if (*(data+7) != 0) {
        if ( ((*(data+4) >> 2) & 0x03) == 0x03 ) {
            printf("%d", *(data+7) );
        } else {
            printf("%d", (*(data+7)) *2 );
        }
    } else {
        printf(" Reserved: Do Not Use ");
    }

    printf("\n %9c %s" , Space1, "Maximum Horizontal Rate:");
    if (*(data+8) != 0) {
        if ( ((*(data+4) >> 2) & 0x01) != 0x01 ) {
            printf("%d", *(data+8) );
        } else {
            printf("%d", (*(data+8)) * 2 );
        }
    } else {
        printf(" Reserved: Do Not Use ");
    }

    printf("\n %9c %s" , Space1, "Maximum Pixel clock:");
    if (*(data+9) != 0) {
        printf("%f MHz", (float)(*(data+8)) / 10 );
    } else {
        printf(" Reserved: Do Not Use ");
    }

    printf("\n %9c %s" , Space1, "Video Timing Support Flags:");
    if (*(data+10) == 0x03 || *(data+10) >= 0x05 ) {
        printf(" Reserved for future timing definitions --- Do Not Use. ");
    } else {
        if (*(data+10) == 0) {
            printf(" Default GTF supported if bit 0 in Feature Support Byte at address ");
        } else  if (*(data+10) == 0x01) {
            printf(" Range Limits Only --- no additional timing information is provided ");
        } else  if (*(data+10) == 0x02) {
            printf(" Secondary GTF supported --- requires support for Default GTF ");
        } else  if (*(data+10) == 0x04) {
            printf(" CVT supported if bit 0 in Feature Support Byte at address  ");
        }
    }

    if ( (*(data+10) == 0 || (*(data+10)) == 0x01) && (*(data+10) == 0x0A)) {
        printf(" Line Feed ");
    } else if (*(data+10) == 0x02 || *(data+10) == 0x04) {
        printf(" Video timing Data IN byte 11-17 Deskriptor");
    } else {
        printf(" Reserved ");
    }

}

void DisplayProductName(unsigned char *data, char **arr, size_t *arr_len) {
    
    char Data[] = "\n           Display Product Name is: ";
    int Size = sizeof(Data) + 13;
    
    char *result = malloc(Size);

    for( int i = 0; i < (int)sizeof(Data) ; i++ ){
        result[i] = Data[i];
    }

    for (int i = 5; i < 18;i++) {
        result[sizeof(Data) + (i-5) ] = *(data + i);
    }
    
    /* Set output parameters */
    *arr = result;
    *arr_len = Size;
  
}


void ColorPointDeskriptor(unsigned char *data) {

    for (int i = 5; i< 11;) {
        if (*(data+i) != 0) {
            printf("\n %9c %s %d" , Space1, "Index white point : ", *(data+i));
            printf("\n %9c %s" , Space1, "White     -   x, y: ");
            printf("\n %9c %s %5d %5d" , Space1,  "0    -", ((*(data+i+1)) >> 2)&0x01, ((*(data+i+1)) >> 0)&0x01);
            printf("\n %9c %s %5d %5d" , Space1,  "1    -", ((*(data+i+1)) >> 3)&0x01, ((*(data+i+1)) >> 1)&0x01);

            for (int l = 2; l < 10; l++) {
                printf("\n %9c %d %5d %5d" , Space1,  l, ((*(data+i+2)) >> (l-2))&0x01, ((*(data+i+3)) >> (l-2))&0x01);
            } 

            if ( *(data+i+4) == 0xff ) {
                printf("\n %9c %s" , Space1, "Gamma vallue not defined : ");
            } else {
                printf("\n %9c %s %d" , Space1, "Value Stored :", (*(data+i+4) * 100) - 100);
            }
        } else {
            printf("\n %9c %s" , Space1, "Index white point : Reserved not use");
        }
        i+=5;
    }

    printf("\n %9c %s %d" , Space1, "Line Feed (Byte 15 == 0x0A) : ", *(data+15));

    printf("\n %9c %s" , Space1, "Byte 16 and Byte 17 : Reserved) : " );


    





}

void StandartTiming(unsigned int *data) {

    printf("\n Standard Timing Identifier Definition:");
    printf("\n StandardTimingIdentification9 : , %d", ((*(data+5)) << 8) | *(data+6) );
    



}

void ColorManageDeskriptor(unsigned char *data) {

    printf("\n Color Management Data Descriptor Definitions:");
    printf("\n Version Number (Should be = 03h ) : %d", *(data+5) );

    uint ColorManage = 0;

    for (int i=0; i< 6; i++) {

        ColorManage = ((*(data+5)) << (7+i*2)) | *(data+(6+i*2));

        if (0 == i) {
            printf("\n Red a3: %d", ColorManage );
        } else if (1 == i) {
            printf("\n Red a2: %d", ColorManage );
        } else if (2 == i) {
            printf("\n Green a3: %d", ColorManage );
        } else if (3 == i)  {
            printf("\n Green a2: , %d", ColorManage );
        } else if (4 == i) {
            printf("\n Blu a3: , %d", ColorManage );
        } else if (5 == i) {
            printf("\n Blu a2: , %d", ColorManage );
        }
    }



}

void CVT3codeDeskriptor(unsigned int *data) {
    printf("\n This decryptor is not scheduled %d", *data );
}


void EsteblishTimingIII_Deskriptor(unsigned int *data) {
    printf("\n This decryptor is not scheduled %d", *data );
}


void Reserved_Deskriptor(unsigned int *data) {
    printf("\n This decryptor is not scheduled %d", *data );
}

void Dummy_Deskriptor(unsigned int *data) {
    printf("\n This decryptor is not scheduled %d", *data );
}

void Manufactur_Deskriptor(unsigned int *data) {
    printf("\n This decryptor is not scheduled %d", *data );
}