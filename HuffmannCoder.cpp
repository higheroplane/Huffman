
/////////////////////////////////////////////////////////////////////

#include "txlib.h"

/////////////////////////////////////////////////////////////////////

struct symbol
{
    int abc;
    int freq;
    int LeftSon;
    int RightSon;
    int Parent;
    int LR;
    string CodeName;
    string ForVoc;
};

//-------------------------------------------------------------------

void alphabet (symbol arr[], int size, int shift);

//-------------------------------------------------------------------

void readText(char texty[], int limit, FILE* txt);

//-------------------------------------------------------------------

void PrintAlphabet (symbol arr[], int size);

//-------------------------------------------------------------------

void sorting (symbol arr[], int Size);

//-------------------------------------------------------------------

int CreateTree (symbol symbols[], int Size);

//-------------------------------------------------------------------

void CreateKnot (symbol symbols[], int LeftChild, int RihgtChild, int Knot);

//-------------------------------------------------------------------

void CreateVocabluary (symbol symbols[], int AmountUsed);

//-------------------------------------------------------------------

string EncodeText (char text[], symbol symbols[], string Encoded, int used);

//-------------------------------------------------------------------

void CreateCharArray (char code[], char FinalCode[], int length, FILE* file);

//-------------------------------------------------------------------

void CreateFileVoc (symbol symbols[], int SymbolsUsed, FILE* file);

//-------------------------------------------------------------------

const int AlphabetSize = 256;
const int TextLimit = 100000;
const int AlphabetShift = 0;

/////////////////////////////////////////////////////////////////////

int main()
{
    int ArraySize = 2 * AlphabetSize + 1;
    symbol letter [2 * AlphabetSize + 1];


    alphabet(letter, ArraySize, AlphabetShift);
    printf ("alphabet initialised\n");
   // PrintAlphabet(letter, AlphabetSize);

    char text[TextLimit] = {};
    FILE* nigga = fopen ("maNiggaText.txt", "r");
    readText(text, TextLimit, nigga);


    for (int i = 0; text[i]; i ++)
    {
        letter [(unsigned char) text [i] - AlphabetShift] .freq ++;
    }

    letter [AlphabetSize] .freq ++;


    sorting (letter, AlphabetSize);

    //PrintAlphabet (letter, AlphabetSize);

    printf ("text is sorted\n");
    int Used = CreateTree (letter, AlphabetSize);
    printf ("tree is created\n");

    CreateVocabluary (letter, Used);
    string coded;

    string code = EncodeText (text, letter, coded, Used);
    int length = strlen (code.c_str());
    puts (text);
    PrintAlphabet (letter, Used + 1);
    char* Encoded = &code[0];

    puts (Encoded);

    char FinalArr [TextLimit] = {};


    FILE* Nigger = fopen ("MyNiggaText.txt", "wb");


    string bio = "GS10";
    fputs (bio.c_str(), Nigger);

    char AmountUsed[] ={};

    string SymUsed;
    SymUsed += Used + 1;
    fputs (SymUsed.c_str(), Nigger);
    puts (SymUsed.c_str());


    CreateFileVoc   (letter, Used, Nigger);




    CreateCharArray (Encoded, FinalArr, length, Nigger);
    puts (FinalArr);


    assert (nigga);
    fclose (nigga);

    assert (Nigger);
    fclose (Nigger);

    printf("Encoded succesfully\n");

    return 0;
}


/////////////////////////////////////////////////////////////////////


void alphabet (symbol arr[], int size, int shift)
{
    for(int i = 0; i < size; i++)
    {
        arr[i].abc = i + shift;
        arr[i].freq = 0;
        arr[i].LeftSon = 0;
        arr[i].RightSon = 0;
        arr[i].Parent = 0;
        arr[i].LR = 0;

        //printf ("[%d] <%c>\n", i, alp[i]);
    }


}

//-------------------------------------------------------------------

void readText(char texty[], int limit, FILE* txt)
{
    fgets (texty, limit, txt);
    puts (texty);
}

//-------------------------------------------------------------------

void PrintAlphabet (symbol arr[], int size)
{
    for (int i = 0; i < size; i ++)
    {
        printf ("[%3d] = <%3c> <%3d> LS = <%3d> RS = <%3d> Parent = <%3d> LR = <%d> Code Name = <%s>\n",
                 i, arr[i].abc, arr[i].freq, arr[i].LeftSon, arr[i].RightSon,
                  arr[i].Parent, arr[i] .LR, arr[i].CodeName.c_str());

    }


    for (int i = size; i < size * 2 + 1; i ++)
    {
        printf ("[%3d] = <%3d> <%3d> LS = <%3d> RS = <%3d> Parent = <%3d> LR = <%d>\n",
                 i, arr[i].abc - AlphabetShift, arr[i].freq, arr[i].LeftSon - AlphabetShift,
                  arr[i].RightSon - AlphabetShift, arr[i].Parent - AlphabetShift, arr[i] .LR);

    }
}

//-------------------------------------------------------------------

void sorting (symbol arr[], int Size)
{
    symbol spinoff = {};
    for (int i = 0; i <= Size; i ++)
    {
        for (int j = 0; j <= Size - i; j ++)
        {
            if (arr[j].freq < arr[j + 1].freq)
            {
                spinoff = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = spinoff;
            }
        }
    }
}

//-------------------------------------------------------------------


int CreateTree (symbol symbols[], int Size)
{
    int ActiveSymbol = -1;
    int CurrentEnd = Size + 1;
    int LastKnot = CurrentEnd;

    #define KNOT_ LastKnot

    for (int i = 0; symbols[i].freq != 0; i++)
    {
        ActiveSymbol ++;
    }

    int SymbolsUsed = ActiveSymbol;


    CreateKnot (symbols, ActiveSymbol, ActiveSymbol - 1, KNOT_);
    ActiveSymbol -= 2;
    LastKnot ++;

    //printf ("1st knot is created\n");

    if(ActiveSymbol == 0)
    {
        CreateKnot (symbols, ActiveSymbol, CurrentEnd, KNOT_);
        ActiveSymbol --;
    }
    else
    {
    if (symbols [CurrentEnd]      .freq <
        symbols [ActiveSymbol - 1] .freq)
    {
        CreateKnot (symbols, ActiveSymbol, CurrentEnd, KNOT_);


        ActiveSymbol -= 1;
        CurrentEnd++;
    }
    else
    {
        CreateKnot (symbols, ActiveSymbol, ActiveSymbol - 1, KNOT_);


        ActiveSymbol -= 2;
    }
    }
    LastKnot ++;

    //printf ("2nd knot is created\n");

    for (int i = 0; ActiveSymbol >= 0; i++)
    {
        if(ActiveSymbol == 0)
        {
        CreateKnot (symbols, ActiveSymbol, CurrentEnd, KNOT_);

        CurrentEnd ++;
        ActiveSymbol -= 1;
        }
        else
        {
        if (symbols [CurrentEnd]  .freq <
            symbols [ActiveSymbol] .freq)
        {
            if (symbols [ActiveSymbol]    .freq <
                symbols [CurrentEnd + 1] .freq ||
                symbols [CurrentEnd+1]   .freq  == 0)
                {
                    CreateKnot (symbols, ActiveSymbol, CurrentEnd, KNOT_);


                    ActiveSymbol -= 1;
                    CurrentEnd ++;
                }
                else
                {
                   {
                    CreateKnot (symbols, CurrentEnd, CurrentEnd + 1, KNOT_);


                    CurrentEnd += 2;
                }
                }
        }
        else
        {
            if (symbols [CurrentEnd]      .freq <
                symbols [ActiveSymbol - 1] .freq)
                {
                    CreateKnot (symbols, ActiveSymbol, CurrentEnd, KNOT_);


                    ActiveSymbol -= 1;
                    CurrentEnd ++;
                }
                else
                {

                    CreateKnot (symbols, ActiveSymbol, ActiveSymbol - 1, KNOT_);
                    ActiveSymbol -= 2;
                }
        }

        }
        LastKnot ++;

       // printf ("%dth knot is created\n", i+2);
    }


    for (int i = 0; CurrentEnd < LastKnot - 1; i++)
        {
            printf("%d\n", i);


            CreateKnot (symbols, CurrentEnd, CurrentEnd + 1, KNOT_);
            CurrentEnd += 2;
            LastKnot ++;
        }


    #undef KNOT_
    return SymbolsUsed;
    printf ("tree was created\n");
}

//-------------------------------------------------------------------

void CreateKnot (symbol symbols[], int LeftChild, int RightChild, int Knot)
{
        symbols [Knot] .freq   = symbols [LeftChild]  .freq +
                                     symbols [RightChild] .freq;


        symbols [Knot] .LeftSon  = symbols [LeftChild]  .abc;
        symbols [Knot] .RightSon = symbols [RightChild] .abc;


        symbols [LeftChild]  .Parent = symbols [Knot] .abc;
        symbols [LeftChild]  .LR = 1;
        symbols [RightChild] .Parent = symbols [Knot] .abc;
        symbols [RightChild] .LR = 0;
}

//-------------------------------------------------------------------

void CreateVocabluary (symbol symbols[], int AmountUsed)
{
   int CurrentSymbol = 0;


   for (int i = 0; i <= AmountUsed; i++)
   {
      CurrentSymbol = i;


      for (int j = 0; symbols [CurrentSymbol] .Parent; j++)
      {
             assert (i >= 0 && i < AlphabetSize *2 + 1);
             assert (j >= 0 && j < AlphabetSize *2 + 1);


             symbols [i] .CodeName += symbols [CurrentSymbol] .LR + '0';
             CurrentSymbol = symbols [CurrentSymbol] .Parent - AlphabetShift;
      }
   }

   for (int i = 0; i <= AmountUsed; i++)
   symbols [i] .CodeName = string (symbols [i] .CodeName.rbegin(), symbols [i] .CodeName.rend());

}

//-------------------------------------------------------------------

string EncodeText (char text[], symbol symbols[], string Encoded, int used)
{
    bool stop = true;


    for (int i = 0; text[i]; i++)
    {
        stop = true;
        for (int j = 0; stop; j++)
        {

          if ((unsigned char)text[i] == symbols [j]. abc)
          {
                assert (j >= 0 && j < AlphabetSize *2 +1);
                assert (i >= 0 && i < TextLimit);



                printf ("%c is %s\n", symbols [j] .abc,
                                      symbols [j] .CodeName.c_str());
                Encoded += symbols[j] .CodeName;
                stop = false;
          }
        }
    }

    printf ("%c is %s\n", symbols [used] .abc,
                          symbols [used] .CodeName.c_str());
    Encoded += symbols[used] .CodeName;


    printf ("encoding finished\n");
    return Encoded;
}

//-------------------------------------------------------------------

void CreateCharArray (char code[], char FinalCode[], int length, FILE* file)
{
    int counter = 0;

    printf ("length is <%d>\n", length);

    int BytesAmount = 0;

    if (length % 8 == 0)
        BytesAmount = length/8;
    else
        BytesAmount = length/8 + 1;

    printf ("\n%d\n", BytesAmount);

    for (int i = 0; i < BytesAmount; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            //assert (i >= 0 && i < AlphabetSize *2 +1);
            if (counter <= length)
            {
            if (code [counter] == '1')
            FinalCode[i] = (FinalCode[i] * 2) + 1;
            else
            FinalCode[i] *= 2;
            //assert (i >= 0 && i < AlphabetSize *2 +1);
            // printf ("<%d>\n", counter);
            }
            else
            FinalCode[i] *= 2;

            counter ++;
        }

        putc (FinalCode[i], file);
        printf ("[%c]\n", (unsigned char)FinalCode[i]);
    }

    printf ("array created\n");
    puts (FinalCode);

}

//-------------------------------------------------------------------

void CreateFileVoc (symbol symbols[], int SymbolsUsed, FILE* file)
{
    char CharCode [AlphabetSize] = {};


    for (int i = 0; i < SymbolsUsed; i++)
    {
        assert (i >= 0 && i < AlphabetSize *2 + 1);
        symbols [i] .ForVoc =  symbols [i] .abc;
        //symbols [i] .ForVoc += '|';
        symbols [i] .ForVoc += strlen (symbols [i] .CodeName .c_str());
        //symbols [i] .ForVoc += '|';
//        Name = &symbols [i] .CodeName[0];

        //fwrite (symbols [i] .ForVoc.c_str(), sizeof(char), sizeof(symbols [i] .ForVoc.c_str()), file);
         fputs (symbols [i] .ForVoc.c_str(), file);
         puts (symbols [i] .ForVoc.c_str()      );
    }



    symbols [SymbolsUsed] .ForVoc += strlen (symbols [SymbolsUsed] .CodeName .c_str());
    fputs (symbols [SymbolsUsed] .ForVoc.c_str(), file);

    string Name = symbols [0] .CodeName;

    for (int i = 1; i <= SymbolsUsed; i++)
    {
        Name += symbols [i] .CodeName;
    }

    //string check = "|";
    //fputs (check.c_str(), file);
    char* BinAlph = &Name[0];
    printf ("!/\n%d\n", strlen (BinAlph));
    puts (BinAlph);
    printf ("!/\n\n");
    CreateCharArray (BinAlph, CharCode, strlen (BinAlph), file);
    puts (CharCode);
    //fwrite (CharCode, sizeof(char), sizeof(CharCode), file);
    //fputs (CharCode, file);

     //puts (check.c_str());
}

/////////////////////////////////////////////////////////////////////

