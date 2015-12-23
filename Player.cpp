//
// Created by iMer on 12.12.2015.
//

#include "Player.hpp"
#include "Level.hpp"
#include <Engine/Game.hpp>
#include <Engine/util/misc.hpp>
#include <iostream>

Player::Player(engine::Scene* scene) : SpriteNode(scene), m_toPosTime(0), m_toPosVel(0, 0), m_slot(2) {
    m_keyHandler = m_scene->GetGame()->OnKeyDown.MakeHandler([this](const sf::Event::KeyEvent& e) {
        if (e.code == sf::Keyboard::Left) {
            ProcessKey(e.code);
        } else if (e.code == sf::Keyboard::Right) {
            ProcessKey(e.code);
        }
    });
    m_collisionHandler = m_scene->OnContactPreSolve.MakeHandler([this](b2Contact* contact, const b2Manifold* manifold) {
        auto a = static_cast<engine::Node*>(contact->GetFixtureA()->GetBody()->GetUserData());
        auto b = static_cast<engine::Node*>(contact->GetFixtureB()->GetBody()->GetUserData());
        engine::Node* other = nullptr;
        if (a == this) {
            other = b;
        } else if (b == this) {
            other = a;
        }
        if (other) {
            Level* level = static_cast<Level*>(m_scene);
            if (other->GetFilename() == level->GetSearching()) {
                level->AddPoint(10);
            } else {
                level->AddPoint(-20);
            }
            other->Delete();
        }
    });
}

Player::~Player() {
    delete m_keyHandler;
    delete m_collisionHandler;
}

void Player::OnUpdate(sf::Time interval) {
    m_toPosTime -= interval.asSeconds();
    if (m_toPosTime < 0) {
        m_body->SetLinearVelocity(b2Vec2(0, 0));
        m_body->SetTransform(b2Vec2((m_slot * m_scene->GetSize().x / 4.0f) / m_scene->GetPixelMeterRatio(),
                                    (m_scene->GetSize().y - 50) / m_scene->GetPixelMeterRatio()), m_body->GetAngle());
    } else {
        m_body->SetLinearVelocity(m_toPosVel);
    }
    float speed = static_cast<Level*>(m_scene)->GetSpeed();
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
    m_toPosVel.y = (m_scene->GetSize().y - 50) - GetPosition().y;
    m_toPosVel *= 1.0f / m_scene->GetPixelMeterRatio() * sqrtf(static_cast<Level*>(m_scene)->GetSpeed());
    m_toPosTime = 1.0f / sqrtf(static_cast<Level*>(m_scene)->GetSpeed());
}

bool Player::initialize(Json::Value& root) {
    if (!engine::SpriteNode::initialize(root)) {
        return false;
    }
    GoTo();
    return true;
}
