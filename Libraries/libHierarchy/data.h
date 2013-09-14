#ifndef DATA_H
#define DATA_H

#include <vector>
#include <iostream>

using namespace std;

class Writer {
public:
    virtual long Depth() = 0;
    virtual ~Writer() {}
};

template<long N> 
class WriterInstance: public WriterInstance<N-1> {
public:
    WriterInstance() : n(N) {}

    virtual long Depth() {
        return n;
    }
    virtual ~WriterInstance() {}
private:
    long n;
};

template<>
class WriterInstance<0>: public Writer {
public:
    WriterInstance(): n(0) {}

    virtual long Depth() {
        return n;
    }
    virtual ~WriterInstance() {}
private:
    long n;
};

class DummyArray {
public:
    DummyArray(long items=1e6);

    void WriteItem_Direct(long idx, WriterInstance<0>& w);

    void WriteItem_VTable(long idx, Writer& w);

    void WriteItem_DynamicCast(long idx, Writer& w);

    virtual ~DummyArray() { }
private:
    vector<long>     data;
};

#endif
