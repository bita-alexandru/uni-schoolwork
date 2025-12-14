#include <iostream>
#include <fstream>
#include <winbgim.h>
#include <time.h>
#include <math.h>
#include <SFML/Audio.hpp>
using namespace std;

#define LUNGIME 1632
#define LATIME 960
#define LATURA 96

#define JUCATOR1 1
#define JUCATOR2 2
#define POSIBIL 3
#define CULOARE_POSIBIL LIGHTGREEN

#define MARGINE_V 108
#define MARGINE_O 420

#define LEN 50

#define ZI 0
#define NOAPTE 1

#define RO 0
#define EN 1

#define PORNIT 0
#define OPRIT 1

#define COORD1(x) x[limba][0], x[limba][1], x[limba][2], x[limba][3] // ast e pt imagini
#define COORD2(x) x[0], x[1] // asta e pt text
#define STERGE(x) x[limba][0], x[limba][1], x[limba][2]+1, x[limba][3]+1 // pt bar()

#define debug(x,y) cout<<x<<' '<<y<<'\n';
// locatii fisiere[mod][limba][2] + pozitii butoane[limba][4]

// butoane muzica+credits
const char imgMuzica[2][2][LEN] = {"img/muzicaD1.jpg", "img/muzicaD2.jpg", "img/muzicaN1.jpg", "img/muzicaN2.jpg"};
const char imgSfx[2][2][LEN] = {"img/sfxD1.jpg", "img/sfxD2.jpg", "img/sfxN1.jpg", "img/sfxN2.jpg"};
const char imgCredit[2][2][LEN] = {"img/creditDRO.jpg", "img/creditDEN.jpg", "img/creditNRO.jpg", "img/creditNEN.jpg"};
const char imgInfo[2][2][LEN] = {"img/infoDRO.jpg", "img/infoDEN.jpg", "img/infoNRO.jpg", "img/infoNEN.jpg"};
const int pozMuzica[2][4] = {24, 24, 55, 55, 24, 24, 55, 55};
const int pozSfx[2][4] = {80, 24, 111, 55, 80, 24, 111, 55};
const int pozCredit[2][4] = {1512, 24, 1608, 48, 1512, 24, 1608, 48};

// setari meniu principal
const char imgSoare[2][LEN] = {"img/soareD.jpg", "img/soareN.jpg"};
const char imgLuna[2][LEN] = {"img/lunaD.jpg", "img/lunaN.jpg"};
const char imgRo[2][2][LEN] = {"img/roN.jpg", "img/roD.jpg", "img/roD.jpg", "img/roN.jpg"};
const char imgEn[2][2][LEN] = {"img/enD.jpg", "img/enN.jpg", "img/enN.jpg", "img/enD.jpg"};
const int pozSoare[2][4] = {24, 816, 72, 864, 24, 816, 72, 864};
const int pozLuna[2][4] = {24, 888, 72, 936, 24, 888, 72, 936};
const int pozRo[2][4] = {1488, 888, 1536, 936, 1488, 888, 1536, 936};
const int pozEn[2][4] = {1560, 888, 1608, 936, 1560, 888, 1608, 936};

// butoane meniu principal
const char imgTitlu[2][2][LEN] = {"img/titluDRO.jpg", "img/titluDEN.jpg", "img/titluNRO.jpg", "img/titluNEN.jpg"};
const char imgJocNou[2][2][LEN] = {"img/jocnouDRO.jpg", "img/jocnouDEN.jpg", "img/jocnouNRO.jpg", "img/jocnouNEN.jpg"};
const char imgTutorial[2][2][LEN] = {"img/tutorialDRO.jpg", "img/tutorialDEN.jpg", "img/tutorialNRO.jpg", "img/tutorialNEN.jpg"};
const char imgSetari[2][2][LEN] = {"img/setariDRO.jpg", "img/setariDEN.jpg", "img/setariNRO.jpg", "img/setariNEN.jpg"};
const char imgIesire[2][2][LEN] = {"img/iesireDRO.jpg", "img/iesireDEN.jpg", "img/iesireNRO.jpg", "img/iesireNEN.jpg"};
const int pozTitlu[2][4] = {288, 120, 1344, 216, 288, 120, 1344, 216};
const int pozJocNou[2][4] = {672, 312, 960, 408, 648, 312, 984, 408};
const int pozTutorial[2][4] = {600, 432, 1032, 528, 624, 432, 1008, 528};
const int pozSetari[2][4] = {720, 552, 912, 648, 696, 552, 936, 648};
const int pozIesire[2][4] = {696, 672, 936, 768, 744, 672, 888, 768};

// buton inapoi + butoane meniu Joc Nou
const char imgInapoi[2][LEN] = {"img/inapoiD.jpg", "img/inapoiN.jpg"};
const char imgPVP[2][2][LEN] = {"img/pvpDRO.jpg", "img/pvpDEN.jpg", "img/pvpNRO.jpg", "img/pvpNEN.jpg"};
const char imgPVIA[2][2][LEN] = {"img/pviaDRO.jpg", "img/pviaDEN.jpg", "img/pviaNRO.jpg", "img/pviaNEN.jpg"};
const char imgReluare[2][2][LEN] = {"img/reluareDRO.jpg", "img/reluareDEN.jpg", "img/reluareNRO.jpg", "img/reluareNEN.jpg"};
const char imgOptiuni[2][2][LEN] = {"img/optiuniDRO.jpg", "img/optiuniDEN.jpg", "img/optiuniNRO.jpg", "img/optiuniNEN.jpg"};
const int pozInapoi[2][4] = {1512, 24, 1608, 72, 1512, 24, 1608, 72};
const int pozPVP[2][4] = {576, 288, 1056, 384, 600, 288, 1032, 384};
const int pozPVIA[2][4] = {624, 408, 1008, 504, 648, 408, 984, 504};
const int pozReluare[2][4] = {696, 528, 936, 624, 696, 528, 936, 624};
const int pozOptiuni[2][4] = {72, 768, 1560, 811, 72, 768, 1560, 811};

// butoane <Selectie> Joc Nou
const char imgSageataL[2][LEN] = {"img/sageatalD.jpg", "img/sageatalN.jpg"};
const char imgSageataR[2][LEN] = {"img/sageatarD.jpg", "img/sageatarN.jpg"};
const int pozS1[2] = {240, 840+10};
const int pozS1a[2][4] = {216-72, 816, 264-72, 864, 216-72, 816, 264-72, 864};
const int pozS1b[2][4] = {216+72, 816, 264+72, 864, 216+72, 816, 264+72, 864};
const int pozS2[2] = {816, 840+10};
const int pozS2a[2][4] = {792-72, 816, 840-72, 864, 792-72, 816, 840-72, 864};
const int pozS2b[2][4] = {792+72, 816, 840+72, 864, 792+72, 816, 840+72, 864};
const int pozS3[2] = {1392, 840+10};
const int pozS3a[2][4] = {1368-72, 816, 1416-72, 864, 1368-72, 816, 1416-72, 864};
const int pozS3b[2][4] = {1368+72, 816, 1416+72, 864, 1368+72, 816, 1416+72, 864};

// imagini In Joc + butoane informative/abandon
const char imgTabla[2][3][LEN] = {"img/tabla1.jpg", "img/tabla2.jpg", "img/tabla3.jpg", "img/tabla1p.jpg", "img/tabla2p.jpg", "img/tabla3p.jpg"};
const char imgPatrat[3][LEN] = {"img/patrat1.jpg", "img/patrat2.jpg","img/patrat3.jpg"};
const char imgPiesaA[3][LEN] = {"img/piesaA1.gif", "img/piesaA2.gif", "img/piesaA3.gif"};
const char imgPiesaB[3][LEN] = {"img/piesaB1.gif", "img/piesaB2.gif", "img/piesaB3.gif"};
const char imgAbandon[2][2][LEN] = {"img/abandonDRO.jpg", "img/abandonDEN.jpg", "img/abandonNRO.jpg", "img/abandonNEN.jpg"};
const int pozRand1[2] = {93, 364}, pozRand2[2] = {325, 599}, pozScor[2] = {210, 482};
const int pozPiesaA[2][4] = {36, 384, 131, 479, 36, 384, 131, 479};
const int pozPiesaB[2][4] = {288, 480, 383, 575, 288, 480, 383, 575};
const int pozTabla[2][4] = {408, 96, 1200, 888, 408, 96, 1200, 888};
const int pozIstoric[2][4] = {1248, 240, 1608, 822, 1248, 240, 1608, 822};
const int pozRamase[2] = {203, 853}, pozTimer[2] = {1430, 163};
const int pozAbandon[2][4] = {1368, 840, 1488, 864, 1368, 840, 1488, 864};

// butoane informative + meniu Sfarsit Joc
const char imgIstoric[2][LEN] = {"img/istoricD.jpg", "img/istoricN.jpg"};
const char imgEgal[2][2][LEN] = {"img/egalDRO.jpg", "img/egalDEN.jpg", "img/egalNRO.jpg", "img/egalNEN.jpg"};
const char imgVictorie[2][2][LEN] = {"img/victorieDRO.jpg", "img/victorieDEN.jpg", "img/victorieNRO.jpg", "img/victorieNEN.jpg"};
const char imgSfarsit[2][LEN] = {"img/sfarsitD.jpg", "img/sfarsitN.jpg"};
const char imgRestart[2][LEN] = {"img/restartD.jpg", "img/restartN.jpg"};
const char imgSalveaza[2][2][LEN] = {"img/salveazaDRO.jpg", "img/salveazaDEN.jpg", "img/salveazaNRO.jpg", "img/salveazaNEN.jpg"};
const char imgSalvat[2][2][LEN] = {"img/salvatDRO.jpg", "img/salvatDEN.jpg", "img/salvatNRO.jpg", "img/salvatNEN.jpg"};
const char imgLaMeniu[2][2][LEN] = {"img/lameniuDRO.jpg", "img/lameniuDEN.jpg", "img/lameniuNRO.jpg", "img/lameniuNEN.jpg"};
const int pozRezultat[2][4] = {528, 216, 1104, 360, 528, 216, 1104, 360};
const int pozSfarsit[2][4] = {528, 408, 1104, 744, 528, 408, 1104, 744};
const int pozRestart[2][4] = {696, 432, 936, 528, 696, 432, 936, 528};
const int pozSalveaza[2][4] = {576, 528, 1056, 624, 576, 528, 1056, 624};
const int pozLaMeniu[2][4] = {576, 624, 1056, 720, 576+24, 624, 1056-24, 720};

// butoane Cum Se Joaca + imagini ghid
const char imgTut1[2][2][LEN] = {"img/tut1DRO.jpg", "img/tut1DEN.jpg", "img/tut1NRO.jpg", "img/tut1NEN.jpg"};
const char imgTut2[2][2][LEN] = {"img/tut2DRO.jpg", "img/tut2DEN.jpg", "img/tut2NRO.jpg", "img/tut2NEN.jpg"};
const char imgTut3[2][2][LEN] = {"img/tut3DRO.jpg", "img/tut3DEN.jpg", "img/tut3NRO.jpg", "img/tut3NEN.jpg"};
const char imgTut4[2][2][LEN] = {"img/tut4DRO.jpg", "img/tut4DEN.jpg", "img/tut4NRO.jpg", "img/tut4NEN.jpg"};
const char imgTut5[2][2][LEN] = {"img/tut5DRO.jpg", "img/tut5DEN.jpg", "img/tut5NRO.jpg", "img/tut5NEN.jpg"};
const char imgGhid1[2][2][LEN] = {"img/ghid1DRO.jpg", "img/ghid1DEN.jpg", "img/ghid1NRO.jpg", "img/ghid1NEN.jpg"};
const char imgGhid2[2][2][LEN] = {"img/ghid2DRO.jpg", "img/ghid2DEN.jpg", "img/ghid2NRO.jpg", "img/ghid2NEN.jpg"};
const char imgGhid3[2][2][LEN] = {"img/ghid3DRO.jpg", "img/ghid3DEN.jpg", "img/ghid3NRO.jpg", "img/ghid3NEN.jpg"};
const char imgGhid4[2][2][LEN] = {"img/ghid4DRO.jpg", "img/ghid4DEN.jpg", "img/ghid4NRO.jpg", "img/ghid4NEN.jpg"};
const char imgGhid5[2][2][LEN] = {"img/ghid5DRO.jpg", "img/ghid5DEN.jpg", "img/ghid5NRO.jpg", "img/ghid5NEN.jpg"};
const int pozTut1[2][4] = {48, 168, 288, 264, 48, 168, 288, 264};
const int pozTut2[2][4] = {96, 312, 360, 408, 96, 312, 360, 408};
const int pozTut3[2][4] = {96, 456, 384, 552, 96, 456, 384, 552};
const int pozTut4[2][4] = {96, 600, 432, 696, 96, 600, 432, 696};
const int pozTut5[2][4] = {48, 744, 312, 840, 48, 744, 264, 840};
const int pozGhid[2][4] = {576, 192, 1632, 768, 576, 192, 1632, 768};

// butoane <selectie> Aspect + text in Setari
const char imgAspect[2][2][LEN] = {"img/aspectDRO.jpg", "img/aspectDEN.jpg", "img/aspectNRO.jpg", "img/aspectNEN.jpg"};
const int pozAspect[2][4] = {48, 96, 1440, 600, 48, 96, 1440, 600};
const int pozA1[2][4] = {240, 336, 335, 431, 240, 336, 335, 431};
const int pozA1a[2][4] = {168, 336+24, 216, 432-24, 168, 336+24, 216, 432-24};
const int pozA1b[2][4] = {360, 336+24, 408, 432-24, 360, 336+24, 408, 432-24};
const int pozA2[2][4] = {240, 600, 335, 695, 240, 600, 335, 695};
const int pozA2a[2][4] = {168, 600+24, 216, 696-24, 168, 600+24, 216, 696-24};
const int pozA2b[2][4] = {360, 600+24, 408, 696-24, 360, 600+24, 408, 696-24};
const int pozA3[2][4] = {768, 192, 1439, 863, 768, 192, 1439, 863};
const int pozA3a[2][4] = {696, 504, 744, 552, 696, 504, 744, 552};
const int pozA3b[2][4] = {1464, 504, 1512, 552, 1464, 504, 1512, 552};
const int pozInfo[2][4] = {384, 192, 1248, 768, 384, 192, 1248, 768};

// iconite
const char imgJoystick[2][LEN] = {"img/joystickD.jpg", "img/joystickN.jpg"};
const char imgCarte[2][LEN] = {"img/carteD.jpg", "img/carteN.jpg"};
const char imgRotita[2][LEN] = {"img/rotitaD.jpg", "img/rotitaN.jpg"};
const char imgX[2][LEN] = {"img/xD.jpg", "img/xN.jpg"};
const char imgOm[2][LEN] = {"img/omD.jpg", "img/omN.jpg"};
const char imgOchi[2][LEN] = {"img/ochiD.jpg", "img/ochiN.jpg"};
const char imgReplay[2][LEN] = {"img/replayD.jpg", "img/replayN.jpg"};
const int pozJoystick[2][4] = {1008, 342, 1055, 390, 1008+24, 342, 1055+24, 390};
const int pozCarte[2][4] = {1080, 460, 1128, 508, 1080-24, 461, 1128-24, 508};
const int pozRotita[2][4] = {960, 576, 1007, 624, 960+24, 576, 1007+24, 624};
const int pozX[2][4] = {984, 696, 1031, 743, 984-48, 696, 1031-48, 743};
const int pozOm[2][4] = {1080+24, 312, 1128+23, 360, 1080, 312, 1127, 360};
const int pozOchi[2][4] = {1032+24, 432, 1080+23, 480, 1032, 432, 1079, 480};
const int pozReplay[2][4] = {984, 552, 1032, 599, 984, 552, 1032, 599};

// muzica si efecte sonore
sf::Music muzicaFundal;
sf::SoundBuffer bufferHover, bufferZi, bufferNoapte, bufferInainte, bufferInapoi, bufferSchimba, bufferVictorie, bufferEgal;
sf::Sound sunetHover, sunetZi, sunetNoapte, sunetInainte, sunetInapoi, sunetSchimba, sunetVictorie, sunetEgal;
const char sunetHit[6][LEN] = {"audio/hit1.wav", "audio/hit2.wav", "audio/hit3.wav", "audio/hit4.wav", "audio/hit5.wav", "audio/hit6.wav"};

// date joc
int tabla[8][8], nr_mutari, nr_timp, nr_safe;
int scor_j1, scor_j2, timp_limita, mutari_ramase, castigator;
bool timp_expirat, joc_terminat;
char txt_infoP1[2][LEN], txt_infoP2[2][LEN], txt_infoMutari[2][LEN], txt_infoTimer[LEN];
int pozMutare[2]; // info
char txt_mutare[LEN], txt_logs[101][LEN]; // istoric mutari
struct pieseAI {int linie, coloana, status;} ai[8];
int sizeAI, index_ai;

// estetica jocului
int aspect_j1, aspect_j2, aspect_tabla;
int mod, limba, fundal, mod_muzica, mod_sfx;

void Meniu();//Marian+Alex
void JocNou();//Marian+Alex
void Tutorial();//Marian+Alex
void Setari();//Alex+Marian
void Credits();//Marian
void PVP();//Alex
void PVIA();//Alex
void Reluare();//Alex
void Sfarsit(int,int);//Alex
void Restart(int);//Alex
void Salveaza();//Alex

char* itoa(int nr, char b[]) // converteste un nr in char*   Marian
{
    char const cifre[] = "0123456789";
    char* p = b;
    if(nr < 0)
    {
        *p++ = '-';
        nr *= -1;
    }

    int aux = nr;
    do
    {
        ++p;
        aux = aux/10;
    }while(aux);

    *p = '\0';
    do
    {
        *--p = cifre[nr%10];
        nr = nr/10;
    }while(nr);

    return b;
}

bool esteDeasupra(int x, int y, const int poz[2][4])
{
    return x >= poz[limba][0] && x <= poz[limba][2] && y >= poz[limba][1] && y <= poz[limba][3];
}

void initializareTabla(int cod=0) // 0 = razboi in 8, 1 = razboi in 4    Marian
{
    // goleste bufferul
    while (kbhit()) getch();
    clearmouseclick(WM_MBUTTONDOWN);
    clearmouseclick(WM_MBUTTONDBLCLK);

    // deseneaza tabla
    readimagefile(imgTabla[0][aspect_tabla], COORD1(pozTabla));

    // resetare scoruri
	scor_j1 = scor_j2 = 0;

    for(int i = 0; i < 8; i++)
        if(i%2 == 1)
        {
            // jucator negru
            tabla[0][i] = JUCATOR2;
            tabla[1][i] = 0;

            // jucator alb
            tabla[6][i] = JUCATOR1;
            tabla[7][i] = 0;
        }
        else
        {
            // jucator negru
            tabla[0][i] = 0;
            tabla[1][i] = JUCATOR2;

            // jucator alb
            tabla[6][i] = 0;
            tabla[7][i] = JUCATOR1;
        }

    for(int i = 2; i < 6; i++)
        for(int j = 0; j < 8; j++) tabla[i][j] = 0; // zone libere

    if(cod == 0 && nr_safe == 0) // razboi in 4 live
        for(int i = 0; i < 8; i++) tabla[1][i] = tabla[6][i] = 0;
    else if(cod == 1) // razboi in 4 replay
        for(int i = 0; i < 8; i++) tabla[1][i] = tabla[6][i] = 0;

    sizeAI = 0;
    // piese ai
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 8; j++)
            if(tabla[i][j] == JUCATOR2)
            {
                ai[sizeAI].linie = i;
                ai[sizeAI].coloana = j;
                ai[sizeAI].status = 1;
                sizeAI++;
            }

    //deseneaza piese
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
        {
            int x1, y1, x2, y2;
            x1 = j*LATURA + MARGINE_O;
            y1 = i*LATURA + MARGINE_V;

            x2 = (j+1)*LATURA + MARGINE_O;
            y2 = (i+1)*LATURA + MARGINE_V;

            if(tabla[i][j] == JUCATOR2) readimagefile(imgPiesaB[aspect_j2], x1+12, y1+12, x2-12, y2-12);
            else if(tabla[i][j] == JUCATOR1) readimagefile(imgPiesaA[aspect_j1], x1+12, y1+12, x2-12, y2-12);
        }
}

int turaJucator()
{
    return mutari_ramase%2 + 1;
}

bool esteInauntru(int linie, int coloana)
{
    return linie >= 0 && linie < 8 && coloana >= 0 && coloana < 8;
}

bool esteBlocat(int linie, int coloana)//Alex
{
    int di[4] = {-1,-1,1,1}, dj[4] = {-1,1,-1,1};
    int blocaje = 0;

    // numara cate piese se gasesc in vecinatate
    for(int d = 0; d < 4; d++)
    {
        int i = linie + di[d];
        int j = coloana + dj[d];

        if(i < 0 || i >= 8 || j < 0 || j >= 8 || tabla[i][j] != 0) blocaje++;
    }

    return blocaje == 4;
}

int nrBlocaje(int linie, int coloana)//Alex
{
    int di[4] = {-1,-1,1,1}, dj[4] = {-1,1,-1,1};
    int blocaje = 0;

    // numara cate piese se gasesc in vecinatate
    for(int d = 0; d < 4; d++)
    {
        int i = linie + di[d];
        int j = coloana + dj[d];

        if(i < 0 || i >= 8 || j < 0 || j >= 8 || tabla[i][j] != 0) blocaje++;
    }

    return blocaje;
}

void determinaPozitie(int &linie, int &coloana)//Marian
{
    int x, y;
    x = mousex();
    y = mousey();

    linie = floor((1.0*y-MARGINE_V)/LATURA);
    coloana = floor((1.0*x-MARGINE_O)/LATURA);
}

bool verificaSfarsit()
{
    return (mutari_ramase <= 0 || scor_j1 == 8 || scor_j2 == 8);
}

void deseneazaPiesa(int linie, int coloana, int cod)//Marian
{

    int x1, x2, y1, y2;
    x1 = coloana*LATURA + MARGINE_O;
    y1 = linie*LATURA + MARGINE_V;

    x2 = (coloana+1)*LATURA + MARGINE_O;
    y2 = (linie+1)*LATURA + MARGINE_V;

    readimagefile(imgPatrat[aspect_tabla], x1, y1, x2-1, y2-1); // deseneaza patrat fundal

    if(cod == 1) readimagefile(imgPiesaA[aspect_j1], x1+12, y1+12, x2-12, y2-12);
    else if(cod == 2) readimagefile(imgPiesaB[aspect_j2], x1+12, y1+12, x2-12, y2-12);
    else if(cod == 3)
    {
        setfillstyle(SOLID_FILL, CULOARE_POSIBIL);
        bar(x1,y1,x2,y2);
        setfillstyle(SOLID_FILL, fundal);
    }
}

void stergePiesa(int linie, int coloana)//Marian
{
    int x1, x2, y1, y2;

    x1 = coloana*LATURA + MARGINE_O;
    y1 = linie*LATURA + MARGINE_V;

    x2 = (coloana+1)*LATURA + MARGINE_O;
    y2 = (linie+1)*LATURA + MARGINE_V;

    readimagefile(imgPatrat[aspect_tabla], x1, y1, x2-1, y2-1);
}

void deseneazaPosibile(int linie, int coloana)//Alex
{
    int di[4] = {-1,-1,1,1}, dj[4] = {-1,1,1,-1};

    // evidentiaza zonele unde se poate efectua mutarea
    for(int d = 0; d < 4; d++)
    {
        int i = linie + di[d];
        int j = coloana + dj[d];

        if(esteInauntru(i,j) && tabla[i][j] == 0)
        {
            tabla[i][j] = POSIBIL;
            deseneazaPiesa(i,j,POSIBIL);
        }
    }
}

void stergePosibile(int linie, int coloana)//Alex
{
    int di[4] = {-1,-1,1,1}, dj[4] = {-1,1,1,-1};

    for(int d = 0; d < 4; d++)
    {
        int i = linie + di[d];
        int j = coloana + dj[d];

        if(esteInauntru(i,j) && tabla[i][j] == POSIBIL)
        {
            tabla[i][j] = 0;
            deseneazaPiesa(i,j,0);
        }
    }
}

bool timpExpirat(time_t inceput, time_t sfarsit)
{
    int timp = (sfarsit-inceput) / CLOCKS_PER_SEC;
    return (timp >= nr_timp+1);
}

void skipMutare(bool &skip_mutare)//Alex
{
    if(ismouseclick(WM_MBUTTONDOWN) || ismouseclick(WM_MBUTTONDBLCLK))
    {
        clearmouseclick(WM_MBUTTONDOWN);
        clearmouseclick(WM_MBUTTONDBLCLK);
        skip_mutare = true;
    }
    if(kbhit())
    {
        char c = getch();
        skip_mutare = (c==32);
    }
}

void verificaButoane(int x, int y, int cod=0)//Alex
{
    // buton muzica
    if(esteDeasupra(x,y,pozMuzica))
    {
        if(mod_muzica == PORNIT) // muzica este pornita, deci o oprim
        {
            muzicaFundal.stop();
            mod_muzica = OPRIT;
        }
        else
        {
            muzicaFundal.play();
            mod_muzica = PORNIT;
        }

        readimagefile(imgMuzica[mod][mod_muzica], COORD1(pozMuzica));
    }
    // buton sfx
    else if(esteDeasupra(x,y,pozSfx))
    {
        mod_sfx = (mod_sfx+1) % 2;
        readimagefile(imgSfx[mod][mod_sfx], COORD1(pozSfx));
    }
    // buton abandon
    else if(esteDeasupra(x,y,pozAbandon))
    {
        Sfarsit(0,cod);
        readimagefile(imgAbandon[mod][limba], COORD1(pozAbandon));
    }
}

void vulnerabilitate(int blocaje, bool &mutat)//Alex
{
    int di[4] = {-1,-1,1,1}, dj[4] = {-1,1,1,-1};

    for(int k = 0; k < sizeAI && !mutat; k++)
    {
        if(ai[k].status == 1) // putem folosi aceasta piesa
        {
            for(int d = 0; d < 4 && !mutat; d++) // simulam mutarile in toate pozitiile libere
            {
                int l1 = ai[k].linie+di[d];
                int c1 = ai[k].coloana+dj[d];

                if(esteInauntru(l1,c1) && tabla[l1][c1] == 0) // ar putea fi o mutare valida
                {
                    for(int d = 0; d < 4 && !mutat; d++) // ma uit la vecinii care ar putea aparea in acest caz
                    {
                        int l2 = l1+di[d];
                        int c2 = c1+dj[d];

                        if(esteInauntru(l2,c2) && tabla[l2][c2] == JUCATOR1) // vecin inamic, numar de cate blocaje este inconjurat
                        {
                            if(nrBlocaje(l2,c2) == blocaje) // piesa vulnerabila, o atac
                            {
                                mutat = true;
                                // actualizeaza info mutare
                                char iab[8][2]={"a","b","c","d","e","f","g","h"}, i08[8][2]={"8","7","6","5","4","3","2","1"};
                                strcat(txt_mutare,iab[ai[k].coloana]); strcat(txt_mutare,i08[ai[k].linie]);
                                strcat(txt_mutare,"-");
                                strcat(txt_mutare,iab[c1]); strcat(txt_mutare,i08[l1]);
                                strcat(txt_mutare," ");

                                tabla[ai[k].linie][ai[k].coloana] = 0;
                                stergePiesa(ai[k].linie,ai[k].coloana);
                                ai[k].linie = l1;
                                ai[k].coloana = c1;
                                tabla[l1][c1] = JUCATOR2;
                                deseneazaPiesa(l1,c1,JUCATOR2);
                            }
                        }
                    }
                }
            }
        }
    }
}

void mutareAi(int index)//Alex
{
    index_ai = index;
    sizeAI = (nr_safe == 0 ? 4:8);
    // daca pot elimina piese -> elimin
    // daca pot bloca piese -> blochez + elimin
    // daca am o piesa inconjurata in 3 parti -> mut in partea libera
    // daca pot, mut o piesa random inainte
    // altfel, mut o piesa random
    // nu pot face nimic

    itoa(index_ai,txt_mutare); strcat(txt_mutare,". ");

    int di[4] = {-1,-1,1,1}, dj[4] = {-1,1,1,-1};
    bool mutat = false, eliminat = false;

    // elimin piesele inamice blocate
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(index_ai > nr_safe+2 && tabla[i][j] == JUCATOR1 && esteBlocat(i,j))
            {
                eliminat = true;
                tabla[i][j] = 0;
                stergePiesa(i,j);
                scor_j2++;

                // actualizeaza info mutare
                char iab[8][2]={"a","b","c","d","e","f","g","h"}, i08[8][2]={"8","7","6","5","4","3","2","1"};
                strcat(txt_mutare,"(-");
                strcat(txt_mutare,iab[j]); strcat(txt_mutare,i08[i]);
                strcat(txt_mutare,") ");
            }

    // caut piese inamice foarte vulnerabile
    vulnerabilitate(3,mutat);
    // nu am gasit, caut piese mai putin vulnerabile
    if(!mutat) vulnerabilitate(2,mutat);

    bool sunt_blocat = true;
    for(int i = 0; i < sizeAI && !mutat; i++)
        if(ai[i].status == 1)
        {
            if(nrBlocaje(ai[i].linie,ai[i].coloana) < 4)
            {
                sunt_blocat = false;
                break;
            }
        }
    if(!sunt_blocat)
    {
        bool pot_inainte = false;
        for(int i = 0; i < sizeAI; i++)
        {
            if(ai[i].status == 1)
            {
                int l = ai[i].linie+1;
                int c1 = ai[i].coloana-1;
                int c2 = ai[i].coloana+1;
                if(esteInauntru(l,c1) && tabla[l][c1] == 0)
                {
                    pot_inainte = true;
                    break;
                }
                if(esteInauntru(l,c2) && tabla[l][c2] == 0)
                {
                    pot_inainte = true;
                    break;
                }
            }
        }

        if(pot_inainte) // pot muta agresiv
        {
            while(!mutat)
            {
                int r = rand()%sizeAI;
                if(ai[r].status == 1)
                {
                    int l = ai[r].linie+1;
                    int c1 = ai[r].coloana-1;
                    int c2 = ai[r].coloana+1;
                    if(esteInauntru(l,c1) && tabla[l][c1] == 0)
                    {
                        mutat = true;
                        // actualizeaza info mutare
                        char iab[8][2]={"a","b","c","d","e","f","g","h"}, i08[8][2]={"8","7","6","5","4","3","2","1"};
                        strcat(txt_mutare,iab[ai[r].coloana]); strcat(txt_mutare,i08[ai[r].linie]);
                        strcat(txt_mutare,"-");
                        strcat(txt_mutare,iab[c1]); strcat(txt_mutare,i08[l]);
                        strcat(txt_mutare," ");

                        tabla[ai[r].linie][ai[r].coloana] = 0;
                        stergePiesa(ai[r].linie,ai[r].coloana);
                        ai[r].linie = l;
                        ai[r].coloana = c1;
                        tabla[l][c1] = JUCATOR2;
                        deseneazaPiesa(l,c1,JUCATOR2);
                        break;
                    }
                    if(esteInauntru(l,c2) && tabla[l][c2] == 0)
                    {
                        mutat = true;
                        // actualizeaza info mutare
                        char iab[8][2]={"a","b","c","d","e","f","g","h"}, i08[8][2]={"8","7","6","5","4","3","2","1"};
                        strcat(txt_mutare,iab[ai[r].coloana]); strcat(txt_mutare,i08[ai[r].linie]);
                        strcat(txt_mutare,"-");
                        strcat(txt_mutare,iab[c2]); strcat(txt_mutare,i08[l]);
                        strcat(txt_mutare," ");

                        tabla[ai[r].linie][ai[r].coloana] = 0;
                        stergePiesa(ai[r].linie,ai[r].coloana);
                        ai[r].linie = l;
                        ai[r].coloana = c2;
                        tabla[l][c2] = JUCATOR2;
                        deseneazaPiesa(l,c2,JUCATOR2);
                        break;
                    }
                }
            }
        }
        else // mut in alta parte
        {
            while(!mutat)
            {
                int r = rand()%sizeAI;
                if(ai[r].status == 1)
                {
                    for(int d = 0; d < 4 && !mutat; d++)
                    {
                        int l = ai[r].linie+di[d];
                        int c = ai[r].coloana+dj[d];

                        if(esteInauntru(l,c) && tabla[l][c] == 0)
                        {
                            mutat = true;
                            // actualizeaza info mutare
                            char iab[8][2]={"a","b","c","d","e","f","g","h"}, i08[8][2]={"8","7","6","5","4","3","2","1"};
                            strcat(txt_mutare,iab[ai[r].coloana]); strcat(txt_mutare,i08[ai[r].linie]);
                            strcat(txt_mutare,"-");
                            strcat(txt_mutare,iab[c]); strcat(txt_mutare,i08[l]);
                            strcat(txt_mutare," ");

                            tabla[ai[r].linie][ai[r].coloana] = 0;
                            stergePiesa(ai[r].linie,ai[r].coloana);
                            ai[r].linie = l;
                            ai[r].coloana = c;
                            tabla[l][c] = JUCATOR2;
                            deseneazaPiesa(l,c,JUCATOR2);
                        }
                    }
                }
            }
        }
    }

    // elimin eventualele piese inamice blocate
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(index_ai > nr_safe+2 && tabla[i][j] == JUCATOR1 && esteBlocat(i,j))
            {
                eliminat = true;
                tabla[i][j] = 0;
                stergePiesa(i,j);
                scor_j2++;

                // actualizeaza info mutare
                char iab[8][2]={"a","b","c","d","e","f","g","h"}, i08[8][2]={"8","7","6","5","4","3","2","1"};
                strcat(txt_mutare,"(-");
                strcat(txt_mutare,iab[j]); strcat(txt_mutare,i08[i]);
                strcat(txt_mutare,") ");
            }

    if(!mutat && !eliminat) strcat(txt_mutare, "x"); // atat s-a putut

    // actualizare mutari ramase si text nr mutari
    mutari_ramase--;

    char txtNrMutari[12]; itoa(mutari_ramase, txtNrMutari);
    char txtInfoMutari[LEN]; strcpy(txtInfoMutari,txt_infoMutari[limba]); strcat(txtInfoMutari,txtNrMutari);
    settextstyle(8,0,3);
    bar(pozRamase[0]-200,pozRamase[1]-100,pozRamase[0]+150,pozRamase[1]+100);
    outtextxy(COORD2(pozRamase), txtInfoMutari);

    // actualizare text tura jucator
    bar(pozRand1[0]-80,pozRand1[1]-15,pozRand1[0]+80,pozRand1[1]+15);
    bar(pozRand2[0]-80,pozRand2[1]-15,pozRand2[0]+80,pozRand2[1]+15);

    if(turaJucator() == JUCATOR1) outtextxy(COORD2(pozRand1), txt_infoP1[limba]);
    else outtextxy(COORD2(pozRand2), txt_infoP2[limba]);

    // actualizare text scor
    settextstyle(3,0,4);
    char txtScor1[12], txtScor2[12]; itoa(scor_j1,txtScor1); itoa(scor_j2,txtScor2);
    char txtScor[LEN] = ""; strcat(txtScor,txtScor1); strcat(txtScor," - "); strcat(txtScor,txtScor2);
    outtextxy(COORD2(pozScor), txtScor);

    // actualizeaza tabela istoric
    if((index_ai-1)%23 == 0) // tabela este plina, o sterg
    {
        readimagefile(imgIstoric[mod], COORD1(pozIstoric));
        pozMutare[1] = pozIstoric[limba][1]+12;
    }
    strcpy(txt_logs[index_ai-1], txt_mutare);
    strcpy(txt_logs[index_ai], "NULL");

    settextstyle(3,0,1);
    settextjustify(LEFT_TEXT,TOP_TEXT);
    outtextxy(COORD2(pozMutare), txt_mutare);
    pozMutare[1] += 24;
    settextjustify(CENTER_TEXT,CENTER_TEXT);
}

void mutarePiesa(int cod=0, int altcod=0) // 0 = pvp, 1 = pvai    Alex
{
    int index_mutare = nr_mutari-mutari_ramase+1;
    if(cod == 1)
    {
        mutareAi(index_mutare);
        return;
    }
    itoa(index_mutare,txt_mutare); strcat(txt_mutare,". ");

    bool piesa_mutata = false, piesa_eliminata = false;
    bool skip_mutare = false;

    time_t inceput = clock();
    time_t sfarsit = NULL;
    int timer1 = inceput;
    int timer2 = NULL;

    // actualizeaza text timer
    settextstyle(3,0,8);
    char txtTimp[12]; itoa(timp_limita,txtTimp);
    if(timp_limita < 10) txtTimp[1] = txtTimp[0], txtTimp[0] = '0', txtTimp[2] = NULL;
    char txtInfoTimer[LEN] = "00:"; strcat(txtInfoTimer,txtTimp);
    outtextxy(COORD2(pozTimer), txtInfoTimer);

  	do
    {
        int x = mousex();
        int y = mousey();

        // buton abandon
        if(esteDeasupra(x,y,pozAbandon)) readimagefile(imgAbandon[(mod+1)%2][limba],COORD1(pozAbandon));
        else readimagefile(imgAbandon[mod][limba],COORD1(pozAbandon));

        if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
        {
          	clearmouseclick(WM_LBUTTONDOWN);
          	clearmouseclick(WM_LBUTTONDBLCLK);

            // inceput MUTARE PIESA
            if(piesa_mutata == false)
            {
                int linie1, coloana1;
                determinaPozitie(linie1,coloana1);

                if(esteInauntru(linie1,coloana1) && tabla[linie1][coloana1] == turaJucator()) // piesa valida
                {
                    deseneazaPosibile(linie1,coloana1); // deseneaza ghid

                    do
                    {
                        x = mousex();
                        y = mousey();

                        // buton abandon
                        if(esteDeasupra(x,y,pozAbandon)) readimagefile(imgAbandon[(mod+1)%2][limba],COORD1(pozAbandon));
                        else readimagefile(imgAbandon[mod][limba],COORD1(pozAbandon));

                        if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK)) // selecteaza pozitia in care vrei sa muti piesa
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            clearmouseclick(WM_LBUTTONDBLCLK);

                            verificaButoane(x,y);

                            int linie2, coloana2;
                            determinaPozitie(linie2,coloana2);

                            if(esteInauntru(linie2,coloana2) && abs(linie1-linie2) == 1 && abs(coloana1-coloana2) == 1 && (tabla[linie2][coloana2] == 0 || tabla[linie2][coloana2] == POSIBIL)) // pozitie valida
                            {
                                piesa_mutata = true; // piesa a fost mutata

                                tabla[linie1][coloana1] = 0; // sterg piesa
                                stergePiesa(linie1,coloana1); // de pe vechia pozitie

                                tabla[linie2][coloana2] = turaJucator(); // desenez piesa
                                deseneazaPiesa(linie2,coloana2,turaJucator()); // pe noua pozitie

                                stergePosibile(linie1,coloana1); // sterge ghid

                                // actualizeaza info mutare
                                char iab[8][2]={"a","b","c","d","e","f","g","h"}, i08[8][2]={"8","7","6","5","4","3","2","1"};
                                strcat(txt_mutare,iab[coloana1]); strcat(txt_mutare,i08[linie1]);
                                strcat(txt_mutare,"-");
                                strcat(txt_mutare,iab[coloana2]); strcat(txt_mutare,i08[linie2]);
                                strcat(txt_mutare," ");

                                // sunet mutare piesa
                                if(mod_sfx == PORNIT)
                                {
                                    int rnd = rand()%6;
                                    sf::SoundBuffer rndBfr; rndBfr.loadFromFile(sunetHit[rnd]);
                                    sf::Sound rndSnd(rndBfr); rndSnd.play();
                                    while(rndSnd.getStatus());
                                }
                            }
                        }
                        else if(ismouseclick(WM_RBUTTONDOWN)) break; // actiune invalida -> anulare mutare

                        // actualizeaza text timer
                        if(timer2-timer1 >= CLOCKS_PER_SEC)
                        {
                            timp_limita--;
                            char txtTimp[12]; itoa(timp_limita,txtTimp);
                            if(timp_limita < 10) txtTimp[1] = txtTimp[0], txtTimp[0] = '0', txtTimp[2] = NULL;
                            char txtInfoTimer[LEN] = "00:"; strcat(txtInfoTimer,txtTimp);
                            outtextxy(COORD2(pozTimer), txtInfoTimer);

                            timer1 = timer2;
                        }

                        sfarsit = clock(); timer2 = sfarsit;
                        verificaSfarsit(); // verifica starea jocului
                        timp_expirat = timpExpirat(inceput,sfarsit); // actualizeaza timer
                        skipMutare(skip_mutare); // daca jucatorul sare peste mutare/si-a incheiat mutarea
                    }while(timp_expirat == false && joc_terminat == false && piesa_mutata == false && skip_mutare == false);

                    stergePosibile(linie1,coloana1); // sterge ghid
                }
                else if(!cod) verificaButoane(x,y,altcod);
            }
            // sfarsit MUTARE PIESA
            else if(!cod) verificaButoane(x,y,altcod);
        }
        else if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);

            // inceput ELIMINARE PIESA
            int linie1, coloana1;
            determinaPozitie(linie1,coloana1);

            if(index_mutare > nr_safe+2 && tabla[linie1][coloana1] != 0 && esteInauntru(linie1,coloana1) && esteBlocat(linie1,coloana1)) // sterge piesa valida
            {
                piesa_eliminata = true;

                // actualizeaza scor
                if(tabla[linie1][coloana1] == JUCATOR1) scor_j2++;
                else scor_j1++;

                // daca joc vs ai
                if(altcod == 1)
                {
                    for(int s = 0; s < sizeAI; s++)
                        if(ai[s].linie == linie1 && ai[s].coloana == coloana1)
                        {
                            ai[s].status = 0;
                            break;
                        }
                }

                tabla[linie1][coloana1] = 0;
                stergePiesa(linie1,coloana1); // sterge piesa

                // actualizeaza info mutare
                char iab[8][2]={"a","b","c","d","e","f","g","h"}, i08[8][2]={"8","7","6","5","4","3","2","1"};
                strcat(txt_mutare,"(-");
                strcat(txt_mutare,iab[coloana1]); strcat(txt_mutare,i08[linie1]);
                strcat(txt_mutare,") ");

                // actualizare text scor
                settextstyle(3,0,4);
                char txtScor1[12], txtScor2[12]; itoa(scor_j1,txtScor1); itoa(scor_j2,txtScor2);
                char txtScor[LEN] = ""; strcat(txtScor,txtScor1); strcat(txtScor," - "); strcat(txtScor,txtScor2);
                outtextxy(COORD2(pozScor), txtScor);
                settextstyle(3,0,8);
            }
            // sfarsit ELIMINARE PIESA
        }

        // actualizeaza text timer
        sfarsit = clock(); timer2 = sfarsit;
        if(timer2-timer1 >= CLOCKS_PER_SEC)
        {
            timp_limita--;
            char txtTimp[12]; itoa(timp_limita,txtTimp);
            if(timp_limita < 10) txtTimp[1] = txtTimp[0], txtTimp[0] = '0', txtTimp[2] = NULL;
            char txtInfoTimer[LEN] = "00:"; strcat(txtInfoTimer,txtTimp);
            outtextxy(COORD2(pozTimer), txtInfoTimer);

            timer1 = timer2;
        }
        verificaSfarsit(); // verifica starea jocului
        timp_expirat = timpExpirat(inceput,sfarsit); // actualizeaza timer
        skipMutare(skip_mutare); // daca jucatorul sare peste mutare/si-a incheiat mutarea
    }while(timp_expirat == false && joc_terminat == false && skip_mutare == false);

    if(piesa_mutata == false && piesa_eliminata == false) strcat(txt_mutare, "x");

    // actualizare mutari ramase si text nr mutari
    mutari_ramase--;

    char txtNrMutari[12]; itoa(mutari_ramase, txtNrMutari);
    char txtInfoMutari[LEN]; strcpy(txtInfoMutari,txt_infoMutari[limba]); strcat(txtInfoMutari,txtNrMutari);
    settextstyle(8,0,3);
    bar(pozRamase[0]-200,pozRamase[1]-100,pozRamase[0]+150,pozRamase[1]+100);
    outtextxy(COORD2(pozRamase), txtInfoMutari);

    // actualizare text tura jucator
    bar(pozRand1[0]-80,pozRand1[1]-15,pozRand1[0]+80,pozRand1[1]+15);
    bar(pozRand2[0]-80,pozRand2[1]-15,pozRand2[0]+80,pozRand2[1]+15);

    if(turaJucator() == JUCATOR1) outtextxy(COORD2(pozRand1), txt_infoP1[limba]);
    else outtextxy(COORD2(pozRand2), txt_infoP2[limba]);

    // actualizare text scor
    settextstyle(3,0,4);
    char txtScor1[12], txtScor2[12]; itoa(scor_j1,txtScor1); itoa(scor_j2,txtScor2);
    char txtScor[LEN] = ""; strcat(txtScor,txtScor1); strcat(txtScor," - "); strcat(txtScor,txtScor2);
    outtextxy(COORD2(pozScor), txtScor);

    // actualizeaza tabela istoric
    if((index_mutare-1)%23 == 0) // tabela este plina, o sterg
    {
        readimagefile(imgIstoric[mod], COORD1(pozIstoric));
        pozMutare[1] = pozIstoric[limba][1]+12;
    }
    strcpy(txt_logs[index_mutare-1], txt_mutare);
    strcpy(txt_logs[index_mutare], "NULL");

    settextstyle(3,0,1);
    settextjustify(LEFT_TEXT,TOP_TEXT);
    outtextxy(COORD2(pozMutare), txt_mutare);
    pozMutare[1] += 24;
    settextjustify(CENTER_TEXT,CENTER_TEXT);
}

void Initializari()//Marian
{
    fundal = WHITE;

    nr_mutari = 50;
    nr_timp = 10;
    nr_safe = 6;

    muzicaFundal.openFromFile("audio/bgm.wav");
    muzicaFundal.setLoop(true); muzicaFundal.setVolume(50.f); muzicaFundal.play();

    bufferHover.loadFromFile("audio/mouseHover.wav");
    bufferInainte.loadFromFile("audio/mouseForward.wav");
    bufferInapoi.loadFromFile("audio/mouseBack.wav");
    bufferZi.loadFromFile("audio/mouseLight.wav");
    bufferNoapte.loadFromFile("audio/mouseDark.wav");
    bufferSchimba.loadFromFile("audio/mouseSettings.wav");
    bufferVictorie.loadFromFile("audio/victory.wav");
    bufferEgal.loadFromFile("audio/draw.wav");

    sunetHover.setBuffer(bufferHover);
    sunetInainte.setBuffer(bufferInainte);
    sunetInapoi.setBuffer(bufferInapoi);
    sunetZi.setBuffer(bufferZi);
    sunetNoapte.setBuffer(bufferNoapte);
    sunetSchimba.setBuffer(bufferSchimba);
    sunetVictorie.setBuffer(bufferVictorie);
    sunetEgal.setBuffer(bufferEgal);
}

void Meniu()
{
    // afiseaza fundal si butoane
    setfillstyle(SOLID_FILL, fundal);
    bar(0,0,LUNGIME,LATIME);

    readimagefile(imgMuzica[mod][mod_muzica], COORD1(pozMuzica));
    readimagefile(imgSfx[mod][mod_sfx], COORD1(pozSfx));

    readimagefile(imgTitlu[mod][limba], COORD1(pozTitlu));
    readimagefile(imgCredit[mod][limba], COORD1(pozCredit));

    readimagefile(imgJocNou[mod][limba], COORD1(pozJocNou));
    readimagefile(imgTutorial[mod][limba], COORD1(pozTutorial));
    readimagefile(imgSetari[mod][limba], COORD1(pozSetari));
    readimagefile(imgIesire[mod][limba], COORD1(pozIesire));

    readimagefile(imgSoare[NOAPTE], COORD1(pozSoare));
    readimagefile(imgLuna[ZI], COORD1(pozLuna));

    readimagefile(imgRo[mod][limba], COORD1(pozRo));
    readimagefile(imgEn[mod][limba], COORD1(pozEn));

    // hover si click
    while(true)
    {
        clearmouseclick(WM_LBUTTONDOWN);
        clearmouseclick(WM_MOUSEMOVE);

        int x = mousex();
        int y = mousey();

        // buton muzica
        if(esteDeasupra(x,y,pozMuzica))
        {
            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_muzica == PORNIT) // muzica este pornita, deci o oprim
                    {
                        muzicaFundal.stop();
                        mod_muzica = OPRIT;
                    }
                    else
                    {
                        muzicaFundal.play();
                        mod_muzica = PORNIT;
                    }

                    readimagefile(imgMuzica[mod][mod_muzica], COORD1(pozMuzica));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozMuzica)) break;
                }
            }
        }
        // buton sfx
        else if(esteDeasupra(x,y,pozSfx))
        {
            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    mod_sfx = (mod_sfx+1) % 2;

                    readimagefile(imgSfx[mod][mod_sfx], COORD1(pozSfx));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozSfx)) break;
                }
            }
        }
        // buton joc nou
        else if(esteDeasupra(x,y,pozJocNou))
        {
            if(mod_sfx == PORNIT) sunetHover.play();
            readimagefile(imgJocNou[(mod+1)%2][limba], COORD1(pozJocNou));

            bar(STERGE(pozJoystick));
            readimagefile(imgJoystick[mod], COORD1(pozJoystick));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(mod_sfx == PORNIT) sunetInainte.play();

                    JocNou();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozJocNou))
                    {
                        readimagefile(imgJocNou[mod][limba], COORD1(pozJocNou));
                        bar(STERGE(pozJoystick));
                        break;
                    }
                }
            }
        }
        // buton cum se joaca
        else if(esteDeasupra(x,y,pozTutorial))
        {
           if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgTutorial[(mod+1)%2][limba], COORD1(pozTutorial));

            bar(STERGE(pozCarte));
            readimagefile(imgCarte[mod], COORD1(pozCarte));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(mod_sfx == PORNIT) sunetInainte.play();

                    Tutorial();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozTutorial))
                    {
                        readimagefile(imgTutorial[mod][limba], COORD1(pozTutorial));
                        bar(STERGE(pozCarte));
                        break;
                    }
                }
            }
        }
        // buton setari
        else if(esteDeasupra(x,y,pozSetari))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgSetari[(mod+1)%2][limba], COORD1(pozSetari));

            bar(STERGE(pozRotita));
            readimagefile(imgRotita[mod], COORD1(pozRotita));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(mod_sfx == PORNIT) sunetInainte.play();

                    Setari();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozSetari))
                    {
                        readimagefile(imgSetari[mod][limba], COORD1(pozSetari));
                        bar(STERGE(pozRotita));
                        break;
                    }
                }
            }
        }
        // buton iesire
        else if(esteDeasupra(x,y,pozIesire))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgIesire[(mod+1)%2][limba], COORD1(pozIesire));

            bar(STERGE(pozX));
            readimagefile(imgX[mod], COORD1(pozX));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN)) exit(0);
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozIesire))
                    {
                        readimagefile(imgIesire[mod][limba], COORD1(pozIesire));
                        bar(STERGE(pozX));
                        break;
                    }
                }
            }
        }
        // buton credits
        else if(esteDeasupra(x,y,pozCredit))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgCredit[(mod+1)%2][limba], COORD1(pozCredit));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetInainte.play();

                    Credits();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozCredit))
                    {
                        readimagefile(imgCredit[mod][limba], COORD1(pozCredit));
                        break;
                    }
                }
            }
        }
        // buton zi
        else if(esteDeasupra(x,y,pozSoare) && mod == NOAPTE)
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgSoare[ZI], COORD1(pozSoare));
            readimagefile(imgLuna[NOAPTE], COORD1(pozLuna));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(mod_sfx == PORNIT) sunetZi.play();

                    mod = ZI; fundal = WHITE;
                    Meniu();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozSoare))
                    {
                        readimagefile(imgSoare[NOAPTE], COORD1(pozSoare));
                        readimagefile(imgLuna[ZI], COORD1(pozLuna));
                        break;
                    }
                }
            }
        }
        // buton noapte
        else if(esteDeasupra(x,y,pozLuna) && mod == ZI)
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgLuna[NOAPTE], COORD1(pozLuna));
            readimagefile(imgSoare[ZI], COORD1(pozSoare));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(mod_sfx == PORNIT) sunetNoapte.play();

                    mod = NOAPTE; fundal = BLACK;
                    Meniu();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozLuna))
                    {
                        readimagefile(imgLuna[ZI], COORD1(pozLuna));
                        readimagefile(imgSoare[NOAPTE], COORD1(pozSoare));
                        break;
                    }
                }
            }
        }
        // buton ro
        else if(esteDeasupra(x,y,pozRo) && limba == EN)
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgRo[mod][(limba+1)%2], COORD1(pozRo));
            readimagefile(imgEn[mod][(limba+1)%2], COORD1(pozEn));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(mod_sfx == PORNIT) sunetInainte.play();

                    limba = RO;
                    Meniu();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozRo))
                    {
                        readimagefile(imgRo[mod][limba], COORD1(pozRo));
                        readimagefile(imgEn[mod][limba], COORD1(pozEn));
                        break;
                    }
                }
            }
        }
        // buton en
        else if(esteDeasupra(x,y,pozEn) && limba == RO)
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgEn[mod][(limba+1)%2], COORD1(pozEn));
            readimagefile(imgRo[mod][(limba+1)%2], COORD1(pozRo));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    if(mod_sfx == PORNIT) sunetInainte.play();
                    clearmouseclick(WM_LBUTTONDOWN);

                    limba = EN;
                    Meniu();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozEn))
                    {
                        readimagefile(imgEn[mod][limba], COORD1(pozEn));
                        readimagefile(imgRo[mod][limba], COORD1(pozRo));
                        break;
                    }
                }
            }
        }
    }
}

void JocNou()
{
    setfillstyle(SOLID_FILL, fundal);
    bar(0,0,LUNGIME,LATIME);

    fundal == WHITE ? setcolor(BLACK):setcolor(WHITE);
    setbkcolor(fundal);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(3,0,4);

    // butoane muzica + inapoi
    readimagefile(imgMuzica[mod][mod_muzica], COORD1(pozMuzica));
    readimagefile(imgSfx[mod][mod_sfx], COORD1(pozSfx));
    readimagefile(imgInapoi[mod], COORD1(pozInapoi));

    // butoane meniu
    readimagefile(imgPVP[mod][limba], COORD1(pozPVP));
    readimagefile(imgPVIA[mod][limba], COORD1(pozPVIA));
    readimagefile(imgReluare[mod][limba], COORD1(pozReluare));

    readimagefile(imgOptiuni[mod][limba], COORD1(pozOptiuni));

    char s1[12], s2[12], s3[12];
    itoa(nr_mutari, s1); itoa(nr_timp, s2); itoa(nr_safe, s3);

    readimagefile(imgSageataL[mod], COORD1(pozS1a));
    outtextxy(COORD2(pozS1), s1);
    readimagefile(imgSageataR[mod], COORD1(pozS1b));

    readimagefile(imgSageataL[mod], COORD1(pozS2a));
    outtextxy(COORD2(pozS2), s2);
    readimagefile(imgSageataR[mod], COORD1(pozS2b));

    readimagefile(imgSageataL[mod], COORD1(pozS3a));
    outtextxy(COORD2(pozS3), s3);
    readimagefile(imgSageataR[mod], COORD1(pozS3b));

    while(true)
    {
        clearmouseclick(WM_LBUTTONDOWN);
        clearmouseclick(WM_LBUTTONDBLCLK);
        clearmouseclick(WM_MOUSEMOVE);

        int x = mousex();
        int y = mousey();

        // buton muzica
        if(esteDeasupra(x,y,pozMuzica))
        {
            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_muzica == PORNIT) // muzica este pornita, deci o oprim
                    {
                        muzicaFundal.stop();
                        mod_muzica = OPRIT;
                    }
                    else
                    {
                        muzicaFundal.play();
                        mod_muzica = PORNIT;
                    }

                    readimagefile(imgMuzica[mod][mod_muzica], COORD1(pozMuzica));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozMuzica)) break;
                }
            }
        }
        // buton sfx
        else if(esteDeasupra(x,y,pozSfx))
        {
            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    mod_sfx = (mod_sfx+1) % 2;

                    readimagefile(imgSfx[mod][mod_sfx], COORD1(pozSfx));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozSfx)) break;
                }
            }
        }
        // buton inapoi
        else if(esteDeasupra(x,y,pozInapoi))
        {
            if(mod_sfx == PORNIT) sunetHover.play();
            readimagefile(imgInapoi[(mod+1)%2], COORD1(pozInapoi));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetInapoi.play();
                    Meniu();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozInapoi))
                    {
                        readimagefile(imgInapoi[mod], COORD1(pozInapoi));
                        break;
                    }
                }
            }
        }
        // buton player vs player
        else if(esteDeasupra(x,y,pozPVP))
        {
            if(mod_sfx == PORNIT) sunetHover.play();
            readimagefile(imgPVP[(mod+1)%2][limba], COORD1(pozPVP));

            bar(STERGE(pozOm));
            readimagefile(imgOm[mod], COORD1(pozOm));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetInainte.play();

                    // schimba melodia
                    muzicaFundal.stop();
                    muzicaFundal.openFromFile("audio/ingame.wav");
                    if(mod_muzica == PORNIT)
                    {
                        muzicaFundal.setVolume(50.f);
                        muzicaFundal.play();
                    }
                    PVP();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozPVP))
                    {
                        readimagefile(imgPVP[mod][limba], COORD1(pozPVP));
                        bar(STERGE(pozOm));
                        break;
                    }
                }
            }
        }
        // buton player vs ia
        else if(esteDeasupra(x,y,pozPVIA))
        {
           if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgPVIA[(mod+1)%2][limba], COORD1(pozPVIA));

            bar(STERGE(pozOchi));
            readimagefile(imgOchi[mod], COORD1(pozOchi));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(mod_sfx == PORNIT) sunetInainte.play();

                    // schimba melodia
                    muzicaFundal.stop();
                    muzicaFundal.openFromFile("audio/ingame.wav");
                    if(mod_muzica == PORNIT)
                    {
                        muzicaFundal.setVolume(50.f);
                        muzicaFundal.play();
                    }
                    PVIA();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozPVIA))
                    {
                        readimagefile(imgPVIA[mod][limba], COORD1(pozPVIA));
                        bar(STERGE(pozOchi));
                        break;
                    }
                }
            }
        }
        // buton replay
        else if(esteDeasupra(x,y,pozReluare))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgReluare[(mod+1)%2][limba], COORD1(pozReluare));

            bar(STERGE(pozRotita));
            readimagefile(imgReplay[mod], COORD1(pozReplay));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(mod_sfx == PORNIT) sunetInainte.play();
                    Reluare();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozReluare))
                    {
                        readimagefile(imgReluare[mod][limba], COORD1(pozReluare));
                        bar(STERGE(pozReplay));
                        break;
                    }
                }
            }
        }
        // buton <nr_mutari> stanga
        else if(esteDeasupra(x,y,pozS1a))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgSageataL[(mod+1)%2], COORD1(pozS1a));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetSchimba.play();

                    bar(pozS1[0]-36, pozS1[1]-36, pozS1[0]+36, pozS1[1]+36);

                    nr_mutari -= 10; // din 10 in 10
                    if(nr_mutari == 0) nr_mutari = 100; // [10, 100]

                    itoa(nr_mutari, s1);
                    outtextxy(COORD2(pozS1), s1);
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozS1a))
                    {
                        readimagefile(imgSageataL[mod], COORD1(pozS1a));
                        break;
                    }
                }
            }
        }
        // buton <nr_mutari> dreapta
        else if(esteDeasupra(x,y,pozS1b))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgSageataR[(mod+1)%2], COORD1(pozS1b));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetSchimba.play();

                    bar(pozS1[0]-36, pozS1[1]-36, pozS1[0]+36, pozS1[1]+36);

                    nr_mutari += 10;
                    if(nr_mutari == 110) nr_mutari = 10;

                    itoa(nr_mutari, s1);
                    outtextxy(COORD2(pozS1), s1);
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozS1b))
                    {
                        readimagefile(imgSageataR[mod], COORD1(pozS1b));
                        break;
                    }
                }
            }
        }
        // buton <nr_timp> stanga
        else if(esteDeasupra(x,y,pozS2a))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgSageataL[(mod+1)%2], COORD1(pozS2a));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetSchimba.play();

                    bar(pozS2[0]-36, pozS2[1]-36, pozS2[0]+36, pozS2[1]+36);

                    nr_timp--;
                    if(nr_timp == 0) nr_timp = 15;

                    itoa(nr_timp, s2);
                    outtextxy(COORD2(pozS2), s2);
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozS2a))
                    {
                        readimagefile(imgSageataL[mod], COORD1(pozS2a));
                        break;
                    }
                }
            }
        }
        // buton <nr_timp> dreapta
        else if(esteDeasupra(x,y,pozS2b))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgSageataR[(mod+1)%2], COORD1(pozS2b));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetSchimba.play();

                    bar(pozS2[0]-36, pozS2[1]-36, pozS2[0]+36, pozS2[1]+36);

                    nr_timp++;
                    if(nr_timp == 16) nr_timp = 1;

                    itoa(nr_timp, s2);
                    outtextxy(COORD2(pozS2), s2);
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozS2b))
                    {
                        readimagefile(imgSageataR[mod], COORD1(pozS2b));
                        break;
                    }
                }
            }
        }
        // buton <nr_safe> stanga
        else if(esteDeasupra(x,y,pozS3a))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgSageataL[(mod+1)%2], COORD1(pozS3a));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetSchimba.play();

                    bar(pozS3[0]-36, pozS3[1]-36, pozS3[0]+36, pozS3[1]+36);

                    nr_safe -= 2;
                    if(nr_safe == -2) nr_safe = 10;

                    itoa(nr_safe, s3);
                    outtextxy(COORD2(pozS3), s3);
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozS3a))
                    {
                        readimagefile(imgSageataL[mod], COORD1(pozS3a));
                        break;
                    }
                }
            }
        }
        // buton <nr_safe> dreapta
        else if(esteDeasupra(x,y,pozS3b))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgSageataR[(mod+1)%2], COORD1(pozS3b));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetSchimba.play();

                    bar(pozS3[0]-36, pozS3[1]-36, pozS3[0]+36, pozS3[1]+36);

                    nr_safe += 2;
                    if(nr_safe == 12) nr_safe = 0;

                    itoa(nr_safe, s3);
                    outtextxy(COORD2(pozS3), s3);
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozS3b))
                    {
                        readimagefile(imgSageataR[mod], COORD1(pozS3b));
                        break;
                    }
                }
            }
        }
    }
}

void Tutorial()
{
    //imagini butoane
    setfillstyle(SOLID_FILL, fundal);
    bar(0,0,LUNGIME,LATIME);

    readimagefile(imgMuzica[mod][mod_muzica], COORD1(pozMuzica));
    readimagefile(imgSfx[mod][mod_sfx], COORD1(pozSfx));
    readimagefile(imgInapoi[mod], COORD1(pozInapoi));

    const char imgCartoi[2][LEN] = {"img/cartoiD.jpg", "img/cartoiN.jpg"};
    readimagefile(imgCartoi[mod], COORD1(pozGhid));

    readimagefile(imgTut1[mod][limba], COORD1(pozTut1));
    readimagefile(imgTut2[mod][limba], COORD1(pozTut2));
    readimagefile(imgTut3[mod][limba], COORD1(pozTut3));
    readimagefile(imgTut4[mod][limba], COORD1(pozTut4));
    readimagefile(imgTut5[mod][limba], COORD1(pozTut5));

    while(true)
    {
        clearmouseclick(WM_LBUTTONDOWN);
        clearmouseclick(WM_MOUSEMOVE);

        int x = mousex();
        int y = mousey();

        // buton muzica
        if(esteDeasupra(x,y,pozMuzica))
        {
            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_muzica == PORNIT) // muzica este pornita, deci o oprim
                    {
                        muzicaFundal.stop();
                        mod_muzica = OPRIT;
                    }
                    else
                    {
                        muzicaFundal.play();
                        mod_muzica = PORNIT;
                    }

                    readimagefile(imgMuzica[mod][mod_muzica], COORD1(pozMuzica));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozMuzica)) break;
                }
            }
        }
        // buton sfx
        else if(esteDeasupra(x,y,pozSfx))
        {
            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    mod_sfx = (mod_sfx+1) % 2;

                    readimagefile(imgSfx[mod][mod_sfx], COORD1(pozSfx));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozSfx)) break;
                }
            }
        }
        // buton inapoi
        else if(esteDeasupra(x,y,pozInapoi))
        {
            if(mod_sfx == PORNIT) sunetHover.play();
            readimagefile(imgInapoi[(mod+1)%2], COORD1(pozInapoi));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetInapoi.play();
                    Meniu();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozInapoi))
                    {
                        readimagefile(imgInapoi[mod], COORD1(pozInapoi));
                        break;
                    }
                }
            }
        }
        // prezentare
        else if(esteDeasupra(x,y,pozTut1))
        {
            if(mod_sfx == PORNIT) sunetHover.play();
            readimagefile(imgTut1[(mod+1)%2][limba], COORD1(pozTut1));
            readimagefile(imgGhid1[mod][limba],COORD1(pozGhid));
            while(true)
            {
                clearmouseclick(WM_MOUSEMOVE);
                int x = mousex();
                int y = mousey();
                if(!esteDeasupra(x,y,pozTut1))
                {
                    readimagefile(imgTut1[mod][limba], COORD1(pozTut1));
                    readimagefile(imgCartoi[mod], COORD1(pozGhid));

                    break;
                }
            }
        }
        // mutarea
        else if(esteDeasupra(x,y,pozTut2))
        {
            if(mod_sfx == PORNIT) sunetHover.play();
            readimagefile(imgTut2[(mod+1)%2][limba], COORD1(pozTut2));
            readimagefile(imgGhid2[mod][limba],COORD1(pozGhid));
            while(true)
            {
                clearmouseclick(WM_MOUSEMOVE);
                int x = mousex();
                int y = mousey();
                if(!esteDeasupra(x,y,pozTut2))
                {
                    readimagefile(imgTut2[mod][limba], COORD1(pozTut2));
                    readimagefile(imgCartoi[mod], COORD1(pozGhid));

                    break;
                }
            }
        }
        // blocarea
        else if(esteDeasupra(x,y,pozTut3))
        {
            if(mod_sfx == PORNIT) sunetHover.play();
            readimagefile(imgTut3[(mod+1)%2][limba], COORD1(pozTut3));
            readimagefile(imgGhid3[mod][limba],COORD1(pozGhid));
            while(true)
            {
                clearmouseclick(WM_MOUSEMOVE);
                int x = mousex();
                int y = mousey();
                if(!esteDeasupra(x,y,pozTut3))
                {
                    readimagefile(imgTut3[mod][limba], COORD1(pozTut3));
                    readimagefile(imgCartoi[mod], COORD1(pozGhid));

                    break;
                }
            }
        }
        // limitari
        else if(esteDeasupra(x,y,pozTut4))
        {
            if(mod_sfx == PORNIT) sunetHover.play();
            readimagefile(imgTut4[(mod+1)%2][limba], COORD1(pozTut4));
            readimagefile(imgGhid4[mod][limba],COORD1(pozGhid));
            while(true)
            {
                clearmouseclick(WM_MOUSEMOVE);
                int x = mousex();
                int y = mousey();
                if(!esteDeasupra(x,y,pozTut4))
                {
                    readimagefile(imgTut4[mod][limba], COORD1(pozTut4));
                    readimagefile(imgCartoi[mod], COORD1(pozGhid));

                    break;
                }
            }
        }
        // replay
        else if(esteDeasupra(x,y,pozTut5))
        {
            if(mod_sfx == PORNIT) sunetHover.play();
            readimagefile(imgTut5[(mod+1)%2][limba], COORD1(pozTut5));
            readimagefile(imgGhid5[mod][limba],COORD1(pozGhid));
            while(true)
            {
                clearmouseclick(WM_MOUSEMOVE);
                int x = mousex();
                int y = mousey();
                if(!esteDeasupra(x,y,pozTut5))
                {
                    readimagefile(imgTut5[mod][limba], COORD1(pozTut5));
                    readimagefile(imgCartoi[mod], COORD1(pozGhid));

                    break;
                }
            }
        }
    }
}

void Setari()
{
    setfillstyle(SOLID_FILL, fundal);
    bar(0,0,LUNGIME,LATIME);

    fundal == WHITE ? setcolor(BLACK):setcolor(WHITE);
    setbkcolor(fundal);

    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(3,0,4);

    readimagefile(imgMuzica[mod][mod_muzica], COORD1(pozMuzica));
    readimagefile(imgSfx[mod][mod_sfx], COORD1(pozSfx));
    readimagefile(imgInapoi[mod], COORD1(pozInapoi));

    readimagefile(imgAspect[mod][limba], COORD1(pozAspect));

    readimagefile(imgSageataL[mod], COORD1(pozA1a));
    readimagefile(imgPiesaA[aspect_j1], COORD1(pozA1));
    readimagefile(imgSageataR[mod], COORD1(pozA1b));

    readimagefile(imgSageataL[mod], COORD1(pozA2a));
    readimagefile(imgPiesaB[aspect_j2], COORD1(pozA2));
    readimagefile(imgSageataR[mod], COORD1(pozA2b));

    readimagefile(imgSageataL[mod], COORD1(pozA3a));
    readimagefile(imgTabla[1][aspect_tabla], COORD1(pozA3));
    readimagefile(imgSageataR[mod], COORD1(pozA3b));

    while(true)
    {
        clearmouseclick(WM_LBUTTONDOWN);
        clearmouseclick(WM_MOUSEMOVE);

        int x = mousex();
        int y = mousey();

        // buton muzica
        if(esteDeasupra(x,y,pozMuzica))
        {
            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_muzica == PORNIT) // muzica este pornita, deci o oprim
                    {
                        muzicaFundal.stop();
                        mod_muzica = OPRIT;
                    }
                    else
                    {
                        muzicaFundal.play();
                        mod_muzica = PORNIT;
                    }

                    readimagefile(imgMuzica[mod][mod_muzica], COORD1(pozMuzica));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozMuzica)) break;
                }
            }
        }
        // buton sfx
        else if(esteDeasupra(x,y,pozSfx))
        {
            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    mod_sfx = (mod_sfx+1) % 2;

                    readimagefile(imgSfx[mod][mod_sfx], COORD1(pozSfx));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozSfx)) break;
                }
            }
        }
        // buton inapoi
        else if(esteDeasupra(x,y,pozInapoi))
        {
            if(mod_sfx == PORNIT) sunetHover.play();
            readimagefile(imgInapoi[(mod+1)%2], COORD1(pozInapoi));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(mod_sfx == PORNIT) sunetInapoi.play();
                    Meniu();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozInapoi))
                    {
                        readimagefile(imgInapoi[mod], COORD1(pozInapoi));
                        break;
                    }
                }
            }
        }
        // buton <jucator1> stanga
        else if(esteDeasupra(x,y,pozA1a))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgSageataL[(mod+1)%2], COORD1(pozA1a));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetSchimba.play();

                    aspect_j1 = (aspect_j1-1+3) % 3;
                    readimagefile(imgPiesaA[aspect_j1], COORD1(pozA1));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozA1a))
                    {
                        readimagefile(imgSageataL[mod], COORD1(pozA1a));
                        break;
                    }
                }
            }
        }
        // buton <jucator1> dreapta
        else if(esteDeasupra(x,y,pozA1b))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgSageataR[(mod+1)%2], COORD1(pozA1b));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetSchimba.play();

                    aspect_j1 = (aspect_j1+1) % 3;
                    readimagefile(imgPiesaA[aspect_j1], COORD1(pozA1));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozA1b))
                    {
                        readimagefile(imgSageataR[mod], COORD1(pozA1b));
                        break;
                    }
                }
            }
        }
        // buton <jucator2> stanga
        else if(esteDeasupra(x,y,pozA2a))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgSageataL[(mod+1)%2], COORD1(pozA2a));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetSchimba.play();

                    aspect_j2 = (aspect_j2-1+3) % 3;
                    readimagefile(imgPiesaB[aspect_j2], COORD1(pozA2));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozA2a))
                    {
                        readimagefile(imgSageataL[mod], COORD1(pozA2a));
                        break;
                    }
                }
            }
        }
        // buton <jucator2> dreapta
        else if(esteDeasupra(x,y,pozA2b))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgSageataR[(mod+1)%2], COORD1(pozA2b));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetSchimba.play();

                    aspect_j2 = (aspect_j2+1) % 3;
                    readimagefile(imgPiesaB[aspect_j2], COORD1(pozA2));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozA2b))
                    {
                        readimagefile(imgSageataR[mod], COORD1(pozA2b));
                        break;
                    }
                }
            }
        }
        // buton <tabla> stanga
        else if(esteDeasupra(x,y,pozA3a))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgSageataL[(mod+1)%2], COORD1(pozA3a));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetSchimba.play();

                    aspect_tabla = (aspect_tabla-1 + 3) % 3;
                    readimagefile(imgTabla[1][aspect_tabla], COORD1(pozA3));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozA3a))
                    {
                        readimagefile(imgSageataL[mod], COORD1(pozA3a));
                        break;
                    }
                }
            }
        }
        // buton <tabla> dreapta
        else if(esteDeasupra(x,y,pozA3b))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgSageataR[(mod+1)%2], COORD1(pozA3b));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetSchimba.play();

                    aspect_tabla = (aspect_tabla+1) % 3;
                    readimagefile(imgTabla[1][aspect_tabla], COORD1(pozA3));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozA3b))
                    {
                        readimagefile(imgSageataR[mod], COORD1(pozA3b));
                        break;
                    }
                }
            }
        }
    }
}

void Credits()
{
    setfillstyle(SOLID_FILL, fundal);
    setcolor(fundal);
    bar(0,0,LUNGIME,LATIME);

    readimagefile(imgInfo[mod][limba], COORD1(pozInfo));
    readimagefile(imgInapoi[mod], COORD1(pozInapoi));

    while(true)
    {
        clearmouseclick(WM_LBUTTONDOWN);
        clearmouseclick(WM_MOUSEMOVE);

        int x = mousex();
        int y = mousey();

        // buton inapoi
        if(esteDeasupra(x,y,pozInapoi))
        {
            if(mod_sfx == PORNIT) sunetHover.play();
            readimagefile(imgInapoi[(mod+1)%2], COORD1(pozInapoi));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_sfx == PORNIT) sunetInapoi.play();
                    Meniu();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozInapoi))
                    {
                        readimagefile(imgInapoi[mod], COORD1(pozInapoi));
                        break;
                    }
                }
            }
        }
    }
}

void PVP()
{
    // initializeaza seed
    srand(time(NULL));

    // curata ecran
    setfillstyle(SOLID_FILL, fundal);
    bar(0,0,LUNGIME,LATIME);

    // butoane muzica
    readimagefile(imgMuzica[mod][mod_muzica], COORD1(pozMuzica));
    readimagefile(imgSfx[mod][mod_sfx], COORD1(pozSfx));

    // resetare text
    strcpy(txt_infoP1[0],"randul tau"); strcpy(txt_infoP1[1],"your turn");
    strcpy(txt_infoP2[0],"randul tau"); strcpy(txt_infoP2[1],"your turn");
    strcpy(txt_infoMutari[0],"mutari ramase: "); strcpy(txt_infoMutari[1],"turns left: ");
    strcpy(txt_infoTimer,"00:");

    // informatii text
    fundal == WHITE ? setcolor(BLACK):setcolor(WHITE);
    setbkcolor(fundal);
    settextjustify(CENTER_TEXT, CENTER_TEXT);

    settextstyle(3,0,4);
    readimagefile(imgPiesaA[aspect_j1], COORD1(pozPiesaA)); // tabela
    outtextxy(COORD2(pozScor), "0 - 0");                    // de
    readimagefile(imgPiesaB[aspect_j2], COORD1(pozPiesaB)); // scor

    char txtNrMutari[12]; itoa(nr_mutari, txtNrMutari);
    char txtInfoMutari[LEN]; strcpy(txtInfoMutari, txt_infoMutari[limba]); strcat(txtInfoMutari,txtNrMutari);
    settextstyle(8,0,3);
    outtextxy(COORD2(pozRamase), txtInfoMutari);

    char txtTimp[12]; itoa(nr_timp, txtTimp);
    if(nr_timp < 10) txtTimp[1] = txtTimp[0], txtTimp[0] = '0', txtTimp[2] = NULL;
    char txtInfoTimer[LEN]; strcpy(txtInfoTimer, txt_infoTimer); strcat(txtInfoTimer,txtTimp);
    settextstyle(3,0,8);
    outtextxy(COORD2(pozTimer), txtInfoTimer); // timer

    // istoric mutari
    readimagefile(imgIstoric[mod], COORD1(pozIstoric));
    pozMutare[0] = pozIstoric[limba][0]+12;
    pozMutare[1] = pozIstoric[limba][1]+12;

    // buton abandon
    readimagefile(imgAbandon[mod][limba], COORD1(pozAbandon));

    // joc
    initializareTabla();

    scor_j1 = scor_j2 = 0;
    mutari_ramase = nr_mutari;
    timp_limita = nr_timp;
  	timp_expirat = joc_terminat = false;

  	strcpy(txt_logs[0], "NULL");

  	settextstyle(8,0,2);
  	outtextxy(COORD2(pozRand1), txt_infoP1[limba]);

    while(joc_terminat == false)
    {
        timp_limita = nr_timp;
        mutarePiesa();
        joc_terminat = verificaSfarsit();
    }

    scor_j1 == scor_j2 ? Sfarsit(2,0) : Sfarsit(1,0);
    return;
}

void PVIA()
{
    // initializeaza seed
    srand(time(NULL));

    // curata ecran
    setfillstyle(SOLID_FILL, fundal);
    bar(0,0,LUNGIME,LATIME);

    // butoane muzica
    readimagefile(imgMuzica[mod][mod_muzica], COORD1(pozMuzica));
    readimagefile(imgSfx[mod][mod_sfx], COORD1(pozSfx));

    // resetare text
    strcpy(txt_infoP1[0],"randul tau"); strcpy(txt_infoP1[1],"your turn");
    strcpy(txt_infoP2[0],"randul tau"); strcpy(txt_infoP2[1],"your turn");
    strcpy(txt_infoMutari[0],"mutari ramase: "); strcpy(txt_infoMutari[1],"turns left: ");
    strcpy(txt_infoTimer,"00:");

    // informatii text
    fundal == WHITE ? setcolor(BLACK):setcolor(WHITE);
    setbkcolor(fundal);
    settextjustify(CENTER_TEXT, CENTER_TEXT);

    settextstyle(3,0,4);
    readimagefile(imgPiesaA[aspect_j1], COORD1(pozPiesaA)); // tabela
    outtextxy(COORD2(pozScor), "0 - 0");                    // de
    readimagefile(imgPiesaB[aspect_j2], COORD1(pozPiesaB)); // scor

    char txtNrMutari[12]; itoa(nr_mutari, txtNrMutari);
    char txtInfoMutari[LEN]; strcpy(txtInfoMutari, txt_infoMutari[limba]); strcat(txtInfoMutari,txtNrMutari);
    settextstyle(8,0,3);
    outtextxy(COORD2(pozRamase), txtInfoMutari);

    char txtTimp[12]; itoa(nr_timp, txtTimp);
    if(nr_timp < 10) txtTimp[1] = txtTimp[0], txtTimp[0] = '0', txtTimp[2] = NULL;
    char txtInfoTimer[LEN]; strcpy(txtInfoTimer, txt_infoTimer); strcat(txtInfoTimer,txtTimp);
    settextstyle(3,0,8);
    outtextxy(COORD2(pozTimer), txtInfoTimer); // timer

    // istoric mutari
    readimagefile(imgIstoric[mod], COORD1(pozIstoric));
    pozMutare[0] = pozIstoric[limba][0]+12;
    pozMutare[1] = pozIstoric[limba][1]+12;

    // buton abandon
    readimagefile(imgAbandon[mod][limba], COORD1(pozAbandon));

    // joc
    initializareTabla();

    sizeAI = 0; // nr piese ai
    scor_j1 = scor_j2 = 0;
    mutari_ramase = nr_mutari;
    timp_limita = nr_timp;
  	timp_expirat = joc_terminat = false;

  	strcpy(txt_logs[0], "NULL");

  	settextstyle(8,0,2);
  	outtextxy(COORD2(pozRand1), txt_infoP1[limba]);

    while(joc_terminat == false)
    {
        timp_limita = nr_timp;
        mutarePiesa(0,1);
        joc_terminat = verificaSfarsit();
        if(joc_terminat == false)
        {
            timp_limita = nr_timp;
            mutarePiesa(1,0);
            joc_terminat = verificaSfarsit();
        }
    }

    scor_j1 == scor_j2 ? Sfarsit(2,1) : Sfarsit(1,1);
    return;
}

void Reluare()
{
    // curata ecran
    setfillstyle(SOLID_FILL, fundal);
    bar(0,0,LUNGIME,LATIME);

    // butoane muzica
    readimagefile(imgMuzica[mod][mod_muzica], COORD1(pozMuzica));
    readimagefile(imgSfx[mod][mod_sfx], COORD1(pozSfx));

    // buton inapoi
    readimagefile(imgInapoi[mod], COORD1(pozInapoi));

    // resetare text
    strcpy(txt_infoP1[0],"randul tau"); strcpy(txt_infoP1[1],"your turn");
    strcpy(txt_infoP2[0],"randul tau"); strcpy(txt_infoP2[1],"your turn");
    strcpy(txt_infoMutari[0],"mutari ramase: "); strcpy(txt_infoMutari[1],"turns left: ");
    strcpy(txt_infoTimer,"00:");

    // informatii text
    fundal == WHITE ? setcolor(BLACK):setcolor(WHITE);
    setbkcolor(fundal);
    settextjustify(CENTER_TEXT, CENTER_TEXT);

    // tabela de scor
    settextstyle(3,0,4);
    readimagefile(imgPiesaA[aspect_j1], COORD1(pozPiesaA));
    outtextxy(COORD2(pozScor), "0 - 0");
    readimagefile(imgPiesaB[aspect_j2], COORD1(pozPiesaB));

    // citeste fisierul de replay
    ifstream in("replay.info");

    char c;
    int razboi_in4;

    if(in)
    {
        in>>c; in.ignore();
        razboi_in4 = (c == '0' ? 1:2);
    }

    char txt_replay[102][LEN];
    mutari_ramase = 0;

    while(in && !in.eof()) // cate mutari s-au jucat ?
    {
        in.get(txt_replay[mutari_ramase++],LEN);
        in.ignore();
    }
    mutari_ramase--; // fara mesajul de la final
    if(mutari_ramase == -1) mutari_ramase = 0;

    // afiseaza <nr mutari ramase>
    char txtNrMutari[12]; itoa(mutari_ramase, txtNrMutari);
    char txtInfoMutari[LEN]; strcpy(txtInfoMutari, txt_infoMutari[limba]); strcat(txtInfoMutari,txtNrMutari);
    settextstyle(8,0,3);
    outtextxy(COORD2(pozRamase), txtInfoMutari);

    // afiseaza ghid utilizare mouse
    char imgMouse[2][2][LEN] = {"img/mouseDRO.jpg","img/mouseDEN.jpg","img/mouseNRO.jpg","img/mouseNEN.jpg"};
    readimagefile(imgMouse[mod][limba], 1320, 696, 1512, 888);

    // joc
    int scor1 = 0, scor2 = 0;
    initializareTabla(razboi_in4);

  	settextstyle(8,0,2);
  	outtextxy(COORD2(pozRand1), txt_infoP1[limba]);


  	int index_mutare = 0;
  	bool hover_inapoi = false;

  	while(true)
    {
        clearmouseclick(WM_MOUSEMOVE);
        clearmouseclick(WM_LBUTTONDOWN);
        clearmouseclick(WM_LBUTTONDBLCLK);
        clearmouseclick(WM_RBUTTONDOWN);
        clearmouseclick(WM_RBUTTONDBLCLK);

        int x = mousex();
        int y = mousey();

        // hover buton inapoi
        if(esteDeasupra(x,y,pozInapoi))
        {
            if(mod_sfx == PORNIT && hover_inapoi == false) sunetHover.play();
            hover_inapoi = true;
            readimagefile(imgInapoi[(mod+1)%2], COORD1(pozInapoi));
        }
        else
        {
            hover_inapoi = false;
            readimagefile(imgInapoi[mod], COORD1(pozInapoi));
        }

        if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            clearmouseclick(WM_LBUTTONDBLCLK);

            // buton muzica
            if(esteDeasupra(x,y,pozMuzica))
            {
                if(mod_muzica == PORNIT) // muzica este pornita, deci o oprim
                {
                    muzicaFundal.stop();
                    mod_muzica = OPRIT;
                }
                else
                {
                    muzicaFundal.play();
                    mod_muzica = PORNIT;
                }

                readimagefile(imgMuzica[mod][mod_muzica], COORD1(pozMuzica));
            }
            // buton sfx
            else if(esteDeasupra(x,y,pozSfx))
            {
                mod_sfx = (mod_sfx+1) % 2;
                readimagefile(imgSfx[mod][mod_sfx], COORD1(pozSfx));
            }
            // buton inapoi
            else if(esteDeasupra(x,y,pozInapoi))
            {
                if(mod_sfx == PORNIT) sunetInainte.play();
                JocNou();
                return;
            }
            else // vizualizeaza mutarea urmatoare
            {
                if(index_mutare < mutari_ramase)
                {
                    char mutare[LEN]; strcpy(mutare,txt_replay[index_mutare]);

                    for(int i = 3; i < strlen(mutare); i++)
                    {
                        if(mutare[i] == 'x') break; // jucatorul nu a mutat in aceasta tura

                        if(mutare[i] == '(') // sterge o piesa; "(-cl)" c = coloana, l = linie
                        {
                            int coloana = (mutare[i+2]-'a');
                            int linie = 8-(mutare[i+3]-'0');

                            tabla[linie][coloana] == JUCATOR1 ? ++scor2 : ++scor1;

                            tabla[linie][coloana] *= (-1);
                            stergePiesa(linie,coloana);
                            i+=4;
                        }
                        else if(mutare[i] != ' ') // muta o piesa; "c1l1-c2l2"
                        {
                            int coloana1 = (mutare[i]-'a');
                            int linie1 = 8-(mutare[i+1]-'0');
                            int coloana2 = (mutare[i+3]-'a');
                            int linie2 = 8-(mutare[i+4]-'0');

                            tabla[linie2][coloana2] = (index_mutare%2)+1;
                            stergePiesa(linie1,coloana1);
                            deseneazaPiesa(linie2,coloana2,(index_mutare%2)+1);
                            i+=4;
                        }
                    }

                    index_mutare++;

                    // actualizare mutari ramase si text nr mutari
                    char txtNrMutari[12]; itoa(mutari_ramase-index_mutare, txtNrMutari);
                    char txtInfoMutari[LEN]; strcpy(txtInfoMutari,txt_infoMutari[limba]); strcat(txtInfoMutari,txtNrMutari);
                    settextstyle(8,0,3);
                    bar(pozRamase[0]-200,pozRamase[1]-100,pozRamase[0]+150,pozRamase[1]+100);
                    outtextxy(COORD2(pozRamase), txtInfoMutari);

                    // actualizare text scor
                    settextstyle(3,0,4);
                    char txtScor1[12], txtScor2[12]; itoa(scor1,txtScor1); itoa(scor2,txtScor2);
                    char txtScor[LEN] = ""; strcat(txtScor,txtScor1); strcat(txtScor," - "); strcat(txtScor,txtScor2);
                    outtextxy(COORD2(pozScor), txtScor);

                    // actualizare text tura jucator
                    settextstyle(8,0,3);
                    bar(pozRand1[0]-80,pozRand1[1]-15,pozRand1[0]+80,pozRand1[1]+15);
                    bar(pozRand2[0]-80,pozRand2[1]-15,pozRand2[0]+80,pozRand2[1]+15);

                    if((index_mutare%2)+1 == JUCATOR1) outtextxy(COORD2(pozRand1), txt_infoP1[limba]);
                    else outtextxy(COORD2(pozRand2), txt_infoP2[limba]);

                    if(index_mutare == mutari_ramase)
                    {
                        bar(pozRand1[0]-80,pozRand1[1]-15,pozRand1[0]+80,pozRand1[1]+15);
                        bar(pozRand2[0]-80,pozRand2[1]-15,pozRand2[0]+80,pozRand2[1]+15);

                        char txtRezultat[LEN]; strcpy(txtRezultat, txt_replay[mutari_ramase]);
                        for(int i = 0; i < strlen(txtRezultat); i++)
                            if(strchr(":\n\0", txtRezultat[i]))
                            {
                                txtRezultat[i] = NULL;
                                break;
                            }

                        if(strcmp(txtRezultat,"egalitate") == 0 || strcmp(txtRezultat,"draw") == 0)
                        {
                            (limba == RO) ? strcpy(txtRezultat,"egalitate") : strcpy(txtRezultat,"draw");
                            outtextxy(COORD2(pozRand1), txtRezultat);
                            outtextxy(COORD2(pozRand2), txtRezultat);
                        }
                        else if(strcmp(txtRezultat,"castigator: jucator1") == 0 || strcmp(txtRezultat,"winner: player1") == 0)
                        {
                            (limba == RO) ? strcpy(txtRezultat,"castigator") : strcpy(txtRezultat,"winner");
                            outtextxy(COORD2(pozRand1), txtRezultat);
                        }
                        else
                        {
                            (limba == RO) ? strcpy(txtRezultat,"castigator") : strcpy(txtRezultat,"winner");
                            outtextxy(COORD2(pozRand1), txtRezultat);
                        }
                    }
                }
            }
        }
        else if((ismouseclick(WM_RBUTTONDOWN) || ismouseclick(WM_RBUTTONDBLCLK)) && index_mutare > 0) // da in spate cu o mutare
        {
            index_mutare--;

            char mutare[LEN]; strcpy(mutare,txt_replay[index_mutare]);

            for(int i = 3; i < strlen(mutare); i++)
            {
                if(mutare[i] == 'x') break; // jucatorul nu a mutat in aceasta tura

                if(mutare[i] == '(') // pun la loc piesa stearsa, refac scorurile
                {
                    int coloana = (mutare[i+2]-'a');
                    int linie = 8-(mutare[i+3]-'0');

                    tabla[linie][coloana] *= (-1);
                    tabla[linie][coloana] == JUCATOR1 ? --scor2 : --scor1;

                    deseneazaPiesa(linie,coloana,tabla[linie][coloana]);
                    i+=4;
                }
                else if(mutare[i] != ' ') // anulez mutarea, pun piesa unde era inainte
                {
                    int coloana1 = (mutare[i]-'a');
                    int linie1 = 8-(mutare[i+1]-'0');
                    int coloana2 = (mutare[i+3]-'a');
                    int linie2 = 8-(mutare[i+4]-'0');

                    tabla[linie1][coloana1] = (index_mutare%2)+1;
                    stergePiesa(linie2,coloana2);
                    deseneazaPiesa(linie1,coloana1,(index_mutare%2)+1);
                    i+=4;
                }
            }

            // actualizare mutari ramase si text nr mutari
            char txtNrMutari[12]; itoa(mutari_ramase-index_mutare, txtNrMutari);
            char txtInfoMutari[LEN]; strcpy(txtInfoMutari,txt_infoMutari[limba]); strcat(txtInfoMutari,txtNrMutari);
            settextstyle(8,0,3);
            bar(pozRamase[0]-200,pozRamase[1]-100,pozRamase[0]+150,pozRamase[1]+100);
            outtextxy(COORD2(pozRamase), txtInfoMutari);

            // actualizare text tura jucator
            bar(pozRand1[0]-80,pozRand1[1]-15,pozRand1[0]+80,pozRand1[1]+15);
            bar(pozRand2[0]-80,pozRand2[1]-15,pozRand2[0]+80,pozRand2[1]+15);

            if((index_mutare%2)+1 == JUCATOR1) outtextxy(COORD2(pozRand1), txt_infoP1[limba]);
            else outtextxy(COORD2(pozRand2), txt_infoP2[limba]);

            // actualizare text scor
            settextstyle(3,0,4);
            char txtScor1[12], txtScor2[12]; itoa(scor1,txtScor1); itoa(scor2,txtScor2);
            char txtScor[LEN] = ""; strcat(txtScor,txtScor1); strcat(txtScor," - "); strcat(txtScor,txtScor2);
            outtextxy(COORD2(pozScor), txtScor);
        }
    }
}

void Sfarsit(int cod, int altcod) // 0 = capitulare, 1 = victorie meci complet, 2 = egalitate meci complet
{
    settextstyle(8,0,3);
    settextjustify(CENTER_TEXT,CENTER_TEXT);

    if(cod == 0) // un jucator a capitulat
    {
            const char imgCapitulat[2][2][LEN] = {"img/capitulatDRO.jpg", "img/capitulatDEN.jpg", "img/capitulatNRO.jpg", "img/capitulatNEN.jpg"};
            if(mod_sfx == PORNIT) sunetEgal.play();

            bar(pozRand1[0]-80,pozRand1[1]-15,pozRand1[0]+80,pozRand1[1]+15);
            bar(pozRand2[0]-80,pozRand2[1]-15,pozRand2[0]+80,pozRand2[1]+15);

            readimagefile(imgCapitulat[mod][limba], COORD1(pozRezultat));

            if(turaJucator() == JUCATOR2)
            {
                limba == RO ? outtextxy(COORD2(pozRand1), "castigator") : outtextxy(COORD2(pozRand1), "winner");
                castigator = JUCATOR1;
            }
            else
            {
                limba == RO ? outtextxy(COORD2(pozRand2), "castigator") : outtextxy(COORD2(pozRand2), "winner");
                castigator = JUCATOR2;
            }
    }
    else if(cod == 1) // un jucator a castigat meciul
    {
        if(altcod == 1 && scor_j2 > scor_j1)
        {
            const char imgInfrant[2][2][LEN] = {"img/infrantDRO.jpg", "img/infrantDEN.jpg", "img/infrantNRO.jpg", "img/infrantNEN.jpg"};
            if(mod_sfx == PORNIT) sunetEgal.play();

            bar(pozRand1[0]-80,pozRand1[1]-15,pozRand1[0]+80,pozRand1[1]+15);
            bar(pozRand2[0]-80,pozRand2[1]-15,pozRand2[0]+80,pozRand2[1]+15);

            limba == RO ? outtextxy(COORD2(pozRand2), "castigator") : outtextxy(COORD2(pozRand2), "winner");
            castigator = JUCATOR2;

            readimagefile(imgInfrant[mod][limba], COORD1(pozRezultat));
        }
        else
        {
            if(mod_sfx == PORNIT) sunetVictorie.play();

            bar(pozRand1[0]-80,pozRand1[1]-15,pozRand1[0]+80,pozRand1[1]+15);
            bar(pozRand2[0]-80,pozRand2[1]-15,pozRand2[0]+80,pozRand2[1]+15);

            if(scor_j1 > scor_j2)
            {
                limba == RO ? outtextxy(COORD2(pozRand1), "castigator") : outtextxy(COORD2(pozRand1), "winner");
                castigator = JUCATOR1;
            }
            else
            {
                limba == RO ? outtextxy(COORD2(pozRand2), "castigator") : outtextxy(COORD2(pozRand2), "winner");
                castigator = JUCATOR2;
            }

            readimagefile(imgVictorie[mod][limba], COORD1(pozRezultat));
        }
    }
    else // egalitate
    {
        if(mod_sfx == PORNIT) sunetEgal.play();

        bar(pozRand1[0]-80,pozRand1[1]-15,pozRand1[0]+80,pozRand1[1]+15);
        bar(pozRand2[0]-80,pozRand2[1]-15,pozRand2[0]+80,pozRand2[1]+15);

        castigator = 0;
        readimagefile(imgEgal[mod][limba], COORD1(pozRezultat));
    }

    readimagefile(imgSfarsit[mod], COORD1(pozSfarsit));

    readimagefile(imgRestart[mod], COORD1(pozRestart));
    readimagefile(imgSalveaza[mod][limba], COORD1(pozSalveaza));
    readimagefile(imgLaMeniu[mod][limba], COORD1(pozLaMeniu));

    bool joc_salvat = false;

    while(true)
    {
        clearmouseclick(WM_LBUTTONDOWN);
        clearmouseclick(WM_MOUSEMOVE);

        int x = mousex();
        int y = mousey();

        // buton muzica
        if(esteDeasupra(x,y,pozMuzica))
        {
            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    if(mod_muzica == PORNIT) // muzica este pornita, deci o oprim
                    {
                        muzicaFundal.stop();
                        mod_muzica = OPRIT;
                    }
                    else
                    {
                        muzicaFundal.play();
                        mod_muzica = PORNIT;
                    }

                    readimagefile(imgMuzica[mod][mod_muzica], COORD1(pozMuzica));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozMuzica)) break;
                }
            }
        }
        // buton sfx
        else if(esteDeasupra(x,y,pozSfx))
        {
            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONDBLCLK);
                    mod_sfx = (mod_sfx+1) % 2;

                    readimagefile(imgSfx[mod][mod_sfx], COORD1(pozSfx));
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozSfx)) break;
                }
            }
        }
        // buton restart
        else if(esteDeasupra(x,y,pozRestart))
        {
            if(mod_sfx == PORNIT) sunetHover.play();
            readimagefile(imgRestart[(mod+1)%2], COORD1(pozRestart));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(mod_sfx == PORNIT) sunetInainte.play();

                    Restart(altcod); // restart pvp? (0) sau ia? (1)
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozRestart))
                    {
                        readimagefile(imgRestart[mod], COORD1(pozRestart));
                        break;
                    }
                }
            }
        }
        // buton salveaza meci
        else if(joc_salvat == false && esteDeasupra(x,y,pozSalveaza))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgSalveaza[(mod+1)%2][limba], COORD1(pozSalveaza));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(mod_sfx == PORNIT) sunetInainte.play();

                    joc_salvat = true;
                    Salveaza();

                    readimagefile(imgSalvat[mod][limba], COORD1(pozSalveaza));
                    break;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozSalveaza))
                    {
                        readimagefile(imgSalveaza[mod][limba], COORD1(pozSalveaza));
                        break;
                    }
                }
            }
        }
        // buton inapoi la meniu
        else if(esteDeasupra(x,y,pozLaMeniu))
        {
            if(mod_sfx == PORNIT) sunetHover.play();

            readimagefile(imgLaMeniu[(mod+1)%2][limba], COORD1(pozLaMeniu));

            while(true)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(mod_sfx == PORNIT) sunetInainte.play();

                    muzicaFundal.openFromFile("audio/bgm.wav");
                    if(mod_muzica == PORNIT)
                    {
                        muzicaFundal.setLoop(true); muzicaFundal.setVolume(50.f); muzicaFundal.play();
                    }
                    Meniu();
                    return;
                }
                if(ismouseclick(WM_MOUSEMOVE))
                {
                    clearmouseclick(WM_MOUSEMOVE);
                    x = mousex();
                    y = mousey();

                    if(!esteDeasupra(x,y,pozLaMeniu))
                    {
                        readimagefile(imgLaMeniu[mod][limba], COORD1(pozLaMeniu));
                        break;
                    }
                }
            }
        }
    }
}

void Restart(int cod) // 0 = pvp, 1 = pvia
{
    initializareTabla(cod);
    if(cod == 0) PVP();
    else PVIA();
}

void Salveaza()
{
    ofstream out("replay.info");
    out << (nr_safe != 0) << '\n'; // razboi in 8 sau in 4?

    int ind = 0;
    while(strcmp(txt_logs[ind],"NULL")) out << txt_logs[ind++] << '\n';

    if(castigator == 0) out << (limba == RO ? "egalitate":"draw");
    else
    {
        if(castigator == 1) out << (limba == RO ? "castigator: jucator1":"winner: player1");
        else out << (limba == RO ? "castigator: jucator2":"winner: player2");
    }

    out.close();
}

int main()
{
    initwindow(LUNGIME,LATIME, "Razboi în Opt | War in Eight");

    Initializari();
  	Meniu();

    getch();
    closegraph();
    return 0;
}
