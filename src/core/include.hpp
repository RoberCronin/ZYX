#pragma once

#include <GL/glew.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

// Core files
#include "core/Camera.hpp"
#include "core/Debug.hpp"
#include "core/Time.hpp"
#include "core/Window.hpp"
#include "core/input/Input.hpp"
#include "core/renderer/Shader.hpp"
#include "core/Texture.hpp"
#include "core/renderer/Framerate.hpp"
#include "core/renderer/VertexArrayObject.hpp"
#include "core/renderer/VertexBufferObject.hpp"

// External libraries
#include "stb_image/stb_image.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
