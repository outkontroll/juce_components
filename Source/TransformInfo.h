#pragma once

#include <optional>

struct Rotation
{
    float angle;
};

struct TransformInfo
{
    std::optional<Rotation> rotation;
};
