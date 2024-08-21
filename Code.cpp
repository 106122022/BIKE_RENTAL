#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <algorithm>

using namespace std;

// Structure to represent a bike rental station
struct BikeRental {
    int id;
    int x, y;
    vector<char> models;
    int totalCost;
    int duration;
    bool safety;

    double avgCost() const {
        return totalCost / static_cast<double>(models.size());
    }
};

// Structure for priority queue to sort by distance
struct Compare {
    bool operator()(pair<int, int>& a, pair<int, int>& b) {
        return a.second > b.second;
    }
};

// Function to calculate Manhattan distance
int manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

// Dijkstra's algorithm to find shortest paths
vector<int> dijkstra(int n, vector<vector<int>>& adjMatrix, int src) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    pq.push({src, 0});

    while (!pq.empty()) {
        int u = pq.top().first;
        int d = pq.top().second;
        pq.pop();

        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                pq.push({v, dist[v]});
            }
        }
    }

    return dist;
}

// Function to check if bike rental matches user's specifications
bool matchesSpecifications(const BikeRental& rental, const vector<char>& requiredModels, int maxCost, int minDuration, bool requireSafety) {
    for (char model : requiredModels) {
        if (find(rental.models.begin(), rental.models.end(), model) == rental.models.end()) {
            return false;
        }
    }
    if (rental.avgCost() > maxCost) return false;
    if (rental.duration < minDuration) return false;
    if (requireSafety && !rental.safety) return false;
    return true;
}

int main() {
    // Number of bike rentals
    int n = 100;
    vector<BikeRental> rentals(n);


    rentals = {
        {0, 10, 20, {'A', 'B'}, 400, 72, true},
        {1, 15, 30, {'A', 'C'}, 500, 48, false},
        {2, 20, 40, {'B', 'C'}, 300, 96, true},
        {3, 25, 50, {'A'}, 200, 24, true},
        {4, 30, 60, {'B'}, 600, 72, false},
        {5, 35, 70, {'C'}, 450, 48, true},
        {6, 40, 80, {'A', 'B', 'C'}, 500, 120, false},
        {7, 45, 90, {'A'}, 250, 60, true},
        {8, 50, 100, {'B', 'C'}, 350, 72, true},
        {9, 55, 110, {'A', 'C'}, 400, 96, false},
        {10, 60, 120, {'A', 'B'}, 450, 48, true},
        {11, 65, 130, {'C'}, 300, 72, false},
        {12, 70, 140, {'A'}, 500, 60, true},
        {13, 75, 150, {'B', 'C'}, 550, 96, true},
        {14, 80, 160, {'A', 'B'}, 600, 48, false},
        {15, 85, 170, {'C'}, 650, 72, true},
        {16, 90, 180, {'A', 'C'}, 700, 120, false},
        {17, 95, 190, {'B'}, 750, 96, true},
        {18, 100, 200, {'A', 'B'}, 800, 60, true},
        {19, 105, 210, {'C'}, 850, 72, false},
        {20, 110, 220, {'A'}, 900, 48, true},
        {21, 115, 230, {'B', 'C'}, 950, 96, false},
        {22, 120, 240, {'A', 'B'}, 1000, 120, true},
        {23, 125, 250, {'C'}, 1050, 60, true},
        {24, 130, 260, {'A'}, 1100, 72, false},
        {25, 135, 270, {'B', 'C'}, 1150, 96, true},
        {26, 140, 280, {'A', 'B'}, 1200, 48, true},
        {27, 145, 290, {'C'}, 1250, 72, false},
        {28, 150, 300, {'A'}, 1300, 120, true},
        {29, 155, 310, {'B', 'C'}, 1350, 96, true},
        {30, 160, 320, {'A', 'B'}, 1400, 60, false},
        {31, 165, 330, {'C'}, 1450, 72, true},
        {32, 170, 340, {'A', 'C'}, 1500, 48, true},
        {33, 175, 350, {'B'}, 1550, 96, false},
        {34, 180, 360, {'A', 'B'}, 1600, 120, true},
        {35, 185, 370, {'C'}, 1650, 60, true},
        {36, 190, 380, {'A'}, 1700, 72, false},
        {37, 195, 390, {'B', 'C'}, 1750, 96, true},
        {38, 200, 400, {'A', 'B'}, 1800, 48, true},
        {39, 205, 410, {'C'}, 1850, 72, false},
        {40, 210, 420, {'A'}, 1900, 120, true},
        {41, 215, 430, {'B', 'C'}, 1950, 96, true},
        {42, 220, 440, {'A', 'B'}, 2000, 60, false},
        {43, 225, 450, {'C'}, 2050, 72, true},
        {44, 230, 460, {'A', 'C'}, 2100, 48, true},
        {45, 235, 470, {'B'}, 2150, 96, false},
        {46, 240, 480, {'A', 'B'}, 2200, 120, true},
        {47, 245, 490, {'C'}, 2250, 60, true},
        {48, 250, 500, {'A'}, 2300, 72, false},
        {49, 255, 510, {'B', 'C'}, 2350, 96, true},
        {50, 260, 520, {'A', 'B'}, 2400, 48, true},
        {51, 265, 530, {'C'}, 2450, 72, false},
        {52, 270, 540, {'A'}, 2500, 120, true},
        {53, 275, 550, {'B', 'C'}, 2550, 96, true},
        {54, 280, 560, {'A', 'B'}, 2600, 60, false},
        {55, 285, 570, {'C'}, 2650, 72, true},
        {56, 290, 580, {'A', 'C'}, 2700, 48, true},
        {57, 295, 590, {'B'}, 2750, 96, false},
        {58, 300, 600, {'A', 'B'}, 2800, 120, true},
        {59, 305, 610, {'C'}, 2850, 60, true},
        {60, 310, 620, {'A'}, 2900, 72, false},
        {61, 315, 630, {'B', 'C'}, 2950, 96, true},
        {62, 320, 640, {'A', 'B'}, 3000, 48, true},
        {63, 325, 650, {'C'}, 3050, 72, false},
        {64, 330, 660, {'A'}, 3100, 120, true},
        {65, 335, 670, {'B', 'C'}, 3150, 96, true},
        {66, 340, 680, {'A', 'B'}, 3200, 60, false},
        {67, 345, 690, {'C'}, 3250, 72, true},
        {68, 350, 700, {'A', 'C'}, 3300, 48, true},
        {69, 355, 710, {'B'}, 3350, 96, false},
        {70, 360, 720, {'A', 'B'}, 3400, 120, true},
        {71, 365, 730, {'C'}, 3450, 60, true},
        {72, 370, 740, {'A'}, 3500, 72, false},
        {73, 375, 750, {'B', 'C'}, 3550, 96, true},
        {74, 380, 760, {'A', 'B'}, 3600, 48, true},
        {75, 385, 770, {'C'}, 3650, 72, false},
        {76, 390, 780, {'A'}, 3700, 120, true},
        {77, 395, 790, {'B', 'C'}, 3750, 96, true},
        {78, 400, 800, {'A', 'B'}, 3800, 60, false},
        {79, 405, 810, {'C'}, 3850, 72, true},
        {80, 410, 820, {'A', 'C'}, 3900, 48, true},
        {81, 415, 830, {'B'}, 3950, 96, false},
        {82, 420, 840, {'A', 'B'}, 4000, 120, true},
        {83, 425, 850, {'C'}, 4050, 60, true},
        {84, 430, 860, {'A'}, 4100, 72, false},
        {85, 435, 870, {'B', 'C'}, 4150, 96, true},
        {86, 440, 880, {'A', 'B'}, 4200, 48, true},
        {87, 445, 890, {'C'}, 4250, 72, false},
        {88, 450, 900, {'A'}, 4300, 120, true},
        {89, 455, 910, {'B', 'C'}, 4350, 96, true},
        {90, 460, 920, {'A', 'B'}, 4400, 60, false},
        {91, 465, 930, {'C'}, 4450, 72, true},
        {92, 470, 940, {'A', 'C'}, 4500, 48, true},
        {93, 475, 950, {'B'}, 4550, 96, false},
        {94, 480, 960, {'A', 'B'}, 4600, 120, true},
        {95, 485, 970, {'C'}, 4650, 60, true},
        {96, 490, 980, {'A'}, 4700, 72, false},
        {97, 495, 990, {'B', 'C'}, 4750, 96, true},
        {98, 500, 1000, {'A', 'B'}, 4800, 48, true},
        {99, 505, 1010, {'C'}, 4850, 72, false},
    };

    // Adjacency matrix representing distances between rentals (Manhattan distance)
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            adjMatrix[i][j] = manhattanDistance(rentals[i].x, rentals[j].x, rentals[i].y, rentals[j].y);
        }
    }

    // User input: Location
    int userX, userY;
    cout << "Enter your location (x, y): ";
    cin >> userX >> userY;

    // User input: Specifications
    vector<char> requiredModels;
    cout << "Enter required bike models (A, B, C). Type '0' to end input: ";
    char model;
    while (cin >> model && model != '0') {
        requiredModels.push_back(model);
    }

    int maxCost;
    cout << "Enter the maximum average cost you're willing to pay: ";
    cin >> maxCost;

    int minDuration;
    cout << "Enter the minimum rental duration you need (in hours): ";
    cin >> minDuration;

    bool requireSafety;
    cout << "Do you require safety features (helmet, lights, etc.)? Enter 1 for Yes, 0 for No: ";
    cin >> requireSafety;

    // Calculate distances from the user's location to each bike rental
    vector<int> dist(n);
    for (int i = 0; i < n; ++i) {
        dist[i] = manhattanDistance(userX, userY, rentals[i].x, rentals[i].y);
    }

    // Priority queue to sort rentals by distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

    for (int i = 0; i < n; ++i) {
        if (matchesSpecifications(rentals[i], requiredModels, maxCost, minDuration, requireSafety)) {
            pq.push({i, dist[i]});
        }
    }

    // Display results
    int f = 0;
    cout << "\nBike rentals sorted by distance (nearest first):\n";
    while (!pq.empty()) {
        int rentalId = pq.top().first;
        cout << "Rental ID: " << rentalId 
             << ", Distance: " << pq.top().second 
             << ", Avg Cost: " << rentals[rentalId].avgCost() 
             << ", Duration: " << rentals[rentalId].duration 
             << ", Safety: " << (rentals[rentalId].safety ? "Yes" : "No") 
             << endl;
        pq.pop();
        f = 1;
    }
    // If no matching Rental is found
    if(f == 0){
        cout << "Sorry we donot find any matching Rentals Try again!!!" << endl;
    }

    return 0;
}
