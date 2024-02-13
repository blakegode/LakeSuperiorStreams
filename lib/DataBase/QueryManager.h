#ifndef LAKESUPERIORSTREAMS_QUERYMANAGER_H
#define LAKESUPERIORSTREAMS_QUERYMANAGER_H

#include <memory>

#include "DataManager.h"

/**
 * @brief Performs different opperations from a given query
 * 
 */
class QueryManager {
public:
    std::shared_ptr<DataManager> data;

/**
 * @brief Construct a new Query Manager object
 * 
 */
    QueryManager() = default;

/**
 * @brief 
 * 
 * @param data 
 * @param flag 
 * @return std::vector<Datum> 
 */
    std::vector<Datum> filterDataByFlag(std::vector<Datum> data, std::string flag); //TODO

/**
 * @brief 
 * 
 * @return std::vector<Datum> 
 */
    static std::vector<Datum> filterDataByTime(const std::vector<Datum>); //TODO

/**
 * @brief 
 * 
 * @param data 
 * @param begin 
 * @param end 
 * @return std::vector<Datum> 
 */
    std::vector<Datum> filterDataByDataSet(std::vector<Datum> data, TimeStamp begin, TimeStamp end); //TODO

/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @param dataset 
 * @param field 
 * @param timeStamp 
 * @return Datum 
 */
    Datum diff(Datum a, Datum b, std::string dataset, std::string field, TimeStamp timeStamp);

/**
 * @brief Construct a new Query Manager object
 * 
 * @param data 
 */
    explicit QueryManager(std::shared_ptr<DataManager> data);

/**
 * @brief 
 * 
 * @param stream 
 * @param t 
 * @return Datum 
 */
    Datum binarySearch(std::string stream, std::string,  TimeStamp t);

/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @return std::vector<Datum> 
 */
    std::vector<Datum> diffVector(std::vector<Datum> a,std::vector<Datum> b);

    /**
 * @brief
 *
 * @param a
 * @param  threshold
 * @return std::vector<Datum>
 */
    std::vector<Datum> vectorOfVariance(std::vector<Datum>& a, float threshold);
};


#endif //LAKESUPERIORSTREAMS_QUERYMANAGER_H
