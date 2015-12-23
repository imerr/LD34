//
// Created by iMer on 12.12.2015.
//

#include "Level.hpp"
#include <Engine/util/Random.hpp>
#include <iostream>
#include <cstdlib>
#include <Engine/Factory.hpp>
#include <Engine/util/Event.hpp>
#include <sstream>
#include <Engine/Text.hpp>
#include <Engine/util/misc.hpp>

Level::Level(engine::Game* game) : Scene(game), m_speed(1), m_searching(0), m_score(0), m_combo(0) {

}

Level::~Level() {

}

void Level::OnUpdate(sf::Time interval) {
    engine::Scene::OnUpdate(interval);
    if (m_speed < 5) {
        m_speed += 0.2 * interval.asSeconds();
    } else if (m_speed < 50) {
        m_speed += 0.1 * interval.asSeconds();
    }

    engine::util::RandomFloat<> r(0, 1);
    if (r() < 0.004 * sqrtf(m_speed)) {
        engine::util::RandomInt<> slot(1, 3);
        engine::util::RandomInt<> obj(0, m_objects.size() - 1);

        float pos = (slot() * m_scene->GetSize().x / 4);
        engine::Node* n = engine::Factory::CreateChildFromFile(m_objects[obj()], this);
        // Check if it's even fair to spawn a thing here
        auto size = n->GetSize();
        bool found = false;
        auto aabbc = engine::MakeAABBQueryCallback([&, this](void*){
            found = true;
            return false;
        });
        b2AABB aabb;
        aabb.lowerBound = b2Vec2(pos - 128, -size.y*2.5f) * (1.0/GetPixelMeterRatio());
        aabb.upperBound = b2Vec2(pos + 128, -size.y*1.5f + 50) * (1.0/GetPixelMeterRatio());
        m_world->QueryAABB(&aabbc, aabb);
        if (found) {
            n->Delete();
        } else {
            n->SetPosition(pos, -n->GetSize().y*2);
        }
    }
    if (r() < 0.0005) {
        SetSearching();
    }
    engine::Text* change = static_cast<engine::Text*>(m_ui->GetChildByID("change"));
    sf::Color c = change->GetColor();
    c.r = static_cast<uint8_t>(std::min<uint16_t>(1 + c.r * 1.04f, 255));
    c.g = static_cast<uint8_t>(std::min<uint16_t>(1 + c.g * 1.04f, 255));
    c.b = static_cast<uint8_t>(std::min<uint16_t>(1 + c.b * 1.04f, 255));
    change->SetColor(c);
}

bool Level::initialize(Json::Value& root) {
    if (!engine::Scene::initialize(root)) {
        return false;
    }
    for (auto& node : root["objects"]) {
        m_objects.push_back(node.asString());
    }
    for (auto& node : root["objectIcons"]) {
        m_objectIcons.push_back(node.asString());
    }
    SetSearching();
    return true;
}

void Level::SetSearching() {
    engine::util::RandomInt<uint32_t> obj(0, m_objects.size() - 1);
    m_searching = obj();
    auto sn = m_ui->GetChildByID("searching");
    for (auto c : sn->GetChildren()) {
        c->Delete();
    }
    auto n = engine::Factory::CreateChildFromFile(m_objectIcons[m_searching], sn);
    n->SetPosition(sn->GetSize().x/2, sn->GetSize().y/2);
}

void Level::AddPoint(int point) {
    if (point > 0) {
        m_combo += 1;
        m_score += point * m_combo;
    } else {
        m_score += point * (m_combo ? m_combo : 1);
        m_combo = 0;
    }
    engine::Text* score = static_cast<engine::Text*>(m_ui->GetChildByID("score"));
    engine::Text* change = static_cast<engine::Text*>(m_ui->GetChildByID("change"));
    std::ostringstream ss;
    ss << m_score;
    score->SetText(ss.str());
    ss.str("");
    ss.clear();
    if (point >= 0) {
        ss << "x" << m_combo << " ";
        ss << "+";
        ss << point * m_combo;
        change->SetColor(sf::Color::Green);
    } else {
        ss << point;
        change->SetColor(sf::Color::Red);
        m_combo = 0;
    }
    change->SetText(ss.str());
}
