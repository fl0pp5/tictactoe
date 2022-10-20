#ifndef TYPES_H
#define TYPES_H

#include <array>

enum class CellType
{
    Empty, Cross, Zero
};

typedef std::array<CellType, 9> ttt_field_t;

#endif //TYPES_H
