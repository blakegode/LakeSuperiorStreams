#include <catch2/catch_test_macros.hpp>

#include "lib/DataBase/DataManager.h"

TEST_CASE("Search By Time"){
    Datum a,b,c,d,e,f,g = Datum("t_field","t_dataset",std::chrono::system_clock::time_point(),0);
    auto t_present = std::chrono::system_clock::time_point();
    auto t_past4 = t_present - std::chrono::days(4);
    auto t_past3 = t_present - std::chrono::days(3);
    auto t_past2 = t_present - std::chrono::days(2);
    auto t_past1 = t_present - std::chrono::days(1);
    auto t_fut1 = t_present + std::chrono::days(1);
    auto t_fut2 = t_present + std::chrono::days(2);
    auto t_fut3 = t_present + std::chrono::days(3);
    auto t_fut4 = t_present+ std::chrono::days(4);


    a.setTimestamp(t_past3);
    b.setTimestamp(t_past2);
    c.setTimestamp(t_past1);
    d.setTimestamp(t_present);
    e.setTimestamp(t_fut1);
    f.setTimestamp(t_fut2);
    g.setTimestamp(t_fut3);

    std::vector<Datum> test;
    TimeSeries::insert(test,a);
    TimeSeries::insert(test,g);
    TimeSeries::insert(test,b);
    TimeSeries::insert(test,f);
    TimeSeries::insert(test,c);
    TimeSeries::insert(test,e);
    TimeSeries::insert(test,d);


    CHECK(TimeSeries::findIndex(test,t_past3) == 0);
    CHECK(TimeSeries::findIndex(test,t_past4,TimeSeries::SearchType::GE) == 0);
    CHECK(TimeSeries::findIndex(test,t_fut4,TimeSeries::SearchType::LE) == (test.size()-1));
}

