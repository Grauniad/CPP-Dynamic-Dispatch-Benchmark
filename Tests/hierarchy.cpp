#include "tester.h"
#include "data.h"
#include "csv.h"
#include <iostream>
#include <iomanip>
#include <type_traits>
#include "stdWriter.h"

using namespace std;

const long NUM_ITEMS = 65000000;

// DEPTH, DIRECT_TIME, VTABLE_TIME, DYNAMIC_TIME, VTABLE_COST, DYNAMIC_COST
using DATA_FILE = CSV<int, double, double, double, double, double>;

template<long DEPTH>
void DoTests(DATA_FILE& results);

// Loop over DoTests
template<long I>
void TestLoop(DATA_FILE& results) {
    DoTests<I>(results);
    TestLoop<I-1>(results);
}
template<>
void TestLoop<0>(DATA_FILE& results) {
    DoTests<0>(results);
}


int main(int argc, const char *argv[]) {
    DATA_FILE dataFile;

    TestLoop<10>(dataFile);
    OFStreamWriter dest("GNU.csv");
    dataFile.WriteCSV(dest);
    return 0;
}

int DIRECT(long ITEMS) {
    DATA_FILE  data;
    WriterInstance<0> w;
    DummyArray arr(ITEMS);

    for (long idx=0; idx<ITEMS; ++idx) {
        arr.WriteItem_Direct(idx,w);
    }
    return 0;
}

template<long DEPTH>
int VTABLE(long ITEMS) {
    WriterInstance<DEPTH> w;
    DummyArray arr(ITEMS);

    for (long idx=0; idx<ITEMS; ++idx) {
        arr.WriteItem_VTable(idx,w);
    }
    return 0;
}

template<long DEPTH>
int DYNAMIC(long ITEMS) {
    WriterInstance<DEPTH> w;
    DummyArray arr(ITEMS);

    for (long idx=0; idx<ITEMS; ++idx) {
        arr.WriteItem_DynamicCast(idx,w);
    }
    return 0;
}


template <long DEPTH>
void DoTests(DATA_FILE& results) {
    clock_t direct_start = clock();

    DIRECT(NUM_ITEMS);
    clock_t direct_stop = clock();

    clock_t vtable_start = clock();
    VTABLE<DEPTH>(NUM_ITEMS);
    clock_t vtable_stop = clock();

    // scale resolution to the amount of work dynamic_cast is going to take AGES to fo
    long DITEMS = NUM_ITEMS / (10*DEPTH+1); 
    clock_t dynamic_start = clock();
    DYNAMIC<DEPTH>(DITEMS);
    clock_t dynamic_stop = clock();

    cout << setprecision(2) << endl;

    cout << "**********************************************************************" << endl;
    cout << "** Hierarchy Depth: " << DEPTH << endl;
    cout << "**********************************************************************" << endl;
    double direct_time = double(direct_stop - direct_start) / CLOCKS_PER_SEC;
    double vtable_time = double(vtable_stop - vtable_start) / CLOCKS_PER_SEC;
    double dynamic_time = double(dynamic_stop - dynamic_start) / CLOCKS_PER_SEC;
    cout << "Direct took: " <<  direct_time << " seconds " << endl;
    cout << "vtable took: " <<  vtable_time << " seconds " << endl;
    cout << "dynamic_cast: " <<  dynamic_time << " seconds " << endl;

    double vtableCost = vtable_time- direct_time;
    double vtableCostPerCall = 1e9 * (vtableCost/ NUM_ITEMS);
    cout << "Additional cost to vtable loopup: " << vtableCost;
    cout << "s (" <<  vtableCostPerCall << " ns/call)" << endl;
    cout << endl;

    double dynamicCost = dynamic_time- direct_time * (double(DITEMS)/double(NUM_ITEMS));
    double dynamicCostPerCall = 1e9 * (dynamicCost/ DITEMS);
    cout << "Additional cost to dynamic_cast: " << dynamicCost;
    cout << "s (" <<  dynamicCostPerCall << " ns/call)" << endl;
    cout << endl;
    cout << "**********************************************************************" << endl;

    results.AddRow (
        DEPTH,
        direct_time + 0,
        vtable_time + 0,
        dynamic_time  +0,
        vtableCostPerCall +0,
        dynamicCostPerCall +0
    );
}
