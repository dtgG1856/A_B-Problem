# A_B Problem 为 A+B Problem 的升级版.

## 项目功能 

支持 + - $\times$ mod xor gcd sin 七种运算;

+ - $\times$ mod sin 支持小数运算;

xor gcd 仅支持整数运算, 输入小数将会报错.

支持查看运算历史记录.

## 使用方法

1. 下载 `httplib` 库 (文件 `httplib.h`);

2. 下载 `server.cpp` 并编译: **Windows**: `g++ -std=c++17 -pthread -D_WIN32_WINNT=0x0A00 server.cpp -o server.exe -lws2_32`  **Linux**: `g++ -std=c++17 -pthread server.cpp -o server`

3. 下载 `index.html` 前端文件;

4. 确保这些文件在同一文件夹里;

5. 编译后的 server 文件运行, 可以打开前端网页进行计算.