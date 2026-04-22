# Problem 082 - Linked Hash Map 21年期末

**ACMOJ Problem ID**: 1779

## Table of Contents

- [Problem 082 - Linked Hash Map 21年期末](#problem-082-linked-hash-map-21年期末)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Background](#background)
  - [Assignment Description](#assignment-description)
    - [Grade Composition](#grade-composition)
  - [Assignment Requirements](#assignment-requirements)
    - [Input Format](#input-format)
    - [Output Format](#output-format)
    - [Samples](#samples)
    - [Data Constraints](#data-constraints)
  - [Per-Testcase Resource Limits](#per-testcase-resource-limits)
  - [Test Data](#test-data)
  - [Submission Requirements](#submission-requirements)
    - [OJ Git Repository Compilation Process](#oj-git-repository-compilation-process)
    - [Git Configuration Requirements](#git-configuration-requirements)
    - [Submission Guidelines](#submission-guidelines)
    - [Evaluation Notes](#evaluation-notes)
    - [Academic Integrity](#academic-integrity)

## Introduction

### Background

This problem tests algorithmic problem-solving skills.

## Assignment Description

### Grade Composition

| Grading Component | Percentage |
| :--: | :--: |
| Pass **1779. Linked Hash Map 21年期末** | 80% |
| Code Review | 20% |

Here are several points that need clarification:

- In the Code Review, we will **strictly examine your code style and repository organization structure, etc.**

- This assignment provides some sample data for testing, stored in the `/workspace/data/082/data_test/` directory. Note that these are not the test cases on the Online Judge. Passing all local test cases does not guarantee that you will pass the OJ tests.

- Besides the provided sample data, we also encourage you to design your own test data based on your program logic to assist debugging.

## Assignment Requirements

### Problem Description

在本题中，你需要实现一个 LinkedHashMap，下面是对于这个结构的具体说明：

下图是对于这个结构的简要说明图，数组 array 的每个元素对应一个单链表。我们将 ``array[i]`` 指向的的节点称为链表的头节点，单链表最后一个结点称为尾节点。如在 6 下方对应的链表中 `'E'` 为头节点，`'A'` 为尾节点。

<img src="https://acm.sjtu.edu.cn/OnlineJudge-pic/20221215-001158-778673.jpg" style="width: 100%">

除此以外，我们还需要实现一个双向链表（如图中蓝色虚线箭头所示）来维护元素的插入的先后顺序，例如上图的插入顺序是依照字符串的字典序 A, B, C, ...。在给定的代码框架中，我们给出 beg 指向双向链表的头结点，current 指向双向链表的尾节点；但你也可以根据自己写双向链表的习惯修改或删除这两个节点。

遍历 LinkedHashMap 中的所有元素可以在以下两种方法中选择一种（在定义对象时指定）。分别为按照插入的时间从早到晚输出、按照 key 的从小至大输出。按照 key 的从小至大输出时，在每个 key 对应的链表输出时，将链表元素从头向尾输出。每个方法由一个全局函数实现。你需要在下方的两个全局函数中填入两种遍历的实现。

LinkedHashMap 必须实现下列功能：

- 构造函数：参数为数组长度和本对象采用的遍历函数。根据传入的长度参数来构建一个长度恰为传入的长度参数的数组，数组的元素为给出的`node` 类的指针。并将双链表设置为空表。保存遍历函数。
- 析构函数：释放空间。
- 插入指令 `void insert(int key, std::string value)`：将新的节点插入在上图中 `array[key]` 对应的单链表的**头部**以及双链表的**尾部**。
- 删除操作 `void remove(int key, std::string value)`：删除指定 `key` 的单链表中值为 `value` 的结点。若不存在相应的 `(key,value)` 对，你不应当做任何事情。注意还需要在双链表中做删除操作。
- 查找操作 `vector<string> ask(int key)const`：在要返回的 `vector` 中插入指定的 `key` 对应的链表中的所有 `value` 值，顺序为从链表的头向链表的尾。
- 输出链表的全部内容 `vector<data> forEach() const`：根据所选的遍历函数遍历所有节点。
* **tips：如果你没能够完成这个小问，你可以使用 ``LinkedHashMap_simple.hpp`` 来通过编译。**
* **注意：你不能使用 ``auto`` 关键字**
* **注意：除了修改构造函数中链表头指针的设计外，你仅能在 `//todo` 标识的地方写代码。**

LinkedHashMap.hpp:

```cpp
//
// Created by wzj on 2021/12/3.
//

#ifndef FINAL_SRC_HPP
#define FINAL_SRC_HPP

#include <string>
#include <vector>
using namespace std;

class LinkedHashMap;
struct Node{
    Node* next=nullptr;
    Node* timePre=nullptr;
    Node* timeNext=nullptr;

    int key=0;
    string value;
};

struct Data{
    int key;
    string value;
};

vector<Data> traverseByTime(const LinkedHashMap& obj);
vector<Data> traverseByIndex(const LinkedHashMap& obj);

class LinkedHashMap{
// todo: Modify "beg", "current" and related parts in the constructor as you wish.
// todo: 你可以根据自己写链表的习惯修改或删除头尾节点并对应修改构造函数。
public:
    int len;
    Node** array;
    Node* beg;
    Node* current;
    // todo: define a function pointer called "forEachMethod"
    // to be pointed to function "traverseByTime" or "traverseByDict".
    // todo: 定义一个名为forEachMethod的函数指针，用于对应travelByTime和travelByDict函数。

    LinkedHashMap(int _len_,bool forEachByTime){
        len=_len_;
        beg=new Node();
        current=beg;
        array=new Node*[len];
        for(int i=0;i<len;i++)
            array[i]=nullptr;
        if(forEachByTime)
            forEachMethod=traverseByTime;
        else
            forEachMethod=traverseByIndex;
    }

    ~LinkedHashMap(){
        //todo

    }

    void insert(int key,string value){
        //todo
    }

    void remove(int key,string value){
        //todo
    }

    vector<string> ask(int key)const{
        //todo
    }

    vector<Data> forEach()const{
        return forEachMethod(*this);
    }
};

vector<Data> traverseByTime(const LinkedHashMap& obj){
    //todo
}

vector<Data> traverseByIndex(const LinkedHashMap& obj){
    //todo
}

#endif //FINAL_SRC_HPP

```

### Input Format



### Output Format



### Samples

No sample data provided for this problem.

### Data Constraints

仅有一个复杂度的要求，删除双向链表中的元素复杂度为 $O(1)$。

| check point | 考察的内容                                     | 分数       |
| ----------- | ---------------------------------------------- | ---------- |
| 1，2        | 考察插入和查找                                 | 2 x 5 = 10 |
| 3，4        | 考察插入，删除和查找                           | 2 x 5 = 10 |
| 5，6        | 考察插入，查找，按照 key 字典顺序输出            | 2 x 6 = 12 |
| 7，8        | 考察插入，查找，按照时间顺序输出               | 2 x 6 = 12 |
| 9，10，11   | 考察插入，删除，查找，按照 key 字典顺序输出      | 3 x 6 = 18 |
| 12，13，14  | 考察插入，删除，查找，按照时间顺序输出         | 3 x 6 = 18 |
| 15 ~ 22     | 数据内容同 1 ~ 8，使用 valgrind 进行内存泄漏检查  | 8 x 1 = 8  |
| 23 ~ 28     | 数据内容同 9 ~ 14，使用 valgrind 进行内存泄漏检查 | 6 x 2 = 12 |

## Per-Testcase Resource Limits

- **Time Limit (per test case)**: 3000 ms
- **Memory Limit (per test case)**: 244 MiB
- **Disk Usage**: No disk usage is permitted.

## Test Data

The test data for this problem is located at `/workspace/data/082/data_test/`.

## Submission Requirements

### OJ Git Repository Compilation Process

For Git compilation, we will first clone the repository using a command similar to:
```bash
git clone <repo_url> . --depth 1 --recurse-submodules --shallow-submodules --no-local
```

Then we check if there is a `CMakeLists.txt` file. If it exists, we run (if not, a warning message will be displayed):
```bash
cmake .
```

Finally, we check if there is any of `GNUmakefile`/`makefile`/`Makefile` (if cmake was run previously, this will be the generated Makefile). If it exists, we run (if not, a warning message will be displayed):
```bash
make
```

After this process is complete, we will use the `code` file in the project root directory as the compilation result.

A `CMakeLists.txt` file is provided in the project. You can use or modify it as needed. The local environment has gcc-13 and g++-13 available.

### Git Configuration Requirements

**IMPORTANT**: You must create a `.gitignore` file in your project root directory to avoid OJ evaluation conflicts.

The `.gitignore` file should include at least the following entries:

```gitignore
CMakeFiles/
CMakeCache.txt
```

### Submission Guidelines

- The submitted code must be able to compile successfully through the above compilation process
- The compiled executable file name must be `code`
- The program needs to be able to read data from standard input and write results to standard output
- Please ensure the code runs correctly within the given time and space limits
- **You must use C++ or C language** to implement this assignment

### Evaluation Notes

- The evaluation system will test your program using the provided test data
- The program output must exactly match the expected output (including format)
- Exceeding time or memory limits will be judged as the corresponding error type
- Please pay attention to the overall time performance of your code and the time complexity of each part of your algorithm.

### Academic Integrity

If any violations are found during evaluation or code review (including but not limited to using unconventional methods to pass test cases), your final score may be significantly reduced or become **0 points**.
