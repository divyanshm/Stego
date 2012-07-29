using namespace std;
class Data
   {
          protected:
                    //the toEmbed stream will be shared by all the derived classes
                    ifstream toEmbed;
                    // the extract stream will contain the input file stream out
                    // of which the hidden data is to be extracted.
                    ifstream extract;
                    char check[3], fname[50], name[100];
                    long length;
          public:
                 void embedData(BMP &obj);
                 void embedRest(BMP &obj);
                 void embedLength(BMP &obj);
                 int checkLength(BMP &obj);
                 int setHead();
                 void extractLength();
                 void openExtractFile();
   };
   
// Returns 1 if length of the file to be embedded is smaller than length of the bitmap file
int Data::checkLength(BMP &obj)
   {
         ifstream temp(name, ios::binary);
         length = 0;
         char c;
         while ( !temp.eof() )
               {
                      temp.get(c);
                      length++;
               }
         temp.close();
         if(length < (obj.length-100))
            {
                   cout<<"\tEmbedding "<<length/1024<<" Kb of MP3 file now!"<<endl;
                   return 1;
            }
         else
              return 0;
   }
   
// Embedding the length of the Data file to the bitmap image
void Data::embedLength(BMP &obj)
   {
         union{
               long l_temp;
               char eq[4];
               };
         char c; int temp, num;
         unsigned char temp2;
         long bin;
         unsigned char c_out;
         l_temp=length;

     //Generates the reverse binary code for the variable length   
         for(int i=0;i<4;i++)
            {
                temp2=eq[3-i];        
                bin=1;
                         
                for(int j=0;j<8;j++)
                   {  
			            if(temp2%2==0)
                           bin=bin*10;
			            else
				           bin=bin*10+1;
			            temp2/=2;
                   }                  
	            for(int i=0;i<8;i++)
	               {
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
   
// Some file has already been opened using the toEmbed stream
// This function embeds the stream into the BMP output file
void Data::embedData(BMP &obj)
   {        
	     int i=0,  temp, num;
	     long bin;
	     char c;
	     unsigned char c_out;
	
	     while( !toEmbed.eof() )
             {
		          bin=1;
	  	          toEmbed.get(c);
		          num=c;
		          if ( num<0 )
		              num += 256;
		          for(int j=0;j<8;j++)
		              {  
			              if( num%2 == 0 )
				               bin=bin*10;
			              else
				               bin=bin*10+1;
			              num/=2;
   		              }   
		
		          for(int k=0;k<8;k++)
                      {
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
   
// When the data has been successfully embedded the rest of the file is copied as it is
void Data::embedRest(BMP &obj)
   {
         char c;
	     while( !obj.in.eof() )
	         {
                  obj.in.get(c);
                  obj.out.put(c);
             }
   }
   
void Data::extractLength()
   {
         length = 0;
         char c;
         unsigned char c_out = 0;
         int temp;
  
         for(int i = 0; i<4 ; i++ )
           {
             length = length << 8;
             for(int j = 0;j<8 ; j++)
                {
                    extract.get(c);
                    temp = c;
                    if(temp < 0)
                         temp += 256;
                    if( (temp & 0x01) == 1)
                      {
					     c_out=c_out<<1;
					     c_out=c_out | 1;
                      }
                    else
					     c_out=c_out<<1;
                }
             length = length | c_out;
          }
         cin.get();
   }      
   
// Retreives the Header that was extracted into the original BMP and
// Stores it in the array check[].
int Data::setHead()
   {
         char c;
         int temp, n;
         cout<<"\tEnter the name of the file from which data is to be extracted :: "<<endl<<"\t";
         cin>>fname;
         extract.open(fname, ios::binary);
         if ( !extract )
             {
                  cout<<"\tCould not open the file."<<endl;
                  return 0;
             }
         else
             {
                  // Byepassing the header as it contains no hidden information
                  for( int i=0; i<56; i++ )
                       extract.get(c);
                       
                  for(int i=0 ; i<3 ; i++ )
		             {
                       temp=0;   
			           for(int j=0;j<8;j++)
			              {
				              extract.get(c);
				              n=c;
				              if( (n & 0x01) == 1)
				                  {
					                  temp=temp<<1;
					                  temp=temp | 1;
	                              }
				              else
					                  temp=temp<<1;
			              }
			           c=(char)temp;
			           check[i]=c;
                     }           
                  check[3]='\0';
                  return 1;
             }
   }
