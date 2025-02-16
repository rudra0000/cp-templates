 vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

vector<int> kmp_search(string text, string pattern) {
    string s = pattern + "#" + text; // Concatenate with a separator
    int m = pattern.size(), n = s.size();
    vector<int> pi = prefix_function(s);
    vector<int> occurrences;
    
    for (int i = m + 1; i < n; i++) {
        if (pi[i] == m)  // Full match of the pattern
            occurrences.push_back(i - 2 * m); // Compute the starting index in text
    }
    
    return occurrences;
}
