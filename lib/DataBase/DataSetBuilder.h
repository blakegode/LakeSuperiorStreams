#ifndef LAB4_DATASETBUILDER_H
#define LAB4_DATASETBUILDER_H


#include "DataSet.h"
#include <string>

/**
 * @brief builds data set
 * 
 */
class DataSetBuilder{
private:
    DataSet m_dataSet;
public:

/**
 * @brief Construct a new Data Set Builder object
 * 
 * @param name 
 */
    DataSetBuilder(const std::string& name) : m_dataSet(name) {}

/**
 * @brief 
 * 
 * @return DataSet 
 */
    operator DataSet() const { return std::move(m_dataSet); }

/**
 * @brief Inserts a datum to dataset
 * 
 * @param datum 
 * @return DataSetBuilder 
 */
    DataSetBuilder insert(std::pair<std::string, std::vector<Datum>> datum);

/**
 * @brief 
 * 
 * @param title 
 * @return DataSetBuilder 
 */
    DataSetBuilder title(std::string title);
    std::string getTitle();
    DataSet getDataSet();
};

#endif //LAB4_DATASETBUILDER_H
