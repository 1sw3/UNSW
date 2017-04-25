#include <stdio.h>
#include <stdlib.h>
#include "captcha.h"

int main(int argc, char *argv[]) {

    //read the digit, get it's bounding box and get its balance

    int height, width, start_row, start_column, box_width, box_height, holes;
    double h_balance, v_balance, density;
    double quadrant_densities[4];
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }
    if (get_pbm_dimensions(argv[1], &height, &width) != 1) {
        return 1;
    }

    //reads the pbm into the array pixels
    int pixels[height][width];

    //get all the attributes of the digit inside this function
    if (read_pbm(argv[1], height, width, pixels)) {
        
        //gets the bounding box around the pixel
        get_bounding_box(height, width, pixels, &start_row, &start_column,
                &box_height, &box_width);

        //puts the bounded pixel in box_pixels 
        int box_pixels[box_height][box_width];

        copy_pixels(height, width, pixels, start_row, start_column, box_height,
                box_width, box_pixels);
        
        get_attributes(height, width, pixels, start_row,
                start_column, box_height, box_width,
                box_pixels, &h_balance, &v_balance,
                &density, &holes, quadrant_densities);
    

        //get scores based on templating
        double match_score[DIGITS][TESTS];
        get_scores(box_height, box_width, box_pixels, match_score);
        double total_score[DIGITS] = {0};
        for(int digit = 0; digit < DIGITS; digit ++){
            for(int version = 0; version < TESTS; version ++){
                total_score[digit] += match_score[digit][version];
            }
        }
        
        //using the scores, get the best digit
        int best_digit = 0;
        int max_score = 0;
        for(int i = 0; i<DIGITS; i++){
            if(total_score[i] > max_score){
                best_digit = i;
                max_score = total_score[i];
            }
        }  
        printf("%d\n", best_digit);
    }
    return 0;
}
