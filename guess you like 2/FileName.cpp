#include <iostream>  
#include <vector>  
#include <string>  
#include <algorithm> 
#include <ctime>     
#include <sstream>

class SongInfo {//创建SongInfo类用于存储歌曲信息
public:
    std::string name;//名字
    std::string tags;//标签

    SongInfo(std::string name, std::string tags) : name(name), tags(tags) {}//初始化

    bool hasTag(const std::string& wantedTag) const {  // 检查歌曲是否包含特定标签  
        //使用istringstream
        std::istringstream iss(tags);//使用istringstream函数将字符串tags读取为iss
        std::string token;//创建token存储分割出的单词
        //此处必须保证tags前后没有空格，否则需要消去
        while (std::getline(iss, token, ',')) { // 使用getline遍历所有分割出的单词，过程中getline从iss中获取每一个单词并赋值到token上，以逗号为分割 
            if (token == wantedTag) { // 比较单词是否为需要的标签
                return true; 
            }
        }
        return false;

    /* size_t pos = 0; // 初始位置  
        size_t foundPos;
        // 循环直到找不到逗号  
        while ((foundPos = tags.find(',', pos)) != std::string::npos) { // 提取逗号之前的子字符串（即一个单词） 
            std::string token = tags.substr(pos, foundPos - pos);
            if (token == wantedTag) {
                return true;
            }
            pos = foundPos + 1;// 若不是，更新位置以查找下一个单词  
        }
        std::string token = tags.substr(pos); // 检查最后一个单词（后面没有逗号）  
        if (token == wantedTag) {
            return true;
        }
        return false;*/
    }

    void print() const { // 打印歌曲信息  
        std::cout <<"名字: " << name << ", 标签: " << tags << std::endl;
    }
};

class SongPlaylist { //创建SongPlaylist类管理歌曲顺序
private:
    std::vector<SongInfo> songs;
public:
    void addSong(const SongInfo& song) { //添加歌曲信息 
        songs.push_back(song);
    }
    // 获取包含特定标签的所有歌曲的随机排列  
    std::vector<SongInfo> getSongsByTagRandomly(const std::string& wantedTag) const {
        std::vector<SongInfo> filteredSongs;//创建数组储存筛选（未排序）后的歌曲
        for (const auto& song : songs) {//使用songInfo中创建的hasTag函数筛选出拥有特定标签的歌曲并添加到filteredSongs后
            if (song.hasTag(wantedTag)) {
                filteredSongs.push_back(song);
            }
        }

        std::vector<SongInfo> shuffledSongs(filteredSongs);  // 随机排列筛选后的歌曲  
        std::random_shuffle(shuffledSongs.begin(), shuffledSongs.end()); 

        return shuffledSongs;
    }

    void printAllSongs() const { // 打印原始顺序
        for (const auto& song : songs) {
            song.print();
        }
    }
};

int main() {
    SongPlaylist playlist;//定义SongPlaylist类变量playlist

    // 添加歌曲  
    playlist.addSong(SongInfo("Song1", "Classical, Acoustic"));
    playlist.addSong(SongInfo("Song2", "Pop,Live,Experimental"));
    playlist.addSong(SongInfo("Song3", "Rock,Studio"));
    playlist.addSong(SongInfo("Song4", "Acoustic,Pop,Indie"));
    playlist.addSong(SongInfo("Song5", "Pop,Alternative"));
    playlist.addSong(SongInfo("Song6", "Pop"));
  
    std::cout << "原始顺序:" << std::endl;// 打印所有歌曲（原始顺序） 
    playlist.printAllSongs();

   
    std::cout << "\n包含“Pop”标签的歌曲(随机排列后):" << std::endl; //获取并打印包含"Pop"标签的歌曲的随机排列 
    auto popSongs = playlist.getSongsByTagRandomly("Pop");
    for (const auto& song : popSongs) {
        song.print();
    }
    return 0;
}