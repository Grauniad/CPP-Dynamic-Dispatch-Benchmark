template<char N>
void AddWriter(vector<Writer * >& arr) {
    arr[N] = new WriterInstance<N>();
   AddWriter<N-1>(arr);
}

template<>
void AddWriter<0>(vector<Writer *>& arr) {
    arr[0] = new WriterInstance<0>();
}

template<long items, char N>
Data<items,N>::Data() {
    dest = new char[items];
    writers.resize(N+1);
    AddWriter<N>(writers);
    for ( long i =0; i< items; i++ ) {
        dest[i] = -1;
    }
}
