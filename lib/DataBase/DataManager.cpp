#include "DataManager.h"
#include <vector>

void DataManager::insert(DataSet &dataSet) {
    TimeSeries::insert(this->m_data,dataSet);
}

const bool DataManager::empty() const {
    return this->m_data.empty();
}

std::vector<Datum> DataManager::getData(std::string field) {
    std::vector<Datum> out{};
    std::vector<Datum> append{};
    for(auto dataSet : this->m_data){
        append = dataSet.getData(field);
        out.insert(
                out.end(),
                std::make_move_iterator(append.begin()),
                std::make_move_iterator(append.end())
           );
    }
    return out;
}

