#ifndef DATA_WRITER_BINARY_WRITER_H
#define DATA_WRITER_BINARY_WRITER_H
#include "binaryWriter.h"
#include "dataLump.h"

using namespace std;

template<long SIZE>
class DataWriter_BinaryWriter: public BinaryWriter {
public:
    DataWriter_BinaryWriter(DataLump<SIZE>& f, const long& offset):
        BinaryWriter(f,offset), lump(f) {}
    DataWriter_BinaryWriter(DataLump<SIZE>& f):
        BinaryWriter(f), lump(f) {}

    template<class T>
    void Push_VTable(const T& object, unsigned long offset) {
        file.Write(offset,&object,sizeof(T));
    }

    template<class T>
    void Push_Static(const T& object, unsigned long offset) {
        static_cast<DataLump<SIZE>&>(file).DataLump<SIZE>::Write(
             offset,
             &object,
             sizeof(T));
    }


    template<class T>
    void Push_Dynamic(const T& object, unsigned long offset) {
        dynamic_cast<DataLump<SIZE>&>(file).DataLump<SIZE>::Write(
             offset,
             &object,
             sizeof(T));
    }
    
    template<class T>
    void Push_Direct(const T& object, unsigned long offset) {
        lump.DataLump<SIZE>::Write(
            offset,
            &object,
            sizeof(T));
    }
private:
    DataLump<SIZE>& lump;
};

#endif
