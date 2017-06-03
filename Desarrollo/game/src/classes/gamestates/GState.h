#ifndef GSTATE_H
#define GSTATE_H

#include <GraphicsEngine.h>

class GState {
public:
    virtual void HandleEvents() { };
    virtual void Update() { };
    virtual void Render() { };
    virtual void Init() {};
    virtual	~GState(){};

};

#endif /* GSTATE_H */
