Dynamic Dispatch in C++
=======================================

Results
=======

2013  (icc 14.0.0, g++ 4.7.3)
------------------------------
<table>
<tr>
<th colspan="3"> Additional cost of call* [nano seconds] </th>
</tr>
<tr>
    <th> Method </th> 
    <th> GNU </th> <th> INTEL </th>
</tr>
<tr>
     <td> static_casts </td>      
     <td> 0.17 ns</td> <td> 0.32 ns</td>
</tr>
<tr>
     <td> Dynamic Dispatch </td>  
     <td> 1.6 ns</td> <td> 1.7 ns</td>
</tr>
<tr>
     <td> dynamic_cast </td>      
     <td> 2.7 ns</td> <td> 0.31 ns</td>
</tr>
<tr>
<td colspan="3"> *Release flags, hiearchy depth = 127 </td>
</tr>
</table>


Results indicate the extra time required to dynamically call a function in an implementation class (WriterInstance<N>), from an interface (Writer).

The template parameter N indicates the distance in the class of hierarchy between Writer and WriterInstance.

```
WriterInstance<N>& obj  = object;
Writer& file = object;
....
// Direct Call - avoding dynamic dispatch by specifying implementation class
obj.WriterInstance<N>::Write(...);

// dynamic dispatch
file.Write(...);

// dynamic_cast - avoiding dynamic dispatch by specifying implementation class
dynamic_cast<WriterInstance<N>&>(file).WriterInstance<N>::Write(...);
....
```

Method
======
We want to know the cost of the run-time operation to resolve the correct function call, we are not measuring the raw performance of the compiler:

```
 cost_of_call = time(direct_function_call) - time(dynamic_dispatch)
```

The error involved on a single call is large, so it is repeated 0.65 Billion times, and the time averaged:

```
    ...
    clock_t startTime = clock();
    for ( RECORD i =0; i<NUM_RECORDS; i++) {
        writer.Push_VTable(i,i*sizeof(RECORD));
    }
    clock_t stopTime = clock();
    ...
```

<table>
<tr>
     <td> Hardware </td> <td> Intel(R) Core(TM) i7-2600 CPU @ 3.40GHz, 8GB DDR3 @ 1333MHz </td>
</tr>
<tr>
    <td> Intel icc version  </td> <td> icc (ICC) 14.0.0 20130728, Copyright (C) 1985-2013 Intel Corporation.  All rights reserved.
 </td>
</tr>
<tr>
    <td> icc "Release" flags </td> <td> -O2 -xHost </td>
</tr>
<tr>
    <td> icc "Fast" flags </td> <td> -fast </td>
</tr>

<tr>
     <td> GNU g++ version </td> <td> g++ (Ubuntu/Linaro 4.7.3-1ubuntu1) 4.7.3, Copyright © 2012 Free Software Foundation, Inc. </td>
</tr>
<tr>
    <td> g++ "Release" flags </td> <td> -O2 -march=native </td>
</tr>
<tr>
    <td> g++ "Fast" flags </td> <td> -Ofast -march=native </td>
</tr>
</table>
(Additionally all compilations are done with -Wall -Werror)


Raw Results
-----------

<table>
<tr>
    <th> Test </th> <th> g++ (debug) </th> <th> icc (debug) </th> <th> g++ (release) </th> <th> icc (release) </th>  <th> g++ (fast) </th> <th> icc (fast) </th> 
</tr>
<tr>
    <td> Direct Function Calls </td>  
    <td> 11.57 seconds </td> <td> 11.59 seconds </td> 
    <td> 9.15 seconds </td> <td> 8.82 seconds </td> 
    <td> 9.13 seconds </td> <td> 8.49 seconds </td>
</tr>
<tr>
    <td> static_casts </td>  
    <td> 11.71 seconds </td> <td> 11.98 seconds </td> 
    <td> 9.26 seconds </td> <td> 9.03 seconds </td> 
    <td> 9.25 seconds </td> <td> 9.03 seconds </td>
</tr>
<tr>
    <td> Dynamic Dispatches </td>     
    <td> 11.71 seconds </td> <td> 12.23 seconds </td> 
    <td> 10.17 seconds </td> <td> 9.91 seconds </td> 
    <td> 10.28 seconds </td> <td> 9.96 seconds </td> 
</tr>
<tr>
    <td> dynamic_casts </td>          
    <td> 13.66 seconds </td> <td> 12.68 seconds </td> 
    <td> 10.92 seconds </td> <td> 9.02 seconds </td> 
    <td> 10.99 seconds </td> <td> 9.02 seconds </td>
</tr>
</table>

Hierarchy Depth
-------------------------
<table>
<tr>
<th> </th> 
<th colspan="2"> Hierarchy Depth = 127 </th>
<th colspan="2"> Hierarchy Depth = 63 </th>
<th colspan="2"> Hierarchy Depth = 30 </th>
<th colspan="2"> Hierarchy Depth = 15 </th>
<th colspan="2"> Hierarchy Depth = 7 </th>
</tr>
<tr>
    <th> Method </th> 
    <th> GNU </th> <th> INTEL </th>
    <th> GNU </th> <th> INTEL </th>
    <th> GNU </th> <th> INTEL </th>
    <th> GNU </th> <th> INTEL </th>
    <th> GNU </th> <th> INTEL </th>
</tr>
<tr>
     <td> static_casts </td>      
     <td> 0.17ns </td> <td> 0.32ns </td>
     <td> 0ns </td> <td> 0.26ns </td>
     <td> 0ns </td> <td> 0ns </td>
     <td> 0ns </td> <td> 0ns </td>
     <td> 0ns </td> <td> 0.35ns </td>
</tr>
<tr>
     <td> Dynamic Dispatch </td>  
     <td> 1.6ns </td> <td> 1.7ns </td>
     <td> 0.49ns </td> <td> 0.69ns </td>
     <td> 0.29ns </td> <td> 0.28ns </td>
     <td> 0.58ns </td> <td> 0.83ns </td>
     <td> 0.87ns </td> <td> 1.7ns </td>
</tr>
<tr>
     <td> dynamic_cast </td>      
     <td> 2.7ns </td> <td> 0.31ns </td>
     <td> 4.7ns </td> <td> 0.23ns </td>
     <td> 6.9ns </td> <td> 0ns </td>
     <td> 7.5ns </td> <td> 0.17ns </td>
     <td> 5.5ns </td> <td> 0.66ns </td>
</tr>
</table>
Usage
=====

Clone the repositry, (recursive is required to clone the submodules)

```
git clone --recursive https://github.com/Grauniad/CPP-Dynamic-Dispatch-Speed.git
```

Running make will trigger all build tests (including the final benchmark test)

Debug build:
```
make -j <cores>
```

Optimized build:

```
make -j <cores> release
```

Fast build:

```
make -j <cores> fast
```
