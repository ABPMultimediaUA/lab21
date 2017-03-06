#ifndef GSTATE_H
#define GSTATE_H

class GState {
public:
    virtual void HandleEvents() { };
    virtual void Update() { };
    virtual void Render() { };
    virtual	~GState(){};

};

#endif /* GSTATE_H */