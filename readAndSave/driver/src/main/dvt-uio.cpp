#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdexcept>
#include <poll.h>
#include "dvt-uio.h"

UIO::UIO(const char *fn) {
  _fd = open(fn, O_RDWR);

  if (_fd < 0)
    throw std::runtime_error("failed to open UIO device");
}

UIO::~UIO() { close(_fd); }

void UIO::unmask_interrupt() {
  uint32_t unmask = 1;
  ssize_t rv = write(_fd, &unmask, sizeof(unmask));
  if (rv != (ssize_t)sizeof(unmask)) {
    perror("UIO::unmask_interrupt()");
  }
}

int UIO::wait_interrupt(int timeout_ms) {
  // wait for the interrupt
  struct pollfd pfd = {.fd = _fd, .events = POLLIN};
  int rv = poll(&pfd, 1, timeout_ms);
  // clear the interrupt
  if (rv >= 1) {
    read(_fd, &_irq_cnt, sizeof(_irq_cnt));
  } else if (rv == 0) {
    // this indicates a timeout, will be caught by device busy flag
  } else {
    perror("UIO::wait_interrupt()");
  }
  return rv;
}

// _size(size) assign `size` to _size
UIO_mmap::UIO_mmap(const UIO &u, int index, size_t size) : _size(size) {
  _ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, u._fd, index * getpagesize());
  if (_ptr == MAP_FAILED) {
    perror("UIO_mmap");
    std::runtime_error("UIO_mmap construction failed");
  }
}

UIO_mmap::~UIO_mmap() { munmap(_ptr, _size); }

uint32_t UIO_mmap::rreg32_f(uint32_t addr, uint32_t mask, uint32_t shift) const{
  uint32_t reg = rreg32(addr);
  return (reg & mask) >> shift;
}

void UIO_mmap::wreg32_f(uint32_t addr, uint32_t mask, uint32_t shift, uint32_t value) const{
  uint32_t reg = rreg32(addr);
  wreg32(addr, (reg & ~mask) | ((value << shift) & mask));
}
