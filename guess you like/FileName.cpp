#include <iostream>  
#include <vector>  
#include <string>  
#include <algorithm> 
#include <ctime>     

class SongInfo {//����SongInfo�����ڴ洢�ʹ�ӡ��������Ϣ
public:
    std::string name;//����
    std::string tags;//��ǩ
    std::string singer;//����

    SongInfo(std::string name, std::string tags,std::string singer) : name(name), tags(tags),singer(singer) {}//��ʼ���б�

    void print()const{  // ��ӡ������Ϣ
        std::cout << "��������: " << name << ", ��ǩ: " << tags <<"�����֣�"<<singer <<std::endl;
    }
};

class SongPlaylist {// ����SongPlaylist�����ڶԸ������й���
private:
    std::vector<SongInfo> songsOrder;//��������������˳��
    std::vector<SongInfo> originalOrder; // ���������¼ԭʼ˳��  

  
public:
    void addSong(const SongInfo& song) { // ��Ӹ�����Ϣ  
        songsOrder.push_back(song);//��SongPlaylist�м�¼˳��
        originalOrder.push_back(song); // ��SongPlaylist�м�¼ԭʼ˳�� 
    }
    void shuffleSongs() {    // ������и���˳��
        std::random_shuffle(songsOrder.begin(), songsOrder.end()); 
    }

    void printOriginalOrder() const { // ��ӡԭʼ˳��ĸ���  
        std::cout << "ԭʼ˳��Ϊ:" << std::endl;
        for (const auto& song : originalOrder) {
            song.print();
        }
    }

    void printSongs() const { // ��ӡ������к����˳��  
        std::cout << "������к�:" << std::endl;
        for (const auto& song : songsOrder) {
            song.print();
        }
    }
};

int main() {
    SongPlaylist playlist;

    // ��Ӹ���  
    playlist.addSong(SongInfo("Song 1", "Classical","singer1"));
    playlist.addSong(SongInfo("Song 2", "Pop","singer2"));
    playlist.addSong(SongInfo("Song 3", "Rock","singer3"));
    playlist.addSong(SongInfo("Song 4", "Jazz","singer4"));
    playlist.addSong(SongInfo("Song 5", "Classical","singer5"));

    playlist.printOriginalOrder();    // ��ӡԭʼ˳��  

    std::srand(std::time(0)); // ��ʼ�������������  
    playlist.shuffleSongs(); // ������и���˳��
    playlist.printSongs();// ��ӡ������к�ĸ���  

    return 0;
}