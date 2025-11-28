#pragma once
#include <vector>
#include <string>
#include <cstdlib>

class UpgradeMenu
{
public:
    std::vector<int> options;

    void roll()
    {
        options.clear();
        while (options.size() < 3)
        {
            int r = (rand() % 3) + 1;
            bool exists = false;
            for (int o : options)
                if (o == r) exists = true;

            if (!exists) options.push_back(r);
        }
    }

    std::string getText(int opt)
    {
        if (opt == 1) return "Piercing Bolt";
        if (opt == 2) return "Triple Shot";
        if (opt == 3) return "Orbiting Blades";
        return "";
    }
};
