#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;

int main() {
    const int start_fd = 100;
    const int file_cnt = 100;
    vector<int> fds;
    fds.reserve(file_cnt);
    for (size_t i = start_fd; i < start_fd + file_cnt; ++i) {
        string filename = std::to_string(i);
        printf("opening file %s\n", filename.c_str());
        int fd = open(filename.c_str(), O_RDONLY | O_DIRECT, 0755);
        // int fd = open(filename.c_str(), O_RDONLY, 0755);
        fds.push_back(fd);
    }

    for (int fd : fds) {
        cout << fd << endl;
    }

    // 执行一千次读 IO
    const int len = 1 * 1024;
    for (size_t i = 0; i < 1000; ++i) {
        int index = i % file_cnt;
        lseek(fds[index], 512, SEEK_SET);  // 转移偏移量
        char* buf;
        size_t buf_size = len * 2;
        posix_memalign((void**)&buf, getpagesize(), buf_size);
        // buf = (char*)malloc(sizeof(char) * buf_size);
        printf("size of mem of buf: %d\n", malloc_usable_size(buf));
        int ret = read(fds[index], buf, len);
        printf("fd: %d, real read: %d, expected read: %d\n", fds[index], ret, len);
        if(ret != len) {
            free(buf);
            std::cerr << "partially read!\n";
            continue;
        }
        free(buf);
        sync();  // 如果 disable sync, 那么文件数据可能还存在于 page cache, 以后的读取可能会更快
    }

    for(int fd : fds) {
        close(fd);
    }

    return 0;
}

