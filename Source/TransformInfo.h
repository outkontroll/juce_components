#pragma once

#include <variant>

struct Identity
{
};

struct Rotation
{
    float angle;
};

struct Scale
{
    float factorX;
    float factorY;
};

struct TransformInfo
{
    std::variant<Identity, Rotation, Scale> transformation = Identity{};
};
