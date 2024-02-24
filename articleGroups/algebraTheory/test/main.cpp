#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <numeric>
#include <stack>
#include <fstream>
#include <sstream>
#include <bitset>
#include <iomanip>
#include <regex>
#include <deque>
#include <unordered_map>
#include <cstdlib>

#define PairInt std::pair<int, int>
#define Vector std::vector
#define String std::string
#define Map std::map
#define Set std::set
#define Pair std::pair
#define LL long long
#define LD long double

using std::cin, std::cout, std::cerr;

Vector<Vector<int>> graph;
Vector<int> ans;
Vector<bool> vec;

bool dfs(int vertex, int color = 0) {
    ans[vertex] = color;
    if (color && vec[vertex]) return false;
    for (auto to : graph[vertex]) {
        if (ans[to] == color) return false;
        if (ans[to] != -1) continue;
        ans[to] = (color + 1) % 2;
        if (!dfs(to, (color + 1) % 2)) return false;
    }
    return true;
}

LL sum0 = 0, sum1 = 0;
Vector<bool> used;

void dfs0(int vertex, bool flag) {
    used[vertex] = true;
    if (flag) {
        sum0++; sum1++;
    } else if (ans[vertex]) {
        sum1++;
    } else {
        sum0++;
    }
    for (auto to : graph[vertex]) {
        if (used[to]) continue;
        used[to] = true;
        dfs0(to, flag);
    }
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.precision(100);
    // std::ifstream in("../dist.in");
    // std::ofstream out("../dist.out");
    int n; cin >> n;
    vec.resize(n);
    for (int i = 0; i < n; ++i) {
        int elem; cin >> elem;
        vec[i] = elem;
    }
    int m; cin >> m;
    graph.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }
    ans.resize(n, -1);
    used.resize(n);
    for (int i = 0; i < n; ++i) {
        if (used[i] || !vec[i]) continue;
        dfs0(i, !dfs(i));
    }
    cout << std::max(sum0, sum1);
}