#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define HASHTABLESIZE 20000
#define SALT 23
#define MAXLINESIZE 256
#define MAXGENRES 30
#define MOVIES_CSV "movies_proj.csv"
#define RATINGS_CSV "ratings_names.csv"

struct genre {
	char *name;
	struct genre *next;
};

struct review {
	float stars;
	int userid;
	struct review *next;
};

struct movie {
	char *name;
	struct genre *nextGenre;
	struct review *nextReview;
	struct movie *nextMovie;
};

int powmod(int base, int power, int mod)
{
	int i;
	int total = 1;
	for (i=0; i<power; i++) {
		total = (total*base) % mod;
	}
	assert(total >= 0);
	return total;
}


int gns_hash(char *input, int salt)
{
	int i;
	int total;
	int len;
	total = 0;
	len = strlen(input);
	for (i=1; i<len; i++) {
		total += input[i] * i * powmod(salt, i, HASHTABLESIZE);
		if (total < 0) { total*=-1; }
		total %= HASHTABLESIZE;
	}
	assert(total >= 0);
	return total;
}

void scrape_newlines(char *input)
{
	if (!input) { return; }
	int i;
	int len;
	len = strlen(input);
	for (i=0; i<len; i++) {
		if (*(input + i) == 10 || *(input + i) == 13) {
			if (*(input + i + 1) == 0) {
				*(input + i) = 0;
			} else {
				*(input + i) = 32;
			}
		}
	}
	return;
}

void delete_char(char *input, int index)
{
	if (!input) { return; }
	while (*(input + index)) {
		*(input + index) = *(input + index + 1);
		index++;
	}
	return;
}

void remove_quotes(char *input)
{
	if (!input) { return; }
	int i;
	i = 0;
	while (*(input + i)) {
		if (*(input + i) == 34) {
			delete_char(input, i);
			i--;
		}
		i++;
	}
	return;
}

void readin_moviedata(struct movie **buckets, int *collisions)
{
	if (!buckets || !collisions) { return; }
	FILE *fp;
	fp = fopen(MOVIES_CSV, "r");
	char line[MAXLINESIZE];
	fgets(line, MAXLINESIZE, fp);
	while (fgets(line, MAXLINESIZE, fp)) {
		if (*(line + strlen(line) - 1) != 10 &&
		*(line + strlen(line) - 1) != 13) {
			char garbage[1000];
			fgets(garbage, 1000, fp);
			while (*(garbage + strlen(garbage) - 1) != 10 &&
			*(garbage + strlen(garbage) - 1) != 13) {
				fgets(garbage, 1000, fp);
			}
		}
		int i;
		int j;
		char *movie;
		char *commastrs[MAXGENRES];
		char *genrelist;
		char *genre[MAXGENRES];
		i = 1;
		commastrs[0] = strtok(line, ",");
		while (commastrs[0] &&
		(commastrs[i] = strtok(0, ",")) &&
		commastrs[i]) {
			i++;
		}
		if (i > 1) {
			genrelist = commastrs[i-1];
			for (j=1; j<i-1; j++) {
				commastrs[j][-1] = ',';
			}
		}
		movie = commastrs[0];
		scrape_newlines(genrelist);
		remove_quotes(movie);
		i = 1;
		if (genrelist) {
			genre[0] = strtok(genrelist, "|");
			while (i < MAXGENRES && genre[0] &&
			(genre[i] = strtok(0, "|")) && genre[i]) {
				i++;
			}
			genre[i] = 0;
		}

		// assign to structures
		int index;
		struct movie *node;
		struct movie *lastnode;
		index = gns_hash(movie, SALT);
		node = *(buckets + index);
		if (node) {
			while (node) {
				lastnode = node;
				node = node->nextMovie;
			}
			node = calloc(1, sizeof(*node));
			lastnode->nextMovie = node;
			(*collisions)++;
		} else {
			node = calloc(1, sizeof(*node));
			*(buckets + index) = node;
		}

		node->name = calloc(strlen(movie)+1,sizeof(*(node->name)));
		strncpy(node->name, movie, strlen(movie));

		struct genre *tmp;
		if (genre[0]) {
			tmp = node->nextGenre;
			if (tmp) {
				while (tmp) {
					tmp = tmp->next;
				}
				tmp = calloc(1, sizeof(*tmp));
			} else {
				tmp = calloc(1, sizeof(*tmp));
				node->nextGenre = tmp;
			}
			tmp->name = malloc((strlen(genre[0]) + 1)*
				sizeof(*(tmp->name)));
			strncpy(tmp->name, genre[0], strlen(genre[0]));
		}
		i = 1;
		while (i < MAXGENRES && genre[i]) {
			struct genre *newtmp;
			newtmp = calloc(1, sizeof(*newtmp));
			newtmp->name = malloc((strlen(genre[0]) + 1)*
				sizeof(*(newtmp->name)));
			strncpy(newtmp->name, genre[i], strlen(genre[i]));
			tmp->next = newtmp;
			tmp = newtmp;
			i++;
		}
	}
	return;
}

void readin_reviewdata(struct movie **buckets, int *misses)
{
	int i;
	int j;
	FILE *fp;
	fp = fopen(RATINGS_CSV, "r");
	char line[MAXLINESIZE];
	fgets(line, MAXLINESIZE, fp);
	while (fgets(line, MAXLINESIZE, fp)) {
		if (*(line + strlen(line) - 1) != 10 &&
		*(line + strlen(line) - 1) != 13) {
			char garbage[1000];
			fgets(garbage, 1000, fp);
			while (*(garbage + strlen(garbage) - 1) != 10 &&
			*(garbage + strlen(garbage) - 1) != 13) {
				fgets(garbage, 1000, fp);
			}
		}
		int i;
		int j;
		int userid;
		userid = atoi(strtok(line, ","));
		float stars;
		stars = atof(strtok(0, ","));
		char *movie_title;
		movie_title = strtok(0, "\n");
		scrape_newlines(movie_title);
		remove_quotes(movie_title);
		int hash;
		hash = gns_hash(movie_title, SALT);
		struct movie *movie;
		movie = *(buckets + hash);
		struct review *review;
		review = calloc(1, sizeof(*review));
		review->userid = userid;
		review->stars = stars;

		while (movie && strcmp(movie_title, movie->name)) {
			movie = movie->nextMovie;
		}
		if (movie && !strcmp(movie_title, movie->name)) {
			struct review *tmp;
			tmp = movie->nextReview;
			if (!tmp) {
				movie->nextReview = review;
			} else {
				while (tmp->next) {
					tmp = tmp->next;
				}
				tmp->next = review;
			}
		} else {
			(*misses)++;
		}
	}
	return;
}

void free_genres(struct genre *node)
{
	if (!node) { return; }
	if (node->next) {
		free_genres(node->next);
	}
	free(node->name);
	node->name = 0;
	free(node);
	node = 0;
	return;
}

void free_reviews(struct review *node)
{
	if (!node) { return; }
	if (node->next) {
		free_reviews(node->next);
	}
	free(node);
	node = 0;
	return;
}

void free_movies(struct movie *node)
{
	if (!node) { return; }
	if (node->nextGenre) {
		free_genres(node->nextGenre);
	}
	if (node->nextReview) {
		free_reviews(node->nextReview);
	}
	if (node->nextMovie) {
		free_movies(node->nextMovie);
	}
	free(node->name);
	node->name = 0;
	free(node);
	node = 0;
	return;
}

void buckets_destructor(struct movie **buckets)
{
	int i;
	if (!buckets) { return; }
	for (i=0; i<HASHTABLESIZE; i++) {
		if (*(buckets + i)) {
			if ((*(buckets + i))->nextGenre) {
				free_genres((*(buckets + i))->nextGenre);
			}
			if ((*(buckets + i))->nextReview) {
				free_reviews((*(buckets + i))->nextReview);
			}
			if ((*(buckets + i))->nextMovie) {
				free_movies((*(buckets + i))->nextMovie);
			}
			free((*(buckets + i))->name);
			(*(buckets + i))->name = 0;
			free(*(buckets + i));
			*(buckets + i) = 0;
		}
	}
	return;
}

int main()
{
	int i;
	struct movie **buckets;
	buckets = calloc(HASHTABLESIZE, sizeof(*buckets));
	int collisions;
	int misses;

	// read in data and build reviews and genres
	readin_moviedata(buckets, &collisions);
	readin_reviewdata(buckets, &misses);

	char *buffer;
	buffer = malloc(200*sizeof(*buffer));
	while (1) {
		buffer[0] = 0;
		int hash;
		struct movie *cur;
		printf("Type name of movie or 'q' to quit: ");
		fgets(buffer, 100, stdin);
		scrape_newlines(buffer);
		if (buffer[0] == 'q') { break; }
		hash = gns_hash(buffer, SALT);
		cur = *(buckets + hash);
		while (cur && strcmp(buffer, cur->name) && cur->nextMovie) {
			cur = cur->nextMovie;
		}
		if (cur && !strcmp(buffer, cur->name)) {
			struct review *cur_review;
			cur_review = cur->nextReview;
			float review_sum;
			review_sum = 0;
			int review_count;
			review_count = 0;
			printf("Reviews:\n");
			while (cur_review) {
				printf(" %3i: %f\n", cur_review->userid, cur_review->stars);
				review_sum+=cur_review->stars;
				review_count++;
				cur_review = cur_review->next;
			}
			if (review_count) {
				printf("Average Review: %f\n", review_sum/review_count);
			} else {
				printf("No reviews found.\n");
			}
		} else {
			printf("Movie not found.\n");
		}
	}
	free(buffer);
	buffer = 0;

	// go through all movies and free any genres, reviews, and
	//  lastly, the buckets
	buckets_destructor(buckets);
	free(buckets);
	buckets = 0;

	return 0;
}
