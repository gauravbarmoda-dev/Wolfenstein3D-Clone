#ifndef INPUT_H
#define INPUT_H

#include <vector>

enum class Keys{
    W, A, S, D, E, Q
};

class Input{
private:
    std::vector<unsigned char> previousKeyState;
    const unsigned char* sdlKey;
    int numKey;

public:
    Input();
    ~Input() = default;

    void Update();
    
    bool isKeyDown(Keys key);
    bool isKeyPressed(Keys key);
};

#endif
