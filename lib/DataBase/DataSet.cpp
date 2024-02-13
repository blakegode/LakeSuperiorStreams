#include "DataSet.h"
#include "DataSetBuilder.h"


TimeStamp DataSet::m_getTimeByIndex(const int& idx) {
    return this->m_time.at(idx);
}

std::vector<Datum> DataSet::getData(std::string field) {
    auto it = this->m_data.find(field);
    if(it != this->m_data.end()) return it->second;
    return {};
}


const TimeStamp DataSet::start() const {
    return this->m_time.empty()?std::chrono::time_point<std::chrono::system_clock>():this->m_time.at(0);
    ;
}

TimeStamp DataSet::end() {
    return this->m_time.at(this->m_time.size()-1);
}

int DataSet::m_getIndexByTime(const std::vector<Datum> &data, TimeStamp target, TimeSeries::SearchType searchType) {
    int left = 0, right = (static_cast<int>(data.size())-1), idx = -1;
    while(left <= right){
        idx = left + (right - left) / 2;
        if(data[idx].getTimeStamp() == target){
            return idx;
        }
        if(data[idx].getTimeStamp() < target){
            left = idx + 1;
        }
        else{
            right = idx - 1;
        }
    }
    switch(searchType){
        case(TimeSeries::SearchType::EQ):
            return -1;
        case(TimeSeries::SearchType::GE):
            return (left < data.size()) ? left : -1;
        case(TimeSeries::SearchType::LE):
            return right;
    }
    return -1;
}


DataSetBuilder DataSet::create(std::string name){
    return DataSetBuilder{name};
}

Datum DataSet::get(const std::string& field, const int& idx) const {
    return this->m_data.at(field).at(idx);
}



TimeStamp DataSet::getTimeStamp() const{
    return this->start();
}

Datum DataSet::getDatum(std::string field, TimeStamp time, TimeSeries::SearchType type) {
    auto data = this->getData(field);
    auto idx = TimeSeries::findIndex(data,time,type);
    if(!this->getData(field).empty() && idx>=0&&idx<this->getData(field).size()){
        return this->getData(field).at(idx);
    }
    return {};
}

std::string DataSet::getTitle(){
    return this->m_title;
}
