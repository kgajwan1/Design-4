// I hate the platform, it gets on my head, no wonder I have to design it
class Twitter {
private:    
   unordered_map<int, set<int>> fo;
   unordered_map<int, vector<pair<int, int>>> t;
   long long time; 
//max heap and hashmap solution
//did this in 2019    
public:
/** Initialize your data structure here. */

    Twitter() {
    time = 0;
}

/** Compose a new tweet. */
void postTweet(int userId, int tweetId) {
    t[userId].push_back({time++, tweetId});
}

/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
vector<int> getNewsFeed(int userId) {
    //we sort by time and pop out 10 most recent tweets, O(1) (10logn to  be fair, but 10 has no value, sooo)
    priority_queue<pair<int, int>> maxHeap; 
    for (auto it=t[userId].begin();it!=t[userId].end();++it)
        maxHeap.push(*it);
    for (auto it1=fo[userId].begin();it1!=fo[userId].end();++it1){
        int usr = *it1; // get target user
        for (auto it2=t[usr].begin();it2!=t[usr].end();++it2)
            maxHeap.push(*it2);
    }   
    vector<int> res;
    while(maxHeap.size()>0) {
        res.push_back(maxHeap.top().second);
        if (res.size()==10) break;
        maxHeap.pop();
    }
    return res;
}

/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
void follow(int followerId, int followeeId) {
    //same O(1) insertion in hashmap, I'd likely explain compliacted stufff regarding hmap insertion and how theyy are not O(1) to interviewrer
    if (followerId != followeeId)
        fo[followerId].insert(followeeId);
}

/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
void unfollow(int followerId, int followeeId) {
    //O(1) erase from hmap
    fo[followerId].erase(followeeId);
}
};
/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
