#include <iostream>  
#include <vector>  
#include <string>  
#include <algorithm> 
#include <ctime>   
#include <sstream>
#include <unordered_set> 
#include <conio.h>
#include <windows.h>

class SongInfo {//创建类存储歌曲信息
public:
    std::string name;//名字
    std::string tags;//标签

    SongInfo(std::string name, std::string tags) : name(name), tags(tags) {}//初始化列表
    /*使用成员初始化列表可能比在构造函数体内赋值更高效，因为成员初始化列表直接在对象的
    构造过程中初始化成员变量，而构造函数体内的赋值操作则可能涉及额外的拷贝或移动操作。*/

    //检查当前歌曲是否拥有特定的标签
    bool hasTag(const std::string& wantedTag) const {//使用const将其声明为常量成员函数
        //这允许类的常量实例（即被声明为 const 的实例）调用这个函数，而不会违反常量性约束。

        std::istringstream iss(tags);//创建一个istringstream对象，以tags字符串作为数据源
        /*使用std::istringstream可以将一个包含多个数据项的字符串分割成单独的数据项，
        并将这些数据项转换为相应的数据类型（如整数、浮点数、字符串等）。*/

        std::string token;//用于临时存储从 std::istringstream 对象 iss 中读取的每一个由逗号分隔的字符串片段

        while (std::getline(iss, token, ',')) {//使用std::getline从iss中读取数据，直到没有更多数据，以','作为分隔符
            /*std::getline()从输入流iss中读取字符，直到遇到指定的分隔符','或到达输入流的末尾。
            读取的字符（不包括分隔符）被存储在字符串token中。*/
            if (token == wantedTag) {
                return true;
            }
        }
        return false;
    }

    void print() const { // 打印歌曲信息  
        std::cout << "名字: " << name << ", 标签: " << tags << std::endl;
    }
};

class SongPlaylist {//创建SongPlaylist类用于管理歌曲列表
public:
    void Init() {// 添加库中的初始歌曲  
        addSong(SongInfo("Song1", "Rock,Blues"));
        addSong(SongInfo("Song2", "Pop,Jazz,Latin"));
        addSong(SongInfo("Song3", "Classic"));
        addSong(SongInfo("Song4", "Pop,Rock,Classic"));
        addSong(SongInfo("Song5", "Blues"));
        addSong(SongInfo("Song6", "Classic,Pop"));
        addSong(SongInfo("Song7", "Jazz,Latin"));
        addSong(SongInfo("Song8", "Jazz,Blues,Rock"));
    }

    std::vector<SongInfo> originalOrder; // 创建数组记录原始顺序
    void addSong(const SongInfo& song) { // 添加歌曲  
        originalOrder.push_back(song);//记录顺序
    }

    //随机排列并打印给出的歌曲顺序
    void shuffleSongs(const std::vector<SongInfo>& givedOrder)const {
        std::vector<SongInfo> songsOrder = givedOrder;

        //考虑到编译器版本不同，这里留下两个方式随机排列songsOrder
        std::random_shuffle(songsOrder.begin(), songsOrder.end());
        /*std::random_device rd;  // 非确定性随机数生成器
          std::mt19937 g(rd());   // 以rd()为种子的Mersenne Twister生成器
          std::uniform_int_distribution<> dist(0, songsOrder.size() - 1); //创建一个整数分布，范围从0到songsOrder.size()-1
          std::shuffle(songsOrder.begin(), songsOrder.end(), [&]() { return dist(g); });// 使用std::shuffle来随机重排songsOrder*/

        for (const auto& song : songsOrder) {//打印
            song.print();
        }
    }
    void shuffleSongs()const {//未输入就将原始列表随机排序
        std::vector<SongInfo> songsOrder = originalOrder;
        std::random_shuffle(songsOrder.begin(), songsOrder.end());
        for (const auto& song : songsOrder) {//打印
            song.print();
        }
    }

    void printAllSongs() const { //打印初始列表
        for (const auto& song : originalOrder) {//打印
            song.print();
        }
    }


    // 获取包含特定标签的所有歌曲的随机排列  
    void getSongsByTagRandomly(const std::string& wantedTag) const {
        std::vector<SongInfo> filteredSongs;//创建数组储存筛选（未排序）后的歌曲
        for (const auto& song : originalOrder) {//使用songInfo中创建的hasTag函数筛选出拥有特定标签的歌曲并添加到filteredSongs后
            if (song.hasTag(wantedTag)) {
                filteredSongs.push_back(song);
            }
        }

        if (!filteredSongs.empty()) {//若不为空（即存在符合要求的歌曲），则随机排列

            std::cout << "符合条件的歌曲列表为：" << std::endl;
            shuffleSongs(filteredSongs);  // 随机排列并输出筛选后的歌曲  
        }
        else {
            std::cout << "没有找到对应歌曲，再试试吧。" << std::endl;
        }
    }


    // 获取与给定歌曲具有相同标签的所有歌曲的随机排列  
    void getSongsWithSameTagsRandomly(const SongInfo& referenceSong) const {

        std::vector<SongInfo> filteredSongs;//筛选后的歌曲列表

        std::istringstream iss(referenceSong.tags);//获取想要的歌曲的标签
        std::vector<std::string> tags;//tags作为数组分开存储不同的标签
        std::string token;
        while (std::getline(iss, token, ',')) {
            tags.push_back(token);
        }
        //现在获得了能够轻松遍历的所有需要的标签
        for (const auto& song : originalOrder) {//遍历所有歌曲列表
            for (const auto& wantedTag : tags) {//遍历想要的歌曲的所有标签
                if (song.hasTag(wantedTag)) {
                    filteredSongs.push_back(song);
                    break;
                }
            }
        }
        //现在获得了所有符合要求的歌曲列表

        shuffleSongs(filteredSongs);  // 随机排列并输出筛选后的歌曲  
    }

};

void menu() {
    SongPlaylist playlist;
    for (int i = 0;i <= 600;i++) {//炫酷的启动画面
        if (i == 0) { system("color 4F"); }
        if (i == 100) { system("color 2F"); }
        if (i == 200) { system("color 1F"); }
        if (i == 300) { system("color 4F"); }
        if (i == 400) { system("color 6F"); }
        if (i == 500) { system("color 1F"); }
        if (i % 8 == 0) { std::cout << std::endl; }
        if (i <= 100) { std::cout << "|   欢迎   |"; }
        if (i <= 200 && i > 100) { std::cout << "|   使用   |"; }
        if (i <= 300 && i > 200) { std::cout << "|    由    |"; }
        if (i <= 400 && i > 300) { std::cout << "|  Zircon  |"; }
        if (i <= 500 && i > 400) { std::cout << "|  编写的  |"; }
        if (i > 500) { std::cout << "|  歌曲库  |"; }
        Sleep(1);
    }

    playlist.addSong(SongInfo("Song1", "Rock,Blues"));//填充最初的数据
    playlist.addSong(SongInfo("Song2", "Pop,Jazz,Latin"));
    playlist.addSong(SongInfo("Song3", "Classic"));
    playlist.addSong(SongInfo("Song4", "Pop,Rock,Classic"));
    playlist.addSong(SongInfo("Song5", "Blues"));
    playlist.addSong(SongInfo("Song6", "Classic,Pop"));
    playlist.addSong(SongInfo("Song7", "Jazz,Latin"));
    playlist.addSong(SongInfo("Song8", "Jazz,Blues,Rock"));

    int choice;

    while (true) {
        system("cls");//清屏
        std::cout << "\n";
        std::cout << "菜单:\n";
        std::cout << "1. 列表循环\n";
        std::cout << "2. 随机播放\n";
        std::cout << "3. 标签搜索\n";
        std::cout << "4. 猜你喜欢\n";
        std::cout << "5. 添加歌曲\n";
        std::cout << "0. Exit\n";
        std::cout << "Tips：请不要直接点叉结束进程，防止异常占用\n";
        std::cout << "如果真的点了的话，接下来，任务管理器会很有用\n";
        std::cout << "\n";
        std::cin >> choice;

        switch (choice) {

        case 1: {
            std::cout << "歌单里有:" << std::endl;
            playlist.printAllSongs();
            system("PAUSE");
            break;
        }
        case 2: {
            std::cout << "随机排列后的歌单为：" << std::endl;
            playlist.shuffleSongs();
            system("PAUSE");
            break;
        }
        case 3: {
            std::string wanttag;

            std::cout << "请输入要搜索的标签: ";
            std::cin >> wanttag;

            playlist.getSongsByTagRandomly(wanttag);
            system("PAUSE");
            break;
        }

        case 4: {
            // 获取并打印与选择的歌曲拥有相同标签的歌曲的随机排列 
            std::cout << "歌单里有:" << std::endl;// 打印所有歌曲（原始顺序） 
            playlist.printAllSongs();

            std::cout << "\n今天想听第几首歌？" << std::endl;
            int n;
            std::cin >> n;

            auto referenceSong = playlist.originalOrder[n - 1];
            std::cout << "\n由第" << n << "首歌，猜你喜欢:" << std::endl;
            playlist.getSongsWithSameTagsRandomly(referenceSong);
            system("PAUSE");
            break;
        }
        case 5: {
            std::string NewSong, NewTag;

            std::cout << "请输入要增加的歌曲名：" << std::endl;
            std::cin >> NewSong;
            std::cout << "请输入要增加的歌曲标签，标签之间用逗号隔开：" << std::endl;
            std::cin >> NewTag;

            playlist.addSong(SongInfo(NewSong, NewTag));
            //playlist.addSong(SongInfo("Song9", "Latin"));

            std::cout << "现在歌单里有:" << std::endl;
            playlist.printAllSongs();// 打印所有歌曲（原始顺序） 
            system("PAUSE");
            break;
        }

        case 0: {
            std::cout << "退出中...你的电脑在感谢你良好的使用习惯\n";

            return;
        }
        case 666: {
            std::cout << "恭喜你找到了隐藏的神秘咒语，今天一定会有好事发生。";
            system("PAUSE");
            break;
        }
        default: {
            std::cout << "看不懂，请重试。\n";
            system("PAUSE");
            break;
        }
        }
    }
}

int main() {

    menu();

    return 0;
}