#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include "IMAGEclass.h"
#include "DATAclass.h"
#include "TEXTclass.h"
#include "JPEGclass.h"
#include "MP3class.h"

int main()
    {
          int choice;
          Text tobj;
          JPEG jobj;
          MP3 mobj;
          BMP bobj;
          cout<<"\n\n";
          cout<<"\t\t\tIMAGE STEGANOGRAPHY"<<endl<<endl;
          cout<<"\tDo you want to \n\t1. Embed Data\n\t2. Extract Data"<<endl;
          cout<<"\n\tEnter choice :: ";
          cin>>choice;
          system("cls");
          cout<<"\n\n";
          cout<<"\t\t\tIMAGE STEGANOGRAPHY"<<endl<<endl;
          switch(choice){
               case 1: cout<<"\t1. Embed Text.\n\t2. Embed JPEG Image.\n\t3. Embed MP3 file."<<endl;
                       cout<<"\n\tEnter choice :: ";
                       cin>>choice;
                       system("cls");
                       cout<<"\n\n";
                       cout<<"\t\t\tIMAGE STEGANOGRAPHY"<<endl<<endl;
                       if ( !bobj.getInputfile() )
                              cout<<"\tInvalid file name."<<endl;
                       else
                          {
                              if( !bobj.checkFile() )
                                    cout<<"\tNot a BMP image."<<endl;
                              else
                                {
                                    bobj.setlength();
                                    switch(choice){
                                         case 1: bobj.getOutputfile();
                                                 bobj.byepassHeader();
                                                 tobj.getData();
                                                 tobj.openStream();
                                                 tobj.embedHeader(bobj);
                                                 tobj.embedData(bobj);
                                                 tobj.embedTrailer(bobj);
                                                 tobj.embedRest(bobj);
                                                 cout<<"\n\tText successfully embedded to \"output.bmp\"."<<endl;
                                                 cout<<"\tThe file can be found in the current folder."<<endl;
                                                 break;
                                         case 2: jobj.getData();
                                                 if ( !jobj.checkFile() )
                                                      cout<<"\tNot a JPEG file."<<endl;
                                                 else
                                                    {
                                                      if ( !jobj.checkLength(bobj) )
                                                           cout<<"\tFile too large to be embedded."<<endl;
                                                      else
                                                        {
                                                           bobj.getOutputfile();
                                                           bobj.byepassHeader();
                                                           jobj.embedHeader(bobj);
                                                           jobj.embedLength(bobj);
                                                           jobj.embedData(bobj);
                                                           jobj.embedRest(bobj);
                                                           cout<<"\n\tJPEG file successfully embedded to \"output.bmp\"."<<endl;
                                                           cout<<"\tThe file can be found in the current folder."<<endl;
                                                        }
                                                    }
                                                 break;
                                         case 3: mobj.getData();
                                                 if( !mobj.checkFile() )
                                                      cout<<"\tNot a MP3 file!"<<endl;
                                                 else
                                                    {                                                                      
                                                      if( !mobj.checkLength(bobj) )
                                                           cout<<"\tFile too large to be embedded."<<endl;
                                                      else
                                                        {
                                                           bobj.getOutputfile();
                                                           bobj.byepassHeader();
                                                           mobj.embedHeader(bobj);
                                                           mobj.embedLength(bobj);
                                                           mobj.embedData(bobj);
                                                           mobj.embedRest(bobj);
                                                           cout<<"\n\tMP3 file successfully embedded to \"output.bmp\"."<<endl;
                                                           cout<<"\tThe file can be found in the current folder."<<endl;
                                                        }
                                                    }
                                                 break;
                                         default: if (choice != 1 || choice != 2 || choice != 3 )
                                                      cout<<"\tInvalid choice."<<endl;
                                                  break;
                                         }        // End of switch
                                    bobj.closefiles();
                                }        // End of else
                                }
                       break;
                       
               case 2: cout<<"\t1. Extract Text.\n\t2. Extract JPEG Image.\n\t3. Extract MP3 file."<<endl;
                       cout<<"\n\tEnter choice :: ";
                       cin>>choice;
                       system("cls");
                       cout<<"\n\n";
                       cout<<"\t\t\tIMAGE STEGANOGRAPHY"<<endl<<endl;
                       switch(choice){
                               case 1: if ( tobj.setHead() )
                                         if (  tobj.checkHead() )
                                             tobj.extractData();
                                       getch();
                                       cout<<"\n\n\tPress any key to exit...";
                                      break; 
                               case 2: if ( jobj.setHead() )
                                         if (  jobj.checkHead() )
                                            {
                                                jobj.extractLength();
                                                jobj.extractData();  
                                            }                                     
                                      break; 
                               case 3: if ( mobj.setHead() )
                                         if (  mobj.checkHead() )
                                            {
                                                mobj.extractLength();
                                                mobj.extractData();
                                            }
                                       break;
                               default: if (choice != 1 || choice != 2 || choice != 3 )
                                           cout<<"\tInvalid choice."<<endl;
                                        break; 
                               }
                       break;
               default: cout<<"\tInvalid choice entered!"<<endl;
                        break;
               }        // End of outer switch
          getch();
    }          // End of Main                                                                                         
