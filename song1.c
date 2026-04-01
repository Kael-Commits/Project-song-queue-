#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song{
    char title[100];
    char artist[100];
    int duration;
    struct Song* next;
} Song;

typedef struct{
    Song* head;
    Song* tail;
} Playlist;

int isEmpty(Playlist* playlist){
    return playlist->head == NULL;

}

void addSong(Playlist* playlist, const char* title, const char* artist, int duration){ //Enqueue para insert sa tail 
    Song* newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    newSong->duration = duration;
    newSong->next = NULL;

    if(isEmpty(playlist)){
        playlist->head = playlist->tail = newSong;
    } else {
        playlist->tail->next = newSong;
        playlist->tail = newSong;
    }
    printf("-> Added: %s by %s\n", title, artist);
}

void playNext(Playlist* playlist){ //Dequeue para remove sa head
    if(isEmpty(playlist)){
        printf("Playlist is empty! No songss to play! Add Songs first.\n"); 
        return;
    }
    Song* temp = playlist->head;
    printf("... Now Playing ...\n");
    printf("-> Dequeued and Played: %s (%s)\n", temp->title, temp->artist);
    playlist->head = playlist->head->next;
    if(playlist->head == NULL){
        playlist->tail = NULL;
    }
    free(temp);
}

