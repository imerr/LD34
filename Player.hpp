//
// Created by iMer on 12.12.2015.
//

#ifndef LD34_PLAYER_HPP
#define LD34_PLAYER_HPP


#include <Engine/SpriteNode.hpp>
#include <SFML/Window/Keyboard.hpp>

class Player: public engine::SpriteNode {
protected:
    void* m_keyHandler;
    b2Vec2 m_toPosVel;
    float m_toPosTime;
    uint8_t m_slot;
    float m_jumping;
    sf::Keyboard::Key m_lastPressed;
    float m_lastPressedTimeout;
public:
    Player(engine::Scene* scene);
    ~Player();
    void GoTo();
    bool IsJumping() {
        return m_jumping > 0 && m_jumping < 0.45;
    };
    void Jump();
    virtual bool initialize(Json::Value& root);
    void ProcessKey(sf::Keyboard::Key key);
protected:
    virtual void OnUpdate(sf::Time interval);

};


#endif //LD34_PLAYER_HPP
