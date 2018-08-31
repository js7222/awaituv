// Test5.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <string>
#include <fcntl.h>
#include <awaituv.h>
#include "google.h"

using namespace awaituv;
using namespace std;

awaitable_t<void> test_a()
{
  auto f1 = start_http_google();
  auto f2 = start_http_google();
  co_await future_of_all(f1, f2);
}

awaitable_t<void> test_b()
{
  awaitable_t<size_t> futures[2] = { start_http_google(), start_http_google() };
  auto fut = future_of_all_range(&futures[0], &futures[2]);
  auto results = co_await fut;
  printf("\n");
  for (auto& i : results)
    printf("%d\n", i);
}

awaitable_t<void> test_c()
{
  std::vector<awaitable_t<size_t>> vec;
  vec.push_back(start_http_google());
  vec.push_back(start_http_google());
  auto fut = future_of_all_range(vec.begin(), vec.end());
  auto results = co_await fut;
  printf("\n");
  for (auto& i : results)
    printf("%d\n", i);
}

//awaitable_t<void> test_d()
//{
//  auto f1 = start_http_google();
//  auto f2 = start_http_google();
//  co_await future_of_any(f1, f2);
//}

int main(int argc, char* argv[])
{
  // Process command line
  if (argc != 1)
  {
    printf("testuv");
    return -1;
  }

  test_a();
  uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  test_b();
  uv_run(uv_default_loop(), UV_RUN_DEFAULT);

   test_c();
  uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  //test_d();
  //uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  uv_loop_close(uv_default_loop());

  return 0;
}
