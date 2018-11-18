// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Implementing Traveling Salesman Problem using Branch and Bound

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../utils/constant.h"
#include "../utils/utility.h"

#define inf 2147483647

int cost = 0;

//int matrix[100][100], visited[100], number_of_cities, cost = 0;
int display_cost_matrix(int **array, int no_of_elements) {
    // display given array of given size(no. of elements require because sizeof() returns max bound value)
    write_log(": ");
    for (int i = 0; i < no_of_elements; i++) {
        printf("City-%d >>: ", i);
        for (int j = 0; j < no_of_elements; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int get_nearest_city(int c, int **cost_matrix, int *visited_status, int number_of_cities) {
    int nearest_neighbour_city = inf;
    int min = inf, temp;
    for (int i = 0; i < number_of_cities; i++) {
        if ((cost_matrix[c][i] != 0) && (visited_status[i] == 0)) {
            if (cost_matrix[c][i] < min) {
                min = cost_matrix[i][0] + cost_matrix[c][i];
            }
            temp = cost_matrix[c][i];
            nearest_neighbour_city = i;
        }
    }
    if (min != inf)
        cost += temp;
    return nearest_neighbour_city;
}

int min_cost_calc(int city, int **cities, int *visited_cities, int number_of_cities) {
    int i, nearest_neighbour_city;
    visited_cities[city] = 1;
    printf("%d ===> ", city + 1);
    nearest_neighbour_city = get_nearest_city(city, cities, visited_cities, number_of_cities);

    if (nearest_neighbour_city == inf) {
        nearest_neighbour_city = 0;
        printf("%d", nearest_neighbour_city + 1);
        cost += cities[city][nearest_neighbour_city];
        return 1;
    }
    return min_cost_calc(nearest_neighbour_city, cities, visited_cities, number_of_cities);
}

int main() {
    int number_of_cities;
    printf("\nEnter Number of Cities: \n");
    scanf("%d", &number_of_cities);
    int **cities = malloc(number_of_cities * sizeof(int *));
    int *visited_cities = malloc(number_of_cities * sizeof(int *));
    for (int i = 0; i < number_of_cities; i++) {
        cities[i] = malloc(number_of_cities * sizeof(int));
    }


    printf("\nEnter Cost Matrix for travelling through %d cities: \n", number_of_cities);
    for (int i = 0; i < number_of_cities; i++) {
//        printf("\n Enter cost from city 1# : %d\n", i + 1);
        for (int j = 0; j < number_of_cities; j++)
            if (i == j) {
//                cities[i][j] = inf;
                cities[i][j] = 0;
            } else {
                cities[i][j] = 1 + rand() % 9;
            }
//            scanf("%d", &cities[i][j]);
        visited_cities[i] = 0;
    }

    printf("\nThe Cost Matrix is:\n");
    display_cost_matrix(cities, number_of_cities);

    printf("\nThe Path is:\n");
    min_cost_calc(0, cities, visited_cities, number_of_cities);
    printf("\nMinimum Cost of tour: -> %d", cost);
    return 1;
}
