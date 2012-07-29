using namespace std;
class JPEG : public Data {
    public:
        void getData();
        int checkFile();
        void embedHeader(BMP &obj);
        int checkHead();
        void extractData();
};
   
// Takes the filename as input. The file is not loaded at the stream as of now,
// as another stream needs access to it to calculate the length first.  
void JPEG::getData() {
    cout<<"\tEnter the name of the JPEG file :: ";
    cin>>name;
}
   
// Checking the input file with the JPEGs magic number FF D9   
int JPEG::checkFile() {
    char c;
    int flag = 0, num;
    ifstream temp(name, ios::binary);
    if ( temp ) {
        temp.get(c);
        num = c;
        if ( num<0 )
            num += 256;
        if(num == 255 )
            flag = 1;
              
        temp.get(c);
        num = c;
        if ( num<0 )
            num += 256;
        if( num != 216 )
            flag = 0;
        temp.close();
    }
    return flag;
}
      
// To verify during extraction that the BMP contains an embedded image, we embed the 
// characters JPG before embedding the data.   
void JPEG::embedHeader(BMP &obj) {
    toEmbed.open(name, ios::binary);
    int num, temp;
    char c;
    unsigned char c_out;
    long bin;
    // jpg contains the the reverse binary values of the characters J, P and G
    // 1 is appended to the left. JPG will be embedded to an image first
    // ASCII values are. J(74), P(80) and G(71)
    long jpg[3] = {101010010, 100001010, 111100010};
    for(int i=0;i<3;i++) {
        bin = jpg[i];
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
   
// Checks if the header value extracted corresponds to JPG.
// As JPG was embedded before embedding the JPEG image.
int JPEG::checkHead() {
    if( !strcmp(check,"JPG") )
        return 1;
    else {
        cout<<"\n\tThe Bitmap file you mentioned contains no embedded data."<<endl;
        return 0;
    }
}      

// Extracts the embedded JPG image from the BMP file   
void JPEG::extractData() {
    int temp, n;
    char c;
    unsigned char c_write;
    ofstream out("output.jpg",ios::binary);
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
    cout<<"\tJPEG image has been successfully extracted to \"output.jpg\""<<endl;
    cout<<"\tThe file can be found in the current folder."<<endl;
}
