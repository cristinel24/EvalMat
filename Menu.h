#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

RenderWindow window;
bool fullscreen;

void changeBck(Sprite &background) {
    const float WIDTH = 1920;
    const float HEIGHT = 1722;
    background.setScale({ window.getSize().x / WIDTH, window.getSize().y / HEIGHT });
}
void input(Sprite &back) {
    Event event;
    auto vec = back.getGlobalBounds();
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed) window.close();
        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
        if (Keyboard::isKeyPressed(Keyboard::F)) {
            if (!fullscreen)
                window.create(VideoMode(1920, 1080), "EvalMat", Style::Fullscreen); 
            if (fullscreen) 
                window.create(VideoMode(960, 540), "EvalMat");
            fullscreen = !fullscreen;
            changeBck(back);
        }
    }
}

void update(Sprite &back) {
    
    window.clear();
    window.draw(back);
    window.display();
}
void Menu() {

    window.create(VideoMode(960, 540), "EvalMat");
    Texture back_txt;
    back_txt.loadFromFile("./Resources/Images/background.png");
    Sprite background(back_txt);
    changeBck(background);

    while (window.isOpen())
    {
        input(background);
        update(background);
    }
}

