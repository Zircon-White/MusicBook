#include <iostream>  
#include <vector>  
#include <string>  
#include <algorithm> 
#include <ctime>     

class SongInfo {//创建SongInfo类用于存储和打印歌曲的信息
public:
    std::string name;//名字
    std::string tags;//标签
    std::string singer;//歌手

    SongInfo(std::string name, std::string tags,std::string singer) : name(name), tags(tags),singer(singer) {}//初始化列表

    void print()const{  // 打印歌曲信息
        std::cout << "歌曲名称: " << name << ", 标签: " << tags <<"，歌手："<<singer <<std::endl;
    }
};

class SongPlaylist {// 创建SongPlaylist类用于对歌曲进行管理
private:
    std::vector<SongInfo> songsOrder;//创建数组管理歌曲顺序
    std::vector<SongInfo> originalOrder; // 创建数组记录原始顺序  

  
public:
    void addSong(const SongInfo& song) { // 添加歌曲信息  
        songsOrder.push_back(song);//在SongPlaylist中记录顺序
        originalOrder.push_back(song); // 在SongPlaylist中记录原始顺序 
    }
    void shuffleSongs() {    // 随机排列歌曲顺序
        std::random_shuffle(songsOrder.begin(), songsOrder.end()); 
    }

    void printOriginalOrder() const { // 打印原始顺序的歌曲  
        std::cout << "原始顺序为:" << std::endl;
        for (const auto& song : originalOrder) {
            song.print();
        }
    }

    void printSongs() const { // 打印随机排列后歌曲顺序  
        std::cout << "随机排列后:" << std::endl;
        for (const auto& song : songsOrder) {
            song.print();
        }
    }
};

int main() {
    SongPlaylist playlist;

    // 添加歌曲  
    playlist.addSong(SongInfo("Song 1", "Classical","singer1"));
    playlist.addSong(SongInfo("Song 2", "Pop","singer2"));
    playlist.addSong(SongInfo("Song 3", "Rock","singer3"));
    playlist.addSong(SongInfo("Song 4", "Jazz","singer4"));
    playlist.addSong(SongInfo("Song 5", "Classical","singer5"));

    playlist.printOriginalOrder();    // 打印原始顺序  

    std::srand(std::time(0)); // 初始化随机数生成器  
    playlist.shuffleSongs(); // 随机排列歌曲顺序
    playlist.printSongs();// 打印随机排列后的歌曲  

    return 0;
}