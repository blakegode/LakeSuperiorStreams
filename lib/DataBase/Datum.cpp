#include "Datum.h"

float Datum::getVal() const {
    return this->m_val;
}

const TimeStamp Datum::getTimeStamp() const {
    return this->m_timeStamp;
}

const std::string Datum::getDataset() const {
    return this->m_dataset;
}

void Datum::setVal(float value) {
    m_val = value;
}

void Datum::setTimestamp(TimeStamp timeStamp) {
    m_timeStamp = timeStamp;
}

void Datum::setDataset(std::string dataset) {
    m_dataset = dataset;
}

Datum::Datum(std::string field, std::string dataset, TimeStamp timeStamp, float val) :
        m_dataset(dataset),
        m_field(field),
        m_timeStamp(timeStamp),
        m_val(val){}

const std::string Datum::getField() const {
    return this->m_field;
};

void Datum::setField(std::string INm_field) {
    m_field = INm_field;
}
