#include <catch2/catch_test_macros.hpp>
#include <ctime>
#include "lib/DataBase/CSVProcessor.cpp"
TEST_CASE( "Constructor works" ){
    CSVProcessor processor;
}

TEST_CASE( "Returns correct time" ){
    CSVProcessor processor;
    std::string time = "05/06/2020 11:30:00";

    auto timeStamp = processor.getTime(time);
    time_t tt = std::chrono::system_clock::to_time_t(timeStamp);
    tm *thing = localtime(&tt);
    const int monthsSinceJanuary = 5 - 1;
    const int yearsSince1900 = 2020 - 1900;

    CHECK(thing->tm_mon == monthsSinceJanuary);
    CHECK(thing->tm_mday == 06);
    CHECK(thing->tm_year == yearsSince1900);
    CHECK(thing->tm_hour == 11);
    CHECK(thing->tm_min == 30);
    CHECK(thing->tm_sec == 00);
}
