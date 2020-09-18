# design

## Introdoce

- this project is designed to convert image to another type
- support imagetype
  - PNM:Portable Image Format,but currently support P5(PGM binary),P6(PPM binary),(1~16 bits)
  - RAW:currently only support default Format,(8/10/12/14/16 bits)
  - output_file:will support it,(8/10/12/14/16 bits)
  - JPEG: will support it (8 bits)
- All supported image type can be load from local file and convert to another supported image type,except that raw image can not be load from other image type
- this project consists of more basic project as `portableImage`,`rawImage`,`outputFile`,`JPEG`, all project will be coded with c/c++

## Struct
- Class  
  - image will be saved in `class ImageBuffer`,which only hold RGB data or gray data(single channel data).For other types of data will be converted from or converted to this two types. Although some functions will cost more time.

- ImageConverter Constructor
   - load local file and initialize parameters
   - correct parameters should be provided,otherwise Error will be thrown and program exit directly
   - it is not supported to change data in class once ImageBuffer has been set

- saveToFile
  - it is supported to convert ImageBuffer to different type of image as show in supprted imagetype list
