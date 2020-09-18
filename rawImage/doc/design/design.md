# design
## 1 function
- a class to save data of raw image
  - RGGB（a），BGGR（b），GBRG（c），GRBG（d）
- support the convertion from raw to rgb

## 2 design
- import from file or memory

```cpp

class RAW{

  RAW();
  ~RAW();

public:
  enum RAWType {
    RAWType_RGGB=0,
    RAWType_BGGR,
    RAWType_GBRG,
    RAWType_GRBG
    };

  enum ConvertType{
     // Adjacent_Interpolation=0,
     // Boundary_Gradient_Interpolation,
     // Hamilton_Interpolation
     ConvertType_A=0,
     ConvertType_B,
     ConvertType_H
  }ConvertType;

  private:
    RAWType _type;
    unsigned int _valid_bits;
    unsigned int _height;
    unsigned int _width;
    unsigned short* _pdata;

public:
    //load from file
    int loadFromFile(
      const string &v_file,
      RAWType v_type,
      unsigned int v_valid_bits,
      unsigned int v_height,
      unsigned int v_width);

    //save to file
    int saveToFile(const string &v_file,RAWType v_type) const;
    unsigned short * getRGBData();


}RAW;
```


## 3 process
- read file and get raw data
- raw data saved in class
- use function to get data pointer

## 4 faq

- what type of data should save in class
  - src data
  - rgb data
