# hash-accelerated
Use hash table to store the result of expensive function calls and accelerate your simulation procedures. This is useful whwn the function call is expensive. But the precision of the result might lost when the parameters of the function is a real number (i.e., float). This is because the library will discretize the float number according to the user-defined lower limit, upper limit and the grid size. The function values on the grids will be exactly computed and stored. While those that do not locate exactly on the grid points will be retrieved according to neighbouring grid points based on a certain interpolation strategy.

![alt tag](https://github.com/zhongjingjogy/hash-accelerated/blob/master/demos/demo1/result.png)
