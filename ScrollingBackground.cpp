#include "ScrollingBackground.hpp"
#include "Level.hpp"

ScrollingBackground::ScrollingBackground(engine::Scene *scene): SpriteNode(scene) {

}

ScrollingBackground::~ScrollingBackground() {

}

void ScrollingBackground::OnUpdate(sf::Time interval) {
    engine::SpriteNode::OnUpdate(interval);
    auto& pos = getPosition();
    float speed = 60 * sqrtf(static_cast<Level*>(m_scene)->GetSpeed() * 2.0f);
    if (pos.y + speed * interval.asSeconds() > 0) {
        setPosition(pos.x, pos.y - m_size.y/2 + speed * interval.asSeconds());
    } else {
        setPosition(pos.x, pos.y + speed * interval.asSeconds());
    }
}
