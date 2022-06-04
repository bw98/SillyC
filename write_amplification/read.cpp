#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

int main() {
    vector<int> fds;
    fds.reserve(500);

    const int len = 1024;
    const int start_fd = 1000;
    const int file_cnt = 10;

    for (size_t i = start_fd; i < start_fd + file_cnt; ++i) {
        int fd = open(std::to_string(i).c_str(), O_RDONLY | O_DIRECT, 0755);
        std::cout << fd << std::endl;
        fds.push_back(fd);
    }

    // 执行一千次读 IO
    for (size_t i = 0; i < 1000; ++i) {
        int index = start_fd + i % 10;
        lseek(fds[index], 1024 * 1024 * 512, SEEK_SET);  // 转移偏移量
        char* buf;
        posix_memalign((void**)&buf, getpagesize(), 1025);
        std::cout << fds[index] << std::endl;
        size_t buf_size = len;
        int ret = read(fds[index], buf, buf_size);
        if(ret != buf_size) {
            free(buf);
            std::cerr << "Partially written！\n";
            continue;
        }
        free(buf);
        sync();  // 如果去掉sync, 因为这个文件数据现在还存在于 page cache, 所以可以预料到的读取数据会比较小, tps 也会比较小
    }
    

    for(int fd : fds) {
        close(fd);
    }

    return  0;
}

