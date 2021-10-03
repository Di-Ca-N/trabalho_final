#ifndef RANKING_H
#define RANKING_H

#define MAX_USERNAME_LENGTH 100

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    int score;
} RankingEntry;

typedef struct {
    RankingEntry entries[5];
} Ranking;

Ranking getRanking();                                               // Load and return the current ranking
Ranking saveOnRanking(Ranking ranking, char* username, int score);  // Add an entry to the rank with the given username and score

#endif