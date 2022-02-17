#include "cachelab.h"
#include <stdio.h>  
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>  
#include <getopt.h>
#include <math.h>

typedef struct 
{
	int valid;
	int tag;
	int recency;
} set;


typedef struct
{
	int s;
	int E;
	int b;
	int set_num;
	int block_size;
	int hits;
	int misses;
	int evicts;
} cache_info;

cache_info init_tracker(int s, int E, int b)
{
	cache_info tracker;
	tracker.s = s;
	tracker.E = E;
	tracker.b = b;
	tracker.set_num = 1 << s; //same as 2^s
	tracker.block_size = 1 << b; //same as 2^b
	tracker.hits = 0;
	tracker.misses = 0;
	tracker.evicts = 0;
	return tracker;
}	

int getIndex(int mem_addr, cache_info tracker)
{
	//Set the middle portion. So have to isolate that through masking. 
	int rem_offset = mem_addr >> tracker.b; //Removes offset which is at beg. 
	int mask = tracker.set_num - 1; 
	int index = rem_offset & mask; //Removes everything but index now at beg. 
	return index;
}

int getTag(int mem_addr, cache_info tracker)
{
	//tag everything leftover. So, mask everything and shift over.
	int offset = tracker.s + tracker.b; 
	int mask = (~0x0) << offset; 
	int isolate = mem_addr&mask;
	int tag = isolate >> offset;
	return tag;
}

//Cycles through the caches sets and lines to set everything to a cold block.
void createEmptyCache(int sets, int lines, set created[sets][lines],cache_info tracker)
{
    int set_index,line_num;
    for(set_index = 0; set_index<sets;set_index++)
    {
    	for(line_num = 0;line_num<lines;line_num++)
    	{
    		created[set_index][line_num].valid = 0;
    		created[set_index][line_num].recency = 0;
    		created[set_index][line_num].tag = 0;
    	}
    }
}

//Looks inside specified set to find if hit,miss, or miss/evict.
cache_info set_look(int add_space, int tag, set* current, cache_info info)
{
	int line;
	int place = 0;
	int least_recent = current[place].recency;
	
	//Search for tag within set and update recency and hit counter if found.
	for(line=0;line<info.E;line++)
	{
		if((current[line].valid == 1) && (current[line].tag == tag))
		{
			current[line].recency=0;
			info.hits += 1;
			//printf("Hit \n");
			return info;
		}
	}

	//If can't find, put in first invalid line and update counters. 
	for(line=0; line<info.E; line++)
	{
		if(current[line].valid == 0)
		{
			current[line].valid =1;
			current[line].tag = tag;
			current[line].recency =0;
			info.misses +=1;
			printf("Miss \n");
			return info;
		}
	}

	//If no where to put it, go through set to find least recently used line.
	for(line=0;line<info.E;line++)
	{
		if(current[line].recency > least_recent)
		{
			least_recent = current[line].recency;
			place = line;
		}
	}

	//After finding place of least recent use, place it there,update counters.
	if(place>=0)
	{
		current[place].tag = tag;
		current[place].recency = 0;
		info.misses += 1;
		info.evicts +=1;
		printf("Miss and Evict\n");
		return info;
	}

	//An extra return info just in case something goes wrong. 	
	return info;
}

int main(int argc, char **argv)
{
	int set_index, line_per_set, block_num;
  	char *file;
  	cache_info tracker;

  	//Largely taken from the example given. 
	int buffer_cmdline; 
    while((buffer_cmdline = getopt(argc, argv, ":if:s:E:b:t:")) != -1)  
    {  
        switch(buffer_cmdline)  
        {  
            case 's':
            	set_index = atoi(optarg); 
            	printf("%d\n",set_index);
            	break; 
            case 'E':  
            	line_per_set = atoi(optarg);
            	printf("%d\n",line_per_set);
            	break;
            case 'b':  
                block_num = atoi(optarg); 
                printf("%d\n",block_num); 
                break;
            case 't':  
            	file = optarg;
                printf("filename: %s\n", file);  
                break;   
        }  
    }

    //Data Structure tracking vitals.
    tracker = init_tracker(set_index,line_per_set,block_num);

    //Creating 2D array cache of format [sets][lines]
    int sets = tracker.set_num;
    int lines = tracker.E;
    set activeCache[sets][lines]; //Have to pass sets& lines to avoid errors.
    createEmptyCache(sets,lines,activeCache,tracker);


    // open file for reading
    FILE *fp = fopen(file, "r");

    // read in each instruction from the file
    char buffer[BUFSIZ];
    while (!feof(fp) && (fgets(buffer,500,fp) != NULL))
	{
		char *mem_access_type;
		char *temp_s;
		int add_space, i;

		mem_access_type = strtok(buffer," ,\n");

		temp_s = strtok(NULL," ,\n");
		add_space = strtol(temp_s,NULL,16); //Converts *char to long int
		//No point in collecting size. 

		int set = getIndex(add_space,tracker); //Returns set.
		int tag = getTag(add_space,tracker);//Returns tag. 

		//'L': load. 'S': store. 'M': modify.
		if(*mem_access_type == 'L') 
		{
			tracker = set_look(add_space, tag, activeCache[set],tracker);
		}
		if(*mem_access_type == 'S')
		{
			tracker = set_look(add_space, tag, activeCache[set],tracker);
		}
		if(*mem_access_type == 'M') //Modify is instr. twice loaded
		{
			tracker = set_look(add_space, tag, activeCache[set],tracker);
			tracker = set_look(add_space, tag, activeCache[set],tracker);
		}

		//Updates use counter for all the lines in that set. 
		for(i=0; i<tracker.E; i++)
		{
				activeCache[set][i].recency++;
		}
	}

	//Prints summary. 
	printSummary(tracker.hits, tracker.misses, tracker.evicts);
    return 0;
}

