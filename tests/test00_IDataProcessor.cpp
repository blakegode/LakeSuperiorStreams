#include <catch2/catch_test_macros.hpp>
#include <ctime>
#include "lib/DataBase/DataManager.h"
#include "lib/DataBase/IDataProcessor.h"
#include "lib/DataBase/CSVProcessor.h"
#include <vector>
#include <iostream>
#include <map>
#include <sstream>

#include "rapidcsv.h"



TEST_CASE("TEST TO MAKE SURE WE CAN OPEN FILE"){

    rapidcsv::Document doc("../lib/StreamData/testCSV - twoRow.csv");

    int numRows = doc.GetRowCount();

    REQUIRE(numRows == 3);
}


TEST_CASE("READ IN DATA FILE") {
    rapidcsv::Document doc("../lib/StreamData/testCSV - twoRow.csv");

    std::vector<std::vector<std::string>> contents;

    std::vector<std::vector<std::string>> testContents = {{"", "MM/dd/yyyy HH:mm:ss", "m", "m3/sec", "deg C", "uS/cm",
                                                          "NTU", "inches"}, {"Tischer2020", "05/05/2020 11:30:00", "0.518",
                                                          "1.36", "7", "370", "", ""}, {"Tischer2020", "05/05/2020 11:45:00",
                                                          "0.518", "1.36", "7.18", "370", "", ""}
    };

    for (int row = 0; row < doc.GetRowCount(); ++row) {
        std::vector<std::string> rowData = doc.GetRow<std::string>(row);
        contents.push_back(rowData);
    }

    REQUIRE(contents == testContents);
}

TEST_CASE("Extract Specific Column Information From A File") {
   rapidcsv::Document doc("../lib/StreamData/Tischner Example - Sheet1.csv");

   std::vector<std::string> col = doc.GetColumn<std::string>("DateTime");

   int numEntries = col.size();

    REQUIRE(numEntries == 7);

}

TEST_CASE("EXTRACT ALL FIELDS FROM FILE AND SPLIT THEM INTO SEPARATE VECTORS") {
    rapidcsv::Document doc("../lib/StreamData/Tischner Example - Sheet1.csv");

    std::vector<std::string> fieldNames = doc.GetColumnNames();

    std::map<std::string, std::vector<float>> fieldToFieldVals;

    for (const std::string& string : fieldNames) {

        std::vector<std::string> newVector = doc.GetColumn<std::string>(string);

        std::vector<float> floatVector;

        newVector.erase(newVector.begin());

        for (const std::string& str : newVector) {
            if (string != "DateTime") {
                float valAsFloat = -1;
                try {
                    valAsFloat = std::stof(str);
                } catch (std::invalid_argument) {}
                if (valAsFloat != -1) {
                    floatVector.push_back(valAsFloat);
                }
            }
        }
        if (floatVector.size() != 0) {
            fieldToFieldVals[string] = floatVector;
        }
    }

    for (const auto& pair : fieldToFieldVals) {
        const std::vector<float>& vec = pair.second;
        std::cout << "KEY: " << pair.first << " Vector: ";
        for (float val : vec) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        //fieldToFieldVals[pair.first].push_back(doc.GetColumn<float>(pair.first));
    }

    // Get the data from the first column (including row headers)
    std::vector<std::string> firstColumnData = doc.GetColumn<std::string>(fieldNames[0]);

    // Print the data from the first column
    for (const std::string& cell : firstColumnData) {
        std::cout << cell << std::endl;
    }

    std::vector<std::string> dateTimeColumnData = doc.GetColumn<std::string>(fieldNames[1]);

    dateTimeColumnData.erase(dateTimeColumnData.begin());

    for (const std::string& cell : dateTimeColumnData) {
        std::cout << cell << std::endl;
    }
}

TEST_CASE("Check if processor returns the map we want") {
    CSVProcessor processor;
    std::unordered_map<std::string, std::vector<Datum>> testMap;
    std::unordered_map<std::string, std::vector<Datum>> contentsMap;
    testMap = processor.read("../lib/StreamData/testCSV - Sheet1.csv");


    std::cout << testMap["Temp"][3].getVal() << std::endl;

    REQUIRE(abs((testMap["Flow"][0].getVal() - 1.36)) < 0.005);
}

/*TEST_CASE("Read in CSV file"){
    DataManager db;
    db.readFile("test.csv"); //TODO: create a test CSV file
    std::string title = ""; //TODO: replace the value of title with the title of the TimeSeries subject (eg, "Tischer")
    std::string param = ""; //TODO: replace the value of param with a field within test.csv
    std::time_t begin = std::time(nullptr); //TODO: create a beginning timestamp that corresponds to the first data in the JSON
    std::time_t end = std::time(nullptr); //TODO: create a ending timestamp that corresponds to the first data in the JSON
    REQUIRE(db.query.get("Tischer", param, begin, end).empty() == false); //TODO: how are we going to confirm successful file read?
}*/