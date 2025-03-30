// Name: Dennis Madapatu and Ar-Raniry Ar-Rasyid
// Date: 1/22/2025
// Description: Takes song data and organizes it. Prints it out into a neat catalog, artists with a subcategory of their albums with a subcategory of their songs.

#include <bits/stdc++.h>

using namespace std;

struct Song // Struct for song taken from the writeup
{
    string songName;
    int songTime;
};

struct Album // Struct for album taken from the writeup
{
    string albumName;
    int albumRuntime;
    int albumSongs;
    map<int, Song> albumMap; // int should be the tracking number
};

struct Artist // Struct for Artist taken from the writeup
{
    map<string, Album> discography; // string should be the album's name
    string artistName;
    int artistRuntime;
    int artistSongs;
};

string timeToString(int totalTime) // Helper function used to convert the time into a string
{
    int minutes = totalTime / 60;
    int seconds = totalTime % 60;
    string time;
    if (seconds < 10)
    {
        time = "0" + to_string(seconds);
    }
    else
    {
        time = to_string(seconds);
    }
    return to_string(minutes) + ":" + time;
}

void printEverything(map<string, Artist> &artistMap) // Helper function used to print everything 
{
    for (map<string, Artist>::const_iterator artistIterator = artistMap.begin(); artistIterator != artistMap.end(); ++artistIterator)
    {
        const Artist &artist = artistIterator->second;

        cout << artist.artistName << ": " << artist.artistSongs << ", " << timeToString(artist.artistRuntime) << endl;

        for (map<string, Album>::const_iterator albumIterator = artist.discography.begin(); albumIterator != artist.discography.end(); ++albumIterator)
        {
            const Album &album = albumIterator->second;

            cout << "        " << album.albumName << ": " << album.albumSongs << ", " << timeToString(album.albumRuntime) << endl;

            for (map<int, Song>::const_iterator songIterator = album.albumMap.begin(); songIterator != album.albumMap.end(); ++songIterator)
            {
                const Song &song = songIterator->second;

                cout << "                " << songIterator->first << ". " << song.songName << ": " << timeToString(song.songTime) << endl;
            }
        }
    }
}

string replaceUnderscores(string str) // Helper function used to replace underscores with whitespace. replace function found on geeksforgeeks (https://www.geeksforgeeks.org/std-string-replace-in-cpp/)
{
    replace(str.begin(), str.end(), '_', ' ');
    return str;
}

int calculateTime(string minutes, string seconds) // Helper function used to find total time in seconds
{
    int numMinutes = stoi(minutes);
    int numSeconds = stoi(seconds);
    int totalSeconds = (numMinutes * 60) + numSeconds;
    return totalSeconds;
}

int main(int argc, char *argv[])
{

    map<string, Artist> artistMap; // Map of all of the artists
    ifstream fin(argv[1]);         // Opens the file given by the user

    string line;
    while (getline(fin, line)) // While statement used to start reading through the file
    {
        istringstream iss(line); // Taking in all of the pieces of information from the lines and splitting them into separate variables
        string title, minutes, seconds, artist, album, genre, trackNumOne;
        getline(iss, title, ' ');
        getline(iss, minutes, ':');
        getline(iss, seconds, ' ');
        getline(iss, artist, ' ');
        getline(iss, album, ' ');
        getline(iss, genre, ' ');
        getline(iss, trackNumOne, ' ');
        // Immediately removing underscores from the strings
        title = replaceUnderscores(title);
        artist = replaceUnderscores(artist);
        album = replaceUnderscores(album);

        int time = calculateTime(minutes, seconds); // Putting the time in seconds (int rather than string)
        int trackNumTwo = stoi(trackNumOne); // changing trackNum's data type to int

        if (artistMap.find(artist) == artistMap.end()) // If the artist was not found in the map, make a new artist 
        {
            artistMap[artist] = Artist();
            artistMap[artist].artistName = artist;
        }
        Artist &newArtist = artistMap[artist]; // Make a reference to the artist inside of the map for editting variables later

        if (newArtist.discography.find(album) == newArtist.discography.end()) // If the album is not found inside of the album map, create a new album
        {
            newArtist.discography[album] = Album();
            newArtist.discography[album].albumName = album;
        }
        Album &newAlbum = newArtist.discography[album]; // Make a reference to the album inside of the map

        Song newSong{title, time};
        newAlbum.albumMap[trackNumTwo] = newSong; // Adding the song (under the assumption that duplicate songs do not exist in this dataset) 
        // Updating the variables of the artist and album using the references made earlier
        newArtist.artistRuntime += time;
        newArtist.artistSongs++;
        newAlbum.albumRuntime += time;
        newAlbum.albumSongs++;
    }
    printEverything(artistMap); // Print everything out after the data has been inserted correctly
}