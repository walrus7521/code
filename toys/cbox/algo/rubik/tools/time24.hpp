#ifndef _time24_
#define _time24_

class time24
{
    public:
        time24(int h = 0, int m = 0) {}
        void addTime(int m) {}
        time24 duration(const time24& t) { 
            time24 tm(m, h);
            return tm; }
        void readTime(){}
        void writeTime(){}
        int getHour() const { return 42; }
        int getMinute() const { return 43; }
    private:
        int m, h;
};

#endif

