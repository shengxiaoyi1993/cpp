#ifndef MAX_H
#define MAX_H

template <typename T>
inline T const & max(T const &v_0,T const &v_1 ){
  return v_0>v_1?v_0:v_1;
}

template <typename T>
inline T* const & max(T* const &v_0,T* const &v_1 ){
  return *v_0>*v_1?v_0:v_1;
}




#endif
