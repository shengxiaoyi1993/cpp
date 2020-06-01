#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define	TEXT_SZ	2048

struct	shared_use_st{
	int	written_by_you;
	char	some_text[TEXT_SZ];
};
