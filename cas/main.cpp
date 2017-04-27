#include <iostream>
#include <thread>
#include <vector>
#include <boost/atomic.hpp>
#include <boost/thread/thread.hpp>
using namespace std;

boost::atomic_int a ;//typedef atomic<int> atomic_int;

void fun()
{
    for (auto i = 0; i < 10000; ++i)
    {
        a++;
    }
}

int main(int argc, char** argv)
{
    a = 0;
    std::vector<std::thread> th;
    for (int i = 0; i <10; ++i)
    {
        th.push_back(std::thread(fun));
    }
    for (auto& t : th)
    {
        t.join();
    }
    cout << a << std::endl;
    getchar();
    return 0;
}