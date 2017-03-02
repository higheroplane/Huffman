/////////////////////////////////////////////////////////////////////

#include "txlib.h"

#include "io.h"

/////////////////////////////////////////////////////////////////////

struct symbol
{
    char abc;
    string CodeName;
    char CodeLength;
};

//-------------------------------------------------------------------

void readText(char texty[], int limit, FILE* txt);

//-------------------------------------------------------------------

int GetAmountUsed (char texty[]);

//-------------------------------------------------------------------

string GetCodeNames (FILE* txt, char texty[], symbol symbols[], int SymbolsUsed);

//-------------------------------------------------------------------

string BitsToString (char texty[], int Bytes, int Bits, int SymbolsUsed, int Shift);

//-------------------------------------------------------------------

string ByteToString (char Sym);

//-------------------------------------------------------------------

string CodeToText (FILE* txt, char texty[], symbol symbols[], int SymbolsUsed, int Bytes);

//-------------------------------------------------------------------

const int AlphabetSize = 255;
const int TextLimit = 100000;

/////////////////////////////////////////////////////////////////////

int main()
{
    char text[TextLimit] = {};
    FILE* nigga = fopen ("MyNiggaText.txt", "rb");
    readText(text, TextLimit, nigga);

    int AmountUsed = GetAmountUsed (text) - 1;


    symbol letter [AlphabetSize + 1];

    string DecodedText = GetCodeNames (nigga, text, letter, AmountUsed);

    FILE* Nigger = fopen ("DisarmedNigger.txt", "w");
    fputs (DecodedText.c_str(), Nigger);

    fclose (Nigger);
    fclose(nigga);

    return 0;
}

/////////////////////////////////////////////////////////////////////

void readText(char texty[], int limit, FILE* txt)
{
    //for (int i = 0; i < ftell (txt); i++)
        fread (texty, 1, filelength (fileno (txt)), txt);
    //fgets (texty, limit, txt);
        for (int i = 0; i < filelength (fileno (txt)); i++)
            printf ("%c", texty [i]);

        printf ("\n");
}

//-------------------------------------------------------------------

int GetAmountUsed (char texty[])
{
    int lol = texty [4];
    printf ("%d symbols used\n", lol);
    return lol;
}

//-------------------------------------------------------------------

string GetCodeNames (FILE* txt, char texty[], symbol symbols[], int SymbolsUsed)
{
    for (int i = 0; i < SymbolsUsed; i ++)
    {
       symbols [i] .CodeLength = texty [i * 2 + 6];
       symbols [i] .abc        = texty [i * 2 + 5];
       printf ("abc = [%c] len = <%d>\n", symbols [i] .abc,  symbols [i] .CodeLength);
    }


    symbols [SymbolsUsed] .CodeLength = texty [SymbolsUsed * 2 + 5];
    printf ("End       len = <%d>\n", symbols [SymbolsUsed] .CodeLength);

    int BytesUsed = 0;
    int BitsUsed  = 0;
    assert (texty);
    assert (symbols);
    for (int i = 0 ; i <= SymbolsUsed + 1; i++)
    {
        assert (symbols);

        assert (i >= 0 && i < AlphabetSize + 1);
        BitsUsed += symbols [i] .CodeLength;
    }

    printf ("%d bits used\n", BitsUsed);

    if (BitsUsed % 8 == 0)
    BytesUsed = BitsUsed / 8 ;
    else
    BytesUsed = BitsUsed / 8 + 1;

    printf ("%d bytes used\n", BytesUsed);
    //assert (BitsToString (texty, BytesUsed, BitsUsed, SymbolsUsed));
    string Voc = BitsToString (texty, BytesUsed, BitsUsed, SymbolsUsed, SymbolsUsed * 2 + 6);

    char* BinAlph = &Voc[0];
    char Transport [AlphabetSize] = {};


    for(int i = 0, Current = 0; i <= SymbolsUsed; i ++)
    {
          memset (Transport, 0, sizeof(Transport));
          for (int j = 0; j < symbols[i] .CodeLength; j ++)
          {
              Transport [j] = BinAlph [j + Current];
          }

          Current += symbols[i] .CodeLength;
          symbols[i] .CodeName += Transport;
          puts (Transport);
    }

    string Final = CodeToText (txt,texty, symbols, SymbolsUsed, BytesUsed);
    return Final;

}

//-------------------------------------------------------------------

string BitsToString (char texty[], int Bytes, int Bits, int SymbolsUsed, int Shift)
{
    string STR;


    for (int i = Shift; i < Shift + Bytes; i ++)
        STR += ByteToString (texty[i]);

    puts (STR.c_str());

    return STR;
}

//-------------------------------------------------------------------

string ByteToString (char Sym)
{
    string Code;

    unsigned char Symbol = (unsigned char)Sym;

    for(int i = 0; i < 8; i ++)
    {
        if (Symbol % 2 == 0)
        Code += '0';
        else
        Code += '1';

        Symbol /=2;
    }

    Code = string (Code.rbegin(), Code.rend());

    puts (Code.c_str());

    return Code;
}

//-------------------------------------------------------------------

string CodeToText (FILE* txt, char texty[], symbol symbols[], int SymbolsUsed, int Bytes)
{
    int BytesUsed = filelength (fileno (txt)) - (6 + SymbolsUsed * 2 + Bytes);


    printf ("%d bytes used\n", BytesUsed);
    //assert (BitsToString (texty, BytesUsed, BitsUsed, SymbolsUsed));
    string Voc = BitsToString (texty, BytesUsed, BytesUsed * 8, SymbolsUsed, SymbolsUsed * 2 + 6 + Bytes);
    puts (Voc.c_str());
    char* EncodedText = &Voc[0];
    puts (EncodedText);


    bool stop = true;
    bool pause = true;
    int Current = 0;
    string transport;
    char zero[1] = {};
    string FinalText;

    for (int i = 0; stop; i ++)
    {

        assert (i < strlen (EncodedText));

        pause = true;
        for (int j = 0; pause; j ++)
        {
            //delete []transport; // Именно с [] по стандарту.
            transport = zero;

            assert (j < AlphabetSize);

            for (int h = Current; h < symbols[j] .CodeLength + Current; h++)
            {
                     printf ("%c", EncodedText[h]);
                     transport += EncodedText[h];
            }
            printf("\n\n");

            puts (transport.c_str());


            if (transport == symbols [j] .CodeName)
            {

                if (j == SymbolsUsed)
                {
                    printf ("stopped");
                    stop = false;
                    break;
                }
                FinalText += symbols[j].abc;
                printf ("\n%d is %c\n", i, symbols[j].abc);
                pause = false;
                Current += symbols[j] .CodeLength;
            }
        }
    }

    puts (FinalText.c_str());
    return FinalText;
}

//-------------------------------------------------------------------



/////////////////////////////////////////////////////////////////////
