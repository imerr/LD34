//
// Created by iMer on 12.12.2015.
//

#ifndef LD34_LEVEL_HPP
#define LD34_LEVEL_HPP


#include <Engine/Scene.hpp>

class Level : public engine::Scene {
protected:
    float m_speed;
public:
    Level(engine::Game *game);

    ~Level();

    float GetSpeed() const {
        return m_speed;
    }

protected:
    virtual void OnUpdate(sf::Time interval);
};


#endif //LD34_LEVEL_HPP
