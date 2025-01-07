#pragma once

#include <tuple>
//C++17引入optional
#include <optional>
//variant容器，更安全的union
#include <variant>

struct Test
{
    int value;
    std::string name;
};

std::tuple<bool, float>mysqrt_01(float x);

std::optional<float> mysqrt_02(float x);

void check_tuple();

void check_optional();

void print_01(std::variant<int, float>const& value);

void print_02(std::variant<int, float>const& value);

void print_03(std::variant<int, float>const& value01,
    std::variant<int, float>const& value02);

void check_variant();