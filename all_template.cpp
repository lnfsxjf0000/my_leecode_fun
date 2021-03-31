
分支1
版本1
// all_template.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include<queue>
#include<deque>
#include<list>
#include<numeric>
#include<map>
#include < unordered_map >
#include<string>

#include <cstdio>

using namespace std;


//背包问题
struct Bag
{
	int v;
	int w;
};
void bag_problem()
{
	int F[1024] = { 0 };
	int n, m;//商品数量，背包大小
	cin >> n >> m;
	//01背包
	for (int i = 0; i < n; i++)
	{
		int v, w;//价值  体积
		cin >> v >> w;
		for (int j = m; j >= w; j--)
			F[j] = max(F[j], F[j - w] + v);
	}
	cout << F[m] << endl;

	//完全背包
	for (int i = 0; i < n; i++)
	{
		int v, w;
		cin >> v >> w;
		for (int j = w; j <= m; j++)
			F[j] = max(F[j], F[j - w] + v);
	}
	cout << F[m] << endl;

	//多重背包   每个数量100以内
	for (int i = 0; i < n; i++)
	{
		int v, w, s;//每个商品的个数
		cin >> v >> w >> s;//价值 重量  个数
		for (int j = m; j >= 0; j--)//j 0 还是 w 
		{
			for (int k = 0; k < s && k*w < j; k++)
				F[j] = max(F[j], F[j - k * w] + k * v);

		}

	}

	//多重背包优化
	vector<Bag> bag_partion;

	for (int i = 0; i < n; i++)
	{
		int v, w, s;//每个数量不一样
		cin >> v >> w >> s;
		for (int k = 1; k <= s; k = k * 2)
		{
			s -= k;
			bag_partion.push_back({ k*v,k*w });
		}
		if (s > 0)
			bag_partion.push_back({ s*v,s*w });
	}

	for (auto bag : bag_partion)
	{
		for (int j = m; j >= bag.w; j--)
			F[j] = max(F[j], F[j - bag.w] + bag.v);

	}

	cout << F[m] << endl;
}

//斐波那契
void fbnq(int n) {
	int now = 0, last = 1, before_last = 0;
	for (int i = 1; i <= n; i++) {
		now = last + before_last;
		before_last = last;
		last = now;
	}
	cout << "fbnq: " << now << " " << endl;
}





//二分：
#define check(n)   true
int bsearch_2(int l, int r)
{
	while (l < r)
	{
		int mid = l + r + 1 >> 1;
		if (check(mid)) l = mid;
		else r = mid - 1;
	}
	return l;
}
int binary_search(vector<int> &nums, int target) {
	int left = 0, right = nums.size() - 1;
	
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (nums[mid] > target)
			right = mid - 1;
		else if (nums[mid] < target)
			left = mid + 1;
		else if (nums[mid] == target)
			return mid;
	}
	return -1;
}
int left_bound(vector<int> &nums, int target) {
	int left = 0, right = nums.size() - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (nums[mid] > target)
			right = mid - 1;
		else if (nums[mid] < target)
			left = mid + 1;
		else if (nums[mid] == target)
			right = mid - 1;
	}
	if(left >=nums.size()||nums[left]!=target)
		return -1;
	return left;
}
int right_bound(vector<int>&nums, int target) {
	int left = 0, right = nums.size() - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (nums[mid] > target)
			right = mid - 1;
		else if (nums[mid] < target)
			left = mid + 1;
		else if (nums[mid] == target)
			left = mid + 1;
	}
	if (right < 0|| nums[right] != target)
		return -1;
	return right;
}

//排序：
//快排：
void quick_sort_2(vector<int> &q, int left, int right) {
	if (left >= right) return;
	int i = left - 1, j = right + 1;
	int target = q[left + right >> 1];
	//int target = q[right-1];//left
	//int target = q[left + 1+(right-left)>> 1];//不行
	while (i < j) {
		do i++; while (q[i] < target);
		do j--; while (q[j] > target);
		if (i < j) swap(q[i], q[j]);
	}
	quick_sort_2(q, left, j);
	quick_sort_2(q, j + 1, right);
}
//归并排序：
//容器方法
void merge_sort(vector<int> &q, int left, int right) {
	if (left >= right) return;
	int mid = left + right >> 1;

	merge_sort(q, left, mid);
	merge_sort(q, mid + 1, right);

	static vector<int> temp;
	temp.clear();//注意清除

	int i = left, j = mid + 1;//等于left
	while (i <= mid && j <= right) {
		if (q[i] > q[j])
			temp.push_back(q[j++]);
		else
			temp.push_back(q[i++]);
	}
	while (i <= mid) temp.push_back(q[i++]);
	while (j <= right) temp.push_back(q[j++]);
	for (int m = left, t = 0; t < temp.size(); m++, t++)q[m] = temp[t];
}

//逆序对：
//res += merge_sort2(q, l, mid);
//res += mid - i + 1;
//return res;




//堆排序：
//CSDN版本
void push_down(vector<int>&q, int root, int size) {
	int max = root;
	int left = 2 * root + 1;
	int right = 2 * root + 2;

	if (left < size && q[max] < q[left])	max = left; //注意先判断是否溢出
	if (right < size && q[max] < q[right])	max = right;

	if (max != root) {
		swap(q[max], q[root]);
		push_down(q, max, size);
	}
}
void heap_sort(vector<int> &q, int size) {
	for (int i = size / 2 - 1; i >= 0; i--) {
		push_down(q, i, size);
	}
	while (size > 1) {
		swap(q[0], q[--size]);//先-- swap
		push_down(q, 0, size);
	}
}

//判断质数
bool is_prime(int x)
{
	if (x < 2) return false;
	for (int i = 2; i <= x / i; i++)
		if (x % i == 0)
			return false;
	return true;
}
//输出所有质数和个数
bool all_prime(int x) {


	for (int i = 2; i <= x / i; i++) {
		if (x % i == 0)
		{
			int s=0;
			while (x % i == 0) s++, x /= i;
			cout << "i: " << i << " s: " << s << endl;
		}
	}
	return true;
}



//最长回文字符串
string longestPalindrome(string s) {
	string res;
	int len = 0;
	//OK 简单
	for (int k = 0; k < s.size(); k++) {

		int i = k, j = k + 1;
		while (i >= 0 && j < s.size() && s[i] == s[j]) j++, i--;
		if (j - i - 1 > len) {
			len = j - i - 1;
			res = s.substr(i + 1, len);
		}

		i = k - 1, j = k + 1;
		while (i >= 0 && j < s.size() && s[i] == s[j]) j++, i--;
		if (j - i - 1 > len) {
			len = j - i - 1;
			res = s.substr(i + 1, len);
		}
	}
	return res;
}

//反转字符串里的单词
string reverseWords(string &s) {
	int i = 0, j = 0;
	s += ' ';
	//先取出多余的空格
	while (j < s.size() && s[j] == ' ') j++;
	while (j < s.size()) {
		if (s[j] != ' ')
			s[i++] = s[j++];
		else {
			s[i++] = ' ';
			while (j < s.size() && s[j] == ' ') j++;
		}
	}
	if (!i) {
		string m = "";
		return m;
	}

	//擦除多余部分
	s.erase(s.begin() + i - 1, s.end());
	//一次反转
	i = 0; j = 0;
	while (i < s.size())
	{
		while (j < s.size() && s[j] != ' ') j++;
		reverse(s.begin() + i, s.begin() + j);

		j++;//记得++和顺序
		i = j;
	}
	//两次反转
	i = 0, j = s.size();
	reverse(s.begin() + i, s.begin() + j);
	return s;
}
//有n个数，两两组成二元组，相差最小的有多少对呢？相差最大呢？
//1.先排序
//特殊情况：如果排完序之后发现数组中所有数都相同，直接输出结果
//结果为：差最大个数 = 差最小个数 = （n * (n - 1)) / 2; (两两组合)
//2.统计数组中每种数字的个数（这里用的map）
//3.计算差最小个数
//3.1.如果数组中没有重复数字，说明最小差不为0，最小差肯定是数组中相邻两个数的差
//因此，遍历一边数组，计算并统计最小差。
//3.2.如果数组中有重复数字，说明最小差是0，此时，遍历一边map，数字个数不为0的
//数字会产生最小差0，利用公式计算即可
//4.计算差最大个数
//只有一种情况，最大值与最小值的两两组合，即最大值个数 * 最小值个数                                                                                                                     

//49. 字母异位词分组
vector<vector<string>> groupAnagrams(vector<string>& strs) {
	//通过了 不难  看一下哈希表
	unordered_map<string, vector<string>> hash;
	for (auto str : strs)
	{
		string s = str;
		sort(str.begin(), str.end());
		hash[str].push_back(s);
	}
	vector<vector<string>> res;
	for (auto str : hash)
	{
		res.push_back(str.second);
	}
	return res;

}
//外观数列
//不难 思路要对
string countAndSay(int n) {
	string s = "1";
	for (int i = 1; i < n; i++) {
		string ns = "";
		int l = 0, r = 0;
		for (; r < s.size(); ) {

			while (s[l] == s[r]) r++;
			ns += to_string(r - l);
			ns += s[l];
			l = r;
		}
		s = ns;
	}
	return s;
}
//3无重复字符的最长字符串 长度
int lengthOfLongestSubstring(string s) {
	unordered_map<char, int> hash;
	
	int res = 0;

	for (int i = 0, j = 0; j < s.size(); j++) {

		hash[s[j]]++;
		while (hash[s[j]] > 1) hash[s[i]]--, i++;
		res = max(res, j - i + 1);
	}
	return res;
}
//寻找连个有序数组的中位数
double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
	//自己写 行了
	int n = A.size();
	int m = B.size();
	int len = m + n;
	int left = 0, right = 0;
	int aStart = 0, bStart = 0;
	
	for (int i = 0; i <= len / 2; i++) {//注意条件小于等于

		left = right;
		if (aStart < n && (bStart >= m || A[aStart] < B[bStart])) {
			right = A[aStart++];
		}
		else {
			right = B[bStart++];
		}
	}
	cout << "left: " << left << "right: " << right << " len " << len << endl;
	if (len % 2)
		return right;
	else
		return (left + right) / 2.0;

}
#define ge 1
#define shi ge*25
#define bai shi*25
#define qian bai*25
//20分钟
long int ecode(string s) {
	vector<int> dig;
	int t = 0;

	for (int i = 0; i < s.size(); i++) {
		t = s[i] - 'a';
		//cout<<"t: "<<t<<endl;
		dig.push_back(t);
	}
	long int res = dig[0] * qian
		+ dig[1] * bai
		+ dig[2] * shi
		+ dig[3];
	return res;
}

long int ecode_all(string s) {
	string t;
	long int res;
	for (int i = 0; i < s.size() / 4; i++) {
		t = s.substr(i * 4, 4);
		res = ecode(t);
	}
	cout << res << endl;
	return res;
}

//肯定有其他坑  20分中
std::unordered_map<int, int> hash_1;//不能放外边？  hash 容易重复  
int finish_task(int x, int y) {
	
	
	int num[10];
	num[x >> 5] |= (1 << (x >> 5));
	num[y >> 5] & (1 << (y >> 5));

	if ((x < 1 || x >1024) || (y < 1 || y>1024)) {
		cout << int(-1) << endl;
		return 0;
	}
	hash_1[x] = 1;
	if (hash_1[y]) cout << int(1) << endl;
	else cout << int(0) << endl;
	return 1;
}

vector <int> get_all_prime(int x) {
	vector <int > res;
	for (int i = 2; i <= x; i++) {
			if(is_prime(i))
				res.push_back(i);
	}
	return res;
}

int isPrimeSum(int x, vector<int> num) {
	int count = 0;
	for (int i = 0, j = num.size() - 1; i < j;) {
		if ((num[i] + num[j]) == x) {
			count++;
		}
		else if ((num[i] + num[j]) > x)j--;
		else if ((num[i] + num[j]) < x)i++;
	}
	return count;
}

//特例 经纬度二分
int bsearch_3(int x, int l, int r, int n) {
	int res = 0;
	int count =1;
	while (l < r) {
		int mid = l + r  >> 1;
		if (mid > x) {
			r = mid ;
			res =res<< 1;
		}
		else {
			l = mid;
			res =res<< 1;
			res++;
		}
		if (count == n) break;
		else count++;
	}
	return res;
}



int get_circlestr_len(string &s) {
	int len = s.size() - 1;
	int max_len = 0;
	for (int mid = 0; mid <= len; mid++) {
		for (int l = mid, r = mid + 1; l >= 0 && r <= len;) {
			if (s[l] == s[r]) {
				l--, r++;
				max_len = max(max_len, r - l - 1);
			}
			else break;
		}
		for (int l = mid - 1, r = mid + 1; l >= 0 && r <= len;) {
			if (s[l] == s[r]) {
				l--, r++;
				max_len = max(max_len, r - l - 1);
			}
			else break;
		}
	}
	cout << len + 1 - max_len;
	return 0;
}


int dp2(int i, int j, string &s1, string &s2) {
	static vector<vector<int>> result(s1.length(), vector<int>(s2.length(), (0)));
	int res = 0;
	//base case;
	if (i = -1) return 0;
	if (j = -1) return 0;
	
	if (result[i][j] != 0)  return result[i][j];

	if (s1[i] == s2[j]) {
		result[i][j] = dp2(i - 1, j - 1, s1, s2);
	}
	else
		result[i][j] = min(min(dp2(i - 1, j - 1, s1, s2), dp2(i, j - 1, s1, s2)), dp2(i - 1, j, s1, s2)) + 1;
	return result[i][j];
}
//第一个转换为第二个字符串的最少操作 s12s2 用替换删除插入
int min_distance(string &s1, string &s2) {
	int i = s1.length() - 1;
	int j = s2.length() - 1;
	return dp2(i, j, s1, s2);
}
//
int dp3(int i, int j, string &s1, string &s2) {
	int len1 = s1.length(), len2 = s2.length();
	//static int result[len1][len2] = { 0 };
	static vector<vector<int>> result(s1.length()+1, vector<int>(s2.length()+1, (0)));//要+1
	//int [][]result  = new int[len1 + 1][len2 + 1]; //错误
	//初始化问题
	for (int i = 1; i <= len1; i++)
		result[i][0] = i;
	for (int j = 1; j <= len2; j++)
		result[0][j] = j;

	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			if (s1[i] == s2[j])//需要-1？
				result[i][j] = result[i - 1][j - 1];
			else {
				result[i][j] = min(min(result[i - 1][j - 1], result[i - 1][j]), result[i][j - 1]) + 1;
			}
		}
	}
	return result[len1][len2];
}

int dp4(int k, int n) {
	if (k == 1) return n;
	if (n == 0) return 0;
	static vector<vector<int>> result(k+1, vector<int>(n+1, (0)));//要
	static int res = 0;

	if (result[k][n] != 0)
		return result[k][n];

	int low = 1, high = n;	
	while (low <= high) {
		int mid = low + high > 1;
		int notbroken=dp4(k, n - mid);
		int brobroken = dp4(k - 1, mid - 1);
		if (notbroken > brobroken) {
			low =mid+1;
			result[k][n] = min(res, notbroken + 1);
		}
		else {
			high = mid-1;
			result[k][n] = min(res, brobroken + 1);
		}
	}
	return result[k][n];

	for (int i = 1; i <= n; i++)
		res = min(res, max(dp4(k, n - i), dp4(k - 1, i-1))+1);//ok
	return res;
}
//ctrl-c问题
int dp6(int n) {
	static vector<int> result(n+1, 0);
	result[0] = 0;

	if (result[n] != 0)
		return result[n];

	for (int i = 1; i <=n; i++) {
		int res = dp6(n - i) + 1;

		for (int j = 2; j <i; j++) {//注意j起始位置
			res = max(res, dp6(j - 2)*(i - j+1));
		}
		result[i] = res;
	}
	return result[n];
}
//正则表达式匹配  暂时可以 加了好多条件
bool dp5(string &s, string &pattern, int i, int j) {
	static int slen = s.length(),plen=pattern.length();

	if (j >= plen && i >= slen)
	{
		cout << "res: find " << "i: " << i << " j: " << j << endl;
		return true;
	}
	if (s[i] == pattern[j]) {
		cout << "res: 1" << "i: " << i << " j: " << j << endl;
		return dp5(s, pattern, i + 1, j + 1);
	}
		
	else if ((pattern[j] == '.' && j + 1 < plen && pattern[j + 1] != '*' )|| (pattern[j] == '.' && j + 1 == plen )) {
		cout << "res: 2" << "i: " << i << " j: " << j << endl;
		return dp5(s, pattern, i + 1, j + 1);
	}		
	else if (pattern[j] == '.' && j + 1 < plen && pattern[j + 1] == '*') {		
		while (i + 1 < slen && s[i] == s[i + 1]) i++;
		cout << "res: 3" << "i: " << i << " j: " << j << endl;
		return dp5(s, pattern, i + 1, j + 2);
	}
	else if (pattern[j] == '*'&& i - 1 >= 0) {
		while (i  < slen && s[i] == s[i - 1]) i++;
		cout << "res: 4" << "i: " << i << " j: " << j << endl;
		return dp5(s, pattern, i, j + 1);
	}
	else if (pattern[j] != s[i]) {
		cout << "res: 5" <<"i: "<<i<<" j: "<<j<< endl;
		return false;	
	}
	return false;
}


int main()

{
	//int res = bsearch_3(24, -90, 90, 6);;
	//cout << res << endl;;

	//for (int i = 5; i >= 0; i--)
	//{
	//	if (res &(1 << i))
	//		std::cout << "1";
	//	else std::cout << "0";
	//}

	int input=10;
	vector<int> test = { 1,2,3,4,6,7,6,6,6,6,8,8,9,3,4512,521,215,21,55,477,44,22,2 };
	//int test[20] = { 1,2,3,4,6,7,6,6,6,6,8,8,9,3 };
	//merge_sort(test, 0, test.size()-1);
	//heap_sort(test, test.size());
	//for (int i = 0; i <test.size(); i++) {
	//	cout << " " << test[i] << " ";
	//}
	//cout << "result: " << right_bound(test, 8) << endl;;
	//cout << isPrimeSum(input, get_all_prime(input));

	while (1) {
		string s, p;
		cout << "请输入" << endl;
		cin >> s >> p;
		cout << "dp5:  " << dp5(s, p, 0, 0) << endl;;
		system("pause");
	}

    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
