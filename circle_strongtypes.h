#pragma once

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

namespace StrongTypes
{
    template<typename T, typename Tag>
    class StrongType
    {
    public:
        constexpr StrongType() = default;
        explicit constexpr StrongType(const T& value) : m_Value{value} {}
        explicit constexpr StrongType(T&& value) : m_Value{std::move(value)} {}

        [[nodiscard]] constexpr T& Get() { return m_Value; }
        [[nodiscard]] constexpr const T& Get() const { return m_Value; }

        [[nodiscard]] constexpr bool operator==(const T& other) const { return m_Value == other; }
        [[nodiscard]] constexpr bool operator==(const StrongType<T, Tag>& other) const { return m_Value == other; }

    private:
        T m_Value{};
    };

    using Meter = StrongType<float_t, struct MeterTag>;
    constexpr Meter operator""_meter(const long double value)
    {
        return Meter{static_cast<float_t>(value)};
    }

    using X = StrongType<Meter, struct XTag>;
    using Y = StrongType<Meter, struct YTag>;

    class Vector2D
    {
    public:
        constexpr Vector2D() = default;
        explicit constexpr Vector2D(const X x, const Y y)
            : m_X{x.Get()}
            , m_Y{y.Get()}
        {
        }

        [[nodiscard]] constexpr bool operator==(const Vector2D& other) const = default;

        [[nodiscard]] constexpr Meter GetX() const { return m_X; }
        [[nodiscard]] constexpr Meter GetY() const { return m_Y; }

        constexpr Vector2D& SetX(const X x) { m_X = x.Get(); return *this; }
        constexpr Vector2D& SetY(const Y y) { m_Y = y.Get(); return *this; }

        constexpr Vector2D& Set(const X x) { m_X = x.Get(); return *this; }
        constexpr Vector2D& Set(const Y y) { m_Y = y.Get(); return *this; }

        [[nodiscard]] constexpr Vector2D Build() const { return Vector2D{*this}; }

    private:
        Meter m_X{0.0_meter};
        Meter m_Y{0.0_meter};
    };

    enum class Colour : uint32_t
    {
        White,
        Black
    };

    enum class MaterialId : uint32_t {};

    using Position = StrongType<Vector2D, struct PositionTag>;
    using Velocity = StrongType<Vector2D, struct VelocityTag>;

    using KG = StrongType<float_t, struct KGTag>;
    constexpr KG operator""_kg(const long double value)
    {
        return KG{static_cast<float_t>(value)};
    }

    using Weight = StrongType<KG, struct WeightTag>;
    using Radius = StrongType<Meter, struct RadiusTag>;

    class Circle
    {
    public:
        constexpr Circle() = default;

        template<typename... Args>
        explicit constexpr Circle(Args... args)
        {
            (Set(std::move(args)), ...);
        }

        constexpr Circle& Set(const Position& position) { m_Position = position.Get(); return *this; }
        constexpr Circle& Set(const Velocity& velocity) { m_Velocity = velocity.Get(); return *this; }
        constexpr Circle& Set(const Colour colour) { m_Colour = colour; return *this; }
        constexpr Circle& Set(const MaterialId material) { m_Material = material; return *this; }
        constexpr Circle& Set(const Weight weight) { m_Weight = weight.Get(); return *this; }
        constexpr Circle& Set(const Radius radius) { m_Radius = radius.Get(); return *this; }

        [[nodiscard]] constexpr Circle Build() const { return Circle{*this}; }

        [[nodiscard]] constexpr const Vector2D& GetPosition() const { return m_Position; }
        [[nodiscard]] constexpr const Vector2D& GetVelocity() const { return m_Velocity; }
        [[nodiscard]] constexpr Colour GetColour() const { return m_Colour; }
        [[nodiscard]] constexpr MaterialId GetMaterial() const { return m_Material; }
        [[nodiscard]] constexpr KG GetWeight() const { return m_Weight; }
        [[nodiscard]] constexpr Meter GetRadius() const { return m_Radius; }

    private:
        Vector2D m_Position{Vector2D{X{0.0_meter}, Y{0.0_meter}}};
        Vector2D m_Velocity{Vector2D{X{0.0_meter}, Y{0.0_meter}}};
        Colour m_Colour{Colour::White};
        MaterialId m_Material{0};
        KG m_Weight{0.0_kg};
        Meter m_Radius{0.0_meter};
    };

    using Circles = std::vector<Circle>;

    namespace
    {
        constexpr Position position{Vector2D{X{1.0_meter}, Y{2.0_meter}}};
        constexpr Velocity velocity{Vector2D{X{3.0_meter}, Y{4.0_meter}}};
        constexpr Colour colour{Colour::Black};
        constexpr MaterialId material{6};
        constexpr Weight weight{7.0_kg};
        constexpr Radius radius{8.0_meter};
        constexpr uint32_t creationCount{1'000'000};
    }

    TEST_CASE("StrongTypes - Unit Test - Constructor")
    {
        constexpr Circle circle{position, velocity, colour, material, weight, radius};

        REQUIRE(circle.GetPosition() == position.Get());
        REQUIRE(circle.GetVelocity() == velocity.Get());
        REQUIRE(circle.GetColour() == colour);
        REQUIRE(circle.GetMaterial() == material);
        REQUIRE(circle.GetWeight() == weight.Get());
        REQUIRE(circle.GetRadius() == radius.Get());
    }

    TEST_CASE("StrongTypes - Unit Test - Fluent Constructor")
    {
        constexpr Circle circle{
            Circle{}
                .Set(position)
                .Set(velocity)
                .Set(colour)
                .Set(material)
                .Set(weight)
                .Set(radius)
                .Build()};

        REQUIRE(circle.GetPosition() == position);
        REQUIRE(circle.GetVelocity() == velocity);
        REQUIRE(circle.GetColour() == colour);
        REQUIRE(circle.GetMaterial() == material);
        REQUIRE(circle.GetWeight() == weight);
        REQUIRE(circle.GetRadius() == radius);
    }

    TEST_CASE("StrongTypes - Benchmark - Constructor Push Back")
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

    TEST_CASE("StrongTypes - Benchmark - Constructor Emplace Back")
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

    TEST_CASE("StrongTypes - Benchmark - Fluent Constructor Push Back")
    {
        BENCHMARK("Benchmark")
        {
            Circles circles{};
            for(uint32_t i{0}; i != creationCount; ++i)
            {
                circles.push_back(
                    Circle{}
                        .Set(position)
                        .Set(velocity)
                        .Set(colour)
                        .Set(material)
                        .Set(weight)
                        .Set(radius)
                        .Build());
            }
        };
    }
}
