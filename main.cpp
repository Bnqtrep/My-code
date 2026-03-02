//holy shit
#include <bits/stdc++.h>
using namespace std;
int check(tuple<char, int, int> piece_a, tuple<char, int, int> piece_b) {
	int total = 0;
	auto [type_a, a_x, a_y] = piece_a;
	auto [type_b, b_x, b_y] = piece_b;
	
	if(type_a == 'Q') {
		if(abs(a_x - b_x) == abs(a_y - b_y) || a_x == b_x || a_y == b_y) total++; 
	}
	if(type_a == 'R') {
		if(a_x == b_x || a_y == b_y)  total++;
	}
	if(type_a == 'B') {
		if(abs(a_x - b_x) == abs(a_y - b_y)) total++; 
	}
	return total;

}
int solve(int N, int M, int K, vector<tuple<char, int, int>> P) {
    int total = 0;
	int stop_index = 0;
	// N: Number of rows of the board
    // M: Number of columns of the board
    // K: Number of pieces
    // P: list of tuples. Each tuple contains (piece type, x position, y position)
	vector<tuple<char, int, int>> hori (P);
	sort(hori.begin(), hori.end(), [](auto a, auto b){
		return get<1>(a) < get<1>(b);
	});	
	while(stop_index != hori.size())
	{
		int index;
		for(index = stop_index; index < hori.size(); index++)
		{
			if(get<1>(hori[index]) != get<1>(hori[stop_index]))
			{
				stop_index = index; break;
			}
		}
		sort(hori.begin() + index, hori.begin() + index + stop_index, [](auto a, auto b){
			return get<2>(a) < get<2>(b);
		});
	
	}
	

	for(int i = 0; i + 1 < hori.size(); i++)
	{
		int a = i, b = i + 1;
		auto [atype, ax, ay] = hori[a]; auto [btype, bx, by] = hori[b];
		if(ax == bx){
			total += check(hori[a], hori[b]); total += check(hori[b], hori[a]);
		}
	}

	//------

	vector<tuple<char, int, int>> verti (P);
	sort(verti.begin(), verti.end(), [](auto a, auto b){
		return get<2>(a) < get<2>(b);
	});

	while(stop_index != verti.size())
	{
		int index;
		for(index = stop_index; index < verti.size(); index++)
		{
			if(get<2>(verti[index]) != get<2>(verti[stop_index]))
			{
				stop_index = index; break;
			}
		}
		sort(verti.begin() + index, verti.begin() + index + stop_index, [](auto a, auto b){
			return get<1>(a) < get<1>(b);
		});
	
	}

	for(int i = 0; i + 1 < verti.size(); i++)
	{
		int a = i, b = i + 1;
		auto [atype, ax, ay] = verti[a]; auto [btype, bx, by] = verti[b];
		if(ay == by){
			total += check(verti[a], verti[b]); total += check(verti[b], verti[a]);
		}
	}

	//------

	vector<tuple<char, int, int>> LtoR_diag (P);
	sort(LtoR_diag.begin(), LtoR_diag.end(), [](auto a, auto b){
		return get<1>(a) + get<2>(a) < get<1>(b) + get<2>(b);// x + y sort
	});
	while(stop_index != LtoR_diag.size())
	{
		int index;
		for(index = stop_index; index < LtoR_diag.size(); index++)
		{
			if(get<1>(LtoR_diag[index]) + get<2>(LtoR_diag[index]) != get<1>(LtoR_diag[stop_index]) + get<2>(LtoR_diag[stop_index]))
			{
				stop_index = index; break;
			}
		}
		sort(LtoR_diag.begin() + index, LtoR_diag.begin() + index + stop_index, [](auto a, auto b){
			return N + 1 - get<1>(a) + get<2>(a) < N + 1 - get<1>(b) + get<2>(b) ; // N + 1 - x + y  sort
		});
	
	}

	for(int i = 0; i + 1 < LtoR_diag.size(); i++)
	{
		int a = i, b = i + 1;
		auto [atype, ax, ay] = LtoR_diag[a]; auto [btype, bx, by] = LtoR_diag[b];
		if(ax + ay == bx + by){
			total += check(LtoR_diag[a], LtoR_diag[b]); total += check(LtoR_diag[b], LtoR_diag[a]);
		}
	}
//------
	vector<tuple<char, int, int>> RtoL_diag (P);
	sort(RtoL_diag.begin(), RtoL_diag.end(), [&N](auto a, auto b){
		return N + 1 - get<1>(a) + get<2>(a) < N + 1 - get<1>(b) + get<2>(b) ; // N + 1 - x + y  sort
	});
	
	while(stop_index != RtoL_diag.size())
	{
		int index;
		for(index = stop_index; index < RtoL_diag.size(); index++)
		{
			if(N + 1 - get<1>(RtoL_diag[index]) + get<2>(RtoL_diag[index]) != N + 1 - get<1>(RtoL_diag[stop_index]) + get<2>(RtoL_diag[stop_index]))
			{
				stop_index = index; break;
			}
		}
		sort(RtoL_diag.begin() + index, RtoL_diag.begin() + index + stop_index, [](auto a, auto b){
			return get<1>(a) + get<2>(a) < get<1>(b) + get<2>(b); // x + y sort
		});
	
	}

	for(int i = 0; i + 1 < RtoL_diag.size(); i++)
	{
		int a = i, b = i + 1;
		auto [atype, ax, ay] = RtoL_diag[a]; auto [btype, bx, by] = RtoL_diag[b];
		if(N + 1 - ax + ay == N + 1 - bx + by){
			total += check(RtoL_diag[a], RtoL_diag[b]); total += check(RtoL_diag[b], RtoL_diag[a]);
		}
	}

	
	
	return total;
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(NULL); cout.tie(NULL);
	int t; cin >> t;
	for (int i = 0; i < t; i++) {
		int n, m; cin >> n >> m;
		int k; cin >> k;
		vector<tuple<char, int, int>> pieces;
		for (int i = 0; i < k; i++) {
			char piece; int x, y; cin >> piece >> x >> y;
            pieces.emplace_back(piece, x, y);
		}
	    cout << solve(n, m, k, pieces) << "\n";
	}
}