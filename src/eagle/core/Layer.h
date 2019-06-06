//
//  Created by Novak 05/06/2019
//  Code HEAVILY based on Hazel layers: https://github.com/TheCherno/Hazel
//

#ifndef EAGLE_LAYER_H
#define EAGLE_LAYER_H

#include "eagle/core/Core.h"
#include "eagle/core/events/Event.h"

_EAGLE_BEGIN

class Layer {

public:
    Layer()                         = default;
    virtual ~Layer()                = default;

    virtual void handle_attach()        {}
    virtual void handle_deattach()      {}
    virtual void handle_update()        {}
    virtual void handle_event(Event& e) {}
};

_EAGLE_END

#endif //EAGLE_LAYER_H
