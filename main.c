/**********************************************************************************
* I C finns ett f�tal standarddatastr�mmar som alla utg�r olika typer av filpekare 
* (FILE* fr�n biblioteket stdio.h):
* 
* Standardenheten stdout anv�nds f�r utskrift till konsolen.
* Standardinenheten stdin anv�nds f�r inmatning fr�n konsolen.
* Standardfelenheten stderr anv�nds f�r felutskrift, vanligtvis via konsolen.
* 
* F�rutom ovanst�ende standardstr�mmar kan anv�ndaren skriva till eller l�sa 
* fr�n en specifik fils�kv�g genom att deklarera en egen filstr�m via en 
* filpekare, d�r ett flertal modes kan v�lja, exempelvis w (write) f�r att
* skriva till en fil, d�r befintligt inneh�ll skrivs �ver, r (read) f�r att
* l�sa inneh�ll fr�n en fil samt a (append) f�r att l�gga till inneh�ll i en
* fil utan att radera befintligt inneh�ll.
* 
* F�r att �ppna en fil f�r skrivning kan f�ljande instruktion anv�ndas:
* FILE* file = fopen("filepath.txt", "w);
* 
* F�r att �ppna en fil f�r att bifoga inneh�ll kan f�ljande instruktion anv�ndas:
* FILE* file = fopen("filepath.txt", "a");
* 
* F�r att �ppna en fil f�r l�sning kan f�ljande instruktion anv�ndas:
* FILE* file = fopen("filepath.txt", "r");
* 
* Om filen inte gick att �ppna returneras en nullpekare. Kontroll av 
* returv�rdet efter anrop av funktionen fopen b�r d�rmed kontrolleras.
* Om filen inte gick att �ppna b�r funktionen avslutas, alternativt med
* ett felmeddelande:
* 
* if (!fstream)
* {
*    fprintf(stderr, "Could not open file at path %s!\n\n", filepath);
*    return;
* }
* 
* Filskrivning kan sedan ske via anrop av funktionen fprintf:
* fprintf(fstream, "This data is written to the file!\n");
* 
* Precis som funktionen printf kan inneh�ll fr�n variabler och konstanter
* skrivas via anv�ndning av motsvarande formatspecificerare, exempelvis
* fprintf(fstream, "Writing integer %d\n" 5);
* fprintf(fstream, "My name is %s\n", name);
* 
* F�r att l�sa en rad fr�n en fil och spara i en str�ng d�pt s kan anrop av
* funktionen fgets anv�ndas, vilket ocks� g�ller f�r inl�sning fr�n konsolen:
* fgets(s, sizeof(s), fstream);
* 
* Efter skrivning eller l�sning �r f�rdig b�r filen st�ngas, vilket �stadkommes
* via anrop av funktionen fclose, d�r aktuell filpekare passeras som argument:
* fclose(fstream);
**********************************************************************************/

/* Inkluderingsdirektiv: */
#include <stdio.h>

/**********************************************************************************
* Skriver en rad med text till en fil. Eventuellt f�reg�ende inneh�ll raderas. 
* Ing�ende argument filepath utg�r fils�kv�gen, medan s utg�r textraden som skall 
* skrivas till filen.
**********************************************************************************/
static void file_write(const char* filepath, const char* s)
{
   FILE* fstream = fopen(filepath, "w");

   if (!fstream)
   {
      fprintf(stderr, "Could not open file at path %s!\n\n", filepath);
      return;
   }

   fprintf(fstream, "%s\n", s);
   fclose(fstream);
   return;
}

/**********************************************************************************
* Bifogar en rad med text till en fil. Eventuellt f�reg�ende inneh�ll bibeh�lls
* och det nya inneh�llet bifogas l�ngst ned i filen. Ing�ende argument filepath 
* utg�r fils�kv�gen, medan s utg�r textraden som skall bifogas.
**********************************************************************************/
static void file_append(const char* filepath, const char* s)
{
   FILE* fstream = fopen(filepath, "a");

   if (!fstream)
   {
      fprintf(stderr, "Could not open file at path %s!\n\n", filepath);
      return;
   }

   fprintf(fstream, "%s\n", s);
   fclose(fstream);
   return;
}

/**********************************************************************************
* L�ser varje rad fr�n en fil en efter en och skriver ut i konsolen. Ing�ende
* argument filepath utg�r fils�kv�gen som l�sning skall ske fr�n.
**********************************************************************************/
static void file_read(const char* filepath)
{
   FILE* fstream = fopen(filepath, "r"); 
   
   if (!fstream)
   {
      fprintf(stderr, "Could not open file at path %s!\n\n", filepath);
      return;
   }

   char s[100];
   s[0] = '\0';
   while (fgets(s, sizeof(s), fstream))
      fprintf(stdout, "%s", s);
   fclose(fstream);
   return;
}

/**********************************************************************************
* Skriver en rad till filen data.txt. Bifogar sedan ytterligare en rad till 
* samma fil. L�ser sedan in inneh�llet och skriver ut i konsolen.
**********************************************************************************/
int main(void)
{
   file_write("data.txt", "C programming is fun!");
   file_append("data.txt", "Especially pointer aritmetic!");
   file_read("data.txt");
   return 0;
}