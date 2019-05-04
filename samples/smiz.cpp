#include <awaituv.h>
#include <thread>
#include <chrono>
#include <iostream>
using namespace awaituv;

future_t<void> start_hello_world()
{
    for (int i = 0; i < 1000; ++i)
    {
        string_buf_t buf("\nhello world\n");
        fs_t req;
        auto ret = co_await fs_write(uv_default_loop(), &req, 1 /*stdout*/, &buf, 1, -1);
        std::cout << "ret: " << ret << '\n';
    }
}

int main(int argc, char* argv[]) 
{
    using namespace std::chrono_literals;
    start_hello_world();
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    std::this_thread::sleep_for(2s);
    return 0;
}