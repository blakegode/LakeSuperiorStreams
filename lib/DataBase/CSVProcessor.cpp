#include "CSVProcessor.h"

TimeStamp CSVProcessor::getTime(std::string ddMMyyyy_hhMMss) {
    std::tm time;

    time.tm_mon = stoi(ddMMyyyy_hhMMss.substr(0,2))-1;
    time.tm_mday = stoi(ddMMyyyy_hhMMss.substr(3,2));
    time.tm_year = stoi(ddMMyyyy_hhMMss.substr(6,4))-1900;
    time.tm_hour = stoi(ddMMyyyy_hhMMss.substr(11,2));
    time.tm_min = stoi(ddMMyyyy_hhMMss.substr(14,2));
    time.tm_sec = stoi(ddMMyyyy_hhMMss.substr(17,2));

    time_t tt = std::mktime(&time);
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::from_time_t(tt);
    return tp;
}

std::unordered_map<std::string,std::vector<Datum>> CSVProcessor::read(std::string filename) {
    rapidcsv::Document doc(filename);

    //Create a vector of all the data field names
    std::vector<std::string> fieldNames = doc.GetColumnNames();

    //Creates a map of the data field name to a vector of the values from the column of that data field
    std::map<std::string, std::vector<float>> fieldToFieldVals;

    //Fill each vector with the data from the file
    for (const std::string& string : fieldNames) {
        std::vector<std::string> newVector = doc.GetColumn<std::string>(string);

        //Create an empty vector of floats that will contain the float values once we convert from strings to floats
        std::vector<float> floatVector;

        //Erase the first row of the read in data - the first row is what the data is measured in. Example: m3/sec
        newVector.erase(newVector.begin());

        //We will try to convert each string to be a float, if it cannot like for empty values or dates then -1 will be inserted
        for (const std::string& str : newVector) {
            if (string != "DateTime") {
                float valAsFloat = -1;
                try {
                    valAsFloat = std::stof(str);
                } catch (std::invalid_argument) {}
                if (valAsFloat != -1) {
                    floatVector.push_back(valAsFloat);
                }
            }
        }

        //if the vector is not empty add it to the map
        if (floatVector.size() != 0) {
            fieldToFieldVals[string] = floatVector;
        }
    }

    // Get the data from the first column AKA the stream name (including row headers)
    std::vector<std::string> StreamNameColumnData = doc.GetColumn<std::string>(fieldNames[0]);

    // Get the dateTime data from its Column and save it into a vector
    std::vector<std::string> dateTimeColumnData = doc.GetColumn<std::string>(fieldNames[1]);
    dateTimeColumnData.erase(dateTimeColumnData.begin());

    //convert dateTime vector to a vector of time stamps
    std::vector<TimeStamp> timeStampData;
    for (const auto& t : dateTimeColumnData) {
        TimeStamp timeStamp = getTime(t);

        timeStampData.push_back(timeStamp);
    }

    //Build datum objects and add too unordered map
    std::unordered_map<std::string, std::vector<Datum>> fieldToDatumVector;


    for (const auto& pair : fieldToFieldVals) {
        int i = 0;
        std::vector<Datum> datumVector;
        for (float x : pair.second) {
            Datum newDatum = Datum(StreamNameColumnData[0], pair.first, timeStampData[i], x);
            ++i;
            datumVector.push_back(newDatum);
        }
        fieldToDatumVector[pair.first] = datumVector;
    }


    return fieldToDatumVector;
}

int CSVProcessor::foo() {
    return 1;

}
