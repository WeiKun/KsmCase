# KSM使用示例
首先判断内核是否开启了KSM配置，去检查下config，如果里面的CONFIG_KSM=y那就是已经配置了
```shell
$ cat /boot/config-$(uname -r)|grep KSM
CONFIG_KSM=y
```
如果没有配置则需要重新编译内核。

然后去查看已经启用ksm服务没，/sys/kernel/mm/ksm/run文件内容如果是1，那就已经启用了。
```shell
$ cat /sys/kernel/mm/ksm/run
1
```
如果不为1，那使用"echo "1">/sys/kernel/mm/ksm/run"即可（需要root用户，sudo一般不行，除非先改权限）

再将useksm.c编译成可执行文件并重复运行即可
```shell
$ gcc useksm.c 
$ ./a.out &
[4] 31298
$ ./a.out &
[5] 31299
$ ./a.out &
[6] 31300
$ ./a.out &
[7] 31301
```
之后马上打开top，可以看到ksmd进程会开始占用CPU，used的内存也会逐渐降低并且free出内存。
测试代码中的25K页的数据是完全相同的，因此每一个进程的这些页都会使用同一页实际内存。

```c
#define SIZE 4096 * 1024 * 25

int main()
{
    void *mem = NULL;
    posix_memalign(&mem, 4096, SIZE);
    memset((char *)mem, 0xCC, SIZE);
    int ret = madvise(mem, SIZE, MADV_MERGEABLE);
    sleep(1000);
    return 0 ;
}
```


