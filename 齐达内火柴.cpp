Description

7、Matches

Zidane is a weird arithmetic expert. Unlike other mathematician, he loves using matches to represent numbers as illustrated in Fig.1. 



 

Fig.1

One day Zidane “wrote”an equation on his desk and then went out. The equation was in “A + B = C” format. A, B, and C were numbers made up by matches. “+” and “=” were wrote in ink. 

When Zidane came back after a lecture, he found out that somebody must have touched the equation and the equation became wrong! After promised a new toy, Zidane's son confessed that he had broken in the room and moved ONE match (not removed, that match was still in the equation). Given the wrong equation on his desk, can you help Zidane find the original one? 

Note: Both the wrong and original equations may have numbers with leading zeros. And it is guaranteed that only ONE possible original equation exists.

Input

The input consists of several test cases. Each test case is a single line representing a wrong equation. Each wrong equation is in the format of “A + B = C” (A, B and C are all numbers), and consists of no more than 100000 characters. 

Output

Output the original equation in a single line followed by 17 “*” for each test

case. 

Sample Input

0 + 7 = 9

9 + 80 = 8

Sample Output

8 + 1 = 9

*****************

8 + 00 = 8

翻译：齐达内是一个奇怪的算术专家。不像其他的数学家，他喜欢用火柴来代表数字如图1所示。有一天，齐达内在他的桌子上写了一个等式，然后就出去了.。方程为“A + B = C”格式。A、B和C是由火柴组成的数字。“+”和“=”写在 墨水。

当齐达内在一次演讲后回来时，他发现有人肯定摸过了方程，方程式就错了.！在答应了一个新玩具后，齐达内的儿子承认他已经在房间里摔坏了，移动了一根火柴（没有取出，那火柴还在等式里）。鉴于他的桌子上有错误的等式，你能帮齐达内找到原来的吗？ 

注：错误的和原始的方程可以有前导零的数字。并保证只有一个可能的原始方程存在。

输入：输入由几个测试用例。每个测试用例是一个表示错误方程的单行.。每一个错误的公式是“A + B = C”的格式（A，B和C都是数字），并由不超过100000个字符。

二、问题叙述
齐达内是一个奇怪的算术专家。不像其他的数学家，他喜欢用火柴来代表数字。

一天，齐达内说道：“他桌上原本有一个方程，然后他出去了。方程为“A + B = C”格式。A，B，和C分别由匹配数表示。“+”和“=”是用墨水写的。当齐达内在演讲后回来时，他发现肯定有人动了方程，方程式就错了.！在答应了给他儿子买一个新玩具后，齐达内的儿子承认他在房间里弄坏的，移动了一根火柴（没有取出，那火柴还在等式里）。鉴于他的书桌上错误的方程，你能帮齐达内找到原来的吗？

注：无论是错误的还是原方程组可以带前导零的数字。必须保证只有一个可能存在的原始方程。输入包含多个测试案例。每个测试用例都是代表一个错误的方程一行。每一个错误的公式是“A + B = C”的格式（A，B和C都是数字），并由不超过100000个字符组成。输出一行跟着17“*”为每个测试案例的原始方程。

 

样本输入：

0 + 7 = 9

9 + 80 = 8

 

样本输出：

*****************

              1 + 8 = 9

8 + 00 = 8

*****************

三、问题分析
这次问题主要来源于火柴问题，并进行了相应的变形。传统的火柴问题是要求移动火柴使得等式成立，而这次的题目要求，给出一个错误的方程，要求推导出正确的方程。其中方程的表现形式为A + B = C 的形式的，方程是由火柴摆成的。因此这次的问题只是对传统火柴问题的变形。我们可以用动态规划进行求解。

四、概要设计
实验要求对错误的火柴等式进行还原，我们考虑到动态规划的思想，对问题进行动态规划的分析，可以知道该问题可以通过动态规划的方法求得。把多阶段过程转化为一系列单阶段问题，利用各阶段之间的关系，逐个求解。动态规划程序设计往往是针对一种最优化问题，由于各种问题的性质不同，确定最优解的条件也互不相同，因而动态规划的设计方法对不同的问题，有各具特色的解题方法，而不存在一种万能的动态规划算法，可以解决各类最优化问题。

五、详细设计
该程序代码用到了动态规划的思想，首先创建数组dp_state[i][j][k]。其中i代表保存从

A[0…i]+B[0…i]==C[0…i]，而j取值为[0，3]，其含义分别为：

当 j==0,从0至i无火柴移动

当 j==1,从0至i拿走一根火柴

      当 j==2, 0至i数位移入一根火柴

当 j==3, 0至i数位中一根火柴被移动且放入该数位区间。

k=0，1代表了A[i]+B[i] + carry>= 10, 如果10 <= A[i]+B[i]+carry，则k=1代表需向前进位。

设函数F(I,J,carry)代表j取值[0,3]时，在A[i],B[i],C[i]对应数位操作可否让(A[i]+B[i]+carry)%10==C[i]成立

DP状态转移方程如下

dp_state[i][0][0] ={ (dp_state [i-1][0][0]&&F(I,0,0)||(dp_state [i-1][0][0]&&F(I,0,1))&& A[i]+B[i]+carry < 10}

dp_state[i][0][1] = {(dp_state [i-1][0][0]&&F(I,0,0)|| (dp_state [i-1][0][0]&&F(I,0,1))&& A[i]+B[i]+carry >= 10}

类似可推导dp_state[i][j][k]其余对应转移.

六、调试分析
由于实验的代码涉及到了string类的定义，在改正的过程中遇到了没有解决的问题，因此在老师和同学的帮助下，我们换了一个运行的软件系统，一个可以兼容该类的环境。最终运行的结果如下所示;

  Output Size: 1.80714988708496 MiB

Compilation Time: 3.32s

实验过程中占用的字节数为1.807149MiB，运行的整个花费的时间为3.32秒。
#include<iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

/************************************************************************/

void  move_to_other(int deep,bool had, int* n, int op, int pos, int s,int preop, int one = 0);

bool  unchange_add(int pos, int s, int preop, int one = 0);

void  move_to_orgin(int deep, int op, int* n, int pos, int s, int preop, int one = 0);

void print_ans(int mn);

/************************************************************************/

struct Point

{  int x,y;  };

#define BUFSIZE 100010

struct  State {

int n[3];

int op;

bool is_ok;

State() {

n[2] = n[1]= n[0] = 0;

op = -1;

is_ok = false;  }

void reset() {

n[2] = n[1]= n[0] = 0;

op = -1;

is_ok = false;  }

};

State dp_state[BUFSIZE][4][2];

vector<int>convert_n[10][3];

string num[3];

string ans_num[3];

char buf[BUFSIZE];



void init() {//0->change one stick, remove stick, add stick

convert_n[0][0].push_back(0);

convert_n[0][0].push_back(6);

convert_n[0][0].push_back(9);

convert_n[0][2].push_back(8);

convert_n[1][0].push_back(1);

convert_n[1][2].push_back(7);

convert_n[2][0].push_back(2);

convert_n[2][0].push_back(3);

convert_n[3][0].push_back(3);

convert_n[3][0].push_back(2);

convert_n[3][0].push_back(5);

convert_n[3][2].push_back(9);

convert_n[4][0].push_back(4);

convert_n[5][0].push_back(5);

convert_n[5][0].push_back(3);

convert_n[5][2].push_back(6);

convert_n[5][2].push_back(9);

convert_n[6][0].push_back(6);

convert_n[6][0].push_back(0);

convert_n[6][0].push_back(9);

convert_n[6][1].push_back(5);

convert_n[6][2].push_back(8);

convert_n[7][0].push_back(7);

convert_n[7][1].push_back(1);

convert_n[8][0].push_back(8);

convert_n[8][1].push_back(0);

convert_n[8][1].push_back(6);

convert_n[8][1].push_back(9);

convert_n[9][0].push_back(9);

convert_n[9][0].push_back(0);

convert_n[9][0].push_back(6);

convert_n[9][1].push_back(3);

convert_n[9][1].push_back(5);

convert_n[9][2].push_back(8);

}

void  move_to_orgin(int deep, int op, int* n, int pos, int s, int preop, int one/* = 0*/)

 {      //op 1有移入matches -1,移走 matches

if (deep == 3) {

if (0x03 != op)

return;

bool res = (n[2] == ((n[0] + n[1] + one)%10));

int carry = (n[0]+n[1]+one)/10;

if (res) {

dp_state[pos][s][carry].is_ok = true;

dp_state[pos][s][carry].op = preop;

memcpy(dp_state[pos][s][carry].n, n, sizeof(int)*3);

}

return;}

 else {

if (pos < num[deep].length()) {

int v = num[deep][pos] - '0';

int new_op = 0;

if ((op&0x1) == 0) {

for (int i = 0;  i < convert_n[v][1].size(); ++i) {

n[deep] = convert_n[v][1][i];

new_op = (op|0x1);

move_to_orgin(deep + 1, new_op, n, pos, s, preop, one);

}

}

if ((op&0x2) == 0) {

for (int i = 0;  i < convert_n[v][2].size(); ++i) {

n[deep] = convert_n[v][2][i];

new_op = (op|0x2);

move_to_orgin(deep + 1, new_op, n, pos, s, preop, one);

}

}

if ((0 == op)) {

for (int i = 0; i < convert_n[v][0].size(); ++i) {

n[deep] = convert_n[v][0][i];

new_op = 0x3;

move_to_orgin(deep + 1, new_op, n, pos, s,preop, one);

}

}

n[deep] = v;

move_to_orgin(deep + 1, op, n, pos, s,preop, one);

} else {

n[deep] = 0;

move_to_orgin(deep + 1, op, n, pos, s, preop, one);

}


}

}

void  move_to_other(int deep,bool had, int* n, int op, int pos, int s,int preop, int one/* = 0*/) {//op = 1, 2

if (deep == 3) {

if (false == had)

return;

bool res = (n[2] == (n[0] + n[1] + one)%10);

int carry = (n[0]+n[1]+one)/10;

if (res) {

dp_state[pos][s][carry].is_ok = true;

dp_state[pos][s][carry].op = preop;

memcpy(dp_state[pos][s][carry].n, n, sizeof(int)*3);

}

return;

} else {

if (pos < num[deep].length()) {

int v = (int)(num[deep][pos] - '0');

if (!had) {

for (int i = 0;  i < convert_n[v][op].size(); ++i) {

n[deep] = convert_n[v][op][i];

move_to_other(deep + 1, true, n, op, pos, s, preop, one);

}

}

n[deep] = v;

move_to_other(deep + 1, had, n, op, pos, s, preop, one);

} else {

n[deep] = 0;

move_to_other(deep + 1, had, n, op, pos, s, preop, one);

}


}

return ;

}

bool  unchange_add(int pos, int s, int preop, int one/* = 0*/) {

int n[3] = {0};

for (int i = 0; i < 3; ++i) {

if (pos < num[i].length())  {

n[i] = (int)(num[i][pos] - '0');

}

}

bool res = (n[2] == (n[0] + n[1] + one)%10);

if (res) {

int carry = (n[0]+n[1] + one)/10;

dp_state[pos][s][carry].is_ok = true;

dp_state[pos][s][carry].op = preop;

memcpy(dp_state[pos][s][carry].n, n, sizeof(int)*3);

}

return res;

}

void dp_solve() {

int mn = 0;

for (int i = 0; i < 3; ++i) {

reverse(num[i].begin(), num[i].end());

if (mn < num[i].length()) {

mn = num[i].length();

}

}

for (int i = 0; i< mn; ++i) {

for (int j = 0; j < 4; ++j) {

for (int k = 0; k < 2; ++k) {

dp_state[i][j][k].reset();

}

}

}

for (int i = 0; i < mn; ++i) {

if (0 == i) {

unchange_add(0,0, 0);

int n[3] = {0};

move_to_other(0, false,n, 1, 0, 1, 0, 0);

move_to_other(0, false,n, 2, 0, 2, 0, 0);

move_to_orgin(0, 0, n, 0, 3, 0);

} else {

int n[3] = {0};

//case j ==0

if (dp_state[i-1][0][0].is_ok) {

unchange_add(i, 0, 0, 0);

move_to_other(0, false, n, 1, i, 1, 0, 0);

move_to_other(0, false, n, 2, i, 2, 0, 0);

move_to_orgin(0, 0, n, i, 3, 0, 0);

}

if (dp_state[i-1][0][1].is_ok) {

unchange_add(i, 0, 0, 1);

move_to_other(0, false, n, 1, i, 1, 4, 1);

move_to_other(0, false, n, 2, i, 2, 4, 1);

move_to_orgin(0, 0, n, i, 3, 4, 1);

}

for (int j = 1; j <= 3; ++j) {

if (dp_state[i-1][j][0].is_ok) {

unchange_add(i, j, j, 0);

}

if (dp_state[i-1][j][1].is_ok) {

unchange_add(i, j, 4 + j, 1);

}

}

if (dp_state[i-1][1][0].is_ok) {

move_to_other(0, false, n, 2, i, 3, 1, 0);

}

if (dp_state[i-1][1][1].is_ok) {

move_to_other(0, false, n, 2, i, 3, 5, 1);

}

if (dp_state[i-1][2][0].is_ok) {

move_to_other(0, false, n, 1, i, 3, 2, 0);

}

if (dp_state[i-1][2][1].is_ok) {

move_to_other(0, false, n, 1, i, 3, 6, 1);

}

}

}

print_ans(mn);

}

void insert_ans(int pos, int n[]) {

for (int i = 0; i < 3; ++i) {

if (pos < num[i].length()) {

ans_num[i].append(1, n[i] + '0');

}

}

}

void print_ans(int mn) {

int preop = -1;

for (int i = mn - 1; 0 <= i; --i) {

if (i == (mn - 1)) {

preop = dp_state[mn-1][3][0].op;

insert_ans(mn-1, dp_state[mn-1][3][0].n);

} else {

int j = preop%4;

int k = preop/4;

preop = dp_state[i][j][k].op;

insert_ans(i, dp_state[i][j][k].n);

}

}

printf("%s + %s = %s\n", ans_num[0].c_str(), ans_num[1].c_str(), ans_num[2].c_str());

printf("*****************\n");   }

void reset_init() {

for (int i = 0; i < 3; ++i) {

num[i].clear();

ans_num[i].clear();  }

}

int main()

{

char c;

int cur_idx = 0;

init();

while (gets(buf)) {

int len = strlen(buf);

for (int i = 0; i < len; ++i) {

char c = buf[i];

if ('0' <= c && c <= '9') {

num[cur_idx].append(1,c);

} else {

if (' ' == c && num[cur_idx].length() > 0){

cur_idx = (cur_idx + 1) % 3; }

}

}

cur_idx = 0;

dp_solve();

reset_init();  }

return 0;   }

