/**
 * Author: cp-algo
 * Date: 2025-07-20
 * Description: The Speedup is applied for transitions of the form
 * $$dp(i, j) = \min_{i \leq k < j} [ dp(i, k) + dp(k+1, j) + C(i, j) ].$$ 
 * Similar to divide and conquer DP, let  
 * $opt(i, j)$  be the value of  
 * $k$  that minimizes the expression in the transition ( 
 * $opt$  is referred to as the "optimal splitting point" further in this article). The optimization requires that the following holds:
 * $$opt(i, j-1) \leq opt(i, j) \leq opt(i+1, j).$$ 
 * We can show that it is true when the cost function  
 * $C$  satisfies the following conditions for  
 * $a \leq b \leq c \leq d$ :
 * $C(b, c) \leq C(a, d)$ ;
 * $C(a, c) + C(b, d) \leq C(a, d) + C(b, c)$  (the quadrangle inequality [QI]).
 * This result is proved further below.
 */

int solve() {
    int N;
    ... // read N and input
    int dp[N][N], opt[N][N];

    auto C = [&](int i, int j) {
        ... // Implement cost function C.
    };

    for (int i = 0; i < N; i++) {
        opt[i][i] = i;
        ... // Initialize dp[i][i] according to the problem
    }

    for (int i = N-2; i >= 0; i--) {
        for (int j = i+1; j < N; j++) {
            int mn = INT_MAX;
            int cost = C(i, j);
            for (int k = opt[i][j-1]; k <= min(j-1, opt[i+1][j]); k++) {
                if (mn >= dp[i][k] + dp[k+1][j] + cost) {
                    opt[i][j] = k; 
                    mn = dp[i][k] + dp[k+1][j] + cost; 
                }
            }
            dp[i][j] = mn; 
        }
    }

    return dp[0][N-1];
}