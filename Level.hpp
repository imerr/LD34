//
// Created by iMer on 12.12.2015.
//

#ifndef LD34_LEVEL_HPP
#define LD34_LEVEL_HPP


#include <Engine/Scene.hpp>

class Level : public engine::Scene {
protected:
    float m_speed;
    std::vector<std::string> m_objects;
    std::vector<std::string> m_objectIcons;
    uint32_t m_searching;
    int m_score;
    int m_combo;
public:
    Level(engine::Game* game);

    ~Level();

    float GetSpeed() const {
        return m_speed;
    }

    virtual bool initialize(Json::Value& root);

    std::string GetSearching() {
        return m_objects[m_searching];
    }
    void SetSearching();
    void AddPoint(int point);

protected:
    virtual void OnUpdate(sf::Time interval);
};


#endif //LD34_LEVEL_HPP
