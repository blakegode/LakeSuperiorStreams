#include <catch2/catch_test_macros.hpp>
#include "lib/DataBase/DataBase.h"

TEST_CASE("DataSet Construction"){
    auto testBuilder = DataSet::create("test");
    SECTION("DataSet::create") SECTION("Successfully instantiates builder") REQUIRE(testBuilder.getTitle() == "test");
    SECTION("DataSetBuilder::insert"){
        SECTION("Successfully inserts data into dataset"){
            testBuilder.insert(std::make_pair<std::string,std::vector<Datum>>("foo",{Datum()}));
            REQUIRE(!testBuilder.getDataSet().getData("foo").empty());
        }
    }
    SECTION("DataSetBuilder::DataSet"){
        testBuilder.insert(std::make_pair<std::string,std::vector<Datum>>("foo",{Datum()}));
        DataSet test = testBuilder;
        SECTION("Successful conversion between DataSet and DataSetBuilder objects") REQUIRE(test.getTitle() == "test");
    }
}