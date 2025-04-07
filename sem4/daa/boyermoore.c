#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256

// Build Bad Character Table
void badCharHeuristic(char* pattern, int m, int badchar[]) {
    for (int i = 0; i < MAX; i++)
        badchar[i] = -1;

    for (int i = 0; i < m; i++)
        badchar[(unsigned char) pattern[i]] = i;
}

// Build Suffix Table for Good Suffix Heuristic
void buildSuffixes(char *pattern, int m, int *suffixes) {
    int f = 0, g = m - 1;
    suffixes[m - 1] = m;

    for (int i = m - 2; i >= 0; i--) {
        if (i > g && suffixes[i + m - 1 - f] < i - g) {
            suffixes[i] = suffixes[i + m - 1 - f];
        } else {
            if (i < g)
                g = i;
            f = i;

            while (g >= 0 && pattern[g] == pattern[g + m - 1 - f])
                g--;

            suffixes[i] = f - g;
        }
    }
}

// Build Good Suffix Table
void goodSuffixHeuristic(char *pattern, int m, int *shift) {
    int *suffixes = (int *) malloc(m * sizeof(int));
    buildSuffixes(pattern, m, suffixes);

    for (int i = 0; i < m; i++)
        shift[i] = m;

    int j = 0;
    for (int i = m - 1; i >= 0; i--) {
        if (suffixes[i] == i + 1) {
            for (; j < m - 1 - i; j++) {
                if (shift[j] == m)
                    shift[j] = m - 1 - i;
            }
        }
    }

    for (int i = 0; i <= m - 2; i++) {
        shift[m - 1 - suffixes[i]] = m - 1 - i;
    }

    free(suffixes);
}

// Boyer-Moore Search using Bad Character + Good Suffix
void BoyerMoore(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    int badchar[MAX], *goodsuffix = (int *) malloc(m * sizeof(int));

    badCharHeuristic(pattern, m, badchar);
    goodSuffixHeuristic(pattern, m, goodsuffix);

    int s = 0, comparisons = 0;
    while (s <= n - m) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
            comparisons++;
        }

        if (j < 0) {
            printf("Pattern occurs at index %d\n", s);
            s += goodsuffix[0];
        } else {
            comparisons++;
            int shift1 = j - badchar[(unsigned char)text[s + j]];
            int shift2 = goodsuffix[j];
            s += (shift1 > shift2) ? shift1 : shift2;
        }
    }

    printf("Total comparisons: %d\n", comparisons);
    free(goodsuffix);
}

int main() {
    char text[1000], pattern[1000];
    printf("Enter the text: ");
    scanf("%s", text);
    printf("Enter the pattern: ");
    scanf("%s", pattern);

    BoyerMoore(text, pattern);
    return 0;
}
