#include <iostream>
#include <fstream>
#include <string>
#include "image.h"

struct Input {
    int length;
    int width;
    std::string input;
    std::string output;
    int max_iter;
    int freq;
};

void CreateImage(int& new_size_x, int& new_size_y, int** sandbox[[]], int& number_file_counter);
//void СompletionOfMassive(int** old[[]],int** recent[[]],int start_x,int start_y,int end_x,int end_y);

int main(int argc, char **argv) {
    Input table;
    for (int i = 0; i < argc; ++i) {
        std::string s = argv[i];
        if (s == "-l" || s == "--length") {
            table.length = atoi(argv[i + 1]);
        } else if (s == "-w" || s == "--width") {
            table.width = atoi(argv[i + 1]);
        } else if (s == "-i" || s == "--input") {
            table.input = argv[i + 1];
        } else if (s == "-o" || s == "--output") {
            table.output = argv[i + 1];
        } else if (s == "-m" || s == "--max-iters") {
            table.max_iter = atoi(argv[i + 1]);
        } else if (s == "-f" || s == "--freq") {
            table.freq = atoi(argv[i + 1]);
        }


    }
    //table={3,3,"input.txt","image.bmp",700,0};
    int **sandbox = (int **) malloc(sizeof(int *) * table.length);
    for (int i = 0; i < table.length; i++) {
        sandbox[i] = (int *) malloc(sizeof(int) * table.width);
    }
    std::string s;

    std::ifstream in(table.input);
    unsigned long long i = 0;
    unsigned long long j = 0;

    while (in >> s) {
        if (s != " ") {
            if (j > table.width - 1) {
                i++;
                j = 0;
                sandbox[i][j] = stoi(s);

                j++;

            } else {
                sandbox[i][j] = stoi(s);

                j++;
            }

        }
    }

    bool fl = true;
    bool fl1 = false;
    long long iteration_count = 0;
    int count = 0;
    bool count1 = false;
    if (table.freq == 0) {
        count1 = true;
    }

    int new_size_x = table.length;
    int new_size_y = table.width;
    int a[4] = {0, 0, 0, 0};
    //high,down,left,right changes
    int number_file_counter = 0;

    while (fl) {

        for (int y = 0; y < new_size_y; y += new_size_y - 1) {
            for (int x = 0; x < new_size_x; x++) {
                if (sandbox[y][x] > 3) {
                    if (y == 0) {
                        a[2] = 1;
                        break;
                    } else if (y == new_size_y - 1) {
                        a[3] = 1;
                        break;
                    }

                }
            }
        }
        for (int x = 0; x < new_size_x; x += new_size_x - 1) {
            for (int y = 0; y < new_size_y; y++) {
                if (sandbox[y][x] > 3) {
                    if (x == 0) {
                        a[0] = 1;
                        break;
                    } else if (x == new_size_x - 1) {
                        a[1] = 1;
                        break;
                    }

                }
            }
        }

        new_size_x += a[0] + a[1];
        new_size_y += a[2] + a[3];

        int **sandbox1 = (int **) malloc(sizeof(int *) * new_size_x);
        for (int i = 0; i < new_size_y; i++) {
            sandbox1[i] = (int *) malloc(sizeof(int) * new_size_y);
        }
        int start_x = 0;
        int start_y = 0;
        int end_x = new_size_x;
        int end_y = new_size_y;
        if (a[0]) {
            for (int y = 0; y < new_size_y; ++y) {
                sandbox1[0][y] = 0;
            }
            start_x++;
        }
        if (a[1]) {
            for (int y = 0; y < new_size_y; ++y) {
                sandbox1[new_size_x - 1][y] = 0;
            }
            end_x--;
        }
        if (a[2]) {
            for (int x = 0; x < new_size_x; ++x) {
                sandbox1[x][0] = 0;
            }
            start_y++;
        }
        if (a[3]) {
            for (int x = 0; x < new_size_x; ++x) {
                sandbox1[x][new_size_y - 1] = 0;
            }
            end_y--;
        }

        //СompletionOfMassive(sandbox,sandbox1,start_x,start_y,end_x,end_y);

        int old_x = 0;
        int old_y = 0;
        int const s_y = start_y;
        for (; start_x < end_x; ++start_x, old_x++) {

            for (; start_y < end_y; ++start_y, old_y++) {
                sandbox1[start_x][start_y] = sandbox[old_x][old_y];

            }
            start_y = s_y;
            old_y = 0;

        }
        //std::cout<<start_x<<' '<<end_x<<' '<<start_y<<' '<<end_y<<'\n';
        a[0] = 0;
        a[1] = 0;
        a[2] = 0;
        a[3] = 0;


        free(sandbox);
        sandbox = sandbox1;


        for (int i = 0; i < new_size_x; ++i) {
            for (int j = 0; j < new_size_y; ++j) {

                if (sandbox[i][j] > 3) {
                    sandbox[i][j] -= 4;
                    if (i - 1 > -1) {
                        sandbox[i - 1][j] += 1;
                        if (sandbox[i - 1][j] > 3) {
                            fl1 = true;
                        }
                    } else {
                        sandbox[i][j] += 1;
                    }
                    if (i + 1 < new_size_x) {
                        sandbox[i + 1][j] += 1;
                        if (sandbox[i + 1][j] > 3) {
                            fl1 = true;
                        }
                    } else {
                        sandbox[i][j] += 1;
                    }
                    if (j - 1 > -1) {
                        sandbox[i][j - 1] += 1;
                        if (sandbox[i][j - 1] > 3) {
                            fl1 = true;
                        }
                    } else {
                        sandbox[i][j] += 1;
                    }
                    if (j + 1 < new_size_y) {
                        sandbox[i][j + 1] += 1;
                        if (sandbox[i][j + 1] > 3) {
                            fl1 = true;
                        }
                    } else {
                        sandbox[i][j] += 1;
                    }
                    if (sandbox[i][j] > 3) {
                        fl1 = true;
                    }
                }

            }

        }

        iteration_count++;

        if (fl1) {
            fl = true;
        } else {
            fl = false;
        }
        fl1 = false;
        count++;

        if (count == table.freq) {
            CreateImage(new_size_x, new_size_y, sandbox, number_file_counter);
            count = 0;
            number_file_counter++;
        }

        if (iteration_count == table.max_iter) {

            break;
        }

    }

    if (count1) {
        CreateImage(new_size_x, new_size_y, sandbox, number_file_counter);
    }


    free(sandbox);


    return 0;
}

void CreateImage(int& new_size_x, int& new_size_y, int** sandbox[[]], int& number_file_counter) {
    Image image(new_size_y, new_size_x);
    for (int y = 0; y < new_size_x; ++y) {
        for (int x = 0; x < new_size_y; ++x) {
            if (sandbox[y][x] == 0) {
                image.SetColor(Color(255.0, 255.0, 255.0), x, y);
            } else if (sandbox[y][x] == 1) {
                image.SetColor(Color(0, 128, 0), x, y);
            } else if (sandbox[y][x] == 2) {
                image.SetColor(Color(139, 0, 255), x, y);
            } else if (sandbox[y][x] == 3) {
                image.SetColor(Color(255, 255, 0), x, y);
            } else {
                image.SetColor(Color(0, 0, 0), x, y);
            }
        }
    }
    std::string s = "image" + std::to_string(number_file_counter) + ".bmp";
    const char *out_put = s.c_str();
    image.Export(out_put);
}
/*
void СompletionOfMassive(int** old[[]],int** recent[[]],int start_x,int start_y,int end_x,int end_y){
    int old_x=0;
    int old_y=0;
    int const s_y=start_y;
    for(start_x;start_x<end_x;++start_x,old_x++){

        for(start_y;start_y<end_y;++start_y,old_y++){

            recent[start_x][start_y]=old[old_x][old_y];
            std::cout<<start_x<<' '<<start_y<<'\n';
        }
        start_y=s_y;

    }
    std::cout<<1;
}
*/
