#ifndef DATA_H
#define DATA_H

#include <vector>

using namespace std;

class Writer {
public:
    virtual void Write(char &dest) = 0;
    virtual ~Writer() {}
};

template<char N> 
class WriterInstance: public WriterInstance<N-1> {
public:
    WriterInstance(): data(N) {}

    virtual void Write(char &dest) {
        dest = data;
    }
    virtual ~WriterInstance() {}
private:
    char data;
};

template<>
class WriterInstance<0>: public Writer {
public:
    WriterInstance(): data(0) {}

    virtual void Write(char &dest) {
        dest = data;
    }
    virtual ~WriterInstance() {}
private:
    char data;
};

template<long items, char N>
class Data {
public:
    Data();
    const long ITEMS = items;
    const char WRITERS = N;
    char Get(long i) { 
        return dest[i];
    }

    inline void WriteItem_VTable(long idx) {
        writers[idx%(N+1)]->Write(*(dest+idx));
    }

    template<char I>
    inline void WriteItem_StaticCast(long idx) {
        using INSTANCE = WriterInstance<I>;
        static_cast<INSTANCE*>(writers[idx%(N+1)])->INSTANCE::Write(
            *(dest+idx)
        );
    }

    template<char I>
    inline void WriteItem_DynamicCast(long idx) {
        using INSTANCE = WriterInstance<I>;
        dynamic_cast<INSTANCE*>(writers[idx%(N+1)])->INSTANCE::Write(
            *(dest+idx)
        );
    }

    inline void WriteItem_Direct(long idx) {
        w.WriterInstance<0>::Write(*(dest+idx));
    }

    ~Data() {
        delete [] dest;
        for ( Writer* w: writers) {
            delete w;
       }
    }
private:
    char * dest;
    vector<Writer *> writers;
    WriterInstance<0> w;
};


#include "data.hpp"

#endif
