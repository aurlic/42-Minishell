int ft_strictcmp(const char *s1, const char *s2);

int main() {
    // Test case 1: s1 and s2 are equal
    const char *s1 = "Hello";
    const char *s2 = "Hello";
    int result = ft_strictcmp(s1, s2);
    printf("Test case 1: %d\n", result); // Expected output: 0

    // Test case 2: s1 is lexicographically smaller than s2
    s1 = "Apple";
    s2 = "Banana";
    result = ft_strictcmp(s1, s2);
    printf("Test case 2: %d\n", result); // Expected output: -1

    // Test case 3: s1 is lexicographically greater than s2
    s1 = "Banana";
    s2 = "Apple";
    result = ft_strictcmp(s1, s2);
    printf("Test case 3: %d\n", result); // Expected output: 1

    // Test case 4: s1 is a substring of s2
    s1 = "Hello";
    s2 = "Hello World";
    result = ft_strictcmp(s1, s2);
    printf("Test case 4: %d\n", result); // Expected output: -1

    // Test case 5: s2 is a substring of s1
    s1 = "Hello World";
    s2 = "Hello";
    result = ft_strictcmp(s1, s2);
    printf("Test case 5: %d\n", result); // Expected output: 1

    return 0;
}