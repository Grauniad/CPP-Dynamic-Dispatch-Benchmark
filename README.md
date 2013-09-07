CPP-Dynamic-Dispatch-Speed
==========================

Simple test of vtable / dynamic_cast lookup times in C++

Results
=======

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
