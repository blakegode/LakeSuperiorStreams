#include <catch2/catch_test_macros.hpp>

#include "lib/DataBase/DataManager.h"

#include <algorithm>

bool compareTimestamp (const Datum& a, const Datum& b){
    return a.getTimeStamp() < b.getTimeStamp();
};

TEST_CASE("Time Sorted Insert Two"){
    std::string subject{"t_subject"},field{"t_field"};
    auto a = Datum(field,"t_dataset",std::chrono::system_clock::time_point(),0);
    Datum b,c,d,e,f,g = Datum(a);
    a.setTimestamp(std::chrono::system_clock::time_point() - std::chrono::days(3));
    b.setTimestamp(std::chrono::system_clock::time_point() - std::chrono::days(2));
    c.setTimestamp(std::chrono::system_clock::time_point() - std::chrono::days(1));
    e.setTimestamp(std::chrono::system_clock::time_point() + std::chrono::days(1));
    f.setTimestamp(std::chrono::system_clock::time_point() + std::chrono::days(2));
    g.setTimestamp(std::chrono::system_clock::time_point() + std::chrono::days(3));

    auto test = std::vector<Datum>{};
    TimeSeries::insert(test,a);
    TimeSeries::insert(test,g);
    TimeSeries::insert(test,b);
    TimeSeries::insert(test,f);
    TimeSeries::insert(test,c);
    TimeSeries::insert(test,e);
    TimeSeries::insert(test,d);

    CHECK(std::is_sorted(test.begin(),test.end(),compareTimestamp));
}
