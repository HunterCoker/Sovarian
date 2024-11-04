#pragma once

class render_system {
public:
    virtual void renderBegin() const = 0;
    virtual void renderEnd() const = 0;
private:
};