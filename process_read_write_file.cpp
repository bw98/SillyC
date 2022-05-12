#include <iostream>
#include <string>
#include <sys/file.h>

/*
 * (待实现) 多进程不同 programs 读写文件, 目前参考的是 http://www.tkxiong.com/archives/2165
 */

bool IsFile(const std::string &filePath) {
    // 判断一个路径是文件
    struct stat st;
    if (0 == stat(filePath.c_str(), &st)) {
        if (st.st_mode & S_IFDIR) {
            return false; // 目录
        }
        else if (st.st_mode & S_IFREG) {
            return true; // 文件
        }
    }

    return false;
}
 
bool FastReadFile(const std::string &filePath, std::string &fileData, bool lock) {
    // buf的大小推荐4k或者1k都行, 一次性全读虽然快, 但是浪费内存
    static constexpr long bufSize = 4096;
 
    // 判断给定的路径是一个文件
    if (!IsFile(filePath)) {
        return false;
    }
 
    // 采用C方式读取文件信息, 比CPP的readline方式快N倍.
    FILE *pFile;
    if ((pFile = fopen(filePath.c_str(), "r")) == NULL) {
        return false;
    }
 
    // 共享锁/不阻塞
    if (lock && flock(fileno(pFile), LOCK_SH | LOCK_NB) != 0) {
        fclose(pFile);
        return false;
    }
 
    // 计算文件大小
    fseek(pFile, 0, SEEK_SET);
    long begin = ftell(pFile);
    fseek(pFile, 0, SEEK_END);
    long end = ftell(pFile);
    long fileSize = end - begin;
    fseek(pFile, 0, SEEK_SET); //重新指向文件头
 
    // 预分配内存空间
    fileData.reserve(fileSize + 1);
 
    // 读取文件内容
    char readBuf[bufSize + 1];
    long readSize = 0;
    while (readSize < fileSize) {
        long minRead = std::min(fileSize - readSize, bufSize);
        long len = fread(readBuf, 1, minRead, pFile);
        readSize += len;
        fileData.append(readBuf, len);
    }
 
    // 解锁
    if (lock && flock(fileno(pFile), LOCK_UN) != 0) {
        fclose(pFile);
        return false;
    }
 
    fclose(pFile);
    return true;
}
 
bool WriteFile(const std::string &filePath, const std::string &fileData, bool lock) {
    FILE *pFile;
    if ((pFile = fopen(filePath.c_str(), "w")) == NULL)
    {
        return false;
    }
 
    // 互斥锁/不阻塞
    if (lock && flock(fileno(pFile), LOCK_EX | LOCK_NB) != 0)
    {
        fclose(pFile);
        return false;
    }
 
    fwrite(fileData.c_str(), 1, fileData.length(), pFile);
 
    // 解锁
    if (lock && flock(fileno(pFile), LOCK_UN) != 0)
    {
        fclose(pFile);
        return false;
    }
 
    fclose(pFile);
    return true;
}

