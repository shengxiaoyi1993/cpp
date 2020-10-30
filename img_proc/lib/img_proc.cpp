#include <stdio.h>
#include <memory.h>
#include <math.h>

#include "img_proc.h"
#include "ImageConverter.hpp"
#include "jpge.h"


//----------------------------------------------------------------------------------------------------
imgProc::imgProc()
  : _width(0), _height(0), _praw(0), _pr(0), _pg(0), _pb(0), _py(0), _pu(0), _pv(0)
{
  // init
}

//----------------------------------------------------------------------------------------------------
imgProc::~imgProc()
{
  clean();
}

//----------------------------------------------------------------------------------------------------
void imgProc::clean(void)
{
  _width = 0;
  _height = 0;

  // clean raw buffer
  if(_praw) delete[] _praw;
  _praw = 0;
  // clean r buffer
  if(_pr) delete[] _pr;
  _pr = 0;
  // clean g buffer
  if(_pg) delete[] _pg;
  _pg = 0;
  // clean b buffer
  if(_pb) delete[] _pb;
  _pb = 0;
  // clean y buffer
  if(_py) delete[] _py;
  _py = 0;
  // clean u buffer
  if(_pu) delete[] _pu;
  _pu = 0;
  // clean v buffer
  if(_pv) delete[] _pv;
  _pv = 0;

}

//----------------------------------------------------------------------------------------------------
bool imgProc::readFromPNM(const char* fileName)
{ // --{{{
  char line[1024];
  char *p;
  int cols, rows, maxval;
  bool successed = false;
  int pnm_mode = 0;

  // open the file
  FILE *fp = fopen(fileName, "rb");
  if(fp==0) return false;

  // read header
  // all break will jump out loop;
  do {
    // if read comment line, then read again
    do {
      p = fgets(line, sizeof(line), fp);
    } while (p != NULL && *p == '#');
    // if empty, then jump out
    if (p == NULL) break;

    // check if PPM(P5) or PGM(P6)
    if (strncmp(line, "P5", 2) == 0) {
      pnm_mode = 5;
    } else if (strncmp(line, "P6", 2) == 0) {
      pnm_mode = 6;
    } else {
      printf("Not PPM or PGM file! \n");
      break;
    }

    // read parameter
    if (strlen(line) > 3) {
      // if all in one line
      // <mode> <cols> <rows> <maxval>
      if (sscanf(line+2, "%d %d %d", &cols, &rows, &maxval) != 3)
        break;
    } else {
      // if parameters in different lines
      // if read comment line, then read again
      do {
        p = fgets(line, sizeof(line), fp);
      } while (p != NULL && *p == '#');
      // if empty, then jump out
      if (p == NULL) break;

      // <cols> <rows>
      if (sscanf(line, "%d %d", &cols, &rows) != 2)
        break;
      
      // if read comment line, then read again
      do {
        p = fgets(line, sizeof(line), fp);
      } while (p != NULL && *p == '#');
      // if empty, then jump out
      if (p == NULL) break;

      // <cols> <rows>
      if (sscanf(line, "%d", &maxval) != 1)
        break;
      
    }

    printf("PNM read header success, mode = %d, cols = %d, rows = %d, maxval = %d\n", pnm_mode, cols, rows, maxval);

    if ((maxval != 255) && (maxval != 65535)) {
      // not 8 bits or 16 bits file, break
      printf("PNM file not 8bits or 16bits, not supported!\n");
      break;
    }

    int bufsize = cols*rows;
    if (pnm_mode==5) {
      // PGM mode
      unsigned short *buffer = new unsigned short[bufsize];
      unsigned short pixel;

      for (int j=0; j<rows; j++) {
        for (int i=0; i<cols; i++) {
          if (maxval==255) {
            if (fread(&pixel, 1, 1, fp) == 0) {
              printf("Not enough data in PNM file!\n");
              delete[] buffer;
              buffer = 0;
              break;
            }
            buffer[j*cols+i] = pixel*256;
          } else {
            if (fread(&pixel, 2, 1, fp) == 0) {
              printf("Not enough data in PNM file!\n");
              delete[] buffer;
              buffer = 0;
              break;
            }
            buffer[j*cols+i] = pixel;
          }
        }
      }
      // assign to _pv if PGM file
      _pv = buffer;

    } else if (pnm_mode==6) {
      // PPM mode
      unsigned short *buffer_r = new unsigned short[bufsize];
      unsigned short *buffer_g = new unsigned short[bufsize];
      unsigned short *buffer_b = new unsigned short[bufsize];
      
      for (int j=0; j<rows; j++) {
        for (int i=0; i<cols; i++) {
          if (maxval==255) {
            unsigned char pixel[3];
            if (fread(pixel, 1, 3, fp) == 0) {
              printf("Not enough data in PNM file!\n");
              delete[] buffer_r;
              buffer_r = 0;
              delete[] buffer_g;
              buffer_g = 0;
              delete[] buffer_b;
              buffer_b = 0;
              break;
            }
            buffer_r[j*cols+i] = pixel[0]*256;
            buffer_g[j*cols+i] = pixel[1]*256;
            buffer_b[j*cols+i] = pixel[2]*256;
          } else {
            unsigned short pixel[3];
            if (fread(pixel, 2, 3, fp) == 0) {
              printf("Not enough data in PNM file!\n");
              delete[] buffer_r;
              buffer_r = 0;
              delete[] buffer_g;
              buffer_g = 0;
              delete[] buffer_b;
              buffer_b = 0;
              break;
            }
            buffer_r[j*cols+i] = pixel[0];
            buffer_g[j*cols+i] = pixel[1];
            buffer_b[j*cols+i] = pixel[2];
          }
        }
      }
      // assign to _pr, _pg, _pb if PPM file
      _pr = buffer_r;
      _pg = buffer_g;
      _pb = buffer_b;

    }

    _width = cols;
    _height = rows;
    successed = true;

  } while (false);

  fclose(fp);
  fp = 0;
  printf("Read PNM file successed!\n");
  return successed;

} // --}}}

//----------------------------------------------------------------------------------------------------
bool imgProc::writeToPPM(const char* fileName, int pixel_bits)
{ // --{{{
  int maxval;

  FILE *fp = fopen(fileName, "wb");

  if (pixel_bits==8) {
    maxval = 255;
  } else if (pixel_bits==16) {
    maxval = 65535;
  } else {
    printf("Pixel size = %d not supported!\n", pixel_bits);
    return false;
  }

  // write ppm header
  fprintf(fp, "P6\n%d %d\n%d\n", _width, _height, maxval);

  // write data
  for (int j=0; j<_height; j++) {
    for (int i=0; i<_width; i++) {
      if (pixel_bits==8) {
        unsigned char pixel;
        pixel = _pr[j*_width+i]/256;
        fwrite(&pixel, 1, 1, fp);
        pixel = _pg[j*_width+i]/256;
        fwrite(&pixel, 1, 1, fp);
        pixel = _pb[j*_width+i]/256;
        fwrite(&pixel, 1, 1, fp);
      } else {
        unsigned char pixel[2];
        pixel[0] = _pr[j*_width+i]>>8;
        pixel[1] = (unsigned char)_pr[j*_width+i];
        fwrite(&pixel, 1, 2, fp);
        pixel[0] = _pg[j*_width+i]>>8;
        pixel[1] = (unsigned char)_pg[j*_width+i];
        fwrite(&pixel, 1, 2, fp);
        pixel[0] = _pb[j*_width+i]>>8;
        pixel[1] = (unsigned char)_pb[j*_width+i];
        fwrite(&pixel, 1, 2, fp);
      }
    }
  }

  fclose(fp);
  return true;

} // --}}}

//----------------------------------------------------------------------------------------------------
bool imgProc::readFromRAW(const char* fileName,
                 unsigned int v_channels,
                 unsigned v_total_bits,
                 unsigned int v_valid_bits,
                 unsigned int v_width,
                 unsigned int v_height){
  string file(fileName);
  ImageConverter   imageconverter(file,ImageType::ImageType_RAW,v_channels,
                                  v_total_bits,v_valid_bits,v_width,v_height);
  unsigned size=v_width*v_height;
  _width=v_width;
  _height=v_height;
  _pr=new  unsigned short[size];
  _pg=new  unsigned short[size];
  _pb=new  unsigned short[size];
  for(unsigned i=0;i<size;i++){
    _pr[i]=imageconverter._pimagebufer->_pdata[3*i+0];
    _pg[i]=imageconverter._pimagebufer->_pdata[3*i+1];
    _pb[i]=imageconverter._pimagebufer->_pdata[3*i+2];
  }
  return true;
}


//----------------------------------------------------------------------------------------------------
bool imgProc::readFromJPEG(const char* fileName){
  ImageConverter   imageconverter(string(fileName),ImageType::ImageType_JPEG);
  _width=imageconverter._pimagebufer->_width;
  _height=imageconverter._pimagebufer->_height;
  unsigned size=_width*_height;
  _pr=new  unsigned short[size];
  _pg=new  unsigned short[size];
  _pb=new  unsigned short[size];
  for(unsigned i=0;i<size;i++){
    _pr[i]=imageconverter._pimagebufer->_pdata[3*i+0];
    _pg[i]=imageconverter._pimagebufer->_pdata[3*i+1];
    _pb[i]=imageconverter._pimagebufer->_pdata[3*i+2];
  }

  return true;

}


//----------------------------------------------------------------------------------------------------
bool imgProc::writeToJPEG_color(const char* fileName){
  if(!(_pr != nullptr && _pg != nullptr && _pb != nullptr)){
    printf("Error:data pointer is null !");
  }
  unsigned size =_width*_height;
  unsigned char* pdata=new unsigned char[size*3];
  for(size_t i=0;i<size;i++){
    pdata[i*3+0]=_pr[i]>>8;
    pdata[i*3+1]=_pg[i]>>8;
    pdata[i*3+2]=_pb[i]>>8;
  }

  jpge::compress_image_to_jpeg_file(fileName, _width,_height,3,pdata);
  delete []pdata;
  pdata=nullptr;

  return 0;

}


//----------------------------------------------------------------------------------------------------
bool imgProc::writeToJPEG_mono(const char* fileName){
  if(!(_pr != nullptr && _pg != nullptr && _pb != nullptr)){
    printf("Error:data pointer is null !");
  }
  unsigned size =_width*_height;
  unsigned char* pdata=new unsigned char[size];
  for(size_t i=0;i<size;i++){
    pdata[i]=(_pr[i]>>8)*0.3+(_pg[i]>>8)*0.59+(_pb[i]>>8)*0.11;
  }

  jpge::compress_image_to_jpeg_file(fileName, _width,_height,1,pdata);
  delete []pdata;
  pdata=nullptr;

  return 0;
}


void imgProc::rgbToAllData(){

}




//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
