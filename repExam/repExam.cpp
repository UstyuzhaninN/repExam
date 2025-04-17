#include <iostream>
#include <string.h>
#include <fstream>


#define DEBUG


using namespace std;


struct Composer
{
    char name[20];
    char surname[20];
};

struct Song
{
    Composer composer;
    char songName[100];
    char text[5000];
    char performer[100];
    char year[15];
};

struct SongList
{
    Song* songs;
    int listSize = 10;
    int numberOfSongs = 0;
};

void fillSongInfo(Song& song, const char* songname, const char* performer,
    const char* composerName, const char* composerSurname, const char* year, const char* lyrics)
{
    strncpy_s(song.songName, songname, sizeof(song.songName) - 1);
    song.songName[sizeof(song.songName) - 1] = '\0';
    strncpy_s(song.performer, performer, sizeof(song.performer) - 1);
    song.performer[sizeof(song.performer) - 1] = '\0';
    strncpy_s(song.composer.name, composerName, sizeof(song.composer.name) - 1);
    song.composer.name[sizeof(song.composer.name) - 1] = '\0';
    strncpy_s(song.composer.surname, composerSurname, sizeof(song.composer.surname) - 1);
    song.composer.surname[sizeof(song.composer.surname) - 1] = '\0';
    strncpy_s(song.year, year, sizeof(song.year) - 1);
    song.year[sizeof(song.year) - 1] = '\0';
    strncpy_s(song.text, lyrics, sizeof(song.text) - 1);
    song.text[sizeof(song.text) - 1] = '\0';
}

void fillSongInfo(Song& song)
{
    cout << "Enter songname: "; cin.getline(song.songName, sizeof(song.songName));
    cout << "Enter performer: "; cin.getline(song.performer, sizeof(song.performer));
    cout << "Enter composer`s name: "; cin.getline(song.composer.name, sizeof(song.composer.name));
    cout << "Enter composer`s surname: "; cin.getline(song.composer.surname, sizeof(song.composer.surname));
    cout << "Enter release year: "; cin.getline(song.year, sizeof(song.year));
    cout << "Enter lyrics: "; cin.getline(song.text, 5000);
}

void printSong(Song song)
{
    cout << "Performer: " << song.performer << ", Song: " << song.songName << endl;
    cout << "(Composer: " << song.composer.name << " " << song.composer.surname << ", " << song.year << ")" << endl << endl;
    cout << song.text << endl;
}

void addSong(SongList& list, Song song)
{
    if(list.listSize == list.numberOfSongs-1) //проверка и уведичение размера массива
    {
        Song* newList = new Song[list.listSize *= 2];
        for (int i = 0; i < list.numberOfSongs; i++)
        {
            newList[i] = list.songs[i];
        }
        delete[] list.songs;
        list.songs = newList;
    }
    list.songs[list.numberOfSongs++] = song;
}

void printSongList(SongList& list)
{
    for (int i = 0; i < list.numberOfSongs;i++)

    {
        printSong(list.songs[i]);
        cout << endl;
    }

}

void deleteSong(SongList& list, const char* songname)
{
    if(list.numberOfSongs>0)
    {
        bool isFound = false;
        Song* newSongs = new Song[list.listSize - 1]; //создаем новый массив с размером на один меньше, чем был каталог
        int newsize = 0;
        for (int i = 0; i < list.numberOfSongs; i++) // перебор всех песен в каталоге
        {
            if (strcmp(list.songs[i].songName, songname) != 0) //если названия не совпали, то
            {
                newSongs[newsize++] = list.songs[i];
            }
            else
            {
                isFound = true;
            }
        }

        if (isFound)
        {
            delete[] list.songs;
            list.songs = newSongs;
            list.numberOfSongs = newsize;
        }
        else
        {
            delete[] newSongs;
            cout << "Song is not found" << endl;
        }
    }

}

void downloadSong(SongList list, const char* songname)
{
    cout << "Enter path to save: ";
    char nameToDownload[100] = ""; // Инициализация пустой строки
    cin.ignore(); // Очистка буфера // Игнорируем один символ (обычно это '\n')
    cin.getline(nameToDownload, sizeof(nameToDownload));
    // Добавление ".txt" к имени файла
    strncat_s(nameToDownload, ".txt", sizeof(nameToDownload) - strlen(nameToDownload) - 1);
    cout << nameToDownload << endl;
    bool isFound = false;
    int i = 0;


    //поиск совпадений

    for (; i < list.numberOfSongs; i++)
    {
        if (strcmp(list.songs[i].songName, songname) == 0)
        {
            isFound = true;
            break;
        }
    }

    if (isFound)
    {
        ofstream fout(nameToDownload);
        if (!fout.is_open())
        {
            cout << "Не удалось открыть файл";
            return;
        }
        fout << list.songs[i].text << endl;
        fout.close();
    }
    else
    {
        cout << "Song is not found" << endl;
    }
}

void searchByPerformer(SongList list, const char* performer)

{
    bool isFound = false;
    int i = 0;

    for (; i < list.numberOfSongs; i++)
    {
        if (strstr(list.songs[i].performer, performer) != nullptr)
        {
            printSong(list.songs[i]);
            cout << endl;
            isFound = true;
        }
    }

    if (!isFound)
    {
        cout << "No match found" << endl;
    }
}

void searchByKey(SongList list, const char* keyword)
{
    bool isFound = false;
    int i = 0;
    for (; i < list.numberOfSongs; i++)
    {
        if (strstr(list.songs[i].text, keyword) != nullptr)
        {
            printSong(list.songs[i]);
            cout << endl;
            isFound = true;
        }
    }
    if (!isFound)
    {
        cout << "No match found" << endl;
    }
}


int main()
{
    system("chcp 1251");
    setlocale(LC_ALL, "ru");

    //common info
    SongList list;
    list.songs = new Song[list.listSize];
    int menu;
    int exit = 1;

    while (exit)

    {
        cout << "Menu:" << endl << "1. Add song" << endl << "2. Delete song" << endl << "3. Edit the text" << endl << "4. Download the song" << endl <<
            "5. Search by musician" << endl << "6. Search by keyword" << endl << "7. Song list" << endl << "0. Exit" << endl;

        cin >> menu;

        switch (menu)
        {
        case 1: {
            //song info
            int songAdd = 1;
            while (songAdd)
            {
                Song song;

#ifdef DEBUG
                fillSongInfo(song, "Weight", "Agent Orrange", "Nikita", "Ustyuzhanin", "2023", "Na-na-na");
#endif // DEBUG



#ifndef DEBUG
                fillSongInfo(song);
#endif // DEBUG

                addSong(list, song);
                cout << "Song added. Do you want to add another song? 1 - yes, 0 - no" << endl;;
                cin >> songAdd;
                cout << endl;
            }
            break;
        }
        case 2: {
            deleteSong(list, "Weight");
            break;
        }
        case 4: {
            downloadSong(list, "Weight");
            break;
        }
        case 7: {
            printSongList(list);
            break;
        }
        }

        cout << "1 - return to menu, 0 - exit" << endl;
        cin >> exit;
    }


    return 0;
}

//Добавление текста песни {может быть введен с клавиатуры или загружен из файла}

//Удаление текста песни

//Изменение текста песни

//Отображение текста песни в файл

//Поиск и отображение всех песен одного автора

//Поиск и отображение Всех песен, содержащих слово, указанное пользователем

