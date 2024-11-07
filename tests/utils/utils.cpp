#include <catch2/catch_test_macros.hpp>

#include "utils/view_ptr.h"

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
