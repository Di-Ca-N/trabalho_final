/******************************************************
 * ranking module
 * Ranking records management
 ******************************************************/
#ifndef RANKING_H
#define RANKING_H

// ==== CONSTANTS ====
#define MAX_USERNAME_LENGTH 15 // Maximum allowed username length on ranking
#define RANKING_ENTRIES 5

// ==== TYPES ====

// Represent a single entry on the ranking
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    int score;
} RankingEntry;

// Represent the ranking itself
typedef struct {
    RankingEntry entries[RANKING_ENTRIES];
} Ranking;

// ==== FUNCTIONS ====

Ranking getRanking();                    // Return the current ranking
void saveOnRanking(RankingEntry entry);  // Add an entry to the ranking

#endif