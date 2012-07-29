using namespace std;
class MP3 : public Data {
    public:
        void getData();
        int checkFile();
        void embedHeader(BMP &obj);
        void extractData();
        int checkHead();
};
   
void MP3::getData() {
    cout<<"\tEnter the name of the MP3 file :: ";
    cin>>name;
}
   
// The input file is verfied if its a valid MP3 file. The first 3 bytes in any
// MP3 file correspond to the characters ID3
int MP3::checkFile() {
    char c;
    int flag = 0;
    ifstream temp(name);
    temp.get(c);
    if(c == 'I' )
        flag = 1;
    temp.get(c);
    if(c != 'D')
        flag = 0;
    if ( flag == 1 ) {
        temp.get(c);
        if( c != '3' )
            flag = 0;
    }
    temp.close();
    return flag;
}
   
// A check value :: the string "MP3" is embedded first. This helps during extraction
// to verify that a MP3 is indeed embedded.
void MP3::embedHeader(BMP &obj) {
    toEmbed.open(name, ios::binary);
    int num, temp;
    char c;
    unsigned char c_out;
    long bin;
    // jpg contains the the reverse binary values of the characters J, P and G
    // 1 is appended to the left. JPG will be embedded to an image first
    // ASCII values are. J(74), P(80) and G(71)
    long mp3[3] = {110110010, 100001010, 111001100};
    for(int i=0;i<3;i++) {
        bin = mp3[i];
        for(int j=0;j<8;j++) {
            obj.in.get(c);
            num=c;
 	    if ( num < 0 )
  	        num += 256;        
            temp=bin%10;
	    if(temp==0)
                num = num & 0xFE;
	    else
                num = num | 1;
            bin/=10;
	    c_out=(unsigned char)num;
	    obj.out.put(c_out);
        }
    }
}
   


// Checks if the header value extracted corresponds to MP3.
// As "MP3" was embedded before embedding the MP3 file.
int MP3::checkHead() {
    if( !strcmp(check,"MP3") )
        return 1;
    else {
        cout<<"\n\tThe Bitmap file you mentioned contains no embedded data."<<endl;
        return 0;
    }
}       
               
// Extracts the data from the embedded bitmap file and stores on "output.mp3"        
void MP3::extractData() {
    int temp, n;
    char c;
    unsigned char c_write;
    ofstream out("output.mp3",ios::binary);
    for(int i = 0; i<length ; i++) {
        temp=0;   
	for(int i=0;i<8;i++) {
	    extract.get(c);
	    n=c;
	    if(n<0)
	        n += 256;
	    if( (n & 0x01) == 1) {
	        temp=temp<<1;
	        temp=temp | 1;
            } else
                temp=temp<<1;
        }
    c_write = (unsigned char)temp;
    out.put(c_write);			  
    }
    out.close();
    extract.close();
    cout<<"\tMP3 image has been successfully extracted to \"output.mp3\""<<endl;
    cout<<"\tThe file can be found in the current folder."<<endl;
}
