#include <iostream>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

// int CNT = 0;
// // std::atomic<int> CNT(0);
// const int CNT_MAX = 100;
// std::mutex MTX;
// 
// void print_num_test(const int thd_id) {
//     while (CNT < CNT_MAX) {
//         std::scoped_lock lk(MTX);
//         if (CNT < CNT_MAX) {
//             ++CNT;
//             cout << "thd_id: " << thd_id << ", CNT: " << CNT << endl;
//         }
//     }
// }

// std::mutex MTX;
// int CNT_A = 100;
// int CNT_B = 100;
// int CNT_C = 100;
// 
// void print_letter_test(const int thd_id) {
//     while (CNT_A + CNT_B + CNT_C > 0) {
//         std::scoped_lock lk(MTX);
//         if (CNT_A + CNT_B + CNT_C > 0) {
//             if (CNT_A >= CNT_B && CNT_A >= CNT_C) {
//                 cout << "thd_id: " << thd_id << ", letter: A" << endl;
//                 --CNT_A;
//             } else if (CNT_B >= CNT_A && CNT_B >= CNT_C) {
//                 cout << "thd_id: " << thd_id << ", letter: B" << endl;
//                 --CNT_B;
//             } else if (CNT_C >= CNT_A && CNT_C >= CNT_B) {
//                 cout << "thd_id: " << thd_id << ", letter: C" << endl;
//                 --CNT_C;
//             }
//         }
//     }
// }

// std::mutex MTX;
// int CNT_LETTER = 1;
// int CNT_NUM = 1;
//  
// // OUTPUT: A1B2C3D4...X24Y25Z26
// void print_letter_num_test(const int thd_id) {
//     while (CNT_LETTER <= 26 || CNT_NUM <= 26) {
//         std::scoped_lock guard(MTX);
//         if (CNT_LETTER <= 26 || CNT_NUM <= 26) {
//             if (CNT_LETTER == CNT_NUM) {
//                 cout << "thd_id: " << thd_id << ", letter: " << (char)('A' + CNT_LETTER - 1) << endl;
//                 ++CNT_LETTER;
//             } else {
//                 cout << "thd_id: " << thd_id << ", num: " << CNT_NUM << endl;
//                 ++CNT_NUM;
//             }
//         }
//     }
// }


// OUTPUT still is: A1B2C3D4...X24Y25Z26
// but only use 2 thds, one only works for printing letter, another only works for printing number

std::mutex MTX;
std::condition_variable CV;
int CNT_LETTER = 1;
int CNT_NUM = 1;
bool PRINT_LETTER = true;

bool ready_print_letter() {
    return PRINT_LETTER;
}

bool ready_print_num() {
    return !PRINT_LETTER;
}

void print_letter(const int thd_id) {
    while (CNT_LETTER <= 26) {
        std::unique_lock<std::mutex> lock(MTX);
        CV.wait(lock, ready_print_letter);
        if (CNT_LETTER <= 26) {
            cout << "thd_id: " << thd_id << ", letter: " << (char)('A' + CNT_LETTER - 1) << endl;
            ++CNT_LETTER;
            PRINT_LETTER = false;
        }
        
        lock.unlock();
        CV.notify_one();
    }
}

void print_num(const int thd_id) {
    while (CNT_NUM <= 26) {
        std::unique_lock<std::mutex> lock(MTX);
        bool a = false;
        // CV.wait(lock, ready_print_num);
        CV.wait(lock, []() { return !PRINT_LETTER;});
        if (CNT_NUM <= 26) {
            cout << "thd_id: " << thd_id << ", num: " << CNT_NUM << endl;
            ++CNT_NUM;
            PRINT_LETTER = true;
        }
        
        lock.unlock();
        CV.notify_one();
    }
}

int main() {
    int thd_num = 3;
    std::vector<std::thread> threads(thd_num);
    clock_t start, end;

    //// print num test
    //for (int i = 0; i < thd_num; ++i) {
    //    threads[i] = std::thread(print_num_test, i);
    //}
    //for (int i = 0; i < thd_num; ++i) {
    //    threads[i].join();
    //}

    // // print letter test
    // for (int i = 0; i < thd_num; ++i) {
    //     threads[i] = std::thread(print_letter_test, i);
    // }
    // for (int i = 0; i < thd_num; ++i) {
    //     threads[i].join();
    // }

    // // print letter num test
    // for (int i = 0; i < thd_num; ++i) {
    //     threads[i] = std::thread(print_letter_num_test, i);
    // }
    // for (int i = 0; i < thd_num; ++i) {
    //     threads[i].join();
    // }

    // print letter num test2
    auto letter_thd = std::thread(print_letter, 0);
    auto num_thd = std::thread(print_num, 1);
    letter_thd.join();
    num_thd.join();

    return 0;
}

