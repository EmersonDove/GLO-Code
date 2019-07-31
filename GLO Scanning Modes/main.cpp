//
//  Created by Emerson on 7/16/19.
//  Copyright © 2019 Emerson. All rights reserved.
//

#include <iostream>
#include "ScanningModes.cpp"
#include <chrono>

int main(int argc, const char * argv[]) {
    //Create object: scan(int xWidth, int yHeight, int lingerTime (samples spent in a grid)
    S_TOP_LEFT scan(36,36,10);
    //Show angles (for debugging)
    std::cout << "Showing angles generated: " << endl;
    scan.printAngles();
    //When the getOffset is called, it will iterate rather than return 0,0
    scan.enableScan();

    //Uncomment for speedtest
    //auto start = std::chrono::high_resolution_clock::now();
    //auto finish = std::chrono::high_resolution_clock::now();

    //Looping an arbitrary amount of 40 to show scan looping (scan will go back to top left when it reaches the end)
    std::cout << "Querying offset repeatedly gives: " << endl;
    for (int i = 0; i< 40; i++) {
        //Some commented code if you want to run a speedtest on getting offsets. STARTING AND STOPPING TIMER TAKES ~40ns

        //start = std::chrono::high_resolution_clock::now();
        Point offsets = scan.getOffset();
        //finish = std::chrono::high_resolution_clock::now();
        //std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns" << std::endl;
        //std::cout << offsets.getX() << "," << offsets.getY() << endl;
        std::cout << offsets.getX() << "," << offsets.getY() << endl;
    }

    //Demonstrate mutability
    std::cout << "Changing angle generation preferences: " << endl;
    scan.setSunPixelDiameter(100);
    scan.setSensorWidth(1020);
    scan.setSensorHeight(512);
    std::cout << "Showing changed angles: " << endl;
    //Reprint for the new changed angles
    scan.printAngles();

    std::cout << "Disabling scan, will now return 0 when called to scan: " << endl;
    //Will now return 0 if called:
    scan.disableScan();
    for (int i = 0; i<3; i++) {
        Point offsets = scan.getOffset();
        std::cout << offsets.getX() << "," << offsets.getY() << endl;
    }
    return(0);
}
