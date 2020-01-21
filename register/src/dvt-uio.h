
#include <stdint.h>
#include <stddef.h>

class UIO {
private:
  int _fd;

public:
  explicit UIO(const char *fn);
  ~UIO();
  void unmask_interrupt();
  void wait_interrupt(int timeout_ms);
  friend class UIO_mmap;
};

class UIO_mmap {
private:
  size_t _size;
  void *_ptr;

public:
  UIO_mmap(const UIO &u, int index, size_t size);
  ~UIO_mmap();
  // `const` here make sure all data(including private and public, protect) can't be modified
  size_t size() const { return _size; }
  void *get_ptr() const { return _ptr; }
  uint32_t read_word(int offset) const { return *((unsigned *)(_ptr+offset)); }
  void write_word(int offset,unsigned wr_word) const { *((unsigned *) (_ptr+offset)) = wr_word; }

};
