#ifndef LAKESUPERIORSTREAMS_DATUM_H
#define LAKESUPERIORSTREAMS_DATUM_H

#include <string>
#include "Time.h"

/**
 * @class Datum
 * @brief Stores values into datamembers
 * 
 */

class Datum {
private:
    float m_val;
    TimeStamp m_timeStamp;
    std::string m_field;
    std::string m_dataset;
public:
    /**
     * @brief Get the Val object
     *
     * @return float
     */
    [[nodiscard]] float getVal() const;

    /**
     * @brief Get the Time Stamp object
     * 
     * @return const TimeStamp 
     */
    [[nodiscard]] const TimeStamp getTimeStamp() const;

    /**
     * @brief Get the Dataset object
     * 
     * @return const std::string 
     */
    [[nodiscard]] const std::string getDataset() const;

    /**
     * @brief Get the Subject object
     * 
     * @return const std::string 
     */
    [[nodiscard]] const std::string getSubject() const;

    /**
     * @brief Get the Field object
     * 
     * @return const std::string 
     */
    [[nodiscard]] const std::string getField() const;

    /**
     * @brief Set the Val object
     *
     * @param INm_val
     */
    void setVal(float INm_val);

    /**
     * @brief Set the Timestamp object
     *
     * @param INm_timeStamp
     */
    void setTimestamp(TimeStamp INm_timeStamp);

    /**
     * @brief Set the Dataset object
     * 
     * @param INm_dataset 
     */
    void setDataset(std::string INm_dataset);

    /**
     * @brief Set the Subject object
     * 
     * @param INm_subject 
     */
    void setSubject(std::string INm_subject);

    /**
     * @brief Set the Field object
     * 
     * @param INm_field 
     */
    void setField(std::string INm_field);

    /**
     * @brief Construct a new Datum object
     *
     */
    Datum() = default;

    /**
     * @brief Construct a new Datum object
     *
     * @param dataset
     * @param field
     * @param timeStamp
     * @param val
     */
    Datum(std::string dataset, std::string field, TimeStamp timeStamp, float val);

    Datum(TimeStamp timeStamp) : m_timeStamp(timeStamp){}
    Datum(TimeStamp timeStamp, std::string field) : m_timeStamp(timeStamp), m_field(field){}


};


#endif //LAKESUPERIORSTREAMS_DATUM_H
