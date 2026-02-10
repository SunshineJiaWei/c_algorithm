/*
242. 有效的字母异位词
给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的 字母异位词。

示例 1:
输入: s = "anagram", t = "nagaram"
输出: true
示例 2:

输入: s = "rat", t = "car"
输出: false
 
提示:
1 <= s.length, t.length <= 5 * 104
s 和 t 仅包含小写字母
 
进阶: 如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？
*/


#include <stdio.h>
#include <stdbool.h>
#include <string.h>


bool isAnagram(char* s, char* t) 
{
    // 这里设计的比较巧妙，仅仅是小写字母，所以是a-z，并且不需要关注ascii值，只需要根据a算出相对位置即索引
    int hash_letter[26] = {0};
    int s_len = strlen(s);
    int t_len = strlen(t);
    // int sum = 0; // 这里不能使用累计值来判断，因为可能会出现互相-1+1互相抵消的情况，误判为字母异构词
    int arr_size = sizeof(hash_letter) / sizeof(hash_letter[0]);

    if (s_len != t_len)
    {
        return false;
    }

    for (int i = 0; i < s_len; i ++)
    {
        hash_letter[s[i] - 'a'] ++;
    }

    for (int j = 0; j < t_len; j ++)
    {
        hash_letter[t[j] - 'a'] --;
    }

    for (int z = 0; z < arr_size; z ++)
    {
        if (hash_letter[z] != 0)
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char *s = "hello";
    char *t = "helol";

    bool res = isAnagram(s, t);
    if (res)
    {
        printf("isAnagram\n");
    }
    else
    {
        printf("isn't Anagram\n");
    }

}