#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "trader_functions.h"

//We often need to find the min or max of two values
int max(int a, int b){
    return a>=b ? a:b;
}
int min(int a, int b){
    return a<=b ? a:b;
}

int overcrowded(int move, Location *curr){
    int i = 0;
    if(move>=0){
        for(i = 0; i < move; i++){
            curr = curr->next;
        }
    }else{
        move = -1*move;
        for(i = 0; i < move; i ++){
            curr = curr->previous;
        }
    }
    
    int bot_count = 0;
    //here curr is the location we wanted to sell at
    for(struct bot_list *bots = curr->bots; bots!=NULL; bots=bots->next){
        //look in each bots cargo to see if they have the item 
        int contains = 0; 
        for(struct cargo *cur_bot_cargo = bots->bot->cargo;cur_bot_cargo !=NULL ;cur_bot_cargo = cur_bot_cargo->next){
            if(strcmp(cur_bot_cargo->commodity->name, curr->commodity->name)==0){
                contains = 1;
            }
        }
        if(contains){
            bot_count ++;
        }
    }
    if(curr->quantity <= bot_count){
        return 1;
    }

    return 0;
}

//find the distance between any two locations in the circular map
int distance_search(Location *loc1, Location *loc2){
    Location *forward = loc1;
    Location *backward = loc1;
    int distance_f = 0;
    int distance_b = 0;
    for(;forward!=loc2;forward=forward->next){
        distance_f ++;
    }
    for(;backward!=loc2;backward=backward->previous){
        distance_b ++;
    }
    //returns positive when equal otherwise, the shortest abs distance
    return distance_f<=distance_b ? distance_f:-distance_b;
}

//find whether we need to move towards a fuel station and whre it is relative to us
int fuel_status(int *fuel_distance, Bot *bot){
    Location *forward = bot->location;
    Location *backward = bot->location;
    int distance_f = 0;
    int distance_b = 0;
    //check fuel is still available in the word
    Location *check_world = bot->location;
    int no_fuel_left = 1;
    do{
        if(check_world->type==LOCATION_PETROL_STATION&&check_world->quantity!=0){
            no_fuel_left = 0;
        }
        check_world = check_world->next;
    }while(check_world != bot->location);

    if(no_fuel_left) return 0;

    for(;forward->type!=LOCATION_PETROL_STATION || forward->quantity==0;forward=forward->next){
        distance_f ++;
    }
    for(;backward->type!=LOCATION_PETROL_STATION || backward->quantity==0;backward=backward->previous){
        distance_b ++;
    }


    *fuel_distance = distance_f<=distance_b ? distance_f:-distance_b;
    if(bot->fuel <= 2*bot->maximum_move + abs(*fuel_distance)){
        return 1;
    }
    return 0;
}

