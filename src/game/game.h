#pragma once

class game {
public:
    game(const game&) = delete;
    game& operator=(const game&) = delete;
    ~game();

    static game& get();
    bool isRunning() const;

    void update(double dt);
private:
    game();
    static game* _S_instance;
};