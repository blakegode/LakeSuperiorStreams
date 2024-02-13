#ifndef LAKESUPERIORSTREAMS_DATAMANAGER_H
#define LAKESUPERIORSTREAMS_DATAMANAGER_H

#include <unordered_map>
#include <string>
#include <vector>

#include "DataSet.h"
#include "DataSetBuilder.h"

/**
 * @brief Manages database by getting or inserting data
 * 
 */
class DataManager {
private:
    std::vector<DataSet> m_data;
    
public:

    /**
     * @brief Get the Datum object
     *
     * @param field
     * @param time
     * @return Datum
     */
    Datum getDatum(std::string field, TimeStamp time); //TODO: requires binary search by time

    /**
     * @brief Gets the Data object given a field
     * 
     * @param field 
     * @return std::vector<Datum> 
     */
    std::vector<Datum> getData(std::string field); //TODO

    /**
     * @brief Gets the Data object given a field, a start timestamp and a end timestamp
     * 
     * @param field 
     * @param begin 
     * @param end 
     * @return std::vector<Datum> 
     */
    std::vector<Datum> getData(std::string field, TimeStamp begin, TimeStamp end); //TODO

    /**
     * @brief Construct a new Data Manager object
     *
     */
    DataManager() = default;

    /**
     * @brief Destroy the Data Manager object
     * 
     */
    ~DataManager() = default;

    /**
     * @brief Get the Data object
     *
     * @param subject
     * @param field
     * @param begin
     * @param end
     * @return std::vector<Datum>
     */
    std::vector<Datum> getData(std::string subject, std::string field, TimeStamp begin, TimeStamp end); //TODO

    //    void insert(const std::string &subject, const std::string &field, bool isSecond, const Datum &datum);
    /**
     * @brief inserts dataset into database
     *
     * @param dataSet
     */
    void insert(DataSet& dataSet);

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    [[nodiscard]] const bool  empty() const;
    
};


#endif //LAKESUPERIORSTREAMS_DATAMANAGER_H
