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

void addSong(Playlist* playlist, const char* title, const char* artist, int duration){
    Song* newSong = (Song*)malloc(sizeof(Song));

    if(newSong == NULL){
        printf("Memory allocation failed!\n");
        return;
    }

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

    printf("-> Added: %s by %s\n\n", title, artist);
}

void playNext(Playlist* playlist){
    if(isEmpty(playlist)){
        printf("ERROR: The playlist is currently empty! Add some songs first.\n\n");
        return;
    }

    Song* temp = playlist->head;

    printf("... Now Playing ...\n");
    printf("-> Dequeued and Played: %s (%s)\n\n", temp->title, temp->artist);

    playlist->head = playlist->head->next;

    if(playlist->head == NULL){
        playlist->tail = NULL;
    }

    free(temp);
}

void viewPlaylist(Playlist* playlist){
    if(isEmpty(playlist)){
        printf("The playlist is currently empty.\n\n");
        return;
    }

    Song* current = playlist->head;
    int i = 1;

    printf("--- Current Playlist (Next Up is Song 1) ---\n");

    while(current != NULL){
        printf("[%d] %s (%s) - %d sec\n",
               i,
               current->title,
               current->artist,
               current->duration);
        current = current->next;
        i++;
    }

    printf("------------------------------------------\n\n");
}

void totalDuration(Playlist* playlist){
    if(isEmpty(playlist)){
        printf("Total Duration: 0 seconds\n\n");
        return;
    }

    Song* current = playlist->head;
    int total = 0;

    while(current != NULL){
        total += current->duration;
        current = current->next;
    }

    int minutes = total / 60;
    int seconds = total % 60;

    printf("Total Duration of Playlist: %d seconds (%d min, %d sec)\n\n",
           total, minutes, seconds);
}

void displayLibrary(){
    printf("\n--- Initial Song Library ---\n");
    printf("[1] One Last Breath (Creed) - 242 sec\n");
    printf("[2] My Sacrifice (Creed) - 294 sec\n");
    printf("[3] Higher (Creed) - 316 sec\n");
    printf("[4] With Arms Wide Open (Creed) - 258 sec\n");
    printf("[5] My Own Prison (Creed) - 300 sec\n");
    printf("[6] What If (Creed) - 305 sec\n");
    printf("[7] Bullets (Creed) - 240 sec\n");
    printf("[8] Don't Stop Dancing (Creed) - 275 sec\n");
    printf("[9] Torn (Creed) - 250 sec\n");
    printf("[10] Are You Ready? (Creed) - 260 sec\n\n");
}

void menu(){
    printf("** Playlist Menu **\n");
    printf("1. Add Song to Playlist (Enqueue)\n");
    printf("2. View Current Playlist\n");
    printf("3. Play Next Song (Dequeue)\n");
    printf("4. Show Total Duration\n");
    printf("5. Exit\n");
    printf("----------------------------\n");
}

void freePlaylist(Playlist* playlist){
    Song* current = playlist->head;
    while(current != NULL){
        Song* temp = current;
        current = current->next;
        free(temp);
    }
    playlist->head = NULL;
    playlist->tail = NULL;
}

int main(){
    Playlist playlist;
    playlist.head = NULL;
    playlist.tail = NULL;

    int choice, num;

    printf("*** MUSIC PLAYLIST (LINKED LIST QUEUE) ***\n\n");

    do{
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                displayLibrary();
                printf("Enter song number (1-10): ");
                scanf("%d", &num);

                switch(num){
                    case 1: addSong(&playlist, "One Last Breath", "Creed", 242); break;
                    case 2: addSong(&playlist, "My Sacrifice", "Creed", 294); break;
                    case 3: addSong(&playlist, "Higher", "Creed", 316); break;
                    case 4: addSong(&playlist, "With Arms Wide Open", "Creed", 258); break;
                    case 5: addSong(&playlist, "My Own Prison", "Creed", 300); break;
                    case 6: addSong(&playlist, "What If", "Creed", 305); break;
                    case 7: addSong(&playlist, "Bullets", "Creed", 240); break;
                    case 8: addSong(&playlist, "Don't Stop Dancing", "Creed", 275); break;
                    case 9: addSong(&playlist, "Torn", "Creed", 250); break;
                    case 10: addSong(&playlist, "Are You Ready?", "Creed", 260); break;
                    default:
                        printf("Invalid song number!\n\n");
                }
                break;

            case 2:
                viewPlaylist(&playlist);
                break;

            case 3:
                playNext(&playlist);
                break;

            case 4:
                totalDuration(&playlist);
                break;

            case 5:
                printf("Exiting... Goodbye!\n");
                break;

            default:
                printf("Invalid choice!\n\n");
        }

    } while(choice != 5);

    freePlaylist(&playlist);
    return 0;
}
