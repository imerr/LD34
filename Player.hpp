//
// Created by iMer on 12.12.2015.
//

#ifndef LD34_PLAYER_HPP
#define LD34_PLAYER_HPP


#include <Engine/SpriteNode.hpp>

class Player: public engine::SpriteNode {
protected:
    void* m_keyHandler;
    b2Vec2 m_toPosVel;
    float m_toPosTime;
    uint8_t m_slot;
public:
    Player(engine::Scene* scene);
    ~Player();
    void GoTo();
protected:
    virtual void OnUpdate(sf::Time interval);
};


#endif //LD34_PLAYER_HPP
