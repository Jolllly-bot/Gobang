# Gobang

### Introduction
This is a final project for the C programming course at UCAS during my freshman year. It features a Gobang AI that uses Minimax search, Alpha-Beta pruning, and move-killing techniques. 

Looking back, many of the implementations and coding practices seem quite immature, but I'm still proud that I taught my computer to play Gobang and surpass myself ;) By the way, it also clinched first place in the final competition. I’d say that’s a decent return on my sleep-deprived investment.

### Usage Instructions
1. Compile the code:

```bash
gcc -o gobang main.c minmax.c interact.c score.c
```

Add `-D NKILL` flag to enable move-killing.
Add `-D SIX` flag to set the search depth to six layers (note: this will be slow).

2. Run the game:

```bash
./gobang
```

- Choose the game mode:

1: Player vs Player
2: Player vs Computer (computer plays second)
3: Player vs Computer (computer plays first)

- Making a move:

Enter a lowercase letter followed by a number.

- Undo the last move:

Press r (only one undo is allowed).


### Contributing
Fork the repository. Create a new branch. Commit your code. Open a Pull Request.
If you encounter any bugs, feel free to open an issue, although there's a good chance I'll be too lazy to fix it.

### 介绍

UCAS C程序设计与分析大作业，采用极大极小值搜索，Αlpha-beta剪枝，带算杀的五子棋AI，建议谨慎参考。

### 使用说明

1.  `git clone` + 本仓库地址

2.  编译：`gcc -o gobang main.c minmax.c intereact.c score.c`

    `-D NKILL`：增加算杀

    `-D SIX`：深度算六层（比较慢）

3.  运行：`./gobang`

    模式选择：1.人人对战 2.电脑后手 3.电脑先手
    
    落子：`小写字母+数字`
    
    悔棋：`r` （只能悔一步）


### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request

- 如遇bug，请提issue，虽然八成懒得de。

### 参考教程

1. [言川/ 五子棋AI教程](https://github.com/lihongxun945/myblog/issues/11)：虽然是代码是JS，但是思路详细完整，还支持在线对战，方便用他测一测你的水平如何。
2. [livingsu/ 五子棋ai：极大极小搜索和α-β剪枝算法的思想和实现(qt和c++)](https://blog.csdn.net/livingsu/article/details/104536005) ：推荐（二）里对于两种不同评估函数的理解，让我当时醍醐灌顶。
2. [Bruce Moreland/ Alpha-Beta搜索](https://www.xqbase.com/computer/search_alphabeta.htm)
2. [univasity/ Minimax算法研究](https://www.iteye.com/blog/univasity-1170216)
