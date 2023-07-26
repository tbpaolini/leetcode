// Problem 1870 - Minimum Speed to Arrive on Time
// https://leetcode.com/problems/minimum-speed-to-arrive-on-time/description/

// On this one I used only floating point math to calculate the speed
// (this solution finished on 91% of the time than the other)

#include <math.h>

double get_time(double* dist, int distSize, double speed){
    
    double total_speed = 0;
    int i;
    
    for (i = 0; i < distSize - 1; i++)
    {
        total_speed += ceil(dist[i] / speed);
    }
    
    return total_speed + (dist[i] / speed);
}

int minSpeedOnTime(int* dist, int distSize, double hour){
    
    if (hour <= distSize - 1) return -1;

    double dist_f[distSize];
    for (int i = 0; i < distSize; i++)
    {
        dist_f[i] = dist[i];
    }
    
    int min_speed = 1;
    int max_speed = 1e7;
    
    int target_speed = -1;
    
    while (min_speed <= max_speed)
    {
        const int mid_speed = (min_speed + max_speed) / 2;
        const double mid_time = get_time(dist_f, distSize, mid_speed);
        
        if (mid_time <= hour)
        {
            target_speed = mid_speed;
            max_speed = mid_speed - 1;
        }
        else
        {
            min_speed = mid_speed + 1;
        }
    }
    
    return target_speed;
}