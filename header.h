#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define ALPHABET_SIZE 26
#define BUSINESS_NUMBER 0
#define WORLD_NUMBER 1
#define SCITECH_NUMBER 2
#define HEALTH_NUMBER 3
#define ENTERTAINMENT_NUMBER 4
#define US_NUMBER 5
#define SPORT_NUMBER 6
#define FINAL_NUMBER 1450
#define TOTAL_WORDS 90000

typedef struct Words{
    char name[100];
    int cat;
    double val;
    bool flag;
    int occurrence;
}words;
words word[TOTAL_WORDS];
//
typedef struct News {
    struct News *children[ALPHABET_SIZE];
    bool isLeaf;
    int occurrence;
}news;
//
struct NewsData
{
    char title[500];
    char description[3000];
    char pubDate[100];
};

int process(int *occurrence,news **Category_Root,news **News_Root,int *Category_Number);
void vectorBuilder (news *news_root,int *Category_Number,double **Category_Weight,double **weight,int num,int News_Number,int Final_Number,bool uncategorized);
double dot(double **uncategorizedNews_Weight,double **Category_Weight,int News_Index,int Category_Index,int Final_Number);
void writeProcessedDataInFile(char *description,char *title,char *pubDate);
int readUncategorizedNews(news **Uncategorized_Root);
void dateAnalyse(char *pubDate);
int preProcess(news **Category_Root,news **News_Root,int *Category_Number);
news *getNode();
void insert(news *root,char *key);
int search(news *root,char *key);
int iterateTrie(news **Category_Root,news *root,int *occurrence,char *buffer,int k,int num);
void splitFunc(news *root,news *news_root,char *description,char *title);
int cmp(const void *a, const void *b);
char* titleAnalyse(char *title);
char* categoryAnalyse(char *category);
char* descriptionAnalyse(char *description);
void jsonMaker(int *Category_Number);
void getRSS();
void getURLS();

#endif // _HEADER_H_
