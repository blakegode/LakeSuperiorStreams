#include <catch2/catch_test_macros.hpp>
#include "lib/DataBase/QueryManager.h"
#include "lib/DataBase/Datum.h"

TEST_CASE("Tests the diff method of QueryManager"){

    Datum A("","",std::chrono::system_clock::now(),0);
    Datum B("","",std::chrono::system_clock::now(),0);
    Datum C("","",std::chrono::system_clock::now(),0);

    A.setVal(5.3);
    B.setVal(3.2);

    QueryManager QM;

    C = QM.diff(A,B," ", " ",std::chrono::system_clock::now());

    REQUIRE(C.getVal()-2.1 < 0.00001);
}

TEST_CASE("Tests the diffVector method of QueryManager"){

    QueryManager QM;
    std::vector<Datum> a;
    std::vector<Datum> b;

    a.push_back(Datum("DatasetA", "FieldA", TimeStamp(), 1.0));
    a.push_back(Datum("DatasetB", "FieldB", TimeStamp(), 2.0));
    a.push_back(Datum("DatasetC", "FieldC", TimeStamp(), 3.0));

    b.push_back(Datum("DatasetA", "FieldA", TimeStamp(), 0.5));
    b.push_back(Datum("DatasetB", "FieldB", TimeStamp(), 1.5));
    b.push_back(Datum("DatasetC", "FieldC", TimeStamp(), 2.5));

    std::vector<Datum> c = QM.diffVector(a, b);

    REQUIRE(c.size() == 3);

    REQUIRE(c[0].getVal()-.5 < 0.00001);
    REQUIRE(c[1].getVal()-.5 < 0.00001);
    REQUIRE(c[2].getVal()-.5 < 0.00001);

}

TEST_CASE("Tests the vectorOfVariance method of QueryManager"){

    QueryManager QM;
    std::vector<Datum> a;
    std::vector<Datum> b;

    a.push_back(Datum("DatasetA", "FieldA", TimeStamp(), 1.0));
    a.push_back(Datum("DatasetB", "FieldB", TimeStamp(), 2.0));
    a.push_back(Datum("DatasetC", "FieldC", TimeStamp(), 3.0));

    b.push_back(Datum("DatasetA", "FieldA", TimeStamp(), 0.5));
    b.push_back(Datum("DatasetB", "FieldB", TimeStamp(), 1.0));
    b.push_back(Datum("DatasetC", "FieldC", TimeStamp(), 0.5));

    std::vector<Datum> c = QM.diffVector(a, b);

    std::vector<Datum> d = QM.vectorOfVariance(c,2.0);

    REQUIRE(c.size() == 1);
    REQUIRE(c[0].getVal()-2.5 < 0.00001);
}