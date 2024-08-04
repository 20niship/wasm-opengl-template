#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>  // Will drag system OpenGL headers

// This example can also compile and run with Emscripten! See
// 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
// TODO:
// #include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

static void glfw_error_callback(int error, const char* description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

static GLFWwindow* window_ = nullptr;

void load_imgui(GLFWwindow* window) {
  window_ = window;
#if defined(IMGUI_IMPL_OPENGL_ES2)
  // GL ES 2.0 + GLSL 100
  const char* glsl_version = "#version 100";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
  // GL 3.2 + GLSL 150
  const char* glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Required on Mac
#else
  // GL 3.0 + GLSL 130
  const char* glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+
  // only glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only
#endif

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

  // disable ini file
  io.IniFilename = nullptr;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
  ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
  ImGui_ImplOpenGL3_Init(glsl_version);

  // TODO: Load Fonts

  // Our state
}
using namespace std;

static bool show_demo_window = true;
static bool show_another_window = false;

void imgui_shutdown() {
  /* #ifdef __EMSCRIPTEN__ */
  /*     EMSCRIPTEN_MAINLOOP_END; */
  /* #endif */
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window_);
  glfwTerminate();
}

void imgui_draw() {
  static float time = 0;
  float t = glfwGetTime();
  auto deltaTime = t - time;
  time = t;

  glfwPollEvents();
  if (glfwGetWindowAttrib(window_, GLFW_ICONIFIED) != 0) {
    ImGui_ImplGlfw_Sleep(10);
    return;
  }

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  if (show_demo_window)
    ImGui::ShowDemoWindow(&show_demo_window);
  {
    static float f = 0.0f;
    static int counter = 0;
    ImGui::Begin("Hello, world!");
    auto io = ImGui::GetIO();
    ImGui::Text("This is some useful text.");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
  }

  if (show_another_window) {
    ImGui::Begin( "Another Window", &show_another_window); 
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
      show_another_window = false;
    ImGui::End();
  }

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // Rendering
  ImGui::Render();
  int display_w, display_h;
  glfwGetFramebufferSize(window_, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  /* glfwSwapBuffers(window); */
}
