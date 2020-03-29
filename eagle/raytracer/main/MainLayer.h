//
// Created by Novak on 28/03/2020.
//

#ifndef EAGLE_MAINLAYER_H
#define EAGLE_MAINLAYER_H

#include <eagle/raytracer/RaytracerGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

class MainLayer : public Layer{
public:

    MainLayer();

    virtual ~MainLayer() override;

    virtual void handle_attach() override;

    virtual void handle_deattach() override;

    virtual void handle_update() override;

    virtual void handle_event(Event &e) override;

};

EG_RAYTRACER_END


#endif //EAGLE_MAINLAYER_H
