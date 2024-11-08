#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cmath>

#include "utils/math.h"
#include "utils/view_ptr.h"

// TODO: Custom main that can run multiple unit tests eventually ?

TEST_CASE("view_ptr", "[utils]")
{
    SECTION("Init")
    {
        {
            std::unique_ptr<int> test(new int(5));
            {
                utils::view_ptr view = test;
                REQUIRE(*view == *test);
            }
            REQUIRE(*test == 5);
        }
        {
            std::shared_ptr<int> test(new int(5));
            {
                utils::view_ptr view = test;
                REQUIRE(*view == *test);
                {
                    std::shared_ptr<int> test2(test);
                    REQUIRE(*view == *test2);
                }
            }
            REQUIRE(*test == 5);
        }
    }

    SECTION("Type constraints")
    {
        std::unique_ptr<int> unique(new int(5));
        std::shared_ptr<int> shared(new int(5));
        REQUIRE(utils::SmartPointer<std::decay_t<decltype(unique)>> == true);
        REQUIRE(utils::SmartPointer<std::decay_t<decltype(shared)>> == true);
        REQUIRE(utils::SmartPointer<decltype(unique.get())> == false);
        REQUIRE(utils::SmartPointer<decltype(shared.get())> == false);
    }

    SECTION("Comparison")
    {
        {
            std::unique_ptr<int> test(new int(5));
            utils::view_ptr view = test;

            REQUIRE(view == test);
        }
        {
            std::shared_ptr<int> test(new int(5));
            utils::view_ptr view = test;
            REQUIRE(view == test);
            {
                std::shared_ptr<int> test2(test);
                utils::view_ptr view = test2;
                REQUIRE(view == test2);
            }
        }
    }
}

TEST_CASE("math", "[utils]")
{
    SECTION("power")
    {
        SECTION("Zeros")
        {
            REQUIRE(utils::pow<0>(0) == std::pow(0, 0));
            REQUIRE(utils::pow<1>(0) == std::pow(0, 1));
            REQUIRE(utils::pow<2>(0) == std::pow(0, 2));
            REQUIRE(utils::pow<3>(0) == std::pow(0, 3));
            REQUIRE(utils::pow<4>(0) == std::pow(0, 4));
            REQUIRE(utils::pow<5>(0) == std::pow(0, 5));
            REQUIRE(utils::pow<6>(0) == std::pow(0, 6));
            REQUIRE(utils::pow<7>(0) == std::pow(0, 7));
            REQUIRE(utils::pow<8>(0) == std::pow(0, 8));
            REQUIRE(utils::pow<9>(0) == std::pow(0, 9));
            REQUIRE(utils::pow<10>(0) == std::pow(0, 10));
        }

        SECTION("Ones")
        {
            REQUIRE(utils::pow<0>(1) == std::pow(1, 0));
            REQUIRE(utils::pow<1>(1) == std::pow(1, 1));
            REQUIRE(utils::pow<2>(1) == std::pow(1, 2));
            REQUIRE(utils::pow<3>(1) == std::pow(1, 3));
            REQUIRE(utils::pow<4>(1) == std::pow(1, 4));
            REQUIRE(utils::pow<5>(1) == std::pow(1, 5));
            REQUIRE(utils::pow<6>(1) == std::pow(1, 6));
            REQUIRE(utils::pow<7>(1) == std::pow(1, 7));
            REQUIRE(utils::pow<8>(1) == std::pow(1, 8));
            REQUIRE(utils::pow<9>(1) == std::pow(1, 9));
            REQUIRE(utils::pow<10>(1) == std::pow(1, 10));
        }

        SECTION("of two")
        {
            REQUIRE(utils::pow<0>(2) == std::pow(2, 0));
            REQUIRE(utils::pow<1>(2) == std::pow(2, 1));
            REQUIRE(utils::pow<2>(2) == std::pow(2, 2));
            REQUIRE(utils::pow<3>(2) == std::pow(2, 3));
            REQUIRE(utils::pow<4>(2) == std::pow(2, 4));
            REQUIRE(utils::pow<5>(2) == std::pow(2, 5));
            REQUIRE(utils::pow<6>(2) == std::pow(2, 6));
            REQUIRE(utils::pow<7>(2) == std::pow(2, 7));
            REQUIRE(utils::pow<8>(2) == std::pow(2, 8));
            REQUIRE(utils::pow<9>(2) == std::pow(2, 9));
            REQUIRE(utils::pow<10>(2) == std::pow(2, 10));
        }

        SECTION("randoms")
        {
            REQUIRE(utils::pow<2>(31l) == std::pow(31, 2));
            REQUIRE(utils::pow<4>(231l) == std::pow(231, 4));
            REQUIRE(utils::pow<21>(1l) == std::pow(1, 21));
        }
    }

    SECTION("Benchmarking")
    {
        SECTION("std::pow")
        {
            BENCHMARK("pow(2, 32)")
            {
                return std::pow(2, 32);
            };

            BENCHMARK("pow(x, 0)")
            {
                return std::pow(23902l, 0);
            };

            BENCHMARK("pow(32, 1)")
            {
                return std::pow(32l, 1);
            };

            BENCHMARK("pow(16, 16)")
            {
                return std::pow(16, 16);
            };
        }

        SECTION("utils::pow")
        {
            BENCHMARK("pow(2, 32)")
            {
                return utils::pow<32>(2l);
            };

            BENCHMARK("pow(23902, 0)")
            {
                return utils::pow<0>(23902l);
            };

            BENCHMARK("pow(32, 1)")
            {
                return utils::pow<1>(32l);
            };

            BENCHMARK("pow(16, 16)")
            {
                return utils::pow<16>(16l);
            };
        }
    }
}
