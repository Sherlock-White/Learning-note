#include<iostream>
#include<string>

#define MAX_SIZE 1005
#define INF 99999999

using namespace std;

class Locker {
private:
    string _cur;
    string _des;
    int _len;
    int _newStep;
    int _dp[MAX_SIZE][15][15];
public:
    //init every element in _dp as INFINITY，which is the fundemental of searching for the shortest path
    //将_dp每个元素都初始化为正无穷,作为搜索最短路径的基础
    Locker(string cur, string des) :_cur(cur), _des(des) {
        _len = cur.length();
        _newStep = INF;
        for (int i = 0; i <= _len; i++) {
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 10; k++) {
                    _dp[i][j][k] = INF;
                }
            }
        }
        _dp[0][0][0] = 0;
    }

    void run() {
        for (int i = 0; i < _len; i++) {
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 10; k++) {
                    if (_dp[i][j][k] != INF) {
                        //for the digits can be rotated up or down, so there are two direct differences between _cur[i] and _des[i]
                        //因为数字能被向上或向下旋转，因此在_cur[i]和_des[i]之间直接的差值有两种
                        int differ1 = (_des[i] - _cur[i] - j + 20) % 10;
                        int differ2 = 10 - differ1;

                        _newStep = _dp[i][j][k] + differ1;
                        for (int m = 0; m <= differ1; m++) {
                            for (int n = 0; n <= m; n++) {
                                if (_newStep < _dp[i + 1][(k + m) % 10][n]) {
                                    _dp[i + 1][(k + m) % 10][n] = _newStep;
                                }
                            }
                        }

                        _newStep = _dp[i][j][k] + differ2;
                        for (int m = 0; m <= differ2; m++) {
                            for (int n = 10; n >= 10 - m; n--) {
                                if (_newStep < _dp[i + 1][(k - m + 10) % 10][n % 10]) {
                                    _dp[i + 1][(k - m + 10) % 10][n % 10] = _newStep;
                                }
                            }
                        }
                    }
                }
            }
        }
        cout << _dp[_len][0][0] << endl;
    }
};

int main() {
    string cur, des;
    while (cin >> cur >> des) {
        Locker locker(cur,des);
        locker.run();
    }
    return 0;
}