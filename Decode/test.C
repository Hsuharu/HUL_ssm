void test(){
int n = 9999;
//バイナリ出力モード
fstream file("./filename.dat",ios::binary | ios::out);
//file open("./filename,dat",ios::bunary | ios::out);
//バイナリ入力モード
//fstream file("./filename.dat",ios::binary | ios::in);
//file open("./filename,dat",ios::bunary | ios::in);

//書き込む
file.write((char*)&n, sizeof(n));

//読み込む
//file.read((char*)&n, sizeof(n));
//cout << n << endl;

file.close();
}
