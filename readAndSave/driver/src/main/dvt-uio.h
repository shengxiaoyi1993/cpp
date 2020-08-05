#ifndef DVT_UIO_H
#define DVT_UIO_H
#include <stdint.h>
#include <stddef.h>

class UIO {
private:
  int _fd;
  uint32_t _irq_cnt;

public:
  explicit UIO(const char *fn);
  ~UIO();
  void unmask_interrupt();
  int wait_interrupt(int timeout_ms);
  friend class UIO_mmap;
  uint32_t get_irq_cnt() const { return _irq_cnt; }
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
  uint32_t rreg32(uint32_t addr) const { return *((unsigned *)(_ptr+addr)); }
  void wreg32(uint32_t addr, uint32_t value) const { *((unsigned *)(_ptr+addr)) = value; }
  uint32_t rreg32_f(uint32_t addr, uint32_t mask, uint32_t shift) const;
  void wreg32_f(uint32_t addr, uint32_t mask, uint32_t shift, uint32_t value) const;
};
#endif
