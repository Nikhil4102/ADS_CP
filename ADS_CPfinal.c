#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE (26)

#define CHAR_TO_INDEX(b) ((int)b- (int)'a')

// Trie node
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];

  
    bool isWordEnd;
};

// Returns a new trie node (initialized to NULLs)
struct TrieNode* getNode(void) {
    struct TrieNode* pNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    pNode->isWordEnd = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie. If the
// key is a prefix of a trie node, just marks the leaf node
void insert(struct TrieNode* root, const char* key) {
    struct TrieNode* pCrawl = root;

    for (int level = 0; level < strlen(key); level++) {
        int index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // Mark the last node as a leaf
    pCrawl->isWordEnd = true;
}

// Returns 0 if the current node has a child
// If all children are NULL, return 1.
bool isLastNode(struct TrieNode* root) {
    
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}

// Recursive function 

void suggestionsRec(struct TrieNode* root, char* currPrefix) {
   
    if (root->isWordEnd)
        printf("%s\n", currPrefix);

    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i]) {

            // Child node character value
            char child = 'a' + i;
            char newPrefix[strlen(currPrefix) + 2];
            strcpy(newPrefix, currPrefix);
            newPrefix[strlen(currPrefix)] = child;
            newPrefix[strlen(currPrefix) + 1] = '\0';
            suggestionsRec(root->children[i], newPrefix);
        }
}

// Print suggestions for the given  prefix.
int printAutoSuggestions(struct TrieNode* root, const char* query) {

    struct TrieNode* pCrawl = root;
    for (int i = 0; i < strlen(query); i++) {
        int ind = CHAR_TO_INDEX(query[i]);

        
        if (!pCrawl->children[ind])
            return 0;

        pCrawl = pCrawl->children[ind];
    }
    

    if (isLastNode(pCrawl)) {
        printf("%s\n", query);
        return -1;
    }

    suggestionsRec(pCrawl, (char*)query);
    return 1;
}
 
// Driver Code
int main() {

    struct TrieNode* root = getNode();
    
    // Specify the number of words and the words directly in string form
    char* words[] = {"account", "act", "addition", "adjustment", "advertisement", 
    "agreement", "air", "amount", "amusement", "animal", "answer", "apparatus", "approval", 
    "argument", "art", "attack", "attempt", "attention", "attraction", "authority", "back", 
    "balance", "base", "behaviour", "belief", "birth", "bit", "bite", "blood", "blow", "body",
     "brass", "bread", "breath", "brother", "building", "burn", "burst", "business", "butter", "canvas",
      "care", "cause", "chalk", "chance", "change", "cloth", "coal", "colour", "comfort",
       "committee", "company", "comparison", "competition", "condition", "connection", "control",
       "cook", "copper", "copy", "cork", "cotton", "cough", "country", "cover", "crack", "credit", "crime",
        "crush", "cry", "current", "curve", "damage", "danger", "daughter", "day", "death", "debt", "decision",
        "degree", "design", "desire", "destruction," "detail", "development", "digestion", 
        "direction", "discovery", "discussion", "disease", "disgust", "distance", "distribution", 
        "division", "doubt", "drink", "driving", "dust", "earth", "edge", "education", "effect",
         "end", "error", "event", "example", "exchange", "existence", "expansion", "experience",
          "expert", "fact", "fall", "family", "father", "fear", "feeling", "fiction", "field", "fight",
           "fire", "flame", "flight", "flower", "fold", "food", "force", "form", "friend", "front", 
           "fruit", "glass", "gold", "government", "grain", "grass", "grip", "group", "growth", "guide",
            "harbour", "harmony", "hate", "hearing", "heat", "help", "history", "hole", "hope", "hour",
             "humour", "ice", "idea", "impulse", "increase", "industry", "ink", "insect", "instrument", 
             "insurance", "interest", "invention", "iron", "jelly", "join", "journey", "judge", "jump", 
             "kick", "kiss", "knowledge", "land", "language", "laugh", "law", "lead", "learning", "leather", 
             "letter", "level", "lift", "light", "limit", "linen", "liquid", "list", "look", "loss", "love",
             "machine", "man", "manager", "mark", "market", "mass", "meal", "measure", "meat", "meeting", "memory", 
             "metal", "middle", "milk", "mind", "mine", "minute", "mist", "money", "month", "morning", "mother", "motion",
              "mountain", "move", "music", "name", "nation", "need", "news", "night", "noise", "note", "number", "observation",
               "offer", "oil", "operation", "opinion", "order", "organization", "ornament", "owner", "page", "pain", "paint", 
               "paper", "part", "paste", "payment", "peace", "person", "place", "plant", "play", "pleasure", "point", "poison",
                "polish", "porter", "position", "powder", "power", "price", "print", "process", "produce", "profit", "property",
                 "prose", "protest", "pull", "punishment", "purpose", "push", "quality", "question", "rain", "range", "rate",
                  "ray", "reaction", "reading", "reason", "record", "regret", "relation", "religion", "representative", "request", 
                  "respect", "rest", "reward", "rhythm", "rice", "river", "road", "roll", "room", "rub", "rule", "run", "salt", 
                  "sand", "scale", "science", "sea", "seat", "secretary", "selection", "self", "sense", "servant", "sex", "shade", 
                  "shake", "shame", "shock", "side", "sign", "silk", "silver", "sister", "size", "sky", "sleep", "slip", "slope", 
                  "smash", "smell", "smile", "smoke", "sneeze", "snow", "soap", "society", "son", "song", "sort", "sound", "soup", 
                  "space", "stage", "start", "statement", "steam", "steel", "step", "stitch", "stone", "stop", "story", "stretch",
                   "structure", "substance", "sugar", "suggestion", "summer", "support", "surprise", "swim", "system", "talk", "taste",
                    "tax", "teaching", "tendency", "test", "theory", "thing", "thought", "thunder", "time", "tin", "top", "touch", "trade", 
                    "transport", "trick", "trouble", "turn", "twist", "unit", "use", "value", "verse", "vessel", "view", "voice", "walk", "war",
                     "wash", "waste", "water", "wave", "wax", "way", "weather", "week", "weight", "wind", "wine", "winter", 
                     "woman", "wood", "wool", "word", "work", "wound", "writing", "year"

};
    int numWords = sizeof(words) / sizeof(words[0]);

    
    // Insert the words into the trie
    for (int i = 0; i < numWords; i++) {
        insert(root, words[i]);
    }
    
    
    char inputString[100];
    printf("Enter the initial letters of the given string: ");
    scanf("%s", inputString);

   
    int len = strlen(inputString);
    char query[len + 1];
    strcpy(query, inputString);
    query[len] = '\0';

    int comp = printAutoSuggestions(root, query);

    if (comp == -1)
        printf("No other strings found with this prefix\n");
    else if (comp == 0)
        printf("No string found with this prefix\n");

return 0;
}
