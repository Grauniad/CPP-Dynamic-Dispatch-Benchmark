#include "data.h"

DummyArray::DummyArray(long items) {
    data.reserve(items);
}

void DummyArray::WriteItem_Direct(long idx, WriterInstance<0>& w) {
    data[idx] = w.WriterInstance<0>::Depth();
}

void DummyArray::WriteItem_VTable(long idx, Writer& w) {
    data[idx] = w.Depth();
}

void DummyArray::WriteItem_DynamicCast(long idx, Writer& w) {
    dynamic_cast<WriterInstance<0>&>(w).WriterInstance<0>::Depth();
}
