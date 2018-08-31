// Test4.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <string>
#include <fcntl.h>
#include <awaituv.h>
#include "google.h"

using namespace awaituv;
using namespace std;

awaitable_t<void> start_dump_file(const std::string& str)
{
  // We can use the same request object for all file operations as they don't overlap.
  static_buf_t<1024> buffer;

  uv_file file = co_await fs_open(uv_default_loop(), str.c_str(), O_RDONLY, 0);
  if (file > 0)
  {
    (void) co_await fs_close(uv_default_loop(), file);
  }
}

int main(int argc, char* argv[])
{
  // Process command line
  if (argc == 1)
  {
    printf("test4 [--sequential] <file1> <file2> ...");
    return -1;
  }

  bool fRunSequentially = false;
  vector<string> files;
  for (int i = 1; i < argc; ++i)
  {
    string str = argv[i];
    if (str == "--sequential")
      fRunSequentially = true;
    else
      files.push_back(str);
  }

  if (fRunSequentially)
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  for (auto& file : files)
  {
    start_dump_file(file.c_str());
    if (fRunSequentially)
      uv_run(uv_default_loop(), UV_RUN_DEFAULT);
  }

  if (!fRunSequentially)
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  uv_loop_close(uv_default_loop());

  return 0;
}
