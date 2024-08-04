/**
 * Application.cpp
 * Contributors:
 *      * Arthur Sonzogni (author)
 * Licence:
 *      * MIT
 */

#ifndef OPENGL_CMAKE_SKELETON_APPLICATION_HPP
#define OPENGL_CMAKE_SKELETON_APPLICATION_HPP

#include <string>

struct GLFWwindow;

class Application {
 public:
  Application();

  GLFWwindow* getWindow() const;
  void exit();

  // delta time between frame and time from beginning
  float getFrameDeltaTime() const;
  float getTime() const;

  void run();

  float getWindowRatio() { return float(width) / float(height); }
  bool windowDimensionChanged();

 private:
  enum State { stateReady, stateRun, stateExit };

  State state;

  Application& operator=(const Application&) { return *this; }

  GLFWwindow* window;

  // Time:
  float time;
  float deltaTime;

  // Dimensions:
  bool dimensionChanged;
  void detectWindowDimensionChange();

 protected:
  Application(const Application&){};

  int width;
  int height;
  std::string title;

  virtual void loop();
};

#endif /* end of include guard: OPENGL_CMAKE_SKELETON_APPLICATION_HPP */
