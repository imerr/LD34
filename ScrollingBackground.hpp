#ifndef LD34_SCROLLINGBACKGROUND_HPP
#define LD34_SCROLLINGBACKGROUND_HPP
#include <Engine/SpriteNode.hpp>

class ScrollingBackground: public engine::SpriteNode {
public:
    ScrollingBackground(engine::Scene* scene);
    ~ScrollingBackground();

protected:
    virtual void OnUpdate(sf::Time interval);
};


#endif //LD34_SCROLLINGBACKGROUND_HPP
