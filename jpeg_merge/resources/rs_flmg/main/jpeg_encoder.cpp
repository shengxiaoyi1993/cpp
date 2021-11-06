#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <memory.h>
#include <math.h>

#include "jpeg_encoder.h"

namespace {
//-------------------------------------------------------------------------------
const unsigned char Quantization_Table_1[64] =
{
   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1
};

//-------------------------------------------------------------------------------
const unsigned char Quantization_Table_2[64] =
{
   1,   1,   1,   1,   1,   2,   2,   2,
   1,   1,   1,   1,   2,   2,   2,   2,
   1,   1,   1,   2,   2,   2,   2,   2,
   1,   1,   2,   2,   2,   2,   2,   2,
   1,   2,   2,   2,   2,   2,   2,   2,
   2,   2,   2,   2,   2,   2,   2,   2,
   2,   2,   2,   2,   2,   2,   2,   2,
   2,   2,   2,   2,   2,   2,   2,   2
};

//-------------------------------------------------------------------------------
const unsigned char Quantization_Table_3[64] =
{
   1,   1,   1,   2,   2,   2,   4,   4,
   1,   1,   2,   2,   2,   4,   4,   4,
   1,   2,   2,   2,   4,   4,   4,   8,
   2,   2,   2,   4,   4,   4,   8,   8,
   2,   2,   4,   4,   4,   8,   8,   8,
   2,   4,   4,   4,   8,   8,   8,  16,
   4,   4,   4,   8,   8,   8,  16,  16,
   4,   4,   8,   8,   8,  16,  16,  16
};

//-------------------------------------------------------------------------------
const unsigned char Quantization_Table_4[64] =
{
   1,   1,   2,   2,   4,   4,   8,   8,
   1,   2,   2,   4,   4,   8,   8,  16,
   2,   2,   4,   4,   8,   8,  16,  16,
   2,   4,   4,   8,   8,  16,  16,  32,
   4,   4,   8,   8,  16,  16,  32,  32,
   4,   8,   8,  16,  16,  32,  32,  32,
   8,   8,  16,  16,  32,  32,  32,  32,
   8,  16,  16,  32,  32,  32,  32,  32
};

//-------------------------------------------------------------------------------
const unsigned char Luminance_Quantization_Table[64] =
{
  16,  11,  10,  16,  24,  40,  51,  61,
  12,  12,  14,  19,  26,  58,  60,  55,
  14,  13,  16,  24,  40,  57,  69,  56,
  14,  17,  22,  29,  51,  87,  80,  62,
  18,  22,  37,  56,  68, 109, 103,  77,
  24,  35,  55,  64,  81, 104, 113,  92,
  49,  64,  78,  87, 103, 121, 120, 101,
  72,  92,  95,  98, 112, 100, 103,  99
};

//-------------------------------------------------------------------------------
const unsigned char Chrominance_Quantization_Table[64] =
{
  17,  18,  24,  47,  99,  99,  99,  99,
  18,  21,  26,  66,  99,  99,  99,  99,
  24,  26,  56,  99,  99,  99,  99,  99,
  47,  66,  99,  99,  99,  99,  99,  99,
  99,  99,  99,  99,  99,  99,  99,  99,
  99,  99,  99,  99,  99,  99,  99,  99,
  99,  99,  99,  99,  99,  99,  99,  99,
  99,  99,  99,  99,  99,  99,  99,  99
};

//-------------------------------------------------------------------------------
const char ZigZag[64] =
{
  0, 1, 5, 6,14,15,27,28,
  2, 4, 7,13,16,26,29,42,
  3, 8,12,17,25,30,41,43,
  9,11,18,24,31,40,44,53,
  10,19,23,32,39,45,52,54,
  20,22,33,38,46,51,55,60,
  21,34,37,47,50,56,59,61,
  35,36,48,49,57,58,62,63
};

//-------------------------------------------------------------------------------
const char Standard_DC_Luminance_NRCodes[] = { 0, 0, 7, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
const unsigned char Standard_DC_Luminance_Values[] = { 4, 5, 3, 2, 6, 1, 0, 7, 8, 9, 10, 11 };

//-------------------------------------------------------------------------------
const char Standard_DC_Chrominance_NRCodes[] = { 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 };
const unsigned char Standard_DC_Chrominance_Values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

//-------------------------------------------------------------------------------
const char Standard_AC_Luminance_NRCodes[] = { 0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7d };
const unsigned char Standard_AC_Luminance_Values[] =
{
  0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
  0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
  0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
  0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
  0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
  0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
  0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
  0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
  0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
  0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
  0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
  0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
  0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
  0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
  0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
  0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
  0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
  0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
  0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
  0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
  0xf9, 0xfa
};

//-------------------------------------------------------------------------------
const char Standard_AC_Chrominance_NRCodes[] = { 0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 0x77 };
const unsigned char Standard_AC_Chrominance_Values[] =
{
  0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21,
  0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
  0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
  0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0,
  0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34,
  0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26,
  0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38,
  0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
  0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
  0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
  0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
  0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
  0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
  0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
  0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4,
  0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
  0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2,
  0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
  0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
  0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
  0xf9, 0xfa
};

}

//-------------------------------------------------------------------------------
JpegEncoder::JpegEncoder()
  : m_width(0)
  , m_height(0)
  , m_rgbBuffer(0)
  //<> by SXY
  ,m_dri(8)
{
  //初始化静态表格
  _initHuffmanTables();
}

//-------------------------------------------------------------------------------
JpegEncoder::~JpegEncoder()
{
  clean();
}

//-------------------------------------------------------------------------------
void JpegEncoder::clean(void)
{
  if(m_rgbBuffer) delete[] m_rgbBuffer;
  m_rgbBuffer=0;

  m_width=0;
  m_height=0;
}


//-------------------------------------------------------------------------------
bool JpegEncoder::readFromPPM(const char* fileName)
{
  char line[1024];
  char *p;
  int cols, rows, maxval;

  //清理旧数据
  clean();

  //打开文件
  FILE* fp = fopen(fileName, "rb");
  if(fp==0) return false;

  bool successed=false;

  // all break to jump out process
  do {
    // if read comment line, then read again
    do {
      p = fgets(line, sizeof(line), fp);
    } while (p != NULL && *p == '#');
    if (p == NULL) break;

    // if not P6 mode PPM, break
    if (strncmp(line, "P6", 2) != 0) {
      printf("PPM format not P6\n");
      break;
    }

    if (strlen(line) > 3) {
      // if all parameter in same line
      if (sscanf(line+2, "%d %d %d", &cols, &rows, &maxval) != 3) break;
    } else {
      // if read comment line, then read again
      do {
        p = fgets(line, sizeof(line), fp);
      } while (p != NULL && *p == '#');
      if (p == NULL) break;

      // read cols and rows
      if (sscanf(line, "%d %d", &cols, &rows) != 2) break;

      // if read comment line, then read again
      do {
        p = fgets(line, sizeof(line), fp);
      } while (p != NULL && *p == '#');
      if (p == NULL) break;

      // read maxval
      if (sscanf(line, "%d", &maxval) != 1) break;
    }

    printf("PPM read header success, cols = %d, rows = %d, maxval = %d\n", cols, rows, maxval);

    int bufsize = cols*rows*3;
    unsigned char *buffer = new unsigned char[bufsize];

    if (fread(buffer, 1, bufsize, fp) == 0) {
      printf("PPM read data, not enough pixel in file\n");
      delete[] buffer;
      buffer = 0;
      break;
    }

    m_rgbBuffer = buffer;
    m_width = cols;
    m_height = rows;
    successed = true;

  } while (false);

  fclose(fp);fp=0;

  return successed;
}

//-------------------------------------------------------------------------------
bool JpegEncoder::encodeToJPG(const char* fileName, int quality_scale)
{
  //尚未读取？
  if(m_rgbBuffer==0 || m_width==0 || m_height==0) return false;

  //输出文件
  FILE* fp = fopen(fileName, "wb");
  if(fp==0) return false;

  //初始化量化表
  _initQualityTables(quality_scale);

  //文件头
  _write_jpeg_header(fp);

  short prev_DC_Y = 0, prev_DC_Cb = 0, prev_DC_Cr = 0;
  int newByte=0, newBytePos=7;

  //<> by SXY
  int counter_rst=0;
  unsigned short counter_mcu=0;

  for(int yPos=0; yPos<m_height; yPos+=8)
  {
    for (int xPos=0; xPos<m_width; xPos+=8)
    {
      char yData[64], cbData[64], crData[64];
      float yFdc[64], cbFdc[64], crFdc[64];
      float yLfdc[64], cbLfdc[64], crLfdc[64];
      short yQuant[64], cbQuant[64], crQuant[64];

      //转换颜色空间
      _convertColorSpace(xPos, yPos, yData, cbData, crData);

      BitString outputBitString[128];
      int bitStringCounts;

      //Y通道压缩
      _foword_FDC(yData, yFdc);
      for (int i=0; i<64; i++) {
        yQuant[i] = (short)((short)((yFdc[i]/m_YTable[i]) + 16384.5) - 16384);
      }
      // _doHuffmanEncoding(yQuant, prev_DC_Y, m_Y_DC_Huffman_Table, m_Y_AC_Huffman_Table, outputBitString, bitStringCounts);
      _doHuffmanEncodingAll(yQuant, prev_DC_Y, m_Huffman_Table, 0, outputBitString, bitStringCounts);
      _write_bitstring_(outputBitString, bitStringCounts, newByte, newBytePos, fp);

      //Cb通道压缩
      _foword_FDC(cbData, cbFdc);
      for (int i=0; i<64; i++) {
        cbQuant[i] = (short)((short)((cbFdc[i]/m_CbCrTable[i]) + 16384.5) - 16384);
      }
      // _doHuffmanEncoding(cbQuant, prev_DC_Cb, m_CbCr_DC_Huffman_Table, m_CbCr_AC_Huffman_Table, outputBitString, bitStringCounts);
      _doHuffmanEncodingAll(cbQuant, prev_DC_Cb, m_Huffman_Table, 1, outputBitString, bitStringCounts);
      _write_bitstring_(outputBitString, bitStringCounts, newByte, newBytePos, fp);

      //Cr通道压缩
      _foword_FDC(crData, crFdc);
      for (int i=0; i<64; i++) {
        crQuant[i] = (short)((short)((crFdc[i]/m_CbCrTable[i]) + 16384.5) - 16384);
      }
      // _doHuffmanEncoding(crQuant, prev_DC_Cr, m_CbCr_DC_Huffman_Table, m_CbCr_AC_Huffman_Table, outputBitString, bitStringCounts);
      _doHuffmanEncodingAll(crQuant, prev_DC_Cr, m_Huffman_Table, 1, outputBitString, bitStringCounts);
      _write_bitstring_(outputBitString, bitStringCounts, newByte, newBytePos, fp);

      //<> by SXY
      //if counter_mcu can be divede by m_dri,insert a rst
      counter_mcu++;
      counter_mcu=counter_mcu%8;
      if (counter_mcu == 0) {
        _write_bytealign_(newByte, newBytePos, fp);
        newByte=0;
        newBytePos=7;
        _write_word_(0xFFD0|counter_rst, fp);
        counter_rst++;
        counter_rst=counter_rst%8;
        prev_DC_Y = 0;
        prev_DC_Cb = 0;
        prev_DC_Cr = 0;

      }

    }
  }

  printf("newByte = 0x%2x, newBytePos = %d\n", newByte, newBytePos);
  _write_bytealign_(newByte, newBytePos, fp);

  _write_word_(0xFFD9, fp); //Write End of Image Marker

  fclose(fp);

  return true;
}


//-------------------------------------------------------------------------------
bool JpegEncoder::encodeToJPGbw(const char* fileName, int quality_scale)
{
  //尚未读取？
  if(m_rgbBuffer==0 || m_width==0 || m_height==0) return false;

  //输出文件
  FILE* fp = fopen(fileName, "wb");
  if(fp==0) return false;

  //初始化量化表
  _initQualityTables(quality_scale);

  //文件头
  _write_jpeg_header_bw(fp);

  short prev_DC_Y = 0, prev_DC_Cb = 0, prev_DC_Cr = 0;
  int newByte=0, newBytePos=7;

  //<> by SXY
  int counter_rst=0;
  unsigned short counter_mcu=0;

  for(int yPos=0; yPos<m_height; yPos+=8)
  {
    for (int xPos=0; xPos<m_width; xPos+=8)
    {
      char yData[64], cbData[64], crData[64];
      float yFdc[64], cbFdc[64], crFdc[64];
      float yLfdc[64], cbLfdc[64], crLfdc[64];
      short yQuant[64], cbQuant[64], crQuant[64];

      //转换颜色空间
      _convertColorSpace(xPos, yPos, yData, cbData, crData);
      printf("yPos = %d, xPos = %d \n", yPos, xPos);

      // if (yPos == 8 && xPos == 280) {
      //   for (int j=0; j<8; j++) {
      //     for (int i=0; i<8; i++) {
      //       printf("%4d ", yData[j*8+i]);
      //     }
      //     printf("\n");
      //   }
      // }

      // for (int i=0; i<64; i++) {
      //   printf("%3d ", yData[i]);
      // }
      // printf("\n");



      BitString outputBitString[128];
      int bitStringCounts;

      //Y通道压缩
      _foword_FDC(yData, yFdc);

      // for (int i=0; i<64; i++) {
      //   printf("%4f ", (float)yFdc[i]);
      // }
      // printf("\n");

      for (int i=0; i<64; i++) {
        yQuant[i] = (short)((short)((yFdc[i]/m_YTable[i]) + 16384.5) - 16384);
      }

      for (int i=0; i<64; i++) {
        printf("%3d ", yQuant[i]);
      }
      printf("\n");

      _doHuffmanEncoding(yQuant, prev_DC_Y, m_Y_DC_Huffman_Table, m_Y_AC_Huffman_Table, outputBitString, bitStringCounts);
      // _doHuffmanEncodingAll(yQuant, prev_DC_Y, m_Huffman_Table, 0, outputBitString, bitStringCounts);
      _write_bitstring_(outputBitString, bitStringCounts, newByte, newBytePos, fp);

      //<> by SXY
      //if counter_mcu can be divede by m_dri,insert a rst
      counter_mcu++;
      counter_mcu=counter_mcu%8;
      if (counter_mcu == 0) {
        _write_bytealign_(newByte, newBytePos, fp);
        newByte=0;
        newBytePos=7;
        _write_word_(0xFFD0|counter_rst, fp);
        counter_rst++;
        counter_rst=counter_rst%8;
        prev_DC_Y = 0;
        prev_DC_Cb = 0;
        prev_DC_Cr = 0;

      }

    }
  }

  printf("newByte = 0x%2x, newBytePos = %d\n", newByte, newBytePos);
  _write_bytealign_(newByte, newBytePos, fp);

  _write_word_(0xFFD9, fp); //Write End of Image Marker

  fclose(fp);

  return true;
}

//-------------------------------------------------------------------------------
void JpegEncoder::_initHuffmanTables(void)
{
  memset(&m_Y_DC_Huffman_Table, 0, sizeof(m_Y_DC_Huffman_Table));
  _computeHuffmanTable(Standard_DC_Luminance_NRCodes, Standard_DC_Luminance_Values, m_Y_DC_Huffman_Table);

  memset(&m_Y_AC_Huffman_Table, 0, sizeof(m_Y_AC_Huffman_Table));
  _computeHuffmanTable(Standard_AC_Luminance_NRCodes, Standard_AC_Luminance_Values, m_Y_AC_Huffman_Table);

  memset(&m_CbCr_DC_Huffman_Table, 0, sizeof(m_CbCr_DC_Huffman_Table));
  _computeHuffmanTable(Standard_DC_Chrominance_NRCodes, Standard_DC_Chrominance_Values, m_CbCr_DC_Huffman_Table);

  memset(&m_CbCr_AC_Huffman_Table, 0, sizeof(m_CbCr_AC_Huffman_Table));
  _computeHuffmanTable(Standard_AC_Chrominance_NRCodes, Standard_AC_Chrominance_Values, m_CbCr_AC_Huffman_Table);

  memset(&m_Huffman_Table, 0, sizeof(m_Huffman_Table));
  for (int j=0; j<16; j++) {
    for (int i=0; i<11; i++) {
      m_Huffman_Table[j*16+i] = m_Y_AC_Huffman_Table[j*16+i];
      m_Huffman_Table[(j+16)*16+i] = m_CbCr_AC_Huffman_Table[j*16+i];
    }
  }
  for (int j=0; j<12; j++) {
      m_Huffman_Table[j*16+12] = m_Y_DC_Huffman_Table[j];
      m_Huffman_Table[(j+16)*16+12] = m_CbCr_DC_Huffman_Table[j];
  }

  /*
  printf("m_Y_DC_Huffman_Table is :\n");
  for (int i=0; i<12; i++) {
    printf("loc %d, length = %d, value = 0x%4x\n", i, m_Y_DC_Huffman_Table[i].length, m_Y_DC_Huffman_Table[i].value);
  }

  printf("m_Y_AC_Huffman_Table is :\n");
  for (int j=0; j<16; j++) {
    printf("line %2d ", j);
    for (int i=0; i<16; i++) {
      printf("'%2d, 0x%4x ", m_Y_AC_Huffman_Table[j*16+i].length, m_Y_AC_Huffman_Table[j*16+i].value);
    }
    printf("\n");
  }

  printf("m_CbCr_DC_Huffman_Table is :\n");
  for (int i=0; i<12; i++) {
    printf("loc %d, length = %d, value = 0x%4x\n", i, m_CbCr_DC_Huffman_Table[i].length, m_CbCr_DC_Huffman_Table[i].value);
  }

  printf("m_CbCr_AC_Huffman_Table is :\n");
  for (int j=0; j<16; j++) {
    printf("line %2d ", j);
    for (int i=0; i<16; i++) {
      printf("'%2d, 0x%4x ", m_CbCr_AC_Huffman_Table[j*16+i].length, m_CbCr_AC_Huffman_Table[j*16+i].value);
    }
    printf("\n");
  }

  printf("m_Huffman_Table is :\n");
  for (int j=0; j<32; j++) {
    printf("line %2d ", j);
    for (int i=0; i<16; i++) {
      printf("'%2d, 0x%4x ", m_Huffman_Table[j*16+i].length, m_Huffman_Table[j*16+i].value);
    }
    printf("\n");
  }
  */


}
//-------------------------------------------------------------------------------
JpegEncoder::BitString JpegEncoder::_getBitCode(int value)
{
  BitString ret;
  int v = (value>0) ? value : -value;

  //bit 的长度
  int length = 0;
  for(length=0; v; v>>=1) length++;

  ret.value = value>0 ? value : ((1<<length)+value-1);
  ret.length = length;

  return ret;
};

//-------------------------------------------------------------------------------
// Scale the Quant table, and zigzag it
void JpegEncoder::_initQualityTables(int quality_scale)
{
  if(quality_scale<=0) quality_scale=1;
  if(quality_scale>=100) quality_scale=99;

  for(int i=0; i<64; i++)
  {
    // int temp = ((int)(Luminance_Quantization_Table[i] * quality_scale + 50) / 100);
    int temp = Quantization_Table_2[i];
    if (temp<=0) temp = 1;
    if (temp>0xFF) temp = 0xFF;
    m_YTable[ZigZag[i]] = (unsigned char)temp;

    // temp = ((int)(Chrominance_Quantization_Table[i] * quality_scale + 50) / 100);
    temp = Quantization_Table_2[i];
    if (temp<=0)   temp = 1;
    if (temp>0xFF) temp = 0xFF;
    m_CbCrTable[ZigZag[i]] = (unsigned char)temp;
  }
}

//-------------------------------------------------------------------------------
void JpegEncoder::_computeHuffmanTable(const char* nr_codes, const unsigned char* std_table, BitString* huffman_table)
{
  unsigned char pos_in_table = 0;
  unsigned short code_value = 0;

  for(int k = 1; k <= 16; k++)
  {
    for(int j = 1; j <= nr_codes[k-1]; j++)
    {
      huffman_table[std_table[pos_in_table]].value = code_value;
      huffman_table[std_table[pos_in_table]].length = k;
      pos_in_table++;
      code_value++;
    }
    code_value <<= 1;
  }
}

//-------------------------------------------------------------------------------
void JpegEncoder::_write_byte_(unsigned char value, FILE* fp)
{
  _write_(&value, 1, fp);
}

//-------------------------------------------------------------------------------
void JpegEncoder::_write_word_(unsigned short value, FILE* fp)
{
  unsigned short _value = ((value>>8)&0xFF) | ((value&0xFF)<<8);
  _write_(&_value, 2, fp);
}

//-------------------------------------------------------------------------------
void JpegEncoder::_write_(const void* p, int byteSize, FILE* fp)
{
  fwrite(p, 1, byteSize, fp);
}

//-------------------------------------------------------------------------------
void JpegEncoder::_doHuffmanEncoding(const short* DU, short& prevDC, const BitString* HTDC, const BitString* HTAC,
  BitString* outputBitString, int& bitStringCounts)
{
  BitString EOB = HTAC[0x00];
  BitString SIXTEEN_ZEROS = HTAC[0xF0];

  int index=0;

  // encode DC
  int dcDiff = (int)(DU[0] - prevDC);
  prevDC = DU[0];

  if (dcDiff == 0)
    outputBitString[index++] = HTDC[0];
  else
  {
    BitString bs = _getBitCode(dcDiff);

    outputBitString[index++] = HTDC[bs.length];
    outputBitString[index++] = bs;
  }

  // encode ACs
  int endPos=63; //end0pos = first element in reverse order != 0
  while((endPos > 0) && (DU[endPos] == 0)) endPos--;

  for(int i=1; i<=endPos; )
  {
    int startPos = i;
    while((DU[i] == 0) && (i <= endPos)) i++;

    int zeroCounts = i - startPos;
    if (zeroCounts >= 16)
    {
      for (int j=1; j<=zeroCounts/16; j++)
        outputBitString[index++] = SIXTEEN_ZEROS;
      zeroCounts = zeroCounts%16;
    }

    BitString bs = _getBitCode(DU[i]);

    outputBitString[index++] = HTAC[(zeroCounts << 4) | bs.length];
    outputBitString[index++] = bs;
    i++;
  }

  if (endPos != 63)
    outputBitString[index++] = EOB;

  bitStringCounts = index;

  // printf("Encode sets for this block is %d\n", index);
}

//-------------------------------------------------------------------------------
void JpegEncoder::_doHuffmanEncodingAll(const short* DU, short& prevDC, const BitString* HT, int isCrCb,
  BitString* outputBitString, int& bitStringCounts)
{

  int index=0;

  // encode DC
  int dcDiff = (int)(DU[0] - prevDC);
  prevDC = DU[0];

  if (dcDiff == 0)
    // DC 0
    outputBitString[index++] = HT[0*16+12+isCrCb*256];
  else
  {
    BitString bs = _getBitCode(dcDiff);

    outputBitString[index++] = HT[bs.length*16+12+isCrCb*256];
    outputBitString[index++] = bs;
  }

  // encode ACs
  int endPos=63; //end0pos = first element in reverse order != 0
  while((endPos > 0) && (DU[endPos] == 0)) endPos--;

  for(int i=1; i<=endPos; )
  {
    int startPos = i;
    while((DU[i] == 0) && (i <= endPos)) i++;

    int zeroCounts = i - startPos;
    if (zeroCounts >= 16)
    {
      for (int j=1; j<=zeroCounts/16; j++)
        // 16 zeros
        outputBitString[index++] = HT[0xF0+isCrCb*256];
      zeroCounts = zeroCounts%16;
    }

    BitString bs = _getBitCode(DU[i]);

    outputBitString[index++] = HT[((zeroCounts << 4) | bs.length) + isCrCb*256];
    outputBitString[index++] = bs;
    i++;
  }

  if (endPos != 63)
    // end of block
    outputBitString[index++] = HT[0x00 + isCrCb*256];

  bitStringCounts = index;

  // printf("Encode sets for this block is %d\n", index);
}

//-------------------------------------------------------------------------------
void JpegEncoder::_write_bitstring_(const BitString* bs, int counts, int& newByte, int& newBytePos, FILE* fp)
{
  unsigned short mask[] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};

  for(int i=0; i<counts; i++)
  {
    int value = bs[i].value;
    int posval = bs[i].length - 1;

    while (posval >= 0)
    {
      if ((value & mask[posval]) != 0)
      {
        newByte = newByte  | mask[newBytePos];
      }
      posval--;
      newBytePos--;
      if (newBytePos < 0)
      {
        // Write to stream
        _write_byte_((unsigned char)(newByte), fp);
        if (newByte == 0xFF)
        {
          // Handle special case
          _write_byte_((unsigned char)(0x00), fp);
        }

        // Reinitialize
        newBytePos = 7;
        newByte = 0;
      }
    }
  }
}

//-------------------------------------------------------------------------------
void JpegEncoder::_write_bytealign_(int& newByte, int& newBytePos, FILE* fp)
{
  unsigned short mask[] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};

  // only when it's not byte aligned, needs to write byte aligned
  while (newBytePos >= 0 && newBytePos < 7)
  {
    newByte = newByte  | mask[newBytePos];
    newBytePos--;
    if (newBytePos < 0)
    {
      // Write to stream
      _write_byte_((unsigned char)(newByte), fp);
      if (newByte == 0xFF)
      {
        // Handle special case
        _write_byte_((unsigned char)(0x00), fp);
      }

      // Reinitialize
      newBytePos = 7;
      newByte = 0;
    }
  }
}

//-------------------------------------------------------------------------------
void JpegEncoder::_convertColorSpace(int xPos, int yPos, char* yData, char* cbData, char* crData)
{
  for (int y=0; y<8; y++)
  {
    unsigned char* p = m_rgbBuffer + (y+yPos)*m_width*3 + xPos*3;
    for (int x=0; x<8; x++)
    {
      unsigned char R = *p++;
      unsigned char G = *p++;
      unsigned char B = *p++;

      yData[y*8+x] = (char)(0.299f * R + 0.587f * G + 0.114f * B - 128);
      // yData[y*8+x] = (char)(0.299f * R + 0.587f * G + 0.114f * B);
      cbData[y*8+x] = (char)(-0.1687f * R - 0.3313f * G + 0.5f * B );
      crData[y*8+x] = (char)(0.5f * R - 0.4187f * G - 0.0813f * B);
    }
  }
}

//-------------------------------------------------------------------------------
void JpegEncoder::_foword_FDC(const char* channel_data, float* fdc_data)
{
  const float PI = 3.1415926f;

  for(int v=0; v<8; v++)
  {
    for(int u=0; u<8; u++)
    {
      float alpha_u = (u==0) ? 1/sqrt(2.0f) : 1.0f;
      float alpha_v = (v==0) ? 1/sqrt(2.0f) : 1.0f;

      float temp = 0.f;
      for(int x=0; x<8; x++)
      {
        for(int y=0; y<8; y++)
        {
          float data = channel_data[y*8+x];

          data *= cos((2*x+1)*u*PI/16.0f);
          data *= cos((2*y+1)*v*PI/16.0f);

          temp += data;
        }
      }

      // temp *= alpha_u*alpha_v/m_YTable[ZigZag[v*8+u]];
      // fdc_data[ZigZag[v*8+u]] = (short) ((short)(temp + 16384.5) - 16384);

      fdc_data[ZigZag[v*8+u]] = temp * alpha_u * alpha_v/4.0f;
    }
  }
}

//-------------------------------------------------------------------------------
void JpegEncoder::_foword_LFDC(const char* channel_data, float* fdc_data)
{
  const float PI = 3.1415926f;
  float mat_z[64], mat_zt[64], mat_d[64], mat_dt[64];
  // u, x, i for col, horizontal
  // v, y, j for row, vertical

  for (int j=0; j<8; j++) {
    for (int i=0; i<8; i++) {
      float alpha = (i==0) ? 1/sqrt(2.0f) : 1.0f;

      float temp = 0.f;

      for (int x=0; x<8; x++) {
        float data = channel_data[j*8+x];
        temp += alpha*data*cos((2*x+1)*i*PI/16.0f);
      }
      mat_z[j*8+i] = sqrt(2.0f)*temp;
    }
  }

  for (int j=0; j<8; j++) {
    for (int i=0; i<8; i++) {
      mat_zt[j*8+i] = mat_z[i*8+j];
    }
  }

  for (int j=0; j<8; j++) {
    for (int i=0; i<8; i++) {
      float alpha = (i==0) ? 1/sqrt(2.0f) : 1.0f;

      float temp = 0.f;

      for (int x=0; x<8; x++) {
        float data = mat_zt[j*8+x];
        temp += alpha*data*cos((2*x+1)*i*PI/16.0f);
      }
      mat_d[j*8+i] = sqrt(2.0f)*temp;
    }
  }

  for (int j=0; j<8; j++) {
    for (int i=0; i<8; i++) {
      mat_dt[j*8+i] = mat_d[i*8+j];
    }
  }

  for (int j=0; j<8; j++) {
    for (int i=0; i<8; i++) {
      fdc_data[ZigZag[j*8+i]] = mat_dt[j*8+i]/8.0f;
    }
  }
}

//-------------------------------------------------------------------------------
void JpegEncoder::_write_jpeg_header(FILE* fp)
{
  //SOI
  _write_word_(0xFFD8, fp);    // marker = 0xFFD8

  // Comment
  _write_word_(0xFFFE, fp);    // comment
  _write_word_(32, fp);      // 2 for length, 16 for comment, 14 for www.dgvtec.com
  _write_word_(0x0102, fp);    //
  _write_word_(0x0304, fp);    //
  _write_word_(0x0506, fp);    //
  _write_word_(0x0708, fp);    //
  _write_word_(0x090a, fp);    //
  _write_word_(0x0b0c, fp);    //
  _write_word_(0x0d0e, fp);    //
  _write_word_(0x0f00, fp);    //
  _write_word_(0x7777, fp);    // ww  lsb[4] msb[4]
  _write_word_(0x77e2, fp);    // w.  lsb[4] msb[4]
  _write_word_(0x4676, fp);    // dg  lsb[4] msb[4]
  _write_word_(0x6747, fp);    // vt  lsb[4] msb[4]
  _write_word_(0x5636, fp);    // ec  lsb[4] msb[4]
  _write_word_(0xe236, fp);    // .c  lsb[4] msb[4]
  _write_word_(0xf6d6, fp);    // om  lsb[4] msb[4]

  //APPO
  _write_word_(0xFFE0,fp);    // marker = 0xFFE0
  _write_word_(16, fp);      // length = 16 for usual JPEG, no thumbnail
  _write_("JFIF", 5, fp);      // 'JFIF\0'
  _write_word_(0x0101,fp);    // version
  _write_byte_(0, fp);      // xyunits = 0 no units, normal density
  _write_word_(1, fp);      // xdensity
  _write_word_(1, fp);      // ydensity
  _write_byte_(0, fp);      // thumbWidth
  _write_byte_(0, fp);      // thumbHeight

  //DQT
  _write_word_(0xFFDB, fp);    //marker = 0xFFDB
  _write_word_(132, fp);      //size=132
  _write_byte_(0, fp);      //QTYinfo== 0:  bit 0..3: number of QT = 0 (table for Y)
                  //        bit 4..7: precision of QT, 0 means baseline
  _write_(m_YTable, 64, fp);    //YTable
  _write_byte_(1, fp);      //QTCbinfo = 1 (quantization table for Cb,Cr)
  _write_(m_CbCrTable, 64, fp);  //CbCrTable

  //SOFO
  _write_word_(0xFFC0, fp);      //marker = 0xFFC0
  _write_word_(17, fp);        //length = 17 for a truecolor YCbCr JPG
  _write_byte_(8, fp);        //precision = 8: 8 bits/sample
  _write_word_(m_height&0xFFFF, fp);  //height
  _write_word_(m_width&0xFFFF, fp);  //width
  _write_byte_(3, fp);        //nrofcomponents = 3: We encode a truecolor JPG

  _write_byte_(1, fp);        //IdY = 1
  _write_byte_(0x11, fp);        //HVY sampling factors for Y (bit 0-3 vert., 4-7 hor.)(SubSamp 1x1)
  _write_byte_(0, fp);        //QTY  Quantization Table number for Y = 0

  _write_byte_(2, fp);        //IdCb = 2
  _write_byte_(0x11, fp);        //HVCb = 0x11(SubSamp 1x1)
  _write_byte_(1, fp);        //QTCb = 1

  _write_byte_(3, fp);        //IdCr = 3
  _write_byte_(0x11, fp);        //HVCr = 0x11 (SubSamp 1x1)
  _write_byte_(1, fp);        //QTCr Normally equal to QTCb = 1

  //<>by SXY
  //DRI
  _write_word_(0xFFDD, fp);    //marker = 0xFFDD
  _write_word_(0x4, fp);    //
  _write_word_(m_dri, fp);    //the number of MCUs between Interval,must divide width with no remainder
  //possible width is 4096/1920, proper value 8/16

  //DHT
  _write_word_(0xFFC4, fp);    //marker = 0xFFC4
  _write_word_(0x01A2, fp);    //length = 0x01A2
  _write_byte_(0, fp);      //HTYDCinfo bit 0..3  : number of HT (0..3), for Y =0
                  //      bit 4    : type of HT, 0 = DC table,1 = AC table
                  //      bit 5..7  : not used, must be 0
  _write_(Standard_DC_Luminance_NRCodes, sizeof(Standard_DC_Luminance_NRCodes), fp);  //DC_L_NRC
  _write_(Standard_DC_Luminance_Values, sizeof(Standard_DC_Luminance_Values), fp);    //DC_L_VALUE
  _write_byte_(0x10, fp);      //HTYACinfo
  _write_(Standard_AC_Luminance_NRCodes, sizeof(Standard_AC_Luminance_NRCodes), fp);
  _write_(Standard_AC_Luminance_Values, sizeof(Standard_AC_Luminance_Values), fp); //we'll use the standard Huffman tables
  _write_byte_(0x01, fp);      //HTCbDCinfo
  _write_(Standard_DC_Chrominance_NRCodes, sizeof(Standard_DC_Chrominance_NRCodes), fp);
  _write_(Standard_DC_Chrominance_Values, sizeof(Standard_DC_Chrominance_Values), fp);
  _write_byte_(0x11, fp);      //HTCbACinfo
  _write_(Standard_AC_Chrominance_NRCodes, sizeof(Standard_AC_Chrominance_NRCodes), fp);
  _write_(Standard_AC_Chrominance_Values, sizeof(Standard_AC_Chrominance_Values), fp);

  //SOS
  _write_word_(0xFFDA, fp);    //marker = 0xFFDA
  _write_word_(12, fp);      //length = 12
  _write_byte_(3, fp);      //nrofcomponents, Should be 3: truecolor JPG

  _write_byte_(1, fp);      //Idy=1
  _write_byte_(0, fp);      //HTY  bits 0..3: AC table (0..3)
                  //    bits 4..7: DC table (0..3)
  _write_byte_(2, fp);      //IdCb
  _write_byte_(0x11, fp);      //HTCb

  _write_byte_(3, fp);      //IdCr
  _write_byte_(0x11, fp);      //HTCr

  _write_byte_(0, fp);      //Ss not interesting, they should be 0,63,0
  _write_byte_(0x3F, fp);      //Se
  _write_byte_(0, fp);      //Bf
}

//-------------------------------------------------------------------------------
void JpegEncoder::_write_jpeg_header_bw(FILE* fp)
{
  //SOI
  _write_word_(0xFFD8, fp);    // marker = 0xFFD8

  // Comment
  _write_word_(0xFFFE, fp);     // comment, marker = 0xFFFE
  _write_word_(32, fp);         // 2 for length, 16 for comment, 14 for www.dgvtec.com
  _write_word_(0x0102, fp);     //
  _write_word_(0x0304, fp);     //
  _write_word_(0x0506, fp);     //
  _write_word_(0x0708, fp);     //
  _write_word_(0x090a, fp);     //
  _write_word_(0x0b0c, fp);     //
  _write_word_(0x0d0e, fp);     //
  _write_word_(0x0f00, fp);     //
  _write_word_(0x7777, fp);     // ww  lsb[4] msb[4]
  _write_word_(0x77e2, fp);     // w.  lsb[4] msb[4]
  _write_word_(0x4676, fp);     // dg  lsb[4] msb[4]
  _write_word_(0x6747, fp);     // vt  lsb[4] msb[4]
  _write_word_(0x5636, fp);     // ec  lsb[4] msb[4]
  _write_word_(0xe236, fp);     // .c  lsb[4] msb[4]
  _write_word_(0xf6d6, fp);     // om  lsb[4] msb[4]

  //APPO
  _write_word_(0xFFE0,fp);    // marker = 0xFFE0
  _write_word_(16, fp);      // length = 16 for usual JPEG, no thumbnail
  _write_("JFIF", 5, fp);      // 'JFIF\0'
  _write_word_(0x0101,fp);    // version
  _write_byte_(0, fp);      // xyunits = 0 no units, normal density
  _write_word_(1, fp);      // xdensity
  _write_word_(1, fp);      // ydensity
  _write_byte_(0, fp);      // thumbWidth
  _write_byte_(0, fp);      // thumbHeight

  //DQT
  _write_word_(0xFFDB, fp);    //marker = 0xFFDB
  _write_word_(67, fp);      //size=67
  _write_byte_(0, fp);      //QTYinfo== 0:  bit 0..3: number of QT = 0 (table for Y)
                  //        bit 4..7: precision of QT, 0 means baseline
  _write_(m_YTable, 64, fp);    //YTable

  //SOFO
  _write_word_(0xFFC0, fp);      //marker = 0xFFC0
  _write_word_(11, fp);        //length = 17 for a truecolor YCbCr JPG
  _write_byte_(8, fp);        //precision = 8: 8 bits/sample
  _write_word_(m_height&0xFFFF, fp);  //height
  _write_word_(m_width&0xFFFF, fp);  //width
  _write_byte_(1, fp);        //nrofcomponents = 3: We encode a truecolor JPG

  _write_byte_(1, fp);        //IdY = 1
  _write_byte_(0x11, fp);        //HVY sampling factors for Y (bit 0-3 vert., 4-7 hor.)(SubSamp 1x1)
  _write_byte_(0, fp);        //QTY  Quantization Table number for Y = 0

  //<> by SXY
//DRI
_write_word_(0xFFDD, fp);    //marker = 0xFFDD
_write_word_(0x4, fp);    //
_write_word_(m_dri, fp);    //the number of MCUs between Interval,must divide width with no remainder
//possible width is 4096/1920, proper value 8/16

  //DHT
  _write_word_(0xFFC4, fp);    //marker = 0xFFC4
  // _write_word_(0x01A2, fp);    //length = 0x01A2
  _write_word_(210, fp);    //length = 0x01A2
  _write_byte_(0, fp);      //HTYDCinfo bit 0..3  : number of HT (0..3), for Y =0
                  //      bit 4    : type of HT, 0 = DC table,1 = AC table
                  //      bit 5..7  : not used, must be 0
  _write_(Standard_DC_Luminance_NRCodes, sizeof(Standard_DC_Luminance_NRCodes), fp);  //DC_L_NRC
  _write_(Standard_DC_Luminance_Values, sizeof(Standard_DC_Luminance_Values), fp);    //DC_L_VALUE
  _write_byte_(0x10, fp);      //HTYACinfo
  _write_(Standard_AC_Luminance_NRCodes, sizeof(Standard_AC_Luminance_NRCodes), fp);
  _write_(Standard_AC_Luminance_Values, sizeof(Standard_AC_Luminance_Values), fp); //we'll use the standard Huffman tables

  //SOS
  _write_word_(0xFFDA, fp);    //marker = 0xFFDA
  _write_word_(8, fp);      //length = 12
  _write_byte_(1, fp);      //nrofcomponents, Should be 3: truecolor JPG

  _write_byte_(1, fp);      //Idy=1
  _write_byte_(0, fp);      //HTY  bits 0..3: AC table (0..3)
                  //    bits 4..7: DC table (0..3)
  _write_byte_(0, fp);      //Ss not interesting, they should be 0,63,0
  _write_byte_(0x3F, fp);      //Se
  _write_byte_(0, fp);      //Bf
}
