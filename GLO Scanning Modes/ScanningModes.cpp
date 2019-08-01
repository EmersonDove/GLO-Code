//
//  ScanningModes.cpp
//  GLO Scaning Modes
//
//  Created by Emerson on 7/16/19.
//  Copyright © 2019 Emerson. All rights reserved.
//
#include <vector>
#include <iostream>
#include <mutex>

//std::mutex mtx;
using namespace std;
class Point {
protected:
    double x;
    double y;
public:
    Point(double x_, double y_) {
        x=x_;
        y=y_;
    }
    double getX() {
        return x;
    }
    double getY() {
        return y;
    }
    void setX(double x_) {
        x=x_;
    }
    void setY(double y_) {
        y=y_;
    }
};

class intPoint {
protected:
    int x;
    int y;
public:
    intPoint(int x_, int y_) {
        x=x_;
        y=y_;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    void setX(int x_) {
        x=x_;
    }
    void setY(int y_) {
        y=y_;
    }
};


class ScanningBase {
protected:
    std::mutex padlock;
    //Time spent in each grid
    int lingerTime;
    //Time in current grid
    int lingeringNumber = -1;
    //Defaults used for generating the angles
    int sensorWidth = 1280;
    int sensorHeight = 1024;
    int sunPixelDiameter = 200;
    //Angle array
    vector<vector<Point *> > angles;
    //X and Y limits of the table (avoids more accesses)
    int tableXLimit;
    int tableYLimit;

    bool scanning = false;

    double pushX = 0;
    double pushY = 0;
public:
    //Constructor - sets in initation
    ScanningBase(int x, int y, int lingerTime_) {
        tableXLimit = x-1;
        tableYLimit = y-1;
        lingerTime = lingerTime_;
        createAngleTable(x, y);
    };
    ScanningBase(int x, int y, int lingerTime_, double offsetX_, double offsetY_) {
        tableXLimit = x-1;
        tableYLimit = y-1;
        pushX = offsetX_;
        pushY = offsetY_;
        lingerTime = lingerTime_;
        createAngleTable(x,y);
    }

    //Setters for table generation
    void setSensorWidth(int width) {
        sensorWidth = width;
        createAngleTable(tableXLimit+1,tableYLimit+1);
    }
    void setSensorHeight(int height) {
        sensorHeight = height;
        createAngleTable(tableXLimit+1,tableYLimit+1);
    }
    void setSunPixelDiameter(int diameter) {
        sunPixelDiameter=diameter;
        createAngleTable(tableXLimit+1,tableYLimit+1);
    }
    void setAngleTableDimensions(int newTableX, int newTableY) {
        tableXLimit = newTableX-1;
        tableYLimit = newTableY-1;
        createAngleTable(newTableX,newTableY);
    }

    //Creates the table which has the angles
    void createAngleTable(int x, int y) {
        const double degPerPixel = .53/((double)sunPixelDiameter);
        const double cameraFOVWidth = degPerPixel*((double) sensorWidth);
        const double cameraFOVHeight = degPerPixel*((double) sensorHeight);

        const double unitX = (cameraFOVWidth/2)/x;
        const double unitY = (cameraFOVHeight/2)/y;

        double offsetX;
        double offsetY;

        offsetX = unitX * (x-1) * -1;
        offsetY = unitY * (y-1) * -1;

        angles.clear();
        for (int j = 0; j<y; j++) {
            vector<Point *> xVals;
            for (int i = 0; i<x; i++) {
                xVals.push_back(new Point((offsetX+(unitX*i*2))+pushX,((offsetY+(unitY*j*2))*-1 )+pushY));
            }
            angles.push_back(xVals);
        }
    }
    //Destructor
    ~ScanningBase() {}

    //Prints the angle table to the terminal
    void printAngles() {
        std::cout << "Length X: " << angles.at(0).size() << endl;
        std::cout << "Length Y: " << angles.size() << endl;
        for (int i = 0; i<angles.size(); i++) {
            for (int j = 0; j<angles.at(i).size(); j++) {
                std::cout << angles[i][j]->getX() << "," << angles[i][j]->getY() << "  ";
            }
            std::cout << endl;
        }
    };

    void enableScan() {
        scanning = true;
    }
    void disableScan() {
        scanning = false;
    }
};

//Starts in the top left and does an S shape down
class S_TOP_LEFT : public ScanningBase {
protected:
    intPoint currentLocation{0,0};
    vector<Point> convertedAngles;
    int currentLinger = -1;
    int currentPoint = 0;
private:
    void generateConvertedArray() {
        int currentX = 0;
        int currentY = 0;
        convertedAngles.clear();
        while(true) {
            if (currentY % 2 == 0) {
                if (currentX != tableXLimit+1) {
                    convertedAngles.push_back(*angles[currentY][currentX]);
                    currentX++;
                }
                else {
                    if (currentY != tableYLimit) {
                        currentY++;
                    }
                    else {
                        break;
                    }
                }
            }
            else {
                if (currentX != 0) {
                    currentX--;
                    convertedAngles.push_back(*angles[currentY][currentX]);
                }
                else {
                    if (currentY != tableYLimit) {
                        currentY++;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
public:
    S_TOP_LEFT(int xNumber, int yNumber, int lingerTime) : ScanningBase(xNumber,yNumber,lingerTime) {
        std::lock_guard<std::mutex> lock(padlock);
        generateConvertedArray();
    };
    S_TOP_LEFT(int xNumber, int yNumber, int lingerTime, double offsetX, double offsetY) : ScanningBase(xNumber, yNumber, lingerTime,offsetX,offsetY) {
        std::lock_guard<std::mutex> lock(padlock);
        generateConvertedArray();
    };
    void regenerateAngles() {
        generateConvertedArray();
    }
    Point getOffset() {
        if (scanning) {
            if (currentLinger == lingerTime-1) {
                currentPoint++;
                currentLinger = 0;
                if (currentPoint == convertedAngles.size()) {
                    currentPoint = 0;
                }
                return convertedAngles[currentPoint];
            }
            else {
                currentLinger++;
                return convertedAngles[currentPoint];
            }
        }
        else {
            return Point(0,0);
        }
    }
//    Point getOffset() {
//        if (scanning) {
//            advanceSScan(currentLocation);
//            return Point(*angles.at(currentLocation.getY()).at(currentLocation.getX()));
//        }
//        else {
//            return Point(0,0);
//        }
//    }
    //Direct access to currentLocation makes it necessary to place in this class, but with more modes I can make a getter/setter
    void resetScan() {
        currentLinger = -1;
        currentPoint = 0;
    }
};
