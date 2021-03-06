// Copyright 2018-2020 the openhoi authors. See COPYING.md for legal info.

#include "gui/gui_manager.hpp"

#include <OgreImGuiOverlay.h>
#include <OgreOverlayManager.h>
#include <imgui_impl_sdl.h>

#include <hoibase/openhoi.hpp>
#ifdef OPENHOI_OS_WINDOWS
#  include <OgreD3D11RenderSystem.h>
#endif
#include <OgreGLRenderSystemCommon.h>

#include <cassert>

namespace openhoi {

// Initializes the GUI manager
GuiManager::GuiManager() {
  // Configure ImGui
  configureGui();

  // Create debug console
  debugConsole = std::make_shared<DebugConsole>();
}

// Destroys the GUI manager
GuiManager::~GuiManager() {
  // Destroy ImGui SDL2 implementation
  ImGui_ImplSDL2_Shutdown();
}

// Initialize GUI manager
void GuiManager::initialize(Ogre::SceneManager* sceneManager,
                            Ogre::RenderSystem* renderSystem,
                            SDL_Window* window) {
  // Set scene manager reference
  this->sceneManager = sceneManager;

  // Set window reference
  this->window = window;

  // Initialize ImGui SDL implementation
#ifdef OPENHOI_OS_WINDOWS
  if (Ogre::D3D11RenderSystem* d3d11RenderSystem =
          dynamic_cast<Ogre::D3D11RenderSystem*>(renderSystem)) {
    ImGui_ImplSDL2_InitForD3D(window);
  } else {
#endif
    Ogre::GLContext* glContext = nullptr;
    if (Ogre::GLRenderSystemCommon* glRenderSystem =
            dynamic_cast<Ogre::GLRenderSystemCommon*>(renderSystem)) {
      glContext = glRenderSystem->_getCurrentContext();
    }
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
#ifdef OPENHOI_OS_WINDOWS
  }
#endif
}

// Handle SDL event
void GuiManager::handleEvent(SDL_Event event) {
  ImGui_ImplSDL2_ProcessEvent(&event);
}

// Gets the default font
ImFont* GuiManager::getDefaultFont() {
  assert(defaultFont);
  return defaultFont;
}

// Gets the big font
ImFont* GuiManager::getBigFont() {
  assert(bigFont);
  return bigFont;
}

// Get debug console
std::shared_ptr<DebugConsole> const& GuiManager::getDebugConsole() const {
  return debugConsole;
}

// Render new GUI frame
void GuiManager::newFrame(const Ogre::FrameEvent& e) {
  // Start the ImGui frame
  ImGui_ImplSDL2_NewFrame(window);
  Ogre::ImGuiOverlay::NewFrame(e);

  // Draw debug console
  debugConsole->draw();
}

// Configure GUI
void GuiManager::configureGui() {
  // Create ImGui overlay
  auto imguiOverlay = new Ogre::ImGuiOverlay();
  imguiOverlay->setZOrder(300);

  // Load default dont
  defaultFont = imguiOverlay->addFont("gui/default");
  // Load big font
  bigFont = imguiOverlay->addFont("gui/default");

  // Show overlay (fonts must be added at this point)
  imguiOverlay->show();

  // Add overlay to overlay manager
  Ogre::OverlayManager::getSingleton().addOverlay(imguiOverlay);

  // Get ImGui IO
  ImGuiIO& io = ImGui::GetIO();

  // Disable INI file
  io.IniFilename = NULL;

  // Enable docking
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  // Enable viewports
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  // Set GUI style
  ImGuiStyle& style = ImGui::GetStyle();
  style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
  style.Colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 0.95f);
  style.Colors[ImGuiCol_ChildBg] = ImVec4(0.25f, 0.25f, 0.25f, 0.95f);
  style.Colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 0.95f);
  style.Colors[ImGuiCol_Border] = ImVec4(0.12f, 0.12f, 0.12f, 0.71f);
  style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  style.Colors[ImGuiCol_FrameBg] = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
  style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
  style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
  style.Colors[ImGuiCol_TitleBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
  style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
  style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
  style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.335f, 0.335f, 0.335f, 1.00f);
  style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
  style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
  style.Colors[ImGuiCol_ScrollbarGrabHovered] =
      ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
  style.Colors[ImGuiCol_ScrollbarGrabActive] =
      ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
  style.Colors[ImGuiCol_CheckMark] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
  style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
  style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
  style.Colors[ImGuiCol_Button] = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
  style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
  style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
  style.Colors[ImGuiCol_Header] = ImVec4(0.38f, 0.38f, 0.38f, 0.94f);
  style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.47f, 0.47f, 0.47f, 0.98f);
  style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.98f);
  style.Colors[ImGuiCol_Separator] = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
  style.Colors[ImGuiCol_SeparatorHovered] =
      ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
  style.Colors[ImGuiCol_SeparatorActive] =
      ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
  style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
  style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.48f, 0.47f, 0.45f, 0.29f);
  style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.70f, 0.67f, 0.60f, 0.67f);
  style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
  style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  style.Colors[ImGuiCol_PlotHistogramHovered] =
      ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
  style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
  style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
  style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  style.Colors[ImGuiCol_NavWindowingHighlight] =
      ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
  style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
  style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
  style.Colors[ImGuiCol_Tab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  style.Colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
  style.Colors[ImGuiCol_TabActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
  style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  style.Colors[ImGuiCol_TabUnfocusedActive] =
      ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
  style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);

  style.PopupRounding = 3;

  style.WindowPadding = ImVec2(4, 4);
  style.FramePadding = ImVec2(6, 4);
  style.ItemSpacing = ImVec2(6, 2);

  style.ScrollbarSize = 18;

  style.WindowBorderSize = 1;
  style.ChildBorderSize = 1;
  style.PopupBorderSize = 1;
  style.FrameBorderSize = 1;
  style.TabBorderSize = 1;

  style.WindowRounding = 3;
  style.ChildRounding = 3;
  style.FrameRounding = 3;
  style.ScrollbarRounding = 2;
  style.GrabRounding = 3;
  style.TabRounding = 3;

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }
}

}  // namespace openhoi