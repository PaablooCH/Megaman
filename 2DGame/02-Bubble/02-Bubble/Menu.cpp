#include "Menu.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Game.h"
#include <GL/freeglut_std.h>

Menu::Menu() {}

Menu::~Menu() {
    if (background != NULL) {
        delete background;
        background = nullptr;
    }
}

void Menu::init() {
    state = 0;
    play = false;
    cont = 0;
    glm::vec2 geom[2] = { glm::vec2(0.f), glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT) };
    glm::vec2 texCoords[2] = { glm::vec2(0.f), glm::vec2(1.f) };

    initShaders();
    background = Background::createBackground(geom, texCoords, texProgram);
    tex[0].loadFromFile("images/Menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
    tex[0].setMinFilter(GL_NEAREST);
    tex[0].setMagFilter(GL_NEAREST);
    tex[1].loadFromFile("images/iPlayer.png", TEXTURE_PIXEL_FORMAT_RGBA);
    tex[1].setMinFilter(GL_NEAREST);
    tex[1].setMagFilter(GL_NEAREST);
    tex[2].loadFromFile("images/Objetos.png", TEXTURE_PIXEL_FORMAT_RGBA);
    tex[2].setMinFilter(GL_NEAREST);
    tex[2].setMagFilter(GL_NEAREST);
    tex[3].loadFromFile("images/Bonus1.png", TEXTURE_PIXEL_FORMAT_RGBA);
    tex[3].setMinFilter(GL_NEAREST);
    tex[3].setMagFilter(GL_NEAREST);
    tex[4].loadFromFile("images/Bonus2.png", TEXTURE_PIXEL_FORMAT_RGBA);
    tex[4].setMinFilter(GL_NEAREST);
    tex[4].setMagFilter(GL_NEAREST);
    tex[5].loadFromFile("images/Enemigos.png", TEXTURE_PIXEL_FORMAT_RGBA);
    tex[5].setMinFilter(GL_NEAREST);
    tex[5].setMagFilter(GL_NEAREST);
    tex[6].loadFromFile("images/Obstaculos.png", TEXTURE_PIXEL_FORMAT_RGBA);
    tex[6].setMinFilter(GL_NEAREST);
    tex[6].setMagFilter(GL_NEAREST);
    tex[7].loadFromFile("images/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
    tex[7].setMinFilter(GL_NEAREST);
    tex[7].setMagFilter(GL_NEAREST);
    projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
}

void Menu::update(int deltaTime)
{
    cont += deltaTime;
    if (cont >= 200) {
        switch (state) {
        case 0: { //Menu
            if (Game::instance().getKey(GLUT_s) || Game::instance().getKey(GLUT_S))
                play = true;
            else if (Game::instance().getKey(GLUT_i) || Game::instance().getKey(GLUT_I)) {
                state = 1;
            }
            else if (Game::instance().getKey(GLUT_c) || Game::instance().getKey(GLUT_C)) {
                state = 7;
                cont = 0;
            }
        }break;
        case 1: { //iPlayer
            if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
                state = 0;
                cont = 0;
            }
            else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
                state = 2;
                cont = 0;
            }
        }break;
        case 2: { //Objetos
            if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
                state = 1;
                cont = 0;
            }
            else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
                state = 3;
                cont = 0;
            }
        }break;
        case 3: { //Bonus1
            if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
                state = 2;
                cont = 0;
            }
            else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
                state = 4;
                cont = 0;
            }
        }break;
        case 4: { //Bonus2
            if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
                state = 3;
                cont = 0;
            }
            else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
                state = 5;
                cont = 0;
            }
        }break;
        case 5: {//Enemigos
            if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
                state = 4;
                cont = 0;
            }
            else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
                state = 6;
                cont = 0;
            }
        }break;
        case 6: {//Obstaculos
            if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
                state = 5;
                cont = 0;
            }
            else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
                state = 0;
                cont = 0;
            }
        }break;
        case 7: {//credit
            if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
                state = 0;
                cont = 0;
            }
        } break;
        }
    }
}

void Menu::render() {
    glm::mat4 modelview;

    texProgram.use();
    texProgram.setUniformMatrix4f("projection", projection);
    texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
    modelview = glm::mat4(1.0f);

    switch (state) {
    case 0: //Menu
        background->render(tex[0], modelview);
        break;
    case 1: //iPlayer
        background->render(tex[1], modelview);
        break;
    case 2: //Objetos
        background->render(tex[2], modelview);
        break;
    case 3: //Bonus1
        background->render(tex[3], modelview);
        break;
    case 4: //Bonus2
        background->render(tex[4], modelview);
        break;
    case 5: //Enemigos
        background->render(tex[5], modelview);
        break;
    case 6: //Obstaculos
        background->render(tex[6], modelview);
        break;
    case 7: //credit
        background->render(tex[7], modelview);
        break;
    }
}

bool Menu::getPlay()
{
    return play;
}

void Menu::initShaders() {
    Shader vShader, fShader;

    vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
    if (!vShader.isCompiled()) {
        cout << "Vertex Shader Error" << endl;
        cout << "" << vShader.log() << endl << endl;
    }
    fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
    if (!fShader.isCompiled()) {
        cout << "Fragment Shader Error" << endl;
        cout << "" << fShader.log() << endl << endl;
    }
    texProgram.init();
    texProgram.addShader(vShader);
    texProgram.addShader(fShader);
    texProgram.link();
    if (!texProgram.isLinked()) {
        cout << "Shader Linking Error" << endl;
        cout << "" << texProgram.log() << endl << endl;
    }
    texProgram.bindFragmentOutput("outColor");
    vShader.free();
    fShader.free();
}