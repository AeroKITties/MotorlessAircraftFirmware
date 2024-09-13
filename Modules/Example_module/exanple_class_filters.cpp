#include "Vectors.h"
#include "example_class.hpp"
#include "stm32f4xx_hal.h"


bool is_deltas_trend(std::vector<double> a){
    int positiv_deltas_mount = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i+1] - a[i] >= 0)
            positiv_deltas_mount += 1;       
    }
    if ((positiv_deltas_mount >= (a.size())*0.85 || positiv_deltas_mount < (a.size())*0.15) && abs(a[0] - a[1] > 0.4))
        return 1;
    return 0;
}

double get_weight_average(std::vector<double> a, int d)
{
    int num = a.size();
    double weighted_average = 0;
    double s = 0;
    for (int i=num-1;i >= num-d; i--){
        
        weighted_average += pow(2, -(i+1)) * a[i];
        s += pow(2, -(i+1));
    } 
    weighted_average /= s;
    return weighted_average;
}

double get_average(std::vector<double> a, int d)
{
    int num = a.size();
    double average = 0;
    for (int i=num-d;i < num; i++)
        average += pow(num, -1) * a[i];
    return average;
}

double crop_double(double d){
    double n = int(d);
    if (d - int(d) > 0.6) { n += 0.6; }
    else if (d - int(d) > 0.3) { n += 0.3; }
    else { n += 0; }
    return n;
}

double ExampleClass::AccelFilter(std::vector<double> & accel_history, double new_elem, bool make_discret)
{
    accel_history.push_back(new_elem);
    int max_gap = accel_x_history.size();
    double min_gap = f*0.05;
    if (min_gap > max_gap) {min_gap = 1;}
    static int d = max_gap;

    int counter_max_gap = 0;
    if (is_deltas_trend(accel_history))
    {
        d -= 1; 
        counter_max_gap = 0;
        if (d < min_gap)
            d = min_gap;
    }
    else{
        d += 1;
        if (d > max_gap)
        {
            counter_max_gap += 1;
            d = max_gap;
        }
    }
/*    if (counter_max_gap > f/2)
        new_elem = get_average(accel_history, d); 
    else
        new_elem = get_weight_average(accel_history, d); */
    if (make_discret){
        double n;
        new_elem = get_average(accel_history, d); 
        if (new_elem - int(new_elem) < 0.3){
            n = new_elem - int(new_elem);
        }
        else if (new_elem - int(new_elem) < 0.6){
            n = new_elem - int(new_elem) + 0.4;
        }
        else{
            n = new_elem -= int(new_elem) + 0.8;
        }
        new_elem = n;
    }

    accel_history.erase(accel_history.begin());
    return new_elem;
}


void ExampleClass::EnableFilter()
{
    f_filter = 1;
}

void ExampleClass::DisableFilter()
{
    f_filter = 0;
}

void ExampleClass::Filter()
{
    if (f_filter){
        accel = Vector3{AccelFilter(accel_x_history, accel.x, 1), AccelFilter(accel_y_history, accel.y, 1), AccelFilter(accel_z_history, accel.z, 1)};
        gyro = Vector3{AccelFilter(gyro_x_history, gyro.x), AccelFilter(gyro_y_history, gyro.y), AccelFilter(gyro_z_history, gyro.z)};
    }
}