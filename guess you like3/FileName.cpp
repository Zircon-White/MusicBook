#include <iostream>  
#include <vector>  
#include <string>  
#include <algorithm> 
#include <ctime>   
#include <sstream>
#include <unordered_set> 

class SongInfo {
public:
    std::string name;
    std::string tags;

    SongInfo(std::string name, std::string tags) : name(name), tags(tags) {}

    bool hasTag(const std::string& wantedTag) const {//检查当前歌曲是否拥有给出的标签
        std::istringstream iss(tags);
        std::string token;
        while (std::getline(iss, token, ',')) {
            if (token == wantedTag) return true;
        }
        return false;
    }

    void print() const { // 打印歌曲信息  
        std::cout << "名字: " << name << ", 标签: " << tags << std::endl;
    }
};

class SongPlaylist {
public:
    std::vector<SongInfo> songs;

    void addSong(const SongInfo& song) { // 添加歌曲  
        songs.push_back(song);
    }

    // 获取与给定歌曲具有相同标签的所有歌曲的随机排列  
    std::vector<SongInfo> getSongsWithSameTagsRandomly(const SongInfo& referenceSong) const {

        std::vector<SongInfo> filteredSongs;//筛选后的歌曲

        std::istringstream iss(referenceSong.tags);//提取想要的歌曲的标签
        std::vector<std::string> tags;
        std::string token;
        while (std::getline(iss, token, ',')) {
            tags.push_back(token);
        }
         for (const auto& song : songs){//遍历所有歌曲
            for(const auto & wantedTag : tags){//遍历想要的歌曲的所有标签
                if (song.hasTag(wantedTag)) {
                    filteredSongs.push_back(song);
                    break;
                }
            }
        }


        if (!filteredSongs.empty()) {// 如果filteredSongs不为空，则随机排列  
            std::random_shuffle(filteredSongs.begin(), filteredSongs.end());
        }

        return filteredSongs;
    }

    void printAllSongs() const { //打印所有歌曲 
        for (const auto& song : songs) {
            song.print();
        }
    }
};

int main() {
    SongPlaylist playlist;

    // 添加歌曲  
    playlist.addSong(SongInfo("Song1", "Rock,Blues"));
    playlist.addSong(SongInfo("Song2", "Pop,Jazz,Latin"));
    playlist.addSong(SongInfo("Song3", "Classic"));
    playlist.addSong(SongInfo("Song4", "Pop,Rock,Classic"));
    playlist.addSong(SongInfo("Song5", "Blues"));
    playlist.addSong(SongInfo("Song6", "Classic,Pop"));
    playlist.addSong(SongInfo("Song7", "Jazz,Latin"));
    playlist.addSong(SongInfo("Song8", "Jazz,Blues,Rock"));
    playlist.addSong(SongInfo("Song9", "Latin"));

    std::cout << "歌单里一共有:" << std::endl;// 打印所有歌曲（原始顺序） 
    playlist.printAllSongs();

    // 获取并打印与选择的歌曲拥有相同标签的歌曲的随机排列  
    std::cout << "\n今天想听第几首歌？" << std::endl;
    int n;
    std::cin >> n;
    auto referenceSong = playlist.songs[n-1];
    std::cout << "\n由第"<<n<<"首歌，猜你喜欢:" << std::endl;
    auto sameTagSongs = playlist.getSongsWithSameTagsRandomly(referenceSong);
    for (const auto& song : sameTagSongs) {
        song.print();
    }

    return 0;
}