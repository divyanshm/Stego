using namespace std;
class Text : public Data {
    private:
        string tex;
    public:
        void getData();
        void openStream();
        void embedHeader (BMP &obj);
        void embedTrailer(BMP &obj);
        void extractData();
        int checkHead();
   };
   
// Takes the text to be embedded as input from the user   
void Text::getData() {
    cin.get();
    cout<<"\n\tEnter the Text to be embedded onto the image :: "<<endl;
    cout<<"\t";
    getline(cin, tex);
}

// Initialises the output stream
// The text to be embedded is stored onto a file
// and fed to the toEmbed stream
void Text::openStream() {
    ofstream otemp("text_temp.txt");
    otemp<<tex;
    otemp.close();
    toEmbed.open("text_temp.txt", ios::binary);
}

// To verify during extraction that Text was embedded in the image
// we place a string "BEG" before hiding data into the image.
void Text::embedHeader (BMP &obj) {
    int num, temp;
    char c;
    unsigned char c_out;
    long bin;
    // BEG contains the the reverse binary values of the characters B, E and G
    // 1 is appended to the left. BEG will be embedded to an image first
    // ASCII values are. B(66), E(69) and G(71)
    long BEG[3] = {101000010, 110100010, 111100010};
    for(int i=0;i<3;i++) {
        bin = BEG[i];
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
   
// Embed \0 at the end, makes extraction easier
void Text::embedTrailer(BMP &obj) {
    int num;
    char c;
    unsigned char c_out;
    for(int i=0;i<16;i++) {
		    obj.in.get(c);
		    num=c;
		    if(num < 0)
			      num += 256;
		    num=num | 0x01;
		    c_out=(unsigned char)num;
		    obj.out.put(c_out);
    }
}

// Checks if the header value extracted corresponds to BEG.
// As BEG was embedded before embedding any further Text.
int Text::checkHead() {
    if( !strcmp(check,"BEG") )
        return 1;
    else {
        cout<<"\n\tThe Bitmap file you mentioned contains no embedded data."<<endl;
        return 0;
    }
}                 

// This function extracts the text hidden in the file and displays it on the screen         
void Text::extractData() {
    int temp = 0, n;
    char c;
    cout<<"\tThe extracted text is :: "<<endl;
    cout<<"\n\t";
    while( temp!=255 ) {
        temp=0;   
        for(int i=0;i<8;i++) {
            extract.get(c);
            n=c;
            if( (n & 0x01) == 1) {
                temp=temp<<1;
                temp=temp | 1;
            } else
                temp=temp<<1;
            }
            c=(char)temp;
            if(temp!=255)
                cout<<c;			  
        }
    extract.close();
}
