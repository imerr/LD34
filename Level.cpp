//
// Created by iMer on 12.12.2015.
//

#include <iostream>
#include "Level.hpp"

Level::Level(engine::Game *game) : Scene(game), m_speed(1) {

}

Level::~Level() {

}

void Level::OnUpdate(sf::Time interval) {
    engine::Scene::OnUpdate(interval);
    if (m_speed < 5) {
        m_speed += 0.2 * interval.asSeconds();
    } else if (m_speed < 50) {
        m_speed += 0.1 * interval.asSeconds();
    }
}
