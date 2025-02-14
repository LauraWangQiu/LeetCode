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
//#define _151
//#define _238
//#define _334

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

#pragma region 151. Reverse Words in a String
/**
* Given an input string s, reverse the order of the words.
* 
* A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.
* 
* Return a string of the words in reverse order concatenated by a single space.
* 
* Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.
* 
* Example 1:
* 
* Input: s = "the sky is blue"
* Output: "blue is sky the"
* 
* Example 2:
* 
* Input: s = "  hello world  "
* Output: "world hello"
* Explanation: Your reversed string should not contain leading or trailing spaces.
* 
* Example 3:
* 
* Input: s = "a good   example"
* Output: "example good a"
* Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.
* 
* Constraints:
* 
*     1 <= s.length <= 104
*     s contains English letters (upper-case and lower-case), digits, and spaces ' '.
*     There is at least one word in s.
*/

// Time complexity: O(n), n = length of string
// Space complexity: O(n), n = length of string
string reverseWords(string s) {
    /*if (s.size() == 1) return s;

    int i = 0, j = s.size() - 1, answerIdx = 0;
    string answer = "", left = "", right = "";
    while (i < j) {
        while (i < s.size() - 1 && s[i] == ' ') i++;
        while (j >= 1 && s[j] == ' ') j--;
        if (i > j) return answer;
        while (i < s.size() && s[i] != ' ') {
            left += s[i]; i++;
        }
        while (i < j && s[j] != ' ') {
            right.insert(0, string(1, s[j])); j--;
        }
        if (!right.empty()) {
            answer.insert(answerIdx, right + " ");
            answerIdx += right.size() + 1;
        }
        if (!left.empty())
            answer.insert(answerIdx, (((answerIdx - (int(right.size()) + 1)) <= 0) ? left : left + " "));
        left.clear(); right.clear();
    }
    return answer;*/

    reverse(s.begin(), s.end());
    string ans = "";

    for (int i = 0; i < s.length(); ++i) {
        string word = "";
        while (i < s.length() && s[i] != ' ')
            word += s[i++];
        reverse(word.begin(), word.end());
        if (word.length() > 0)
            ans += " " + word;
    }

    return ans.substr(1); // eliminate the first space
}

#ifdef _151
int main(int argc, char** argv) {
    while (true) {
        string input; getline(cin, input);
        cout << reverseWords(input) << '\n';
    }
    return 0;
}
#endif
#pragma endregion

#pragma region 238. Product of Array Except Self
/*
* Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].
* 
* The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
* 
* You must write an algorithm that runs in O(n) time and without using the division operation.
* 
* Example 1:
* 
* Input: nums = [1,2,3,4]
* Output: [24,12,8,6]
* 
* Example 2:
* 
* Input: nums = [-1,1,0,-3,3]
* Output: [0,0,9,0,0]
* 
* Constraints:
* 
*     2 <= nums.length <= 105
*     -30 <= nums[i] <= 30
*     The input is generated such that answer[i] is guaranteed to fit in a 32-bit integer.
* 
* Follow up: Can you solve the problem in O(1) extra space complexity? (The output array does not count as extra space for space complexity analysis.)
*/

// Time complexity: O(n), n = length of nums
// Space complexity: O(n), n = length of nums
vector<int> productExceptSelf(vector<int>& nums) {
    vector<int> output(nums.size(), 1);

    int left = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        output[i] *= left;
        left *= nums[i];
    }

    int right = nums[nums.size() - 1];
    for (int i = nums.size() - 2; i >= 0; i--) {
        output[i] *= right;
        right *= nums[i];
    }

    return output;
}

#ifdef _238
int main(int argc, char** argv) {
    while (true) {
        int n; cin >> n;
        vector<int> nums(n);
        for (int& e : nums) cin >> e;
        vector<int> answer = productExceptSelf(nums);
        cout << "[ " << answer[0];
        for (int i = 1; i < answer.size(); ++i)
            cout << ", " << answer[i];
        cout << " ]\n";
    }

    return 0;
}
#endif
#pragma endregion

#pragma region 334. Increasing Triplet Subsequence
/*
* Given an integer array nums, return true if there exists a triple of indices (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k]. If no such indices exists, return false.
* 
* Example 1:
* 
* Input: nums = [1,2,3,4,5]
* Output: true
* Explanation: Any triplet where i < j < k is valid.
* 
* Example 2:
* 
* Input: nums = [5,4,3,2,1]
* Output: false
* Explanation: No triplet exists.
* 
* Example 3:
* 
* Input: nums = [2,1,5,0,4,6]
* Output: true
* Explanation: The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 < nums[5] == 6.
* 
* Constraints:
* 
*     1 <= nums.length <= 5 * 105
*     -231 <= nums[i] <= 231 - 1
* 
* Follow up: Could you implement a solution that runs in O(n) time complexity and O(1) space complexity?
*/

// Time complexity: O(n), n = length of nums
// Space complexity: O(n), n = length of nums
bool increasingTriplet(vector<int>& nums) {
    int first = INT_MAX, second = INT_MAX;
    for (int n : nums) {
        if (n <= first) first = n;
        else if (n <= second) second = n;
        else return true;
    } return false;
}

#ifdef _334
int main(int argc, char** argv) {
    while (true) {
        int n; cin >> n;
        vector<int> input(n);
        for (int& e : input) cin >> e;
        cout << ((increasingTriplet(input)) ? "true" : "false") << '\n';
    }
    return 0;
}
#endif
#pragma endregion