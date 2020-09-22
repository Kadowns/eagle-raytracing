//
// Created by Novak on 12/04/2020.
//

#ifndef EAGLE_SCENELAYER_H
#define EAGLE_SCENELAYER_H

#include <eagle/engine/EngineGlobalDefinitions.h>

EG_ENGINE_BEGIN

class SceneLayer : public Layer {
public:
    SceneLayer();
    virtual void handle_attach() override;

    virtual void handle_deattach() override;

    virtual void handle_update() override;

    virtual void handle_event(Event &e) override;
private:
    void generate_scene();
    glm::vec2 random_inside_unit_circle();
};

EG_ENGINE_END

#endif //EAGLE_SCENELAYER_H
