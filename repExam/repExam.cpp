#include <iostream>
#include <string.h>
#include <fstream>


//#define DEBUG


using namespace std;

const int MAX_LINES = 100;
const int MAX_LENGTH = 256;

struct Composer
{
    char name[20];
    char surname[20];
};

struct Lyrics
{
    char lines[MAX_LINES][MAX_LENGTH];
    int lineCounter = 0;
};

struct Song
{
    Composer composer;
    char songName[100];
    Lyrics lyrics;
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
   // strncpy_s(song.text, lyrics, sizeof(song.text) - 1);
  //  song.text[sizeof(song.text) - 1] = '\0';
}

void fillLyrics(Song& song)
{
    cout << "Enter lyrics: ";
    while (song.lyrics.lineCounter < MAX_LINES)
    {
        cin.getline(song.lyrics.lines[song.lyrics.lineCounter], MAX_LENGTH);
        if (strcmp(song.lyrics.lines[song.lyrics.lineCounter], "end") == 0)
        {
            break;
        }
        song.lyrics.lineCounter++;
    }
}

void printLyrics(Song& song)
{
    cout << "Lyrics: " << endl;
    for (int i = 0; i < song.lyrics.lineCounter; i++)
    {
        cout << song.lyrics.lines[i] << endl;
    }
}


void fillSongInfo(Song& song)
{
    cout << "Enter songname: "; cin.getline(song.songName, sizeof(song.songName));
    cout << "Enter performer: "; cin.getline(song.performer, sizeof(song.performer));
    cout << "Enter composer`s name: "; cin.getline(song.composer.name, sizeof(song.composer.name));
    cout << "Enter composer`s surname: "; cin.getline(song.composer.surname, sizeof(song.composer.surname));
    cout << "Enter release year: "; cin.getline(song.year, sizeof(song.year));
    fillLyrics(song);
}

void printSong(Song song)
{
    cout << "Performer: " << song.performer << ", Song: " << song.songName << endl;
    cout << "(Composer: " << song.composer.name << " " << song.composer.surname << ", " << song.year << ")" << endl << endl;
    printLyrics(song);
}


void addSong(SongList& list, Song song)
{
    if(list.listSize == list.numberOfSongs) //проверка и уведичение размера массива
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

                                                                                  //2
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
            cout << "Song deleted! " << endl;
        }
        else
        {
            delete[] newSongs;
            cout << "Song is not found" << endl;
        }
    }
    else
    {
        cout << "Song list is empty!" << endl;
    }

}

                                                                               //2 перегруз
void deleteSong(SongList& list)
{
    if (list.numberOfSongs > 0)
    {
        char songname[50];
        cout << "Enter song name to delete: ";
        cin >> songname;
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
            cout << "Song deleted! " << endl;

        }
        else
        {
            delete[] newSongs;
            cout << "No match found" << endl;
        }
    }
    else
    {
        cout << "Song list is empty!" << endl;
    }

}

#ifdef DEBUG
                                                                                                        //3
void editTheLyrics(SongList& list, const char* songname, const char* newLyrics)
{
    bool isFound = false;
    for (int i = 0; i < list.numberOfSongs; i++)
    {
        if (strcmp(list.songs[i].songName, songname) == 0)
        {
            isFound = true;
            cout << "Lyrcs before edit: " << endl;
            cout << list.songs[i].text << endl;
            cout << "Lyrcs after edit: " << endl;
            strncpy_s(list.songs[i].text, newLyrics, sizeof(list.songs[i].text - 1));
            list.songs[i].text[sizeof(list.songs[i].text - 1)] = '\0';
            cout << list.songs[i].text << endl;
        }
    }
}
#endif // DEBUG

                                                                                 //3 перегруз
void editTheLyrics(SongList& list)
{
    char songname[50];
    char newLyrics[5000];
    cout << "Enter song name to edit lyrics: ";
    cin >> songname;
    bool isFound = false;
    for (int i = 0; i < list.numberOfSongs; i++)
    {
        if (strcmp(list.songs[i].songName, songname) == 0)
        {
            isFound = true;
            cout << "Lyrcs before edit: " << endl;
            printLyrics(list.songs[i]);
            cout << "Enter new lyrics: ";
            //cin.ignore();
            fillLyrics(list.songs[i]);
            cout << "Lyrics edited successfully" << endl;
        }
        else
        {
            cout << "No match found" << endl;
        }
    }
}

#ifdef DEBUG

                                                                            //4
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
#endif // DEBUG

                                                                                   //4 перегруз
void downloadSong(SongList list)
{
    char songname[50];
    cout << "Enter song name to save: ";
    cin >> songname;
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
        cout << "Enter path to save: ";
        char nameToDownload[100] = ""; // Инициализация пустой строки
        cin.ignore(); // Очистка буфера // Игнорируем один символ (обычно это '\n')
        cin.getline(nameToDownload, sizeof(nameToDownload));
        // Добавление ".txt" к имени файла
        strncat_s(nameToDownload, ".txt", sizeof(nameToDownload) - strlen(nameToDownload) - 1);
        cout << nameToDownload << endl;

        ofstream fout(nameToDownload);
        if (!fout.is_open())
        {
            cout << "Не удалось открыть файл";
            return;
        }
            for (int j = 0; j < list.songs[i].lyrics.lineCounter; j++)
            {
                fout << list.songs[i].lyrics.lines[j];

            }
        fout.close();
    }
    else
    {
        cout << "Song is not found" << endl;
    }
}

                                                                                //5
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

                                                                    //5 перегруз
void searchByPerformer(SongList list)

{
    char performer[50];
    cout << "Enter performer to  find the song: ";
    cin >> performer;
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

#ifdef DEBUG
                                                                                    //6
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
#endif // DEBUG
                                                                    //6 перегруз
void searchByKey(SongList list)
{
    char keyword[50];
    cout << "Enter keyword to find the song: ";
    cin >> keyword;
    bool isFound = false;
    int i = 0;
    for (; i < list.numberOfSongs; i++)
    {
        for (int j = 0; j < list.songs[i].lyrics.lineCounter; j++)
        {
            if (strstr(list.songs[i].lyrics.lines[j], keyword) != nullptr)
            {
                printSong(list.songs[i]);
                cout << endl;
                isFound = true;
                break;
            }
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
        cout << "Menu:" << endl << "1. Add song" << endl << "2. Delete song" << endl << "3. Edit the lyrics"
            << endl << "4. Create txt file with lyrics" << endl << "5. Search by musician" << endl << "6. Search by keyword" << endl
            << "7. Song list" << endl <<  endl;

        cin >> menu;
        cin.ignore();

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
                cout << endl << "Song added. Do you want to add another song? 1 - yes, 0 - no" << endl;;
                cin >> songAdd;
                cout << endl;
            }
            break;
        }
#ifdef DEBUG
        case 2: {
            deleteSong(list, "Weight");
            break;
        }
        case 3: {
            editTheLyrics(list, "Weight", "Lyrics changed");
            break;
        }
        case 4: {
            downloadSong(list, "Weight");
            break;
        }
        case 5: {
            searchByPerformer(list, "Agent Orrange");
            break;
        }
        case 6: {
            searchByKey(list, "na");
            break;
        }
#endif // DEBUG
#ifndef DEBUG
        case 2: {
            deleteSong(list);
            break;
        }
        case 3: {
            editTheLyrics(list);
            break;
        }
        case 4: {
            downloadSong(list);
            break;
        }
        case 5: {
            searchByPerformer(list);
            break;
        }
        case 6: {
            searchByKey(list);
            break;
        }
#endif // DEBUG
        case 7: {
            printSongList(list);
            break;
        }
        }

        cout << endl << "1 - return to menu, 0 - exit" << endl;
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

