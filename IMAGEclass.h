using namespace std;
class Image
   {
         protected:
                   // Filename is the name of the input file
                   char filename[100];
         public:
                ifstream in;
                long length;
                int getInputfile();
                void setlength();
   };
   
//getInputfile opens the bitmap file and returns 1 when the file successfully opens 
int Image::getInputfile()
   {
         cout<<"\tEnter the name of the Bitmap file :: ";
         cin>>filename;
         in.open(filename, ios::binary);
         if( !in )
             return 0;
         else
             return 1;
   }
   
// Sets the length of the file, and this can be used to check the maximum size of
// data that can be embedded into it.
void Image::setlength()
   {
         char c;
         ifstream temp(filename, ios::binary);
         length = 0;
         while ( !temp.eof() )
               {
                      temp.get(c);
                      length++;
               }
         temp.close();
         cout<<"\tThe size of the BMP file is :: "<<(length/1024)<<"Kb"<<endl;
         cout<<"\tMaximum of :: "<<(length-100)/(8*1024)<<"Kb can be embedded onto this file!"<<endl<<endl;
   }

// The BMP class has been derived from the image class. Steganography in this project has
// been performed on Bitmap files.
class BMP: public Image
   {
         public:
                ofstream out;
                int getOutputfile();
                int checkFile();
                void byepassHeader();
                void closefiles();
   };
    
// checkFile returns 1 when the file is a valid BMP
// A valid BMP has the characers "BM" as the first 2 bytes.
int BMP::checkFile()
   {
         char c;
         int flag = 0;
         ifstream temp(filename);
         temp.get(c);
         if(c == 'B' )
              flag = 1;
         temp.get(c);
         if(c != 'M')
              flag = 0;
         temp.close();
         return flag;
   }

// A BMP file has a header of size 54 bytes. No embedding is thus allowed in the first 56 bytes.
// If the header is tampered with, we might not get a valid BMP file.   
void BMP::byepassHeader()
   {
         char c;
         for(int i = 0; i<56; i++)
            {
                 in.get(c);
                 out.put(c);
            }
   }
   
//Sets the output BMP file as "output.BMP"
int BMP::getOutputfile()
   {
         out.open("output.bmp", ios::binary);
         if( !out )
              return 0;
         else
              return 1;
   }
    
// Closes both the input and output file streams when called by the user.
void BMP::closefiles()
   {
         in.close();
         out.close();
   }
