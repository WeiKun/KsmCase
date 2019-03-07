// File Name: test_mem.c
// Author: weikun
// Created Time: Thu 07 Mar 2019 12:26:56 AM CST

#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/mman.h>
#include <errno.h>

#define SIZE 4096 * 1024 * 25

int main()
{
    void *mem = NULL;
    posix_memalign(&mem, 4096, SIZE);
    memset((char *)mem, 0xCC, SIZE);
    int ret = madvise(mem, SIZE, MADV_MERGEABLE);
    //printf("ret=%d errno=%d %p\n", ret, errno, mem);
    sleep(1000);
    return 0 ;
}
