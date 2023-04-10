#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10// maximum size of the queues

// structure for a query
struct Query {
    int id; 
    int time_left; 
};


struct Query init_query(int id) {
    struct Query q;
    q.id = id;
    q.time_left = 10; // fixed time slot of 10 minutes
    return q;
}

//check if a queue is empty
bool is_empty(struct Query* queue, int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (queue[i].id != 0) {
            return false;
        }
    }
    return true;
}

//add a query to the back of a queue
void enqueue(struct Query* queue, int size, struct Query q) {
    int i;
    for (i = 0; i < size; i++) {
        if (queue[i].id == 0) {
            queue[i] = q;
            return;
        }
    }
    printf("Queue is full!\n");
}

//remove the front query from a queue
struct Query dequeue(struct Query* queue, int size) {
    if (is_empty(queue, size)) {
        printf("Queue is empty!\n");
        return init_query(0);
    }
    struct Query q = queue[0];
    int i;
    for (i = 0; i < size - 1; i++) {
        queue[i] = queue[i+1];
    }
    queue[size-1] = init_query(0);
    return q;
}

int main() {
    struct Query student_queue[MAX_SIZE]; // declare student queue
    struct Query faculty_queue[MAX_SIZE]; // declare faculty queue
    
    // add 2 queries to the queues other request can be added here
    enqueue(student_queue, MAX_SIZE, init_query(1));
    enqueue(faculty_queue, MAX_SIZE, init_query(2));


    
    // start the session from 10am to 12am
    int total_time = 0;
    int time;
    for (time = 10; time <= 12; time++) {
        printf("Time: %d:00\n", time);
        
        // handle student queries
        if (!is_empty(student_queue, MAX_SIZE)) {
            printf("Handling student query %d\n", student_queue[0].id);
            student_queue[0].time_left--;
            if (student_queue[0].time_left == 0) {
                printf("Student query %d resolved\n", student_queue[0].id);
                dequeue(student_queue, MAX_SIZE);
            } else {
                printf("Student query %d needs more time, moving to the back of the queue\n", student_queue[0].id);
                enqueue(student_queue, MAX_SIZE, dequeue(student_queue, MAX_SIZE));
            }
            total_time++;
        }
        
        // handle faculty queries
        if (!is_empty(faculty_queue, MAX_SIZE)) {
            printf("Handling faculty query %d\n", faculty_queue[0].id);
            faculty_queue[0].time_left--;
            if (faculty_queue[0].time_left == 0) {
                printf("Faculty query %d resolved\n", faculty_queue[0].id);
                dequeue(faculty_queue, MAX_SIZE);
            } else {
                printf("Faculty query %d needs more time, moving to the back of the queue\n", faculty_queue[0].id);
                enqueue(faculty_queue, MAX_SIZE, dequeue(faculty_queue, MAX_SIZE));
            }
            total_time++;
        }
    }
    
    // calculate total time spent on handling queries and average query time
    int num_queries = MAX_SIZE * 2; // total number of queries
    float avg_time = (float) total_time / num_queries;
    printf("Total time spent on handling queries: %d minutes\n", total_time);
    printf("Average query time: %.2f minutes\n", avg_time);
    
    return 0;
}
