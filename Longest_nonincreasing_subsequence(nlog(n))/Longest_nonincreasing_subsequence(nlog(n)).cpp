#include <iostream>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

int bin_search_less(vector<int> &en, int &val) {
	int begin = 0, end = en.size(), current;
	while (begin < end) {
		current = (begin + end) / 2;
		if (en[current] > val) {
			begin = current + 1;
		}
		else {
			end = current;
		}
	}
	while (en[current] >= val) ++current;
	return current;
}

int main()
{
	unsigned int arr_size;
	cin >> arr_size;
	vector<int> arr (arr_size);
	for (int j = 0; j < arr_size; ++j) cin >> arr[j];
	vector<int> ending_number(arr_size + 1, INT_MIN); // d[i - 1] >= d[i]
	ending_number[0] = INT_MAX;
	vector<int> ending_index(arr_size + 1, -1);
	vector<int> ancestor(arr_size);
	int max_length = 0;
	for (int j = 0; j < arr_size; ++j) {
		int tmp = bin_search_less(ending_number, arr[j]);
		if (ending_number[tmp - 1] >= arr[j] && arr[j] >= ending_number[tmp]) {
			ending_number[tmp] = arr[j];
			ending_index[tmp] = j; // на элементе с индексом j оканчивается оптимальная подпоследовательность длины tmp.
			ancestor[j] = ending_index[tmp - 1];
			max_length = max(max_length, tmp);
		}
	}
	cout << endl << max_length << endl;
	vector<int> answer;
	int p = ending_index[max_length];
	while (p != -1) {
		answer.push_back(p);
		p = ancestor[p];
	}
	reverse(answer.begin(), answer.end());
	for (int e : answer) cout << e + 1 << ' ';
	return 0;
}

