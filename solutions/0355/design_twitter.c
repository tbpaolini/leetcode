// Problem 355 - Design Twitter
// https://leetcode.com/problems/design-twitter/description/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MIN_USER (1)
#define MAX_USER (501)  // User IDs are guaranteed to be from 1 to 500 (inclusive)

typedef struct TweetList
{
    int tweet_id;
    size_t timestamp;
    struct TweetList* next;
} TweetList;

typedef struct User
{
    TweetList* tweets;          // Linked list of this user's tweet IDs
    TweetList* first_tweet;     // Head of the list
    TweetList* last_tweet;      // Tail of the list
    size_t tweet_counter;       // This user's tweet counter
    bool followed[MAX_USER];    // Who this user follows
} User;

typedef struct {
    size_t tweet_count;     // All users' tweet counter
    User users[MAX_USER];   // Table of users
} Twitter;


// Return a negative value if the first tweet is newer than the second,
// or a positive value if it is older, or zero if the timestamp is the same.
// (Function meant to be passed to `qsort()`)
static int compare_tweet(const TweetList** tweet_1, const TweetList** tweet_2)
{
    return (**tweet_2).timestamp - (**tweet_1).timestamp;
}

Twitter* twitterCreate() {
    Twitter* obj = calloc(1, sizeof(Twitter));
    for (size_t i = MIN_USER; i < MAX_USER; i++)
    {
        // User is considered to follow themself so the news feed also returns the tweets from own user
        obj->users[i].followed[i] = true;
    }
    return obj;
}

void twitterPostTweet(Twitter* obj, int userId, int tweetId) {
    
    User* user = &obj->users[userId];
    TweetList* new_tweet = malloc(sizeof(TweetList));
    
    // Create the tweet
    *new_tweet = (TweetList){
        .tweet_id = tweetId,
        .timestamp = obj->tweet_count++,
        .next = NULL,
    };
    
    // Add the new tweet to the linked list
    if (user->last_tweet)
    {
        user->last_tweet->next = new_tweet;
    }
    else
    {
        user->first_tweet = new_tweet;
    }

    user->last_tweet = new_tweet;
    user->tweet_counter++;
}

int* twitterGetNewsFeed(Twitter* obj, int userId, int* retSize) {
    
    User* user = &obj->users[userId];
    
    // Counter of tweets from the followed users and from the user themself
    size_t count = 0;

    for (size_t i = MIN_USER; i < MAX_USER; i++)
    {
        if (user->followed[i])
        {
            // Add the tweet count for each followed user
            count += obj->users[i].tweet_counter;
        }
    }

    if (count == 0) return NULL;

    TweetList* tweets[count];   // Array for all the followed tweets
    size_t pos = 0;             // Current index on the `tweets[]` array

    for (size_t i = MIN_USER; i < MAX_USER; i++)
    {
        if (user->followed[i])
        {
            TweetList* tweet = obj->users[i].first_tweet;
            while (tweet)
            {
                tweets[pos++] = tweet;
                tweet = tweet->next;
            }
        }
    }
    
    // Sort the array in ascending order by the timestamp
    qsort(tweets, count, sizeof(TweetList*), &compare_tweet);
    
    // Create the array for the news feed
    *retSize = (count >= 10) ? 10 : count;
    int* feed = malloc((*retSize) * sizeof(int));
    
    // Populate the news feed
    for (size_t i = 0; i < *retSize; i++)
    {
        feed[i] = tweets[i]->tweet_id;
    }

    // Return the news feed
    return feed;
}

void twitterFollow(Twitter* obj, int followerId, int followeeId) {
    obj->users[followerId].followed[followeeId] = true;
}

void twitterUnfollow(Twitter* obj, int followerId, int followeeId) {
    if (followerId != followeeId)
    {
        obj->users[followerId].followed[followeeId] = false;
    }
}

void twitterFree(Twitter* obj) {
    
    // Free each user's list of tweets
    for (size_t i = MIN_USER; i < MAX_USER; i++)
    {
        TweetList* tweet = obj->users[i].first_tweet;
        while (tweet != NULL)
        {
            TweetList* next_tweet = tweet->next;
            free(tweet);
            tweet = next_tweet;
        }
    }
    
    // Free the container itself
    free(obj);
}

/**
 * Your Twitter struct will be instantiated and called as such:
 * Twitter* obj = twitterCreate();
 * twitterPostTweet(obj, userId, tweetId);
 
 * int* param_2 = twitterGetNewsFeed(obj, userId, retSize);
 
 * twitterFollow(obj, followerId, followeeId);
 
 * twitterUnfollow(obj, followerId, followeeId);
 
 * twitterFree(obj);
*/