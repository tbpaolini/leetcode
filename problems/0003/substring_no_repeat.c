int lengthOfLongestSubstring(char * s){
    
    int seen[128] = {0};
    char *first = s;
    char *curr = s;
    
    while (*curr){
        char my_char = *curr++;
        seen[my_char]++;
        bool unique = true;
        
        for (char *c = first; c <= curr; c++){
            if (seen[*c] > 1){
                unique = false;
                break;
            }
        }
        
        if (!unique){
            seen[*first++]--;
        }
    }
    
    return curr - first;
}