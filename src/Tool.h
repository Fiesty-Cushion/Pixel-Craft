#pragma once

class Tool {
public:
    virtual void Draw() = 0;
    virtual void HandleEvents() = 0;
    virtual void Preview() = 0;
    virtual ~Tool() {
    }
};
