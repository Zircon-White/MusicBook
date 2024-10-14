#include <iostream>  
#include <vector>  
#include <string>  
#include <algorithm> 
#include <ctime>   
#include <sstream>
#include <unordered_set> 
#include <conio.h>
#include <windows.h>

class SongInfo {//������洢������Ϣ
public:
    std::string name;//����
    std::string tags;//��ǩ

    SongInfo(std::string name, std::string tags) : name(name), tags(tags) {}//��ʼ���б�
    /*ʹ�ó�Ա��ʼ���б���ܱ��ڹ��캯�����ڸ�ֵ����Ч����Ϊ��Ա��ʼ���б�ֱ���ڶ����
    ��������г�ʼ����Ա�����������캯�����ڵĸ�ֵ����������漰����Ŀ������ƶ�������*/

    //��鵱ǰ�����Ƿ�ӵ���ض��ı�ǩ
    bool hasTag(const std::string& wantedTag) const {//ʹ��const��������Ϊ������Ա����
        //��������ĳ���ʵ������������Ϊ const ��ʵ�����������������������Υ��������Լ����

        std::istringstream iss(tags);//����һ��istringstream������tags�ַ�����Ϊ����Դ
        /*ʹ��std::istringstream���Խ�һ�����������������ַ����ָ�ɵ����������
        ������Щ������ת��Ϊ��Ӧ���������ͣ������������������ַ����ȣ���*/

        std::string token;//������ʱ�洢�� std::istringstream ���� iss �ж�ȡ��ÿһ���ɶ��ŷָ����ַ���Ƭ��

        while (std::getline(iss, token, ',')) {//ʹ��std::getline��iss�ж�ȡ���ݣ�ֱ��û�и������ݣ���','��Ϊ�ָ���
            /*std::getline()��������iss�ж�ȡ�ַ���ֱ������ָ���ķָ���','�򵽴���������ĩβ��
            ��ȡ���ַ����������ָ��������洢���ַ���token�С�*/
            if (token == wantedTag) {
                return true;
            }
        }
        return false;
    }

    void print() const { // ��ӡ������Ϣ  
        std::cout << "����: " << name << ", ��ǩ: " << tags << std::endl;
    }
};

class SongPlaylist {//����SongPlaylist�����ڹ�������б�
public:
    void Init() {// ��ӿ��еĳ�ʼ����  
        addSong(SongInfo("Song1", "Rock,Blues"));
        addSong(SongInfo("Song2", "Pop,Jazz,Latin"));
        addSong(SongInfo("Song3", "Classic"));
        addSong(SongInfo("Song4", "Pop,Rock,Classic"));
        addSong(SongInfo("Song5", "Blues"));
        addSong(SongInfo("Song6", "Classic,Pop"));
        addSong(SongInfo("Song7", "Jazz,Latin"));
        addSong(SongInfo("Song8", "Jazz,Blues,Rock"));
    }

    std::vector<SongInfo> originalOrder; // ���������¼ԭʼ˳��
    void addSong(const SongInfo& song) { // ��Ӹ���  
        originalOrder.push_back(song);//��¼˳��
    }

    //������в���ӡ�����ĸ���˳��
    void shuffleSongs(const std::vector<SongInfo>& givedOrder)const {
        std::vector<SongInfo> songsOrder = givedOrder;

        //���ǵ��������汾��ͬ����������������ʽ�������songsOrder
        std::random_shuffle(songsOrder.begin(), songsOrder.end());
        /*std::random_device rd;  // ��ȷ���������������
          std::mt19937 g(rd());   // ��rd()Ϊ���ӵ�Mersenne Twister������
          std::uniform_int_distribution<> dist(0, songsOrder.size() - 1); //����һ�������ֲ�����Χ��0��songsOrder.size()-1
          std::shuffle(songsOrder.begin(), songsOrder.end(), [&]() { return dist(g); });// ʹ��std::shuffle���������songsOrder*/

        for (const auto& song : songsOrder) {//��ӡ
            song.print();
        }
    }
    void shuffleSongs()const {//δ����ͽ�ԭʼ�б��������
        std::vector<SongInfo> songsOrder = originalOrder;
        std::random_shuffle(songsOrder.begin(), songsOrder.end());
        for (const auto& song : songsOrder) {//��ӡ
            song.print();
        }
    }

    void printAllSongs() const { //��ӡ��ʼ�б�
        for (const auto& song : originalOrder) {//��ӡ
            song.print();
        }
    }


    // ��ȡ�����ض���ǩ�����и������������  
    void getSongsByTagRandomly(const std::string& wantedTag) const {
        std::vector<SongInfo> filteredSongs;//�������鴢��ɸѡ��δ���򣩺�ĸ���
        for (const auto& song : originalOrder) {//ʹ��songInfo�д�����hasTag����ɸѡ��ӵ���ض���ǩ�ĸ�������ӵ�filteredSongs��
            if (song.hasTag(wantedTag)) {
                filteredSongs.push_back(song);
            }
        }

        if (!filteredSongs.empty()) {//����Ϊ�գ������ڷ���Ҫ��ĸ����������������

            std::cout << "���������ĸ����б�Ϊ��" << std::endl;
            shuffleSongs(filteredSongs);  // ������в����ɸѡ��ĸ���  
        }
        else {
            std::cout << "û���ҵ���Ӧ�����������԰ɡ�" << std::endl;
        }
    }


    // ��ȡ���������������ͬ��ǩ�����и������������  
    void getSongsWithSameTagsRandomly(const SongInfo& referenceSong) const {

        std::vector<SongInfo> filteredSongs;//ɸѡ��ĸ����б�

        std::istringstream iss(referenceSong.tags);//��ȡ��Ҫ�ĸ����ı�ǩ
        std::vector<std::string> tags;//tags��Ϊ����ֿ��洢��ͬ�ı�ǩ
        std::string token;
        while (std::getline(iss, token, ',')) {
            tags.push_back(token);
        }
        //���ڻ�����ܹ����ɱ�����������Ҫ�ı�ǩ
        for (const auto& song : originalOrder) {//�������и����б�
            for (const auto& wantedTag : tags) {//������Ҫ�ĸ��������б�ǩ
                if (song.hasTag(wantedTag)) {
                    filteredSongs.push_back(song);
                    break;
                }
            }
        }
        //���ڻ�������з���Ҫ��ĸ����б�

        shuffleSongs(filteredSongs);  // ������в����ɸѡ��ĸ���  
    }

};

void menu() {
    SongPlaylist playlist;
    for (int i = 0;i <= 600;i++) {//�ſ����������
        if (i == 0) { system("color 4F"); }
        if (i == 100) { system("color 2F"); }
        if (i == 200) { system("color 1F"); }
        if (i == 300) { system("color 4F"); }
        if (i == 400) { system("color 6F"); }
        if (i == 500) { system("color 1F"); }
        if (i % 8 == 0) { std::cout << std::endl; }
        if (i <= 100) { std::cout << "|   ��ӭ   |"; }
        if (i <= 200 && i > 100) { std::cout << "|   ʹ��   |"; }
        if (i <= 300 && i > 200) { std::cout << "|    ��    |"; }
        if (i <= 400 && i > 300) { std::cout << "|  Zircon  |"; }
        if (i <= 500 && i > 400) { std::cout << "|  ��д��  |"; }
        if (i > 500) { std::cout << "|  ������  |"; }
        Sleep(1);
    }

    playlist.addSong(SongInfo("Song1", "Rock,Blues"));//������������
    playlist.addSong(SongInfo("Song2", "Pop,Jazz,Latin"));
    playlist.addSong(SongInfo("Song3", "Classic"));
    playlist.addSong(SongInfo("Song4", "Pop,Rock,Classic"));
    playlist.addSong(SongInfo("Song5", "Blues"));
    playlist.addSong(SongInfo("Song6", "Classic,Pop"));
    playlist.addSong(SongInfo("Song7", "Jazz,Latin"));
    playlist.addSong(SongInfo("Song8", "Jazz,Blues,Rock"));

    int choice;

    while (true) {
        system("cls");//����
        std::cout << "\n";
        std::cout << "�˵�:\n";
        std::cout << "1. �б�ѭ��\n";
        std::cout << "2. �������\n";
        std::cout << "3. ��ǩ����\n";
        std::cout << "4. ����ϲ��\n";
        std::cout << "5. ��Ӹ���\n";
        std::cout << "0. Exit\n";
        std::cout << "Tips���벻Ҫֱ�ӵ��������̣���ֹ�쳣ռ��\n";
        std::cout << "�����ĵ��˵Ļ���������������������������\n";
        std::cout << "\n";
        std::cin >> choice;

        switch (choice) {

        case 1: {
            std::cout << "�赥����:" << std::endl;
            playlist.printAllSongs();
            system("PAUSE");
            break;
        }
        case 2: {
            std::cout << "������к�ĸ赥Ϊ��" << std::endl;
            playlist.shuffleSongs();
            system("PAUSE");
            break;
        }
        case 3: {
            std::string wanttag;

            std::cout << "������Ҫ�����ı�ǩ: ";
            std::cin >> wanttag;

            playlist.getSongsByTagRandomly(wanttag);
            system("PAUSE");
            break;
        }

        case 4: {
            // ��ȡ����ӡ��ѡ��ĸ���ӵ����ͬ��ǩ�ĸ������������ 
            std::cout << "�赥����:" << std::endl;// ��ӡ���и�����ԭʼ˳�� 
            playlist.printAllSongs();

            std::cout << "\n���������ڼ��׸裿" << std::endl;
            int n;
            std::cin >> n;

            auto referenceSong = playlist.originalOrder[n - 1];
            std::cout << "\n�ɵ�" << n << "�׸裬����ϲ��:" << std::endl;
            playlist.getSongsWithSameTagsRandomly(referenceSong);
            system("PAUSE");
            break;
        }
        case 5: {
            std::string NewSong, NewTag;

            std::cout << "������Ҫ���ӵĸ�������" << std::endl;
            std::cin >> NewSong;
            std::cout << "������Ҫ���ӵĸ�����ǩ����ǩ֮���ö��Ÿ�����" << std::endl;
            std::cin >> NewTag;

            playlist.addSong(SongInfo(NewSong, NewTag));
            //playlist.addSong(SongInfo("Song9", "Latin"));

            std::cout << "���ڸ赥����:" << std::endl;
            playlist.printAllSongs();// ��ӡ���и�����ԭʼ˳�� 
            system("PAUSE");
            break;
        }

        case 0: {
            std::cout << "�˳���...��ĵ����ڸ�л�����õ�ʹ��ϰ��\n";

            return;
        }
        case 666: {
            std::cout << "��ϲ���ҵ������ص������������һ�����к��·�����";
            system("PAUSE");
            break;
        }
        default: {
            std::cout << "�������������ԡ�\n";
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