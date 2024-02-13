//
// Created by Eli on 10/15/2023.
//

#ifndef LAKESUPERIORSTREAMS_DATASET_H
#define LAKESUPERIORSTREAMS_DATASET_H

#include <unordered_map>
#include <string>
#include <vector>

#include "Time.h"
#include "Datum.h"

class DataSetBuilder;

/**
 * @brief Creates datasets by getting data
 * 
 */
class DataSet {
private:
    std::string m_title;
    std::vector<TimeStamp> m_time;
    std::unordered_map<std::string,std::vector<Datum>> m_data;

    /**
     * @brief
     *
     * @param data
     * @param target
     * @param searchType
     */
    void m_searchByTime(const std::vector<Datum> &data, TimeStamp target, TimeSeries::SearchType searchType); // TODO: imported binary search functionality

    /**
     * @brief 
     * 
     * @param idx 
     * @return TimeStamp 
     */
    TimeStamp m_getTimeByIndex(const int& idx);

    /**
     * @brief 
     * 
     * @param data 
     * @param target 
     * @param searchType 
     * @return int 
     */
    int m_getIndexByTime(const std::vector<Datum> &data, TimeStamp target, TimeSeries::SearchType searchType);

    /**
     * @brief Construct a new Data Set object
     * 
     * @param title 
     */
    DataSet(std::string title) : m_title(title){}
public:
    friend class DataSetBuilder;

    /**
     * @brief Creates new dataset
     * 
     * @param name 
     * @return DataSetBuilder 
     */
    static DataSetBuilder create(std::string name);

/**
 * @brief 
 * 
 * @return const TimeStamp 
 */
    [[nodiscard]] const TimeStamp start() const;

    /**
     * @brief 
     * 
     * @return TimeStamp 
     */
    TimeStamp end();



    /**
     * @brief Get the Data object
     * 
     * @param field 
     * @return std::vector<Datum> 
     */
    std::vector<Datum> getData(std::string field);

    /**
     * @brief Get the Data object
     * 
     * @param field 
     * @param begin 
     * @param end 
     * @return float 
     */
//    float getData(std::string field, TimeStamp begin, TimeStamp end); // TODO



    /**
     * @brief
     *
     * @param field
     * @param idx
     * @return Datum
     */
    [[nodiscard]] Datum get(const std::string& field, const int& idx) const; //TODO: get by timestamp

    /**
     * @brief Get the Time Stamp object
     * 
     * @return TimeStamp 
     */
    TimeStamp getTimeStamp() const;
Datum getDatum(std::string field, TimeStamp time, TimeSeries::SearchType type=TimeSeries::SearchType::EQ);
    std::string getTitle();
};


#endif //LAKESUPERIORSTREAMS_DATASET_H
