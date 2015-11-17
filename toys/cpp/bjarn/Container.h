#ifndef _CONTAINER_H_
#define _CONTAINER_H_

class Container {
public:
    virtual double& operator[](int) = 0;
    virtual int size() const = 0;
    virtual ~Container(){}
};


#endif
