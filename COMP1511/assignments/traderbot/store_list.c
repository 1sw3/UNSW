#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trader_bot.h"
#include "trader_functions.h"

//adds a store to the appropriate buyer or seller list
Store *add_store(Store *node, Store *head){
    node->next = head;
    return node;
}

void create_store(Store *seller_list, Store *buyer_list, Location *loc){
    if(loc->type == LOCATION_BUYER){
        buyer_list->name = loc->name;
        buyer_list->price = loc->price;
        buyer_list->amount = loc->quantity;
        buyer_list->next = NULL;
    }
    if(loc->type == LOCATION_SELLER){
        seller_list->name = loc->name;
        seller_list->price = loc->price;
        seller_list->amount = loc->quantity;
        seller_list->next = NULL;
    }
}


//prints a custom Store linked list
void print_store_locations(Store *location_list){
    while(location_list!=NULL){
        printf("\t name: %s", location_list->name);
        printf("\t distance: %d", location_list->distance);
        printf("\t price: %d", location_list->price);
        printf("\t amount: %d", location_list->amount);
        printf("\t preference: %.0lf\n", location_list->store_preference);
        location_list=location_list->next;
    }
}
