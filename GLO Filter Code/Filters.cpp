#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include "CircularBuffer.hpp"
using namespace std;

enum class FilterType {
    UNKNOWN,
    ROLLING_AVERAGE,
    EXPONENTIAL,
    HIGH_PASS,
    BUTTERWORTH
};

// BASE CLASS DEFINITION
class FilterBase {
protected:
    std::mutex padlock;
    //gloabl filter type
    FilterType filter_type = FilterType::UNKNOWN;
    int rollingLength;
    double bufferValue = 0.0;
    int originalRollingLength;
public:
    // Constructor
    FilterBase(int theRollingLength) {
        rollingLength = theRollingLength;
        originalRollingLength = theRollingLength;
    }
    // Destructor
    ~FilterBase() {};
    virtual double Execute(circular_buffer<double>& buffer) = 0;
    FilterType GetFilterType() {
        return filter_type;
    }
};


// ROLLING FILTER CLASS DEFINITION
class RollingFilter : FilterBase {
public:
    RollingFilter(int theRollingLength) : FilterBase(theRollingLength) {
        filter_type = FilterType::ROLLING_AVERAGE;
    }
    //Does a rolling average at the length of the rolling average specified
    //If rolling average is larger than the length of the circular buffer, the entire circular buffer is averaged without raising exception
    double Execute(circular_buffer<double>& input) override {
        std::lock_guard<std::mutex> lock(padlock);
        double sum = 0.0;

        int arrLength = (int)input.size();
        if (rollingLength >= arrLength) {
            for (int i = 0; i < arrLength; i++) {
                input.read(i, bufferValue);
                sum += bufferValue;
            }
        }
        else {
            for (int i = arrLength - 1; i >= arrLength - rollingLength; i--) {
                input.read(i, bufferValue);
                sum += bufferValue;
            }
        }
        return sum / rollingLength;
    }
};

// EXPONENTIAL FILTER CLASS DEFITION
class ExponentialFilter : FilterBase {
protected:
    //Set the smoothing constant of the exponential filter, higher means the most recent is more weighted
    double smoothingConstant = 2;
    double lastEMA = 0.0;
    double k = 0.0;
    int readIndex;
    int arrLength = 0;

public:
    ExponentialFilter(int theRollingLength, double theSmoothingConstant = 2.0) : FilterBase(theRollingLength) {
        filter_type = FilterType::EXPONENTIAL;
        smoothingConstant = theSmoothingConstant;
    }
    //Does a exponential rolling average at the length of the rolling average specified (uses the same variable as rolling())
    //If rolling average is larger than the length of the circular buffer, the entire circular buffer is averaged without raising exception
    double Execute(circular_buffer<double>& input) override {
        std::lock_guard<std::mutex> lock(padlock);
        lastEMA = 0.0;
        k = 0.0;
        readIndex = 0;
        arrLength = (int)input.size();

        rollingLength = originalRollingLength;
        if (rollingLength > arrLength) {
            rollingLength = arrLength;
        }

        input.read(arrLength - rollingLength, lastEMA);

        for (int i = 1; i < arrLength; i++) {
            k = smoothingConstant / ((double)i + 2);
            readIndex = (arrLength - rollingLength) + i;
            input.read(readIndex, bufferValue);
            lastEMA = (bufferValue * k) + (lastEMA * (1 - k));
        }
        return lastEMA;
    }
};

// HIGH-PASS FILTER CLASS DEFINITION
class HighPassFilter : FilterBase {
protected:
    double cutoffFrequency;
    double oldBufferValue = 0.0;
    int arrLength = 0;
    int i = 0;
    double sum = 0.0;

public:
    HighPassFilter(int theRollingLength, double theCutOffFrequency = 0.5) : FilterBase(theRollingLength) {
        filter_type = FilterType::HIGH_PASS;
        cutoffFrequency = theCutOffFrequency;
    }
    //Performs a highpass on the data inputed and then averages the buffer based on the rollinglength
    double Execute(circular_buffer<double>& input) override {
        std::lock_guard<std::mutex> lock(padlock);
        arrLength = (int)input.size();
        i = 0;
        sum = 0.0;

        rollingLength = originalRollingLength;
        if (rollingLength > arrLength) {
            rollingLength = arrLength;
        }

        vector<double> data(arrLength);
        input.read(0, bufferValue);
        data[0] = bufferValue;

        double a = cutoffFrequency;
        for (i = 1; i < arrLength; i++) {
            oldBufferValue = bufferValue;
            input.read(i, bufferValue);
            data[i] = (a * (data[i - 1] + bufferValue - oldBufferValue));
        }
        sum = 0;
        for (i = arrLength - 1; i >= arrLength - rollingLength; i++) {
            sum = sum + data[i];
        }
        data.empty();
        return sum / rollingLength;
    }
};

//BUTTERWORTH FILTER CLASS DEFINITION
class ButterWorthLowPass : FilterBase {
protected:
    int NZEROS = 1;
    int NPOLES = 1;
    double GAIN = 7.173081781e+01;
    double sum = 0;
    double size = 0;
public:
    ButterWorthLowPass(int theRollingLength) : FilterBase(theRollingLength) {
        filter_type = FilterType::BUTTERWORTH;
    }

    double Execute(circular_buffer<double>& input) override {
        size = input.size();

        rollingLength = originalRollingLength;
        if (rollingLength > size) {
            rollingLength  = size;
        }
        float xv[NZEROS+1], yv[NPOLES+1];
        vector<double> output;
        for (int i = size-rollingLength;i<size;i++) {
            xv[0] = xv[1];
            input.read(i,bufferValue);
            xv[1] = bufferValue / GAIN;
            yv[0] = yv[1];
            yv[1] = (xv[0] + xv[1]) + (0.9721179814 * yv[0]);
            output.push_back(yv[1]);
        }
        sum = 0;
        for (int i = 0; i<output.size(); i++) {
            sum+=output.at(i);
        }
        return sum/size;
    }
};
