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

Ranking getRanking();                    // Load and return the current ranking
void saveOnRanking(RankingEntry entry);  // Add an entry to the ranking

#endif