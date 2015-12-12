//
// Created by iMer on 12.12.2015.
//

#include "Player.hpp"
#include <Engine/Game.hpp>
#include <iostream>

Player::~Player() {
    delete m_keyHandler;
}

Player::Player(engine::Scene *scene) : SpriteNode(scene), m_toPosTime(0), m_toPosVel(0, 0), m_slot(2) {
    m_keyHandler = m_scene->GetGame()->OnKeyDown.MakeHandler([this](const sf::Event::KeyEvent &e) {
        if (e.code == sf::Keyboard::Left && m_slot > 1) {
            m_slot--;
            GoTo();
        } else if (e.code == sf::Keyboard::Right && m_slot < 3) {
            m_slot++;
            GoTo();
        }
    });
    GoTo();
}

void Player::OnUpdate(sf::Time interval) {
    m_toPosTime -= interval.asSeconds();
    if (m_toPosTime < 0) {
        m_body->SetLinearVelocity(b2Vec2(0, 0));
    } else {
        m_body->SetLinearVelocity(m_toPosVel);
    }
}

void Player::GoTo() {
    float delta =  (m_slot * m_scene->GetSize().x/4) - GetPosition().x;
    m_toPosVel.x = delta;
    m_toPosVel.y = 500 - GetPosition().y;
    m_toPosVel *= 1/0.2/m_scene->GetPixelMeterRatio();
    m_toPosTime = 0.2;
}
