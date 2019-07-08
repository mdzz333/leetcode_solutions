# 程序结构

## 结构体

两个类型相同的结构变量可以相互赋值。但是结构变量之间不能直接进行比较运算。（ == != < > <= >= 等）

一般来说，一个结构变量所占内存空间的大小，就是结构中所有变量大小之和。结构变量中的各个成员变量在内存中一般是连续存放。

## 全局变量、局部变量、静态变量

- 局部变量：定义在函数内部的变量（函数形参也是局部变量）
- 全局变量：定义在函数外部的变量

>静态变量：全局变量都是静态变量。局部变量如果在定义时加了`static`，则也是静态变量。静态变量的存放地址在整个程序运行期间，都是不变的。静态变量只初始化一次。

>非静态变量：（一定是局部变量，但反之不对）地址在每次函数调用时都可能不同，但在函数的依次执行期间不变。

静态变量不初始化，则值为0，非静态变量的值则是随机的。

静态变量的应用：`strtok`的实现。我们先看看`strtok`是怎么使用的

```cpp
#include<iostream>
#include<cstring>    // strtok在此库
using namespace std;
int main(){
    char str[] = "- This, a sample string OK.";
    // 下面从str逐个抽取被" ,.-"这四个字符分割的字符串
    char *p = strtok(str, " ,.-");
    // 只要p不为空，就说明找到了一个子串
    while(p != NULL){
        cout << p << endl;
        // 后续调用，第一个参数必须是NULL
        p = strtok(NULL, " ,.-");
    }
    return 0;
}
```

由上可以看出，`strtok`需要一个记录往后找的开始位置。(注意教程中给出的这种实现会改变原字符串)

```cpp
char *strtok(char *p, char *sep){
    static char *start;      // 本次查找子串的起点
    if(p)   
        start = p;           // 第一次调用，start指向出入字符串的开头
    for(; *start && strchr(sep, *start); ++start); //跳过分隔符
    if(*start == 0)
        return NULL;         // 已经到字符串结尾，返回NULL
    char *q = start;
    for(; *start && !strchr(sep, *start); ++start); // 跳过非分割符
    if(*start){
        *start = 0;        // 手工加上结尾标志，注意这样做会改变原字符串。
        ++start;
    }
    return q;
}
```

## 作用域和生存期

- 标识符：变量名、函数名和类型名统称为标识符。
- 标识符的作用域：一个标识符能起作用的范围。

在标识符的作用域之外使用该标识符，会导致“标识符没有定义”的编译错误。使用标识符的语句，必须出现在他们的声明或定义之后。

单文件的程序中，结构、函数和全局变量的作用域是其定义所在的整个文件。

- 函数形参的作用域是整个函数
- 局部变量的作用域，是从其定义开始，到包含它的最内层的一对大括号的右括号为止
- for循环中定义的循环控制变量，作用域就是整个for循环。

变量的生存期是指，在此期间，变量很占有内存空间，其占有的内存空间只能归他使用，不会被用来存放别的东西。

- 全局变量的生存期：从程序被装入内存开始，到整个程序结束。
- 静态局部变量的生存期：从定义它语句第一次被执行开始，到程序结束为止。
- 非静态局部变量的生存期：从执行到定义它的语句开始，到其执行到作用域结束。
- 函数形参的生存期：从函数执行开始，到函数返回时结束。