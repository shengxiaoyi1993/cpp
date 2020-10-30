#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "../lib/img_proc.h"

//----------------------------------------------------------------------------------------------------
void usage(char *command)
{
  printf("%s:\n", command);
  printf("  -I <SRC_FILE>     Src file, e.g. /temp/in_file.txt\n");
  printf("  -O <DST_FILE>     Src file, e.g. /temp/out_file.txt\n");
  printf("  -w <IMG_WIDTH>    Image width\n");
  printf("  -h <IMG_HEIGHT>   Image height\n");
  printf("  -b <PIXEL_BITS>   Pixel bits, only 8 bits, 12 bits or 16 bits supported\n");
  printf("  -?                Help\n");
}

void test_RAW();
void test_JPEG();
int main(int argc, char* argv[])
{
  int c;
  char *inFile, *outFile;
  unsigned int img_width = 0, img_height = 0, pixel_bits = 0;

  //  while((c = getopt(argc, argv, "I:O:w:h:b:?")) != -1) {
  //    switch(c) {
  //      case 'I':
  //        inFile = optarg;
  //        printf("%s: Input File = %s\n", argv[0], inFile);
  //        break;
  //      case 'O':
  //        outFile = optarg;
  //        printf("%s: Output File = %s\n", argv[0], outFile);
  //        break;
  //      case 'w':
  //        img_width = atoi(optarg);
  //        printf("%s: Image Width = %d\n", argv[0], img_width);
  //        break;
  //      case 'h':
  //        img_height = atoi(optarg);
  //        printf("%s: Image Height = %d\n", argv[0], img_height);
  //        break;
  //      case 'b':
  //        pixel_bits = atoi(optarg);
  //        printf("%s: Pixel Bits = %d\n", argv[0], pixel_bits);
  //        break;
  //      case '?':
  //        usage(argv[0]);
  //        return 0;
  //      default :
  //        printf("%s: Invalid Option: %c\n", argv[0], (char)c);
  //        usage(argv[0]);
  //        return -1;
  //    }
  //  }

  //  // declare image class
  //  imgProc pnm_proc;

  //  if (!pnm_proc.readFromPNM(inFile)) {
  //    return 1;
  //    printf("Reading PNM file fail!\n");
  //  }

  //  pnm_proc.writeToPPM(outFile, 8);

   test_RAW();
   test_JPEG();
  return 0;
}



void test_RAW(){
  char* inFile="../../resources/image_raw/imagebuffer.raw";
  char* outFile="imagebuffer_fromraw.ppm";
  std::cout<<"inFile:"<<inFile<<std::endl;

  try {
    // declare image class
    imgProc pnm_proc;

    if (!pnm_proc.readFromRAW(inFile,3,8,8,4096,4096)) {
      return ;
      printf("Reading RAW file fail!\n");
    }

    pnm_proc.writeToPPM(outFile, 8);

  } catch (std::string msg) {
    std::cout<<"msg:"<<msg<<std::endl;
  }
}


void test_JPEG(){


  char* inFile="../../resources/image_jpeg/jpg_rgb.jpeg";
  char* outFile="ppm_rgb_fromjpg.ppm";
  char  *outFile1="jpg_color_fromjpg.jpg";
  char*  outFile2="jpg_mono_fromjpg.jpg";

  std::cout<<"inFile:"<<inFile<<std::endl;

  try {
    // declare image class
    imgProc pnm_proc;

    if (!pnm_proc.readFromJPEG(inFile)) {
      return ;
      printf("Reading JPEG file fail!\n");
    }

    pnm_proc.writeToPPM(outFile, 8);
    pnm_proc.writeToJPEG_color(outFile1);
    pnm_proc.writeToJPEG_mono(outFile2);


  } catch (std::string msg) {
    std::cout<<"msg:"<<msg<<std::endl;
  }


}

