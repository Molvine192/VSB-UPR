#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>

void normalize_string(char *str);

typedef unsigned char byte;

typedef struct 
{
    byte id_length;
    byte color_map_type;
    byte image_type;
    byte color_map[5];
    byte x_origin[2];
    byte y_origin[2];
    byte width[2];
    byte height[2];
    byte depth;
    byte descriptor;
} TGAHeader;

int header_width(TGAHeader * self)
{
    int width = 0;

    memcpy(&width, self->width, 2);

    return width;
}

int header_height(TGAHeader * self)
{
    int height = 0;

    memcpy(&height, self->height, 2);

    return height;
}

typedef struct {
    byte blue;
    byte green;
    byte red;
} Pixel;

Pixel* load_pixels(TGAHeader header, FILE* file) {
    int width = 0;
    int height = 0;
    
    memcpy(&width, header.width, 2);
    memcpy(&height, header.height, 2);

    Pixel* pixels = (Pixel*) malloc(sizeof(Pixel) * width * height);
    fread(pixels, sizeof(Pixel) * width * height, 1, file);

    return pixels;
}

void write_pixels( TGAHeader header, Pixel * pixels, char * filename)
{
    int width = header_width(&header);
    int height = header_height(&header);

    FILE* file_out  = fopen(filename, "wb");
    assert(fwrite(&header, sizeof(TGAHeader), 1, file_out) == 1);
    assert(fwrite(pixels, sizeof(Pixel) * width * height, 1, file_out) == 1);

    fclose(file_out);
}

int main(int argc, char ** argv)
{
    if (argc < 4) {
        printf("Wrong parameters\n");
        return 1;
    }

    char* input_file_path = argv[1];
    char* output_file_path = argv[2];
    char* font_path = argv[3];

    FILE* input_file = fopen(input_file_path, "rb");
    if (!input_file) {
        printf("Could not load image\n");
        return 1;
    }

    FILE** letters = (FILE**) malloc(sizeof(FILE*) * 26);
    TGAHeader* letter_headers = (TGAHeader*) malloc(sizeof(TGAHeader) * 26);
    Pixel** letter_pixels = (Pixel**) malloc(sizeof(Pixel*) * 26);
    for (int i = 0; i < 26; i++) {
        char str[20];
        sprintf(str, "%s/%c.tga", font_path, i+65);
        letters[i] = fopen(str, "rb");
        fread(&letter_headers[i], sizeof(TGAHeader), 1, letters[i]);
        letter_pixels[i] = load_pixels(letter_headers[i], letters[i]);
    }
    
    TGAHeader header = {};
    fread(&header, sizeof(TGAHeader), 1, input_file);

    int width = header_width(&header);
    int height = header_height(&header);

    Pixel* pixels = load_pixels(header, input_file);

    int top, bottom;
    char buf[10];
    fgets(buf, sizeof(buf), stdin);
    top = atoi(buf);
    bottom = atoi(buf+1);
    char* strings_top = (char*) malloc(sizeof(char) * 101 * top);
    char* strings_bottom = (char*) malloc(sizeof(char) * 101 * bottom);

    for (int i = 0; i < top; i++) {
        fgets(strings_top+i*101, sizeof(char)*100, stdin);
        normalize_string(strings_top+i*101);
    }
    for (int i = 0; i < bottom; i++) {
        fgets(strings_bottom+i*101, sizeof(char)*100, stdin);
        normalize_string(strings_bottom+i*101);
    }

    for (int i = 0; i < (top + bottom); i++) {
        int str_width = 0;
        char* text;
        if (i < top) {
            text = strings_top+i*101;
        }
        else {
            text = strings_bottom+(i-top)*101;
        }
        
        for (int k = 0; text[k] != '\0'; ++k) {
            text[k] = toupper(text[k]);
        }

        for (size_t k = 0; k < strlen(text); k++) {
            if (text[k] != ' ') {
                str_width += header_width(&letter_headers[text[k]-65]);
            }
            else {
                str_width += 8;
            }
            str_width++;
        }

        int x = (width - str_width)/2, y = 10+36*i;
        if (i >= top) {
            y = height - 10 - 36*(bottom-(i-top));
        }
        int letter_color_index = 0;
        for (int k = 0; text[k] != '\0'; ++k) {
            int letter_width = 0;
            if (text[k] != ' ') {
                letter_width = header_width(&letter_headers[text[k]-65]);
                int letter_height = header_height(&letter_headers[text[k]-65]);

                for (int row = 0; row < letter_height; row++) {
                    for (int col = 0; col < letter_width; col++) {
                        int target_index = (y + row) * width + (x + col);
                        int letter_index = row * letter_width + col;

                        if (target_index < width * height && letter_index < letter_width * letter_height) {
                            Pixel* letter_pixel = letter_pixels[text[k]-65] + letter_index;
                            Pixel* pixel = pixels + target_index;

                            if (letter_pixel->green != 0 && letter_pixel->red != 0 && letter_pixel->blue != 0) {
                                if (letter_pixel->green > 100 && letter_pixel->red > 100 && letter_pixel->blue > 100) {
                                    if ((letter_color_index+6) % 6 == 0) {
                                        pixel->red = 255;
                                        pixel->green = 160;
                                        pixel->blue = 246;
                                    }
                                    else if ((letter_color_index+6) % 6 == 1) {
                                        pixel->red = 255;
                                        pixel->green = 202;
                                        pixel->blue = 250;
                                    }
                                    else if ((letter_color_index+6) % 6 == 2) {
                                        pixel->red = 255;
                                        pixel->green = 225;
                                        pixel->blue = 252;
                                    }
                                    else if ((letter_color_index+6) % 6 == 3) {
                                        pixel->red = 255;
                                        pixel->green = 236;
                                        pixel->blue = 253;
                                    }
                                    else if ((letter_color_index+6) % 6 == 4) {
                                        pixel->red = 255;
                                        pixel->green = 225;
                                        pixel->blue = 252;
                                    }
                                    else if ((letter_color_index+6) % 6 == 5) {
                                        pixel->red = 255;
                                        pixel->green = 202;
                                        pixel->blue = 250;
                                    }
                                }
                                else {
                                    pixel->red = letter_pixel->red;
                                    pixel->green = letter_pixel->green;
                                    pixel->blue = letter_pixel->blue;
                                }
                            }
                        }
                    }    
                }
                letter_color_index++;
            }
            else {
                letter_width = 8;
            }


            x = x + letter_width + 1;

        }
    }

    write_pixels( header, pixels, output_file_path);
    fclose(input_file);
    for (int i = 0; i < 26; i++) {
        fclose(letters[i]);
    }
    free(pixels);
    free(strings_top);
    free(strings_bottom);
    free(letters);
    free(letter_headers);
    for (int i = 0; i < 26; i++) {
        if (letter_pixels[i] != NULL) {
            free(letter_pixels[i]);
        }
    }
    free(letter_pixels);
    return 0;
}

void normalize_string(char *str) {
    size_t index = 0;
    for (size_t i = 0; i < strlen(str); i++) {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == ' ') {
            str[index++] = str[i];
        }
    }
    str[index] = '\0';
}