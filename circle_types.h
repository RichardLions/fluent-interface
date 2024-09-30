#pragma once

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

namespace Types
{
    class Vector2D
    {
    public:
        constexpr Vector2D() = default;
        explicit constexpr Vector2D(const float_t x, const float_t y)
            : m_X{x}
            , m_Y{y}
        {
        }

        [[nodiscard]] constexpr bool operator==(const Vector2D&) const = default;

        [[nodiscard]] constexpr float_t GetX() const { return m_X; }
        [[nodiscard]] constexpr float_t GetY() const { return m_Y; }

        constexpr Vector2D& SetX(const float_t x) { m_X = x; return *this; }
        constexpr Vector2D& SetY(const float_t y) { m_Y = y; return *this; }
        [[nodiscard]] constexpr Vector2D Build() const { return Vector2D{*this}; }

    private:
        float_t m_X{0.0f};
        float_t m_Y{0.0f};
    };

    enum class Colour : uint32_t
    {
        White,
        Black
    };

    enum class MaterialId : uint32_t {};

    class Circle
    {
    public:
        constexpr Circle() = default;

        explicit constexpr Circle(
            const Vector2D& position,
            const Vector2D& velocity,
            const Colour colour,
            const MaterialId material,
            const float_t weight,
            const float_t radius)
            : m_Position{position}
            , m_Velocity{velocity}
            , m_Colour{colour}
            , m_Material{material}
            , m_Weight{weight}
            , m_Radius{radius}
        {
        }

        constexpr Circle& SetPosition(const Vector2D& position) { m_Position = position; return *this; }
        constexpr Circle& SetVelocity(const Vector2D& velocity) { m_Velocity = velocity; return *this; }
        constexpr Circle& SetColour(const Colour colour) { m_Colour = colour; return *this; }
        constexpr Circle& SetMaterial(const MaterialId material) { m_Material = material; return *this; }
        constexpr Circle& SetWeight(const float_t weight) { m_Weight = weight; return *this; }
        constexpr Circle& SetRadius(const float_t radius) { m_Radius = radius; return *this; }

        [[nodiscard]] constexpr Circle Build() const { return Circle{*this}; }

        [[nodiscard]] constexpr const Vector2D& GetPosition() const { return m_Position; }
        [[nodiscard]] constexpr const Vector2D& GetVelocity() const { return m_Velocity; }
        [[nodiscard]] constexpr Colour GetColour() const { return m_Colour; }
        [[nodiscard]] constexpr MaterialId GetMaterial() const { return m_Material; }
        [[nodiscard]] constexpr float_t GetWeight() const { return m_Weight; }
        [[nodiscard]] constexpr float_t GetRadius() const { return m_Radius; }

    private:
        Vector2D m_Position{};
        Vector2D m_Velocity{};
        Colour m_Colour{Colour::White};
        MaterialId m_Material{0};
        float_t m_Weight{0.0f};
        float_t m_Radius{0.0f};
    };

    using Circles = std::vector<Circle>;

    namespace
    {
        constexpr Vector2D position{1.0f, 2.0f};
        constexpr Vector2D velocity{3.0f, 4.0f};
        constexpr Colour colour{Colour::Black};
        constexpr MaterialId material{6};
        constexpr float_t weight{7.0f};
        constexpr float_t radius{8.0f};
        constexpr uint32_t creationCount{1'000'000};
    }

    TEST_CASE("Types - Unit Test - Constructor")
    {
        constexpr Circle circle{position, velocity, colour, material, weight, radius};

        REQUIRE(circle.GetPosition() == position);
        REQUIRE(circle.GetVelocity() == velocity);
        REQUIRE(circle.GetColour() == colour);
        REQUIRE(circle.GetMaterial() == material);
        REQUIRE(circle.GetWeight() == weight);
        REQUIRE(circle.GetRadius() == radius);
    }

    TEST_CASE("Types - Unit Test - Fluent Constructor")
    {
        constexpr Circle circle{
            Circle{}
                .SetPosition(position)
                .SetVelocity(velocity)
                .SetColour(colour)
                .SetMaterial(material)
                .SetWeight(weight)
                .SetRadius(radius)
                .Build()};

        REQUIRE(circle.GetPosition() == position);
        REQUIRE(circle.GetVelocity() == velocity);
        REQUIRE(circle.GetColour() == colour);
        REQUIRE(circle.GetMaterial() == material);
        REQUIRE(circle.GetWeight() == weight);
        REQUIRE(circle.GetRadius() == radius);
    }

    TEST_CASE("Types - Benchmark - Constructor Push Back")
    {
        BENCHMARK("Benchmark")
        {
            Circles circles{};
            for(uint32_t i{0}; i != creationCount; ++i)
            {
                circles.push_back(Circle{position, velocity, colour, material, weight, radius});
            }
        };
    }

    TEST_CASE("Types - Benchmark - Constructor Emplace Back")
    {
        BENCHMARK("Benchmark")
        {
            Circles circles{};
            for(uint32_t i{0}; i != creationCount; ++i)
            {
                circles.emplace_back(position, velocity, colour, material, weight, radius);
            }
        };
    }

    TEST_CASE("Types - Benchmark - Fluent Constructor Push Back")
    {
        BENCHMARK("Benchmark")
        {
            Circles circles{};
            for(uint32_t i{0}; i != creationCount; ++i)
            {
                circles.push_back(
                    Circle{}
                        .SetPosition(position)
                        .SetVelocity(velocity)
                        .SetColour(colour)
                        .SetMaterial(material)
                        .SetWeight(weight)
                        .SetRadius(radius)
                        .Build());
            }
        };
    }
}
