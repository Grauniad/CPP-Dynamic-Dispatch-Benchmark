#include <cstring>
#include <ctime>
#include <iostream>
#include "dataLump.h"
#include "tester.h"
#include "fileLikeObject.h"
#include <sstream>
#include <cmath>
#include <memory>
#include "dataWriter_BinaryWriter.h"

using namespace std;
const long BILLION = 1e9; 
const unsigned long NUM_RECORDS = 650000000;

// Tests
int BENCHMARK(testLogger& log);
int DIRECT(testLogger& log);
int STATIC(testLogger& log);
int VTABLE(testLogger& log);
int DYNAMIC(testLogger& log);

using RECORD = unsigned long;

using DATA_STORE = DataLump<sizeof(RECORD)*NUM_RECORDS>;
using WRITER = DataWriter_BinaryWriter<sizeof(RECORD)*NUM_RECORDS>;

unique_ptr<DATA_STORE> store(new DATA_STORE);


int main(int argc, const char *argv[]) {
    Test("Running benchmark...",  (loggedTest)BENCHMARK).RunTest();
    Test("Initialising store using direct access...",  (loggedTest)DIRECT).RunTest();
    Test("Initialising store using static_cast...",  (loggedTest)STATIC).RunTest();
    Test("Initialising store using vtable...",  (loggedTest)VTABLE).RunTest();
    Test("Initialising store using dynamic_cast...",  (loggedTest)DYNAMIC).RunTest();
    return 0;
}

int BENCHMARK(testLogger& log) {
    for ( RECORD i =0; i<NUM_RECORDS; i++) {
        memcpy(store->RawPtr()+i*sizeof(RECORD),&i,sizeof(RECORD));
    }
    return 0;
}
int DIRECT(testLogger& log) {
    WRITER writer(*store);
    for ( RECORD i =0; i<NUM_RECORDS; i++) {
        writer.Push_Direct(i,i*sizeof(RECORD));
    }
    return 0;
}

int VTABLE(testLogger& log) {
    WRITER writer(*store);
    for ( RECORD i =0; i<NUM_RECORDS; i++) {
        writer.Push_VTable(i,i*sizeof(RECORD));
    }
    return 0;
}

int STATIC(testLogger& log) {
    WRITER writer(*store);
    for ( RECORD i =0; i<NUM_RECORDS; i++) {
        writer.Push_Static(i,i*sizeof(RECORD));
    }
    return 0;
}

int DYNAMIC(testLogger& log) {
    WRITER writer(*store);
    for ( RECORD i =0; i<NUM_RECORDS; i++) {
        writer.Push_Dynamic(i,i*sizeof(RECORD));
    }
    return 0;
}
