//
// Created by micha on 2024/11/14.
//
#include "VLPR.h"

using namespace std;

//start
int penColor = 255;
//end

//gen pic start
typedef uint8_t BYTE;
char *error;
struct my_error_mgr {
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
};
typedef struct my_error_mgr *my_error_ptr;
//end

//trans start
//end

//recog start
map<string, string> map1, map2, map3, map4, map5;
map<int, map<string, string>> mapmap;
//recog end

struct hit_info {
    int x, y;
    bool hit;
};

struct img_pic_info {
    int r, g, b, a, x, y, group;

    void setGroup(int g) {

    }

    void set(int rv) {
        this->r = rv;
        this->g = rv;
        this->b = rv;
    }

    void setrgb(int r, int g, int b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

struct group_info {
    int lx, ly, bx, by;

    int width() {
        return bx - lx;
    }

    int height() {
        return by - ly;
    }

    bool isV() {
        return true;
    }

    void updateXy(int x, int y) {

    }

    void updateXy(int lx, int ly, int bx, int by) {
        this->lx = lx;
        this->ly = ly;
        this->bx = bx;
        this->by = by;
    }
};

struct ImgPicInfo {
    vector<vector<struct img_pic_info>> vector;
    group_info group_info;
};

int scale = 1;

ImgPicInfo s2(vector<vector<struct img_pic_info>> vector, struct group_info group_info) {
    ImgPicInfo imgs;
    double width = group_info.width();
    double height = group_info.height();
    double outWidth = width + 10 - ((int) width) % 10;
    double outHeight = height + 10 - ((int) height) % 10;
    outWidth = width * scale;
    outHeight = height * scale;
    double fx = outWidth / width;
    double fy = outHeight / height;
    double x, y;
    for (int j = 0; j < outHeight; j++) {
        y = j / fy;
        std::vector<struct img_pic_info> add_line;
        for (int i = 0; i < outWidth; i++) {
            x = i / fx;
            int x1, x2, y1, y2;
            x1 = x;
            x2 = x1 + 1;
            y1 = y;
            y2 = y1 + 1;
            double u, v;
            u = x - x1;
            v = y - y1;

            int r1 = vector.at(group_info.ly + y1).at(group_info.lx + x1).r;
            int r2 = vector.at(group_info.ly + y1).at(group_info.lx + x2).r;
            int r3 = vector.at(group_info.ly + y2).at(group_info.lx + x1).r;
            int r4 = vector.at(group_info.ly + y2).at(group_info.lx + x2).r;
            int r = r1 * (1 - u) + r2 * u;
            int rr = r3 * (1 - u) + r4 * u;
            r = r * (1 - v) + rr * v;

            struct img_pic_info img_info_add;
            img_info_add.x = i;
            img_info_add.y = j;
            img_info_add.set(r);
            add_line.push_back(img_info_add);
        }
        imgs.vector.push_back(add_line);
    }
    imgs.group_info.updateXy(0, 0, outWidth, outHeight);
    return imgs;
}

string tcFeiche(vector<vector<struct img_pic_info>> vector1, group_info group_info) {
    string ret;
    float xs = 1.0000, ys = 1.0000;
    if (group_info.width() > 10.000 && group_info.height() > 10.000) {
        xs = group_info.width() / 10.0000;
        ys = group_info.height() / 10.0000;
    } else if (group_info.height() > 10.0000) {
        ys = group_info.height() / 10.0000;
    } else if (group_info.width() > 10.0000) {
        xs = group_info.width() / 10.0000;
    }
    float lx = group_info.lx, ly = group_info.ly, bx = group_info.bx, by = group_info.by;
    string feiche;
    int ii = 0, jj = 0;
    vector<string> vector;
    LOGI("hitTop tcFeiche feiche2 ys %s", to_string(ys).c_str());
    LOGI("hitTop tcFeiche feiche2 xs %s", to_string(xs).c_str());
    for (float y = ly; y < by; y++) {
        bool w = false, ww = false;
//        if ((int) ((y - ly) / ys) == ii) {
        if ((ly + ys * ii) - y <= 0.5f || (ly + ys * ii) - y < 0 && (ly + ys * ii) - y >= -0.5f) {
            ii++;
            w = true;
            if (ii > 11) {
//                break;
            }
        } else {
            w = false;
        }
        jj = 0;
        string feiche2;
        feiche2.append("\n");
        for (float x = lx; x < bx; x++) {
            if ((lx + xs * jj) - x <= 0.5f ||
                (lx + xs * jj) - x < 0 && (lx + xs * jj) - x >= -0.5f) {
//            if ((int) ((x - lx) / xs) == jj) {
                jj++;
                if (jj > 11) {
//                    break;
                }
                ww = true;
            } else {
                ww = false;
            }
            if (w && ww) {
                if (vector1.at(y).at(x).r == penColor) {
                    feiche.append("1");
                } else {
                    feiche.append("0");
                }
                feiche2.append("$");
            } else if (vector1.at(y).at(x).r == penColor) {
                feiche2.append("1");
            } else {
                feiche2.append("0");
            }
        }
        vector.push_back(feiche2);
    }

    for (const auto &item: vector) {
        LOGI("%s", item.c_str());
    }

    // max - 1
    map2["0111111111000010100000101010100000101000111111111100000000000010000010001000001000100000100010000010"] = "晋";
    map2["0000000000000111110001000010000000010000000001000000000000000000000000001111111000100000100010000010"] = "鲁";
    map2["0000000000011101111000000000000010000000001000000000010010000000100010000001011000000011000000100100"] = "豫";
    map2["0000000000000001000000000000000000000000001000001000100000100011111110000001000000100100100100010001"] = "京";
    map2["0000000000111000000010001111111010100000101001001010000000001001111111100100110010100100001000100001"] = "陕";
    map2["0000010000001001000000100111110010100001011100000000100000100010100000001010000100100000010010000000"] = "你";
    map2["0010000000000001111101110000100000000000000000010001010111110101000100001000010000110001000100000100"] = "好";
    map2["0000000010001000001000100000101111111111001000001000100000100010000010001001111000100000000010000000"] = "世";
    map2["0011111110000001000000000100000000010000001111111000001010000001000100000100000100010000000010000000"] = "界";

    // max - 1
    map2["0000000011000111111111100000110000000011000000001100000000110000000011000000001100000000110000000011"] = "1";
    map2["0000111000001100011001000000100000000011000000001000000001000000011000000011000000010000000110000000"] = "2";
    map2["0000111000001100011001000000100000000010000000011000001111000000000011000000000101000000110010000110"] = "3";
    map2["0000001000000001000000001100000001100000000100000000100001000100000100111111111100000001000000000100"] = "4";
    map2["0011111110001000000001100000000110000000010111100001000001100000000011000000001101000000110110000110"] = "5";
    map2["0000001000000001000000001000000001000000001111100001110001101100000011110000001101000000110010000110"] = "6";
    map2["1111111111000000001100000000100000000100000000110000000110000000011000000011000000001000000001000000"] = "7";
    map2["0000111000001100011001100000100110000010001100011000011111000110000011110000000101000000110011000110"] = "8";
    map2["0000111000001100011001000000111100000001010000001100110001100000111100000000100000000110000000100000"] = "9";
    map2["0000111000001100011001100000100100000011110000000111000000011100000001010000001101100000100011000110"] = "0";
    // max - 1
    map2["0000010000000011000000001010000000001000000100010000010001000010000100001111111001000000100100000001"] = "A";
    map2["1111110000110000011011000000101100000010110000011011111111101100000011110000000111000000011100000110"] = "B";
    map2["0000011000000100001000100000010100000000010000000011000000000100000000010000000000100000010001000010"] = "C";
    map2["1111110000110000110011000000101100000011110000000111000000011100000001110000001111000000101100001100"] = "D";
    map2["1111111111110000000011000000001100000000110000000011111111101100000000110000000011000000001100000000"] = "E";
    map2["1111111111110000000011000000001100000000110000000011111111101100000000110000000011000000001100000000"] = "F";
    map2["0000011100000110001000100000010100000000010000000011000001110100000001010000000100100000010001100011"] = "G";
    map2["1000000001110000000111100000111010000101100100010110001010011000110001100001000110000000011000000001"] = "M";

    // bw = 7
    map1["0000010000001001000000100111110100100001010100000010000000100000100000000010000100000000010000000000"] = "你";
    map1["0010000000001001111101110000100000000000000000010001010111110101000100001000010000110001000100100100"] = "好";
    map1["0000000010001000001000100000101111111111001000001000100000100010000010001001111000100000000010000000"] = "世";
    map1["0011111110000001000000111111100000010000001111111000001010000011000110010100000100010000000010000000"] = "界";

    // bw = 4
    map3["0000010000001001000000100111110010100001011100000000100000100010100000001010000100100000010010001000"] = "你";
    map3["0010000000001001111100000000100000000100010000010001010111110101000100001000010000110001000100000100"] = "好";
    map3["0000000010001000001000100000101111111111001000001000100000100010000010001001111000100000000010000000"] = "世";
    map3["0011111110000001000000111111100000010000001111111000001010000011000100110100000100010000000010000000"] = "界";

    // bw = 3
    map4["0000010000001001000000100000010000100001010000000010000000100000100000000010000100000000000000000000"] = "你";
    map4["0010000000001001111100100000000000000000000000010001010111110101000100001000010000110001000100000100"] = "好";
    map4["0000000010000000001000000000101111111111000000001000000000100000000010000001111000000000000000000000"] = "世";
    map4["0011111110000001001000111111100000010010001111111000001010000011000100010100000100010000000010000000"] = "界";

    map5["0000010000001111111100100000010010010001001011000101000000010111111111111111111100011111100000000110"] = "粤";
    map5["0111111000011000011101100000010110000011011111111001100001110110000011011000001101000000110110011110"] = "B";
    map5["0111111111011111111101100000000110000000011111110000110001110000000011000000001101100000110111111110"] = "5";
    map5["0000000000011111111101100000000110000000011111111000100001110000000011000000001101100000110011111110"] = "5";
    map5["0000000000011111111101100000000110000000011111111001110001110000000011000000001101100000110011111111"] = "5";
    map5["0000000000111111111111000000000110000000011000000001111111100110000000011000000001100000000111111111"] = "E";
    map5["0000000000111111111001100000000110000000011000000001111111100110000000011000000001100000000111111111"] = "E";


    mapmap[5] = map5;

    LOGI("hitTop tcFeiche feiche %s", feiche.c_str());
    LOGI("hitTop tcFeiche feiche %s", mapmap.find(5)->second.find(feiche.c_str())->second.c_str());
    return ret;
}

int feiche(vector<vector<struct img_pic_info>> vector1, map<int, struct group_info> &group_infos) {
    for (auto &item: group_infos) {
        if (item.second.isV()) {
            LOGI("group_infos %s",
                 (to_string(item.first) + "_____" + to_string(item.second.lx) + "_________" +
                  to_string(item.second.ly) + "_____" + to_string(item.second.bx) + "_____" +
                  to_string(item.second.by) + "_____" + to_string(item.second.height())).c_str());
//            ImgPicInfo imgPicInfo = s2(vector1,item.second);
//            LOGI("group_infos ImgPicInfo %s",
//                 (to_string(item.first) + "_____" + to_string(imgPicInfo.group_info.lx) + "_________" +
//                  to_string(imgPicInfo.group_info.ly) + "_____" + to_string(imgPicInfo.group_info.bx) + "_____" +
//                  to_string(imgPicInfo.group_info.by)).c_str());
//            string ret = tcFeiche(imgPicInfo.vector, imgPicInfo.group_info);
            string ret = tcFeiche(vector1, item.second);
        }
    }
    return 1;
}

METHODDEF(void)
my_error_exit(j_common_ptr cinfo) {
    my_error_ptr myerr = (my_error_ptr) cinfo->err;
    (*cinfo->err->output_message)(cinfo);
    LOGI("jpeg_message_table[%d]:%s", myerr->pub.msg_code,
         myerr->pub.jpeg_message_table[myerr->pub.msg_code]);
    longjmp(myerr->setjmp_buffer, 1);
}

int generateJPEG(BYTE *data, int w, int h, int quality,
                 const char *outfilename, bool optimize) {
    int nComponent = 3;
    struct jpeg_compress_struct jcs;
    struct my_error_mgr jem;

    jcs.err = jpeg_std_error(&jem.pub);
    jem.pub.error_exit = my_error_exit;
    if (setjmp(jem.setjmp_buffer)) {
        return 0;
    }

    jpeg_create_compress(&jcs);
    FILE *f = fopen(outfilename, "wb");
    if (f == NULL) {
        return 0;
    }
    jpeg_stdio_dest(&jcs, f);
    jcs.image_width = w;
    jcs.image_height = h;
    if (optimize) {
        LOGI("optimize==true");
    } else {
        LOGI("optimize==false");
    }
    jcs.arith_code = false;
    jcs.input_components = nComponent;
    if (nComponent == 1)
        jcs.in_color_space = JCS_GRAYSCALE;
    else
        jcs.in_color_space = JCS_RGB;

    jpeg_set_defaults(&jcs);
    jcs.optimize_coding = optimize;
    jpeg_set_quality(&jcs, quality, true);

    jpeg_start_compress(&jcs, TRUE);

    JSAMPROW row_pointer[1];
    int row_stride;
    row_stride = jcs.image_width * nComponent;
    while (jcs.next_scanline < jcs.image_height) {
        row_pointer[0] = &data[jcs.next_scanline * row_stride];

        jpeg_write_scanlines(&jcs, row_pointer, 1);
    }
    jpeg_finish_compress(&jcs);
    jpeg_destroy_compress(&jcs);
    fclose(f);

    return 1;
}

int DecodeJPEG(const std::string &filename) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE *file = fopen(filename.c_str(), "rb");
    if (!file) {
        std::cerr << "Unable to open file " << filename << std::endl;
        std::string sdPath = "fopen(filename.c_str()  fail ";
        LOGI("open sdcard fail %s", &sdPath);
        return false;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    jpeg_stdio_src(&cinfo, file);

    (void) jpeg_read_header(&cinfo, TRUE);
    (void) jpeg_start_decompress(&cinfo);

    int width, height, channels;
    std::vector<unsigned char> data;

    width = cinfo.output_width;
    height = cinfo.output_height;
    channels = cinfo.output_components;

    data.resize(width * height * channels);

    JSAMPROW row_pointer[1];
    std::vector<std::vector<struct img_pic_info>> img_pic_info;

    while (cinfo.output_scanline < cinfo.output_height) {
        row_pointer[0] = (JSAMPROW) (&data[cinfo.output_scanline * width * channels]);
        (void) jpeg_read_scanlines(&cinfo, row_pointer, 1);
        string rgba = "";
        std::vector<struct img_pic_info> line;
        for (int i = 0; i < cinfo.output_width; i++) {
            struct img_pic_info img_info;
            line.push_back(img_info);
            char r = row_pointer[0][3 * i + 0];
            char g = row_pointer[0][3 * i + 1];
            char b = row_pointer[0][3 * i + 2];
            char a = 255;
            img_info.x = i;
            img_info.y = cinfo.output_scanline;
            char ret = r * 0.12 + g * 0.58 + b * 0.30;
            if (ret < 125) {
                ret = 0;
            } else {
                ret = 255;
            }
//            if (r < 150 || g < 150 || b < 150) {
//                ret = 0;
//            } else {
//                ret = 255;
//            }
            r = ret;
            g = ret;
            b = ret;
            img_info.r = r;
            img_info.g = g;
            img_info.b = b;
            img_info.a = a;
        }
        img_pic_info.push_back(line);
    }

    //init
    std::vector<std::vector<struct img_pic_info>> img_pic_info_add;
    for (int y = 0; y < cinfo.output_height; y++) {
        std::vector<struct img_pic_info> add_line;
        for (int x = 0; x < cinfo.output_width; x++) {
            struct img_pic_info img_info_add;
            img_info_add.x = x;
            img_info_add.y = y;
            img_info_add.set(penColor == 0 ? 255 : 0);
            add_line.push_back(img_info_add);
        }
        img_pic_info_add.push_back(add_line);
    }

    //get recog outline data
    map<int, struct group_info> group_info;
    vector<int> baseYVector;
    for (int y = 0; y < cinfo.output_height; y++) {
        std::string rgba = "";
        std::vector<struct img_pic_info> s_line_vector = img_pic_info.at(y);
        for (int x = 0; x < cinfo.output_width; x++) {
            struct img_pic_info source_img_info = s_line_vector.at(x);
            //add
            if (x > 1 && y > 1 && x < cinfo.output_width - 2 && y < cinfo.output_height - 2) {
                int tf = 100;
                char l = img_pic_info.at(y).at(x - 1).r - source_img_info.r;
                if (l > tf || l < -tf) {
                    img_pic_info_add.at(y).at(x - 1).set(img_pic_info.at(y).at(x - 1).r);

                    img_pic_info_add.at(y).at(x - 1).set(penColor);
                    img_pic_info_add.at(y).at(x + 1).set(penColor);
                    img_pic_info_add.at(y - 1).at(x).set(penColor);
                    img_pic_info_add.at(y + 1).at(x).set(penColor);

                    img_pic_info_add.at(y).at(x - 2).set(penColor);
                    img_pic_info_add.at(y).at(x + 2).set(penColor);
                    img_pic_info_add.at(y - 2).at(x).set(penColor);
                    img_pic_info_add.at(y + 2).at(x).set(penColor);
                }
                //r
                char r = img_pic_info.at(y).at(x + 1).r - source_img_info.r;
                if (r > tf || r < -tf) {
                    img_pic_info_add.at(y).at(x + 1).set(img_pic_info.at(y).at(x + 1).r);

                    img_pic_info_add.at(y).at(x - 1).set(penColor);
                    img_pic_info_add.at(y).at(x + 1).set(penColor);
                    img_pic_info_add.at(y - 1).at(x).set(penColor);
                    img_pic_info_add.at(y + 1).at(x).set(penColor);

                    img_pic_info_add.at(y).at(x - 2).set(penColor);
                    img_pic_info_add.at(y).at(x + 2).set(penColor);
                    img_pic_info_add.at(y - 2).at(x).set(penColor);
                    img_pic_info_add.at(y + 2).at(x).set(penColor);
                }
                //t
                char t = img_pic_info.at(y - 1).at(x).r - source_img_info.r;
                if (t > tf || t < -tf) {
                    img_pic_info_add.at(y - 1).at(x).set(img_pic_info.at(y - 1).at(x).r);

                    img_pic_info_add.at(y).at(x - 1).set(penColor);
                    img_pic_info_add.at(y).at(x + 1).set(penColor);
                    img_pic_info_add.at(y - 1).at(x).set(penColor);
                    img_pic_info_add.at(y + 1).at(x).set(penColor);

                    img_pic_info_add.at(y).at(x - 2).set(penColor);
                    img_pic_info_add.at(y).at(x + 2).set(penColor);
                    img_pic_info_add.at(y - 2).at(x).set(penColor);
                    img_pic_info_add.at(y + 2).at(x).set(penColor);
                }
                //b
                char b = img_pic_info.at(y + 1).at(x).r - source_img_info.r;
                if (b > tf || b < -tf) {
                    img_pic_info_add.at(y + 1).at(x).set(img_pic_info.at(y + 1).at(x).r);

                    img_pic_info_add.at(y).at(x - 1).set(penColor);
                    img_pic_info_add.at(y).at(x + 1).set(penColor);
                    img_pic_info_add.at(y - 1).at(x).set(penColor);
                    img_pic_info_add.at(y + 1).at(x).set(penColor);

                    img_pic_info_add.at(y).at(x - 2).set(penColor);
                    img_pic_info_add.at(y).at(x + 2).set(penColor);
                    img_pic_info_add.at(y - 2).at(x).set(penColor);
                    img_pic_info_add.at(y + 2).at(x).set(penColor);
                }
            }
        }
    }
    //get recog outline data end

    //target rect calculate
    int target_width = 200;
    int target_height = 50;
    int target_space = 10;
    int targetTopX = 0;
    int targetTopY = 0;
    int targetBottomX = 0;
    int targetBottomY = 0;
    int targetColor = penColor;
    int target_space_temp = 0;
    for (int y = target_height; y < cinfo.output_height - target_height; y++) {
        std::string rgba = "";
        std::vector<struct img_pic_info> s_line_vector = img_pic_info_add.at(y);
        int hc = 0;
        for (int x = target_width; x < cinfo.output_width - target_width; x++) {
            struct img_pic_info source_img_info = s_line_vector.at(x);
            //add
            if (source_img_info.r == targetColor) {
                hc++;
                target_space_temp = 0;
                if (hc == target_width) {
                    int hvc = 0;
                    //find 1
                    for (int i = 0; i < target_height; i++) {
                        if (targetColor == img_pic_info_add.at(y + i).at(x - target_width + 1).r) {
                            hvc++;
                            target_space_temp = 0;
                            if (hvc == target_height) {
                                //
                                targetTopX = x - target_width + 1;
                                targetTopY = y;

                                int tempX = 0;
                                while (targetColor == img_pic_info_add.at(y).at(x + tempX).r) {
                                    tempX++;
                                }

                                targetBottomX = x + tempX - 1;

                                int tempY = 0;
                                while (targetColor ==
                                       img_pic_info_add.at(y + target_height + tempY).at(
                                               targetTopX).r) {
                                    tempY++;
                                }

                                targetBottomY = y + target_height + tempY;

                                int hhc = targetBottomX - targetTopX;
                                hhc = hhc / 4 * 3;
                                int chc = 0;
                                for (int yy = targetBottomY;
                                     yy < cinfo.output_height; yy++) {
                                    bool hit = false;
                                    chc = 0;
                                    for (int s = targetTopX; s < targetBottomX; s++) {
                                        if (targetColor ==
                                            img_pic_info_add.at(yy).at(s).r) {
                                            chc++;
                                            if (chc > hhc) {
                                                hit = true;
                                                break;
                                            }
                                        }
                                    }
                                    if (hit) {
                                        targetBottomY = yy;
                                        break;
                                    } else if (yy > cinfo.output_height - 10) {
                                        targetBottomY = cinfo.output_height - 10;
                                        break;
                                    }
                                }

                                baseYVector.push_back(targetTopY);
                                baseYVector.push_back(targetBottomY);
                                break;
                            }
                        } else {
                            target_space_temp++;
                            if (target_space_temp >= target_space) {
                                hvc = 0;
                                hc = 0;
                                break;
                            }
                        }
                    }

                    //find 2
                    if (hvc != target_height) {
                        hvc = 0;
                        for (int i = 0; i < target_height; i++) {
                            if (targetColor ==
                                img_pic_info_add.at(y - i).at(x - target_width + 1).r) {
                                hvc++;
                                target_space_temp = 0;
                                if (hvc == target_height) {
                                    //
                                    targetTopX = x - target_width;

                                    int tempY = 0;
                                    while (targetColor == img_pic_info_add.at(y + tempY).at(
                                            x - target_width + 1).r) {
                                        tempY--;
                                    }

                                    targetTopY = y + tempY + 1;

                                    int tempX = 0;
                                    while (targetColor == img_pic_info_add.at(y).at(x + tempX).r) {
                                        tempX++;
                                    }

                                    targetBottomX = x + tempX - 1;
                                    targetBottomY = y;


                                    int hhc = targetBottomX - targetTopX;
                                    hhc = hhc / 4 * 3;
                                    int chc = 0;
                                    for (int yy = targetTopY; yy > 0; yy--) {
                                        bool hit = false;
                                        chc = 0;
                                        for (int s = targetTopX; s < targetBottomX; s++) {
                                            if (targetColor ==
                                                img_pic_info_add.at(yy).at(s).r) {
                                                chc++;
                                                if (chc > hhc) {
                                                    hit = true;
                                                    break;
                                                }
                                            }
                                        }
                                        if (hit) {
                                            targetTopY = yy;
                                            break;
                                        } else if (yy < 10) {
                                            targetTopY = 10;
                                            break;
                                        }
                                    }

                                    baseYVector.push_back(targetTopY);
                                    baseYVector.push_back(targetBottomY);
                                    break;
                                }
                            } else {
                                target_space_temp++;
                                if (target_space_temp >= target_space) {
                                    hvc = 0;
                                    hc = 0;
                                    break;
                                }
                            }
                        }
                    }
                } else {

                }
            } else {
                target_space_temp++;
                if (target_space_temp >= target_space) {
                    hc = 0;
                }
            }
        }
    }
    //target rect calculate end

    for (const auto &item: baseYVector) {
//        LOGI("open baseYVector  %s", to_string(item).c_str());
    }


    LOGI("open target xy  %s",
         (to_string(targetTopX)
          + "__" + to_string(targetTopY)
          + "__" + to_string(targetBottomX)
          + "__" + to_string(targetBottomY)).c_str());

    for (int i = targetTopY; i < targetBottomY; i++) {
        string feiche2;
        for (int x = targetTopX; x < targetBottomX; x++) {
            int r = img_pic_info.at(i).at(x).r;
            if (r == penColor) {
                feiche2.append("1");
            } else {
                feiche2.append("0");
            }
        }
        LOGI(" %s",
             feiche2.c_str());
    }


    //group
    int selfGroup = 0;
    for (int i = 0; i < baseYVector.size(); i++) {
        if (i + 1 >= baseYVector.size()) {
            continue;
        }
        int s_y = baseYVector.at(i);
        int e_y = baseYVector.at(i + 1);
        int lh = e_y - s_y;
        int topX = 0, topY = 0;
        if (lh == 1) {
            continue;
        } else if (lh > 1) {
            for (int x = targetTopX; x < targetBottomX; x++) {
                int hc = 0;
                for (int y = s_y; y <= e_y; y++) {
                    int r = img_pic_info.at(y).at(x).r;
                    if (r != 255 - penColor) {
//                        LOGI("open break hc %s", to_string(hc).c_str());
                        break;
                    } else {
                        hc++;
                        if (hc == lh) {
                            for (int y = s_y; y <= e_y; y++) {
                                int r = img_pic_info.at(y).at(x + 1).r;
                                int p_r = img_pic_info.at(y).at(x - 1).r;
                                if (r != 255 - penColor) {
                                    //start
//                                    LOGI("open start %s", to_string(x).c_str());
                                    topX = x + 1;
                                    topY = s_y;
                                    break;
                                } else if (p_r != 255 - penColor) {
                                    //end
                                    int lx = topX, ly = s_y + 1, bx = x, by = e_y;
                                    int hc = bx - lx;
                                    int hi = 0;
                                    for (int y = ly; y < by; y++) {
                                        hi = 0;
                                        for (int x = lx; x < bx; x++) {
                                            int r = img_pic_info.at(y).at(x).r;
                                            if (r != penColor) {
                                                hi++;
                                            }
                                        }
                                        if (hi == hc) {
                                            ly++;
                                        } else {
                                            break;
                                        }
                                    }

                                    hi = 0;
                                    int tby = by;
                                    for (int y = by; y > 0; y--) {
                                        hi = 0;
                                        for (int x = lx; x < bx; x++) {
                                            int r = img_pic_info.at(y).at(x).r;
                                            if (r != penColor) {
                                                hi++;
                                            }
                                        }
                                        if (hi == hc) {
                                            tby--;
                                        } else {
                                            break;
                                        }
                                    }
                                    struct group_info groupInfo;
                                    groupInfo.updateXy(topX, ly, x, tby);
                                    group_info[selfGroup] = groupInfo;
                                    selfGroup++;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //group end

//    1 2 3 4 5 6 7 8 9 10
    int rv = feiche(img_pic_info, group_info);

    BYTE r, g, b;
    BYTE *data2;
    BYTE *tmpdata;
    data2 = (BYTE *) malloc(cinfo.output_width * cinfo.output_height * 3);
    tmpdata = data2;
    int j = 0, i = 0;
    int color;
    for (int y = 0; y < cinfo.output_height; y++) {
        string rgba = "";
        for (int x = 0; x < cinfo.output_width; x++) {
            *data2 = img_pic_info_add.at(y).at(x).b;
            *(data2 + 1) = img_pic_info_add.at(y).at(x).g;
            *(data2 + 2) = img_pic_info_add.at(y).at(x).r;
            data2 = data2 + 3;
        }
    }
    //save
    generateJPEG(tmpdata, cinfo.output_width, cinfo.output_height, 100, "/sdcard/1/2_3.jpg", false);
    free(tmpdata);
    (void) jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(file);
    return rv;
}

int VLPR::process() {
    return DecodeJPEG("/sdcard/1/2.jpg");
}