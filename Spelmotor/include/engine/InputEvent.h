#ifndef ENGINE_INPUT_EVENT_H
#define ENGINE_INPUT_EVENT_H

namespace engine {

    enum class Key {
        Unknown,
        W, A, S, D,
        Up, Down, Left, Right,
        Space, Escape
    };

    enum class MouseButton {
        Left, Middle, Right, Unknown
    };

    struct InputEvent {
        enum class Type {
            KeyDown, KeyUp,
            MouseMove,
            MouseDown, MouseUp,
            Quit
        } type{ Type::Quit };

        Key key{ Key::Unknown };

        int mouseX{ 0 };
        int mouseY{ 0 };
        MouseButton mouseButton{ MouseButton::Unknown };
    };

} 

#endif