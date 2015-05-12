#define BlockSize 50

#include<vector>
#include<io.h>
#include<iostream>
#include<string>
#include<math.h>
#include<algorithm>

int cache[BlockSize][BlockSize];

int fastSum(int n);

void normalize(std::vector<int>& num);

std::vector<int> multiply(const std::vector<int>& a, const std::vector <int>& b);

int bino(int n, int r);

int bino2(int n, int r);

bool jump(int y, int x);

int jump2(int y, int x);

void dfs(int here);

void dfs2(int here);

void makeGraph(const std::vector<std::string>& words);

std::vector<int> topologicalSort();