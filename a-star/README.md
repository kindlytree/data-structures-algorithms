# A star算法示例

## 代码编译
- 在windows平台上下载gcc编译器，下载链接为：https://github.com/niXman/mingw-builds-binaries/releases 。 可以找到最新的ucrt版本
- 解压后，将对应的make可执行文件的路径添加到系统的PATH里
- 在该项目目录下执行make命令，生成search.exe可执行文件

## 代码执行
- search  "single_run" astar_explist_manhattan "608435127" "123456780"
- search  "single_run" uc_explist "608435127" "123456780"
- search "batch_run" astar_explist_manhattan
- 更多的参考command_line.txt文件

## 执行参数解释
- uc_explist即为uniform cost search，即为Dijkstra算法
- astar_explist_manhattan即为基于曼哈顿距离作为启发式函数的A star算法
- single_run为完成一个魔方任务
- batch_run为完成多个魔方任务，这些魔方任务在main.cpp代码的上方list_of_initialStates变量中进行了定义