#pragma once
#include <string>

enum class PassiveType
{
    REGEN,
    SPEED,
    DAMAGE,
    MAGNET,
    ARMOR
};

struct Passive
{
    PassiveType type;
    int level = 1;

    std::string getName() const
    {
        switch(type)
        {
            case PassiveType::REGEN: return "Regeneration";
            case PassiveType::SPEED: return "Speed";
            case PassiveType::DAMAGE: return "Damage";
            case PassiveType::MAGNET: return "Magnet";
            case PassiveType::ARMOR: return "Armor";
        }
        return "";
    }
};
