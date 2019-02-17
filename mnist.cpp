#include "mnist.h"

inline bool is_little_endian() {
	int x = 1;
	return *reinterpret_cast<char*>(&x) != 0;
}
template <typename T>
T* reverse_endian(T* p) {
	std::reverse(reinterpret_cast<char*>(p), reinterpret_cast<char*>(p) + sizeof(T));
	return p;
}

//バイト列からintへの変換
int reverseInt(int i) {
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int) c1 << 24) + ((int) c2 << 16) + ((int) c3 << 8) + c4;
}

vector<vector<float> > Mnist::readTrainingFile(string filename) {
    ifstream ifs(filename.c_str(), std::ios::in | std::ios::binary);
    int magic_number = 0;
    int number_of_images = 0;
    int rows = 0;
    int cols = 0;

	printf("sizeof(int):%d\n", sizeof(int));
	printf("is_little_endian:%d\n", is_little_endian());

    //ヘッダー部より情報を読取る。
    //ifs.read((char*) &magic_number, sizeof(magic_number));
	ifs.read(reinterpret_cast<char*>(&magic_number), sizeof(magic_number));
	magic_number = reverseInt(magic_number);
 	//ifs.read((char*) &number_of_images, sizeof(number_of_images));
	ifs.read(reinterpret_cast<char*>(&number_of_images), sizeof(number_of_images));
	number_of_images = reverseInt(number_of_images);
    //ifs.read((char*) &rows, sizeof(rows));
	ifs.read(reinterpret_cast<char*>(&rows), sizeof(rows));
	rows = reverseInt(rows);
    //ifs.read((char*) &cols, sizeof(cols));
	ifs.read(reinterpret_cast<char*>(&cols), sizeof(cols));
	cols = reverseInt(cols);

    vector<vector<float> > images(number_of_images);
    cout << "magic_number: " << magic_number << " number_of_images: " << number_of_images << " rows: " << rows << " cols: "
            << cols << endl;

    for (int i = 0; i < number_of_images; i++) {
        images[i].resize(rows * cols);

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                unsigned char temp = 0;
                //ifs.read((char*) &temp, sizeof(temp));
				ifs.read(reinterpret_cast<char*>(&temp), sizeof(temp));
				images[i][rows * row + col] = (float) temp;
            }
        }
    }
	printf("%s\n", filename.c_str());
	fflush(stdout);
    return images;
}

vector<float> Mnist::readLabelFile(string filename) {
    ifstream ifs(filename.c_str(), std::ios::in | std::ios::binary);
    int magic_number = 0;
    int number_of_images = 0;

    //ヘッダー部より情報を読取る。
    //ifs.read((char*) &magic_number, sizeof(magic_number));
	ifs.read(reinterpret_cast<char*>(&magic_number), sizeof(magic_number));
	
    magic_number = reverseInt(magic_number);
    //ifs.read((char*) &number_of_images, sizeof(number_of_images));
	ifs.read(reinterpret_cast<char*>(&number_of_images), sizeof(number_of_images));
	number_of_images = reverseInt(number_of_images);

    vector<float> label(number_of_images);

    cout << number_of_images << endl;

    for (int i = 0; i < number_of_images; i++) {
        unsigned char temp = 0;
        //ifs.read((char*) &temp, sizeof(temp));
		ifs.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		label[i] = (float) temp;
    }
    return label;
}

