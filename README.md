# A_B Problem 为 A+B Problem 的实验升级版.

## Demo 功能 

支持 `+` `-` $\times$ `mod` `xor` `gcd` `sin` `cos` `or` 共 9 种运算, 其中 `sin` `cos` 支持小数运算 **(最大 16 位数字, 包含前导 0)**, 其它 7 种运算仅支持整数运算 **(范围为 $[-2^{63}, 2^{63}-1]$ , 即 `int64_t` 范围)** , 输入小数与科学计数法将会报错.

支持查看运算历史记录(**本地存储**).

**Release 可能不随着 GitHub 仓库实际代码的变化而变化。**

## 使用方法

~~0. 也许可以使用 `release`, 但并不会随时更新.~~
   
1. 确保有 `CMake` 3.10+ && 能够运行 `C++17` 的编译器;

2. `git clone https://github.com/dtgG1856/A_B-Problem.git`, `cd A_B-Problem`;

3. 构建:
   i. Windows: 在文件夹的 `cmd` 中, 输入:

    `mkdir build`

    `cmake -B build`

    `cmake --build build`

    `build\server.exe`

    ii. Linux: 在文件夹终端中，输入：

    `mkdir build`

    `cmake -B build`

    `cmake --build build`

    `./build/server`

后台不要关闭, 浏览器打开 `www/index.html`, 即可使用.
