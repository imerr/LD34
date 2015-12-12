//
// Created by iMer on 12.12.2015.
//

#include "Player.hpp"
#include "Level.hpp"
#include <Engine/Game.hpp>
#include <iostream>

Player::~Player() {
    delete m_keyHandler;
}

Player::Player(engine::Scene *scene) : SpriteNode(scene), m_toPosTime(0), m_toPosVel(0, 0), m_slot(2), m_jumping(0),
                                       m_lastPressed(sf::Keyboard::Unknown), m_lastPressedTimeout(0) {
    m_keyHandler = m_scene->GetGame()->OnKeyDown.MakeHandler([this](const sf::Event::KeyEvent &e) {
        if (e.code == sf::Keyboard::Left) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_lastPressed == sf::Keyboard::Right &&
                m_lastPressedTimeout > 0) {
                m_lastPressed = sf::Keyboard::Unknown;
                Jump();
                return;
            }
            if (m_lastPressedTimeout > 0 && m_lastPressed == sf::Keyboard::Unknown) {
                ProcessKey(m_lastPressed);
                m_lastPressed = sf::Keyboard::Unknown;
            }
            m_lastPressed = sf::Keyboard::Left;
            m_lastPressedTimeout = 0.1f;
        } else if (e.code == sf::Keyboard::Right) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_lastPressed == sf::Keyboard::Left &&
                m_lastPressedTimeout > 0) {
                Jump();
                m_lastPressed = sf::Keyboard::Unknown;
                return;
            }
            if (m_lastPressedTimeout > 0 && m_lastPressed == sf::Keyboard::Unknown) {
                ProcessKey(m_lastPressed);
                m_lastPressed = sf::Keyboard::Unknown;
            }
            m_lastPressed = sf::Keyboard::Right;
            m_lastPressedTimeout = 0.1f;
        }
    });
}

void Player::OnUpdate(sf::Time interval) {
    m_jumping -= interval.asSeconds();
    m_toPosTime -= interval.asSeconds();
    m_lastPressedTimeout -= interval.asSeconds();
    if (m_lastPressedTimeout < 0 && m_lastPressed != sf::Keyboard::Unknown) {
        ProcessKey(m_lastPressed);
        m_lastPressed = sf::Keyboard::Unknown;
    }
    if (m_toPosTime < 0) {
        m_body->SetLinearVelocity(b2Vec2(0, 0));
    } else {
        m_body->SetLinearVelocity(m_toPosVel);
    }
    float speed = static_cast<Level *>(m_scene)->GetSpeed();
    if (GetAnimationName() != "jump") {
        if (speed < 5) {
            if (GetAnimationName() != "default") {
                PlayAnimation("default");
            }
        } else if (speed < 10) {
            if (GetAnimationName() != "fast")
                PlayAnimation("fast");
        } else if (speed < 20) {
            if (GetAnimationName() != "faster") {
                PlayAnimation("faster");
            }
        } else if (speed > 20) {
            if (GetAnimationName() != "fastest") {
                PlayAnimation("fastest");
            }
        }
    }
}
void Player::ProcessKey(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Left && m_slot > 1) {
        m_slot--;
        GoTo();
    }
    if (key == sf::Keyboard::Right && m_slot < 3) {
        m_slot++;
        GoTo();
    }
}
void Player::GoTo() {
    float delta = (m_slot * m_scene->GetSize().x / 4) - GetPosition().x;
    m_toPosVel.x = delta;
    m_toPosVel.y = 500 - GetPosition().y;
    m_toPosVel *= 1 / 0.2 / m_scene->GetPixelMeterRatio();
    m_toPosTime = 0.2f;
}

bool Player::initialize(Json::Value &root) {
    if (!engine::SpriteNode::initialize(root)) {
        return false;
    }
    GoTo();
    return true;
}

void Player::Jump() {
    m_jumping = 0.5f;
    PlayAnimation("jump", "default");
}
