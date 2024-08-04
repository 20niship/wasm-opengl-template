/**
 * Main.cpp skeleton
 * Contributors:
 *      * Arthur Sonzogni
 * Licence:
 *      * MIT
 */

#include "MyApplication.hpp"
#include <iostream>

int main(int argc, const char* argv[]) {
  std::cout << "Hello World" << std::endl;
  MyApplication app;
  std::cout << "App created" << std::endl;
  app.run();
  return 0;
}
