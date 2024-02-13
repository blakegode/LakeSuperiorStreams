//
// Created by Eli on 10/12/2023.
//

#ifndef LAKESUPERIORSTREAMS_CSVPROCESSOR_H
#define LAKESUPERIORSTREAMS_CSVPROCESSOR_H

#include "IDataProcessor.h"
#include "rapidcsv.h"
#include "ctime"
#include "chrono"

/**
 * @brief Reads in data from a CSV file.
 * 
 */
class CSVProcessor : public IDataProcessor {
private:

public:
    CSVProcessor() = default;
    TimeStamp getTime(std::string ddMMyyyy_hhMMss);

    int foo() override;

    /**
    * The read function takes in the name of the file you want to read in then using a parser to seperate the data into
    * different vectors and then creates datum objects with the info and returns them in a map
    * (key : stream value : vector of datums from stream)
    *
    * @param filename
    * @return Returns unordered map of the stream name to a vector of datums of that stream
    */
    std::unordered_map<std::string,std::vector<Datum>> read(std::string filename) override;
};


#endif //LAKESUPERIORSTREAMS_CSVPROCESSOR_H
