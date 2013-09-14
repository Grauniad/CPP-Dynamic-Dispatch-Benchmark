Dynamic Dispatch in C++ [![Build Status](https://travis-ci.org/Grauniad/CPP-Dynamic-Dispatch-Benchmark.png)](https://travis-ci.org/Grauniad/CPP-Dynamic-Dispatch-Benchmark)
=======================================

Results
=======

2013  (icc 14.0.0, g++ 4.7.3)
------------------------------
Pending

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
Pending

Hierarchy Depth
-------------------------
Pending

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
