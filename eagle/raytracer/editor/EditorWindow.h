//
// Created by Novak on 22/03/2020.
//

#ifndef EAGLE_EDITORWINDOW_H
#define EAGLE_EDITORWINDOW_H

#include <eagle/raytracer/RaytracerGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

class EditorWindow {
public:
    EditorWindow(const std::string& name);
    virtual ~EditorWindow() = default;
    virtual void handle_update();
    virtual void handle_window_update() = 0;

    inline const std::string &name() const { return m_name; }
    inline bool is_hovered() const { return m_isHovered; }
    inline bool is_focused() const { return m_isFocused; }

protected:
    const std::string& m_name;

private:
    bool m_isHovered, m_isFocused;

};

EG_RAYTRACER_END

#endif //EAGLE_EDITORWINDOW_H
