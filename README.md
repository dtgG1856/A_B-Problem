# A_B Problem 为 A+B Problem 的实验升级版.

## Demo 功能 

支持 `+` `-` $\times$ `mod` `xor` `gcd` `sin` `cos` `or` 共 9 种运算, 其中 `sin` `cos` 支持小数运算, 其它 7 种运算仅支持整数运算 **(范围为 $[-2^{63}, 2^{63}-1]$ , 即 `int64_t` 范围)** , 输入小数将会报错.

支持查看运算历史记录(**本地存储**).

## 使用方法

1. 直接打包这个项目中的所有文件;

2. 确保有 `CMake` 3.10 以上版本;

3. 编译: 在文件夹的 `cmd` 中, 输入:

`mkdir build && cd build`

`cmake ..`

`make`

`./server`

后台不要关闭, 浏览器打开 `www/index.html`, 即可使用.
