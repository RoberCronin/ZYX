#pragma once

#include <utility>

class Input
{
public:
    // returns if a keyboard key is pressed, uses GLFW for keycodes
    inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

    // returns if mouse button is being pressed, uses GLFW for button index
    inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

    // returns a std::pair that contains the mouse position relative to the window
    // the first element is the X, the second is the Y,
    inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

    // gets only the mouse x position, relative to the window
    inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
    
    // gets only the mouse y position, relative to the window
    inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

protected:
    virtual bool IsKeyPressedImpl(int keycode) = 0;

    virtual bool IsMouseButtonPressedImpl(int keycode) = 0;
    virtual std::pair<float, float> GetMousePositionImpl() = 0;
    virtual float GetMouseXImpl() = 0;
    virtual float GetMouseYImpl() = 0;

private:
    static Input* s_Instance;
};