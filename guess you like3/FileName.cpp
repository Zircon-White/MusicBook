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

    bool hasTag(const std::string& wantedTag) const {//��鵱ǰ�����Ƿ�ӵ�и����ı�ǩ
        std::istringstream iss(tags);
        std::string token;
        while (std::getline(iss, token, ',')) {
            if (token == wantedTag) return true;
        }
        return false;
    }

    void print() const { // ��ӡ������Ϣ  
        std::cout << "����: " << name << ", ��ǩ: " << tags << std::endl;
    }
};

class SongPlaylist {
public:
    std::vector<SongInfo> songs;

    void addSong(const SongInfo& song) { // ��Ӹ���  
        songs.push_back(song);
    }

    // ��ȡ���������������ͬ��ǩ�����и������������  
    std::vector<SongInfo> getSongsWithSameTagsRandomly(const SongInfo& referenceSong) const {

        std::vector<SongInfo> filteredSongs;//ɸѡ��ĸ���

        std::istringstream iss(referenceSong.tags);//��ȡ��Ҫ�ĸ����ı�ǩ
        std::vector<std::string> tags;
        std::string token;
        while (std::getline(iss, token, ',')) {
            tags.push_back(token);
        }
         for (const auto& song : songs){//�������и���
            for(const auto & wantedTag : tags){//������Ҫ�ĸ��������б�ǩ
                if (song.hasTag(wantedTag)) {
                    filteredSongs.push_back(song);
                    break;
                }
            }
        }


        if (!filteredSongs.empty()) {// ���filteredSongs��Ϊ�գ����������  
            std::random_shuffle(filteredSongs.begin(), filteredSongs.end());
        }

        return filteredSongs;
    }

    void printAllSongs() const { //��ӡ���и��� 
        for (const auto& song : songs) {
            song.print();
        }
    }
};

int main() {
    SongPlaylist playlist;

    // ��Ӹ���  
    playlist.addSong(SongInfo("Song1", "Rock,Blues"));
    playlist.addSong(SongInfo("Song2", "Pop,Jazz,Latin"));
    playlist.addSong(SongInfo("Song3", "Classic"));
    playlist.addSong(SongInfo("Song4", "Pop,Rock,Classic"));
    playlist.addSong(SongInfo("Song5", "Blues"));
    playlist.addSong(SongInfo("Song6", "Classic,Pop"));
    playlist.addSong(SongInfo("Song7", "Jazz,Latin"));
    playlist.addSong(SongInfo("Song8", "Jazz,Blues,Rock"));
    playlist.addSong(SongInfo("Song9", "Latin"));

    std::cout << "�赥��һ����:" << std::endl;// ��ӡ���и�����ԭʼ˳�� 
    playlist.printAllSongs();

    // ��ȡ����ӡ��ѡ��ĸ���ӵ����ͬ��ǩ�ĸ������������  
    std::cout << "\n���������ڼ��׸裿" << std::endl;
    int n;
    std::cin >> n;
    auto referenceSong = playlist.songs[n-1];
    std::cout << "\n�ɵ�"<<n<<"�׸裬����ϲ��:" << std::endl;
    auto sameTagSongs = playlist.getSongsWithSameTagsRandomly(referenceSong);
    for (const auto& song : sameTagSongs) {
        song.print();
    }

    return 0;
}