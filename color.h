#ifndef COLOR_H
#define COLOR_H

#include <string>

class Color{
public:
    float r, g, b, a;
    Color(float red, float green, float blue, float alpha = 1.0f)
        : r(red), g(green), b(blue), a(alpha) {}
};


inline Color hex2float(const std::string& hex, float alpha = 1.0f) {
        unsigned int hexValue = std::stoul(hex.substr(1), nullptr, 16);
        float red = ((hexValue >> 16) & 0xFF) / 255.0f;
        float green = ((hexValue >> 8) & 0xFF) / 255.0f;
        float blue = (hexValue & 0xFF) / 255.0f;
        return Color(red, green, blue, alpha);
}

// Common colors 
const Color COLOR_WHITE = hex2float("#FFFFFF");
const Color COLOR_BLACK = hex2float("#000000");
const Color COLOR_RED   = hex2float("#FF0000");
const Color COLOR_GREEN = hex2float("#00FF00");
const Color COLOR_BLUE  = hex2float("#0000FF");
const Color COLOR_YELLOW= hex2float("#FFFF00");
const Color COLOR_CYAN  = hex2float("#00FFFF");
const Color COLOR_MAGENTA = hex2float("#FF00FF");
const Color COLOR_GRAY = hex2float("#808080");
const Color COLOR_DARK_GRAY = hex2float("#404040");
const Color COLOR_LIGHT_GRAY = hex2float("#C0C0C0");
const Color COLOR_ORANGE = hex2float("#FFA500");
const Color COLOR_PURPLE = hex2float("#800080");
const Color COLOR_PINK = hex2float("#FFC0CB");
const Color COLOR_BROWN = hex2float("#A52A2A");

// Green variants
const Color COLOR_LIME_GREEN = hex2float("#32CD32");
const Color COLOR_FOREST_GREEN = hex2float("#228B22");
const Color COLOR_DARK_GREEN = hex2float("#006400");
const Color COLOR_SEA_GREEN = hex2float("#2E8B57");
const Color COLOR_MINT_GREEN = hex2float("#98FF98");
const Color COLOR_OLIVE_GREEN = hex2float("#556B2F");
const Color COLOR_EMERALD = hex2float("#50C878");
const Color COLOR_TEAL = hex2float("#008080");

// Blue variants
const Color COLOR_NAVY_BLUE = hex2float("#000080");
const Color COLOR_ROYAL_BLUE = hex2float("#4169E1");
const Color COLOR_SKY_BLUE = hex2float("#87CEEB");
const Color COLOR_LIGHT_BLUE = hex2float("#ADD8E6");
const Color COLOR_DEEP_BLUE = hex2float("#00008B");
const Color COLOR_STEEL_BLUE = hex2float("#4682B4");
const Color COLOR_CORNFLOWER_BLUE = hex2float("#6495ED");
const Color COLOR_DODGER_BLUE = hex2float("#1E90FF");

// Additional UI colors
const Color COLOR_INDIGO = hex2float("#4B0082");
const Color COLOR_VIOLET = hex2float("#8A2BE2");
const Color COLOR_MAROON = hex2float("#800000");
const Color COLOR_NAVY = hex2float("#000080");
const Color COLOR_BEIGE = hex2float("#F5F5DC");
const Color COLOR_IVORY = hex2float("#FFFFF0");
const Color COLOR_SILVER = hex2float("#C0C0C0");
const Color COLOR_GOLD = hex2float("#FFD700");


#endif // COLOR_H


