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
#include <iomanip>

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
    Test directTest("Initialising store using direct access...",  (loggedTest)DIRECT);
    Test staticCastTest("Initialising store using static_cast...",  (loggedTest)STATIC);
    Test vtableTest("Initialising store using vtable...",  (loggedTest)VTABLE);
    Test dynamicCastTest("Initialising store using dynamic_cast...",  (loggedTest)DYNAMIC);
    directTest.RunTest();
    staticCastTest.RunTest();
    vtableTest.RunTest();
    dynamicCastTest.RunTest();

    cout << setprecision(2) << endl;

    cout << "Total number of function calls for each test: " << double(NUM_RECORDS)/1e9 << " billion" << endl;
    cout << endl;

    double staticCost = staticCastTest.RunTime() - directTest.RunTime();
    cout << "Additional cost to static Cast: " << staticCost;
    cout << "s (" << 1e9 * (staticCost/ NUM_RECORDS) << " ns/call)" << endl;
    cout << endl;

    double vtableCost = vtableTest.RunTime() - directTest.RunTime();
    cout << "Additional cost to vtable loopup: " << vtableCost;
    cout << "s (" << 1e9 * (vtableCost/ NUM_RECORDS) << " ns/call)" << endl;
    cout << endl;

    double dynamicCost = dynamicCastTest.RunTime() - directTest.RunTime();
    cout << "Additional cost to dynamic_cast: " << dynamicCost;
    cout << "s (" << 1e9 * (dynamicCost/ NUM_RECORDS) << " ns/call)" << endl;
    cout << endl;

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
