# A_B Problem 为 A+B Problem 的升级版.

## 项目功能 

支持 + - $\times$ `mod` `xor` `gcd` `sin` `cos` `or` 九种运算, 其中 + - $\times$ `mod` `sin` `cos` 支持小数运算, `xor` `gcd` `or` 仅支持整数运算, 输入小数将会报错.**(2026.7.20 更新: 加法缩小到 int64_t 范围(2^{63}-1) 且不再支持小数)**

支持查看运算历史记录.

## 使用方法

1. 直接打包这个项目中的所有文件;

2. 确保有 `CMake` 3.10 以上版本;

3. 编译: 在文件夹 `cmd` 中, 输入:

`mkdir build && cd build`

`cmake ..`

`make`

`./server`

后台不要关闭, 浏览器打开 `www/index.html`, 即可使用.
