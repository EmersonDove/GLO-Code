//
//  ScanningModes.cpp
//  GLO Scaning Modes
//
//  Created by Emerson on 7/16/19.
//  Copyright © 2019 Emerson. All rights reserved.
//
#include <stdio.h>
#include <vector>
#include <iostream>

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
public:
    //Constructor - sets in initation
    ScanningBase(int x, int y, int lingerTime_) {
        tableXLimit = x-1;
        tableYLimit = y-1;
        lingerTime = lingerTime_;
        createAngleTable(x, y);
    };

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
                xVals.push_back(new Point(offsetX+(unitX*i*2),(offsetY+(unitY*j*2))*-1 ));
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
    //Advances an S shape scan. This algorithm needs worth to implement other types of scans if they are necessary.
    //I want it to work for all S modes, but for now it only does the S_TOP_LEFT scan so it could be placed in the S_TOP_LEFT class
    void advanceSScan(intPoint &input) {
        if (lingeringNumber < lingerTime-1) {
            lingeringNumber++;
            return;
        }
        else {
            lingeringNumber = 0;
            if (input.getY() % 2 == 0) {
                if (input.getX() == tableXLimit) {
                    if (input.getY() != tableYLimit) {
                        advanceDown(input);
                    }
                    else {
                        input.setX(0);
                        input.setY(0);
                    }
                    return;
                }
                advanceRight(input);
                return;
            }
            else {
                if (input.getX() == 0) {
                    advanceDown(input);
                    return;
                }
                advanceLeft(input);
                return;
            }
        }
    }

    void enableScan() {
        scanning = true;
    }
    void disableScan() {
        scanning = false;
    }

private:
    //Advancements
    void advanceDown(intPoint &p) {
        p.setY(p.getY()+1);
    }
    void advanceLeft(intPoint &p) {
        p.setX(p.getX()-1);
    }
    void advanceRight(intPoint &p) {
        p.setX(p.getX()+1);
    }
    void advanceUp(intPoint &p) {
        p.setY(p.getY()-1);
    }
};

//Starts in the top left and does an S shape down
class S_TOP_LEFT : public ScanningBase {
protected:
    intPoint currentLocation{0,0};
public:
    S_TOP_LEFT(int xNumber, int yNumber, int lingerTime) : ScanningBase(xNumber,yNumber,lingerTime) {
    };
    Point getOffset() {
        if (scanning == true) {
            advanceSScan(currentLocation);
            return Point(*angles.at(currentLocation.getY()).at(currentLocation.getX()));
        }
        else {
            return Point(0,0);
        }
    }
    //Direct access to currentLocation makes it necessary to place in this class, but with more modes I can make a getter/setter
    void resetScan() {
        currentLocation.setX(0);
        currentLocation.setY(0);
        lingeringNumber = -1;
    }
};
