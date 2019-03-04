asmlinkage int sys_mysyscall(char *srcFile, char *dstFile)
{
    int src = sys_open(srcFile, O_RDONLY, 0);
}