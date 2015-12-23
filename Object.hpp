//
// Created by iMer on 23.12.2015.
//

#ifndef LD34_OBJECT_HPP
#define LD34_OBJECT_HPP

#include <Engine/SpriteNode.hpp>

class Object : public engine::SpriteNode {
protected:
    sf::Vector2f m_speed;
public:
    Object(engine::Scene* scene);

    virtual bool initialize(Json::Value& root);

protected:
    virtual void OnUpdate(sf::Time delta);
};


#endif //LD34_OBJECT_HPP
