#include "tester.h"
#include "data.h"
#include <iostream>
#include <iomanip>

using namespace std;

int DIRECT(testLogger& log);
int STATIC(testLogger& log);
int DYNAMIC(testLogger& log);
int VTABLE(testLogger& log);

#define NUM_WRITERS 127
#define NUM_ITEMS 650000000
using DATA_TYPE = Data<NUM_ITEMS,NUM_WRITERS>;

int main(int argc, const char *argv[]) {
    Test directTest("Initialising store using direct access...",  (loggedTest)DIRECT);
    Test staticCastTest("Initialising store using static_cast...",  (loggedTest)STATIC);
    Test vtableTest("Initialising store using vtable...",  (loggedTest)VTABLE);
    Test dynamicCastTest("Initialising store using dynamic_cast...",  (loggedTest)DYNAMIC);
    directTest.RunTest();
    staticCastTest.RunTest();
    vtableTest.RunTest();
    dynamicCastTest.RunTest();

    cout << setprecision(2) << endl;

    cout << "Total number of function calls for each test: " << double(NUM_ITEMS)/1e9 << " billion" << endl;
    cout << endl;

    double staticCost = staticCastTest.RunTime() - directTest.RunTime();
    cout << "Additional cost to static Cast: " << staticCost;
    cout << "s (" << 1e9 * (staticCost/ NUM_ITEMS) << " ns/call)" << endl;
    cout << endl;

    double vtableCost = vtableTest.RunTime() - directTest.RunTime();
    cout << "Additional cost to vtable loopup: " << vtableCost;
    cout << "s (" << 1e9 * (vtableCost/ NUM_ITEMS) << " ns/call)" << endl;
    cout << endl;

    double dynamicCost = dynamicCastTest.RunTime() - directTest.RunTime();
    cout << "Additional cost to dynamic_cast: " << dynamicCost;
    cout << "s (" << 1e9 * (dynamicCost/ NUM_ITEMS) << " ns/call)" << endl;
    cout << endl;
}

int Validate(DATA_TYPE& d, testLogger& log) {
    for ( long l =0; l<d.ITEMS; l++ ) {
        if ( d.Get(l) != l % (d.WRITERS+1) ) {
            log << "Missmatch at index " << l << endl;
            log << "Expected: " << int( l % (NUM_WRITERS+1)) << endl;
            log << "Got: " << int(d.Get(l)) << endl;
            return 1;
        }
    }
    return 0;
}

template<char N>
void DoDirect(DATA_TYPE& d) {
    for ( long idx =N; idx< NUM_ITEMS; idx+=(NUM_WRITERS+1)) {
        d.WriteItem_Direct(idx);
    }
    DoDirect<N-1>(d);
}
template <>
void DoDirect<0>(DATA_TYPE&d) {
    for ( long idx=0; idx<NUM_ITEMS; idx+=(NUM_WRITERS+1)) {
        d.WriteItem_Direct(idx);
    }
}
int DIRECT(testLogger& log ) {
    DATA_TYPE store;
    DoDirect<NUM_WRITERS>(store);
    return 0;
}

template<char N>
void DoStatic(DATA_TYPE& d) {
    for ( long idx =N; idx< NUM_ITEMS; idx+=(NUM_WRITERS+1)) {
        d.WriteItem_StaticCast<N>(idx);
    }
    DoStatic<N-1>(d);
}
template <>
void DoStatic<0>(DATA_TYPE&d) {
    for ( long idx=0; idx<NUM_ITEMS; idx+=(NUM_WRITERS+1)) {
        d.WriteItem_StaticCast<0>(idx);
    }
}
int STATIC(testLogger& log ) {
    DATA_TYPE store;
    DoStatic<NUM_WRITERS>(store);
    return 0;
}

template<char N>
void DoDynamic(DATA_TYPE& d) {
    for ( long idx =N; idx< NUM_ITEMS; idx+=(NUM_WRITERS+1)) {
        d.WriteItem_DynamicCast<N>(idx);
    }
    DoDynamic<N-1>(d);
}
template <>
void DoDynamic<0>(DATA_TYPE&d) {
    for ( long idx=0; idx<NUM_ITEMS; idx+=(NUM_WRITERS+1)) {
        d.WriteItem_DynamicCast<0>(idx);
    }
}
int DYNAMIC(testLogger& log ) {
    DATA_TYPE store;
    DoDynamic<NUM_WRITERS>(store);
    return 0;
}

template<char N>
void DoVTable(DATA_TYPE& d) {
    for ( long idx =N; idx< NUM_ITEMS; idx+=(NUM_WRITERS+1)) {
        d.WriteItem_VTable(idx);
    }
    DoVTable<N-1>(d);
}
template <>
void DoVTable<0>(DATA_TYPE&d) {
    for ( long idx=0; idx<NUM_ITEMS; idx+=(NUM_WRITERS+1)) {
        d.WriteItem_VTable(idx);
    }
}
int VTABLE(testLogger& log ) {
    DATA_TYPE store;
    DoVTable<NUM_WRITERS>(store);
    return 0;
}


