#pragma once

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

namespace Literals
{
    class Circle
    {
    public:
        constexpr Circle() = default;

        explicit constexpr Circle(
            const float_t positionX,
            const float_t positionY,
            const float_t velocityX,
            const float_t velocityY,
            const uint32_t colour,
            const uint32_t material,
            const float_t weight,
            const float_t radius)
            : m_PositionX{positionX}
            , m_PositionY{positionY}
            , m_VelocityX{velocityX}
            , m_VelocityY{velocityY}
            , m_Colour{colour}
            , m_Material{material}
            , m_Weight{weight}
            , m_Radius{radius}
        {
        }

        constexpr Circle& SetPositionX(const float_t positionX) { m_PositionX = positionX; return *this; }
        constexpr Circle& SetPositionY(const float_t positionY) { m_PositionY = positionY; return *this; }
        constexpr Circle& SetVelocityX(const float_t velocityX) { m_VelocityX = velocityX; return *this; }
        constexpr Circle& SetVelocityY(const float_t velocityY) { m_VelocityY = velocityY; return *this; }
        constexpr Circle& SetColour(const uint32_t colour) { m_Colour = colour; return *this; }
        constexpr Circle& SetMaterial(const uint32_t material) { m_Material = material; return *this; }
        constexpr Circle& SetWeight(const float_t weight) { m_Weight = weight; return *this; }
        constexpr Circle& SetRadius(const float_t radius) { m_Radius = radius; return *this; }

        [[nodiscard]] constexpr Circle Build() const { return Circle{*this}; }

        [[nodiscard]] constexpr float_t GetPositionX() const { return m_PositionX; }
        [[nodiscard]] constexpr float_t GetPositionY() const { return m_PositionY; }
        [[nodiscard]] constexpr float_t GetVelocityX() const { return m_VelocityX; }
        [[nodiscard]] constexpr float_t GetVelocityY() const { return m_VelocityY; }
        [[nodiscard]] constexpr uint32_t GetColour() const { return m_Colour; }
        [[nodiscard]] constexpr uint32_t GetMaterial() const { return m_Material; }
        [[nodiscard]] constexpr float_t GetWeight() const { return m_Weight; }
        [[nodiscard]] constexpr float_t GetRadius() const { return m_Radius; }

    private:
        float_t m_PositionX{0.0f};
        float_t m_PositionY{0.0f};
        float_t m_VelocityX{0.0f};
        float_t m_VelocityY{0.0f};
        uint32_t m_Colour{0};
        uint32_t m_Material{0};
        float_t m_Weight{0.0f};
        float_t m_Radius{0.0f};
    };

    using Circles = std::vector<Circle>;

    namespace
    {
        constexpr float_t positionX{1.0f};
        constexpr float_t positionY{2.0f};
        constexpr float_t velocityX{3.0f};
        constexpr float_t velocityY{4.0f};
        constexpr uint32_t colour{5};
        constexpr uint32_t material{6};
        constexpr float_t weight{7.0f};
        constexpr float_t radius{8.0f};
        constexpr uint32_t creationCount{1'000'000};
    }

    TEST_CASE("Literals - Unit Test - Constructor")
    {
        constexpr Circle circle{positionX, positionY, velocityX, velocityY, colour, material, weight, radius};

        REQUIRE(circle.GetPositionX() == positionX);
        REQUIRE(circle.GetPositionY() == positionY);
        REQUIRE(circle.GetVelocityX() == velocityX);
        REQUIRE(circle.GetVelocityY() == velocityY);
        REQUIRE(circle.GetColour() == colour);
        REQUIRE(circle.GetMaterial() == material);
        REQUIRE(circle.GetWeight() == weight);
        REQUIRE(circle.GetRadius() == radius);
    }

    TEST_CASE("Literals - Unit Test - Fluent Constructor")
    {
        constexpr Circle circle{
            Circle{}
                .SetPositionX(positionX)
                .SetPositionY(positionY)
                .SetVelocityX(velocityX)
                .SetVelocityY(velocityY)
                .SetColour(colour)
                .SetMaterial(material)
                .SetWeight(weight)
                .SetRadius(radius)
                .Build()};

        REQUIRE(circle.GetPositionX() == positionX);
        REQUIRE(circle.GetPositionY() == positionY);
        REQUIRE(circle.GetVelocityX() == velocityX);
        REQUIRE(circle.GetVelocityY() == velocityY);
        REQUIRE(circle.GetColour() == colour);
        REQUIRE(circle.GetMaterial() == material);
        REQUIRE(circle.GetWeight() == weight);
        REQUIRE(circle.GetRadius() == radius);
    }

    TEST_CASE("Literals - Benchmark - Constructor Push Back")
    {
        BENCHMARK("Benchmark")
        {
            Circles circles{};
            for(uint32_t i{0}; i != creationCount; ++i)
            {
                circles.push_back(Circle{positionX, positionY, velocityX, velocityY, colour, material, weight, radius});
            }
        };
    }

    TEST_CASE("Literals - Benchmark - Constructor Emplace Back")
    {
        BENCHMARK("Benchmark")
        {
            Circles circles{};
            for(uint32_t i{0}; i != creationCount; ++i)
            {
                circles.emplace_back(positionX, positionY, velocityX, velocityY, colour, material, weight, radius);
            }
        };
    }

    TEST_CASE("Literals - Benchmark - Fluent Constructor Push Back")
    {
        BENCHMARK("Benchmark")
        {
            Circles circles{};
            for(uint32_t i{0}; i != creationCount; ++i)
            {
                circles.push_back(
                    Circle{}
                        .SetPositionX(positionX)
                        .SetPositionY(positionY)
                        .SetVelocityX(velocityX)
                        .SetVelocityY(velocityY)
                        .SetColour(colour)
                        .SetMaterial(material)
                        .SetWeight(weight)
                        .SetRadius(radius)
                        .Build());
            }
        };
    }
}
