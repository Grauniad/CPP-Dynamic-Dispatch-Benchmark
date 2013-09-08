CPP-Dynamic-Dispatch-Speed
==========================

Simple test of vtable / dynamic_cast lookup times in C++

Results
=======

2013  (icc 14.0.0, g++ 4.7.3)
------------------------------

<table>
   <tr>
       <th> Test </th> <th> "Debug" cost of call </th> <th> "Release" cost of call </th> <th> "Fast" cost of call </th>
   </tr>
   <tr>
       <td> VTable (GNU)   </td> <td> 0 </td> <td> 2.9ns </td> <td> 3.5ns </td>

   </tr>
   <tr>
       <td> VTable (INTEL) </td> <td> 0 </td> <td> 2.6ns </td> <td> 3.4ns </td>
   </tr>
    <tr>
       <td> dynamic_cast (GNU)   </td>  <td> 6.7ns </td>  <td> 8.2ns </td> <td> 9.5ns </td>

   </tr>
   <tr>
       <td> dynamic_cast (INTEL) </td> <td>6.6ns </td> <td> 0.25ns </td> <td> 2ns </td>
   </tr>
</table>

Method
======

We want to know the cost of the run-time operation to resolve the correct function call. 
This is always going to be tiny, sot the called funtion must do a *TINY* amount of work in order for this to be significant.
(In this case the function does a memcpy of sizeof(long) ).

It is also important to note that we are not interested (in this case) of the overall performance of the compiler, we just want the cost of dynamic dispatch.


```
 cost_of_call = time(direct_function_call) - time(dynamic_dispatch)
```

The error involved on a single call is clearly ludicrous, so it is repeated 0.65 Billion times, and the time averaged:

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


Raw Results
-----------



Usage
=====

Clone the repositry, (recursive is required to clone the submodules)

```
git clone --recursive git@github.com:Grauniad/CPP-Dynamic-Dispatch-Speed.git
```

Running make will trigger all build tests (including the final benchmark test)

Debug build:
```
make 
```

Optimized build:

```
make release
```
