#include <catch2/catch_test_macros.hpp>
#include "lib/DataBase/DataBase.h"
#include <algorithm>


bool compareDatumTime (const Datum& a, const Datum& b){
    return (a.getTimeStamp() < b.getTimeStamp());
}

TEST_CASE("TimeSeries::insert","[TimeSeries]") {
    SECTION("Sorted insert into empty vector"){
        std::vector<Datum> data;
        TimeSeries::insert(data, Datum(TimeStamp{} + std::chrono::hours(1)));
        SECTION("Vector size is incremented post-insert") REQUIRE(data.size() == 1);
        SECTION("Element at vector[0] has correct TimeStamp") REQUIRE(data[0].getTimeStamp() == TimeStamp{} + std::chrono::hours(1));
    }
    SECTION("Sorted insert into vector with only one element"){
        std::vector<Datum> data = { Datum(TimeStamp{}) };
        TimeSeries::insert(data, Datum(TimeStamp{} + std::chrono::hours(1)));
        SECTION("Vector size is incremented post-insert") REQUIRE(data.size() == 2);
        SECTION("Vector is sorted by TimeStamp") REQUIRE(std::is_sorted(data.begin(), data.end(), compareDatumTime));
    }
    SECTION("Sorted insert between existing elements") {
        std::vector<Datum> data = { Datum(TimeStamp{}), Datum(TimeStamp{} + std::chrono::hours(2)) };
        TimeSeries::insert(data, Datum(TimeStamp{} + std::chrono::hours(1)));
        SECTION("Vector size is incremented post-insert") REQUIRE(data.size() == 3);
        SECTION("Vector is sorted by TimeStamp") REQUIRE(std::is_sorted(data.begin(), data.end(), compareDatumTime));
    }
    SECTION("Sorted insert - duplicate timestamps") {
        std::vector<Datum> data = { Datum(TimeStamp{}), Datum(TimeStamp{} + std::chrono::hours(1)) };
        TimeSeries::insert(data, Datum(TimeStamp{} + std::chrono::hours(1)));
        SECTION("Vector size is incremented post-insert") REQUIRE(data.size() == 3);
        SECTION("Vector is sorted by TimeStamp") REQUIRE(std::is_sorted(data.begin(), data.end(), compareDatumTime));
    }

}


TEST_CASE("TimeSeries::findIndex", "[TimeSeries]") {
    std::vector<Datum> data = {
            Datum(TimeStamp{}),
            Datum(TimeStamp{} + std::chrono::hours(1)),
            Datum(TimeStamp{} + std::chrono::hours(2)),
            Datum(TimeStamp{} + std::chrono::hours(3))
    };
    SECTION("SearchType::EQ") {
        SECTION("Finds index in vector") {
            int idx = TimeSeries::findIndex(data, TimeStamp{} + std::chrono::hours(1), TimeSeries::SearchType::EQ);
            REQUIRE(idx == 1);
        }
        SECTION("Returns -1 when TimeStamp not found") {
            int idx = TimeSeries::findIndex(data, TimeStamp{} + std::chrono::hours(4), TimeSeries::SearchType::EQ);
            REQUIRE(idx == -1);
        }
    }
    SECTION("SearchType::GE") {
        SECTION("Finds index in vector") {
            int idx = TimeSeries::findIndex(data, TimeStamp{} + std::chrono::hours(1), TimeSeries::SearchType::GE);
            REQUIRE(idx == 1);
        }
        SECTION("Finds nearest equal-or-greater index when TimeStamp not found") {
            int idx = TimeSeries::findIndex(data, TimeStamp{} - std::chrono::hours(1), TimeSeries::SearchType::GE);
            REQUIRE(idx == 0);
        }
    }
    SECTION("SearchType::LE") {
        SECTION("Finds index in vector") {
            int idx = TimeSeries::findIndex(data, TimeStamp{} + std::chrono::hours(2), TimeSeries::SearchType::LE);
            REQUIRE(idx == 2);
        }
        SECTION("Finds nearest less-or-equal index when TimeStamp not found") {
            int idx = TimeSeries::findIndex(data, TimeStamp{} + std::chrono::hours(4), TimeSeries::SearchType::LE);
            REQUIRE(idx == 3);
        }
    }
    SECTION("SearchType::NE") {
        SECTION("Finds nearest index not equal to TimeStamp") {
            int idx = TimeSeries::findIndex(data, TimeStamp{} + std::chrono::minutes(45), TimeSeries::SearchType::NE);
            REQUIRE(idx == 1);
        }
    }
}