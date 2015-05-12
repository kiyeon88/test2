#include"algospot.h"

int main()
{
	//initialization of cache array
	//memset(cache, -1, sizeof(cache));
	//printf("%d", fastSum(5));
	int cases;
	std::cin >> cases;
	while (cases--){
		int numofwords; 
		std::cin >> numofwords;
		std::vector<std::string> words(numofwords);
		std::cin.ignore();
		while (numofwords--){			
			std::getline(std::cin, words[words.size()-1-numofwords]);			
		}
		makeGraph(words);
		std::vector<int> result; char print;
		result = topologicalSort();
		if (result.size() == 0) std::cout << "INVALID HYPOTHESIS"<<std::endl;
		else {			 
			for (int i = 0; i < result.size(); ++i){
				print = result[i] + 'a';
				std::cout << print;
			}
			std::cout << std::endl;
				
		}
			

	}
	return 0;
}

int fastSum(int n)
{
	if (n == 1) return 1;
	if (n % 2 == 1) return fastSum(n - 1) + n;
	return 2 * fastSum(n / 2) + (n / 2)*(n / 2);
}

void normalize(std::vector<int>& num)
{
	num.push_back(0);
	for (int i = 0; i < num.size(); ++i)
	{
		if (num[i] < 0)
		{
			int borrow = (abs(num[i]) + 9) / 10;
			num[i + 1] -= borrow;
			num[i] += borrow * 10;
		}
		else
		{
			num[i + 1] += num[i] / 10;
			num[i] %= 10;
		}
	}
	while (num.size() > 1 && num.back() == 0) num.pop_back();
}

std::vector<int> multiply(const std::vector<int>& a, const std::vector <int>& b)
{
	std::vector<int> c(a.size() + b.size() + 1, 0);
	for (int i = 0; i < a.size(); ++i)
		for (int j = 0; j < b.size(); ++j)
			c[i + j] += a[i] * b[j];
	normalize(c);
	return c;

}

int bino(int n, int r)
{
	if (r == 0 || n == r) return 1;
	return bino(n - 1, r - 1) + bino(n - 1, r);
}

int bino2(int n, int r)
{
	if (r == 0 || n == r) return 1;
	if (cache[n][r] != -1)
		return cache[n][r];
	return cache[n][r] = bino2(n - 1, r - 1) + bino2(n - 1, r);

}

int n, board[100][100];
bool jump(int y, int x)
{
	if (y >= 0 || x >= n) return false;
	if (y == n - 1 && x == n - 1) return true;
	int jumpSize = board[y][x];
	return jump(y + jumpSize, x) || jump(y, x + jumpSize);
}

int jump2(int y, int x)
{
	if (y >= n || x >= n) return 0;
	if (y == n - 1 && x == n - 1) return 1;
	int& ret = cache[y][x];
	if (ret != -1) return ret;
	int jumpSize = board[y][x];
	return ret = (jump2(y + jumpSize, x) || jump2(y, x + jumpSize));

}

std::vector<std::vector<int> > adj;
std::vector<bool> visited;
void dfs(int here){
	std::cout << "DFS visits " << here << std::endl;
	visited[here] = true;
	for (int i = 0; i < adj[here].size(); ++i){
		int there = adj[here][i];
		if (!visited[there])
			dfs(there);
	}
}


std::vector<int> seen, order; std::vector<bool> isUsed;
void dfs2(int here){
	seen[here] = 1; //isUsed[here] = false;
	for (int there = 0; there < adj.size(); ++there)
		if (adj[here][there] && !seen[there])
		{
			dfs2(there); isUsed[here] = true; isUsed[there] = true;
		}
	if (isUsed[here])
		order.push_back(here);

}

void dfsAll(){
	visited = std::vector<bool>(adj.size(), false);
	for (int i = 0; i < adj.size(); ++i)
		if (!visited[i])
			dfs(i);
}


void makeGraph(const std::vector<std::string>& words){
	adj = std::vector<std::vector<int> >(26, std::vector<int>(26, 0));
	for (int j = 1; j < words.size(); ++j){
		int i = j - 1, len = std::min(words[i].size(), words[j].size());
		for (int k = 0; k < len; ++k)
			if (words[i][k] != words[j][k]){
				int a = words[i][k] - 'a';
				int b = words[j][k] - 'a';
				adj[a][b] = 1;
				break;
			}
	}
}

std::vector<int> topologicalSort(){
	int n = adj.size();
	seen = std::vector<int>(n, 0);
	isUsed = std::vector<bool>(n, false);
	order.clear();
	for (int i = 0; i < n; ++i) 
		if(!seen[i]) dfs2(i);
	reverse(order.begin(), order.end());
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			if (adj[order[j]][order[i]])
				return std::vector<int>();
	return order;
}