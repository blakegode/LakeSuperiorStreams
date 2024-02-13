#pragma once

#include <chrono>

using TimeStamp = std::chrono::time_point<std::chrono::system_clock>;

/**
 * @brief 
 * 
 */
namespace TimeSeries {
    enum class SearchType {
        EQ,
        LE,
        GE,
        NE
    };

    /**
     * @brief 
     * 
     * @tparam T 
     * @param data 
     * @param obj 
     */
    template<typename T>
    static void insert(std::vector<T>& data, const T& obj){
        int low = 0;
        int high = static_cast<int>(data.size())-1;
        auto timeStamp = obj.getTimeStamp();
        while(low <= high){
            int mid = (low + high) / 2;
            if(data[mid].getTimeStamp() < timeStamp){
                low = mid + 1;
            }else{
                high = mid - 1;
            }
        }
        data.insert(data.begin()+low,obj);
    }

    static int diff(TimeStamp tA, TimeStamp tB){
        int span = (tA > tB) ?
                std::chrono::duration_cast<std::chrono::milliseconds>(tA - tB).count()
                :
                std::chrono::duration_cast<std::chrono::milliseconds>(tB - tA).count();
        return span;
    }

  /**
     * @brief 
     * 
     * @tparam T 
     * @param data 
     * @param target 
     * @param searchType 
     * @return int 
     */
    template<typename T>
    int findIndex(std::vector<T>& data, TimeStamp target, TimeSeries::SearchType searchType = TimeSeries::SearchType::EQ){
        if(data.empty()) {
            return -1;
        }
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
            case(TimeSeries::SearchType::NE):
                if (left >= data.size()) return right;
                if (right < 0) return left;
                auto diffGE = std::abs(std::chrono::duration_cast<std::chrono::microseconds>(data[left].getTimeStamp() - target).count());
                auto diffLE = std::abs(std::chrono::duration_cast<std::chrono::microseconds>(data[right].getTimeStamp() - target).count());
                return (diffGE < diffLE) ? left : right;
        }
        return -1;
    }

    /**
     * @brief 
     * 
     * @tparam T 
     * @param data 
     * @param target 
     * @return std::vector<T> 
     */
    template<typename T>
    std::vector<T> get(std::vector<T>& data, TimeStamp target); //TODO: return a vector of all  T after the index at target timestamps

/**
 * @brief 
 * 
 * @tparam T 
 * @param data 
 * @param begin 
 * @param end 
 * @return std::vector<T> 
 */
    template<typename T>
    std::vector<T> filterTimeSpan(std::vector<T>& data, TimeStamp begin, TimeStamp end){
        auto out = data;
        auto a = out.begin()
                + TimeSeries::findIndex(data,begin,TimeSeries::SearchType::GE),
            b = out.begin()
                + TimeSeries::findIndex(data,end,TimeSeries::SearchType::LE)
                + 1;
        out.erase(out.begin(),a);
        out.erase(b,out.end());
        return out;
    }
}