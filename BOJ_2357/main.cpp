#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

constexpr auto DMax = numeric_limits<ll>::max();
constexpr auto DMin = numeric_limits<ll>::min();

int n, m;
int sz;
vl minDat;
vl maxDat;

void updateMin(int i, ll x) {
	auto idx = i + sz - 1;
	minDat[idx] = x;
	while (0 < idx) {
		idx = (idx - 1) / 2;
		minDat[idx] = min(minDat[idx * 2 + 1], minDat[idx * 2 + 2]);
	}
}

void updateMax(int i, ll x) {
	auto idx = i + sz - 1;
	maxDat[idx] = x;
	while (0 < idx) {
		idx = (idx - 1) / 2;
		maxDat[idx] = max(maxDat[idx * 2 + 1], maxDat[idx * 2 + 2]);
	}
}

ll queryMinPart(int a, int b, int key, int l, int r) {
	//cout << "min " << a << ' ' << b << ' ' << key << ' ' << l << ' ' << r << '\n';

	if (b <= l || r <= a) {
		return DMax;
	}

	if (a <= l && r <= b) {
		//cout << " -> " << minDat[key] << '\n';
		return minDat[key];
	}

	const auto m = (l + r) / 2;
	const auto v1 = queryMinPart(a, b, key * 2 + 1, l, m);
	const auto v2 = queryMinPart(a, b, key * 2 + 2, m, r);
	return min(v1, v2);
}

ll queryMin(int a, int b) {
	return queryMinPart(a, b, 0, 0, sz);
}

ll queryMaxPart(int a, int b, int key, int l, int r) {
	//cout << "max " << a << ' ' << b << ' ' << key << ' ' << l << ' ' << r << '\n';

	if (b <= l || r <= a) {
		return DMin;
	}

	if (a <= l && r <= b) {
		//cout << " -> " << maxDat[key] << '\n';
		return maxDat[key];
	}

	const auto m = (l + r) / 2;
	const auto v1 = queryMaxPart(a, b, key * 2 + 1, l, m);
	const auto v2 = queryMaxPart(a, b, key * 2 + 2, m, r);
	return max(v1, v2);
}

ll queryMax(int a, int b) {
	return queryMaxPart(a, b, 0, 0, sz);
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n >> m;

	sz = 1;
	while (sz < n) {
		sz *= 2;
	}

	minDat = vl(2 * sz - 1, DMax);
	maxDat = vl(2 * sz - 1, DMin);

	for (auto i = 0; i < n; ++i) {
		ll x;
		cin >> x;

		updateMin(i, x);
		updateMax(i, x);
	}

	/*for (const auto& x : minDat) {
		cout << (x == DMax ? "INF" : to_string(x)) << ' ';
	}
	cout << '\n';

	for (const auto& x : maxDat) {
		cout << (x == DMin ? "-INF" : to_string(x)) << ' ';
	}
	cout << '\n';*/

	for (auto i = 0; i < m; ++i) {
		ll a, b;
		cin >> a >> b;

		cout /*<< "out " */ << queryMin(a - 1, b) << ' ' << queryMax(a - 1, b) << '\n';
	}

	return 0;
}