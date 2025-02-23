#ifndef WAITTIME_H
#define WAITTIME_H


#include <string>

// Constants
extern const int NUM_TABLES;
extern const std::string BASE_PATH;

// Function declarations

// Randomly generate dining time (range between 10 and 15 minutes)
int generateDiningTime();

// Initialize table by creating a file with table number and dining time
void initializeTable(int tableNumber);

// Simulate serving the table (waiting time + service details)
void serveTable(int tableNumber);

// The example function (could be renamed to mainSimulation or something more descriptive)
int example();


#endif // WAITTIME_H
