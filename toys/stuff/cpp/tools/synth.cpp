#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>

// same as SynthFrames.py -- except this one needs updating
//
using namespace std;

vector<string> split(const string& s)
{
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;
    while (i != s.size()) {
        while (i != s.size() && isspace(s[i]))
            ++i;
        string_size j = i;
        while (j != s.size() && !isspace(s[j]))
            ++j;
        if (i != j) {
            ret.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}

#define SAMPLE_SIZE 8 // frames
double cal_running_avg_dbl(double avg, double new_sample) 
{
    if (fabs(avg) > 0.0) {
        avg -= avg / SAMPLE_SIZE;
    }
    avg += new_sample / SAMPLE_SIZE;
    return avg;
}

double denoise(double angle)
{
    static double avg = 0.0, err = 0.0;
    avg = cal_running_avg_dbl(avg, angle);
    err = fabs(avg-angle);
    //cout << "raw: " << angle << ", avg: " << avg << ", err: " << err << endl;
    return avg;
}

int main()
{
    string line;
    bool skip = false;
    int frame = 0;
    int yval = 0;
    float angle = 0.0;
    double avg = 0.0, err = 0.0;
    int prev_frame = -1;
    while(getline(cin, line)) {
        if (!skip) {
            vector<string> entry = split(line);
            if (!entry.empty()) {
                frame = strtol(entry[0].c_str(), NULL, 0);
                yval  = strtol(entry[1].c_str(), NULL, 0);
                angle = strtof(entry[2].c_str(), NULL);
            }
        }
        skip = false;
        if (prev_frame == -1) {
            prev_frame = frame;
        } else 
        if (frame != prev_frame+1) {
            //cout << "missing frame: " << prev_frame+1 << endl;
            frame = prev_frame+1;
            skip = true;
            continue;
        } else {
            prev_frame = frame;
        }
        double avg_angle = denoise(angle);
        printf("%d, %d, %0.2lf\n", frame, yval, avg_angle);
    }
}

