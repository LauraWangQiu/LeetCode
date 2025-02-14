#include <iostream>
#include <string>
#include <numeric>
#include <vector>
using namespace std;

//#define _1768
//#define _1071
//#define _1431
//#define _605
//#define _345

#pragma region 1768. Merge Strings Alternately
/*
* 
* You are given two strings word1 and word2.
* Merge the strings by adding letters in alternating order,
* starting with word1.If a string is longer than the other,
* append the additional letters onto the end of the merged string.
*
* Return the merged string.
*
* Example 1:
*
*  Input: word1 = "abc", word2 = "pqr"
*  Output : "apbqcr"
*  Explanation : The merged string will be merged as so :
*  word1:  a   b   c
*  word2 : p   q   r
*  merged : a p b q c r
*
* Example 2 :
*
*  Input : word1 = "ab", word2 = "pqrs"
*  Output : "apbqrs"
*  Explanation : Notice that as word2 is longer, "rs" is appended to the end.
*  word1 : a   b
*  word2 : p   q   r   s
*  merged : a p b q   r   s
*
* Example 3 :
*
*  Input : word1 = "abcd", word2 = "pq"
*  Output : "apbqcd"
*  Explanation : Notice that as word1 is longer, "cd" is appended to the end.
*  word1 : a   b   c   d
*  word2 : p   q
*  merged : a p b q c   d
*
* Constraints:
*
* 1 <= word1.length, word2.length <= 100
* word1 and word2 consist of lowercase English letters.
*
*/

// Time complexity: O(max(word1.length(), word2.length()))
// Space complexity: O(word1.length() + word2.length())
string mergeAlternately(string word1, string word2) {
    string answer;
    // Reserve memory to avoid reallocations
    answer.reserve(word1.length() + word2.length());
    for (int i = 0; i < max(word1.length(), word2.length()); ++i) {
        if (i < word1.length()) answer += word1[i];
        if (i < word2.length()) answer += word2[i];
    }

    // The compiler optimizes the return of the string
    // without copying it if possible. Although it is not
    // mandatory to use std::move, knowing that the opti-
    // mization exists gives you more control if needed
    return answer;
}

#ifdef _1768
int main(int argc, char** argv) {
    while (true) {
        string word1, word2;
        cin >> word1 >> word2;
        cout << mergeAlternately(word1, word2);
    }
    return 0;
}
#endif
#pragma endregion

#pragma region 1071. Greatest Common Divisor of Strings
/*
* For two strings s and t, we say "t divides s" if and only if s = t + t + t + ... + t + t (i.e., t is concatenated with itself one or more times).
*
* Given two strings str1 and str2, return the largest string x such that x divides both str1 and str2.
*
* Example 1:
*
*  Input: str1 = "ABCABC", str2 = "ABC"
*  Output: "ABC"
*
* Example 2:
*
*  Input: str1 = "ABABAB", str2 = "ABAB"
*  Output: "AB"
*
* Example 3:
*
*  Input: str1 = "LEET", str2 = "CODE"
*  Output: ""
*
* Constraints:
*
*  1 <= str1.length, str2.length <= 1000
*  str1 and str2 consist of English uppercase letters.
*/

// ABABABAB - ABAB => ABAB
// ABCDEF - ABC => ""

// Time complexity: O(word1.length() + word2.length()) because of the concatenation
// Space complexity: O(gcdLength) because of the substr cpy
string gcdOfStrings(string str1, string str2) {
    // Check the fundamental condition of divisibility
    // There is no common divisor if the concatenations are not equal
    if (str1 + str2 != str2 + str1)
        return "";

    // Find the GCD of the lengths
    size_t gcdLength = gcd(str1.length(), str2.length());

    return str1.substr(0, gcdLength);
}

#ifdef _1071
int main(int argc, char** argv) {
    while (true) {
        string str1, str2;
        cin >> str1 >> str2;
        cout << gcdOfStrings(str1, str2);
    }
    return 0;
}
#endif
#pragma endregion

#pragma region 1431. Kids With the Greatest Number of Candies
/*
* There are n kids with candies. You are given an integer array candies, where each candies[i] represents the number of candies the ith kid has, and an integer extraCandies, denoting the number of extra candies that you have.
*
* Return a boolean array result of length n, where result[i] is true if, after giving the ith kid all the extraCandies, they will have the greatest number of candies among all the kids, or false otherwise.
*
* Note that multiple kids can have the greatest number of candies.
*
* Example 1:
*
* Input: candies = [2,3,5,1,3], extraCandies = 3
* Output: [true,true,true,false,true]
* Explanation: If you give all extraCandies to:
* - Kid 1, they will have 2 + 3 = 5 candies, which is the greatest among the kids.
* - Kid 2, they will have 3 + 3 = 6 candies, which is the greatest among the kids.
* - Kid 3, they will have 5 + 3 = 8 candies, which is the greatest among the kids.
* - Kid 4, they will have 1 + 3 = 4 candies, which is not the greatest among the kids.
* - Kid 5, they will have 3 + 3 = 6 candies, which is the greatest among the kids.
* 
* Example 2:
* 
* Input: candies = [4,2,1,1,2], extraCandies = 1
* Output: [true,false,false,false,false] 
* Explanation: There is only 1 extra candy.
* Kid 1 will always have the greatest number of candies, even if a different kid is given the extra candy.
* 
* Example 3:
* 
* Input: candies = [12,1,12], extraCandies = 10
* Output: [true,false,true]
* 
* Constraints:
* 
*     n == candies.length
*     2 <= n <= 100
*     1 <= candies[i] <= 100
*     1 <= extraCandies <= 50
* 
*/

#define BOOL_STR(x) (x ? "true" : "false")

// Time complexity: O(n), n = number of candies
// Space complexity: O(n), n = number of candies
vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
    vector<bool> result(candies.size(), false);
    int mostCandies = 0;
    for (int i = 0; i < candies.size(); ++i)
        mostCandies = max(mostCandies, candies[i]);
    //int mostCandies = *max_element(candies.begin(), candies.end());
    for (int i = 0; i < candies.size(); ++i)
        if (candies[i] + extraCandies >= mostCandies)
            result[i] = true;
    return result;
}

#ifdef _1431
int main(int argc, char** argv) {
    while (true) {
        int n; cin >> n;
        vector<int> candies(n);
        for (int& c : candies) cin >> c;
        int extraCandies; cin >> extraCandies;
        vector<bool> result = kidsWithCandies(candies, extraCandies);
        cout << "[ " << BOOL_STR(result[0]);
        for (int i = 1; i < result.size(); ++i)
            cout << ", " << BOOL_STR(result[i]);
        cout << " ]\n";
    }
    return 0;
}
#endif
#pragma endregion

#pragma region 605. Can Place Flowers
/*
* You have a long flowerbed in which some of the plots are planted, and some are not. However, flowers cannot be planted in adjacent plots.
* 
* Given an integer array flowerbed containing 0's and 1's, where 0 means empty and 1 means not empty, and an integer n, return true if n new flowers can be planted in the flowerbed without violating the no-adjacent-flowers rule and false otherwise.
* 
* Example 1:
* 
* Input: flowerbed = [1,0,0,0,1], n = 1
* Output: true
* 
* Example 2:
* 
* Input: flowerbed = [1,0,0,0,1], n = 2
* Output: false
* 
* Constraints:
* 
*     1 <= flowerbed.length <= 2 * 104
*     flowerbed[i] is 0 or 1.
*     There are no two adjacent flowers in flowerbed.
*     0 <= n <= flowerbed.length
* 
* https://leetcode.com/problems/can-place-flowers/solutions/6416870/easy-solution-advance-index-position-for-more-efficient-calculation
*/

// Time complexity: O(n), n = size of flowerbed
// Space complexity: O(1)
bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    for (int i = 0; i < flowerbed.size();) {
        if (!flowerbed[i]) {
            if (i + 1 < flowerbed.size() && flowerbed[i + 1]) i += 3;
            else if (i - 1 >= 0 && flowerbed[i - 1]) i++;
            else if (--n <= 0) return true;
            else i += 2;
        } else i += 2;
    }
    return n <= 0;
}

#ifdef _605
int main(int argc, char** argv) {
    while (true) {
        int f; cin >> f;
        vector<int> flowerbed(f);
        for (int& e : flowerbed) cin >> e;
        int n; cin >> n;
        cout << ((canPlaceFlowers(flowerbed, n)) ? "true" : "false") << '\n';
    }
    return 0;
}
#endif
#pragma endregion

#pragma region 345. Reverse vowels of a string
/*
* Given a string s, reverse only all the vowels in the string and return it.
* 
* The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases, more than once.
* 
* Example 1:
* 
* Input: s = "IceCreAm"
* 
* Output: "AceCreIm"
* 
* Explanation:
* 
* The vowels in s are ['I', 'e', 'e', 'A']. On reversing the vowels, s becomes "AceCreIm".
* 
* Example 2:
* 
* Input: s = "leetcode"
* 
* Output: "leotcede"
* 
* Constraints:
* 
*     1 <= s.length <= 3 * 105
*     s consist of printable ASCII characters.
*/

bool isVowel(char ch) {
    ch = tolower(ch);
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

// Time complexity: O(n), n = length of the string
// Space complexity: O(1)
string reverseVowels(string s) {
    int i = 0, j = s.size() - 1;
    while (i < j) {
        if (isVowel(s[i]) && isVowel(s[j])) {
            swap(s[i], s[j]);
            ++i; --j;
        }
        else if (!isVowel(s[i])) ++i;
        else --j;
    }
    return s;
}

#ifdef _345
int main(int argc, char** argv) {
    while (true) {
        string input; cin >> input;
        cout << reverseVowels(input) << '\n';
    }
    return 0;
}
#endif
#pragma endregion