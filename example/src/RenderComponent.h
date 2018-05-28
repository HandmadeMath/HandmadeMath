#include <HandmadeMath.h>

#ifndef HMME_RENDER_COMPONENT_H
#define HMME_RENDER_COMPONENT_H

#include "Entity.h"

class RenderComponent {
public:
    virtual void Draw() = 0;
};

#endif
