#include <iostream>  
#include <vector>  
#include <string>  
#include <algorithm> 
#include <ctime>     
#include <sstream>

class SongInfo {//����SongInfo�����ڴ洢������Ϣ
public:
    std::string name;//����
    std::string tags;//��ǩ

    SongInfo(std::string name, std::string tags) : name(name), tags(tags) {}//��ʼ��

    bool hasTag(const std::string& wantedTag) const {  // �������Ƿ�����ض���ǩ  
        //ʹ��istringstream
        std::istringstream iss(tags);//ʹ��istringstream�������ַ���tags��ȡΪiss
        std::string token;//����token�洢�ָ���ĵ���
        //�˴����뱣֤tagsǰ��û�пո񣬷�����Ҫ��ȥ
        while (std::getline(iss, token, ',')) { // ʹ��getline�������зָ���ĵ��ʣ�������getline��iss�л�ȡÿһ�����ʲ���ֵ��token�ϣ��Զ���Ϊ�ָ� 
            if (token == wantedTag) { // �Ƚϵ����Ƿ�Ϊ��Ҫ�ı�ǩ
                return true; 
            }
        }
        return false;

    /* size_t pos = 0; // ��ʼλ��  
        size_t foundPos;
        // ѭ��ֱ���Ҳ�������  
        while ((foundPos = tags.find(',', pos)) != std::string::npos) { // ��ȡ����֮ǰ�����ַ�������һ�����ʣ� 
            std::string token = tags.substr(pos, foundPos - pos);
            if (token == wantedTag) {
                return true;
            }
            pos = foundPos + 1;// �����ǣ�����λ���Բ�����һ������  
        }
        std::string token = tags.substr(pos); // ������һ�����ʣ�����û�ж��ţ�  
        if (token == wantedTag) {
            return true;
        }
        return false;*/
    }

    void print() const { // ��ӡ������Ϣ  
        std::cout <<"����: " << name << ", ��ǩ: " << tags << std::endl;
    }
};

class SongPlaylist { //����SongPlaylist��������˳��
private:
    std::vector<SongInfo> songs;
public:
    void addSong(const SongInfo& song) { //��Ӹ�����Ϣ 
        songs.push_back(song);
    }
    // ��ȡ�����ض���ǩ�����и������������  
    std::vector<SongInfo> getSongsByTagRandomly(const std::string& wantedTag) const {
        std::vector<SongInfo> filteredSongs;//�������鴢��ɸѡ��δ���򣩺�ĸ���
        for (const auto& song : songs) {//ʹ��songInfo�д�����hasTag����ɸѡ��ӵ���ض���ǩ�ĸ�������ӵ�filteredSongs��
            if (song.hasTag(wantedTag)) {
                filteredSongs.push_back(song);
            }
        }

        std::vector<SongInfo> shuffledSongs(filteredSongs);  // �������ɸѡ��ĸ���  
        std::random_shuffle(shuffledSongs.begin(), shuffledSongs.end()); 

        return shuffledSongs;
    }

    void printAllSongs() const { // ��ӡԭʼ˳��
        for (const auto& song : songs) {
            song.print();
        }
    }
};

int main() {
    SongPlaylist playlist;//����SongPlaylist�����playlist

    // ��Ӹ���  
    playlist.addSong(SongInfo("Song1", "Classical, Acoustic"));
    playlist.addSong(SongInfo("Song2", "Pop,Live,Experimental"));
    playlist.addSong(SongInfo("Song3", "Rock,Studio"));
    playlist.addSong(SongInfo("Song4", "Acoustic,Pop,Indie"));
    playlist.addSong(SongInfo("Song5", "Pop,Alternative"));
    playlist.addSong(SongInfo("Song6", "Pop"));
  
    std::cout << "ԭʼ˳��:" << std::endl;// ��ӡ���и�����ԭʼ˳�� 
    playlist.printAllSongs();

   
    std::cout << "\n������Pop����ǩ�ĸ���(������к�):" << std::endl; //��ȡ����ӡ����"Pop"��ǩ�ĸ������������ 
    auto popSongs = playlist.getSongsByTagRandomly("Pop");
    for (const auto& song : popSongs) {
        song.print();
    }
    return 0;
}