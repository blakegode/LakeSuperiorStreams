#include "DataBase.h"

DataBase::DataBase() {
    this->data = std::make_shared<DataManager>();
    this->query = std::make_shared<QueryManager>(this->data);
}
