//
// Created by Eli on 10/16/2023.
//

#ifndef LAKESUPERIORSTREAMS_DATABASE_H
#define LAKESUPERIORSTREAMS_DATABASE_H
#include "QueryManager.h"
#include "DataSetBuilder.h"

#include <memory>

/**
 * @brief Contains a shared data and query pointer
 * 
 */
class DataBase {
public:
    std::shared_ptr<DataManager> data;
    std::shared_ptr<QueryManager> query;
    DataBase();

/**
 * @brief Reads in data from a CSV file
 * 
 * @param filename 
 */
    void read(std::string filename);
};


#endif //LAKESUPERIORSTREAMS_DATABASE_H
