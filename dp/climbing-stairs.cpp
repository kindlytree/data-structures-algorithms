/*

题目来源： https://leetcode.cn/problems/climbing-stairs/

假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

 

示例 1：

输入：n = 2
输出：2
解释：有两种方法可以爬到楼顶。
1. 1 阶 + 1 阶
2. 2 阶
示例 2：

输入：n = 3
输出：3
解释：有三种方法可以爬到楼顶。
1. 1 阶 + 1 阶 + 1 阶
2. 1 阶 + 2 阶
3. 2 阶 + 1 阶
 

提示：

1 <= n <= 45

*/
#include<vector>
//方法：动态规划解法；记录
//有两种方式走到n，而且肯定会不相同
//1、走到n-1，再走一步到达n
//2、走到n-2直接两步到n，不经过n-1
//因此解法是dp[n]=dp[n-1]+dp[n-2]
//初始状态，第一个台阶只有一种走法，即走第一步，第二个台阶有两种走法，第一种分两个一步来走，第二种一次跨两步直接到达
//dp[0]=0,dp[1]=1,dp[2]=2；dp[3] =dp[2]+dp[1]
int climbStairs(int n) {
    if(n==1)return 1;
    if(n==2)return 2;
    std::vector<int>dp(n+1,0);
    dp[0]=0,dp[1]=1,dp[2]=2;
    for(int i=3; i <= n; i++)
    {
        dp[i]=dp[i-1]+dp[i-2];
    }
    return dp[n];
}

int main()
{
    int n = 9;
    int methods = climbStairs(3);
    return 0;
}