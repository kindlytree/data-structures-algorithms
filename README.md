# data-structures-algorithms
- 数据结构和算法的代码实现和相关说明

## 编译文件
- g++ -std=c++11  ***.cpp -o ***.exe
- g++ -std=c++11  path-sum.cpp -o path-sum.exe
- g++ -std=c++11  n-queens.cpp -o n-queens.exe
- g++ -std=c++11  word-break.cpp -o word-break.exe


## 各算法分支

### 树形结构算法
- 树的递归构建
- 树的递归遍历
- 二叉搜索树按[low, high]的范围进行trim
    - 思路，采用递归的方法， 假设函数名为trim(root, low, high)，递归的步骤如下：首先以根节点作为当前节点
        - 如果当前节点值小于low，则直接将当前节点的右孩子节点作为新的当前节点
        - 如果当前节点值大于high，则直接将当前节点的左孩子节点作为新的当前节点
        - 如果当前节点值val基于low和high之间，则
- 二叉搜索树的平衡性判断（左右子树的高度差不能大于1）