#pragma once
#include <SFML/Graphics.hpp>
#include <cstdarg>
using namespace sf;

RenderWindow window;
bool fullscreen, press;

void changeBck(Sprite &background) {
    const float WIDTH = 1920;
    const float HEIGHT = 1722;
    background.setScale({ window.getSize().x / WIDTH, window.getSize().y / HEIGHT });
}
void input(Sprite &back, Sprite& logo, Sprite& start) {
    Event event;
    auto vec = back.getGlobalBounds();
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed) window.close();
        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
        if (Keyboard::isKeyPressed(Keyboard::F)) {
            if (!fullscreen) {
                window.create(VideoMode(1920, 1080), "EvalMat", Style::Fullscreen);
                logo.setPosition({ window.getSize().x / 2.525f , window.getSize().y / 4.4f });
                logo.setScale({ 0.4, 0.4 });
                start.setPosition({ window.getSize().x / 2.41f , window.getSize().y / 1.8f });
                start.setScale({ 0.7, 0.7 });
            }
            if (fullscreen) {
                window.create(VideoMode(960, 540), "EvalMat");
                logo.setPosition({ window.getSize().x / 2.525f , window.getSize().y / 4.4f });
                logo.setScale({ 0.2, 0.2 });
                start.setPosition({ window.getSize().x / 2.5f , window.getSize().y / 1.8f });
                start.setScale({ 0.4, 0.4 });
            }   
            fullscreen = !fullscreen;
            changeBck(back);
        }
        
    }
    if (Mouse::isButtonPressed(Mouse::Left)) {
        auto coord = start.getLocalBounds();
        cout << coord.height << ' ' << coord.width << '\n';
        cout << Mouse::getPosition().x << ' ' << Mouse::getPosition().y << '\n';
        if (coord.contains(Mouse::getPosition().x, Mouse::getPosition().y)) {
            Texture start_press_txt;
            start_press_txt.loadFromFile("./Resources/Images/start-press.png");
            Sprite start_press(start_press_txt);
            start_press.setPosition({ window.getSize().x / 2.5f , window.getSize().y / 1.8f });
            start_press.setScale({ 0.4, 0.4 });
            start.setTexture(start_press_txt);
            cout << "DA";
        }

    }
}

void update(int lg, ...) {
    
    va_list args;
    va_start(args, lg);
    window.clear();
    for (int i = 0; i < lg; i++)
        window.draw(va_arg(args, Sprite));
    window.display();
}
void Menu() {

    window.create(VideoMode(960, 540), "EvalMath");
    Texture back_txt, logo_txt, start_txt;
    back_txt.loadFromFile("./Resources/Images/background.png");
    logo_txt.loadFromFile("./Resources/Images/logo.png");
    start_txt.loadFromFile("./Resources/Images/start.png");
    Sprite background(back_txt), logo(logo_txt), start(start_txt);
    logo.setPosition({ window.getSize().x / 2.525f , window.getSize().y / 4.4f });
    logo.setScale({ 0.2, 0.2 });
    start.setPosition({ window.getSize().x / 2.5f , window.getSize().y / 1.8f });
    start.setScale({0.4, 0.4});
    changeBck(background);

    while (window.isOpen())
    {
        input(background, logo, start);
        update(3, background, logo, start);
    }
}

