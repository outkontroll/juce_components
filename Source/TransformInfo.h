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

struct Translation
{
    float offsetX;
    float offsetY;
};

struct TransformInfo
{
    std::variant<Identity, Rotation, Scale, Translation> transformation = Identity{};
};
