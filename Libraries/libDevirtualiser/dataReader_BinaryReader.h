#ifndef DATA_READER_BINARY_READER_H
#define DATA_READER_BINARY_READER_H
#include "binaryReader.h"
#include "dataLump.h"

using namespace std;

template<long SIZE>
class DataReader_BinaryReader: public BinaryReader {
public:
    DataReader_BinaryReader(const DataLump<SIZE>& f, const long& offset):
        BinaryReader(f,offset){}
    DataReader_BinaryReader(const DataLump<SIZE>& f):
        BinaryReader(f) {}

    // Access data
    void Read_VTable(void *dest, long size) const {
        file.Read(offset,dest,size);
    }
    void Read_Static(void *dest, long size) const {
        static_cast<DataLump<SIZE>>(file)::DataLump<SIZE>::Read(offset,dest,size);
    }
    void Read_Dynamic(void *dest, long size) const {
        dynamic_cast<DataLump<SIZE>>(file)::DataLump<SIZE>::Read(offset,dest,size);
    }
};

#endif
