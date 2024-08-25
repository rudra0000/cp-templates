void phi_1_to_n(int n) {
    vector<int> phi(n + 1); //initialize this globally
    for (int i = 0; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}
//why subtract phi[j]/i from phi[j]
/*
The main reason we subtract phi[j]/i instead of j/i is that phi[j] gets progressively reduced for each prime factor i. This reduction method accounts for all prime factors influencing j.

Initial Step: Assume j is only divisible by i. Initially, phi[j] is j, and subtracting j/i would be equivalent to phi[j]/i.
Subsequent Steps: However, if j has more than one prime factor, phi[j] would have already been reduced by previous steps. For example, if j is divisible by both p and q (where p < q), then after processing p, phi[j] is no longer equal to j, but rather j - j/p.
Now, when processing the prime factor q, the subtraction must be proportional to the current value of phi[j], not the original j. This ensures that each prime factor reduces phi[j] by its appropriate fraction:

After processing p, phi[j] becomes j(1 - 1/p).
When processing q, we subtract phi[j]/q, which is now correctly proportional to the remaining coprime count.
*/




int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}