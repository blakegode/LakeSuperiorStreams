#include "QueryManager.h"

QueryManager::QueryManager(std::shared_ptr<DataManager> data) {
    this->data = data;
}

Datum QueryManager::binarySearch(std::string stream, std::string,  TimeStamp t) {

    return Datum();
}

Datum QueryManager::diff(Datum a, Datum b, std::string dataset, std::string field, TimeStamp timeStamp) {
    return Datum(dataset,field,timeStamp,abs(a.getVal()-b.getVal()));
}

std::vector<Datum> QueryManager::diffVector(std::vector<Datum> a, std::vector<Datum> b) {
    std::vector<Datum> c;
    for (unsigned int i = 0; i < a.size(); i++) {
        Datum diffDatum = diff(a[i], b[i], a[i].getDataset(), a[i].getField(), a[i].getTimeStamp());
        c.push_back(diffDatum);
    }
    return c;
}

std::vector<Datum>QueryManager::vectorOfVariance(std::vector<Datum>& a, float threshold) {

    auto it = a.begin();

    while (it != a.end()) {
        if (it->getVal() < threshold) {
            it = a.erase(it);
        } else {
            ++it;
        }
    }

    return a;
}