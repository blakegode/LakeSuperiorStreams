#include <catch2/catch_test_macros.hpp>
#include "lib/DataBase/DataBase.h"

TEST_CASE("DataSet::getData"){
    DataSet test = DataSet::create("test")
            .insert(std::make_pair<std::string,std::vector<Datum>>("foo",{Datum()}))
            .insert(std::make_pair<std::string,std::vector<Datum>>("bar",{Datum(),Datum()}));
    SECTION("Successfully retrieves vector of Datum objects") REQUIRE((test.getData("foo").size() == 1 && test.getData("bar").size() == 2));
}

TEST_CASE("DataSet::getDatum"){
    auto t1 = TimeStamp{},
        t2 = t1 + std::chrono::hours(1),
        t3 = t1 + std::chrono::hours(2),
        t4 = t1 + std::chrono::hours(3);
    DataSet test = DataSet::create("test")
            .insert(std::make_pair<std::string,std::vector<Datum>>("precipitation",std::vector<Datum>{
                    {Datum("test", "precipitation", t1, 1)},
                    {Datum("test", "precipitation", t2, 2)},
                    {Datum("test", "precipitation", t3, 3)},
                    {Datum("test", "precipitation", t4, 4)}
            }));
    SECTION("SearchType::EQ"){
        SECTION("Returns correct Datum when TimeStamp == target found") {
            Datum result = test.getDatum("precipitation",TimeStamp{}+std::chrono::hours(1));
            REQUIRE(result.getVal() == 2);
        }
        SECTION("Returns vacuous Datum when TimeStamp not found"){
            Datum result = test.getDatum("precipitation",TimeStamp{}+std::chrono::hours(4));
            REQUIRE(result.getVal() == 0);
        }
    }
    SECTION("SearchType::GE"){
        SECTION("Returns correct Datum when TimeStamp == target found") {
            Datum result = test.getDatum("precipitation",TimeStamp{}+std::chrono::hours(1));
            REQUIRE(result.getVal() == 2);
        }
        SECTION("Returns correct Datum when TimeStamp > target found") {
            Datum result = test.getDatum("precipitation",TimeStamp{}+std::chrono::minutes(1),TimeSeries::SearchType::GE);
            REQUIRE(result.getVal() == 2);
        }
        SECTION("Returns vacuous Datum when no TimeStamp >= target found"){
            Datum result = test.getDatum("precipitation",TimeStamp{}+std::chrono::hours(4),TimeSeries::SearchType::GE);
            REQUIRE(result.getVal() == 0);
        }
    }
    SECTION("SearchType::LE"){
        SECTION("Returns correct Datum when TimeStamp == target found") {
            Datum result = test.getDatum("precipitation",TimeStamp{}+std::chrono::hours(1));
            REQUIRE(result.getVal() == 2);
        }
        SECTION("Returns correct Datum when TimeStamp < target found") {
            Datum result = test.getDatum("precipitation",TimeStamp{}+std::chrono::minutes(1),TimeSeries::SearchType::LE);
            REQUIRE(result.getVal() == 1);
        }
        SECTION("Returns vacuous Datum when no TimeStamp <= target found"){
            Datum result = test.getDatum("precipitation",TimeStamp{}-std::chrono::hours(1),TimeSeries::SearchType::LE);
            REQUIRE(result.getVal() == 0);
        }
    }
    SECTION("SearchType::NE"){
        SECTION("Returns correct Datum when TimeStamp == target found") {
            Datum result = test.getDatum("precipitation",TimeStamp{}+std::chrono::hours(1));
            REQUIRE(result.getVal() == 2);
        }
        SECTION("Returns Datum with most proximal Timestamp to target") {
            Datum resultA = test.getDatum("precipitation",TimeStamp{}+std::chrono::minutes(1),TimeSeries::SearchType::NE);
            Datum resultB = test.getDatum("precipitation",TimeStamp{}-std::chrono::minutes(1),TimeSeries::SearchType::NE);
            REQUIRE((resultA.getVal() == 1 && resultB.getVal() == 1));
        }
    }
}