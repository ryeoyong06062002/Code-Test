#include "Stack.h"
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>


#define MAX 100

using namespace std;

// Hàm dùng trong chương trình
bool KT_PhepToan(string c);								// Kiểm tra phép toán
bool KT_ConSo(string c);									// Kiểm tra con số
int DD_PhepToan(string c);									// Định Dạng phép toán	
bool KT_DauNgoac(string s);							
bool KT_SoThuc(string s);
bool KT_Ham(string s);
double TT_Ham(string func, string num);
string TT_2_PhepToan(string opt1, string opt2, string opt);
string trim(string s);
string trim_0(string s);
string Xl_ChuoiHam(string s);
string tinhToan(string s);

// Cài đặt các hàm trên
bool KT_PhepToan(string c) {

	if (c.length() > 1) return false;

	return (c == "+") ? true :
		(c == "-") ? true :
		(c == "*") ? true :
		(c == "/") ? true :
		(c == "^") ? true : false;
}

bool KT_ConSo(string c) {

	if (KT_PhepToan(c)) return false;

	for (int i = 0; i < c.length(); i++) {
		if ((int(c[i]) >= 48 && int(c[i]) <= 57) || c[i] == '.') continue;
		else {
			return false;
		}
	}
	return true;
}

int DD_PhepToan(string c) {
	if (c == "+" || c == "-") return 1;
	if (c == "*" || c == "/") return 2;
	if (c == "^") return 3;
}

bool KT_DauNgoac(string s) {

	string x = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(' || s[i] == ')') x += s[i];
	}

	Stack<char> stack;
	for (int i = 0; i < x.length(); i++) {
		if (x[i] == '(') {
			stack.push(x[i]);
		}
		else if (x[i] == ')') {
			if (stack.get() != '(') return false;
			stack.pop();
		}
	}
	return true;
}

bool KT_SoThuc(string s) {

	bool isMeetDot = false;

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '.') {
			if (!isMeetDot) isMeetDot = true;
			else {
				return false;
			}
		}
		else if (
			s[i] == '+' ||
			s[i] == '-' ||
			s[i] == '*' ||
			s[i] == '/' ||
			s[i] == '^' ||
			s[i] == '(' ||
			s[i] == ')') {

			isMeetDot = false;
		}
	}

	return true;
}

// Cài đặt hàm tính toán thông dụng (sử dụng bảng chữ cái in thường)
bool KT_Ham(string s) {
	if (int(s[0]) >= 97 && int(s[0] <= 122)) return true;
	else return false;
}

double TT_Ham(string func, string num) {
	double _num = stod(num);

	if (func == "sqrt") {
		return (double)sqrt(_num);
	}
	else if (func == "exp") {
		return (double)exp(_num);
	}
	else if (func == "sin") {
		return (double)sin(_num);
	}
	else if (func == "cos") {
		return (double)cos(_num);
	}
	else if (func == "tan") {
		return (double)tan(_num);
	}
	else if (func == "cot") {
		return (double)(1 / tan(_num));
	}
	else if (func == "abs") {
		return (double)fabs(_num);
	}
	// Thêm những dòng này nếu bạn muốn thêm nhiều chức năng
//	else if (func == "name func") {
//		return (double)["name func"](_num);
//	}
}

string TT_2_PhepToan(string opt1, string opt2, string opt) {

	double a, b, res;

	// Xử lí toán hạng 1
	a = stod(opt1);

	// Xử lí toán hạng 2
	b = stod(opt2);

	// Thực hiện tính toán
	if (opt == "+") {
		res = b + a;
	}
	else if (opt == "-") {
		res = b - a;
	}
	else if (opt == "*") {
		res = b * a;
	}
	else if (opt == "/") {
		res = b / a;
	}
	else if (opt == "^") {
		res = pow(b, a);
	}

	return std::to_string(res);
}

string trim(string s) {
	string x = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != ' ') x += s[i];
	}
	return x;
}

string trim_0(string s) {
	string res = s;

	while (res[res.length() - 1] == '0') {
		res.erase(res.length() - 1);
	}
	if (res[res.length() - 1] == '.') res.erase(res.length() - 1);

	return res;
}

/*
		Hàm này được sử dụng để xử lý giá trị hàm
		Nếu bên trong hàm là một biểu thức hoặc biểu thức có chứa các hàm khác
		-> tinhToan (biểu thức);
*/
string Xl_ChuoiHam(string s) {
	string x = "";	// Chuỗi chứa tên hàm
	int i = 0;		// Biến chỉ số của chuỗi s

	while (s[i] != '(') {	// Chạy vòng lặp cho đến khi gặp dấu '('
		x += s[i];			// Thêm từng chữ cái của tên hàm
		i++;				// Tăng biến đếm để đến chữ cái tiếp theo
	}
	i++;					// Bỏ qua dấu '('
	string num = "";		// Chuỗi chứa giá trị bên trong dấu ngoặc "()"
	while (i < s.length() - 1) {	// Chạy cho đến trước dấu ')' cuối cùng để đảm bảo rằng chúng ta nhận tất cả giá trị bên trong dấu ngoặc
		num += s[i];				// Thêm từng chữ cái của giá trị đó
		i++;						// Tương tự với trường hợp trên
	}

	// Sau khi nhận được 2 danh mục, x là tên hàm và num là giá trị bên trong dấu ngoặc ta tiến hành
	// -> TT_Ham(x, tinhToan(num))
	// Trong trường hợp này, hàm tinhToan () được gọi vì chúng ta không biết trong chuỗi num có gì 
	// Nó có thể có bất kỳ biểu thức hoặc biểu thức nào chứa hàm hay không ?
	return std::to_string(TT_Ham(x, tinhToan(num)));
}

/*
	Hàm này được sử dụng để giải quyết một biểu thức chuỗi
	Đầu vào có thể là:
		"1+2+3"
		"0.1*0.1"
		"100-50/(1+1)"
		"10+sqrt(25)"
		"30+sqrt(-(sqrt(81))+8)"
		...
*/
string tinhToan(string s) {
	string infix[MAX];
	string component = "";

	// Chuyển đổi chuỗi đầu vào thành mảng chứa từng thành phần
	int in_idx = 0;
	int i = 0;
	while (i < s.length()) {
		if (int(s[i]) >= 97 && int(s[i] <= 122)) {
			string x = "";
			int cntOpenBracket = 0;
			while (1) {
				if (s[i] == '(') cntOpenBracket++;
				if (s[i] == ')') {
					cntOpenBracket--;
					if (cntOpenBracket == 0) break;
				}
				x += s[i];
				i++;
			}
			x += s[i];

			// Em đã sử dụng biến thành phần ở đây trong trường hợp trước khi tên hàm là toán tử giá trị con
			// Trong trường hợp này, chúng ta biết chính xác rằng x là một hàm, vì vậy chúng ta cần gọi Xl_ChuoiHam () để giải quyết nó
			// Và trả về nó dưới dạng một số
			infix[in_idx++] = component + Xl_ChuoiHam(x);

			// Sau khi giải quyết xong, chúng ta cần đặt lại biến thành phần cho lần sau, nếu có
			component = "";
		}
		else if (s[i] == '+' ||
			s[i] == '-' ||
			s[i] == '*' ||
			s[i] == '/' ||
			s[i] == '^' ||
			s[i] == '(' ||
			s[i] == ')') {
			if (s[i] == '-') {
				if (i == 0) {
					component += s[i];
				}
				else if (s[i - 1] == '+' || s[i - 1] == '-' || s[i - 1] == '*' || s[i - 1] == '/' || s[i - 1] == '^' || s[i - 1] == '(') {
					if (component == "-") component = "";
					else if (component == "+") component = "-";
					else component = "-";
				}
				else {
					infix[in_idx++] = s[i];
				}
			}
			else if (s[i] == '+') {
				if (i == 0) {
					// Ta không làm gì ở trường hợp này
				}
				else if (s[i - 1] == '+' ||
					s[i - 1] == '-' ||
					s[i - 1] == '*' ||
					s[i - 1] == '/' ||
					s[i - 1] == '^' ||
					s[i - 1] == '(') {
					if (component == "-") component = "-";
					else if (component == "+") component = "";
					else component = "";
				}
				else {
					infix[in_idx++] = s[i];
				}
			}
			else {
				infix[in_idx++] = s[i];
			}
		}
		else {
			if (i + 1 < s.length()) {
				if (s[i + 1] == '+' ||
					s[i + 1] == '-' ||
					s[i + 1] == '*' ||
					s[i + 1] == '/' ||
					s[i + 1] == '^' ||
					s[i + 1] == '(' ||
					s[i + 1] == ')') {
					infix[in_idx++] = component + s[i];
					component = "";
				}
				else {
					component += s[i];
				}
			}
			else {
				infix[in_idx++] = component + s[i];
				component = "";
			}
		}
		i++;
	}

	//	for (i = 0; i < in_idx; i++) cout << infix[i] << " ";
	//	std::system("pause");

	// Chuyển đổi infix thành postfix
	string postfix[MAX];
	int pos_idx = 0;
	Stack<string> stack;

	for (int i = 0; i < in_idx; i++) {

		string t = infix[i];

		if (KT_ConSo(t) || (t[0] == '-' && t.length() > 1)) {
			postfix[pos_idx++] = infix[i];
		}
		else if (t == "(") {
			stack.push(t);
		}
		else if (KT_PhepToan(t)) {
			if (stack.isEmpty()) stack.push(t);
			else {

				if (stack.get() == "(") stack.push(t);
				else {
					int prior = DD_PhepToan(t);

					// TH1: dấu +, -
					if (prior == 1) {
						postfix[pos_idx++] = stack.pop();
						stack.push(t);
					}
					// TH2: dấu *, /
					else if (prior == 2) {
						// Nếu toán tử ở đỉnh stack là +, - 
						// => Độ ưu tiên nhỏ hơn => Không pop(), chỉ push()
						if (DD_PhepToan(stack.get()) == 1) stack.push(t);

						// Nếu toán tử ở đỉnh stack
						// => Cùng độ ưu tiên => pop(), sau đó push()
						else if (DD_PhepToan(stack.get()) == 2 || DD_PhepToan(stack.get()) == 3) {
							postfix[pos_idx++] = stack.pop();
							stack.push(t);
						}
					}
					// TH3: dấu ^
					else if (prior == 3) {
						// Nếu toán tử là +,-,*,/ -> độ ưu tiên nhỏ hơn => chỉ push()
						if (DD_PhepToan(stack.get()) == 1 || DD_PhepToan(stack.get()) == 2) stack.push(t);

						// Ở đỉnh stack là dấu ^ thì mới pop(), sau đó push()
						else if (DD_PhepToan(stack.get()) == 3) {
							postfix[pos_idx++] = stack.pop();
							stack.push(t);
						}
					}
				}
			}
		}
		else if (t == ")") {
			while (stack.get() != "(") {
				postfix[pos_idx++] = stack.pop();
			}

			// Pop dấu "(" ra sau khi xử lí xong dấu ")"
			stack.pop();
		}
	}

	while (!stack.isEmpty()) {
		postfix[pos_idx++] = stack.pop();
	}

	//	for (i = 0; i < in_idx; i++) cout << posfix[i] << " ";
	//	std::system("pause");

	// Process posfix
	// Quy tắc:
	// + Nếu là toán hạng -> push()
	// + Nếu là toán tử -> opt1 = pop(), opt2 = pop()
	//					-> Tính res = opt2 [toán tử] opt1 -> push(res)

	// TH chỉ có 1 toán hạng
	if (pos_idx == 1) {
		return trim_0(postfix[0]);
	}

	for (i = 0; i < pos_idx; i++) {
		string t = postfix[i];

		// TH: là toán hạng hoặc là hàm
		if (KT_ConSo(t) || (t[0] == '-' && t.length() > 1)) stack.push(t);

		// TH là toán tử
		if (KT_PhepToan(t)) {
			string opt1 = stack.pop();
			string opt2 = stack.pop();

			stack.push(TT_2_PhepToan(opt1, opt2, t));
		}
	}

	// Xử lý và trả kết quả
	string res = stack.pop();

	return trim_0(res);
}

int main() {


	string s;
	cout << "Nhap Mot Bieu Thuc infix: ";
	getline(cin, s);
	cout << "Ket Qua: ";

	if (!KT_DauNgoac(s)) {
		cout << "Nhap Sai! ";
		std::system("pause");
		return 0;
	}
	if (!KT_SoThuc(s)) {
		cout << "Nhap Sai! ";
		std::system("pause");
		return 0;
	}

	s = trim(s);

	cout << tinhToan(s) << endl;

	std::system("pause");
}