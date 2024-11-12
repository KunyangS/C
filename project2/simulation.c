// Student Name: Kunyang Xie    Student Number: 24447687
// Student Name: Erqian Chen    Student Number: 23421379



#include <stdio.h>
#include <stdlib.h>

// Definitions and structure declarations
#define NUM_PROCESSES 4 // There are 4 processes at the system
#define PAGES_PER_PROCESS 4 // Every process has 4 pages
#define RAM_SIZE 16 // The size of RAM
#define VRMEMORY_SIZE 32 // The size of viritual memory
#define ON_DISK 99 // When the page is on disk and is not in RAM, the constant value is 99


// There are three attributes in a memory page, they are process id, page number, and last accessed time
struct memory {
    int process_id;
    int page_num;
    int last_accessed;
};

// Array of pointers, used to simulate virtual memory, and the number of pages that can be stored in virtual memory is VRMEMORY_SIZE
struct memory *vrmemory[VRMEMORY_SIZE]; 

// Array of pointers, used to simulate RAM, RAM_SIZE is similar to VRMEMORY_SIZE but works for RAM
struct memory *ram[RAM_SIZE];

// 2D array, page_table is used to track where are process's pages
int page_table[NUM_PROCESSES][PAGES_PER_PROCESS];

// The one-dimensional array, which works to record the page number currently being accessed by each process
int process_current_page[NUM_PROCESSES] = {0, 0, 0, 0};


// Function works for initializing vrmemory, and allocate memory for each process's pages.
void initial_vrmemory() {
    int index = 0;
    for (int process_id = 0; process_id < NUM_PROCESSES; process_id++) { // Loop each process, starting from 0 and going to the number of processes in the system NUM_PROCESSES
        for (int page_num = 0; page_num < PAGES_PER_PROCESS; page_num++) { // Loop the pages of each process, starting from 0 and reaching the number of pages of the process PAGES_PER_PROCESS.
            vrmemory[index] = malloc(sizeof(struct memory));
            vrmemory[index]->process_id = process_id;
            vrmemory[index]->page_num = page_num;
            vrmemory[index]->last_accessed = 0;

            vrmemory[index + 1] = malloc(sizeof(struct memory));
            vrmemory[index + 1]->process_id = process_id;
            vrmemory[index + 1]->page_num = page_num;
            vrmemory[index + 1]->last_accessed = 0;

            page_table[process_id][page_num] = ON_DISK;
            index += 2;
        }
    }
}


/*
Function works to initialize RAM
Allocate memory for each page box, and mark each page box as unused which are presented by setting process_id, page_num, and last_accessed to -1
*/
void initial_ram() {
    for (int i = 0; i < RAM_SIZE; i++) {
        ram[i] = malloc(sizeof(struct memory));
        ram[i]->process_id = -1;
        ram[i]->page_num = -1;
        ram[i]->last_accessed = -1;
    }
}

/*
Using LRU to determine the page to be replaced
When RAM is full or space needs to be freed, find the page that has not been accessed for the longest time, move it out of RAM, and update the relevant page information to on disk
*/
int evict_page(int process_id) {
    int lru_index = -1;
    int lru_time = -1;
    for (int i = 0; i < RAM_SIZE; i += 2) { // Loop pages in RAM
        if (ram[i]->process_id == process_id) {
            if (lru_index == -1 || ram[i]->last_accessed < lru_time) {
                lru_index = i;
                lru_time = ram[i]->last_accessed;
            }
        }
    }
    if (lru_index == -1) { // Execute this step, if cannot find out process_id page at the last loop
        for (int i = 0; i < RAM_SIZE; i += 2) {
            if (lru_index == -1 || ram[i]->last_accessed < lru_time) {
                lru_index = i;
                lru_time = ram[i]->last_accessed;
            }
        }
    }

    if (lru_index != -1) { // Execute this step, if lru_index != -1 (means if successfully found out pages at the last step)
        page_table[ram[lru_index]->process_id][ram[lru_index]->page_num] = ON_DISK;
        ram[lru_index]->process_id = -1;
        ram[lru_index]->page_num = -1;
        ram[lru_index]->last_accessed = -1;

        ram[lru_index + 1]->process_id = -1;
        ram[lru_index + 1]->page_num = -1;
        ram[lru_index + 1]->last_accessed = -1;
    }
    return lru_index;
}

/*
Function works for loading a page from virtual memory into RAM 
If there is no free space in RAM, it will make space through page replacement, then load the page into it.
*/
void page_ram(int process_id, int time_step) {
    int page_num = process_current_page[process_id];
    int vrindex = process_id * 2 * PAGES_PER_PROCESS + page_num * 2;

    struct memory* vm1 = vrmemory[vrindex];
    struct memory* vm2 = vrmemory[vrindex + 1];
    vm1->last_accessed = time_step;
    vm2->last_accessed = time_step;

    for (int i = 0; i < RAM_SIZE; i += 2) { // Check if there is any free space at RAM
        if (ram[i]->last_accessed == -1) {
            ram[i]->process_id = vm1->process_id;
            ram[i]->page_num = vm1->page_num;
            ram[i]->last_accessed = time_step;

            ram[i + 1]->process_id = vm2->process_id;
            ram[i + 1]->page_num = vm2->page_num;
            ram[i + 1]->last_accessed = time_step;

            page_table[process_id][page_num] = i / 2;
            printf("process %d page %d move to RAM at time %d\n", process_id, page_num, time_step);
            process_current_page[process_id]++;
            process_current_page[process_id] =  process_current_page[process_id] % 4;
            return;
        }
    }

    int ram_free_index = evict_page(process_id);
    ram[ram_free_index]->process_id = vm1->process_id;
    ram[ram_free_index]->page_num = vm1->page_num;
    ram[ram_free_index]->last_accessed = time_step;

    ram[ram_free_index + 1]->process_id = vm2->process_id;
    ram[ram_free_index + 1]->page_num = vm2->page_num;
    ram[ram_free_index + 1]->last_accessed = time_step;

    page_table[process_id][page_num] = ram_free_index / 2;
    printf("process %d page %d move to RAM at time %d after eviction\n", process_id, page_num, time_step);
    process_current_page[process_id]++;
    process_current_page[process_id] =  process_current_page[process_id] % 4;
}


// Main function works for initializing virtual memory and RAM, reading process requests in input files, performing paging, and also outputting results to specified files.
int main(int argc, char* argv[]) {
    if (argc != 3) { // Check if it is 3 files
        printf("Usage: %s in.txt out.txt\n", argv[0]);
        return 1;
    }

    // Initialize virtual memory and RAM
    initial_vrmemory();
    initial_ram();

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }

    int process_id;
    int time_step = 0;
    while (fscanf(input_file, "%d", &process_id) == 1) {
        page_ram(process_id, time_step);
        time_step++;
    }
    fclose(input_file);

    FILE *output_file = fopen(argv[2], "w");
    if (!output_file) {
        printf("Error: Unable to open output file.\n");
        return 1;
    }

    // Loop page_table of each process and output to a file.
    for (int i = 0; i < NUM_PROCESSES; i++) { 
        for (int j = 0; j < PAGES_PER_PROCESS; j++) {
            fprintf(output_file, "%d", page_table[i][j]);
            if (j < PAGES_PER_PROCESS - 1) {
                fprintf(output_file, ", ");
            }
        }
        fprintf(output_file, "\n");
    }

    // Loop each page box in RAM and output its process_id, page_num, and last_accessed to a file.
    for (int i = 0; i < RAM_SIZE; i++) {
        fprintf(output_file, "%d,%d,%d", ram[i]->process_id, ram[i]->page_num, ram[i]->last_accessed);
        if (i < RAM_SIZE - 1) {
            fprintf(output_file, "; ");
        }
    }
    fprintf(output_file, "\n");

    fclose(output_file);

    // Loop virtual memory vrmemory and RAM and release dynamically allocated memory one by one
    for (int i = 0; i < VRMEMORY_SIZE; i++) {
        free(vrmemory[i]);
    }

    for (int i = 0; i < RAM_SIZE; i++) {
        free(ram[i]);
    }

    return 0;
}
