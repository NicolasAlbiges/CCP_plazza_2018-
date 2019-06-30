#include "SFML/Graphics.hpp"
#include "Plazza.hpp"
#include <iostream>

int runGraphic(PlazzaIPC *ipc, int cookMax)
{
  sf::RenderWindow renderWindow(sf::VideoMode(1220, 1000), "Plazza graphical interface");

    if (cookMax > 25)
        cookMax = 25;
    sf::Font font;
    if (!font.loadFromFile("./ressources/font.ttf")) {
        fprintf(stderr, "No font found.\n");
        exit(84);
    }
  
    sf::Text text("GUI Plazza", font, 100);
    text.setColor(sf::Color::Red);
    text.setPosition(305, 10);
    sf::RectangleShape rectangle(sf::Vector2f(210, 150));
    rectangle.setFillColor(sf::Color::Black);

    sf::RectangleShape rectangleCook(sf::Vector2f(30, 20));
    rectangleCook.setFillColor(sf::Color::Green);

    int x = 10;
    int y = 200;
    int xCook = 10 + x;
    int yCook = 5 + y;
    std::pair<int, std::vector< sf::RectangleShape> > rectangleList;
    std::pair<int, std::vector<sf::RectangleShape> > rectangleListCook;
    int activeCook = 0;
    std::vector<int> fdKitchen = ipc->getKitchenId();
    std::vector<std::pair<int, int>> graphTab = ipc->getGraphTab();

    while (renderWindow.isOpen()){
        sf::Event event;

        fdKitchen = ipc->getKitchenId();
        graphTab = ipc->getGraphTab();
        if (fdKitchen.size() > rectangleList.second.size()) {
            for (unsigned int ct = rectangleList.second.size(); ct != fdKitchen.size(); ct ++) {

            rectangleList.first = fdKitchen[ct];
            rectangleList.second.push_back(rectangle);
            rectangleList.second[ct].setPosition(x, y);
            for (int ctb = 0; ctb != cookMax; ctb ++) {
                rectangleListCook.first = fdKitchen[ct];
                rectangleCook.setFillColor(sf::Color::Red);
                rectangleListCook.second.push_back(rectangleCook);
                rectangleListCook.second[(ct * cookMax) + ctb].setPosition(xCook, yCook);
                xCook = xCook + 40;
                if (xCook > (x + 200)) {
                    xCook = 10 + x;
                    yCook = 30 + yCook;
                }
            }
            rectangleCook.setFillColor(sf::Color::Green);
            x = x + 300;
            if (x > 1200) {
                x = 10;
                y = y + 200;
                yCook = 5 + y;
            }
            yCook = 5 + y;
            xCook = 10 + x;
            
            }
        }
        if (fdKitchen.size() < rectangleList.second.size()) {
            for (unsigned int ct = (cookMax * rectangleList.second.size()); ct != (fdKitchen.size() * cookMax); ct --) {
                rectangleListCook.second.pop_back();
            }
            for (unsigned int ct = rectangleList.second.size(); ct != fdKitchen.size(); ct --) {
                rectangleList.second.pop_back();
                x = x - 300;
                if (x < 0) {
                    x = 10;
                    y = y - 200;
                }
                yCook = 5 + y;
                xCook = 10 + x;
            }
        }
        for (unsigned int ct = 0; ct != fdKitchen.size(); ct ++) {
            activeCook = 0;
            for (unsigned int ctGraph = 0; ctGraph != graphTab.size(); ctGraph ++) {
                    if (fdKitchen[ct] == graphTab[ctGraph].first) {
                        activeCook = graphTab[ctGraph].second;
                        for (int ctb = 0; ctb != cookMax; ctb ++) {
                            if (activeCook > ctb)
                                rectangleListCook.second[(ct * cookMax) + ctb].setFillColor(sf::Color::Green);
                            else
                                rectangleListCook.second[(ct * cookMax) + ctb].setFillColor(sf::Color::Red);
                        }
                    }
                }
        }

        while (renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                renderWindow.close();
            }
        }
        renderWindow.clear(sf::Color::White);

        renderWindow.draw(text);
        for (unsigned int ct = 0; ct != rectangleList.second.size(); ct ++) {
            renderWindow.draw(rectangleList.second[ct]);
        }
        for (unsigned int ct = 0; ct != rectangleListCook.second.size(); ct ++) {
            renderWindow.draw(rectangleListCook.second[ct]);
        }

        renderWindow.display();

        ipc->clearGraphTab();
        for (unsigned int ct = 0; ct != ipc->getKitchenId().size(); ct ++) {
            *ipc << ipc->getKitchenId()[ct];
            *ipc << std::string("GRAPH");
        }
        sleep(1);
    }
    return (0);
}