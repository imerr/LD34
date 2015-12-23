//
// Created by iMer on 23.12.2015.
//

#include "Object.hpp"
#include "Level.hpp"

#include <Engine/util/json.hpp>

Object::Object(engine::Scene* scene) : SpriteNode(scene), m_speed(1, 0) {

}

bool Object::initialize(Json::Value& root) {
    if (!engine::SpriteNode::initialize(root)) {
        return false;
    }
    if (!root["speed"].isNull()) {
        m_speed = engine::vector2FromJson<float>(root["speed"]);
    }
    return true;
}

void Object::OnUpdate(sf::Time delta) {
    engine::SpriteNode::OnUpdate(delta);
    auto pos = GetPosition();
    if (pos.x + m_size.x < 0 || pos.x - m_size.x > m_scene->GetSize().x || pos.y - m_size.y > m_scene->GetSize().y) {
        this->Delete();
    }
    Level* level = static_cast<Level*>(m_scene);
    float speed = level->GetSpeed();
    m_body->SetLinearVelocity(b2Vec2(m_speed.x * sqrtf(speed), m_speed.y * sqrtf(speed)));
}
