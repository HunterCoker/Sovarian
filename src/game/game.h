#pragma once

class game {
public:
    game(const game&) = delete;
    game& operator=(const game&) = delete;
    ~game();

    static game& get();

    void update(double dt);

    bool isRunning() const;
private:
    game();
    static game* _S_instance;
};