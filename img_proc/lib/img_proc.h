#ifndef __IMG_PROC_HEADER__
#define __IMG_PROC_HEADER__

class imgProc
{
  public:
    /** clean all buffer **/
    void clean(void);

    /** read from pnm file **/
    /** based on pnm file, can get _width, _height, pixel_bits **/
    /** then get r, g, b for ppm, y for pgm **/
    bool readFromPNM(const char* fileName); 
  
    /** write to ppm file **/
    bool writeToPPM(const char* fileName, int pixel_bits);

    bool readFromRAW(const char* fileName,
                     unsigned int v_channels,
                     unsigned v_total_bits,
                     unsigned int v_valid_bits,
                     unsigned int v_width,
                     unsigned int v_height);

    bool readFromJPEG(const char* fileName);

    bool writeToJPEG_color(const char* fileName);

    bool writeToJPEG_mono(const char* fileName);


  
    // /** write to pgm file **/
    // bool writeToPGM(const char* fileName, int pixel_bits); 
  
  private:
    /** two member indicate width and height **/
    int  _width;
    int  _height;
    /** all data buffer 16 bits **/
    /** including raw, r, g, b, y, u, v **/
    unsigned short* _praw;
    unsigned short* _pr;
    unsigned short* _pg;
    unsigned short* _pb;
    unsigned short* _py;
    unsigned short* _pu;
    unsigned short* _pv;

    //convert rgb data to other type of data
    void rgbToAllData();



    /** **/
    /** **/
  public:
    imgProc();
    ~imgProc();

};


#endif
