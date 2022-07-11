#pragma once

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <asm/errno.h>
#include <asm/poll.h>
#include <asm/posix_types.h>
#include <asm/siginfo.h>
#include <asm/signal.h>
#include <asm/stat.h>
#include <asm/statfs.h>
#include <linux/aio_abi.h>
#include <linux/eventpoll.h>
#include <linux/futex.h>
#include <linux/kernel.h>
#include <linux/msg.h>
#include <linux/perf_event.h>
#include <linux/sem.h>
#include <linux/times.h>
#include <linux/timex.h>
#include <linux/types.h>
#include <linux/utime.h>
#include <linux/utsname.h>
#include <linux/version.h>

#include "elf.h"
#include "libos_types_arch.h"
#include "linux_socket.h"
#include "pal.h"

typedef unsigned long int nfds_t;
typedef unsigned long int nlink_t;

typedef __kernel_uid_t     uid_t;
typedef __kernel_gid_t     gid_t;
typedef __kernel_pid_t     pid_t;
typedef __kernel_mode_t    mode_t;
typedef __kernel_off_t     off_t;
typedef __kernel_loff_t    loff_t;
typedef __kernel_time_t    time_t;
typedef __kernel_old_dev_t dev_t;
typedef __kernel_ino_t     ino_t;
typedef __kernel_clockid_t clockid_t;
typedef __kernel_fd_set    fd_set;

/* linux/time.h */
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 18, 0)
struct __kernel_timespec {
    __kernel_time_t tv_sec; /* seconds */
    long tv_nsec;           /* nanoseconds */
};
#endif

struct __kernel_timeval {
    __kernel_time_t tv_sec;       /* seconds */
    __kernel_suseconds_t tv_usec; /* microsecond */
};

struct __kernel_itimerval {
    struct __kernel_timeval it_interval; /* time interval */
    struct __kernel_timeval it_value;    /* current value */
};

struct __kernel_timezone {
    int tz_minuteswest; /* minutes west of Greenwich */
    int tz_dsttime;     /* type of dst correction */
};

/* /arch/x86/include/asm/posix_types_64.h */
typedef unsigned int __kernel_uid_t;

struct __kernel_sched_param {
    int __sched_priority;
};

struct __kernel_sigaction {
    __sighandler_t k_sa_handler;
    unsigned long sa_flags;
    void (*sa_restorer)(void);
    __sigset_t sa_mask;
};

/* linux/rlimit.h */
struct __kernel_rusage {
    struct __kernel_timeval ru_utime; /* user time used */
    struct __kernel_timeval ru_stime; /* system time used */
    long ru_maxrss;                   /* maximum resident set size */
    long ru_ixrss;                    /* integral shared memory size */
    long ru_idrss;                    /* integral unshared data size */
    long ru_isrss;                    /* integral unshared stack size */
    long ru_minflt;                   /* page reclaims */
    long ru_majflt;                   /* page faults */
    long ru_nswap;                    /* swaps */
    long ru_inblock;                  /* block input operations */
    long ru_oublock;                  /* block output operations */
    long ru_msgsnd;                   /* messages sent */
    long ru_msgrcv;                   /* messages received */
    long ru_nsignals;                 /* signals received */
    long ru_nvcsw;                    /* voluntary context switches */
    long ru_nivcsw;                   /* involuntary " */
};

struct __kernel_rlimit {
    unsigned long rlim_cur, rlim_max;
};

struct __kernel_rlimit64 {
    uint64_t rlim_cur, rlim_max;
};

struct getcpu_cache {
    unsigned long blob[128 / sizeof(long)];
};

#undef __CPU_SETSIZE
#undef __NCPUBITS

#define LINUX_DT_UNKNOWN 0
#define LINUX_DT_FIFO    1
#define LINUX_DT_CHR     2
#define LINUX_DT_DIR     4
#define LINUX_DT_BLK     6
#define LINUX_DT_REG     8
#define LINUX_DT_LNK     10
#define LINUX_DT_SOCK    12
#define LINUX_DT_WHT     14

struct linux_dirent64 {
    uint64_t d_ino;              /* Inode number */
    uint64_t d_off;              /* Offset to next linux_dirent */
    unsigned short int d_reclen; /* Length of this linux_dirent */
    unsigned char d_type;
    char d_name[]; /* File name (null-terminated) */
};

struct linux_dirent {
    unsigned long d_ino;         /* Inode number */
    unsigned long d_off;         /* Offset to next linux_dirent */
    unsigned short int d_reclen; /* Length of this linux_dirent */
    char d_name[];               /* File name (null-terminated) */
};

struct linux_dirent_tail {
    char pad;
    unsigned char d_type;
};

struct linux_file_handle {
    unsigned int handle_bytes;
    int handle_type;
    unsigned char f_handle[0];
};

typedef Elf64_auxv_t elf_auxv_t;

/* typedef for LibOS internal types */
typedef uint32_t IDTYPE;
#define IDTYPE_MAX UINT32_MAX
typedef uint64_t HASHTYPE;

#define FILE_OFF_MAX INT64_MAX
typedef int64_t file_off_t;

typedef int64_t REFTYPE;

struct libos_lock {
    PAL_HANDLE lock;
    IDTYPE owner;
};

/* maximum length of pipe/FIFO name (should be less than Linux sockaddr_un.sun_path = 108) */
#define PIPE_URI_SIZE 96

#ifndef EPOLLNVAL
/* This is not defined in the older kernels e.g. the default kernel on Ubuntu 18.04. */
#define EPOLLNVAL ((uint32_t)0x00000020)
#endif
