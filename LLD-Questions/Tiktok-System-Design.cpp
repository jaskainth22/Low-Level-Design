#include<iostream>

using namespace std;

// Video management system
class VideoSystem {
    public:
    void Upload_Video(int video_id, string video_url, int user_id) {

    }

    void Get_Video(int video_id) {

    }

    void Follow_User(int userId, int follow_id) {

    }

    void Get_Followers(int userId) {

    }

    void Add_Recommendation(int video_id, string topic) {

    }

    void Get_Recommendation(int topic) {

    }

    void Add_To_Feed(string video_id) {

    }

    void Get_Feed() {

    }

    void Add_To_Pre_Cache(string video_id) {

    }

    void Get_Pre_Cache() {

    }

    void Notify_Followers(int user_id, int video_id) {

    }
};

// Feed and Notification Service
class Video {
    int id;
    string title;
    string description;
    int createdAt;
    int engagement;
    public:
    Video(int id, string title, string desc, int createdAt, int engagement) : id(id), title(title), description(desc), createdAt(createdAt), engagement(engagement) {

    }
};

class User {
    int id;
    string name;
    vector<Video> listVideos;

    User(int id, int name) {
        this->id = id;
        this->name = name;
        listVideo.clear();
    }
};

class Feed_Service() {
    public:
    void GenerateFeed() {

    }
};

class NotificationService() {
    public:
    void Send_Notification(vector<int>followers, Video* video) {

    }
};

class VideoService() {
    public:
    void Upload_Video(Video* video, User* user) {

    }

    Video Get_Video(int video_id) {

    }
};

class FollowService() {
    public:
    void Follow_User(User* user, User* follower) {

    }

    void Get_Followers(User* User) {

    }
};

class RecommendationService() {
    public:
    void Add_Recommendation(Video* video, string topic) {

    }

    vector<Video> Get_Recommendation(string topic) {

    }
};

class Pre_cache_Service() {
    public:
    void Add_To_Pre_Cache(Video* video) {

    }

    vector<Video*> Get_Pre_Cache() {

    }
};

int main() {

}