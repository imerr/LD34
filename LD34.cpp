//
// Created by iMer on 12.12.2015.
//

#include <Engine/Factory.hpp>
#include "LD34.hpp"
#include "Level.hpp"

LD34::LD34(): Game(512, 576)
{
    m_scene = engine::Factory::create<Level>("assets/scripts/level.json", this);
    m_windowTitle = "Runman - LD34 -";
    m_window.setSize(sf::Vector2u(512, 576));
    m_window.setKeyRepeatEnabled(false);
}

LD34::~LD34()
{

}
