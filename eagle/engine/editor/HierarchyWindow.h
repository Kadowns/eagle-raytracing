//
// Created by Novak on 06/08/2019.
//

#ifndef EAGLE_HIERARCHYWINDOW_H
#define EAGLE_HIERARCHYWINDOW_H

#include "EditorWindow.h"

EG_ENGINE_BEGIN

class HierarchyWindow : public EditorWindow {
public:
    HierarchyWindow(const std::shared_ptr<entityx::EntityManager>& entities);
    virtual ~HierarchyWindow();

protected:
    virtual void handle_update() override;
private:
    std::shared_ptr<entityx::EntityManager> m_entities;
};

EG_ENGINE_END


#endif //EAGLE_HIERARCHYWINDOW_H
