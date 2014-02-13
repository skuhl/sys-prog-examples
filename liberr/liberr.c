// Scott Kuhl
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
#include <fcntl.h>
#include <limits.h>

// we may want to change this depending on if the user sets a
// LIBERROR_INFO environment variable (or similar) so that liberr
// doesn't have to be recompiled.
static int liberr_printInfo = 1;

/*
  NOTES:

  Intercepting malloc(), calloc(), realloc(), free() seems to cause
  some programs to segfault. One solution (also see comment) is on
  Stack Overflow: http://stackoverflow.com/a/10008252/474549 We don't
  attempt to intercept them at this point in time.

  If a function is always successful, or doesn't provide a reliably
  way to check if an error occurred, we do not intercept them.

  Functions that begin with liberr_ are intended to be used within
  liberr. For example liberr_fprintf() allows us to write messages to
  the terminal without our own call to fprintf() getting intercepted
  by liberr.

  Some programs will print messages to the console using lower-level
  functions. You can determine this by using "readelf -a /usr/bin/cal
  | grep UND" or "objdump -d /usr/bin/cal"
  
  Contributions are welcome!
*/


static int liberr_snprintf(char *str, size_t size, const char *format, ...);
static int liberr_fprintf(FILE *stream, const char *format, ...);
	
static void liberr_dlcheck(const char *err)
{
	if (err!=NULL)
	{
		liberr_fprintf(stderr, "liberr: Dynamic linking error.");
		exit(1);
	}
}

#define RED  "\x1B[31m"
#define BOLD  "\x1B[1m"
#define NRM  "\x1B[0m"

void _init()
{
	liberr_fprintf(stderr, RED BOLD "Using liberr!\n" NRM);
}

void liberr_printError(const char *funcName, int usePerror, const char *extra)
{

	if(usePerror)
	{
		char str[1024];
		liberr_snprintf(str, 1024, RED BOLD "liberr error: %s()" NRM, funcName);
		perror(str);
	}
	else
		liberr_fprintf(stderr, RED BOLD "liberr error: %s()" NRM "\n", funcName);


	if(extra != NULL)
		liberr_fprintf(stderr, RED BOLD "liberr error: Note: %s()" NRM "\n", extra);

}



static int  (*_real_fork) (void) = NULL;
int fork(void)
{
	const char *name = "fork";
	if(_real_fork == NULL)
	 {
		 _real_fork=dlsym(RTLD_NEXT, name);
		 liberr_dlcheck(dlerror());
	 }

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s()\n", name);

	int r = _real_fork();

	if(r == -1)
		liberr_printError(name, 1, NULL);
	return r;
}

static int (*_real_close) (int fd)  = NULL;
int close(int fd)
{
	const char *name = "close";
	
	if(_real_close == NULL)
	{
		_real_close=dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%d)\n", name, fd);

	int r = _real_close(fd);

	if(r == -1)
		liberr_printError(name, 1, NULL);
	return r;
}




static ssize_t (*_real_write) (int fd, const void *buf, size_t count)= NULL;
ssize_t write(int fd, const void *buf, size_t count)
{
	const char *name = "write";
	
	if(_real_write == NULL)
	{
		_real_write = dlsym(RTLD_NEXT, "write");
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: write(%d, %p, %zd)\n", fd, buf, count);
	
	ssize_t r = _real_write(fd, buf, count);

	if(r == -1)
		liberr_printError(name, 1, NULL);

	return r;
}



static ssize_t (*_real_read) (int fd, const void *buf, size_t count)= NULL;
ssize_t read(int fd, const void *buf, size_t count)
{
	const char *name = "read";
	
	if(_real_read == NULL)
	{
		_real_read = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%d, %p, %zd)\n", name, fd, buf, count);
	
	ssize_t r = _real_read(fd, buf, count);

	if(r == -1)
		liberr_printError(name, 1, NULL);
	return r;
}

static int (*_real_pipe) (int pipefd[2])= NULL;
int pipe(int pipefd[2])
{
	const char *name = "pipe";
	
	if(_real_pipe == NULL)
	{
		_real_pipe = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%p)\n", name, pipefd);
	
	int r = _real_pipe(pipefd);

	if(r == -1)
		liberr_printError(name, 1, NULL);
	return r;
}

static int (*_real_pipe2) (int pipefd[2], int flags)= NULL;
int pipe2(int pipefd[2], int flags)
{
	const char *name = "pipe2";
	
	if(_real_pipe == NULL)
	{
		_real_pipe2 = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%p, %d)\n", name, pipefd, flags);
	
	int r = _real_pipe2(pipefd, flags);

	if(r == -1)
		liberr_printError(name, 1, NULL);
	return r;
}


static int (*_real_dup) (int oldfd)= NULL;
int dup(int oldfd)
{
	const char *name = "dup";
	if(_real_dup == NULL)
	{
		_real_dup = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%d)\n", name, oldfd);
	
	int r = _real_dup(oldfd);

	if(r == -1)
		liberr_printError(name, 1, NULL);
	return r;
}


static int (*_real_dup2) (int oldfd, int newfd)= NULL;
int dup2(int oldfd, int newfd)
{
	const char *name = "dup2";
	if(_real_dup2 == NULL)
	{
		_real_dup2 = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%d, %d)\n", name, oldfd, newfd);
	
	int r = _real_dup2(oldfd, newfd);

	if(r == -1)
		liberr_printError(name, 1, NULL);
	return r;
}


static int (*_real_dup3) (int oldfd, int newfd, int flags)= NULL;
int dup3(int oldfd, int newfd, int flags)
{
	const char *name = "dup3";
	if(_real_dup3 == NULL)
	{
		_real_dup3 = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%d, %d, %d)\n", name, oldfd, newfd, flags);
	
	int r = _real_dup3(oldfd, newfd, flags);

	if(r == -1)
		liberr_printError(name, 1, NULL);
	return r;
}


static int (*_real_fsync) (int fd)= NULL;
int fsync(int fd)
{
	const char *name = "fsync";
	if(_real_fsync == NULL)
	{
		_real_fsync = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%d)\n", name, fd);
	
	int r = _real_fsync(fd);

	if(r == -1)
		liberr_printError(name, 0, "sleep() didn't sleep full amount of time");
	return r;
}

static int (*_real_fdatasync) (int fd)= NULL;
int fdatasync(int fd)
{
	const char *name = "fsync";
	if(_real_fdatasync == NULL)
	{
		_real_fdatasync = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%d)\n", name, fd);
	
	int r = _real_fdatasync(fd);

	if(r == -1)
		liberr_printError(name, 0, "sleep() didn't sleep full amount of time");
	return r;
}



static int (*_real_sleep) (unsigned int seconds)= NULL;
int sleep(unsigned int seconds)
{
	const char *name = "sleep";
	if(_real_sleep == NULL)
	{
		_real_sleep = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%u)\n", name, seconds);
	
	unsigned int r = _real_sleep(seconds);

	if(seconds > 0 && r < seconds)
		liberr_printError(name, 0, "sleep() didn't sleep full amount of time");
	return r;
}

static int (*_real_nanosleep) (const struct timespec *req, struct timespec *rem)= NULL;
int nanosleep(const struct timespec *req, struct timespec *rem)
{
	const char *name = "nanosleep";
	if(_real_nanosleep == NULL)
	{
		_real_nanosleep = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%p, %p)\n", name, req, rem);

	int r = _real_nanosleep(req, rem);

	if(r == -1)
		liberr_printError(name, 1, NULL);
	return r;
}

static off_t (*_real_lseek) (int fd, off_t offset, int whence)= NULL;
off_t lseek(int fd, off_t offset, int whence)
{
	const char *name = "lseek";
	if(_real_lseek == NULL)
	{
		_real_lseek = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%d, %zu, %d)\n", name, fd, offset, whence);

	int r = _real_lseek(fd, offset, whence);

	if(r == -1)
		liberr_printError(name, 1, NULL);
	return r;
}

static off_t (*_real_fseek) (FILE *stream, long offset, int whence)= NULL;
int fseek(FILE *fd, long offset, int whence)
{
	const char *name = "lseek";
	if(_real_fseek == NULL)
	{
		_real_fseek = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%p, %ld, %d)\n", name, fd, offset, whence);

	int r = _real_fseek(fd, offset, whence);

	if(r == -1)
		liberr_printError(name, 1, NULL);
	return r;
}


static int (*_real_stat) (const char *path, struct stat *buf)= NULL;
int stat(const char *path, struct stat *buf)
{
	const char *name = "stat";
	if(_real_stat == NULL)
	{
		_real_stat = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%s, %p)\n", name, path, buf);

	int r = _real_stat(path, buf);

	if(r == -1)
		liberr_printError(name, 1, NULL);
	return r;
}


// used internally to prevent infinite recursion
static int (*_real_vsnprintf) (char *str, size_t size, const char *format, va_list ap)= NULL;
int vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	const char *name = "vsnprintf";

	if(_real_vsnprintf == NULL)
	{
		_real_vsnprintf = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}
	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%p, %zu, %s, %p)\n", name, str, size, format, ap);
	
	int r = _real_vsnprintf(str, size, format, ap);

	if((size_t)r >= size)
		liberr_printError(name, 0, NULL);
	return r;
}


// uses vsnprintf to implement this function
static int liberr_snprintf(char *str, size_t size, const char *format, ...)
{
	if(_real_vsnprintf == NULL)
	{
		_real_vsnprintf = dlsym(RTLD_NEXT, "vsnprintf");
		liberr_dlcheck(dlerror());
	}

	va_list args;
	va_start(args, format);
	int r = _real_vsnprintf(str, size, format, args);

	return r;
}

// we use vsnprintf to implement this function.
int snprintf(char *str, size_t size, const char *format, ...)
{
	const char *name = "snprintf";

	if(_real_vsnprintf == NULL)
	{
		_real_vsnprintf = dlsym(RTLD_NEXT, "vsnprintf");
		liberr_dlcheck(dlerror());
	}
	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%p, %zu, %s, ...)\n", name, str, size, format);
	
	va_list args;
	va_start(args, format);
	int r = _real_vsnprintf(str, size, format, args);

	if((size_t)r >= size)
		liberr_printError(name, 0, NULL);
	return r;
}

static int (*_real_vprintf) (const char *format, va_list ap)= NULL;
int vprintf(const char *format, va_list ap)
{
	const char *name = "vprintf";

	if(_real_vprintf == NULL)
	{
		_real_vprintf = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%s, %p)\n", name, format, ap);
		
	int r = _real_vprintf(format, ap);

	if(r == -1)
		liberr_printError(name, 0, NULL);
	return r;
}

static int (*_real_fputs) (const char *s, FILE *stream)= NULL;
int fputs(const char *s, FILE *stream)
{
	const char *name = "fputs";

	if(_real_fputs == NULL)
	{
		_real_fputs = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%s, %p)\n", name, s, stream);
		
	int r = _real_fputs(s, stream);

	if(r == EOF)
		liberr_printError(name, 0, NULL);
	return r;
}

static int (*_real_puts) (const char *s)= NULL;
int puts(const char *s)
{
	const char *name = "puts";

	if(_real_puts == NULL)
	{
		_real_puts = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%s)\n", name, s);
		
	int r = _real_puts(s);

	if(r == EOF)
		liberr_printError(name, 0, NULL);
	return r;
}



// uses vprintf
int printf(const char *format, ...)
{
	const char *name = "printf";
	if(_real_vprintf == NULL)
	{
		_real_vprintf = dlsym(RTLD_NEXT, "vprintf");
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%s, ...)\n\n", name, format);

	va_list args;
	va_start(args, format);
	int r = _real_vprintf(format, args);

	if(r == -1)
		liberr_printError(name, 0, NULL);
	return r;
}

// uses vwprintf
static int (*_real_vwprintf) (const wchar_t *format, va_list ap)= NULL;
int wprintf(const wchar_t *format, ...)
{
	const char *name = "wprintf";
	if(_real_vwprintf == NULL)
	{
		_real_vwprintf = dlsym(RTLD_NEXT, "vwprintf");
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%s, ...)\n\n", name, format);

	va_list args;
	va_start(args, format);
	int r = _real_vwprintf(format, args);

	if(r == -1)
		liberr_printError(name, 0, NULL);
	return r;
}


static int (*_real_vfprintf) (FILE *stream, const char *format, va_list ap)= NULL;
int vfprintf(FILE *stream, const char *format, va_list ap)
{
	const char *name = "vfprintf";

	if(_real_vfprintf == NULL)
	{
		_real_vfprintf = dlsym(RTLD_NEXT, name);
		liberr_dlcheck(dlerror());
	}

	// don't call ourselves recursively!
	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%p, %s, %p)\n", name, stream, format, ap);
		
	int r = _real_vfprintf(stream, format, ap);

	if(r == -1)
		liberr_printError(name, 0, NULL);
	return r;
}


// uses vfprintf
int fprintf(FILE *stream, const char *format, ...)
{
	const char *name = "fprintf";

	if(_real_vfprintf == NULL)
	{
		_real_vfprintf = dlsym(RTLD_NEXT, "vfprintf");
		liberr_dlcheck(dlerror());
	}

	if(liberr_printInfo)
		liberr_fprintf(stderr, "liberr call: %s(%p, %s, ...)\n", name, stream, format);
		
	va_list args;
	va_start(args, format);
	int r = _real_vfprintf(stream, format, args);

	if(r == -1)
		liberr_printError(name, 0, NULL);
	return r;
}

// uses vfprintf
static int liberr_fprintf(FILE *stream, const char *format, ...)
{
	if(_real_vfprintf == NULL)
	{
		_real_vfprintf = dlsym(RTLD_NEXT, "vfprintf");
		liberr_dlcheck(dlerror());
	}

	va_list args;
	va_start(args, format);
	return _real_vfprintf(stream, format, args);
}


