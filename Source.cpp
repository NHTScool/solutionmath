#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;
string a[110];
bool kttt(char i) {
	if (i == '*' || i == '/' || i == '+' || i == '-'|| i=='^')
		return true;
	else return false;
}
bool ktth(char i) {
	if (i >= '0' && i <= '9') return true;
	else return false;
}
bool ktpt(char i) {
	if (i >= 'a' && i <= 'z') return true;
	else return false;
}
int uutien(char i) {
	if (i == '+' || i == '-') return 1;
	if (i == '*' || i == '/') return 2;
	if (i == '^') return 3;
	return 0;
}

string chuyendoi1(string& s) {
	string kq = "";
	int dem;
	char luu = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ' ') continue;
		if (ktth(s[i])) {
			kq += s[i];
			dem = i + 1;
			while ( dem < s.size() && (ktth(s[dem]) || s[dem] == '.')) {
				kq += s[dem];
				s.erase(dem, 1);
			}
			a[luu] = kq;
			s[i] = luu + 97;
			luu++;
			kq = "";
		}
	}
	return s;
}

string chuyendoi(string s) {
	string kq = "";
	stack <char> luu;
	int n = s.size();
	for (int i = 0; i < n; i++) {
		if (s[i] == '(') {
			luu.push(s[i]);
		}
		else if (ktpt(s[i]))
			kq += s[i];
		else if (s[i] == ')') {
			while (true) {
				if (luu.top() != '(') {
					kq += luu.top();
					luu.pop();
				}
				else {
					luu.pop();
					break;
				}
			}
		}
		else if (kttt(s[i])) {
			while (!luu.empty() && uutien(luu.top()) >= uutien(s[i]))
			{
				kq += luu.top();
				luu.pop();
			}
			luu.push(s[i]);
		}
	}
	while (!luu.empty()) {
		kq += luu.top();
		luu.pop();
	}
	return kq;

}
//khai bao
struct node {
	double data;
	node* left;
	node* right;
};
typedef struct node* Tree;

node* get_node(double i) {
	node* p = new node();
	p->data = i;
	p->left = NULL;
	p->right = NULL;
	return p;
}
typedef struct node* tree;
void init(tree& t) {
	t = NULL;
}
int emptytree(tree t) {
	return t == NULL;
}
tree lefttree(tree t) {
	if (t != NULL)  return t->left;
}
tree righttree(tree t) {
	if (t != NULL)  return t->right;
}
int ktnutla(tree t) {
	if (t != NULL) {
		return (lefttree(t) == NULL && righttree(t) == NULL);
	}
	else return 0;
}
// toa cay  nhi phan
void taocay(tree& t, string s) {
	stack <tree>  luu;
	int n = s.size();
	for (int i = 0; i < n; i++) {
		if (ktpt(s[i])) {
			int k = s[i] -97;
			double p = std::stof(a[k]);
			t = get_node(p);
			luu.push(t);
		}
		if (kttt(s[i])) {
			t = get_node(s[i]);
			t->right = luu.top();
			luu.pop();
			t->left = luu.top();
			luu.pop();
			luu.push(t);
		}
	}
	while (!luu.empty()) {
		t = luu.top();
		luu.pop();
	}
}
// tinh gia tri cay 
double tgtbt(char dau, double a, double b) {
	if (dau == '*') return (a * b);
	else if (dau == '+') return (a + b);
	else if (dau == '-') return (a - b);
	else if (dau == '/')
	{
		if (b == 0)
		{
			cout << " phep tinh khong hop le khong the chia cho 0" << endl;
			exit(0);
		}
		else return(a / b);
	}
	else if (dau == '^') return pow(a, b);
}
double tinhcay(tree t) {
	double a, b; 
	if (!emptytree(t)) {
		if (ktnutla(t)) 
			return (t->data);
	}
	a = tinhcay(lefttree(t));
	b = tinhcay(righttree(t));
	return tgtbt(t->data, a, b);
}


int main() {
	while (1) {
		tree t;
		string s;
		cout << "nhap bieu thuc : ";
		getline(cin, s);
		if (s[0] == '\0') return 0;
		if (s[0] == '-') s = '0' + s;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '(' && s[i + 1] == '-') {
				s.insert(i, 1, '0');
				i++;
			}
		}
		string kq;
		kq = chuyendoi1(s);
		//cout << kq << endl;
		kq = chuyendoi(s);
		//cout << kq << endl;
		taocay(t, kq);
		//cout <<"ket qua cua bieu thuc = " << tinhcay(t) << endl;
		cout << "gia tri cua bieu thuc la ";
		std::cout << std::fixed << std::setprecision(3) << tinhcay(t) << std::endl;
		cout << endl;
	}
}