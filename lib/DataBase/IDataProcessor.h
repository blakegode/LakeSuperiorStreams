//
// Created by Eli on 10/12/2023.
//

#ifndef LAKESUPERIORSTREAMS_IDATAPROCESSOR_H
#define LAKESUPERIORSTREAMS_IDATAPROCESSOR_H
#include <iostream>
#include <string>
#include <memory>

#include "DataManager.h"

/**
 * @class IDataProcessor
 * @brief Interface for reading in files to get the data
 */
class IDataProcessor {
public:
    virtual int foo() = 0;
    /**
    * The read function takes in the name of the file you want to read in then using a parser to seperate the data into
    * different vectors and then creates datum objects with the info and returns them in a map
    * (key : stream value : vector of datums from stream)
    *
    * @param filename
    * @return Returns unordered map of the stream name to a vector of datums of that stream
    */
    virtual std::unordered_map<std::string,std::vector<Datum>>  read(std::string filename) = 0;
   
};

#endif //LAKESUPERIORSTREAMS_IDATAPROCESSOR_H
