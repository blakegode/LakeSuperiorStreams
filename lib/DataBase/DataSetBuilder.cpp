#include "DataSetBuilder.h"

DataSetBuilder DataSetBuilder::title(std::string title){
    this->m_dataSet.m_title = title;
    return *this;
}

DataSetBuilder DataSetBuilder::insert(std::pair<std::string,std::vector<Datum>> column){
    this->m_dataSet.m_data.emplace(column);
    return *this;
}

std::string DataSetBuilder::getTitle() {
    return this->m_dataSet.m_title;
}

DataSet DataSetBuilder::getDataSet() {
    return this->m_dataSet;
}
