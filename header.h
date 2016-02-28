#ifndef HEADER_H
#define HEADER_H

#include <math.h>

#define NPROC    9
#define SSIZE 1024
#define AX 8
#define PA 13

/******* PROC status ********/
#define FREE     0
#define READY    1
#define RUNNING  2
#define STOPPED  3
#define SLEEP    4
#define ZOMBIE   5

typedef struct proc{
    struct proc *next;
    int    *ksp;               // at offset 2

    int    uss, usp;           // at offsets 4,6
    int    inkmode;            // at offset 8

    int    pid;                // add pid for identify the proc
    int    status;             // status = FREE|READY|RUNNING|SLEEP|ZOMBIE
    int    ppid;               // parent pid
    struct proc *parent;
    int    priority;
    int    event;
    int    exitCode;
    char   name[32];           // name string of PROC

    int    kstack[SSIZE];      // per proc stack area
}PROC;
extern int color;
extern int MTXSEG  = 0x1000;

/******Conner's Additions Below***********/
// additions from io.h from lab 2


typedef unsigned char  u8;
typedef unsigned int  u16;
typedef unsigned long  u32;

#define  GREEN  10         // color byte for putc()
#define  CYAN   11
#define  RED    12
#define  MAG    13
#define  YELLOW 14

struct partition {         // Partition table entry in MBR
       u8  drive;          // 0x80 - active
       u8  head;     // starting head
       u8  sector;      // starting sector
       u8  cylinder;       // starting cylinder
       u8  type;     // partition type
       u8  end_head;       // end head
       u8  end_sector;     // end sector
       u8  end_cylinder;   // end cylinder
       u32 start_sector;   // starting sector counting from 0
       u32 nr_sectors;     // nr of sectors in partition
};

struct dap{                // DAP for extended INT 13-42
       u8   len;           // dap length=0x10 (16 bytes)
       u8   zero;          // must be 0
       u16  nsector;       // number of sectors to read: 1 to 127
       u16  addr;          // memory address = (segment:addr)
       u16  segment;
       u32  s1;            // low  4 bytes of sector#
       u32  s2;            // high 4 bytes of sector#
};

struct dap dap, *dp;       // global dap struct

// io globals
int BASE = 10;
int *FP;
char *table = "0123456789ABCDEF";

#define  BOOTSEG 0x9000
#define MAX 256
#define NULL 0
char mbr[512];
char ans[64];
char buffer[1024];

/****** type.h additions *********/
PROC proc[NPROC], *running, *freeList, *readyQueue, *sleepList;
int procSize = sizeof(PROC);
int nproc = 0;

//int goUmode();
int body();
char *pname[]={"Sun", "Mercury", "Venus", "Earth",  "Mars", "Jupiter",
               "Saturn", "Uranus", "Neptune" };

/****** function headers *******/
//ts.s
int goUmode();

// t.c
int init();
int scheduler();
PROC *kfork();

// commands.c
do_tswitch();
do_kfork();
do_ps();
do_exit();
do_sleep();
do_wake();
do_wait();

// kernel.c
int ksleep(int event);
int kwakeup(int event);
int kexit(int exitvalue);
int kwait(int *status);

PROC *kfork(char *filename);
int kgetpid();
int kprintstatus();
int kchname(char name[32]);
int get_block(u16 blk, char *buf);

//inode.c
int getInodeNumberFromFile(char *filename);

//char **chopFirstStringElement(char *array[MAX]);
int parseInput(char *input, char **parsedinput, char *delimiter);


//ForkExec.c
int fork();
int exec();

int ufork();
int uexec();

//io.c
int rpu(u32 x);
int rpu16(u16 x);
int printu(u32 x);
int printd(int x);
int printo(u32 x);
int printx(u32 x);
void printf(char *fmt, ...);
int prints(char *s);
strcmp();
int gets(char s[64]);
int strtoint(char *str);
int isDigit(char c);
int power(int x, int y);

// queue
void showLists();

#endif
