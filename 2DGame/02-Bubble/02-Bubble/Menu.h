#ifndef MENU_INCLUDE
#define MENU_INCLUDE

#include <glm/glm.hpp>

#include "Background.h"
#include "ShaderProgram.h"
#include "Texture.h"

class Menu {
public:
    Menu();
    ~Menu();

    void init(int start);
    void update(int deltaTime);
    void render();

    bool getPlay();

private:
    void initShaders();

private:
    ShaderProgram texProgram;
    int state;
    bool play;
    glm::mat4 projection;
    Background* background;
    Texture tex[10];
    int cont;
};

#endif  // MENU_INCLUDE