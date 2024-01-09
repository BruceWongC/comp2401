#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARR 5000

/*  Function: take_photo()
    Description: Simulates taking a photo as a black-and-white image represented by
                 an array of characters '1' and '0'. The photo is stored in the out[] array.

    Output: out[]   - an array of characters to store the photo data, as a string of 1 and 0 characters
    Output: rows    - an address to an integer to store the number of rows in the photo
    Output: cols    - an address to an integer to store the number of columns in the photo

    Returns: the total number of characters in the photo data OR 0 if no photo was taken
    
*/
int take_photo(unsigned char out[], int* rows, int* cols);

unsigned char get_bit(unsigned char byte, int bit);
unsigned char set_bit(unsigned char byte, int bit);
unsigned char clear_bit(unsigned char byte, int bit);
void print_raw(unsigned char raw_string[], int rows, int cols);
int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]);
void print_packed(unsigned char packed[], int rows, int cols);
int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[]);
void print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols);

int main() {
    unsigned char output[MAX_ARR]; 
    unsigned char bitsPacked[MAX_ARR];
    unsigned char bitsEncoded[MAX_ARR];
    int row = 0;
    int col = 0;
    int size = 0;

    size = take_photo(output, &row, &col);

    while (size != 0){
        printf("Raw photo (%i bytes):\n", size);//need to be fixed, maybe before

        print_raw(output, row, col);
        printf("\n");

        size = pack_bits(output, size, bitsPacked);

        printf("Packed photo (%i bytes):\n", size);

        print_packed(bitsPacked, row, col);
        printf("\n");

        size = encode_bits(bitsPacked, size, bitsEncoded);

        printf("Encoded photo (%i bytes):\n", size);

        print_encoded(bitsEncoded, size, row, col);
        printf("\n");

        size = take_photo(output, &row, &col);

    }

    return 0;
}

void print_raw(unsigned char raw_string[], int rows, int cols) {
    int count = 0;
    for(int i = 0; i < rows; i++){//rows printed
        for(int j = 0; j < cols; j++){//cols printed
            if (raw_string[count] == 48){
                printf(".");
            }
            else{
                printf("*");
            }
            count++;
        }
        printf("\n");

    }

}

void print_packed(unsigned char packed[], int rows, int cols){
    unsigned char chr = 0, byte = 0;
    int index = 0, count = 7;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            byte = packed[index];//get next byte
            chr = get_bit(byte,count);//get the bit

            if(chr == 0){//if 0 or 1 print '.' or '*'
                printf(".");
            }
            else{
                printf("*");
            }

            count--;

            if(count < 0){//go through byte then go to next index
                index++;
                count = 7;
            }

        }

        printf("\n");

    }

}

void print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols){
    int count = 0;
    for(int i = 0; i < encoded_size; i++){
        for(int j = 0; j < encoded[i]; j++){
            if(i % 2 == 0){//print if 0 or 1
                printf("*");
            }
            else{
                printf(".");
            }
            count++;
            if(count == cols){//counter reaches col, go to next line
                printf("\n");
                count = 0;
            }

        }
    }
}




unsigned char get_bit(unsigned char byte, int bit) {
    return (byte >> bit) & 1;
}

unsigned char set_bit(unsigned char byte, int bit) {
    return byte | (1 << bit);
}

unsigned char clear_bit(unsigned char byte, int bit) {
    return byte & ~(1 << bit);
}

int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]){
    unsigned char cur = 00000000;
    int size = 0;

    for(int i = 0; i < num_chars; i++){
        if(unpacked_string[i] == 49){ //it's reading from 2^7 to 2^0, ask if opposite
            cur = set_bit(cur, 7 - (i % 8));
        }

        if ((i + 1) % 8 == 0){//add byte to array after operations 
            packed_result[size] = cur;
            size++;
            cur = 00000000;
        }
    }

    return size;
}

int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[]){
    int count = 0, index = 0;
    for (int i = 0; i < packed_size; i++){
        for (int j = 7; j >= 0; j--){
            if(index % 2 == 0){ // even index are ones, odds are zero
                if(get_bit(packed[i], j) == 0){
                    encoded_result[index] = count;
                    index++;
                    count = 0;
                }
            }

            else{
                if(get_bit(packed[i], j) == 1){
                    encoded_result[index] = count;
                    index++;
                    count = 0;
                }
            }

            count++;


        }
        if((i + 1) == packed_size){
            encoded_result[index] = count;
        }


    }


    return (index + 1);
}